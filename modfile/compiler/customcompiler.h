/*===========================================================================
 *
 * File:	Customcompiler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Defines the CCustomCompiler class.
 *
 *=========================================================================*/
#ifndef __CUSTOMCOMPILER_H
#define __CUSTOMCOMPILER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "charclassarray.h"
  #include "tokentypearray.h"
  #include "tokentablearray.h"
  #include "scansourcestring.h"
  #include "obfixedparser.h"
  #include "obscripterrors.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CCustomCompiler Definition
 *
 *=========================================================================*/
class CCustomCompiler {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CCharClassArray	m_CharClasses;
  CTokenTypeArray	m_TokenTypes;
  CTokenTableArray	m_TokenTables;

  CTokenInstanceArray	m_Tokens;

  CSString		m_CurrentToken;
  char			m_CurrentTokenChar;
  bool			m_GetTokenChar;

  CObFixedParser	m_Parser;

  CObRecordHandler*	m_pRecordHandler;
  CObScptRecord*	m_pScript;

  obscripterrorinfo_t	m_ErrorInfo;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper tokenize methods */
  CTokenType*      RunTokenTable    (CTokenTable* pTable, CScanSource* pScanSource);
  tokeninstance_t* AddTokenInstance (CTokenType* pToken, const sourcepos_t StartPos, const sourcepos_t EndPos);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CCustomCompiler();
  virtual ~CCustomCompiler() { Destroy(); }
  virtual void Destroy (void);

  int AddError (const int ErrorID, sourcepos_t& Pos, const char* pString, ...);

	/* Attempt to compile the given script */
  bool Compile (CObScptRecord* pScript);

	/* Get class members */
  CTokenInstanceArray& GetTokens         (void) { return (m_Tokens); }
  CObFixedParser&      GetParser         (void) { return (m_Parser); }
  CTokenTypeArray&     GetTokenTypes     (void) { return (m_TokenTypes); }
  CObScriptErrorArray& GetErrors         (void) { return (m_ErrorInfo.Errors); }
  dword                GetErrorCount     (void) { return (m_ErrorInfo.ErrorCount); }
  dword                GetWarningCount   (void) { return (m_ErrorInfo.WarningCount); }

	/* Load compiler definitions from the given file */
  bool Load (const char* pFilename);

	/* Set class members */
  void SetRecordHandler (CObRecordHandler* pHandler) { m_pRecordHandler = pHandler; }

	/* Tokenize the given source */
  bool Tokenize (CScanSource* pScanSource);

};
/*===========================================================================
 *		End of Class CCustomCompiler Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Customcompiler.H
 *=========================================================================*/
