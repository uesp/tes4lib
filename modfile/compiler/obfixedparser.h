/*===========================================================================
 *
 * File:	Obfixedparser.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBFIXEDPARSER_H
#define __OBFIXEDPARSER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentypearray.h"
  #include "../obrecordhandler.h"
  #include "../records/obscptrecord.h"
  #include "obscripterrors.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Parser return codes */
  #define OB_PARSE_RESULT_OK		0
  #define OB_PARSE_RESULT_ERROR		-1
  #define OB_PARSE_RESULT_WARNING	1
  #define OB_PARSE_RESULT_ENDFUNCTION	2
  #define OB_PARSE_RESULT_ENDBLOCK      3

  #define OB_SCRIPT_MESSAGE_MAXVARS	9
  #define OB_SCRIPT_MESSAGE_MAXBUTTONS  10

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  struct obparselength_t {
	dword OutputPos;
	dword OutputSize;
  };

  typedef CObPtrArray<obparselength_t> CObParseLengthStack;

  struct obparselocal_t {
	int      Index;
	CSString Name;
	int	 TokenID;
	dword    Flags;

	obparselocal_t() {
		Index   = 0;
		TokenID = 0;
		Flags   = 0;
	}
  };

  typedef CObPtrArray<obparselocal_t> CObParseLocalArray;

  struct obparseref_t {
	int        RefIndex;
	obformid_t FormID;	/* Used for SCRO */
	CSString   LocalRef;	/* Used for SCRV local 'ref' variables */
	int        LocalIndex;
  };

  typedef CObPtrArray<obparseref_t> CObParseRefArray;

	/* Used to parse and return results from an external variable reference */
  struct obextvarinfo_t {
	tokeninstance_t*  pRefToken;
	tokeninstance_t*  pRecordToken;
	tokeninstance_t*  pVarToken;
	CObRecord*        pRecord;
	CObScptRecord*	  pScript;
	CObSlsdSubrecord* pLocalData;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObFixedParser Definition
 *
 * Description
 *
 *=========================================================================*/
class CObFixedParser {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CTokenInstanceArray*	m_pTokens;
  int			m_CurrentToken;

  CSString		m_Scriptname;
  byte*			m_pOutputData;
  dword			m_OutputSize;
  dword			m_AllocatedOutputSize;
  dword			m_OpCount;

  CObParseLengthStack	m_OutputSizeStack;
  CObParseLengthStack	m_OutputSizeStack2;

  CTokenTypeArray*	m_pTokenTypes;
  CObRecordHandler*	m_pRecordHandler;
  CObScptRecord*	m_pScript;

  CObScriptFunction*	 m_pCurrentFunction;
  CRefTokenInstanceArray m_FunctionParams;
  int			 m_CurrentFuncParam;

  CObParseLocalArray	m_LocalVariables;
  CObParseRefArray	m_References;

  CRefTokenInstanceArray m_ExpressionStack;

  int			m_TokenUnknown;
  int			m_TokenLBracket;
  int			m_TokenRBracket;
  int			m_TokenAddOp;
  int			m_TokenMultOp;
  int			m_TokenRelOp;
  int			m_TokenBoolOp;
  int			m_TokenString;
  int			m_TokenIdentifier;
  int			m_TokenIf;
  int			m_TokenElseif;
  int			m_TokenElse;
  int			m_TokenEndif;
  int			m_TokenSet;
  int			m_TokenScriptname;
  int			m_TokenBegin;
  int			m_TokenEnd;
  int			m_TokenEndLine;
  int			m_TokenInteger;
  int			m_TokenFloat;
  int			m_TokenRef;
  int			m_TokenReturn;
  int			m_TokenComma;
  int			m_TokenVarShort;
  int			m_TokenVarLong;
  int			m_TokenVarFloat;
  int			m_TokenVarRef;
  int			m_TokenTo;
  int			m_TokenEndofProgram;

  obscripterrorinfo_t*	m_pErrorInfo;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Clear the output data array */
  void DestroyOutputData (void);
  void ClearParseData    (void);

	/* Error handling methods */
  int AddError (const int Code, tokeninstance_t* pToken, const char* pString, ...);

	/* References */
  word          AddReference       (const obformid_t FormID);
  word          AddLocalReference  (const char* pLocalRef, const int LocalIndex);
  obparseref_t* FindReference      (const obformid_t FormID);
  obparseref_t* FindLocalReference (const char* pLocalRef);
  int           FindReferenceIndex (word& RefIndex, tokeninstance_t* pRefToken, obscriptfuncparam_t* pFuncParam);

  const char* GetTokenString (const int TokenID);

  int ParseExternalVariable (obextvarinfo_t& ExtVarInfo, tokeninstance_t* pRecordToken);

	/* Parse routines */
  int DoMainProgram       (void);
  int DoScriptName        (void);
  int DoAddLocal          (const int LocalType);
  int DoBegin             (void);
  int DoBeginMode         (void);
  int DoStatements        (void);
  int DoStatement         (void);
  int DoFunctionParams    (void);
  int DoFunctionParam     (void);
  int DoCheckFunctionEnd  (void);
  int DoReturn            (void);
  int DoFunction          (void);
  int DoSet		  (void);
  int DoSetTo             (void);
  int DoSimpleExpression  (void);
  int DoFirstSimpleTerm   (void);
  int DoSimpleTerm        (void);
  int DoFirstSimpleFactor (void);
  int DoSimpleFactor      (void);
  int DoSimpleFactorID    (void);
  int DoElse              (void);
  int DoElseIf            (void);
  int DoIf                (void);

  int DoLocalGlobalOutput (tokeninstance_t* pVarToken);

  int DoSetRef  (tokeninstance_t* pRefToken);
  int DoSetCall (tokeninstance_t* pVarToken);

  int DoFunctionRef            (tokeninstance_t* pRefToken);
  int DoFunctionCall           (tokeninstance_t* pFuncToken, const bool IsRefCall = false);
  int DoExprFunction           (tokeninstance_t* pFuncToken);
  int DoExprRef                (tokeninstance_t* pRefToken);
  int DoVariableRef            (tokeninstance_t* pRefToken);
  int DoFunctionHelper         (CObScriptFunction* pFunction, tokeninstance_t* pFuncToken);
  int DoFunctionMessage        (CObScriptFunction* pFunction);
  int DoFunctionMessageBox     (CObScriptFunction* pFunction);
  int DoFunctionStopCombat     (CObScriptFunction* pFunction);
  int DoFunctionGetGameSetting (CObScriptFunction* pFunction);

  int CheckMessageVariables    (void);
  int IsValidMessageFormat     (CSString& Format, const char* pString, tokeninstance_t* pMsgToken);

  int DoFunctionParamInt         (obscriptfuncparam_t* pParam);
  int DoFunctionParamFloat       (obscriptfuncparam_t* pParam);
  int DoFunctionParamString      (obscriptfuncparam_t* pParam);
  int DoFunctionParamRecordID    (obscriptfuncparam_t* pParam);
  int DoFunctionParamRefRecord   (obscriptfuncparam_t* pParam);
  int DoFunctionParamAxis        (obscriptfuncparam_t* pParam);
  int DoFunctionParamSex         (obscriptfuncparam_t* pParam);
  int DoFunctionParamActorValue  (obscriptfuncparam_t* pParam);
  int DoFunctionParamAnimGroup   (obscriptfuncparam_t* pParam);
  int DoFunctionParamFormType    (obscriptfuncparam_t* pParam);
  int DoFunctionParamQuestStage  (obscriptfuncparam_t* pParam);
  int DoFunctionParamVarName     (obscriptfuncparam_t* pParam);
  int DoFunctionParamCrime       (obscriptfuncparam_t* pParam);
  int DoFunctionParamExtVar      (obscriptfuncparam_t* pParam, tokeninstance_t* pRefToken);

	/* Expression stack */
  void PushExpression   (tokeninstance_t* pToken);
  void PopExpressionsTo (const int TokenID);
  void PopExpressions   (const int TokenID);
  int  DoExprInteger    (void);
  int  DoExprFloat      (void);

	/* Find a previously defined local variable */
  int             FindLocalVariableIndex (const char* pString);
  obparselocal_t* FindLocalVariable      (const char* pString);

	/* Find a reference formid */
  CObIdRecord* FindRefRecord (const char* pEditorID);
  
	/* Are we at the end of the token stream? */
  bool IsEofToken (void) { return m_pTokens->IsValidIndex(m_CurrentToken); }

	/* Helper parse methods */
  tokeninstance_t* MatchToken      (const int TokenID, const char* pErrorString);
  tokeninstance_t* MatchToken      (const int TokenID);
  tokeninstance_t* LookAhead       (const int TokenID);
  void             PushBackToken   (void) { if (m_CurrentToken > 0) --m_CurrentToken; }
  tokeninstance_t* GetCurrentToken (void);

	/* Output script data */
  bool OutputData (const byte   Value);
  bool OutputData (const char   Value);
  bool OutputData (const word   Value);
  bool OutputData (const dword  Value);
  bool OutputData (const short  Value);
  bool OutputData (const int    Value);
  bool OutputData (const float  Value);
  bool OutputData (const double Value);
  bool OutputData (const byte* pValue, const dword Size);
  bool OutputData (const char* pValue, const dword Size) { return OutputData((const byte *)pValue, Size); }

	/* Push/pop byte and op length counters */
  obparselength_t* PushOutputSizeWord  (const dword Size, const bool UseSecondStack = false);
  int              PopOutputSizeWord   (const dword Size, const bool UseSecondStack = false);
  obparselength_t* PushOutputSizeDWord (const dword Size, const bool UseSecondStack = false);
  int              PopOutputSizeDWord  (const dword Size, const bool UseSecondStack = false);

	/* Find the current value of required tokens */
  bool ResolveTokenTypes (void);
  void ResetTokens       (void);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFixedParser();
  virtual ~CObFixedParser() { Destroy(); }
  virtual void Destroy (void);

	/* Get class members */
  byte*                GetOutputData     (void) { return (m_pOutputData); }
  dword                GetOutputDataSize (void) { return (m_OutputSize); }
  CObParseLocalArray&  GetLocalVarData   (void) { return (m_LocalVariables); }
  CObParseRefArray&    GetReferenceData  (void) { return (m_References); }
  int                  GetTokenVarRef    (void) { return (m_TokenVarRef); }

	/* Start the parse using the current values */
  bool Parse (void);

	/* Set class members */
  void SetTokens        (CTokenInstanceArray* pTokens) { m_pTokens        = pTokens; }
  void SetTokenTypes    (CTokenTypeArray*     pTokens) { m_pTokenTypes    = pTokens; }
  void SetRecordHandler (CObRecordHandler*   pHandler) { m_pRecordHandler = pHandler; }
  void SetScript        (CObScptRecord*       pScript) { m_pScript        = pScript; }
  void SetErrorInfo     (obscripterrorinfo_t* pInfo)   { m_pErrorInfo     = pInfo; }

};
/*===========================================================================
 *		End of Class CObFixedParser Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obfixedparser.H
 *=========================================================================*/
