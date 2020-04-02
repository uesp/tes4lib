/*===========================================================================
 *
 * File:	Obint64ubrec.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWordSubrecord used for storing a 64-bit integer.
 *
 *=========================================================================*/
#ifndef __OBINT64SUBREC_H
#define __OBIN64SUBREC_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObInt64Subrecord Definition
 *
 *=========================================================================*/
class CObInt64Subrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObInt64Subrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  int64	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(int64)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(int64)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObInt64Subrecord() { m_Value = 0; }
  //virtual ~CObInt64Subrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObInt64Subrecord* pSubrecord1 = ObCastClassNull(CObInt64Subrecord, pSubrecord);
	m_RecordSize = sizeof(int64);

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObInt64Subrecord); }

	/* Get class members */
  int64         GetValue    (void) { return (m_Value); }
  int64*        GetValuePtr (void) { return (&m_Value); }
  int64&        GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }
  
	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(int64); }

  	/* Set class methods */
  void SetValue (const int64 Value) { m_Value = Value; }
 
 };
/*===========================================================================
 *		End of Class CObInt64Subrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obint64subrec.H
 *=========================================================================*/
