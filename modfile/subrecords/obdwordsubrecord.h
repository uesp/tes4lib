/*===========================================================================
 *
 * File:	Obdwordsubrec.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWordSubrecord used for storing a 32-bit dword.
 *
 *=========================================================================*/
#ifndef __OBDWORDSUBREC_H
#define __OBDWORDSUBREC_H


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
 * Begin Class CObDwordSubrecord Definition
 *
 *=========================================================================*/
class CObDwordSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObDwordSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  dword	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(dword)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(dword)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObDwordSubrecord() { m_Value = 0; }
  //virtual ~CObDwordSubrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObDwordSubrecord* pSubrecord1 = ObCastClassNull(CObDwordSubrecord, pSubrecord);
	m_RecordSize = sizeof(dword);

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObDwordSubrecord); }

	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(dword); }

	/* Bit flag operations */
  bool  CheckFlag (const dword Mask)                  { return CheckFlagBits(m_Value, Mask); }
  void  ClearFlag (const dword Mask)		      { m_Value &= ~Mask; }
  dword FlipFlag  (const dword Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); } 
  void  SetFlag   (const dword Mask)		      { m_Value |= Mask; }

	/* Get class members */
  dword         GetValue    (void) { return (m_Value); }
  dword*        GetValuePtr (void) { return (&m_Value); }
  dword&        GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }

  	/* Set class methods */
  void SetValue (const dword Value) { m_Value = Value; }
 
 };

/*===========================================================================
 *		End of Class CObDwordSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obwordsubrec.H
 *=========================================================================*/
