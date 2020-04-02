/*===========================================================================
 *
 * File:	Tokentablerow.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TOKENTABLEROW_H
#define __TOKENTABLEROW_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentableresult.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Types of matches */
  #define TOKEN_MATCHTYPE_NONE		0
  #define TOKEN_MATCHTYPE_CHARCLASS	1
  #define TOKEN_MATCHTYPE_CHAR		2
  #define TOKEN_MATCHTYPE_STRING	3

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenTableRow Definition
 *
 *=========================================================================*/
class CTokenTableRow {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  dword			m_MatchType;

  CSString		m_CharClassName;
  CCharClass*		m_pCharClass;

  char			m_MatchChar;
  CSString		m_MatchString;

  CTokenTableResult	m_Result;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenTableRow();
  ~CTokenTableRow() { Destroy(); }
  void Destroy (void);

	/* Check if the current row matches the current input */
  bool DoesMatch (const char* pTokenString, const char TokenChar);

	/* Get class members */
  dword		     GetMatchType     (void) { return (m_MatchType); }
  CCharClass*	     GetCharClass     (void) { return (m_pCharClass); }
  const char*	     GetCharClassName (void) { return (m_CharClassName); }
  CTokenTableResult& GetResult        (void) { return (m_Result); }

	/* Set the row definition from a string value */
  bool SetDefinition (const char* pString, const char* pResult);

	/* Set class members */
  void SetCharClass (CCharClass *pClass) { m_pCharClass = pClass; }

};
/*===========================================================================
 *		End of Class CTokenTableRow Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Tokentablerow.H
 *=========================================================================*/
