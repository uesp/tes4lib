/*===========================================================================
 *
 * File:	Obbytesubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObByteSubrecord used for storing a 8-bit byte.
 *
 *=========================================================================*/
#ifndef __OBBYTESUBRECORD_H
#define __OBBYTESUBRECORD_H


/*===========================================================================
 *
 * Begin Reqiured Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Reqiured Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObByteSubrecord Definition
 *
 *=========================================================================*/
class CObByteSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObByteSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  byte	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(byte)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(byte)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObByteSubrecord() { m_Value = 0; }
  //virtual ~CObByteSubrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObByteSubrecord* pSubrecord1 = ObCastClassNull(CObByteSubrecord, pSubrecord);
	m_RecordSize = 1;

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObByteSubrecord); }

  	/* Bit flag operations */
  bool CheckFlag (const byte Mask)                  { return CheckFlagBits(m_Value, Mask); }
  word FlipFlag  (const byte Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); } 

	/* Get class members */
  byte          GetValue    (void) { return (m_Value); }
  byte*         GetValuePtr (void) { return (&m_Value); }
  byte&         GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }
  
	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(byte); }

  	/* Set class methods */
  void SetValue (const byte Value) { m_Value = Value; }
 
 };
/*===========================================================================
 *		End of Class CObByteSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbytesubrec.H
 *=========================================================================*/
