/*===========================================================================
 *
 * File:	Scansourcestring.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	August 28, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "scansourcestring.h"


/*===========================================================================
 *
 * Class CScanSourceString Constructor
 *
 *=========================================================================*/
CScanSourceString::CScanSourceString () {
  m_CurrentPos = 0;
}
/*===========================================================================
 *		End of Class CScanSourceString Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CScanSourceString Method - void Destroy (void);
 *
 *=========================================================================*/
void CScanSourceString::Destroy (void) {
  m_Buffer.Empty();
  m_CurrentPos = 0;
  
  CScanSource::Destroy();
}
/*===========================================================================
 *		End of Class Method CScanSourceString::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CScanSourceString Method - char GetChar (void);
 *
 *=========================================================================*/
char CScanSourceString::GetChar (void) {
  char Char;

  if (IsEOF()) return (0);

	/* Ignore any \r characters if required */
  if (m_IgnoreLineFeeds) {
    do {
      Char = m_Buffer.GetAt(m_CurrentPos);
      ++m_CurrentPos;
    } while (Char == '\r' && m_CurrentPos < m_Buffer.GetLength());
  }
  else {
    if (m_CurrentPos >= m_Buffer.GetLength()) {
      Char = 0;
    }
    else {
      Char = m_Buffer.GetAt(m_CurrentPos);
    }
    ++m_CurrentPos;
  }

  if (Char == '\n') {
    ++m_Position.LinePos;
    m_Position.CharPos = 0;
  }
  else {
    ++m_Position.CharPos;
  }

  return Char;
}
/*===========================================================================
 *		End of Class Method CScanSourceString::GetChar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CScanSourceString Method - bool IsEOF (void);
 *
 *=========================================================================*/
bool CScanSourceString::IsEOF (void) {
  return (m_CurrentPos > m_Buffer.GetLength());
}
/*===========================================================================
 *		End of Class Method CScanSourceString::IsEOF()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CScanSourceString Method - char LookAhead (void);
 *
 *=========================================================================*/
char CScanSourceString::LookAhead (void) {

  if (m_CurrentPos + 1 >=  m_Buffer.GetLength()) return (0);

  return m_Buffer.GetAt(m_CurrentPos + 1);
}
/*===========================================================================
 *		End of Class Method CScanSourceString::LookAhead()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CScanSourceString Method - void MoveToStart (void);
 *
 *=========================================================================*/
void CScanSourceString::MoveToStart (void) {
  m_CurrentPos          = 0;  
  m_Position.LinePos    = 0;
  m_Position.CharPos    = 0;
}
/*===========================================================================
 *		End of Class Method CScanSourceString::MoveToStart()
 *=========================================================================*/
