/*===========================================================================
 *
 * File:	ObEffItemRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obeffitemrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObEffectItemRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_EFID, CObEfidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_EFIT, CObEfitSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCIT, CObScitSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObEffectItemRecord, CObItem1Record)
	ADD_OBFIELDMAP("Effect Count", OB_FIELD_EFFECTCOUNT, OBRF_NOCSV, &CObEffectItemRecord::GetFieldEffectCount,	NULL,	&CObEffectItemRecord::CompareFieldEffectCount)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Constructor
 *
 *=========================================================================*/
CObEffectItemRecord::CObEffectItemRecord () {
  m_EffectCount = 0;
 }
/*===========================================================================
 *		End of Class CObEffectItemRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEffectItemRecord::Destroy (void) {
  m_EffectCount = 0;

  CObItem1Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObNameSubrecord* AddEffect (EffectID);
 *
 * Adds a new effect to the enchantment using the given magical effect
 * ID. Returns the new EFID subrecord which identifies the effect.
 *
 *=========================================================================*/
CObEfidSubrecord* CObEffectItemRecord::AddEffect (const obrectype_t EffectID) {
  CObEfitSubrecord* pEfitSubrecord;
  CObEfidSubrecord* pEfidSubrecord;
  CObSubrecord*     pNewSubrecord;

	/* Create the two new subrecords */
  pNewSubrecord  = AddNewSubrecord(OB_NAME_EFID);
  pEfidSubrecord = ObCastClass(CObEfidSubrecord, pNewSubrecord);
  pNewSubrecord  = AddNewSubrecord(OB_NAME_EFIT);
  pEfitSubrecord = ObCastClass(CObEfitSubrecord, pNewSubrecord);
  if (pEfidSubrecord == NULL || pEfitSubrecord == NULL) return (NULL);
  
	/* Initialize the new subrecords */
  pEfidSubrecord->InitializeNew();
  pEfitSubrecord->InitializeNew();
  pEfidSubrecord->SetDataName(EffectID);
  pEfitSubrecord->SetEffectName(EffectID);

  	/* More records are needed for a script effect */
  if (EffectID == OB_MGEF_SEFF) {
    CObScitSubrecord*   pScitSubrecord;
    CObStringSubrecord* pFullSubrecord;

    pNewSubrecord  = AddNewSubrecord(OB_NAME_SCIT);
    pScitSubrecord = ObCastClass(CObScitSubrecord, pNewSubrecord);
    pNewSubrecord  = AddNewSubrecord(OB_NAME_FULL);
    pFullSubrecord = ObCastClass(CObStringSubrecord, pNewSubrecord);
    if (pScitSubrecord == NULL || pFullSubrecord == NULL) return (NULL);
  
    pScitSubrecord->InitializeNew();
    pFullSubrecord->InitializeNew();
   }

  //++m_EffectCount;
  return (pEfidSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::AddEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - dword CopyEffects (pSource);
 *
 * Copy all effects from the given source record. Returns the number copied.
 *
 *=========================================================================*/
dword CObEffectItemRecord::CopyEffects (CObEffectItemRecord* pSource) {
  CObEfidSubrecord*     pEffect;
  CObEfitSubrecord*     pEfit;
  CObScitSubrecord*     pScit;
  CObFullSubrecord*     pFull;
  CObSubrecord*         pNewSubrecord;
  dword			Count = 0;
  int                   ItemPos;
  
  if (pSource == NULL) return (0);

  for (pEffect = pSource->GetFirstEffect(ItemPos); pEffect != NULL; pEffect = pSource->GetNextEffect(ItemPos)) {
    pEfit = pSource->GetEffectData(pEffect);
    pScit = pSource->GetScriptEffectData(pEffect);
    pFull = pSource->GetScriptEffectNameData(pEffect);

    if (pEfit == NULL) continue;
    
    pNewSubrecord  = AddNewSubrecord(OB_NAME_EFID);
    pNewSubrecord->Copy(pEffect);

    pNewSubrecord  = AddNewSubrecord(OB_NAME_EFIT);
    pNewSubrecord->Copy(pEfit);
    ++Count;

    if (pScit != NULL && pFull != NULL) {
      pNewSubrecord  = AddNewSubrecord(OB_NAME_SCIT);
      pNewSubrecord->Copy(pScit);

      pNewSubrecord  = AddNewSubrecord(OB_NAME_FULL);
      pNewSubrecord->Copy(pFull);
    }
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::CopyEffects()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - bool DeleteEffect (pEffect);
 *
 * Delete the specified effect data from the enchantment.
 *
 *=========================================================================*/
bool CObEffectItemRecord::DeleteEffect (CObEfidSubrecord* pEffect) {
  CObSubrecord* pSubrecord;
  int           Index;

	/* Find the effect in the record */
  Index = m_Subrecords.Find(pEffect);
  if (Index < 0) return (false);

	/* Check for subsequent effects */
  pSubrecord = GetSubrecord(pEffect, 3, OB_NAME_FULL);
  if (pSubrecord != NULL) m_Subrecords.Delete(Index + 3);
  
  pSubrecord = GetSubrecord(pEffect, 2, OB_NAME_SCIT);
  if (pSubrecord != NULL) m_Subrecords.Delete(Index + 2);

  pSubrecord = GetSubrecord(pEffect, 1, OB_NAME_EFIT);
  if (pSubrecord != NULL) m_Subrecords.Delete(Index + 1);

  m_Subrecords.Delete(Index);
     
  --m_EffectCount;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::DeleteEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - void DeleteAllEffects (void);
 *
 * Deletes all the effect data from the enchantment.
 *
 *=========================================================================*/
void CObEffectItemRecord::DeleteAllEffects (void) {
  CObSubrecord* pSubrecord;
  int           Index;

	/* Iterate in reverse order since we may be deleting subrecords */
  for (Index = m_Subrecords.GetSize() - 1; Index >= 0; --Index) {
    pSubrecord = m_Subrecords[Index];

		/* Delete any effect subrecord */
    if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
      if (pSubrecord != m_pItemName) m_Subrecords.Delete(Index);	 
     }
    else if (pSubrecord->GetRecordType() == OB_NAME_EFIT || pSubrecord->GetRecordType() == OB_NAME_SCIT || 
        pSubrecord->GetRecordType() == OB_NAME_EFID) {
      m_Subrecords.Delete(Index);	 
     }
   }

  m_EffectCount = 0;
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::DeleteAllEffects()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObEfidSubrecord* FindEffect (EffectIndex);
 *
 * Finds and returns an effect based on its index. Returns NULL if
 * not found.
 *
 *=========================================================================*/
CObEfidSubrecord* CObEffectItemRecord::FindEffect (const dword EffectIndex) {
  CObSubrecord*     pSubrecord;
  CObEfidSubrecord* pEfid;
  dword		    Index;
  dword		    Count = 0;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];

    if (pSubrecord->GetRecordType() == OB_NAME_EFID) {

      if (Count == EffectIndex) {
        pEfid = ObCastClass(CObEfidSubrecord, pSubrecord);
	return (pEfid);
       }

      ++Count;
     }
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::FindEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObEfidSubrecord* GetFirstEffect (ItemIndex);
 *
 * Finds and returns the first effect in the record. Returns NULL if there are
 * no effects.
 *
 *=========================================================================*/
CObEfidSubrecord* CObEffectItemRecord::GetFirstEffect (int& Position) {
  Position = -1;
  return GetNextEffect(Position);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::GetFirstEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObEfidSubrecord* GetNextEffect (ItemIndex);
 *
 * Finds and returns the next effect in the record. Returns NULL if there are
 * no more effects.
 *
 *=========================================================================*/
CObEfidSubrecord* CObEffectItemRecord::GetNextEffect (int& Position) {
  CObSubrecord*     pSubrecord;
  CObEfidSubrecord* pEffect;
  dword		    Index;

  ++Position;
  if (Position < 0) Position = 0;

  for (Index = (dword) Position; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    if (pSubrecord->GetRecordType() != OB_NAME_EFID) continue;

    pEffect = ObCastClass(CObEfidSubrecord, pSubrecord);
    if (pEffect == NULL) continue;

    Position = Index;
    return (pEffect);
   }
  
  Position = Index + 1;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::GetNextEffect()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObEfitSubrecord* GetEffectData (pEffect);
 *
 * Gets effect data based on the first EFID subrecord. Returns NULL
 * if the given effect was not found in the effect data.
 *
 *=========================================================================*/
CObEfitSubrecord* CObEffectItemRecord::GetEffectData (CObEfidSubrecord* pEffect) {
  CObEfitSubrecord* pEfitSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 1, OB_NAME_EFIT);
  if (pSubrecord == NULL) return (NULL);
  pEfitSubrecord = ObCastClass(CObEfitSubrecord, pSubrecord);
  if (pEfitSubrecord == NULL) return (NULL);
  
  return (pEfitSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::GetEffectData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObScitSubrecord* GetScriptEffectData (pEffect);
 *
 * Gets script effect data based on the first EFID subrecord. Returns
 * NULL if the given effect was not found in the effect data.
 *
 *=========================================================================*/
CObScitSubrecord* CObEffectItemRecord::GetScriptEffectData (CObEfidSubrecord* pEffect) {
  CObScitSubrecord* pScitSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 2, OB_NAME_SCIT);
  if (pSubrecord == NULL) return (NULL);
  pScitSubrecord = ObCastClass(CObScitSubrecord, pSubrecord);
  if (pScitSubrecord == NULL) return (NULL);

  return (pScitSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::GetScriptEffectData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - const SSCHAR* GetScriptEffectName (pEffect);
 *
 * Gets the script effect name based on the first EFID subrecord. Returns
 * NULL if the given effect was not found in the effect data.
 *
 *=========================================================================*/
const SSCHAR* CObEffectItemRecord::GetScriptEffectName (CObEfidSubrecord* pEffect) {
  CObFullSubrecord* pFullSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 3, OB_NAME_FULL);
  if (pSubrecord == NULL) return (NULL);
  pFullSubrecord = ObCastClass(CObFullSubrecord, pSubrecord);
  if (pFullSubrecord == NULL) return (NULL);

  return ((const SSCHAR *)pFullSubrecord->GetString().c_str());
 }
/*===========================================================================
 *		End of Class Method SSCHAR* CObEffectItemRecord::GetScriptEffectName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - CObFullSubrecord* GetScriptEffectNameData (pEffect);
 *
 * Gets the script effect name based on the first EFID subrecord. Returns
 * NULL if the given effect was not found in the effect data.
 *
 *=========================================================================*/
CObFullSubrecord* CObEffectItemRecord::GetScriptEffectNameData (CObEfidSubrecord* pEffect) {
  CObFullSubrecord* pFullSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 3, OB_NAME_FULL);
  if (pSubrecord == NULL) return (NULL);
  pFullSubrecord = ObCastClass(CObFullSubrecord, pSubrecord);
  
  return (pFullSubrecord);
 }
/*===========================================================================
 *		End of Class Method SSCHAR* GetScriptEffectNameData::GetScriptEffectName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - void InitializeNew (void);
 *
 * Initialize a new enchantment record.
 *
 *=========================================================================*/
void CObEffectItemRecord::InitializeNew (void) {

  CObItem1Record::InitializeNew();
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObEffectItemRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_SCIT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 16, OB_NAME_SCIT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_EFID) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_EFID);
    ++m_EffectCount;
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_EFIT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 24, OB_NAME_EFIT);
   }
	/* Need to intercept this subrecord as it has multiple meanings for this record type */
  else if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    if (m_pItemName == NULL && HasFullItemName()) {
      m_pItemName = ObCastClass(CObFullSubrecord, pSubrecord);
     }
   }
  else
    CObItem1Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObEffectItemRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObEffectItemRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pItemName == pSubrecord) {
    m_pItemName = NULL;
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_EFID) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_EFID);
    --m_EffectCount;
   }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObEffectItemRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - 
 *
 *	bool SetEffectData (pEffect, Type, Magnitude, Area, Duration, ActorValue);
 *
 * Sets data of a specific effect as given by its EFID subrecord. Returns
 * false on any error (such as effect not found in record).
 *
 *=========================================================================*/
