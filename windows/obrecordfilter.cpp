/*===========================================================================
 *
 * File:	Obrecordfilter.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 27, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrecordfilter.h"


/*===========================================================================
 *
 * Class CObRecordFilter Constructor
 *
 *=========================================================================*/
CObRecordFilter::CObRecordFilter () {
 
  m_pParent      = NULL;

  m_FilterMask   = 0;
  m_Flags        = 0;
  m_BipedCompare = OB_RECFILTER_BIPED_EQUAL;
  m_BipedParts   = 0;
  m_WeaponType   = 0;
  m_ArmorType    = 0;
  m_UserData     = 0;
  m_EnchantType  = 0;
  m_ScriptType   = 0;
  m_SpellType    = 0;
  m_SpellLevel   = 0;
  m_RecordCount  = 0;
 }
/*===========================================================================
 *		End of Class CObRecordFilter Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRecordFilter::Destroy (void) {

  m_ID.Empty();
  m_Material.Empty();
  m_NameFilter.Empty();
  m_ParentName.Empty();
  m_DisplayName.Empty();

  m_FieldFilters.Destroy();

  m_RecordType   = OB_NAME_NULL;
  m_FilterMask   = 0;
  m_Flags        = 0;
  m_BipedCompare = OB_RECFILTER_BIPED_EQUAL;
  m_BipedParts   = 0;
  m_WeaponType   = 0;
  m_ArmorType    = 0;
  m_UserData     = 0;
  m_EnchantType  = 0;
  m_ScriptType   = 0;
  m_SpellType    = 0;
  m_SpellLevel   = 0;
  m_RecordCount  = 0;
}
/*===========================================================================
 *		End of Class Method CObRecordFilter::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - bool CheckRecord (pRecord);
 *
 * Checks if the given record matches the filter. Returns true if it does.
 *
 *=========================================================================*/
bool CObRecordFilter::CheckRecord (CObRecord* pRecord) {
  CObItem1Record* pItem1;
  CObWeapRecord*  pWeapon;
  CObArmoRecord*  pArmor;
  CObClotRecord*  pClothing;
  CObScptRecord*  pScript;
  CObEnchRecord*  pEnchant;
  CObSpelRecord*  pSpell;
  dword		  BipedFlags;
  bool		  Result;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);
  if (IsFlagEmpty())   return (false);

	/* Do the record types match? */
  if (IsMaskRecordType()) {
    if (pRecord->GetRecordType() != m_RecordType) return (false);
   }

	/* Do the item names match? */
  if (IsMaskItemName()) {
    pItem1 = ObCastClass(CObItem1Record, pRecord);
    if (pItem1 == NULL) return (false);
    if (strnicmp(m_NameFilter, pItem1->GetItemName(), m_NameFilter.GetLength()) != 0) return (false);
   }

	/* Do the materials names match? */
  if (IsMaskMaterial()) {
    pItem1 = ObCastClass(CObItem1Record, pRecord);
    if (pItem1 == NULL) return (false);

    if (stristr(pItem1->GetItemName(), m_Material) == NULL) {
      if (stristr(m_NameFilter, pItem1->GetModel()) == NULL) return (false);
     }
   }

	/* Do the weapon types match? */
  if (IsMaskWeaponType()) {
    pWeapon = ObCastClass(CObWeapRecord, pRecord);
    if (pWeapon == NULL) return (false);
    if (pWeapon->GetType() != (dword)m_WeaponType) return (false);
   }

	/* Do the armor types match? */
  if (IsMaskArmorType()) {
    pArmor = ObCastClass(CObArmoRecord, pRecord);
    if (pArmor == NULL) return (false);
    if ((dword) pArmor->IsHeavyArmor() != m_ArmorType) return (false);
   }

   	/* Do the script types match? */
  if (IsMaskScriptType()) {
    pScript = ObCastClass(CObScptRecord, pRecord);
    if (pScript == NULL) return (false);
    if ((int)pScript->GetType() != m_ScriptType) return (false);
   }

   	/* Do the enchant types match? */
  if (IsMaskEnchantType()) {
    pEnchant = ObCastClass(CObEnchRecord, pRecord);
    if (pEnchant == NULL) return (false);
    if ((int)pEnchant->GetType() != m_EnchantType) return (false);
   }

	/* Do the spell types match? */
  if (IsMaskSpellType()) {
    pSpell = ObCastClass(CObSpelRecord, pRecord);
    if (pSpell == NULL) return (false);
    if ((int)pSpell->GetType() != m_SpellType) return (false);
   }

	/* Do the spell levels match? */
  if (IsMaskSpellLevel()) {
    pSpell = ObCastClass(CObSpelRecord, pRecord);
    if (pSpell == NULL) return (false);
    if ((int)pSpell->GetLevel() != m_SpellLevel) return (false);
   }
   
   	/* Do the biped parts match? */
  if (IsMaskBipedParts()) {
    if (pRecord->GetRecordType() == OB_NAME_ARMO) {
      pArmor = ObCastClass(CObArmoRecord, pRecord);
      if (pArmor == NULL) return (false);
      BipedFlags = pArmor->GetBipedFlags();
     }
    else if (pRecord->GetRecordType() == OB_NAME_CLOT) {
      pClothing = ObCastClass(CObClotRecord, pRecord);
      if (pClothing == NULL) return (false);
      BipedFlags = pClothing->GetBipedFlags();
     }
    else {
      return (false);
     }

    switch (m_BipedCompare) {
      case OB_RECFILTER_BIPED_AND:
	if ((BipedFlags & m_BipedParts) != m_BipedParts) return (false);
	break;
      case OB_RECFILTER_BIPED_OR:
	if ((BipedFlags & m_BipedParts) == 0) return (false);
	break;
      case OB_RECFILTER_BIPED_EQUAL:
      default:
	if (BipedFlags != m_BipedParts) return (false);
	break;
     }

   }

	/* Check all field filters */
  Result = CheckFieldRecord(pRecord);
  if (!Result) return (false);

	/* Record matches all filter criteria */
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecordFilter::CheckRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - bool CheckFieldRecord (pRecord);
 *
 * Helper class for checking if the given record matches any field filters.
 *
 *=========================================================================*/
