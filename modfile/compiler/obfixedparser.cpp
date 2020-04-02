/*===========================================================================
 *
 * File:	Obfixedparser.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obfixedparser.h"
#include "../records/obitem1record.h"


/*===========================================================================
 *
 * Class CObFixedParser Constructor
 *
 *=========================================================================*/
CObFixedParser::CObFixedParser() {
  m_pTokens        = NULL;
  m_pTokenTypes    = NULL;
  m_pRecordHandler = NULL;
  m_pScript        = NULL;
  m_pErrorInfo     = NULL;
  m_CurrentToken   = 0;
  m_OpCount        = 0;

  m_pCurrentFunction    = NULL;
  m_CurrentFuncParam    = 0;
  m_pOutputData         = NULL;
  m_OutputSize          = 0;
  m_AllocatedOutputSize = 0;
  
  ResetTokens();
}
/*===========================================================================
 *		End of Class CObFixedParser Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void Destroy (void);
 *
 *=========================================================================*/
void CObFixedParser::Destroy (void) {
  m_pTokens      = NULL;
  m_pTokenTypes  = NULL;
  m_CurrentToken = 0;
  m_OpCount      = 0;

  m_pCurrentFunction = NULL;
  m_CurrentFuncParam = 0;

  m_OutputSizeStack.Destroy();
  m_OutputSizeStack2.Destroy();
  m_LocalVariables.Destroy();
  m_References.Destroy();
  m_ExpressionStack.Destroy();
  m_FunctionParams.Destroy();

  DestroyOutputData();

  ResetTokens();
}
/*===========================================================================
 *		End of Class Method CObFixedParser::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int AddError (Code, pToken, pString, ...);
 *
 *=========================================================================*/
