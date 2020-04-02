/*===========================================================================
 *
 * File:	Tokentablerow.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentablerow.h"


/*===========================================================================
 *
 * Class CTokenTableRow Constructor
 *
 *=========================================================================*/
CTokenTableRow::CTokenTableRow() {
  m_MatchType  = TOKEN_MATCHTYPE_NONE;
  m_pCharClass = NULL;
  m_MatchChar  = 0;
}
/*===========================================================================
 *		End of Class CTokenTableRow Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableRow Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenTableRow::Destroy (void) {
  m_MatchType  = TOKEN_MATCHTYPE_NONE;
  m_pCharClass = NULL;
  m_MatchChar  = 0;

  m_CharClassName.Empty();
  m_MatchString.Empty();
  m_Result.Destroy();
}
/*===========================================================================
 *		End of Class Method CTokenTableRow::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableRow Method - bool DoesMatch (pTokenString, TokenChar);
 *
 *=========================================================================*/
bool CTokenTableRow::DoesMatch (const char* pTokenString, const char TokenChar) {

  switch (m_MatchType) {
    case TOKEN_MATCHTYPE_CHAR:
	return m_MatchChar == TokenChar;
    case TOKEN_MATCHTYPE_CHARCLASS:
	if (m_pCharClass == NULL) return (false);
        return m_pCharClass->DoesMatch(TokenChar);
    case TOKEN_MATCHTYPE_STRING:
	return m_MatchString.CompareNoCase(pTokenString) == 0;
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CTokenTableRow::DoesMatch()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableRow Method - bool SetDefinition (pString, pResult);
 *
 *=========================================================================*/
bool CTokenTableRow::SetDefinition (const char* pString, const char* pResult) {
  char*  pNewString = NULL;
  size_t Length = 0;

	/* Set the row condition if present */
  if (pString != NULL && *pString != NULL_CHAR) {
    Length = strlen(pString);
    pNewString = new char[Length + 4];
    strcpy(pNewString, pString);
    pNewString = trim(pNewString);
    Length = strlen(pNewString);

		/* Check for a string value */
    if (*pNewString == '"') {
      m_MatchType = TOKEN_MATCHTYPE_STRING;
      m_MatchString.Copy(pNewString + 1, (int)Length - 2);
    }
		/* Check for a character value */
    else if (Length == 1) {
      m_MatchType = TOKEN_MATCHTYPE_CHAR;
      m_MatchChar = *pNewString;
    }
		/* Must be a character class */
    else {
      m_MatchType     = TOKEN_MATCHTYPE_CHARCLASS;
      m_CharClassName = pNewString;
    }

    delete[] pNewString;
  }
  
  return m_Result.SetDefinition(pResult);
}
/*===========================================================================
 *		End of Class Method CTokenTableRow::SetDefinition()
 *=========================================================================*/


