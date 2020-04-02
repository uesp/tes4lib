/*===========================================================================
 *
 * File:	Oblvlcrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "oblvlcrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLvlcRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLO, CObLvloSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRI, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_TNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLD, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLF, CObByteSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLvlcRecord, CObIdRecord)
	ADD_OBFIELDALL("Chance None", OB_FIELD_CHANCENONE,		 0, CObLvlcRecord, FieldChanceNone)
	ADD_OBFIELDALL("Calc All",    OB_FIELD_CALCULATEALL,		 0, CObLvlcRecord, FieldCalculateAllLevels)
	ADD_OBFIELDALL("Calc Each",   OB_FIELD_CALCULATEEACH,		 0, CObLvlcRecord, FieldCalculateEachItem)
	ADD_OBFIELDALL("Script",      OB_FIELD_SCRIPT,		         0, CObLvlcRecord, FieldScript)
	ADD_OBFIELDALL("ScriptID",    OB_FIELD_SCRIPTID,		 0, CObLvlcRecord, FieldScriptID)
	ADD_OBFIELDALL("Template",    OB_FIELD_TEMPLATE,	         0, CObLvlcRecord, FieldTemplate)
	ADD_OBFIELDALL("TemplateID",  OB_FIELD_TEMPLATEID,		 0, CObLvlcRecord, FieldTemplateID)
	ADD_OBFIELDALL("Item List",   OB_FIELD_ITEMLIST,		 0, CObLvlcRecord, FieldItemList)
	ADD_OBFIELDALL("Item Count",  OB_FIELD_ITEMCOUNT,	OBRF_NOCSV, CObLvlcRecord, FieldItemCount)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Constructor
 *
 *=========================================================================*/
CObLvlcRecord::CObLvlcRecord () {
  m_pChanceNone   = NULL;
  m_pFlags        = NULL;
  m_pScript       = NULL;
  m_pTemplate     = NULL;
  m_CreatureCount = 0;
}
/*===========================================================================
 *		End of Class CObLvlcRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLvlcRecord::Destroy (void) {
  m_pChanceNone   = NULL;
  m_pFlags        = NULL;
  m_pScript       = NULL;
  m_pTemplate     = NULL;
  m_CreatureCount = 0;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - CObLvloSubrecord* AddCreature (FormID, Level, Count);
 *
 * Adds a new creature to the leveled item list. Returns the new subrecord.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvlcRecord::AddCreature (const obformid_t FormID, const word Level, const word Count) {
  CObLvloSubrecord* pNewSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = AddNewSubrecord(OB_NAME_LVLO);
  if (pSubrecord == NULL) return (NULL);
  pNewSubrecord = ObCastClass(CObLvloSubrecord, pSubrecord);
  if (pNewSubrecord == NULL) return (NULL);

  pNewSubrecord->InitializeNew();

  pNewSubrecord->SetCount(Count);
  pNewSubrecord->SetLevel(Level);
  pNewSubrecord->SetFormID(FormID);

  return (pNewSubrecord);
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::AddCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - void ClearCreatures (void);
 *
 * Deletes all creatures in the levelled list.
 *
 *=========================================================================*/
void CObLvlcRecord::ClearCreatures (void) {
  m_Subrecords.Delete(OB_NAME_LVLO);
  m_CreatureCount = 0;
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::ClearCreatures()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - bool DeleteCreature (pItem);
 *
 * Delete the specified creature from the list. Returns true on success.
 *
 *=========================================================================*/
bool CObLvlcRecord::DeleteCreature (CObLvloSubrecord* pCreature) {
  int Index;

  Index = m_Subrecords.Find(pCreature);
  if (Index < 0) return (false);

  m_Subrecords.Delete(Index);
  --m_CreatureCount;

  return (true);
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::DeleteCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - CObLvloSubrecord* FindCreature (ItemIndex);
 *
 * Finds and returns a creature based on its index. Returns NULL if
 * not found.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvlcRecord::FindCreature (const dword ItemIndex) {
  CObSubrecord*     pSubrecord;
  CObLvloSubrecord* pLevo;
  dword		    Index;
  dword		    Count = 0;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];

    if (pSubrecord->GetRecordType() == OB_NAME_LVLO) {

      if (Count == ItemIndex) {
        pLevo = ObCastClass(CObLvloSubrecord, pSubrecord);
	return (pLevo);
      }

      ++Count;
    }
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::FindCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - CObLvloSubrecord* GetFirstCreature (Position);
 *
 * Finds and returns the first creature in the list. Returns NULL if there are
 * no items in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvlcRecord::GetFirstCreature (int& Position) {
  Position = -1;
  return GetNextCreature(Position);
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::GetFirstCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - CObLvloSubrecord* GetNextCreature (Position);
 *
 * Finds and returns the next creature in the list. Returns NULL if there are
 * no more items in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvlcRecord::GetNextCreature (int& Position) {
  CObSubrecord*     pSubrecord;
  CObLvloSubrecord* pLvlo;
  dword		    Index;

  ++Position;
  if (Position < 0) Position = 0;

  for (Index = (dword) Position; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    if (pSubrecord->GetRecordType() != OB_NAME_LVLO) continue;

    pLvlo = ObCastClass(CObLvloSubrecord, pSubrecord);
    if (pLvlo == NULL) continue;

    Position = Index;
    return (pLvlo);
   }
  
  Position = Index + 1;
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::GetNextCreature()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLvlcRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  	/* Create and intialize the chance none subrecord */
  AddNewSubrecord(OB_NAME_LVLD);
  if (m_pChanceNone != NULL) m_pChanceNone->InitializeNew();

	/* Create and intialize the flags subrecord */
  AddNewSubrecord(OB_NAME_LVLF);
  if (m_pFlags != NULL) m_pFlags->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObLvlcRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvlcRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_LVLD) {
    m_pChanceNone = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLF) {
    m_pFlags = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCRI) {
    m_pScript = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_TNAM) {
    m_pTemplate = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO) {
    ++m_CreatureCount;
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObLvlcRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvlcRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pChanceNone == pSubrecord)
    m_pChanceNone = NULL;
  else if (m_pFlags == pSubrecord)
    m_pFlags = NULL;
  else if (m_pScript == pSubrecord)
    m_pScript = NULL;
  else if (m_pTemplate == pSubrecord)
    m_pTemplate = NULL;
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO && m_CreatureCount > 0)
    --m_CreatureCount;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObLvlcRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - void SetMarkerScript (FormID);
 *
 *=========================================================================*/
void CObLvlcRecord::SetMarkerScript (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL && m_pScript != NULL) {
    DeleteSubrecords(OB_NAME_SCRI);
    return;
  }

  if (m_pScript == NULL) {
     AddNewSubrecord(OB_NAME_SCRI);
     if (m_pScript == NULL) return;
     m_pScript->InitializeNew();
   }

  m_pScript->SetValue(FormID);
 }
/*===========================================================================
 *		End of Class Method CObLvlcRecord::SetMarkerScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvlcRecord Method - void SetCreatureTemplate (FormID);
 *
 *=========================================================================*/
void CObLvlcRecord::SetCreatureTemplate (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL && m_pTemplate != NULL) {
    DeleteSubrecords(OB_NAME_TNAM);
    return;
  }

  if (m_pTemplate == NULL) {
     AddNewSubrecord(OB_NAME_TNAM);
     if (m_pTemplate == NULL) return;
     m_pTemplate->InitializeNew();
   }

  m_pTemplate->SetValue(FormID);
 }
