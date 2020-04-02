/*===========================================================================
 *
 * File:	Obfloatsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Defines the CObFloatSubrecord used for storing a 32-bit float.
 *
 *=========================================================================*/
#ifndef __OBFLOATSUBREC_H
#define __OBFLOATSUBREC_H


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
 * Begin Class CObFloatSubrecord Definition
 *
 *=========================================================================*/
class CObFloatSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObFloatSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  float	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Value, sizeof(float)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(float)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFloatSubrecord() { m_Value = 0; }
  //virtual ~CObFloatSubrecord() { Destroy(); }
  virtual void Destroy (void) { m_Value = 0; CObSubrecord::Destroy(); }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObFloatSubrecord* pSubrecord1 = ObCastClassNull(CObFloatSubrecord, pSubrecord);
	m_RecordSize = sizeof(float);

	if (pSubrecord1 != NULL) {
	  m_Value = pSubrecord1->GetValue();
	}
	else {
	  memset(&m_Value, 0, sizeof(m_Value));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObFloatSubrecord); }

	/* Get class members */
  float         GetValue    (void) { return (m_Value); }
  float*        GetValuePtr (void) { return (&m_Value); }
  float&        GetValueRef (void) { return (m_Value); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Value); }
  
	/* Initialize a new record */
  virtual void InitializeNew (void) { CObSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(float); }

  	/* Set class methods */
  void SetValue (const float Value) { m_Value = Value; }
 
 };
/*===========================================================================
 *		End of Class CObFloatSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obfloatsubrecord.H
 *=========================================================================*/
