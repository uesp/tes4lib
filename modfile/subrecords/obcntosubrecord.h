/*===========================================================================
 *
 * File:	Obcntosubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCNTOSUBRECORD_H
#define __OBCNTOSUBRECORD_H


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

	/* Standard CNTO subrecord size in bytes */
  #define OB_CNTO_SUBRECORD_SIZE 8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* LVLO data structure */
  struct obcntodata_t {
	obformid_t	FormID;
	dword		Count;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObCntoSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObCntoSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObCntoSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obcntodata_t	m_Data;
  obformid_t	m_OrigFormID;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { bool Result = File.Read(&m_Data, m_RecordSize); m_OrigFormID = m_Data.FormID; return (Result); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObCntoSubrecord() { }
  //virtual ~CObCntoSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.FormID == OldID) {
	  m_Data.FormID = NewID;
	  m_OrigFormID  = NewID;
	  return (1);
	}
	return (0); 
  }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObCntoSubrecord* pSubrecord1 = ObCastClassNull(CObCntoSubrecord, pSubrecord);
	m_RecordSize = OB_CNTO_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetItemData();
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
  static CObSubrecord* Create (void) { return (new CObCntoSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_OrigFormID, FixupArray);
  }

	/* Get class members */
  obcntodata_t& GetItemData   (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  obformid_t    GetFormID     (void) { return (m_Data.FormID); }
  obformid_t    GetOrigFormID (void) { return (m_OrigFormID); }
  dword         GetCount      (void) { return (m_Data.Count); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_CNTO_SUBRECORD_SIZE; }

	/* Set class members */
  void SetFormID     (const obformid_t Value) { m_Data.FormID = Value; }
  void SetOrigFormID (const obformid_t Value) { m_OrigFormID  = Value; }
  void SetCount      (const dword      Value) { m_Data.Count  = Value; }

 };
/*===========================================================================
 *		End of Class CObCntoSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obcntosubrecord.H
 *=========================================================================*/