bool CObEffectItemRecord::SetEffectData (CObEfidSubrecord* pEffect, const dword Type, 
				   const dword Magnitude, const dword Area, 
				   const dword Duration, const dword ActorValue) {
  CObEfitSubrecord* pEfitSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 1, OB_NAME_EFIT);
  if (pSubrecord == NULL) return (false);
  pEfitSubrecord = ObCastClass(CObEfitSubrecord, pSubrecord);
  if (pEfitSubrecord == NULL) return (false);

  pEfitSubrecord->SetMagnitude(Magnitude);
  pEfitSubrecord->SetArea(Area);
  pEfitSubrecord->SetDuration(Duration);
  pEfitSubrecord->SetEffectType(Type);
  pEfitSubrecord->SetActorValue(ActorValue);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::SetEffectData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - 
 *
 *	bool SetScriptEffectData (pEffect, ScriptFormID, School, VisualEffect, Hostile);
 *
 * Description
 *
 *=========================================================================*/
bool CObEffectItemRecord::SetScriptEffectData (CObEfidSubrecord* pEffect, const obformid_t ScriptFormID, 
					 const dword School, const obrectype_t VisualEffect, 
					 const bool Hostile) {
  CObScitSubrecord* pScitSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 2, OB_NAME_SCIT);

  if (pSubrecord == NULL) { 
    pSubrecord = CreateSubrecord(OB_NAME_SCIT);
    if (pSubrecord == NULL) return (false);
    pSubrecord->InitializeNew();
    m_Subrecords.InsertAfter(pSubrecord, pEffect, 1);
  }
  
  pScitSubrecord = ObCastClass(CObScitSubrecord, pSubrecord);
  if (pScitSubrecord == NULL) return (false);

  pScitSubrecord->SetHostile(Hostile);
  pScitSubrecord->SetScriptFormID(ScriptFormID);
  pScitSubrecord->SetSchool(School);
  pScitSubrecord->SetVisualEffect(VisualEffect);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::SetScriptEffectData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEffectItemRecord Method - bool SetScriptEffectName (pEffect, pString);
 *
 * Sets the custom name of the given script effect. Returns false if
 * the effect was not found or is invalid.
 *
 *=========================================================================*/
