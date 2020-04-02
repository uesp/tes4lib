/*===========================================================================
 *
 * File:	ObContRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	10 September, 2006
 *
 * Implements the CObContRecord class for container records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obcontrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObContRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObContDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_QNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MODL, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DESC, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNTO, CObCntoSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MODT, CObDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MODB, CObDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObContRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObContRecord, CObItem1Record)
	ADD_OBFIELDALL("Weight",        OB_FIELD_WEIGHT,       0, CObContRecord, FieldWeight)
	ADD_OBFIELDALL("Respawns",      OB_FIELD_RESPAWNS,     0, CObContRecord, FieldRespawns)
	ADD_OBFIELDALL("Open Sound",    OB_FIELD_OPENSOUND,    0, CObContRecord, FieldOpenSound)
	ADD_OBFIELDALL("Open SoundID",  OB_FIELD_OPENSOUNDID,  0, CObContRecord, FieldOpenSoundID)
	ADD_OBFIELDALL("Close Sound",   OB_FIELD_CLOSESOUND,   0, CObContRecord, FieldCloseSound)
	ADD_OBFIELDALL("Close SoundID", OB_FIELD_CLOSESOUNDID, 0, CObContRecord, FieldCloseSoundID)
	ADD_OBFIELDALL("Item Count",    OB_FIELD_ITEMCOUNT,    OBRF_NOCSV, CObContRecord, FieldItemCount)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObContRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Constructor
 *
 *=========================================================================*/
CObContRecord::CObContRecord () {
  m_pOpenSound  = NULL;
  m_pCloseSound = NULL;
  m_pData       = NULL;
  m_ItemCount   = 0;
}
/*===========================================================================
 *		End of Class CObContRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObContRecord::Destroy (void) {
  m_pOpenSound  = NULL;
  m_pCloseSound = NULL;
  m_pData       = NULL;
  m_ItemCount   = 0;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObContRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - CObCntoSubrecord* AddItem (FormID, Count);
 *
 * Adds a new item to the item list. Returns the new subrecord.
 *
 *=========================================================================*/
