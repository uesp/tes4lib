/*===========================================================================
 *
 * File:	Tokentype.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Implements the CTokenType class.
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentype.h"


/*===========================================================================
 *
 * Class CTokenType Constructor
 *
 *=========================================================================*/
CTokenType::CTokenType () {
  m_ID    = TOKEN_ID_UNKNOWN;
  m_Flags = 0;

  m_ForeColor = 0x000000;
  m_BackColor = 0xffffff;
}
/*===========================================================================
 *		End of Class CTokenType Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenType Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenType::Destroy (void) {
  m_Name.Empty();

  m_ID    = TOKEN_ID_UNKNOWN;
  m_Flags = 0;
}
/*===========================================================================
 *		End of Class Method CTokenType::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenType Method - bool SetDefinition (pString);
 *
 * Sets the token type definition from the given string values. Returns
 * false on any error.
 *
 * Expects the input string to have the format:
 *
 *	[id], [option1], [option2], ... [optionn]
 *
 *=========================================================================*/
bool CTokenType::SetDefinition (const char* pString) {
  char*  pNewString;
  char*  pParse;
  char*  pEndPtr;
  size_t Length;
  dword	 Count;

	/* Ignore invalid input */
  if (pString == NULL || *pString == NULL_CHAR) return (true);
  Length = strlen(pString);
  pNewString = new char[Length + 4];
  strcpy(pNewString, pString);

  pParse = strtok(pNewString, ",");
  Count  = 0;

  while (pParse != NULL) {
    pParse = trim(pParse);

		/* Parse the ID */
    if (Count == 0) {
      m_ID = strtoul(pParse, &pEndPtr, 0);
      if (*pEndPtr != NULL_CHAR) SystemLog.Printf("Possible invalid token ID string '%s'!", pParse);
    }
		/* Parse an option */
    else if (stricmp(pParse, "keep") == 0) {
      m_Flags |= TOKEN_FLAG_KEEP;
    }
    else if (stricmp(pParse, "simple") == 0) {
      m_Flags |= TOKEN_FLAG_SIMPLE;
    }
    else if (stricmp(pParse, "ignore") == 0) {
      m_Flags |= TOKEN_FLAG_IGNORE;
    }
    else if (stricmp(pParse, "trimfirst") == 0) {
      m_Flags |= TOKEN_FLAG_TRIMFIRST;
    }
    else if (stricmp(pParse, "trimlast") == 0) {
      m_Flags |= TOKEN_FLAG_TRIMLAST;
    }
    else if (stricmp(pParse, "endtoken") == 0) {
      m_Flags |= TOKEN_FLAG_ENDTOKEN;
    }

    pParse = strtok(NULL, ",");
    ++Count;
  }
  
  delete[] pNewString;
  return (true);
}
/*===========================================================================
 *		End of Class Method CTokenType::SetDefinition()
 *=========================================================================*/