bool CObEffectItemRecord::SetScriptEffectName (CObEfidSubrecord* pEffect, const SSCHAR* pString) {
  CObFullSubrecord* pFullSubrecord;
  CObSubrecord*     pSubrecord;

  pSubrecord = GetSubrecord(pEffect, 3, OB_NAME_FULL);

  if (pSubrecord == NULL) { 
    pSubrecord = CreateSubrecord(OB_NAME_FULL);
    if (pSubrecord == NULL) return (false);
    pSubrecord->InitializeNew();
    m_Subrecords.InsertAfter(pSubrecord, pEffect, 2);
  }

  pFullSubrecord = ObCastClass(CObFullSubrecord, pSubrecord);
  if (pFullSubrecord == NULL) return (false);

  pFullSubrecord->SetString(pString);
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObEffectItemRecord::SetScriptEffectName()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObEffectItemRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObEffectItemRecord::GetFieldEffectCount, String.Format("%u", m_EffectCount))
/*===========================================================================
 *		End of CObRecord Get Field Methods
 *=========================================================================*/

 
/*===========================================================================
 *
 * Begin CObEffectItemRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObEffectItemRecord, CompareFieldEffectCount, GetEffectCount)
/*===========================================================================
 *		End of CObEffectItemRecord Compare Field Methods
 *=========================================================================*/

