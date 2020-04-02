/*===========================================================================
 *
 * File:	Scansourcestring.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	August 28, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __SCANSOURCESTRING_H
#define __SCANSOURCESTRING_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "scansource.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CScanSourceString Definition
 *
 * Description
 *
 *=========================================================================*/
class CScanSourceString : public CScanSource {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CSString	m_Buffer;
  int		m_CurrentPos;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CScanSourceString();
  virtual void Destroy (void);

	/* Get class members */
  const char* GetString (void) { return m_Buffer; }

  	/* Are we at the end of the source */
  virtual bool IsEOF (void);

	/* Access a character */
  virtual char LookAhead (void);
  virtual char GetChar   (void);

	/* Move the current location */
  virtual void MoveToStart (void);

	/* Set class members */
  void SetString (const char* pString) { m_Buffer = pString; }

};
/*===========================================================================
 *		End of Class CScanSourceString Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Scansourcestring.H
 *=========================================================================*/
