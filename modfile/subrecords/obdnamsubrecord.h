/*===========================================================================
 *
 * File:	ObDnamsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBDNAMSUBRECORD_H
#define __OBDNAMSUBRECORD_H


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
  #define OBDNAM_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obdnamdata_t {
	obformid_t  FormID1;
	obformid_t  FormID2;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObDnamSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObDnamSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObDnamSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obdnamdata_t	m_Data;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data, OBDNAM_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObDnamSubrecord() { }
  //virtual ~CObDnamSubrecord() { Destroy(); }
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
	CObDnamSubrecord* pSubrecord1 = ObCastClassNull(CObDnamSubrecord, pSubrecord);
	m_RecordSize = OBDNAM_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetDnamData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }
  
	/* Count uses of the given form */
  virtual dword CountUses (const obformid_t FormID) { 
	dword Count = 0;
	if (m_Data.FormID1 == FormID) ++Count;
	if (m_Data.FormID2 == FormID) ++Count;
	return (Count); 
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObDnamSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID1, m_Data.FormID1, FixupArray) && ObFixupFormid(m_Data.FormID2, m_Data.FormID2, FixupArray);
  }

	/* Get class members */
  obdnamdata_t&     GetDnamData      (void) { return (m_Data); }
  virtual byte*	    GetData          (void) { return (byte *)(&m_Data); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBDNAM_SUBRECORD_SIZE; }

	/* Set class members */
  
 };
/*===========================================================================
 *		End of Class CObDnamSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCreaSnamSubrecord.H
 *=========================================================================*/
