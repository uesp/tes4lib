/*===========================================================================
 *
 * File:	Tokentableresult.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentableresult.h"


/*===========================================================================
 *
 * Class CTokenTableResult Constructor
 *
 *=========================================================================*/
CTokenTableResult::CTokenTableResult() {
  m_Action = TOKEN_RESULT_NONE;

  m_pTable = NULL;
  m_pToken = NULL;

}
/*===========================================================================
 *		End of Class CTokenTableResult Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableResult Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenTableResult::Destroy (void) {

  m_Action = TOKEN_RESULT_NONE;

  m_pTable = NULL;
  m_pToken = NULL;

  m_TableName.Empty();
  m_TokenName.Empty();
  m_Message.Empty();
}
/*===========================================================================
 *		End of Class Method CTokenTableResult::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableResult Method - bool SetDefinition (pString);
 *
 * Sets the table result definition from the given string. Returns false
 * on any error.
 *
 * Expects an input string with the format:
 *
 *	return [TokenType]
 *	moveto [TableName]
 *	error [MessageString]
 *	continue
 *	ignore
 *
 *=========================================================================*/
bool CTokenTableResult::SetDefinition (const char* pString) {

	/* Clear the current result definition */
  Destroy();

	/* Ignore invalid input */
  if (pString == NULL || *pString == NULL_CHAR) return (true);

  if (strnicmp(pString, "return ", 7) == 0) {
    m_Action    = TOKEN_RESULT_RETURN;
    m_TokenName = pString + 7;
  }
  else if (strnicmp(pString, "jmpreturn ", 10) == 0) {
    m_Action    = TOKEN_RESULT_JMPRETURN;
    m_TokenName = pString + 10;
  }
  else if (strnicmp(pString, "moveto ", 7) == 0) {
    m_Action    = TOKEN_RESULT_MOVETO;
    m_TableName = pString + 7;
  }
  else if (strnicmp(pString, "jumpto ", 7) == 0) {
    m_Action    = TOKEN_RESULT_JUMPTO;
    m_TableName = pString + 7;
  }
  else if (strnicmp(pString, "ignore", 6) == 0) {
    m_Action = TOKEN_RESULT_IGNORE;
  }
  else if (strnicmp(pString, "error ", 6) == 0) {
    m_Action  = TOKEN_RESULT_ERROR;
    m_Message = pString + 6;
  }
  else if (strnicmp(pString, "continue", 8) == 0) {
    m_Action = TOKEN_RESULT_CONTINUE;
  }
  else {
    AddObGeneralError("Unknown token result definition '%s'!", pString);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CTokenTableResult::SetDefinition()
 *=========================================================================*/

