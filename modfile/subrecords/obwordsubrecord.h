/*===========================================================================
 *
 * File:	Obwordsubrec.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWordSubrecord used for storing a 16-bit word.
 *
 *=========================================================================*/
#ifndef __OBWORDSUBREC_H
#define __OBWORDSUBREC_H


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
 * Begin Class CObWordSubrecord Definition
 *
 *=========================================================================*/
class CObWordSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObWordSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  word	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(word)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(word)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObWordSubrecord() { m_Value = 0; }
  //virtual ~CObWordSubrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObWordSubrecord* pSubrecord1 = ObCastClassNull(CObWordSubrecord, pSubrecord);
	m_RecordSize = sizeof(word);

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObWordSubrecord); }

  	/* Bit flag operations */
  bool CheckFlag (const word Mask) { return CheckFlagBits(m_Value, Mask); }
  word FlipFlag  (const word Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); } 

	/* Get class members */
  word          GetValue    (void) { return (m_Value); }
  word*         GetValuePtr (void) { return (&m_Value); }
  word&         GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }

	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(word); }

  	/* Set class methods */
  void SetValue (const word Value) { m_Value = Value; }
 
 };
/*===========================================================================
 *		End of Class CObWordSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obwordsubrec.H
 *=========================================================================*/
