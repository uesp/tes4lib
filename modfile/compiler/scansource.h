/*===========================================================================
 *
 * File:	Scansource.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	August 28, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SCANSOURCE_H
#define __SCANSOURCE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/sstring.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Defines a location in the source */
  struct sourcepos_t {
	dword LinePos;
	dword CharPos;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CScanSource Definition
 *
 * Description
 *
 *=========================================================================*/
class CScanSource {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  sourcepos_t	m_Position;
  bool		m_IgnoreLineFeeds;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CScanSource() { m_IgnoreLineFeeds = false; m_Position.LinePos = 0; m_Position.CharPos = 0; }
  virtual ~CScanSource() { Destroy(); }
  virtual void Destroy (void) { m_Position.LinePos = 0; m_Position.CharPos = 0; }

	/* Get current location */
  virtual dword        GetCharPos   (void) { return (m_Position.CharPos); }
  virtual dword        GetLinePos   (void) { return (m_Position.LinePos); }
  virtual sourcepos_t& GetSourcePos (void) { return (m_Position); }

	/* Are we at the end of the source */
  virtual bool IsEOF (void) = 0;

	/* Access a character */
  virtual char LookAhead (void) = 0;
  virtual char GetChar   (void) = 0;
  //virtual void UnGetChar (void) = 0;

	/* Move the current location */
  virtual void MoveToStart (void) = 0;

};
/*===========================================================================
 *		End of Class CScanSource Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Scansource.H
 *=========================================================================*/