bool CObRecordFilter::CheckFieldRecord (CObRecord* pRecord) {
  dword Index;
  bool  Result;

  for (Index = 0; Index < m_FieldFilters.GetSize(); ++Index) {
    Result = CheckFieldRecord(*m_FieldFilters.GetAt(Index), pRecord);
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordFilter::CheckFieldRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - bool CheckFieldRecord (Filter, pRecord);
 *
 *=========================================================================*/
bool CObRecordFilter::CheckFieldRecord (obfilterfield_t& Filter, CObRecord* pRecord) {
  CSString Buffer;
  bool     Result;
  bool     CaseSensitive = ((Filter.Flags & OB_RECFILTER_FIELDFLAG_CASESENSITIVE) != 0);

	/* Ignore a NULL field */
  if (Filter.FieldID == 0) return (true);
  //SystemLog.Printf("Checking field filter %d, %s...", Filter.FieldID, Filter.Value.c_str());

  Result = pRecord->GetField(Buffer, Filter.FieldID);

  if (!Result) {
	/* Do nothing */
  }
  else if ((Filter.Flags & OB_RECFILTER_FIELDFLAG_EXACT) != 0) {
    Result = SafeStringCompare(Buffer, Filter.Value, !CaseSensitive) == 0;
  }
  else if ((Filter.Flags & OB_RECFILTER_FIELDFLAG_CONTAINS) != 0) {
    if (CaseSensitive)
      Result = strstr(Buffer, Filter.Value) != NULL;
    else
      Result = stristr(Buffer, Filter.Value) != NULL;
  }
  else if ((Filter.Flags & OB_RECFILTER_FIELDFLAG_STARTS) != 0) {
    if (CaseSensitive)
      Result = strncmp(Buffer, Filter.Value, Filter.Value.GetLength()) == 0;
    else
      Result = strnicmp(Buffer, Filter.Value, Filter.Value.GetLength()) == 0;
  }

  if ((Filter.Flags & OB_RECFILTER_FIELDFLAG_EXCLUDE) != 0) return (!Result);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRecordFilter::CheckFieldRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - dword CountMatchingRecords (File);
 *
 * Counts and returns the number of matching records in the given file.
 *
 *=========================================================================*/
dword CObRecordFilter::CountMatchingRecords (CObEspFile& File) {
  return CountMatchingRecords(&File.GetRecords());
 }
/*===========================================================================
 *		End of Class Method CObRecordFilter::CountMatchingRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - dword CountMatchingRecords (pTopGroup);
 *
 * Counts and returns the number of matching records in the given file.
 *
 *=========================================================================*/
dword CObRecordFilter::CountMatchingRecords (CObGroup* pTopGroup) {
  CObTypeGroup*  pGroup;
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  dword          Count = 0;
  dword		 Index;

	/* Easy answer for an empty filter */
  if (IsFlagEmpty()) return (0);
  if (!IsMaskRecordType()) return (0);
  if (m_RecordType == OB_NAME_NULL) return (0);
  if (pTopGroup == NULL) return (0);

	/* Try and retrieve the group for the given record type */
  pGroup = pTopGroup->GetTypeGroup(m_RecordType);
  if (pGroup == NULL) return (0);

	/* Very quick result for simple filters */
  if (m_FilterMask == OB_RECFILTER_MASK_RECORDTYPE) {
    return pGroup->GetNumRecords();
   }

  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);
    if (pRecord == NULL) continue;

    if (CheckRecord(pRecord)) ++Count;
   }

  return (Count);
 }
/*===========================================================================
 *		End of Class Method CObRecordFilter::CountMatchingRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - bool SetParameter (pVariable, pValue);
 *
 * Sets a class parameter from the given string pair. Returns false if 
 * the input is invalid.
 *
 *=========================================================================*/
bool CObRecordFilter::SetParameter (const SSCHAR* pVariable, const SSCHAR* pValue) {
  bool Result;
  bool Flag;

  if (stricmp(pVariable, "RecName") == 0 || stricmp(pVariable, "RecordName") == 0 ||
      stricmp(pVariable, "RecType") == 0 || stricmp(pVariable, "RecordType") == 0) {
    m_RecordType = pValue;
    m_FilterMask |= OB_RECFILTER_MASK_RECORDTYPE;
   }
  else if (stricmp(pVariable, "ID") == 0) {
    m_ID = pValue;
    if (m_DisplayName.IsEmpty()) m_DisplayName = pValue;
   }
  else if (stricmp(pVariable, "DisplayName") == 0) {
    m_DisplayName = pValue;
    if (m_ID.IsEmpty()) m_ID = pValue;
   }
  else if (stricmp(pVariable, "NameFilter") == 0) {
    m_NameFilter = pValue;
    m_FilterMask |= OB_RECFILTER_MASK_ITEMNAME;
   }
  else if (stricmp(pVariable, "Material") == 0) {
    m_Material = pValue;
    m_FilterMask |= OB_RECFILTER_MASK_MATERIAL;
   }
  else if (stricmp(pVariable, "Parent") == 0) {
    
    if (stricmp(pValue, "NULL") == 0) {
      m_ParentName.Empty();
      m_pParent = NULL;
     }
    else {
      m_ParentName = pValue;
     }
   }
  else if (stricmp(pVariable, "Empty") == 0) {
    Result = StringToBoolean(Flag, pValue);
    if (!Result) AddObGeneralError("Invalid boolean value '%s'!", pValue);
    SetEmpty(Flag);
   }
  else if (stricmp(pVariable, "ArmorType") == 0) {

    if (stricmp(pValue, "Light") == 0)
      m_ArmorType = 0;
    else if (stricmp(pValue, "Heavy") == 0)
      m_ArmorType = 1;
    else {
      AddObGeneralError("Invalid armor type '%s'!", pValue);    
     }

    m_FilterMask |= OB_RECFILTER_MASK_ARMORTYPE;
   }
  else if (stricmp(pVariable, "ScriptType") == 0) {
    Result = GetObScriptTypeValue(m_ScriptType, pValue);

    if (!Result) 
      AddObGeneralError("Invalid script type value '%s'!", pValue);
    else
      m_FilterMask |= OB_RECFILTER_MASK_SCRIPTTYPE;
   }
  else if (stricmp(pVariable, "EnchantType") == 0) {
    Result = GetObEnchantTypeValue(m_EnchantType, pValue);

    if (!Result) 
      AddObGeneralError("Invalid enchantment type value '%s'!", pValue);
    else
      m_FilterMask |= OB_RECFILTER_MASK_ENCHANTTYPE;
   }
 else if (stricmp(pVariable, "SpellType") == 0) {
    Result = GetObSpellTypeValue(m_EnchantType, pValue);

    if (!Result) 
      AddObGeneralError("Invalid spell type value '%s'!", pValue);
    else
      m_FilterMask |= OB_RECFILTER_MASK_SPELLTYPE;
   }
  else if (stricmp(pVariable, "SpellLevel") == 0) {
    Result = GetObSpellLevelValue(m_SpellLevel, pValue);

    if (!Result) 
      AddObGeneralError("Invalid spell level value '%s'!", pValue);
    else
      m_FilterMask |= OB_RECFILTER_MASK_SPELLLEVEL;
   }
  else if (stricmp(pVariable, "WeaponType") == 0) {
    Result = GetObWeaponTypeValue(m_WeaponType, pValue);
    if (!Result) AddObGeneralError("Invalid weapon type '%s'!", pValue);
    m_FilterMask |= OB_RECFILTER_MASK_WEAPONTYPE;
   }
  else if (stricmp(pVariable, "BipedParts") == 0) {
    m_BipedParts = ParseObBipedFlagString(pValue);
    m_FilterMask |= OB_RECFILTER_MASK_BIPEDPARTS;
   }
  else if (stricmp(pVariable, "BipedCompare") == 0) {
    if (stricmp(pValue, "AND") == 0) {
      m_BipedCompare = OB_RECFILTER_BIPED_AND;
     }
    else if (stricmp(pValue, "OR") == 0) {
      m_BipedCompare = OB_RECFILTER_BIPED_OR;
     }
    else if (stricmp(pValue, "Equal") == 0) {
      m_BipedCompare = OB_RECFILTER_BIPED_EQUAL;
     }
    else {
      AddObGeneralError("Invalid biped compare type '%s'!", pValue);
     }
   }
  else if (stricmp(pVariable, "Field") == 0 || stricmp(pVariable, "FieldExact") == 0) {
    AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_EXACT);
  }
  else if (stricmp(pVariable, "FieldStarts") == 0) {
     AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_STARTS);
  }
  else if (stricmp(pVariable, "FieldContains") == 0) {
     AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_CONTAINS);
  }
  else if (stricmp(pVariable, "FieldNot") == 0 || stricmp(pVariable, "FieldExactNot") == 0) {
    AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_EXACT | OB_RECFILTER_FIELDFLAG_EXCLUDE);
  }
  else if (stricmp(pVariable, "FieldStartsNot") == 0) {
     AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_STARTS | OB_RECFILTER_FIELDFLAG_EXCLUDE);
  }
  else if (stricmp(pVariable, "FieldContainsNot") == 0) {
     AddFieldFilter(pValue, OB_RECFILTER_FIELDFLAG_CONTAINS | OB_RECFILTER_FIELDFLAG_EXCLUDE);
  }
  else {
    AddObGeneralError("Unknown filter variable '%s'!", pVariable);
   }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecordFilter::SetParameter()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordFilter Method - bool AddFieldFilter (pValue, Flags);
 *
 *=========================================================================*/