int CObFixedParser::AddError (const int Code, tokeninstance_t* pToken, const char* pString, ...) {
  obscripterrordef_t* pErrorDef;
  CObScriptError*     pNewError;
  CSString            Buffer;
  va_list             Args;
  int                 ReturnValue = OB_PARSE_RESULT_ERROR;

  if (m_pErrorInfo == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Lookup the error code */
  pErrorDef = ObGetScriptErrorDef(Code);

  if (pErrorDef != NULL) {
    if (pErrorDef->Level <= 0)
      return (0);
    else if (pErrorDef->Level <= OB_SCRIPTERROR_LEVEL_WARNING) {
      ++m_pErrorInfo->WarningCount;
      ReturnValue = OB_PARSE_RESULT_WARNING;
    }
    else {
      ++m_pErrorInfo->ErrorCount;
      ReturnValue = OB_PARSE_RESULT_ERROR;
    }
  }
  else {
    ++m_pErrorInfo->ErrorCount;
  }

  if (m_pErrorInfo == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Create the new error */
  pNewError = new CObScriptError;
  m_pErrorInfo->Errors.Add(pNewError);

  pNewError->SetID(Code);
  pNewError->SetErrorDef(pErrorDef);
  pNewError->SetToken(pToken);

  va_start(Args, pString);
  pNewError->FormatMessageV(pString, Args);
  va_end(Args);

  return (ReturnValue);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::AddError()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void ClearParseData (void);
 *
 *=========================================================================*/
void CObFixedParser::ClearParseData (void) {
  DestroyOutputData();

  m_OutputSizeStack.Destroy();
  m_OutputSizeStack2.Destroy();
  m_LocalVariables.Destroy();
  m_References.Destroy();
  m_ExpressionStack.Destroy();

  m_OpCount          = 0;
  m_CurrentToken     = 0;

  m_pCurrentFunction = NULL;
  m_CurrentFuncParam = 0;  
}
/*===========================================================================
 *		End of Class Method CObFixedParser::ClearParseData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void DestroyOutputData (void);
 *
 *=========================================================================*/
void CObFixedParser::DestroyOutputData (void) {

  if (m_pOutputData != NULL) {
    delete[] m_pOutputData;
    m_pOutputData = NULL;
  }

  m_OutputSize          = 0;
  m_AllocatedOutputSize = 0;
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DestroyOutputData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - word AddLocalReference (pLocalRef, LocalIndex);
 *
 *=========================================================================*/
word CObFixedParser::AddLocalReference (const char* pLocalRef, const int LocalIndex) {
  obparseref_t* pRef;

	/* Find an existing reference */
  pRef = FindLocalReference(pLocalRef);
  if (pRef != NULL) return (word) (pRef->RefIndex);

	/* Add a new reference */
  pRef = new obparseref_t;
  m_References.Add(pRef);

  pRef->FormID     = OB_FORMID_NULL;
  pRef->RefIndex   = m_pScript->GetNextLocalRefIndex();
  pRef->LocalRef   = pLocalRef;
  pRef->LocalIndex = LocalIndex;

  return (pRef->RefIndex);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::AddLocalReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - word AddReference (FormID);
 *
 *=========================================================================*/
word CObFixedParser::AddReference (const obformid_t FormID) {
  obparseref_t* pRef;

	/* Find an existing reference */
  pRef = FindReference(FormID);
  if (pRef != NULL) return (word) (pRef->RefIndex);

	/* Add a new reference */
  pRef = new obparseref_t;
  m_References.Add(pRef);

  pRef->FormID     = FormID;
  pRef->RefIndex   = m_pScript->GetNextLocalRefIndex();
  pRef->LocalIndex = 0;

  return (pRef->RefIndex);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::AddReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - obparseref_t* FindLocalReference (pLocalRef);
 *
 *=========================================================================*/
obparseref_t* CObFixedParser::FindLocalReference (const char* pLocalRef) {
  obparseref_t* pRef;
  dword         Index;

  for (Index = 0; Index < m_References.GetSize(); ++Index) {
    pRef = m_References.GetAt(Index);
    if (pRef->FormID != OB_FORMID_NULL) continue;
    if (pRef->LocalRef.CompareNoCase(pLocalRef) == 0) return (pRef);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindLocalReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - obparseref_t* FindReference (FormID);
 *
 *=========================================================================*/
obparseref_t* CObFixedParser::FindReference (const obformid_t FormID) {
  obparseref_t* pRef;
  dword         Index;

  for (Index = 0; Index < m_References.GetSize(); ++Index) {
    pRef = m_References.GetAt(Index);
    if (pRef->FormID == FormID) return (pRef);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoMainProgram (void);
 *
 *=========================================================================*/
int CObFixedParser::DoMainProgram (void) {
  tokeninstance_t* pToken;
  int              Result;

	/* Skip any leading lines */
  while (LookAhead(m_TokenEndLine)) {
    MatchToken(m_TokenEndLine);
  }

  Result = DoScriptName();
  if (Result < 0) return (Result);

  while (LookAhead(m_TokenEndofProgram) == NULL) {

    if (LookAhead(m_TokenVarShort)) {
      Result = DoAddLocal(m_TokenVarShort);
    }
    else if (LookAhead(m_TokenVarLong)) {
      Result = DoAddLocal(m_TokenVarLong);
    }
    else if (LookAhead(m_TokenVarFloat)) {
      Result = DoAddLocal(m_TokenVarFloat);
    }
    else if (LookAhead(m_TokenVarRef)) {
      Result = DoAddLocal(m_TokenVarRef);
    }
    else if (LookAhead(m_TokenBegin)) {
      Result = DoBegin();
    }
    else if (LookAhead(m_TokenEndLine)) {
      MatchToken(m_TokenEndLine);
      Result = 0;
    }
    else {
      pToken = GetCurrentToken();
      Result = AddError(OB_SCRIPT_ERROR_BADTOKEN, pToken, "Unknown script input '%s' (%s) found!", pToken->Value, pToken->pToken->GetName());
      return (Result);
    }

    if (Result < 0) return (Result);
  }

  pToken = MatchToken(m_TokenEndofProgram, "Unexpected end of script found!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Check output size */
  if (m_OutputSize > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_BADSCRIPTSIZE, NULL, "Exceeded maximum compiler script size of 65535 bytes!");
    return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoMainProgram()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoScriptName (void);
 *
 *=========================================================================*/
int CObFixedParser::DoScriptName (void) {
  tokeninstance_t* pToken;

  pToken = MatchToken(m_TokenScriptname, "Scripts must begin with a 'scriptname' declaration!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  pToken = MatchToken(m_TokenIdentifier, "Missing or invalid scriptname editorid!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  m_Scriptname = pToken->Value;

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after scriptname declaration!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);
  
  OutputData((dword) 0x0000001D);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoScriptName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObFixedParser Method - const GetTokenString (TokenID);
 *
 *=========================================================================*/
const char* CObFixedParser::GetTokenString (const int TokenID) {
  static CSString s_Buffer;
  CTokenType*     pTokenType;

  pTokenType = m_pTokenTypes->GetTokenType(TokenID);
  if (pTokenType != NULL) return pTokenType->GetName();

  s_Buffer.Format("Unknown token %d", TokenID);
  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObFixedParser::GetTokenString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoAddLocal (ocalType);
 *
 *=========================================================================*/
int CObFixedParser::DoAddLocal (const int LocalType) {
  tokeninstance_t* pToken;
  obparselocal_t*  pNewLocal;
  obparselocal_t*  pLocal;
  int              LocalIndex;
  int              Result;

  pToken = MatchToken(LocalType);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Ignore if already defined */
  pLocal = FindLocalVariable(pToken->Value);

  if (pLocal != NULL) {
    if (pLocal->TokenID == LocalType) {
      Result = AddError(OB_SCRIPT_ERROR_LOCALREDEFSAME, pToken, "Redefinition of local variable '%s' as a %s!", pToken->Value.c_str(), GetTokenString(LocalType));
      if (Result < 0) return (OB_PARSE_RESULT_ERROR);
      return (OB_PARSE_RESULT_OK);
    }
    else {
      Result = AddError(OB_SCRIPT_ERROR_LOCALREDEFDIFF, pToken, "Cannot define local variable '%s' as a %s as it has already been defined as a %s!", pToken->Value.c_str(), GetTokenString(LocalType), GetTokenString(pLocal->TokenID));
      if (Result < 0) return (OB_PARSE_RESULT_ERROR);
    }
  }

	/* Reuse an existing local or create a new one */
  LocalIndex = m_pScript->FindVariableIndex(pToken->Value);
  if (LocalIndex <= 0)  LocalIndex = m_pScript->GetNextLocalVarIndex();

	/* Add the local definition */
  pNewLocal = new obparselocal_t;
  m_LocalVariables.Add(pNewLocal);
  pNewLocal->Index   = LocalIndex;
  pNewLocal->Name    = pToken->Value;
  pNewLocal->TokenID = LocalType;
  pNewLocal->Flags   = (LocalType == m_TokenVarShort || LocalType == m_TokenVarLong) ? OBSLSD_FLAG_SHORTLONG : 0;

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after local variable definition!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoAddLocal()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoBegin (void);
 *
 *=========================================================================*/
int CObFixedParser::DoBegin (void) {
  tokeninstance_t* pToken;
  int              Result;

  pToken = MatchToken(m_TokenBegin);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((word) 0x0010);
  
  Result = DoBeginMode();
  if (Result < 0) return (Result);

  Result = DoStatements();
  if (Result < 0) return (Result);
	
  pToken = MatchToken(m_TokenEnd, "Missing 'end' for previous begin block!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((dword) 0x00000011);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after End!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);
  
  Result = PopOutputSizeDWord(m_OutputSize, true);
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoBegin()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoBegin (void);
 *
 *=========================================================================*/
int CObFixedParser::DoBeginMode (void) {
  tokeninstance_t*   pToken;
  CObScriptFunction* pFunction;
  obparselength_t*   pBlockLength;
  int                Result;

  pToken = MatchToken(m_TokenIdentifier, "Missing begin block type!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  pFunction = ObGetScriptConsoleFunction(pToken->Value);

  if (pFunction == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADBLOCKFUNCTION, pToken, "Unknown begin block type '%s'!", pToken->Value);
    return (Result);
  }

  if (!pFunction->IsBeginFunction()) {
    Result = AddError(OB_SCRIPT_ERROR_BADBLOCKFUNCTION, pToken, "The function '%s' is not a valid begin block type!", pToken->Value);
    if (Result < 0) return (Result);
  }

  m_pCurrentFunction = pFunction;
  m_CurrentFuncParam = 0;

  PushOutputSizeWord(m_OutputSize + 2);
  OutputData(pFunction->GetOpCode());
  pBlockLength = PushOutputSizeDWord(m_OutputSize + 4, true);

  Result = DoFunctionParams();

  m_pCurrentFunction = NULL;
  if (Result < 0) return (Result);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after begin block type!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);

	/* Adjust the block size */
  pBlockLength->OutputSize = m_OutputSize;
  
  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoBegin()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParams (void);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParams (void) {
  int  Result;

	/* Ignore if no function defined */
  if (m_pCurrentFunction == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Ignore if function has no parameters */
  if (m_pCurrentFunction->GetNumParameters() == 0) return (OB_PARSE_RESULT_OK);

  PushOutputSizeWord(m_CurrentFuncParam);

	/* Input all function parameters */
  while (m_CurrentFuncParam < (int) m_pCurrentFunction->GetNumParameters()) {
    Result = DoFunctionParam();
    if (Result < 0) return (Result);
    if (Result == OB_PARSE_RESULT_ENDFUNCTION) break;

    ++m_CurrentFuncParam;
  }

	/* Check for any missing parameters */
  Result = DoCheckFunctionEnd();
  if (Result < 0) return (Result);

  Result = PopOutputSizeWord(m_CurrentFuncParam);
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParams()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoCheckFunctionEnd (void);
 *
 *=========================================================================*/
int CObFixedParser::DoCheckFunctionEnd (void) {
  obscriptfuncparam_t* pParam;
  dword		       Index;
  int		       Result = OB_PARSE_RESULT_OK;

  for (Index = m_CurrentFuncParam; Index < m_pCurrentFunction->GetNumParameters(); ++Index) {
    pParam = m_pCurrentFunction->GetParameter(m_CurrentFuncParam);
    if (pParam == NULL) continue;

    if (!pParam->IsOptional()) {
      Result = AddError(OB_SCRIPT_ERROR_MISSINGPARAMETER, GetCurrentToken(), "Missing required function parameter #%d", Index + 1);
      if (Result < 0) return (Result);
    }
  }

  m_FunctionParams.Empty();
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoCheckFunctionEnd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParam (void);
 * 
 *=========================================================================*/
int CObFixedParser::DoFunctionParam (void) {
  tokeninstance_t*     pToken;
  obscriptfuncparam_t* pParam;
  int                  Result;

	/* Ensure a valid parameter */
  pParam = m_pCurrentFunction->GetParameter(m_CurrentFuncParam);

  if (pParam == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_EXTRAPARAMETER, GetCurrentToken(), "Function '%s' does not accept parameter #%d!", m_pCurrentFunction->GetName(), m_CurrentFuncParam + 1);
    return (Result);
  }

	/* Match optional comma */
  if (LookAhead(m_TokenComma)) MatchToken(m_TokenComma);
  pToken = GetCurrentToken();

	/* Check for a possible end of function call */
  if (pParam->IsOptional()) {
    if (LookAhead(m_TokenEndLine)) return (OB_PARSE_RESULT_ENDFUNCTION);
  }

  m_FunctionParams.Add(pToken);

  switch (pParam->Type) {
     case OB_FUNCPARAM_STRING:
	return DoFunctionParamString(pParam);
     case OB_FUNCPARAM_INTEGER:
	return DoFunctionParamInt(pParam);
     case OB_FUNCPARAM_FLOAT:	
	return DoFunctionParamFloat(pParam);
     case OB_FUNCPARAM_ACTORVALUE:
	return DoFunctionParamActorValue(pParam);
     case OB_FUNCPARAM_AXIS:
        return DoFunctionParamAxis(pParam);
     case OB_FUNCPARAM_CRIMETYPE:
	return DoFunctionParamCrime(pParam);
     case OB_FUNCPARAM_ANIMATIONGROUP:
        return DoFunctionParamAnimGroup(pParam);
     case OB_FUNCPARAM_QUESTSTAGE:
        return DoFunctionParamQuestStage(pParam);
     case OB_FUNCPARAM_VARIABLENAME:
	return DoFunctionParamVarName(pParam);
     case OB_FUNCPARAM_SEX:
        return DoFunctionParamSex(pParam);
     case OB_FUNCPARAM_FORMTYPE:
	return DoFunctionParamFormType(pParam);
     case OB_FUNCPARAM_OBJECTREF:
     case OB_FUNCPARAM_ACTOR:
     case OB_FUNCPARAM_CONTAINER:
     case OB_FUNCPARAM_MAPMARKER:
	return DoFunctionParamRefRecord(pParam);
     default:	/* All other record types */
	return DoFunctionParamRecordID(pParam);
  }     
  
  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParam()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamCrime (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamCrime (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken = NULL;
  tokeninstance_t* pSignToken = NULL;
  dword            CrimeType;
  bool             Result;
  int              ErrResult;

  if (LookAhead(m_TokenAddOp)) pSignToken = MatchToken(m_TokenAddOp);

  if (LookAhead(m_TokenInteger)) {
    pToken = MatchToken(m_TokenInteger);
  }
  else {
    PushBackToken();
  }
  
  if (pToken == NULL) {
    if (pParam->IsOptional()) return (OB_PARSE_RESULT_ENDFUNCTION);
    pToken = GetCurrentToken();
    ErrResult = AddError(OB_SCRIPT_ERROR_BADCRIMETYPE, pToken, "Unknown crime type value '%s'!", pToken->Value.c_str());
    return (ErrResult);
  }

  Result = ObFieldConvertDword(pToken->Value, CrimeType);

  if (Result && CrimeType <= 4) {

    if (pSignToken != NULL && pSignToken->Value == "-") {
      ErrResult = AddError(OB_SCRIPT_ERROR_BADCRIMETYPE, pToken, "Invalid crime value '-%s' found!", pToken->Value.c_str());
      return (ErrResult);
    }

    OutputData((word) CrimeType);
  }
  else {
    ErrResult = AddError(OB_SCRIPT_ERROR_UNKNOWNCRIMETYPE, pToken, "Unknown crime value '%s' found!", pToken->Value.c_str());
    if (ErrResult < 0) return (ErrResult);
    OutputData((word) CrimeType);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamCrime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamVarName (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamVarName (obscriptfuncparam_t* pParam) {
  tokeninstance_t*   pToken;
  tokeninstance_t*   pRecordToken;
  CObIdRecord*       pRecord;
  CObRecord*         pBaseRefrRecord;
  CObIdRecord*       pScriptRecord;
  CObScptRecord*     pScript;
  CObSubrecord*      pSubrecord;
  CObSlsdSubrecord*  pLocalSubrecord;
  CObBaseRefrRecord* pReference;
  int                FormType;
  bool               Result;
  int                ErrResult;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = GetObFormTypeValue(FormType, pToken->Value);

  if (Result) {
    OutputData((word) FormType);
  }
  else {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADFORMTYPE, pToken, "Unknown form type '%s' found!", pToken->Value.c_str());
    return (ErrResult);
  }

  if (m_FunctionParams.GetSize() <= 1) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "No previous record to check variable name '%s'!", pToken->Value.c_str());
    return (ErrResult);
  }

	/* TODO: Move some of variable name getting to script or record handler */
  pRecordToken = m_FunctionParams.GetAt(m_FunctionParams.GetSize() - 1);
  pRecord      = m_pRecordHandler->FindEditorID(pRecordToken->Value);

  if (pRecord == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Cannot check variable name '%s' of unknown record '%s'!", pToken->Value.c_str(), pRecordToken->Value.c_str());
    return (ErrResult);
  }

  pReference = ObCastClass(CObBaseRefrRecord, pRecord);

	/* Special case for a reference */
  if (pReference != NULL) {
    pBaseRefrRecord = m_pRecordHandler->FindFormID(pReference->GetBaseFormID());

    if (pBaseRefrRecord == NULL) {
      ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid! The reference '%s' (unknown base record 0x%06X) does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str(), pReference->GetBaseFormID());
      return (ErrResult);
    }

    pSubrecord = pBaseRefrRecord->FindSubrecord(OB_NAME_SCRI);

    if (pSubrecord == NULL) {
      CSString Buffer;
      pBaseRefrRecord->GetField(Buffer, OB_FIELD_EDITORID);
      ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid! The reference '%s' (base record '%s') does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str(), Buffer.c_str());
      return (ErrResult);
    }
	
    if (!pReference->IsQuestItem()) {
      ErrResult = AddError(OB_SCRIPT_ERROR_NOTPERSISTENT, pToken, "The reference '%s' is not set as a persistent reference!", pRecordToken->Value.c_str());
      if (ErrResult < 0) return (ErrResult);
    }

  }
	/* Is a regular record */
  else {
    pSubrecord = pRecord->FindSubrecord(OB_NAME_SCRI);

    if (pSubrecord == NULL) {
      ErrResult = AddError(0, pToken, "Variable name '%s' is not valid! The record '%s' does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str());
      return (ErrResult);
    }
  }

  pScriptRecord = m_pRecordHandler->FindEditorID((char *)pSubrecord->GetData());

  if (pScriptRecord == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid as script '%s' was not found!", pToken->Value.c_str(), (char *)pSubrecord->GetData());
    return (ErrResult);
  }

  pScript = ObCastClass(CObScptRecord, pScriptRecord);

  if (pScript == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid as record '%s' is not a script!", pToken->Value.c_str(), pScriptRecord->GetEditorID());
    return (ErrResult);
  }

  pLocalSubrecord = pScript->FindVariable(pToken->Value);

  if (pLocalSubrecord == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Script '%s' does not have a local variable named '%s'!", pScriptRecord->GetEditorID(), pToken->Value.c_str());
    return (ErrResult);
  }

	/* Output the local variable data */
  OutputData((byte) pLocalSubrecord->IsShortLong() ? 0x73 : 0x66);
  OutputData((word) (word) pLocalSubrecord->GetSlsdData().Index);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamVarName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamQuestStage (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamQuestStage (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken = NULL;
  tokeninstance_t* pSignToken = NULL;
  tokeninstance_t* pQuestToken;
  CObIdRecord*     pRecord;
  CObSubrecord*    pSubrecord;
  int              QuestStage;
  int		   Position;
  bool             Result;
  int              ErrResult;

  if (LookAhead(m_TokenAddOp)) {
    pSignToken = MatchToken(m_TokenAddOp);

    pToken = MatchToken(m_TokenInteger);
    if (pToken == NULL && pSignToken) PushBackToken();
  }
  else if (LookAhead(m_TokenInteger)) {
    pToken = MatchToken(m_TokenInteger);
  }
  else if (LookAhead(m_TokenFloat)) {
    pToken = MatchToken(m_TokenFloat);
    ErrResult = AddError(OB_SCRIPT_ERROR_FLOATTOINTEGER, pToken, "Float value for quest stage found!");
    if (ErrResult < 0) return (ErrResult);
  }
  else if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);
    return DoLocalGlobalOutput(pToken);
  }
  
  if (pToken == NULL) {
    if (pParam->IsOptional()) return (OB_PARSE_RESULT_ENDFUNCTION);
    pToken = GetCurrentToken();
    ErrResult = AddError(OB_SCRIPT_ERROR_BADQUESTSTAGE, pToken, "Unknown quest stage value '%s'!", pToken->Value.c_str());
    return (ErrResult);
  }

  Result = ObFieldConvertInt(pToken->Value, QuestStage);

  if (!Result) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADQUESTSTAGE, pToken, "Invalid quest stage value '%s'!", pToken->Value.c_str());
    return (ErrResult);
  }

  if (pSignToken != NULL && pSignToken->Value == "-") QuestStage = -QuestStage;

  if (m_FunctionParams.GetSize() <= 1) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADQUESTSTAGE, pToken, "No previous quest to check function parameter quest stage value '%s'!", pToken->Value.c_str());
    return (ErrResult);
  }

  pQuestToken = m_FunctionParams.GetAt(m_FunctionParams.GetSize() - 2);
  pRecord     = m_pRecordHandler->FindEditorID(pQuestToken->Value);

  if (pRecord == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADQUESTSTAGE, pToken, "Cannot check stage value '%s' of unknown quest '%s'!", pToken->Value.c_str(), pQuestToken->Value.c_str());
    return (ErrResult);
  }

  if (pRecord->GetRecordType() != OB_NAME_QUST) {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADQUESTSTAGE, pToken, "Cannot check stage value '%s' of non-quest record '%s'!", pToken->Value.c_str(), pQuestToken->Value.c_str());
    return (ErrResult);
  }

	/* TODO: Move to quest record eventually */
  pSubrecord = pRecord->FindFirstSubrecord(OB_NAME_INDX, Position);

  while (pSubrecord != NULL) {
    if (*(word*)pSubrecord->GetData() == QuestStage) break;
    pSubrecord = pRecord->FindNextSubrecord(OB_NAME_INDX, Position);
  }

	/* Not found */
  if (pSubrecord == NULL) {
    ErrResult = AddError(OB_SCRIPT_ERROR_UNKNOWNQUESTSTAGE, pToken, "The value '%s' is not a valid stage of quest '%s'!", pToken->Value.c_str(), pQuestToken->Value.c_str());
    if (ErrResult < 0) return (ErrResult);
  }

  OutputData((byte) 0x6E);
  OutputData((dword) QuestStage);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamQuestStage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamFormType (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamFormType (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  int              FormType;
  bool             Result;
  int              ErrResult;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = GetObFormTypeValue(FormType, pToken->Value);

  if (Result) {
    OutputData((word) FormType);
  }
  else {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADFORMTYPE, pToken, "Unknown form type '%s' found!", pToken->Value.c_str());
    return (ErrResult);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamFormType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamAnimGroup (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamAnimGroup (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  int              AnimGroup;
  bool             Result;
  int              ErrResult;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = GetObAnimationGroupValue(AnimGroup, pToken->Value);

  if (Result) {
    OutputData((word) AnimGroup);
  }
  else {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADANIMATIONGROUP, pToken, "Unknown animation group '%s' found!", pToken->Value.c_str());
    return (ErrResult);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamAnimGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamActorValue (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamActorValue (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken = NULL;
  int              ActorValue;
  bool             Result;
  int              ErrResult;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL && LookAhead(m_TokenString) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  if (LookAhead(m_TokenString)) {
    pToken = MatchToken(m_TokenString);
  }
  else if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);
  }

  if (pToken == NULL) {
    pToken = GetCurrentToken();
    ErrResult = AddError(OB_SCRIPT_ERROR_BADACTORVALUE, pToken, "Unknown actor value '%s' found!", pToken->Value.c_str());
    return (ErrResult);
  } 

  Result = GetObScriptActorValueValue(ActorValue, pToken->Value);

  if (Result) {
    OutputData((word) ActorValue);
  }
  else {
    ErrResult = AddError(OB_SCRIPT_ERROR_BADACTORVALUE, pToken, "Invalid actor value '%s' found!", pToken->Value.c_str());
    return (ErrResult);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamActorValue()
 *=========================================================================*/
 	

/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamSex (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamSex (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  int              Result;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (pToken->Value.CompareNoCase("male") == 0) {
    OutputData((word) 0);
  }
  else if (pToken->Value.CompareNoCase("female") == 0) {
    OutputData((word) 1);
  }
  else {
    Result = AddError(OB_SCRIPT_ERROR_BADGENDER, pToken, "Unknown gender value '%s' found! Expecting male or female.", pToken->Value.c_str());
    return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamSex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamAxis (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamAxis (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  int              Result;

  if (pParam->IsOptional() && LookAhead(m_TokenIdentifier) == NULL) return (OB_PARSE_RESULT_ENDFUNCTION);

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (pToken->Value.CompareNoCase("x") == 0) {
    OutputData('X');
  }
  else if (pToken->Value.CompareNoCase("y") == 0) {
    OutputData('Y');
  }
  else if (pToken->Value.CompareNoCase("z") == 0) {
    OutputData('Z');
  }
  else {
    Result = AddError(OB_SCRIPT_ERROR_BADAXIS, pToken, "Unknown axis value '%s' found! Expecting one of X, Y, or Z.", pToken->Value.c_str());
    return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamAxis()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamInt (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamInt (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  tokeninstance_t* pSignToken = NULL;
  int              Value;
  int              Result;

  if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);

    if (LookAhead(m_TokenRef)) return DoFunctionParamExtVar(pParam, pToken);
    return DoLocalGlobalOutput(pToken);
  }

  if (LookAhead(m_TokenAddOp)) pSignToken = MatchToken(m_TokenAddOp);

  if (LookAhead(m_TokenInteger)) {
    pToken = MatchToken(m_TokenInteger);
    Value  = atoi(pToken->Value);
  }
  else if (LookAhead(m_TokenFloat)) {
    pToken = MatchToken(m_TokenFloat);
    Value  = (int)atof(pToken->Value);
    Result = AddError(OB_SCRIPT_ERROR_FLOATTOINTEGER, pToken, "Converting float parameter #%d '%s' to integer!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    if (Result < 0) return (Result);
  }
  else if (pParam->IsOptional()) {
    return (OB_PARSE_RESULT_ENDFUNCTION);
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADINTEGER, pToken, "Function parameter #%d '%s' is not an integer!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    return (Result);
  }

  if (pSignToken != NULL && pSignToken->Value == "-") Value = -Value;

  OutputData((byte)0x6e);
  OutputData(Value);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamInt()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamFloat (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamFloat (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  tokeninstance_t* pSignToken = NULL;
  double           Value;
  int              Result;

  if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);

    if (LookAhead(m_TokenRef)) return DoFunctionParamExtVar(pParam, pToken);
    return DoLocalGlobalOutput(pToken);
  }

  if (LookAhead(m_TokenAddOp)) pSignToken = MatchToken(m_TokenAddOp);

  if (LookAhead(m_TokenInteger)) {
    pToken = MatchToken(m_TokenInteger);
    Value  = (double) atoi(pToken->Value);
  }
  else if (LookAhead(m_TokenFloat)) {
    pToken = MatchToken(m_TokenFloat);
    Value  = atof(pToken->Value);
  }
  else if (pParam->IsOptional()) {
    return (OB_PARSE_RESULT_ENDFUNCTION);
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADFLOAT, pToken, "Function parameter #%d '%s' is not a float!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    return (Result);
  }

  if (pSignToken != NULL && pSignToken->Value == "-") Value = -Value;
  OutputData((byte)0x6e);
  OutputData(Value);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamFloat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamString (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamString (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken = NULL;
  int              Result;

  if (LookAhead(m_TokenString)) {
    pToken = MatchToken(m_TokenString);
  }
  else if (pParam->IsOptional()) {
    return (OB_PARSE_RESULT_ENDFUNCTION);
  }

  if (pToken == NULL) {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADSTRING, pToken, "Function parameter #%d '%s' is not a string!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    return (Result);
  }

  if (pToken->Value.GetLength() > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_BADSTRING, pToken, "Function parameter #%d string exceeds the maximum length of 65535 bytes!", m_CurrentFuncParam + 1);
    return (Result);
  }

  OutputData((word)pToken->Value.GetLength());
  OutputData(pToken->Value.c_str(), pToken->Value.GetLength());

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamRecordID (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamRecordID (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  CObRecord*       pRecord;
  word		   RefIndex;
  int              Result;

  if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);
  }
  else if (LookAhead(m_TokenString)) {
    pToken = MatchToken(m_TokenString);
  }
  else if (pParam->IsOptional()) {
    return (OB_PARSE_RESULT_ENDFUNCTION);
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADIDENTIFIER, pToken, "Function parameter #%d '%s' is not an identifier!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    return (Result);
  }

  if (LookAhead(m_TokenRef)) return DoFunctionParamExtVar(pParam, pToken);

	/* Find the record */
  pRecord = m_pRecordHandler->FindEditorID(pToken->Value);

  if (pRecord == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pToken, "Unknown record '%s'!", pToken->Value.c_str());
    return (Result);
  }

	/* Check the record type */
  if (!pRecord->IsFormType(pParam->Type)) {
    Result = AddError(OB_SCRIPT_ERROR_BADPARAMETER, pToken, "Function parameter '%s' is not a valid %s type!", pToken->Value.c_str(), ObGetScriptFuncParamString(pParam->Type));
    return (Result);
  }

  	/* Add the reference */
  RefIndex = AddReference(pRecord->GetFormID());

	/* Output the reference data */
  OutputData((byte) 0x72);
  OutputData((word) RefIndex);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamRecordID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamRefRecord (pParam);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamRefRecord (obscriptfuncparam_t* pParam) {
  tokeninstance_t* pToken;
  word		   RefIndex;
  int              Result;

  if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);
  }
  else if (LookAhead(m_TokenString)) {
    pToken = MatchToken(m_TokenString);
  }
  else if (pParam->IsOptional()) {
    return (OB_PARSE_RESULT_ENDFUNCTION);
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADIDENTIFIER, pToken, "Function parameter #%d '%s' is not an identifier!", m_CurrentFuncParam + 1, pToken->Value.c_str());
    return (Result);
  }

  if (LookAhead(m_TokenRef)) return DoFunctionParamExtVar(pParam, pToken);

	/* Ensure a valid reference */
  Result = FindReferenceIndex(RefIndex, pToken, pParam);

  if (Result < 0) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pToken, "Unknown reference '%s'!", pToken->Value.c_str());
    return (Result);
  }
  	
	/* Output the reference data */
  OutputData((byte) 0x72);
  OutputData((word) RefIndex);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamRefRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoStatements (void);
 *
 *=========================================================================*/
int CObFixedParser::DoStatements (void) {
  int Result;

  do {
    Result = DoStatement();
    if (Result < 0) return (Result);
  } while (Result != OB_PARSE_RESULT_ENDBLOCK); 

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoStatements()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoStatement (void);
 *
 *=========================================================================*/
int CObFixedParser::DoStatement (void) {

  if (LookAhead(m_TokenVarShort)) {
    return DoAddLocal(m_TokenVarShort);
  }
  else if (LookAhead(m_TokenVarLong)) {
    return DoAddLocal(m_TokenVarLong);
  }
  else if (LookAhead(m_TokenVarFloat)) {
    return DoAddLocal(m_TokenVarFloat);
  }
  else if (LookAhead(m_TokenVarRef)) {
    return DoAddLocal(m_TokenVarRef);
  }
  else if (LookAhead(m_TokenEndLine)) {
    MatchToken(m_TokenEndLine);
    return (OB_PARSE_RESULT_OK);
  }
  else if (LookAhead(m_TokenIdentifier)) {
    return DoFunction();
  }
  else if (LookAhead(m_TokenReturn)) {
    return DoReturn();
  }
  else if (LookAhead(m_TokenSet)) {
    return DoSet();
  }
  else if (LookAhead(m_TokenIf)) {
    return DoIf();
  }

  return (OB_PARSE_RESULT_ENDBLOCK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoStatement()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSet (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSet (void) {
  tokeninstance_t* pToken;
  int              Result;

  MatchToken(m_TokenSet);

  OutputData((word) 0x0015);
  PushOutputSizeWord(m_OutputSize + 2);

  pToken = MatchToken(m_TokenIdentifier, "Missing destination variable for set statement!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (LookAhead(m_TokenRef)) {
    Result = DoSetRef(pToken);
    if (Result < 0) return (Result);
  }
  else {
    Result = DoSetCall(pToken);
    if (Result < 0) return (Result);
  }

  PopOutputSizeWord(m_OutputSize);
  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSet()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoVariableRef (pRefToken);
 *
 *=========================================================================*/
int CObFixedParser::DoVariableRef (tokeninstance_t* pRefToken) {
  obextvarinfo_t  ExtVarInfo;
  int             Result;
  word            RefIndex;

	/* Parse the external variable definition and ensure it is valid */
  Result = ParseExternalVariable (ExtVarInfo, pRefToken);
  if (Result < 0) return (Result);

 	/* Add the reference */
  RefIndex = AddReference(ExtVarInfo.pRecord->GetFormID());

	/* Output the reference data */
  OutputData((byte) 0x72);
  OutputData((word) RefIndex);

  	/* Output the local variable data */
  OutputData((byte) ExtVarInfo.pLocalData->IsShortLong() ? 0x73 : 0x66);
  OutputData((word) (word) ExtVarInfo.pLocalData->GetSlsdData().Index);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoVariableRef()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSetRef (pRefToken);
 *
 *=========================================================================*/
int CObFixedParser::DoSetRef (tokeninstance_t* pRefToken) {
  int Result;

  Result = DoVariableRef(pRefToken);
  if (Result < 0) return (Result);

  return DoSetTo();
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSetRef()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoLocalGlobalOutput (pVarToken);
 *
 *=========================================================================*/
int CObFixedParser::DoLocalGlobalOutput (tokeninstance_t* pVarToken) {
  CObRecord*      pRecord;
  obparselocal_t* pLocal;
  word		  GlobalIndex;
  int             Result;

	/* Check for a local first */
  pLocal = FindLocalVariable(pVarToken->Value);

  if (pLocal != NULL) {
    
    if (pLocal->TokenID == m_TokenVarShort || pLocal->TokenID == m_TokenVarLong) {
      OutputData((byte)0x73);
    }
    else if (pLocal->TokenID == m_TokenVarFloat || pLocal->TokenID == m_TokenVarRef) {
      OutputData((byte)0x66);
    }
    else {
      Result = AddError(OB_SCRIPT_ERROR_BADLOCAL, pVarToken, "Unknown local variable type %d!", pLocal->TokenID);
      return (Result);
    }

    OutputData((word) pLocal->Index);
    return (OB_PARSE_RESULT_OK);
  }

	/* Check for a global variable */  
  pRecord = m_pRecordHandler->FindEditorID(pVarToken->Value);

  if (pRecord == NULL || pRecord->GetRecordType() != OB_NAME_GLOB) {
    Result = AddError(OB_SCRIPT_ERROR_UNDEFINEDVARIABLE, pVarToken, "Undefined local or global variable '%s'!", pVarToken->Value);
    return (Result);
  }

  GlobalIndex = AddReference(pRecord->GetFormID());
  OutputData((byte)0x47);
  OutputData((word)GlobalIndex);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoLocalGlobalOutput()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSetCall (pVarToken);
 *
 *=========================================================================*/
int CObFixedParser::DoSetCall (tokeninstance_t* pVarToken) {
  int Result;

  Result = DoLocalGlobalOutput(pVarToken);
  if (Result < 0) return (Result);

  return DoSetTo();
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSetCall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSetTo (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSetTo (void) {
  tokeninstance_t* pToken;
  int              Result;

  pToken = MatchToken(m_TokenTo, "Missing 'to' after variable in set statement!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  PushOutputSizeWord(m_OutputSize + 2);

  Result = DoSimpleExpression();
  if (Result < 0) return (Result);

  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after set expression!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSetTo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoIf (void);
 *
 *=========================================================================*/
int CObFixedParser::DoIf (void) {
  tokeninstance_t* pToken;
  int              Result;

  pToken = MatchToken(m_TokenIf);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((word) 0x0016);
  PushOutputSizeWord(m_OutputSize + 2);
  PushOutputSizeWord(m_OpCount, true);
  PushOutputSizeWord(m_OutputSize + 2);

  Result = DoSimpleExpression();
  if (Result < 0) return (Result);

  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);
  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after if expression!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);
  
  Result = DoStatements();
  if (Result < 0) return (Result);

  while (LookAhead(m_TokenElseif)) {
    Result = DoElseIf();
    if (Result < 0) return (Result);
  }

  if (LookAhead(m_TokenElse)) {
    Result = DoElse();
    if (Result < 0) return (Result);
  }

  pToken = MatchToken(m_TokenEndif, "Missing 'endif'!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((dword) 0x00000019);
  PopOutputSizeWord(m_OpCount, true);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after endif!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoIf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoElseIf (void);
 *
 *=========================================================================*/
int CObFixedParser::DoElseIf (void) {
  tokeninstance_t* pToken;
  int              Result;

  PopOutputSizeWord(m_OpCount, true);

  pToken = MatchToken(m_TokenElseif);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((word) 0x0018);
  PushOutputSizeWord(m_OutputSize + 2);
  PushOutputSizeWord(m_OpCount, true);
  PushOutputSizeWord(m_OutputSize + 2);
  
  Result = DoSimpleExpression();
  if (Result < 0) return (Result);

  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);
  Result = PopOutputSizeWord(m_OutputSize);
  if (Result < 0) return (Result);
  
  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after elseif expression!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = DoStatements();
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoElseIf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoElse (void);
 *
 *=========================================================================*/
int CObFixedParser::DoElse (void) {
  tokeninstance_t* pToken;
  int              Result;

  PopOutputSizeWord(m_OpCount, true);

  pToken = MatchToken(m_TokenElse);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  OutputData((word) 0x0017);
  OutputData((word) 0x0002);
  PushOutputSizeWord(m_OpCount, true);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after else statement!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  Result = DoStatements();
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoElse()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSimpleExpression (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSimpleExpression (void) {
  tokeninstance_t* pToken;
  int              Result;

  Result = DoFirstSimpleTerm();
  if (Result < 0) return (Result);

  while (LookAhead(m_TokenAddOp) != NULL) {
    pToken = MatchToken(m_TokenAddOp);

    PopExpressions(m_TokenAddOp);
    PushExpression(pToken);

    Result = DoSimpleTerm();
    if (Result < 0) return (Result);
  }

  if (LookAhead(m_TokenRelOp)) {
    pToken = MatchToken(m_TokenRelOp);

    PopExpressions(m_TokenRelOp);
    PushExpression(pToken);

    Result = DoSimpleExpression();
    if (Result < 0) return (Result);
  }
  else if (LookAhead(m_TokenBoolOp)) {
    pToken = MatchToken(m_TokenBoolOp);

    PopExpressions(m_TokenBoolOp);
    PushExpression(pToken);

    Result = DoSimpleExpression();
    if (Result < 0) return (Result);
  }

  PopExpressionsTo(0);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSimpleExpression()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFirstSimpleTerm (void);
 *
 *=========================================================================*/
int CObFixedParser::DoFirstSimpleTerm (void) {
  tokeninstance_t* pToken;
  int              Result;

  Result = DoFirstSimpleFactor();
  if (Result < 0) return (Result);

  while (LookAhead(m_TokenMultOp) != NULL) {
    pToken = MatchToken(m_TokenMultOp);

    PopExpressions(m_TokenMultOp);
    PushExpression(pToken);
	 
    Result = DoFirstSimpleFactor();
    if (Result < 0) return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFirstSimpleTerm()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSimpleTerm (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSimpleTerm (void) {
  tokeninstance_t* pToken;
  int              Result;

  Result = DoSimpleFactor();
  if (Result < 0) return (Result);

  while (LookAhead(m_TokenMultOp) != NULL) {
    pToken = MatchToken(m_TokenMultOp);

    PopExpressions(m_TokenMultOp);
    PushExpression(pToken);

    Result = DoFirstSimpleFactor();
    if (Result < 0) return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSimpleTerm()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFirstSimpleFactor (void);
 *
 *=========================================================================*/
int CObFixedParser::DoFirstSimpleFactor (void) {
  tokeninstance_t* pToken = NULL;
  int              Result;

  if (LookAhead(m_TokenAddOp) != NULL) {
    pToken = MatchToken(m_TokenAddOp);
    if (pToken->Value == "-") pToken->Value = "~";
    PushExpression(pToken);
  }

  Result = DoSimpleFactor();
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFirstSimpleFactor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSimpleFactor (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSimpleFactor (void) {
  tokeninstance_t* pToken;
  int              Result;

  if (LookAhead(m_TokenLBracket) != NULL) {
    pToken = MatchToken(m_TokenLBracket);
    PushExpression(pToken);
		
    Result = DoSimpleExpression();
    if (Result < 0) return (Result);

    pToken = MatchToken(m_TokenRBracket, "Missing a matching ')'!");
    if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

    PopExpressionsTo(m_TokenLBracket);
  }
  else if (LookAhead(m_TokenInteger) != NULL) {
    Result = DoExprInteger();
    if (Result < 0) return (Result);
  }
  else if (LookAhead(m_TokenFloat) != NULL) {
    Result = DoExprFloat();
    if (Result < 0) return (Result);
  }
  else if (LookAhead(m_TokenIdentifier) != NULL) {
    Result = DoSimpleFactorID();
    if (Result < 0) return (Result);
  }
  else if (LookAhead(m_TokenEndLine) != NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADEXPRESSION, GetCurrentToken(), "Missing expression token before end-of-line!");
    return (Result);
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADEXPRESSION, pToken, "Missing expression token before '%s'!", pToken->Value);
    return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSimpleFactor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoExprInteger (void);
 *
 *=========================================================================*/
int CObFixedParser::DoExprInteger (void) {
  tokeninstance_t* pToken;

  pToken = MatchToken(m_TokenInteger);

  OutputData((byte) ' ');

	/* TODO */
  //if (m_LastSetNegative) OutputData((byte) '-');
                 
  OutputData(pToken->Value, pToken->Value.GetLength());

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoExprInteger()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoExprFloat (void);
 *
 *=========================================================================*/
int CObFixedParser::DoExprFloat (void) {
  tokeninstance_t* pToken;

  pToken = MatchToken(m_TokenFloat);
  
  OutputData((byte) ' ');

	/* TODO */
  //if (m_LastSetNegative) OutputData((byte) '-');
                 
  OutputData(pToken->Value, pToken->Value.GetLength());

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoExprFloat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoExprFunction (pFuncToken);
 *
 *=========================================================================*/
int CObFixedParser::DoExprFunction (tokeninstance_t* pFuncToken) {
  CObScriptFunction* pFunction;
  int                Result;

  pFunction = ObGetScriptFunction(pFuncToken->Value);

  if (pFunction == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADFUNCTION, pFuncToken, "Unknown function '%s'!", pFuncToken->Value);
    return (Result);
  }

	/* Output function data */
  OutputData((byte) ' ');
  OutputData((byte) 0x58);
  OutputData((word) pFunction->GetOpCode());
  PushOutputSizeWord(m_OutputSize + 2);
 
  return DoFunctionHelper(pFunction, pFuncToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoExprFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoExprRef (pRefToken);
 *
 *=========================================================================*/
int CObFixedParser::DoExprRef (tokeninstance_t* pRefToken) {
  tokeninstance_t*   pToken;
  CObScriptFunction* pFunction;
  word		     RefIndex;
  int                Result;

  pToken = m_pTokens->GetAt(m_CurrentToken + 1);

  if (pToken == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADREFERENCE, GetCurrentToken(), "Missing variable/function identifier after '.' in reference call!");
    return (Result);
  }

	/* Is this a function? */
  pFunction = ObGetScriptFunction(pToken->Value);
  if (pFunction == NULL) return DoVariableRef(pRefToken);

	/* Ensure a valid reference */
  Result = FindReferenceIndex(RefIndex, pRefToken, NULL);

  if (Result < 0) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pRefToken, "Unknown reference '%s'!", pRefToken->Value.c_str());
    return (Result);
  }

	/* Output the reference data */
  OutputData((byte) ' ');
  OutputData((byte) 0x72);
  OutputData((word) RefIndex);

	/* Continue with the function call */
  pToken = MatchToken(m_TokenRef);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  pToken = MatchToken(m_TokenIdentifier, "Missing reference function call or parameter after '.'!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return DoFunctionCall(pToken, true);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoExprRef()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoSimpleFactorID (void);
 *
 *=========================================================================*/
int CObFixedParser::DoSimpleFactorID (void) {
  tokeninstance_t*   pToken;
  obparselocal_t*    pLocal;
  CObScriptFunction* pFunction;
  CObRecord*         pRecord;
  CObIdRecord*       pRefRecord;
  word               RefIndex;
  int                Result;

  pToken = MatchToken(m_TokenIdentifier);
  if (LookAhead(m_TokenRef)) return DoExprRef(pToken);

  	/* Check for a local first */
  pLocal = FindLocalVariable(pToken->Value);

  if (pLocal != NULL) {
    OutputData((byte) ' ');
    return DoLocalGlobalOutput(pToken);
  }
   
	/* Check for a global variable */  
  pRecord = m_pRecordHandler->FindEditorID(pToken->Value);

  if (pRecord != NULL && pRecord->GetRecordType() == OB_NAME_GLOB) {
    OutputData((byte) ' ');
    return DoLocalGlobalOutput(pToken);
  }

  	/* Check for a function call */
  pFunction = ObGetScriptFunction(pToken->Value);
  if (pFunction != NULL) return DoExprFunction(pToken);

	/* Check for a plain reference */
  pRefRecord = FindRefRecord(pToken->Value);

  if (pRefRecord != NULL) {

    if (!pRefRecord->IsQuestItem()) {
      Result = AddError(OB_SCRIPT_ERROR_NOTPERSISTENT, pToken, "The reference '%s' is not set as a persistent reference!", pToken->Value.c_str());
      if (Result < 0) return (Result);
    }

    RefIndex = AddReference(pRefRecord->GetFormID());

    OutputData((byte) ' ');
    OutputData((byte) 'Z');
    OutputData((word) RefIndex);

    return (OB_PARSE_RESULT_OK);
  }
  
	/* Unknown identifier found */
  Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pToken, "Unknown identifier '%s'!", pToken->Value);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoSimpleFactorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoReturn (void);
 *
 *=========================================================================*/
int CObFixedParser::DoReturn (void) {
  tokeninstance_t* pToken;

  MatchToken(m_TokenReturn);

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after return!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  ++m_OpCount;
  OutputData((dword) 0x0000001E);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoReturn()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunction (void);
 *
 *=========================================================================*/
int CObFixedParser::DoFunction (void) {
  tokeninstance_t* pToken;
  int              Result;

  pToken = MatchToken(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (LookAhead(m_TokenRef)) {
    Result = DoFunctionRef(pToken);
    if (Result < 0) return (Result);
  }
  else {
    Result = DoFunctionCall(pToken);
    if (Result < 0) return (Result);
  }

  pToken = MatchToken(m_TokenEndLine, "Missing end-of-line after function!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int FindReferenceIndex (RefIndex, pRefToken, pFuncParam);
 *
 *=========================================================================*/
int CObFixedParser::FindReferenceIndex (word& RefIndex, tokeninstance_t* pRefToken, obscriptfuncparam_t* pFuncParam) {
  obparselocal_t*  pLocal;
  CObRecord*       pRecord;
  word		   RecordRefIndex = 0;
  word		   LocalRefIndex  = 0;
  int              Result;

  RefIndex = 0;

	/* Check for a match reference record  */
  pRecord = FindRefRecord(pRefToken->Value);

  if (pRecord != NULL) {
    if (pFuncParam != NULL) {
      if (!pRecord->IsFormType(pFuncParam->Type)) {
        Result = AddError(OB_SCRIPT_ERROR_BADFORMTYPE, pRefToken, "Function parameter '%s' is not a valid %s type!", pRefToken->Value.c_str(), ObGetScriptFuncParamString(pFuncParam->Type));
        return (Result);
      }
    }

    if (!pRecord->IsQuestItem()) {
      Result = AddError(OB_SCRIPT_ERROR_NOTPERSISTENT, pRefToken, "The reference '%s' is not set as a persistent reference!", pRefToken->Value.c_str());
      if (Result < 0) return (Result);
    }

    RecordRefIndex = AddReference(pRecord->GetFormID());
  }

	/* A begin block function must be a record reference */
  if (m_pCurrentFunction != NULL && m_pCurrentFunction->IsBeginFunction()) {
    RefIndex = RecordRefIndex;
    if (RefIndex > 0) return (OB_PARSE_RESULT_OK);
    return (OB_PARSE_RESULT_ERROR);
  }

	/* Check for a local reference variable */
  pLocal = FindLocalVariable(pRefToken->Value);

  if (pLocal != NULL && pLocal->TokenID == m_TokenVarRef) {
    
		/* Check for possible duplicate reference names */
    if (pRecord != NULL) {
      Result = AddError(OB_SCRIPT_ERROR_NAMECONFLICT, pRefToken, "Possible conflict of reference and local variable '%s'!", pRefToken->Value.c_str());
      if (Result < 0) return (Result);
    }
    
    LocalRefIndex = AddLocalReference(pRefToken->Value, pLocal->Index);
  }

	/* Prefer a record reference */
  if (RecordRefIndex > 0) {
    RefIndex = RecordRefIndex;
    return (OB_PARSE_RESULT_OK);
  }

  if (LocalRefIndex > 0) {
    RefIndex = LocalRefIndex;
    return (OB_PARSE_RESULT_OK);
  }

  return (OB_PARSE_RESULT_ERROR);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindReferenceIndex()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionRef (pRefToken);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionRef (tokeninstance_t* pRefToken) {
  tokeninstance_t* pToken;
  word		   RefIndex;
  int              Result;
  
	/* Ensure a valid reference */
  Result = FindReferenceIndex(RefIndex, pRefToken, NULL);

  if (Result < 0) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pRefToken, "Unknown reference '%s'!", pRefToken->Value);
    return (Result);
  }
  
	/* Output the reference data */
  OutputData((word) 0x001C);
  OutputData((word) RefIndex);

	/* Continue with the function call */
  pToken = MatchToken(m_TokenRef);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  pToken = MatchToken(m_TokenIdentifier, "Missing reference function call after '.'!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);

  return DoFunctionCall(pToken, true);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionRef()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionCall (pFuncToken, IsRefCall);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionCall (tokeninstance_t* pFuncToken, const bool IsRefCall) {
  CObScriptFunction* pFunction;
  int                Result;

  pFunction = ObGetScriptFunction(pFuncToken->Value);

  if (pFunction == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADFUNCTION, pFuncToken, "Unknown function '%s'!", pFuncToken->Value);
    return (Result);
  }

  if (!pFunction->IsUsesReference() && IsRefCall) {
    Result = AddError(OB_SCRIPT_ERROR_NONREFFUNCTION, pFuncToken, "Reference call on a non-reference function '%s'!", pFunction->GetName());
    if (Result < 0) return (Result);
  }

  OutputData(pFunction->GetOpCode());
  PushOutputSizeWord(m_OutputSize + 2);
  
  return DoFunctionHelper(pFunction, pFuncToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionCall()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionHelper (pFunction, pFuncToken);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionHelper (CObScriptFunction* pFunction, tokeninstance_t* pFuncToken) {
  int                Result;

	/* Special case functions */
  switch (pFunction->GetOpCode()) {

    case OB_FUNCOPCODE_GETSCRIPTVARIABLE:
	Result = AddError(OB_SCRIPT_ERROR_BADFUNCTION, pFuncToken, "The function 'GetScriptVariable' cannot be used in a script!");
	return (Result);

    case OB_FUNCOPCODE_GETQUESTVARIABLE:
        Result = AddError(OB_SCRIPT_ERROR_BADFUNCTION, pFuncToken, "The function 'GetQuestVariable' cannot be used in a script!");
	return (Result);
  }
  
	/* Normal functions */
  m_pCurrentFunction = pFunction;
  m_CurrentFuncParam = 0;
  m_FunctionParams.Empty();

  switch (pFunction->GetOpCode()) {
    case OB_FUNCOPCODE_MESSAGE:
        Result = DoFunctionMessage(pFunction);
	break;

    case OB_FUNCOPCODE_MESSAGEBOX:
        Result = DoFunctionMessageBox(pFunction);
	break;

    case OB_FUNCOPCODE_STOPCOMBAT:
        Result = DoFunctionStopCombat(pFunction);
	break;

    case OB_FUNCOPCODE_GETGAMESETTING:
	Result = DoFunctionGetGameSetting(pFunction);
	break;

    default:
        Result = DoFunctionParams();
	break;
  }

  m_pCurrentFunction = NULL;
  if (Result < 0) return (Result);
 
  PopOutputSizeWord(m_OutputSize);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionHelper()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int ParseExternalVariable (ExtVarInfo, pRecordToken);
 *
 *=========================================================================*/
int CObFixedParser::ParseExternalVariable (obextvarinfo_t& ExtVarInfo, tokeninstance_t* pRecordToken) {
  CObRecord*         pRecord;
  CObRecord*         pScptRecord;
  CObSubrecord*      pSubrecord;
  CObSlsdSubrecord*  pLocalSubrecord;
  CObBaseRefrRecord* pReference;
  CObRecord*         pBaseRefrRecord;
  CObScptRecord*     pScript;
  tokeninstance_t*   pToken;
  obformid_t	     FormID;
  int                Result;

	/* Initialize the return value */
  ExtVarInfo.pLocalData   = NULL;
  ExtVarInfo.pRecord      = NULL;
  ExtVarInfo.pRecordToken = pRecordToken;
  ExtVarInfo.pScript      = NULL;
  ExtVarInfo.pVarToken    = NULL;
  ExtVarInfo.pRefToken    = NULL;

  pToken = MatchToken(m_TokenRef);
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);
  ExtVarInfo.pRefToken = pToken;

  pToken = MatchToken(m_TokenIdentifier, "Missing reference variable after '.'!");
  if (pToken == NULL) return (OB_PARSE_RESULT_ERROR);
  ExtVarInfo.pVarToken = pToken;

	/* Ensure a valid reference */
	/* TODO: Actually use a reference here if required */
  pRecord = m_pRecordHandler->FindEditorID(pRecordToken->Value);
  ExtVarInfo.pRecord = pRecord;

  if (pRecord == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pRecordToken, "Unknown reference '%s'!", pRecordToken->Value);
    return (Result);
  }

	/* Ensure the record has a script */
  pReference = ObCastClass(CObBaseRefrRecord, pRecord);

	/* Special case for a reference */
  if (pReference != NULL) {
    pBaseRefrRecord = m_pRecordHandler->FindFormID(pReference->GetBaseFormID());

    if (pBaseRefrRecord == NULL) {
      Result = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid! The reference '%s' (unknown base record 0x%06X) does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str(), pReference->GetBaseFormID());
      return (Result);
    }

    pSubrecord = pBaseRefrRecord->FindSubrecord(OB_NAME_SCRI);

    if (pSubrecord == NULL) {
      CSString Buffer;
      pBaseRefrRecord->GetField(Buffer, OB_FIELD_EDITORID);
      Result = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid! The reference '%s' (base record '%s') does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str(), Buffer.c_str());
      return (Result);
    }
	
    if (!pReference->IsQuestItem()) {
      Result = AddError(OB_SCRIPT_ERROR_NOTPERSISTENT, pToken, "The reference '%s' is not set as a persistent reference!", pRecordToken->Value.c_str());
      if (Result < 0) return (Result);
    }

  }
	/* Is a regular record */
  else {
    pSubrecord = pRecord->FindSubrecord(OB_NAME_SCRI);

    if (pSubrecord == NULL) {
      Result = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Variable name '%s' is not valid! The record '%s' does not have a script!", pToken->Value.c_str(), pRecordToken->Value.c_str());
      return (Result);
    }

	/* Don't need a persistent check here */
  }

  FormID = *(dword *)pSubrecord->GetData();

  	/* Does the record have a script? */
  if (FormID == OB_FORMID_NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Record '%s' does not have a script!", pRecordToken->Value);
    return (Result);
  }

	/* Find the script */	
  pScptRecord = m_pRecordHandler->FindFormID(FormID);

  if (pScptRecord == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pToken, "Script 0x%08X used by record '%s' was not found!", FormID, pRecordToken->Value);
    return (Result);
  }

	/* Ensure a valid script */  
  pScript = ObCastClass(CObScptRecord, pScptRecord);
  ExtVarInfo.pScript = pScript;

  if (pScptRecord == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_UNKNOWNRECORD, pToken, "Script 0x%08X used by record '%s' is not valid!", FormID, pRecordToken->Value);
    return (Result);
  }

	/* Find a local variable in the given object */
  pLocalSubrecord = pScript->FindVariable(pToken->Value);
  ExtVarInfo.pLocalData = pLocalSubrecord;

  if (pLocalSubrecord == NULL) {
    Result = AddError(OB_SCRIPT_ERROR_BADVARIABLENAME, pToken, "Script '%s' does not have a local variable '%s'!", pScript->GetEditorID(), pToken->Value);
    return (Result);
  }

  if (pLocalSubrecord->GetSlsdData().Index > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_MAXLOCALS, pToken, "Exceeded the maximum number of local variables (65535) in script '%s'!", pScript->GetEditorID());
    return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::ParseExternalVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionParamExtVar (pParam, pRefToken);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionParamExtVar (obscriptfuncparam_t* pParam, tokeninstance_t* pRefToken) {
  obextvarinfo_t ExtVarInfo;
  word           RefIndex;
  int            Result;

	/* Parse the external variable reference and ensure it is valid */
  Result = ParseExternalVariable(ExtVarInfo, pRefToken);
  if (Result < 0) return (OB_PARSE_RESULT_ERROR);

	/* Ensure the variable matches the parameter type */
  if (pParam) {

    switch (pParam->Type) {
      case OB_FUNCPARAM_STRING:		/* String parameters not supported */
	Result = AddError(OB_SCRIPT_ERROR_BADSTRING, ExtVarInfo.pVarToken, "Function parameter '%s.%s' is not a valid string!", ExtVarInfo.pRecordToken->Value.c_str(), ExtVarInfo.pVarToken->Value.c_str());
	return (Result);
	
      case OB_FUNCPARAM_INTEGER:	/* Numeric types can accept any variable type */
      case OB_FUNCPARAM_FLOAT:
      case OB_FUNCPARAM_QUESTSTAGE:	/* TODO: ? */
      case OB_FUNCPARAM_CRIMETYPE:	/* TODO: ? */
	break;

      case OB_FUNCPARAM_ACTORVALUE:	/* Other unsupported types? */
      case OB_FUNCPARAM_AXIS:
      case OB_FUNCPARAM_ANIMATIONGROUP:
      case OB_FUNCPARAM_SEX:
      case OB_FUNCPARAM_VARIABLENAME:
      case OB_FUNCPARAM_FORMTYPE:
	Result = AddError(OB_SCRIPT_ERROR_BADPARAMETER, ExtVarInfo.pVarToken, "Function parameter '%s.%s' is not a valid %s!", ExtVarInfo.pRecordToken->Value.c_str(), ExtVarInfo.pVarToken->Value.c_str(),  ObGetScriptFuncParamString(pParam->Type));
	return (Result);

      default:				/* All other are reference types */

	if (!ExtVarInfo.pScript->IsVariableReference(ExtVarInfo.pLocalData)) {
	  Result = AddError(OB_SCRIPT_ERROR_BADPARAMETER, ExtVarInfo.pVarToken, "Function parameter '%s.%s' is not a reference variable!", ExtVarInfo.pRecordToken->Value.c_str(), ExtVarInfo.pVarToken->Value.c_str(),  ObGetScriptFuncParamString(pParam->Type));
	  return (Result);
	}

	break;
    }
  }


	/* Update the function parameter stack */
  m_FunctionParams.Add(ExtVarInfo.pRefToken);
  m_FunctionParams.Add(ExtVarInfo.pVarToken);

 	/* Add the reference */
  RefIndex = AddReference(ExtVarInfo.pRecord->GetFormID());

	/* Output the reference data */
  OutputData((byte) 0x72);
  OutputData((word) RefIndex);

  	/* Output the local variable data */
  OutputData((byte) ExtVarInfo.pLocalData->IsShortLong() ? 0x73 : 0x66);
  OutputData((word) (word) ExtVarInfo.pLocalData->GetSlsdData().Index);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionParamExtVar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionMessage (pFunction);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionMessage (CObScriptFunction* pFunction) {
  tokeninstance_t* pMsgToken;
  tokeninstance_t* pToken;
  int		   ParamCount = 0;
  int		   ButtonCount = 0;
  int              Result;

	/* Parse the main message script */
  pMsgToken = MatchToken(m_TokenString, "Missing main string in MessageBox function call!");
  if (pMsgToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (pMsgToken->Value.GetLength() > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_BADSTRING, pMsgToken, "Exceeded maximum string length of 65535 characters in MessageBox string!");
    return (Result);
  }

	/* Output main message box string */
  m_FunctionParams.Add(pMsgToken);
  OutputData((word) 0x0001);
  OutputData((word) pMsgToken->Value.GetLength());
  OutputData(pMsgToken->Value.c_str(), pMsgToken->Value.GetLength());

  PushOutputSizeWord(0);

	/* Parse all messagebox parameters */
  while (LookAhead(m_TokenIdentifier) || LookAhead(m_TokenComma)) {
  
		/* Match the optional comma */
    if (LookAhead(m_TokenComma)) { 
      MatchToken(m_TokenComma); 
      continue;
    }

    if (ParamCount > OB_SCRIPT_MESSAGE_MAXVARS) {
      PopOutputSizeWord(ParamCount);
      Result = AddError(OB_SCRIPT_ERROR_MAXMESSAGEPARAMS, GetCurrentToken(), "Exceeded maximum number of parameters (%d) in a MessageBox call!", OB_SCRIPT_MESSAGE_MAXVARS);
      if (Result < 0) return (Result);
    }

    pToken = MatchToken(m_TokenIdentifier);
    m_FunctionParams.Add(pToken);
    ++ParamCount;

    if (LookAhead(m_TokenRef)) {
      Result = DoFunctionParamExtVar(NULL, pToken);
      if (Result < 0) return (Result);
    }
    else {
      Result = DoLocalGlobalOutput(pToken);
      if (Result < 0) return (Result);
    }
  }
  
  PopOutputSizeWord(ParamCount);
    
  	/* Match the optional display seconds */
  if (LookAhead(m_TokenInteger)) { 
    pToken = MatchToken(m_TokenInteger); 
    OutputData(pToken->Value.c_str(), pToken->Value.GetLength());
  }
  else if (LookAhead(m_TokenFloat)) {
    pToken = GetCurrentToken(); 
    Result = AddError(OB_SCRIPT_ERROR_BADINTEGER, pToken, "Floating point value '%s' is not valid for the timer parameter in a message function call!", pToken->Value.c_str()); 
    return (Result);
  }

	/* Check the messagebox output variables */
  Result = CheckMessageVariables();
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionMessage()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionMessageBox (pFunction);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionMessageBox (CObScriptFunction* pFunction) {
  tokeninstance_t* pMsgToken;
  tokeninstance_t* pToken;
  int		   ParamCount = 0;
  int		   ButtonCount = 0;
  int              Result;

	/* Parse the main message script */
  pMsgToken = MatchToken(m_TokenString, "Missing main string in MessageBox function call!");
  if (pMsgToken == NULL) return (OB_PARSE_RESULT_ERROR);

  if (pMsgToken->Value.GetLength() > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_BADSTRING, pMsgToken, "Exceeded maximum string length of 65535 characters in MessageBox string!");
    return (Result);
  }

	/* Output main message box string */
  m_FunctionParams.Add(pMsgToken);
  OutputData((word) 0x0001);
  OutputData((word) pMsgToken->Value.GetLength());
  OutputData(pMsgToken->Value.c_str(), pMsgToken->Value.GetLength());

  PushOutputSizeWord(0);

	/* Parse all messagebox parameters */
  while (LookAhead(m_TokenIdentifier) || LookAhead(m_TokenComma)) {

		/* Match the optional comma */
    if (LookAhead(m_TokenComma)) { 
      MatchToken(m_TokenComma); 
      continue;
    }

    if (ParamCount > OB_SCRIPT_MESSAGE_MAXVARS) {
      PopOutputSizeWord(ParamCount);
      Result = AddError(OB_SCRIPT_ERROR_MAXMESSAGEPARAMS, GetCurrentToken(), "Exceeded maximum number of parameters (%d) in a MessageBox call!", OB_SCRIPT_MESSAGE_MAXVARS);
      if (Result < 0) return (Result);
    }

    pToken = MatchToken(m_TokenIdentifier);
    m_FunctionParams.Add(pToken);
    ++ParamCount;

    if (LookAhead(m_TokenRef)) {
      Result = DoFunctionParamExtVar(NULL, pToken);
      if (Result < 0) return (Result);
    }
    else {
	Result = DoLocalGlobalOutput(pToken);
	if (Result < 0) return (Result);
    }
  }

  PopOutputSizeWord(ParamCount);
  PushOutputSizeWord(0);

	/* Parse all messagebox buttons */
  while (LookAhead(m_TokenString) || LookAhead(m_TokenComma)) {

  		/* Match the optional comma */
    if (LookAhead(m_TokenComma)) { 
      MatchToken(m_TokenComma); 
      continue;
    }

    if (ButtonCount > OB_SCRIPT_MESSAGE_MAXBUTTONS) {
      PopOutputSizeWord(ParamCount);
      Result = AddError(OB_SCRIPT_ERROR_MAXMESSAGEBUTTONS, GetCurrentToken(), "Exceeded maximum number of buttons (%d) in a MessageBox call!", OB_SCRIPT_MESSAGE_MAXVARS);
      if (Result < 0) return (Result);
    }

    pToken = MatchToken(m_TokenString);
    m_FunctionParams.Add(pToken);
    ++ButtonCount;

    OutputData((word) 0x0001);
    OutputData((word) pToken->Value.GetLength());
    OutputData(pToken->Value.c_str(), pToken->Value.GetLength());
  }

  PopOutputSizeWord(ButtonCount);

	/* Check the messagebox output variables */
  Result = CheckMessageVariables();
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionMessageBox()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionStopCombat (pFunction);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionStopCombat (CObScriptFunction* pFunction) {
  tokeninstance_t* pToken;
  CObRecord*       pRecord;
  obparseref_t*    pLocalRef;
  int              Result;

	/* Do the regular function */
  Result = DoFunctionParams();
  if (Result < 0) return (Result);

	/* Check for an extra parameter after the function call */
  pToken = LookAhead(m_TokenIdentifier);
  if (pToken == NULL) return (OB_PARSE_RESULT_OK);

	/* Is this identifier a reference? */
  pRecord = FindRefRecord(pToken->Value);

  if (pRecord != NULL) {

    if (pRecord->IsFormType(OB_FUNCPARAM_ACTOR)) {
      Result = AddError(OB_SCRIPT_ERROR_EXTRASTOPCOMBATPARAM, pToken, "Ignoring extra actor parameter '%s' after StopCombat function!", pToken->Value.c_str());
      if (Result < 0) return (Result);
      MatchToken(m_TokenIdentifier);
    }

    return (OB_PARSE_RESULT_OK);
  }

	/* Is thie identifier a reference local variable */
  pLocalRef = FindLocalReference(pToken->Value);

  if (pLocalRef != NULL) {
    Result = AddError(OB_SCRIPT_ERROR_EXTRASTOPCOMBATPARAM, pToken, "Ignoring extra reference parameter '%s' after StopCombat function!", pToken->Value.c_str());
    if (Result < 0) return (Result);
    MatchToken(m_TokenIdentifier);
    return (OB_PARSE_RESULT_OK);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionStopCombat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int DoFunctionGetGameSetting (pFunction);
 *
 *=========================================================================*/
int CObFixedParser::DoFunctionGetGameSetting (CObScriptFunction* pFunction) {
  tokeninstance_t* pToken;
  int              Result;

  PushOutputSizeWord(0);

	/* Ignore optional comma */
  if (LookAhead(m_TokenComma)) MatchToken(m_TokenComma);

	/* Get the one and only parameter */
  if (LookAhead(m_TokenString)) {
    pToken = MatchToken(m_TokenString);
    ++m_CurrentFuncParam;
  }
  else if (LookAhead(m_TokenIdentifier)) {
    pToken = MatchToken(m_TokenIdentifier);
    ++m_CurrentFuncParam;
  }
  else {
    pToken = GetCurrentToken();
    Result = AddError(OB_SCRIPT_ERROR_BADGAMESETTING, pToken, "Expecting game setting but found '%s'!", pToken->Value.c_str());
    if (Result < 0) return (Result);
    ++m_CurrentToken;
  }

	/* Output the symbol */
  OutputData(pToken->Value.c_str(), pToken->Value.GetLength());

  Result = PopOutputSizeWord(m_CurrentFuncParam);
  if (Result < 0) return (Result);

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::DoFunctionGetGameSetting()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - CObIdRecord* FindRefRecord (pEditorID);
 *
 *=========================================================================*/
CObIdRecord* CObFixedParser::FindRefRecord (const char* pEditorID) {

	/* Check for the special player reference */
  if (stricmp(pEditorID, "player") == 0) return m_pRecordHandler->GetPlayerReference();

  return m_pRecordHandler->FindEditorID(pEditorID);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindRefRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int IsValidMessageFormat (Format, pString, pMsgToken);
 *
 *=========================================================================*/
int CObFixedParser::IsValidMessageFormat (CSString& Format, const char* pString, tokeninstance_t* pMsgToken) {
  bool     HasPlus   = false;
  bool     HasMinus  = false;
  bool     HasSpace  = false;
  bool     HasZero   = false;
  bool     HasPeriod = false;
  CSString Buffer;
  char     Type = 0;
  int      Width;
  int      Decimals;
  int      Result;

  Format.Empty();
  if (pString == NULL) return (OB_PARSE_RESULT_ERROR);
  //SystemLog.Printf("Checking format '%s'...", pString);

  if (*pString != '%') {
    Result = AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "A message format must begin with a '%%' character!");
    return (Result);
  }

        /* Simple % escape sequence */
  Format += '%';
  ++pString;

  if (*pString == '%') {
    Format += '%';
    return (OB_PARSE_RESULT_OK);
  }

        /* Initial options */
  while (*pString != 0) {

    if (*pString == '+') {
      if (HasPlus) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Extra leading '+' option in format string!");
      HasPlus = true;
    }
    else if (*pString == '-') {
      if (HasMinus) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Extra leading '-' option in format string!");
      HasMinus = true;
    }
    else if (*pString == '0') {
      if (HasZero) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Extra leading '0' option in format string!");
      HasZero = true;
    }
    else if (*pString == ' ') {
      if (HasSpace) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Extra leading ' ' option in format string!");
      HasSpace = true;
    }
    else {
      break;
    }

    Format += *pString;
    ++pString;
  }

        /* Optional Width */
  Buffer.Empty();

  while (isdigit(*pString)) {
    Buffer += *pString;
    Format += *pString;
    ++pString;
  }

  if (!Buffer.IsEmpty()) {
    Width = atoi(Buffer);
    if (Width <= 0) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Format string has a negative or zero width value '%s'!", Buffer);
    if (Width > 32) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Format string has a very large width value '%s'!", Buffer);
  }

        /* Optional period */
  while (*pString == '.') {
    if (HasPeriod) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Extra '.' in format string!");
    HasPeriod = true;
    Format += *pString;
    ++pString;
  }

        /* Optional decimal width */
  Buffer.Empty();

  while (isdigit(*pString)) {
    Buffer += *pString;
    Format += *pString;
    ++pString;
  }

  if (!Buffer.IsEmpty()) {
    Decimals = atoi(Buffer);
    if (Decimals <  0) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Format string has a negative or zero precision value '%s'!", Buffer);
    if (Decimals > 32) AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Format string has a very large precision value '%s'!", Buffer);
  }

        /* Must have a final format type */
  Type = *pString;
  Format += *pString;

  switch (Type) {
    case 'e':
    case 'g':
    case 'f':
        break;
    default:
        Result = AddError(OB_SCRIPT_ERROR_BADMESSAGEFORMAT, pMsgToken, "Unknown format string type specifier '%c' found!", *pString);
        if (Result < 0) return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::IsValidMessageFormat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int CheckMessageVariables (void);
 *
 *=========================================================================*/
int CObFixedParser::CheckMessageVariables (void) {
  tokeninstance_t* pMsgToken;
  tokeninstance_t* pToken = NULL;
  CSString	   Format;
  const char*      pParse;
  dword            ParamIndex;
  int              Result;

  pMsgToken = m_FunctionParams.GetAt(0);
  if (pMsgToken == NULL) return (OB_PARSE_RESULT_OK);

  ParamIndex = 1;
  pParse     = strchr(pMsgToken->Value, '%');

  while (pParse != NULL) {

		/* Special case for the percent sign escape sequence */
    if (pParse[1] == '%') {
      ++pParse;
    }
    else {
      Result = IsValidMessageFormat(Format, pParse, pMsgToken);
      //if (Result < 0) return (Result);

      pToken = m_FunctionParams.GetAt(ParamIndex);

		/* Skip external variable references */
      if (pToken != NULL && pToken->pToken->GetID() == m_TokenRef) {
        ParamIndex += 2;
	pToken = m_FunctionParams.GetAt(ParamIndex);
      }

      if (pToken == NULL) {
        Result = AddError(OB_SCRIPT_ERROR_MISSINGMESSAGEVAR, pMsgToken, "Missing output variable #%d in Message/MessageBox call!", ParamIndex);
	if (Result < 0) return (Result);
      }
      else if (pToken->pToken->GetID() == m_TokenString) {
        Result = AddError(OB_SCRIPT_ERROR_MISSINGMESSAGEVAR, pMsgToken, "Missing output variable #%d in Message/MessageBox call!", ParamIndex);
	if (Result < 0) return (Result);
      }

      ++ParamIndex;  
    }

    pParse = strchr(pParse + 1, '%');
  }

	/* Skip external variable references */
  pToken = m_FunctionParams.GetAt(ParamIndex);

  if (pToken != NULL && pToken->pToken->GetID() == m_TokenRef) {
    ParamIndex += 2;
  }

	/* Check for extra variables */
  for (; ParamIndex < m_FunctionParams.GetSize(); ++ParamIndex) {
    pToken = m_FunctionParams.GetAt(ParamIndex);
    if (pToken->pToken->GetID() == m_TokenString) break;

    Result = AddError(OB_SCRIPT_ERROR_EXTRAMESSAGEVAR, pToken, "Extra output variable #%d (%s) in Message/MessageBox call!", ParamIndex, pToken->Value.c_str());
    if (Result < 0) return (Result);
  }

  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::CheckMessageVariables()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int FindLocalVariableIndex (pString);
 *
 *=========================================================================*/
int CObFixedParser::FindLocalVariableIndex (const char* pString) {
  obparselocal_t* pLocal;
  
  pLocal = FindLocalVariable(pString);
  if (pLocal != NULL) return (pLocal->Index);

  return (-1);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindLocalVariableIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - obparselocal_t* FindLocalVariable (pString);
 *
 *=========================================================================*/
obparselocal_t* CObFixedParser::FindLocalVariable (const char* pString) {
  obparselocal_t* pLocal;
  dword           Index;

  for (Index = 0; Index < m_LocalVariables.GetSize(); ++Index) {
    pLocal = m_LocalVariables.GetAt(Index);
    if (pLocal->Name.CompareNoCase(pString) == 0) return (pLocal);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::FindLocalVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - tokeninstance_t* MatchToken (TokenID, pErrorString);
 *
 * Uses a custom error string if the token does not match.
 *
 *=========================================================================*/
tokeninstance_t* CObFixedParser::MatchToken (const int TokenID, const char* pErrorString) {
  tokeninstance_t* pToken;

  pToken = m_pTokens->GetAt(m_CurrentToken);

  if (pToken == NULL) {
    AddError(OB_SCRIPT_ERROR_BADTOKEN, NULL, "Unexpected end of program found!");
    return (NULL);
  }
 
  assert(pToken->pToken != NULL);

  if (pToken->pToken->GetID() != TokenID) {
    CTokenType* pType = m_pTokenTypes->GetTokenType(TokenID);

    if (pToken->pToken->GetID() == m_TokenIdentifier)
      AddError(OB_SCRIPT_ERROR_BADTOKEN, pToken, "Expected '%s' but found '%s' (%s)!", pType ? pType->GetName() : "n/a", pToken->pToken->GetName(), pToken->Value);   
    else
      AddError(OB_SCRIPT_ERROR_BADTOKEN, pToken, "Expected '%s' but found '%s'!", pType ? pType->GetName() : "n/a", pToken->pToken->GetName());   

    AddError(0, pToken, pErrorString);
    return (NULL);
  }

  ++m_CurrentToken;
  return (pToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::MatchToken()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - tokeninstance_t* MatchToken (TokenID);
 *
 * Matches the next token in the stream to the given type. On success the
 * token stream is advanced one and the token is returns. Returns NULL on any
 * error if the next token is not the given type.
 *
 *=========================================================================*/
tokeninstance_t* CObFixedParser::MatchToken (const int TokenID) {
  tokeninstance_t* pToken;

  pToken = m_pTokens->GetAt(m_CurrentToken);

  if (pToken == NULL) {
    AddError(OB_SCRIPT_ERROR_BADTOKEN, NULL, "Unexpected end of program found!");
    return (NULL);
  }
 
  assert(pToken->pToken != NULL);

  if (pToken->pToken->GetID() != TokenID) {
    CTokenType* pType = m_pTokenTypes->GetTokenType(TokenID);
    AddError(OB_SCRIPT_ERROR_BADTOKEN, pToken, "Expected '%s' but found '%s'!", pType ? pType->GetName() : "n/a", pToken->pToken->GetName());
    return (NULL);
  }

  ++m_CurrentToken;
  return (pToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::MatchToken()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - tokeninstance_t* LookAhead (TokenID);
 *
 * Matches the next token in the stream to the given type. On success the
 * token stream is advanced one and the token is returns. Returns NULL on any
 * error if the next token is not the given type.
 *
 *=========================================================================*/
tokeninstance_t* CObFixedParser::LookAhead (const int TokenID) {
  tokeninstance_t* pToken;

  pToken = m_pTokens->GetAt(m_CurrentToken);
  if (pToken == NULL) return (NULL);
   
  assert(pToken->pToken != NULL);
  if (pToken->pToken->GetID() != TokenID) return (NULL);

  return (pToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::LookAhead()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - tokeninstance_t* GetCurrentToken (void);
 *
 *=========================================================================*/
tokeninstance_t* CObFixedParser::GetCurrentToken (void) {
  return m_pTokens->GetAt(m_CurrentToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::GetCurrentToken()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - bool OutputData (Value);
 *
 *=========================================================================*/
bool CObFixedParser::OutputData (const char   Value) {  return OutputData((byte*)&Value, 1); }
bool CObFixedParser::OutputData (const byte   Value) {  return OutputData((byte*)&Value, 1); }
bool CObFixedParser::OutputData (const short  Value) {  return OutputData((byte*)&Value, 2); }
bool CObFixedParser::OutputData (const word   Value) {  return OutputData((byte*)&Value, 2); }
bool CObFixedParser::OutputData (const dword  Value) {  return OutputData((byte*)&Value, 4); }
bool CObFixedParser::OutputData (const int    Value) {  return OutputData((byte*)&Value, 4); }
bool CObFixedParser::OutputData (const float  Value) {  return OutputData((byte*)&Value, 4); }
bool CObFixedParser::OutputData (const double Value) {  return OutputData((byte*)&Value, 8); }
/*===========================================================================
 *		End of Class Method CObFixedParser::OutputData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - bool OutputData (pData, Size);
 *
 *=========================================================================*/
bool CObFixedParser::OutputData (const byte* pData, const dword Size) {
  byte* pNewData;
  dword NewSize;
  
	/* Grow array as needed */
  if (m_OutputSize + Size >= m_AllocatedOutputSize) {
    NewSize = m_AllocatedOutputSize*2 + 256;
    pNewData = new byte[NewSize];
    m_AllocatedOutputSize = NewSize;

    if (m_pOutputData != NULL) {
      memcpy(pNewData, m_pOutputData, m_OutputSize);
      delete[] m_pOutputData;
    }

    m_pOutputData = pNewData;
  }

	/* Copy data */
  memcpy(m_pOutputData + m_OutputSize, pData, Size);
  m_OutputSize += Size;

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::OutputData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - bool Parse (void);
 *
 *=========================================================================*/
bool CObFixedParser::Parse (void) {
  int Result;
  
  ClearParseData();
  
  if (m_pTokens == NULL || m_pTokenTypes == NULL) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Script token data has not been set!");
    return (false);
  }

  if (m_pRecordHandler == NULL) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Script record handler has not been set!");
    return (false);
  }

  if (m_pScript == NULL) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Script has not been set!");
    return (false);
  }

  ResolveTokenTypes();

  Result = DoMainProgram();
  if (Result < 0) return (false);

  //CObFile File;
  //File.Open("test.dat", "wb");
  //File.Write(m_pOutputData, m_OutputSize);
  //File.Close();

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::Parse()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - obparselength_t* PushOutputSizeWord (Size, UseSecondStack);
 *
 *=========================================================================*/
obparselength_t* CObFixedParser::PushOutputSizeWord (const dword Size, const bool UseSecondStack) {
  obparselength_t* pLength;

  pLength = new obparselength_t;

  if (UseSecondStack)
    m_OutputSizeStack2.Add(pLength);
  else
    m_OutputSizeStack.Add(pLength);

  pLength->OutputPos  = m_OutputSize;
  
	/* Add the placeholder size to the output data */
  OutputData((word) 0x0000);

  pLength->OutputSize = Size;

  return (pLength);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::PushOutputSizeWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int PopOutputSizeWord (Size, UseSecondStack);
 *
 *=========================================================================*/
int CObFixedParser::PopOutputSizeWord (const dword Size, const bool UseSecondStack) {
  obparselength_t*     pLength;
  CObParseLengthStack* pStack = &m_OutputSizeStack;
  dword		       Index;
  int                  Result;

  if (UseSecondStack) pStack = &m_OutputSizeStack2;

  if (pStack->GetSize() == 0) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Popped an empty output size stack (this shouldn't happen)!");
    return (OB_PARSE_RESULT_ERROR);
  }

  Index   = pStack->GetSize() - 1;
  pLength = pStack->GetAt(Index);
  if (pLength == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Sanity check */
  if (Size < pLength->OutputSize) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Invalid negative output size length found!");
    return (OB_PARSE_RESULT_ERROR);
  }

	/* Check for size overflows */
  dword DiffSize = (Size - pLength->OutputSize);

  if (DiffSize > 65535) {
    Result = AddError(OB_SCRIPT_ERROR_BADEXPRESSION, NULL, "Output size overflow! Expression exceeds maximum output size of 65535 bytes!");
    return (OB_PARSE_RESULT_ERROR);
  }

	/* Update the length in the compiler data */
  *(word *)(m_pOutputData + pLength->OutputPos) = (word) DiffSize;

  pStack->Delete(Index);
  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::PopOutputSizeWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - obparselength_t* PushOutputSizeDWord (Size, UseSecondStack);
 *
 *=========================================================================*/
obparselength_t* CObFixedParser::PushOutputSizeDWord (const dword Size, const bool UseSecondStack) {
  obparselength_t* pLength;

  pLength = new obparselength_t;

  if (UseSecondStack)
    m_OutputSizeStack2.Add(pLength);
  else
    m_OutputSizeStack.Add(pLength);

  pLength->OutputPos = m_OutputSize;
  
	/* Add the placeholder size to the output data */
  OutputData((dword) 0x00000000);

  pLength->OutputSize = Size;
  return (pLength);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::PushOutputSizeDWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - int PopOutputSizeDWord (Size, UseSecondStack);
 *
 *=========================================================================*/
int CObFixedParser::PopOutputSizeDWord (const dword Size, const bool UseSecondStack) {
  obparselength_t*     pLength;
  CObParseLengthStack* pStack = &m_OutputSizeStack;
  dword		       Index;

  if (UseSecondStack) pStack = &m_OutputSizeStack2;

  if (pStack->GetSize() == 0) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Popped an empty output size stack (this shouldn't happen)!");
    return (OB_PARSE_RESULT_ERROR);
  }

  Index   = pStack->GetSize() - 1;
  pLength = pStack->GetAt(Index);
  if (pLength == NULL) return (OB_PARSE_RESULT_ERROR);

	/* Sanity check */
  if (Size < pLength->OutputSize) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Invalid negative output size length found!");
    return (OB_PARSE_RESULT_ERROR);
  }

	/* Check for size overflows */
  dword DiffSize = (Size - pLength->OutputSize);

	/* Update the length in the compiler data */
  *(dword *)(m_pOutputData + pLength->OutputPos) = DiffSize;

  pStack->Delete(Index);
  return (OB_PARSE_RESULT_OK);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::PopOutputSizeDWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void PopExpressionsTo (TokenID);
 *
 *=========================================================================*/
void CObFixedParser::PopExpressionsTo (const int TokenID) {
  tokeninstance_t* pToken;
  int		   Index = m_ExpressionStack.GetSize() - 1;

  pToken = m_ExpressionStack.GetAt(Index);
  if (pToken == NULL) return;

  do {
    m_ExpressionStack.Delete(Index);

    if (pToken->pToken->GetID() != m_TokenLBracket) {
      OutputData((byte) ' ');
      OutputData(pToken->Value, pToken->Value.GetLength());
    }

    if (pToken->pToken->GetID() == TokenID) break;

    Index  = m_ExpressionStack.GetSize() - 1;
    pToken = m_ExpressionStack.GetAt(Index);
  } while (pToken != NULL);

}
/*===========================================================================
 *		End of Class Method CObFixedParser::PopExpressionsTo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void PopExpressions (TokenID);
 *
 *=========================================================================*/
void CObFixedParser::PopExpressions (const int TokenID) {
  tokeninstance_t* pToken;
  bool             Match;
  int		   Index = m_ExpressionStack.GetSize() - 1;

  pToken = m_ExpressionStack.GetAt(Index);
  
  while (pToken != NULL) {
    Match = false;

    if (pToken->pToken->GetID() == TokenID) 
      Match = true;
    else if (TokenID == m_TokenAddOp)
      Match = (pToken->pToken->GetID() == m_TokenMultOp);
    else if (TokenID == m_TokenRelOp)
      Match = (pToken->pToken->GetID() == m_TokenMultOp) || (pToken->pToken->GetID() == m_TokenAddOp);
    else if (TokenID == m_TokenBoolOp)
      Match = (pToken->pToken->GetID() == m_TokenMultOp) || (pToken->pToken->GetID() == m_TokenAddOp) || (pToken->pToken->GetID() == m_TokenRelOp);

    if (!Match) break;

    m_ExpressionStack.Delete(Index);

    if (pToken->pToken->GetID() != m_TokenLBracket) {
      OutputData((byte) ' ');
      OutputData(pToken->Value, pToken->Value.GetLength());
    }
   
    Index  = m_ExpressionStack.GetSize() - 1;
    pToken = m_ExpressionStack.GetAt(Index);
  }

}
/*===========================================================================
 *		End of Class Method CObFixedParser::PopExpressions()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void PushExpression (pToken);
 *
 *=========================================================================*/
void CObFixedParser::PushExpression (tokeninstance_t* pToken) {
  m_ExpressionStack.Add(pToken);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::PushExpression()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - void ResetTokens (void);
 *
 *=========================================================================*/
void CObFixedParser::ResetTokens (void) {
  m_TokenUnknown	= TOKEN_ID_UNKNOWN;
  m_TokenLBracket	= TOKEN_ID_UNKNOWN;
  m_TokenRBracket	= TOKEN_ID_UNKNOWN;
  m_TokenAddOp		= TOKEN_ID_UNKNOWN;
  m_TokenMultOp		= TOKEN_ID_UNKNOWN;
  m_TokenRelOp		= TOKEN_ID_UNKNOWN;
  m_TokenBoolOp		= TOKEN_ID_UNKNOWN;
  m_TokenString		= TOKEN_ID_UNKNOWN;
  m_TokenIdentifier	= TOKEN_ID_UNKNOWN;
  m_TokenIf		= TOKEN_ID_UNKNOWN;
  m_TokenElseif		= TOKEN_ID_UNKNOWN;
  m_TokenElse		= TOKEN_ID_UNKNOWN;
  m_TokenEndif		= TOKEN_ID_UNKNOWN;
  m_TokenSet		= TOKEN_ID_UNKNOWN;
  m_TokenScriptname	= TOKEN_ID_UNKNOWN;
  m_TokenBegin		= TOKEN_ID_UNKNOWN;
  m_TokenEnd		= TOKEN_ID_UNKNOWN;
  m_TokenEndLine	= TOKEN_ID_UNKNOWN;
  m_TokenInteger	= TOKEN_ID_UNKNOWN;
  m_TokenFloat		= TOKEN_ID_UNKNOWN;
  m_TokenRef		= TOKEN_ID_UNKNOWN;
  m_TokenReturn		= TOKEN_ID_UNKNOWN;
  m_TokenComma		= TOKEN_ID_UNKNOWN;
  m_TokenEndofProgram	= TOKEN_ID_UNKNOWN;
  m_TokenVarShort	= TOKEN_ID_UNKNOWN;
  m_TokenVarLong	= TOKEN_ID_UNKNOWN;
  m_TokenVarFloat	= TOKEN_ID_UNKNOWN;
  m_TokenVarRef		= TOKEN_ID_UNKNOWN;
  m_TokenTo		= TOKEN_ID_UNKNOWN;
}
/*===========================================================================
 *		End of Class Method CObFixedParser::ResetTokens()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFixedParser Method - bool ResolveTokenTypes (void);
 *
 * Finds the current value of required script tokens. Returns false if any
 * are not found.
 *
 *=========================================================================*/
bool CObFixedParser::ResolveTokenTypes (void) {

	/* Abort if token types are not set */
  if (m_pTokenTypes == NULL) {
    AddError(OB_SCRIPT_ERROR_INTERNAL, NULL, "Cannot resolve token types as array has not been set!");
    return (false);
  }

  m_TokenUnknown	= m_pTokenTypes->FindTokenID("Unknown");
  if ((m_TokenLBracket	= m_pTokenTypes->FindTokenID("LBracket")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenRBracket	= m_pTokenTypes->FindTokenID("RBracket")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenAddOp	= m_pTokenTypes->FindTokenID("Addop")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenMultOp	= m_pTokenTypes->FindTokenID("Multop")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenRelOp	= m_pTokenTypes->FindTokenID("Relop")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenBoolOp	= m_pTokenTypes->FindTokenID("Boolop")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenString	= m_pTokenTypes->FindTokenID("String")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenIdentifier= m_pTokenTypes->FindTokenID("Identifier")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenIf	= m_pTokenTypes->FindTokenID("If")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenElseif	= m_pTokenTypes->FindTokenID("Elseif")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenElse	= m_pTokenTypes->FindTokenID("Else")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenEndif	= m_pTokenTypes->FindTokenID("Endif")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenSet	= m_pTokenTypes->FindTokenID("Set")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenScriptname= m_pTokenTypes->FindTokenID("Scriptname")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenBegin	= m_pTokenTypes->FindTokenID("Begin")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenEnd	= m_pTokenTypes->FindTokenID("End")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenEndLine	= m_pTokenTypes->FindTokenID("Endline")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenInteger	= m_pTokenTypes->FindTokenID("Integer")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenFloat	= m_pTokenTypes->FindTokenID("Float")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenRef	= m_pTokenTypes->FindTokenID("RefCall")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenReturn	= m_pTokenTypes->FindTokenID("Return")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenComma	= m_pTokenTypes->FindTokenID("Comma")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenEndofProgram = m_pTokenTypes->FindTokenID("Endofprogram")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenVarShort	= m_pTokenTypes->FindTokenID("Short")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenVarLong	= m_pTokenTypes->FindTokenID("Long")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenVarFloat	= m_pTokenTypes->FindTokenID("Float")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenTo	= m_pTokenTypes->FindTokenID("To")) == TOKEN_ID_UNKNOWN) return (false);
  if ((m_TokenVarRef	= m_pTokenTypes->FindTokenID("Ref")) == TOKEN_ID_UNKNOWN) return (false);
  

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFixedParser::ResolveTokenTypes()
 *=========================================================================*/


 