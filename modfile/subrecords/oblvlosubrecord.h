/*===========================================================================
 *
 * File:	Oblvlosubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLVLOSUBRECORD_H
#define __OBLVLOSUBRECORD_H


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

	/* Standard LEVO subrecord size in bytes */
  #define OB_LVLO_SUBRECORD_SIZE	12

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
  struct oblvlodata_t {
	word		Level;
	word		Unknown1;
	obformid_t	FormID;
	word		Count;
	word		Unknown2;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLvloSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObLvloSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObLvloSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  oblvlodata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { memset(&m_Data, 0, sizeof(m_Data)); return File.Read(&m_Data, m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLvloSubrecord() { }
  //virtual ~CObLvloSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.FormID == OldID) {
	  m_Data.FormID     = NewID;
	  return (1);
	}
	return (0);
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObLvloSubrecord* pSubrecord1 = ObCastClassNull(CObLvloSubrecord, pSubrecord);
	m_RecordSize = OB_LVLO_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetItemData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObLvloSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_Data.FormID, FixupArray);
  }

	/* Get class members */
  oblvlodata_t& GetItemData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  word          GetLevel     (void) { return (m_Data.Level); }
  obformid_t    GetFormID    (void) { return (m_Data.FormID); }
  word          GetCount     (void) { return (m_Data.Count); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_LVLO_SUBRECORD_SIZE; }

	/* Set class members */
  void SetLevel  (const word       Value) { m_Data.Level  = Value; }
  void SetFormID (const obformid_t Value) { m_Data.FormID = Value; }
  void SetCount  (const word       Value) { m_Data.Count  = Value; }

 };
/*===========================================================================
 *		End of Class CObLvloSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oblvlosubrecord.H
 *=========================================================================*/
