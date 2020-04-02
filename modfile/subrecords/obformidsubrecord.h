/*===========================================================================
 *
 * File:	Obformidsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObFormidSubrecord used for storing a 32-bit formid.
 *
 *=========================================================================*/
#ifndef __OBFORMIDSUBREC_H
#define __OBFORMIDSUBREC_H


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
 * Begin Class CObFormidSubrecord Definition
 *
 *=========================================================================*/
class CObFormidSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObFormidSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obformid_t	m_Value;
  obformid_t	m_OrigValue;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { 
	bool Result = File.Read(&m_Value, sizeof(dword)); 
	m_OrigValue = m_Value; 
	return (Result);
  }

  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(dword)); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFormidSubrecord() { 
	m_Value     = 0; 
	m_OrigValue = 0; 
  }

  virtual void Destroy (void) { 
	m_Value     = 0; 
	m_OrigValue = 0; 
	CObSubrecord::Destroy();
  }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Value == OldID) {
	  m_Value     = NewID;
	  m_OrigValue = NewID;
	  return (1);
	}
	return (0); 
  }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObFormidSubrecord* pSubrecord1 = ObCastClassNull(CObFormidSubrecord, pSubrecord);
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
  static CObSubrecord* Create (void) { return (new CObFormidSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Value, m_OrigValue, FixupArray);
  }

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();  
	m_Value      = 0; 
	m_OrigValue  = 0; 
	m_RecordSize = sizeof(dword); 
  }

	/* Get class members */
  obformid_t    GetValue     (void) { return (m_Value); }
  obformid_t    GetOrigValue (void) { return (m_Value); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Value); }

  	/* Set class methods */
  void SetValue     (const obformid_t Value) { m_Value     = Value; }
  void SetOrigValue (const obformid_t Value) { m_OrigValue = Value; }
 
};
/*===========================================================================
 *		End of Class CObFormidSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFormidsubrec.H
 *=========================================================================*/
