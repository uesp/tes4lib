/*===========================================================================
 *
 * File:	Oblvsprecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "oblvsprecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLvspRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLO, CObLvloSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLD, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLF, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObByteSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLvspRecord, CObIdRecord)
	ADD_OBFIELDALL("Chance None",  OB_FIELD_CHANCENONE,		 0, CObLvspRecord, FieldChanceNone)
	ADD_OBFIELDALL("Calc All",     OB_FIELD_CALCULATEALL,		 0, CObLvspRecord, FieldCalculateAllLevels)
	ADD_OBFIELDALL("Calc Each",    OB_FIELD_CALCULATEEACH,		 0, CObLvspRecord, FieldCalculateEachItem)
	ADD_OBFIELDALL("Use All",      OB_FIELD_USEALLSPELLS,		 0, CObLvspRecord, FieldUseAllSpells)
	ADD_OBFIELDALL("Spell List",   OB_FIELD_ITEMLIST,		 0, CObLvspRecord, FieldItemList)
	ADD_OBFIELDALL("Spell Count",  OB_FIELD_ITEMCOUNT,	OBRF_NOCSV, CObLvspRecord, FieldItemCount)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Constructor
 *
 *=========================================================================*/
CObLvspRecord::CObLvspRecord () {
  m_pChanceNone = NULL;
  m_pFlags      = NULL;
  m_SpellCount  = 0;
}
/*===========================================================================
 *		End of Class CObLvspRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLvspRecord::Destroy (void) {
  m_pChanceNone = NULL;
  m_pFlags      = NULL;
  m_SpellCount  = 0;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLvspRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - CObLvloSubrecord* AddSpell (FormID, Level, Count);
 *
 * Adds a new spell to the leveled list. Returns the new subrecord.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvspRecord::AddSpell (const obformid_t FormID, const word Level, const word Count) {
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
 *		End of Class Method CObLvspRecord::AddSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - void ClearSpells (void);
 *
 * Deletes all spells in the leveled list.
 *
 *=========================================================================*/
void CObLvspRecord::ClearSpells (void) {
  m_Subrecords.Delete(OB_NAME_LVLO);
  m_SpellCount = 0;
}
/*===========================================================================
 *		End of Class Method CObLvspRecord::ClearSpells()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - bool DeleteSpell (pSpell);
 *
 * Delete the specified spell from the list. Returns true on success.
 *
 *=========================================================================*/
bool CObLvspRecord::DeleteSpell (CObLvloSubrecord* pSpell) {
  int Index;

  Index = m_Subrecords.Find(pSpell);
  if (Index < 0) return (false);

  m_Subrecords.Delete(Index);
  --m_SpellCount;

  return (true);
}
/*===========================================================================
 *		End of Class Method CObLvspRecord::DeleteSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - CObLvloSubrecord* FindSpell (SpellIndex);
 *
 * Finds and returns a spell item based on its index. Returns NULL if
 * not found.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvspRecord::FindSpell (const dword SpellIndex) {
  CObSubrecord*     pSubrecord;
  CObLvloSubrecord* pLevo;
  dword		    Index;
  dword		    Count = 0;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];

    if (pSubrecord->GetRecordType() == OB_NAME_LVLO) {

      if (Count == SpellIndex) {
        pLevo = ObCastClass(CObLvloSubrecord, pSubrecord);
	return (pLevo);
       }

      ++Count;
     }
   }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObLvspRecord::FindSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - CObLvloSubrecord* GetFirstSpell (Position);
 *
 * Finds and returns the first spell in the list. Returns NULL if there are
 * no items in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvspRecord::GetFirstSpell (int& Position) {
  Position = -1;
  return GetNextSpell(Position);
 }
/*===========================================================================
 *		End of Class Method CObLvspRecord::GetFirstSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - CObLvloSubrecord* GetNextSpell (Position);
 *
 * Finds and returns the next spell in the list. Returns NULL if there are
 * no more spells in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvspRecord::GetNextSpell (int& Position) {
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
 *		End of Class Method CObLvspRecord::GetNextSpell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLvspRecord::InitializeNew (void) {

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
 *		End of Class Method CObLvspRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvspRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_LVLD) {
    m_pChanceNone = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLF) {
    m_pFlags = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO) {
     ++m_SpellCount;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObLvspRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvspRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvspRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pChanceNone == pSubrecord)
    m_pChanceNone = NULL;
  else if (m_pFlags == pSubrecord)
    m_pFlags = NULL;
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO && m_SpellCount > 0)
    --m_SpellCount;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObLvspRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvspRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldChanceNone,         String.Format("%u", (dword) GetChanceNone()))
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldCalculateAllLevels, String.Format("%s", BooleanToString(IsCalculateAllLevels()) ))
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldCalculateEachItem,  String.Format("%s", BooleanToString(IsCalculateEachItem()) ))
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldUseAllSpells,       String.Format("%s", BooleanToString(IsUseAllSpells()) ))
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldItemList,           String.Format("N/A"))
DEFINE_OBGETFIELD(CObLvspRecord::GetFieldItemCount,          String.Format("%u", GetSpellCount()))
/*===========================================================================
 *		End of CObLvspRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvspRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObLvspRecord, CompareFieldChanceNone, GetChanceNone)
DEFINE_OBCOMPFIELDINT(CObLvspRecord, CompareFieldCalculateAllLevels, IsCalculateAllLevels)
DEFINE_OBCOMPFIELDINT(CObLvspRecord, CompareFieldCalculateEachItem, IsCalculateEachItem)
DEFINE_OBCOMPFIELDINT(CObLvspRecord, CompareFieldUseAllSpells, IsUseAllSpells)
DEFINE_OBCOMPFIELDDWORD(CObLvspRecord, CompareFieldItemCount, GetSpellCount)

BEGIN_OBCOMPFIELD(CObLvspRecord::CompareFieldItemList)
	return (0);
END_OBCOMPFIELD()
/*===========================================================================
 *		End of CObLvspRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvspRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObLvspRecord::SetFieldChanceNone)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetChanceNone(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvspRecord::SetFieldCalculateAllLevels)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateAllLevels(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvspRecord::SetFieldCalculateEachItem)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateEachItem(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvspRecord::SetFieldUseAllSpells)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetUseAllSpells(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvspRecord::SetFieldItemList)
  AddObGeneralError("Setting a level spell list from its set field is not yet implemented!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvspRecord::SetFieldItemCount)
  AddObGeneralError("Cannot set the level spell count its set field!");
  return (false);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObLvspRecord Set Field Methods
 *=========================================================================*/
