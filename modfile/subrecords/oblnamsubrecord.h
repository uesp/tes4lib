/*===========================================================================
 *
 * File:	ObLnamsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLNAMSUBRECORD_H
#define __OBLNAMSUBRECORD_H


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
  #define OBLNAM_SUBRECORD_SIZE	12

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct oblnamdata_t {
	obformid_t  FormID1;
	obformid_t  FormID2;
	dword	    Unknown;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLnamSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObLnamSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObLnamSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  oblnamdata_t	m_Data;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { 
	memset(&m_Data, 0, sizeof(oblnamdata_t)); 
	bool Result = File.Read(&m_Data, m_RecordSize); 
	return (Result); }

  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObLnamSubrecord() { }
  //virtual ~CObLnamSubrecord() { Destroy(); }
  //virtual void Destroy (void);
  
  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	dword Count = 0;
	if (m_Data.FormID1 == OldID) {
	  m_Data.FormID1 = NewID;
	  ++Count;
	}

	if (m_Data.FormID2 == OldID) {
	  m_Data.FormID2 = NewID;
	  ++Count;
	}
	return (Count); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObLnamSubrecord* pSubrecord1 = ObCastClassNull(CObLnamSubrecord, pSubrecord);
	m_RecordSize = OBLNAM_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetLnamData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObLnamSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID1, m_Data.FormID1, FixupArray) & ObFixupFormid(m_Data.FormID2, m_Data.FormID2, FixupArray);
  }

	/* Get class members */
  oblnamdata_t& GetLnamData      (void) { return (m_Data); }
  virtual byte*	GetData          (void) { return (byte *)(&m_Data); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBLNAM_SUBRECORD_SIZE; }

	/* Set class members */
  
 };
/*===========================================================================
 *		End of Class CObLnamSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCreaSnamSubrecord.H
 *=========================================================================*/
