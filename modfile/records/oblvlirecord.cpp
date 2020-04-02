/*===========================================================================
 *
 * File:	Oblvlirecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "oblvlirecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLvliRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLD, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLF, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_LVLO, CObLvloSubrecord::Create)
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
BEGIN_OBFIELDMAP(CObLvliRecord, CObIdRecord)
	ADD_OBFIELDALL("Chance None", OB_FIELD_CHANCENONE,		 0, CObLvliRecord, FieldChanceNone)
	ADD_OBFIELDALL("Calc All",    OB_FIELD_CALCULATEALL,		 0, CObLvliRecord, FieldCalculateAllLevels)
	ADD_OBFIELDALL("Calc Each",   OB_FIELD_CALCULATEEACH,		 0, CObLvliRecord, FieldCalculateEachItem)
	ADD_OBFIELDALL("Item List",   OB_FIELD_ITEMLIST,		 0, CObLvliRecord, FieldItemList)
	ADD_OBFIELDALL("Item Count",  OB_FIELD_ITEMCOUNT,	OBRF_NOCSV, CObLvliRecord, FieldItemCount)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Constructor
 *
 *=========================================================================*/
CObLvliRecord::CObLvliRecord () {
  m_pChanceNone = NULL;
  m_pFlags      = NULL;
  m_ItemCount   = 0;
}
/*===========================================================================
 *		End of Class CObLvliRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLvliRecord::Destroy (void) {
  m_pChanceNone = NULL;
  m_pFlags      = NULL;
  m_ItemCount   = 0;

  CObIdRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObLvliRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - CObLvloSubrecord* AddItem (FormID, Level, Count);
 *
 * Adds a new item to the levelled item list. Returns the new subrecord.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvliRecord::AddItem (const obformid_t FormID, const word Level, const word Count) {
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

  //++m_ItemCount;
  return (pNewSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObLvliRecord::AddItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - void ClearItems (void);
 *
 * Deletes all items in the levelled list.
 *
 *=========================================================================*/
void CObLvliRecord::ClearItems (void) {
  m_Subrecords.Delete(OB_NAME_LVLO);
  m_ItemCount = 0;
 }
/*===========================================================================
 *		End of Class Method CObLvliRecord::ClearItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - bool DeleteItem (pItem);
 *
 * Delete the specified item from the list. Returns true on success.
 *
 *=========================================================================*/
bool CObLvliRecord::DeleteItem (CObLvloSubrecord* pItem) {
  int Index;

  Index = m_Subrecords.Find(pItem);
  if (Index < 0) return (false);

  m_Subrecords.Delete(Index);
  --m_ItemCount;

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObLvliRecord::DeleteItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - CObLvloSubrecord* FindItem (ItemIndex);
 *
 * Finds and returns an effect based on its index. Returns NULL if
 * not found.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvliRecord::FindItem (const dword ItemIndex) {
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
 *		End of Class Method CObLvliRecord::FindItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - CObLvloSubrecord* GetFirstItem (ItemIndex);
 *
 * Finds and returns the first item in the list. Returns NULL if there are
 * no items in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvliRecord::GetFirstItem (int& Position) {
  Position = -1;
  return GetNextItem(Position);
 }
/*===========================================================================
 *		End of Class Method CObLvliRecord::FindItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - CObLvloSubrecord* GetNextItem (ItemIndex);
 *
 * Finds and returns the next item in the list. Returns NULL if there are
 * no more items in the list.
 *
 *=========================================================================*/
CObLvloSubrecord* CObLvliRecord::GetNextItem (int& Position) {
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
 *		End of Class Method CObLvliRecord::GetNextItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLvliRecord::InitializeNew (void) {

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
 *		End of Class Method CObLvliRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvliRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {
  static dword MaxCount = 0;

  if (pSubrecord->GetRecordType() == OB_NAME_LVLD) {
    m_pChanceNone = ObCastClass(CObByteSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pChanceNone->GetRecordSize(), 0x1, OB_NAME_LVLD);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLF) {
    m_pFlags = ObCastClass(CObByteSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pFlags->GetRecordSize(), 0x1, OB_NAME_LVLF);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 12, OB_NAME_LVLO);
    ++m_ItemCount;
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 12, OB_NAME_LVLO);
   
   }
  else
    CObIdRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObLvliRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLvliRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLvliRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pChanceNone == pSubrecord)
    m_pChanceNone = NULL;
  else if (m_pFlags == pSubrecord)
    m_pFlags = NULL;
  else if (pSubrecord->GetRecordType() == OB_NAME_LVLO && m_ItemCount > 0)
    --m_ItemCount;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObLvliRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvliRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObLvliRecord::GetFieldChanceNone,         String.Format("%u", (dword) GetChanceNone()))
DEFINE_OBGETFIELD(CObLvliRecord::GetFieldCalculateAllLevels, String.Format("%s", BooleanToString(IsCalculateAllLevels()) ))
DEFINE_OBGETFIELD(CObLvliRecord::GetFieldCalculateEachItem,  String.Format("%s", BooleanToString(IsCalculateEachItem()) ))
DEFINE_OBGETFIELD(CObLvliRecord::GetFieldItemList,           String.Format("N/A"))
DEFINE_OBGETFIELD(CObLvliRecord::GetFieldItemCount,          String.Format("%u", GetItemCount()))
/*===========================================================================
 *		End of CObLvliRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvliRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObLvliRecord, CompareFieldChanceNone, GetChanceNone)
DEFINE_OBCOMPFIELDINT(CObLvliRecord, CompareFieldCalculateAllLevels, IsCalculateAllLevels)
DEFINE_OBCOMPFIELDINT(CObLvliRecord, CompareFieldCalculateEachItem, IsCalculateEachItem)
DEFINE_OBCOMPFIELDDWORD(CObLvliRecord, CompareFieldItemCount, GetItemCount)

BEGIN_OBCOMPFIELD(CObLvliRecord::CompareFieldItemList)
	return (0);
END_OBCOMPFIELD()
/*===========================================================================
 *		End of CObLvliRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLvliRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObLvliRecord::SetFieldChanceNone)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetChanceNone(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvliRecord::SetFieldCalculateAllLevels)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateAllLevels(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvliRecord::SetFieldCalculateEachItem)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCalculateEachItem(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvliRecord::SetFieldItemList)
  AddObGeneralError("Setting a level item list from its set field is not yet implemented!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLvliRecord::SetFieldItemCount)
  AddObGeneralError("Cannot set the level item count its set field!");
  return (false);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObLvliRecord Set Field Methods
 *=========================================================================*/
