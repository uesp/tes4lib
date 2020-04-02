/*===========================================================================
 *
 * File:	ObAtxtsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBATXTSUBRECORD_H
#define __OBATXTSUBRECORD_H


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
 * Begin Definitions
 *
 *=========================================================================*/

	/* Standard subrecord size in bytes */
  #define OBATXT_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obatxtdata_t {
	obformid_t  FormID;
	dword	    Unknown;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObAtxtSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObAtxtSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObAtxtSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obatxtdata_t	m_Data;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { 
	memset(&m_Data, 0, sizeof(obatxtdata_t)); 
	bool Result = File.Read(&m_Data, m_RecordSize); 
	return (Result); }

  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAtxtSubrecord() { }
  //virtual ~CObAtxtSubrecord() { Destroy(); }
  //virtual void Destroy (void);
  
  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.FormID == OldID) {
	  m_Data.FormID = NewID;
	  return (1);
	}
	return (0); 
  }

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObAtxtSubrecord* pSubrecord1 = ObCastClassNull(CObAtxtSubrecord, pSubrecord);
	m_RecordSize = OBATXT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetAtxtData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Count uses of the given form */
  virtual dword CountUses (const obformid_t FormID) { 
	if (m_Data.FormID == FormID) return (1);
	return (0); 
  }
	
  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObAtxtSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_Data.FormID, FixupArray);
  }

	/* Get class members */
  obatxtdata_t&     GetAtxtData  (void) { return (m_Data); }
  virtual byte*	    GetData      (void) { return (byte *)(&m_Data); }
  obformid_t        GetFormID    (void) { return (m_Data.FormID); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBATXT_SUBRECORD_SIZE; }

	/* Set class members */
  void SetFormID  (const obformid_t Value) { m_Data.FormID = Value; }
  
 };
/*===========================================================================
 *		End of Class CObAtxtSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAtxtSubrecord.H
 *=========================================================================*/
