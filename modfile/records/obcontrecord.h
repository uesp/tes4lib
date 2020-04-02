/*===========================================================================
 *
 * File:	ObContRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObContRecord class for container records.
 *
 *=========================================================================*/
#ifndef __OBCONTRECORD_H
#define __OBCONTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obcntosubrecord.h"
  #include "../subrecords/obcontdatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObContRecord Definition
 *
 *=========================================================================*/
class CObContRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObContRecord, CObItem1Record)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObContDataSubrecord* m_pData;
  CObFormidSubrecord*	m_pOpenSound;
  CObFormidSubrecord*	m_pCloseSound;
  dword			m_ItemCount;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObContRecord();
  //virtual ~CObContRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Add a new item to the levelled list */
  CObCntoSubrecord* AddItem (const obformid_t FormID, const word Count);

	/* Delete all items in the levelled list */
  void ClearItems (void);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObContRecord; }

	/* Delete a specified item record */
  bool DeleteItem (CObCntoSubrecord* pItem);

	/* Find an item in the list based on its index */
  CObCntoSubrecord* FindItem (const dword ItemIndex);
  
	/* Iterate through the list items */
  CObCntoSubrecord* GetFirstItem (int& Position);
  CObCntoSubrecord* GetNextItem  (int& Position);

	/* Get class members */
  obformid_t GetOpenSound  (void) { return (m_pOpenSound ? m_pOpenSound->GetValue() : OB_FORMID_NULL); }
  obformid_t GetCloseSound (void) { return (m_pOpenSound ? m_pOpenSound->GetValue() : OB_FORMID_NULL); }
  float      GetWeight     (void) { return (m_pData ? m_pData->GetWeight() : 0); }
  dword      GetItemCount  (void) { return (m_ItemCount); }
  bool       IsRespawns    (void) { return (m_pData ? m_pData->IsRespawns() : false ); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetOpenSound  (const obformid_t FormID);
  void SetCloseSound (const obformid_t FormID);
  void SetWeight     (const float      Weight) { if (m_pData) m_pData->SetWeight(Weight); }
  void SetRespawns   (const bool       Flag)   { if (m_pData) m_pData->SetRespawns(Flag); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldCloseSound)
  DECLARE_OBFIELD(FieldOpenSound)
  DECLARE_OBFIELD(FieldCloseSoundID)
  DECLARE_OBFIELD(FieldOpenSoundID)
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldRespawns)
  DECLARE_OBFIELD(FieldItemCount)

};
/*===========================================================================
 *		End of Class CObContRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObBsgnRecord.H
 *=========================================================================*/
