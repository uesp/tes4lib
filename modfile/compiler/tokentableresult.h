/*===========================================================================
 *
 * File:	Tokentableresult.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TOKENTABLERESULT_H
#define __TOKENTABLERESULT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentypearray.h"
  #include "charclassarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Action types */
  #define TOKEN_RESULT_NONE	 0	/* Unknown */
  #define TOKEN_RESULT_IGNORE	 1	/* Ignore token */
  #define TOKEN_RESULT_MOVETO	 2	/* Move to another table */
  #define TOKEN_RESULT_RETURN	 3	/* Return a token value */
  #define TOKEN_RESULT_ERROR	 4	/* Invalid character sequence */
  #define TOKEN_RESULT_CONTINUE	 5	/* Continue in same table */
  #define TOKEN_RESULT_JUMPTO	 6
  #define TOKEN_RESULT_JMPRETURN 7

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definitions */
  class CTokenTable;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenTableResult Definition
 *
 *=========================================================================*/
class CTokenTableResult {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  dword		m_Action;

  CSString	m_TableName;
  CTokenTable*	m_pTable;

  CSString	m_TokenName;
  CTokenType*	m_pToken;

  CSString	m_Message;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenTableResult();
  ~CTokenTableResult() { Destroy(); }
  void Destroy (void);

	/* Get class members */
  dword        GetAction    (void) { return (m_Action); }
  CTokenTable* GetTable     (void) { return (m_pTable); }
  CTokenType*  GetToken     (void) { return (m_pToken); }
  const char*  GetMessage   (void) { return (m_Message); }
  const char*  GetTokenName (void) { return (m_TokenName); }
  const char*  GetTableName (void) { return (m_TableName); }

  	/* Set a table result definition from a string */
  bool SetDefinition (const char* pString);

	/* Set class members */
  void SetTokenType (CTokenType*  pToken) { m_pToken = pToken; }
  void SetTable     (CTokenTable* pTable) { m_pTable = pTable; }

};
/*===========================================================================
 *		End of Class CTokenTableResult Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Tokentableresult.H
 *=========================================================================*/