CObCntoSubrecord* CObContRecord::AddItem (const obformid_t FormID, const word Count) {
  CObCntoSubrecord* pNewSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = AddNewSubrecord(OB_NAME_CNTO);
  if (pSubrecord == NULL) return (NULL);
  pNewSubrecord = ObCastClass(CObCntoSubrecord, pSubrecord);
  if (pNewSubrecord == NULL) return (NULL);

  pNewSubrecord->InitializeNew();

  pNewSubrecord->SetCount(Count);
  pNewSubrecord->SetFormID(FormID);

  return (pNewSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObContRecord::AddItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - void ClearItems (void);
 *
 * Deletes all items in the container.
 *
 *=========================================================================*/
void CObContRecord::ClearItems (void) {
  m_Subrecords.Delete(OB_NAME_CNTO);
  m_ItemCount = 0;
}
/*===========================================================================
 *		End of Class Method CObContRecord::ClearItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - bool DeleteItem (pItem);
 *
 * Delete the specified item from the list. Returns true on success.
 *
 *=========================================================================*/
bool CObContRecord::DeleteItem (CObCntoSubrecord* pItem) {
  int Index;

  Index = m_Subrecords.Find(pItem);
  if (Index < 0) return (false);

  m_Subrecords.Delete(Index);
  --m_ItemCount;

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObContRecord::DeleteItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - CObCntoSubrecord* FindItem (ItemIndex);
 *
 * Finds and returns an effect based on its index. Returns NULL if
 * not found.
 *
 *=========================================================================*/
CObCntoSubrecord* CObContRecord::FindItem (const dword ItemIndex) {
  CObSubrecord*     pSubrecord;
  CObCntoSubrecord* pCnto;
  dword		    Index;
  dword		    Count = 0;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];

    if (pSubrecord->GetRecordType() == OB_NAME_CNTO) {

      if (Count == ItemIndex) {
        pCnto = ObCastClass(CObCntoSubrecord, pSubrecord);
	return (pCnto);
       }

      ++Count;
     }
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObContRecord::FindItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - CObCntoSubrecord* GetFirstItem (ItemIndex);
 *
 * Finds and returns the first item in the container. Returns NULL if there 
 * are no items in the container.
 *
 *=========================================================================*/
CObCntoSubrecord* CObContRecord::GetFirstItem (int& Position) {
  Position = -1;
  return GetNextItem(Position);
 }
/*===========================================================================
 *		End of Class Method CObContRecord::FindItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - CObCntoSubrecord* GetNextItem (ItemIndex);
 *
 * Finds and returns the next item in the container. Returns NULL if 
 * there are no more items left.
 *
 *=========================================================================*/
CObCntoSubrecord* CObContRecord::GetNextItem (int& Position) {
  CObSubrecord*     pSubrecord;
  CObCntoSubrecord* pCnto;
  dword		    Index;

  ++Position;
  if (Position < 0) Position = 0;

  for (Index = (dword) Position; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    if (pSubrecord->GetRecordType() != OB_NAME_CNTO) continue;

    pCnto = ObCastClass(CObCntoSubrecord, pSubrecord);
    if (pCnto == NULL) continue;

    Position = Index;
    return (pCnto);
   }
  
  Position = Index + 1;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObContRecord::GetNextItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObContRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pData != NULL) m_pData->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObContRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObContRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_QNAM) {
    m_pCloseSound = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SNAM) {
    m_pOpenSound = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_CNTO) {
    ++m_ItemCount;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pData = ObCastClass(CObContDataSubrecord, pSubrecord);
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObContRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObContRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_QNAM) {
    m_pCloseSound = NULL;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SNAM) {
    m_pOpenSound = NULL;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_CNTO) {
    --m_ItemCount;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pData = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObContRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - void SetOpenSound (FormID);
 *
 *=========================================================================*/
void CObContRecord::SetOpenSound (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL) {
    DeleteSubrecords(OB_NAME_SNAM);
    return;
  }

  if (m_pOpenSound == NULL) {
     AddNewSubrecord(OB_NAME_SNAM);
     if (m_pOpenSound == NULL) return;
     m_pOpenSound->InitializeNew();
   }

  m_pOpenSound->SetValue(FormID);
}
/*===========================================================================
 *		End of Class Method CObContRecord::SetOpenSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObContRecord Method - void SetCloseSound (FormID);
 *
 *=========================================================================*/
void CObContRecord::SetCloseSound (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL) {
    DeleteSubrecords(OB_NAME_QNAM);
    return;
  }

  if (m_pCloseSound == NULL) {
     AddNewSubrecord(OB_NAME_QNAM);
     if (m_pCloseSound == NULL) return;
     m_pCloseSound->InitializeNew();
   }

  m_pCloseSound->SetValue(FormID);
}
/*===========================================================================
 *		End of Class Method CObContRecord::SetCloseSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObContRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObContRecord::GetFieldWeight,   String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObContRecord::GetFieldRespawns,   String.Format("%s", BooleanToString(IsRespawns())))
DEFINE_OBGETFIELD(CObContRecord::GetFieldOpenSoundID,  GetOpenSound()  ? String.Format("0x%08X", GetOpenSound())  : String.Empty())
DEFINE_OBGETFIELD(CObContRecord::GetFieldCloseSoundID, GetCloseSound() ? String.Format("0x%08X", GetCloseSound()) : String.Empty())
DEFINE_OBGETFIELD(CObContRecord::GetFieldItemCount, String.Format("%u", GetItemCount()))

BEGIN_OBGETFIELD(CObContRecord::GetFieldOpenSound)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetOpenSound());
        String.Format("0x%08X", GetOpenSound());
END_OBGETFIELD()

BEGIN_OBGETFIELD(CObContRecord::GetFieldCloseSound)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetCloseSound());
        String.Format("0x%08X", GetCloseSound());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObContRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObContRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObContRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObContRecord, CompareFieldRespawns, IsRespawns)
DEFINE_OBCOMPFIELDEDITORID(CObContRecord, CompareFieldOpenSound, GetOpenSound)
DEFINE_OBCOMPFIELDEDITORID(CObContRecord, CompareFieldCloseSound, GetCloseSound)
DEFINE_OBCOMPFIELDDWORD(CObContRecord, CompareFieldOpenSoundID, GetCloseSound)
DEFINE_OBCOMPFIELDDWORD(CObContRecord, CompareFieldCloseSoundID, GetCloseSound)
DEFINE_OBCOMPFIELDDWORD(CObContRecord, CompareFieldItemCount, GetItemCount)
/*===========================================================================
 *		End of CObContRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObContRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObContRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldRespawns)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetRespawns(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldCloseSoundID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetCloseSound(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldOpenSoundID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetOpenSound(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldCloseSound)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetCloseSound(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The sound '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SOUN) return AddObGeneralError("The record '%s' is not a sound (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetCloseSound(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the sound '%s'!", pString);
  }

END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldOpenSound)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetOpenSound(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The sound '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SOUN) return AddObGeneralError("The record '%s' is not a sound (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetOpenSound(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the sound '%s'!", pString);
  }

END_OBSETFIELD()


BEGIN_OBSETFIELD(CObContRecord::SetFieldItemCount)
  AddObGeneralError("Cannot set the container item count its set field!");
  return (false);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObContRecord Set Field Methods
 *=========================================================================*/
