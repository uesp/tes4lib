/*===========================================================================
 *
 * File:	ObScroSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObScroSubrecord used for storing a 32-bit formid.
 *
 *=========================================================================*/
#ifndef __OBSCROSUBRECORD_H
#define __OBSCROSUBRECORD_H


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
 * Begin Definitions
 *
 *=========================================================================*/
   
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScroSubrecord Definition
 *
 *=========================================================================*/
class CObScroSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObScroSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obformid_t	m_Value;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData (CObFile& File) {  return File.Read(&m_Value, sizeof(dword)); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Value, sizeof(dword));  }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScroSubrecord() { 
	m_Value      = 0; 
  }

  virtual void Destroy (void) { 
	m_Value      = 0;
	CObSubrecord::Destroy();
  }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Value == OldID) {
	  m_Value     = NewID;
	  return (1);
	}
	return (0); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObScroSubrecord* pSubrecord1 = ObCastClassNull(CObScroSubrecord, pSubrecord);
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
  static CObSubrecord* Create (void) { return (new CObScroSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Value, m_Value, FixupArray);
  }

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();  
	m_Value      = 0; 
	m_RecordSize = sizeof(dword); 
  }

	/* Get class members */
  obformid_t    GetValue     (void) { return (m_Value); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Value); }

  	/* Set class methods */
  void SetValue     (const obformid_t Value) { m_Value     = Value; }
 
};
/*===========================================================================
 *		End of Class CObScroSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObScroSubrecord.h
 *=========================================================================*/