bool CObRecordFilter::AddFieldFilter (const char* pValue, const dword Flags) {
  CSString         Buffer(pValue);
  CSString         Field;
  CSString         Value;
  obfilterfield_t* pNewFilter;
  bool		   Result;
  int              FieldID;

	/* Parse the input string */
  Result = Buffer.SeperateVarValue(Field, Value, ',', 0);
  if (!Result) return AddObGeneralError("No value set for field '%s'!", pValue);

	/* Find the field */
  Result = GetObFieldValue(FieldID, Field);
  if (!Result) return AddObGeneralError("Unknown field '%s' found!", Field.c_str());
  
	/* Add a new field */
  pNewFilter = new obfilterfield_t;
  m_FieldFilters.Add(pNewFilter);

  pNewFilter->FieldID = FieldID;
  pNewFilter->Flags   = Flags;
  pNewFilter->Value   = Value;

  m_FilterMask |= OB_RECFILTER_MASK_FIELDS;
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordFilter::AddFieldFilter()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObRecordFilter* FindObRecordFilter (pID, Filters);
 *
 * Find a filter in the given array by its ID. Returns NULL if
 * is is not found.
 *
 *=========================================================================*/
CObRecordFilter* FindObRecordFilter (const SSCHAR* pID, CObRecFilterArray& Filters) {
  CObRecordFilter* pFilter;
  dword		   Index;

  for (Index = 0; Index < Filters.GetSize(); ++Index) {
    pFilter = Filters[Index];
    if (stricmp(pFilter->GetID(), pID) == 0) return (pFilter);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Function FindObRecordFilter()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ResolveObRecordFilterParents (Filters);
 *
 * Fills in the m_pParent field for all filters in the given array.
 *
 *=========================================================================*/
bool ResolveObRecordFilterParents (CObRecFilterArray& Filters) {
  CObRecordFilter* pFilter;
  CObRecordFilter* pParent;
  dword		   Index;

  for (Index = 0; Index < Filters.GetSize(); ++Index) {
    pFilter = Filters[Index];
    if (!pFilter->HasParent()) continue;

    pParent = FindObRecordFilter(pFilter->GetParentName(), Filters);

    if (pParent == NULL) {
      AddObGeneralError("The filter's parent '%s' was not found!", pFilter->GetParentName());
     }
    else {
      pFilter->SetParent(pParent);
     }
    
   }

  return (true);
 }
/*===========================================================================
 *		End of Function ResolveObRecordFilterParents()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool LoadObRecordFilters (pFilename, Records);
 *
 *=========================================================================*/
bool LoadObRecordFilters (const SSCHAR* pFilename, CObRecFilterArray& Records) {
  CObRecordFilter* pFilter;
  CSString         Buffer;
  CSString	   Variable;
  CSString	   Value;
  CObFile	   File;
  dword		   InputLine;
  long		   Filesize;
  bool		   Result;

	/* Clear the current filter data, if any */
  Records.Destroy();

	/* Attempt to open the file for input */
  Result = File.Open(pFilename, "rt");
  if (!Result) return (false);

  Filesize  = File.GetFileSize();
  InputLine = 0;
  pFilter   = NULL;

	/* Read and parse entire file */
  while (!File.IsEOF() && File.Tell() < Filesize) {
    Result = File.ReadLine(Buffer);
    if (!Result) return (false);
    ++InputLine;

    Result = Buffer.SeperateVarValue(Variable, Value);

    if (pFilter != NULL) {
      if (Variable.CompareNoCase("End") == 0) {
	pFilter = NULL;
       }
     else if (Result) {
       Result = pFilter->SetParameter(Variable, Value);
       //if (!Result) AddObGeneralError("%5lu: Invalid filter variable/value found: %s = %s", InputLine, Variable.c_str(), Value.c_str());
      }
     else {
       AddObGeneralError("%5lu: Unknown variable/value pair found: %s = %s", InputLine, Variable.c_str(), Value.c_str());
      }

     }
    else if (Variable.CompareNoCase("DisplayFilter") == 0 || Variable.CompareNoCase("Filter") == 0) {
      pFilter = new CObRecordFilter;
      Records.Add(pFilter);
     }
   }

  if (pFilter != NULL) {
    AddObGeneralError("%5lu: Missing 'End' tag!", InputLine);
   }

  ResolveObRecordFilterParents(Records);
  return (true);
 }
/*===========================================================================
 *		End of Function LoadObRecordFilters()
 *=========================================================================*/