/*===========================================================================
 *		End of Class Method CObLvlcRecord::SetCreatureTemplate()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvlcRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldChanceNone,         String.Format("%u", (dword) GetChanceNone()))
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldCalculateAllLevels, String.Format("%s", BooleanToString(IsCalculateAllLevels()) ))
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldCalculateEachItem,  String.Format("%s", BooleanToString(IsCalculateEachItem()) ))
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldItemList,           String.Format("N/A"))
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldItemCount,          String.Format("%u", GetCreatureCount()))
DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldScriptID, GetMarkerScript() ? String.Format("0x%08X", GetMarkerScript()) : String.Empty())

BEGIN_OBGETFIELD(CObLvlcRecord::GetFieldScript)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetMarkerScript());
        String.Format("0x%08X", GetMarkerScript());
END_OBGETFIELD()

DEFINE_OBGETFIELD(CObLvlcRecord::GetFieldTemplateID, GetCreatureTemplate() ? String.Format("0x%08X", GetCreatureTemplate()) : String.Empty())

BEGIN_OBGETFIELD(CObLvlcRecord::GetFieldTemplate)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetCreatureTemplate());
        String.Format("0x%08X", GetCreatureTemplate());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObLvlcRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvlcRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObLvlcRecord, CompareFieldChanceNone, GetChanceNone)
DEFINE_OBCOMPFIELDINT(CObLvlcRecord, CompareFieldCalculateAllLevels, IsCalculateAllLevels)
DEFINE_OBCOMPFIELDINT(CObLvlcRecord, CompareFieldCalculateEachItem, IsCalculateEachItem)
DEFINE_OBCOMPFIELDDWORD(CObLvlcRecord, CompareFieldItemCount, GetCreatureCount)

BEGIN_OBCOMPFIELD(CObLvlcRecord::CompareFieldItemList)
	return (0);
END_OBCOMPFIELD()


DEFINE_OBCOMPFIELDEDITORID(CObLvlcRecord, CompareFieldScript, GetMarkerScript)
DEFINE_OBCOMPFIELDDWORD(CObLvlcRecord, CompareFieldScriptID, GetMarkerScript)

DEFINE_OBCOMPFIELDEDITORID(CObLvlcRecord, CompareFieldTemplate, GetCreatureTemplate)
DEFINE_OBCOMPFIELDDWORD(CObLvlcRecord, CompareFieldTemplateID, GetCreatureTemplate)
/*===========================================================================
 *		End of CObLvlcRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvlcRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldChanceNone)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetChanceNone(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldCalculateAllLevels)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateAllLevels(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldCalculateEachItem)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateEachItem(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldItemList)
  AddObGeneralError("Setting a level creature list from its set field is not yet implemented!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldItemCount)
  AddObGeneralError("Cannot set the level creature count its set field!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldScriptID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetMarkerScript(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldScript)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetMarkerScript(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The script '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SCPT) return AddObGeneralError("The record '%s' is not a script (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetMarkerScript(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the script '%s'!", pString);
  }

END_OBSETFIELD()



BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldTemplateID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetCreatureTemplate(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvlcRecord::SetFieldTemplate)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetCreatureTemplate(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The creature '%s' does not exist!", pString);
    //if (pIdRecord->GetRecordType() != OB_NAME_SCPT) return AddObGeneralError("The record '%s' is not a script (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetCreatureTemplate(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the script '%s'!", pString);
  }

END_OBSETFIELD()
/*===========================================================================
 *		End of CObLvlcRecord Set Field Methods
 *=========================================================================*/
