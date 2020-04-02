/*===========================================================================
 *
 * File:	Obidledatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBIDLEDATASUBRECORD_H
#define __OBIDLEDATASUBRECORD_H


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

  #define OB_IDLEDATA_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obidledata_t {
	obformid_t FormID1;
	obformid_t FormID2;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObIdleDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObIdleDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObIdleDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obidledata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_IDLEDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_IDLEDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObIdleDataSubrecord() { }
  //virtual ~CObIdleDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }
  
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
	CObIdleDataSubrecord* pSubrecord1 = ObCastClassNull(CObIdleDataSubrecord, pSubrecord);
	m_RecordSize = OB_IDLEDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetIdleData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObIdleDataSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID1, m_Data.FormID1, FixupArray) && ObFixupFormid(m_Data.FormID2, m_Data.FormID2, FixupArray);
  }

	/* Get class members */
  obidledata_t& GetIdleData   (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  obformid_t    GetFormID1    (void) { return (m_Data.FormID1); }
  obformid_t    GetFormID2    (void) { return (m_Data.FormID2); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_IDLEDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetFormID1 (const obformid_t Value)   { m_Data.FormID1 = Value; }
  void SetFormID2 (const obformid_t Value)   { m_Data.FormID2 = Value; }
  
 };
/*===========================================================================
 *		End of Class CObIdleDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obidledatasubrecord.H
 *=========================================================================*/
