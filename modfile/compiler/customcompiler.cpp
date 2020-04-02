/*===========================================================================
 *
 * File:	Customcompiler.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "customcompiler.h"


/*===========================================================================
 *
 * Class CCustomCompiler Constructor
 *
 *=========================================================================*/
CCustomCompiler::CCustomCompiler () {
  m_pRecordHandler = NULL;
  m_pScript        = NULL;

  m_Parser.SetErrorInfo(&m_ErrorInfo);

  m_ErrorInfo.ErrorCount   = 0;
  m_ErrorInfo.WarningCount = 0;
}
/*===========================================================================
 *		End of Class CCustomCompiler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - void Destroy (void);
 *
 *=========================================================================*/
void CCustomCompiler::Destroy (void) {

  m_Tokens.Destroy();
  m_TokenTypes.Destroy();
  m_CharClasses.Destroy();
  m_TokenTables.Destroy();
  m_Parser.Destroy();

  m_ErrorInfo.ErrorCount   = 0;
  m_ErrorInfo.WarningCount = 0;
  m_ErrorInfo.Errors.Destroy();
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - bool Compile (pScript);
 *
 *=========================================================================*/
bool CCustomCompiler::Compile (CObScptRecord* pScript) {
  CScanSourceString ScanSource;
  bool              Result;

  if (pScript == NULL) {
    AddObGeneralError("No script to compile!");
    return (false);
  }

  m_pScript = pScript;
  ScanSource.SetString(m_pScript->GetScriptText());

  m_Parser.SetRecordHandler(m_pRecordHandler);
  m_Parser.SetTokens(&m_Tokens);
  m_Parser.SetTokenTypes(&m_TokenTypes);
  m_Parser.SetScript(m_pScript);

  m_ErrorInfo.ErrorCount   = 0;
  m_ErrorInfo.WarningCount = 0;
  m_ErrorInfo.Errors.Destroy();

  //SystemLog.Printf("Creating script tokens...");
  Result = Tokenize(&ScanSource);
  if (!Result) return (false);
  //if (!Result) SystemLog.Printf("Failed to tokenize script!");

  //SystemLog.Printf("Compiling script...");
  Result = m_Parser.Parse();

 /* if (!Result) 
    SystemLog.Printf("Failed to compile script!");
  else
    SystemLog.Printf("Successfully compiled script!"); //*/

  return (Result);
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::Compile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - bool Load (pFilename);
 *
 *=========================================================================*/
bool CCustomCompiler::Load (const char* pFilename) {
  CObFile  File;
  CSString LineBuffer;
  bool	   Result;

	/* Clear the current data */
  Destroy();

  Result = File.Open(pFilename, "rt");
  if (!Result) return (false);

  while (!File.IsEOF()) {
    Result = File.ReadLine(LineBuffer);
    if (!Result) break;

    LineBuffer.Trim();

    if (LineBuffer.CompareNoCase("charclasses") == 0) {
      Result &= m_CharClasses.Load(File);
    }
    else if (LineBuffer.CompareNoCase("tokens") == 0) {
      Result &= m_TokenTypes.Load(File);
    }
    else if (LineBuffer.CompareNoCase("begin") == 0) {
      Result &= m_TokenTables.LoadNewTable(File, NULL);
    }
    else if (!LineBuffer.IsEmpty()) {
      Result &= m_TokenTables.LoadNewTable(File, LineBuffer);
    }

  }
  
  Result &= m_TokenTables.ResolveReferences(m_TokenTypes, m_CharClasses);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - int AddError (ErrorID, Pos, pString, ...);
 *
 *=========================================================================*/
int CCustomCompiler::AddError (const int ErrorID, sourcepos_t& Pos, const char* pString, ...) {
  CObScriptError*     pNewError;
  obscripterrordef_t* pErrorDef;
  va_list             Args;

  pErrorDef = ObGetScriptErrorDef(ErrorID);

  if (pErrorDef != NULL && pErrorDef->Level <= 0) return (0);

  pNewError = new CObScriptError;
  m_ErrorInfo.Errors.Add(pNewError);

  pNewError->SetID(OB_SCRIPT_ERROR_BADCHARACTER);
  pNewError->SetErrorDef(pErrorDef);
  pNewError->SetPosition(Pos);

  va_start(Args, pString);
  pNewError->FormatMessageV(pString, Args);
  va_end(Args);

  if (pNewError->GetLevel() <= OB_SCRIPTERROR_LEVEL_WARNING) {
    ++m_ErrorInfo.WarningCount;
  }
  else {
    ++m_ErrorInfo.ErrorCount;
  }

  return pNewError->GetLevel();
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::AddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - CTokenType* RunTokenTable (pTable, pScanSource);
 *
 *=========================================================================*/
CTokenType* CCustomCompiler::RunTokenTable (CTokenTable* pTable, CScanSource* pScanSource) {
  CTokenTableRow* pRow;
  dword		  Index;
 
  m_CurrentToken.Empty();

RESTART_RunTokenTable:

  if (pTable == NULL) {
    AddObGeneralError("Invalid NULL table received in RunTokenTable()!");
    return (NULL);
  }

  if (m_GetTokenChar) {

    if (pScanSource->IsEOF()) {
      //AddObGeneralError("Unexpected end of file found!");
      //return (NULL);
      return m_TokenTypes.GetEndToken();
    }

    m_CurrentTokenChar = pScanSource->GetChar();
    m_GetTokenChar     = false;
  }

  for (Index = 0; Index < pTable->GetNumRows() + 1; ++Index) {
    if (Index >= pTable->GetNumRows()) {
      pRow = pTable->GetDefaultRow();
    }
    else {
      pRow = pTable->GetRow(Index);
      if (!pRow->DoesMatch(m_CurrentToken, m_CurrentTokenChar)) continue;
    }
    
    switch (pRow->GetResult().GetAction()) {
      case TOKEN_RESULT_IGNORE:
	m_GetTokenChar = true;
	goto RESTART_RunTokenTable;
      case TOKEN_RESULT_ERROR:
        //SystemLog.Printf("\tToken Error(%s%c): %s", m_CurrentToken, m_CurrentTokenChar, pRow->GetResult().GetMessage());

	AddError(OB_SCRIPT_ERROR_BADCHARACTER, pScanSource->GetSourcePos(), "Invalid character '%c' (0x%02X) found! %s", 
					m_CurrentTokenChar < 0x20 ? ' ' : m_CurrentTokenChar,
					m_CurrentTokenChar, pRow->GetResult().GetMessage());

	m_GetTokenChar = true;
	return (NULL);
      case TOKEN_RESULT_CONTINUE:
        m_CurrentToken += m_CurrentTokenChar;
	m_GetTokenChar  = true;
        goto RESTART_RunTokenTable;
      case TOKEN_RESULT_MOVETO:
        m_CurrentToken += m_CurrentTokenChar;
	m_GetTokenChar  = true;
        pTable = pRow->GetResult().GetTable();
        goto RESTART_RunTokenTable;
      case TOKEN_RESULT_JUMPTO:
        pTable = pRow->GetResult().GetTable();
        goto RESTART_RunTokenTable;
      case TOKEN_RESULT_JMPRETURN:
        //SystemLog.Printf("Found token %s (%s)", pRow->GetResult().GetToken()->GetName(), m_CurrentToken);
	return (pRow->GetResult().GetToken());
      case TOKEN_RESULT_RETURN:
        m_CurrentToken += m_CurrentTokenChar;
        //SystemLog.Printf("Found token %s (%s)", pRow->GetResult().GetToken()->GetName(), m_CurrentToken);
	m_GetTokenChar = true;
	return (pRow->GetResult().GetToken());
    }
  }
  
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::RunTokenTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - tokeninstance_t* AddTokenInstance (pToken, StartPos, EndPos);
 *
 *=========================================================================*/
tokeninstance_t* CCustomCompiler::AddTokenInstance (CTokenType* pToken, const sourcepos_t StartPos, const sourcepos_t EndPos) {
  tokeninstance_t* pNewToken;

  if (pToken == NULL) return (NULL);
  if (pToken->IsIgnoreType()) return (NULL);
      
  pNewToken = new tokeninstance_t;
  m_Tokens.Add(pNewToken);

  pNewToken->pToken   = pToken;
  pNewToken->StartPos = StartPos;
  pNewToken->EndPos   = EndPos;

  if (pToken->IsTrimFirst()) {
    pNewToken->Value = m_CurrentToken.c_str() + 1;
  }
  else {
    pNewToken->Value = m_CurrentToken;
  }

  if (pToken->IsTrimLast() && pNewToken->Value.GetLength() > 0) {
    pNewToken->Value.Truncate(pNewToken->Value.GetLength() - 1);
  }
  
  return (pNewToken);
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::AddTokenInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCustomCompiler Method - bool Tokenize (ScanSource);
 *
 *=========================================================================*/
bool CCustomCompiler::Tokenize (CScanSource* pScanSource) {
  tokeninstance_t* pNewToken;
  CTokenType*	   pToken;
  dword	           ErrorCount = 0;
  dword	           TokenCount = 0;
  sourcepos_t	   StartPos;

  m_Tokens.Destroy();

  if (pScanSource == NULL) {
    return (false);
  }

  pScanSource->MoveToStart();
  m_CurrentTokenChar = 0;
  m_GetTokenChar     = true;
  m_CurrentToken.Empty();

  do {
    StartPos = pScanSource->GetSourcePos();

    pToken = RunTokenTable(m_TokenTables.GetMainTable(), pScanSource);
    ++TokenCount;

    AddTokenInstance(pToken, StartPos, pScanSource->GetSourcePos());
    
    if (pToken == NULL) {
      ++ErrorCount;
    }
  } while (pToken != NULL && !pToken->IsEndToken());

	/* Ensure the token stream ends properly */
  if (pToken == NULL || !pToken->IsEndToken()) {
    pNewToken = new tokeninstance_t;
    m_Tokens.Add(pNewToken);
    pNewToken->pToken = m_TokenTypes.GetEndToken();
  }

  if (ErrorCount == 0) {
    //SystemLog.Printf("Successfully tokenized script!");
    //SystemLog.Printf("Last token of %u is '%s' (%s) LastChar=0x%02X", TokenCount, m_CurrentToken.c_str(), pToken ? pToken->GetName() : "null", (dword) m_CurrentTokenChar);
  }
  else {
    //SystemLog.Printf("%u Errors tokenizing script! LastChar = 0x%02X", ErrorCount, (dword) m_CurrentTokenChar);
  }

  return (ErrorCount == 0);
}
/*===========================================================================
 *		End of Class Method CCustomCompiler::Tokenize()
 *=========================================================================*/
