/*===========================================================================
 *
 * File:	ObMultiRecordhandler.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Steps for loading multiple files
 *	- Get list of masters (only masters allowed)
 *	- Get active file (if any)
 *	- Determine load order of master
 *	- Load masters one by one
 *	- Load active file (if any)
 *
 *	- Index first master
 *	- Index subsequent masters, looking for
 *		- Editorid duplicates (must change ID or ignore)

 *		- Formid duplicates (must change ID or ignore)
 *		- Modified records (replace index)
 *			- Create list of duplicates
 *			- Add duplicates with new IDs after each file
 *	- Index active file, same as masters
 *	- Create master record tree
 *
 *
 *=========================================================================*/

	/* Include Files */
#include "obmultirecordhandler.h"
#include "../common/obtime.h"
#include "obimport.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* One global copy of Oblivion.esm */
  CObEspFile CObMultiRecordHandler::m_OblivionMaster;

	/* Static options for the handler */
  obmultirecoptions_t CObMultiRecordHandler::m_Options;	

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Constructor
 *
 *=========================================================================*/
CObMultiRecordHandler::CObMultiRecordHandler (const dword HashMapSize) {
  m_NextFreeFormID   = OBESPFILE_FIRST_FORMID;
  m_NextFreeEditorID = OBESPFILE_FIRST_EDITORID;

  //m_FormIdMap.InitHashTable(HashMapSize);
  //m_EditorIdMap.InitHashTable(HashMapSize);

  m_ActiveFile.SetParent(this);

	/* Initialize the special player reference */
  m_PlayerRef.Initialize(OB_NAME_REFR);
  m_PlayerRef.InitializeNew();
  m_PlayerRef.SetFormID(OB_PLAYERREF_FORMID);
  m_PlayerRef.SetBaseFormID(OB_PLAYER_FORMID);
  m_PlayerRef.SetParent(this);
  m_PlayerRef.SetQuestItem(true);

}
/*===========================================================================
 *		End of Class CObMultiRecordHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CObMultiRecordHandler::Destroy (void) {
  m_NextFreeFormID   = OBESPFILE_FIRST_FORMID;
  m_NextFreeEditorID = OBESPFILE_FIRST_EDITORID;

	/* Remove the oblivion master file from the array if required */
  if (m_MasterFiles.GetAt(0) == &m_OblivionMaster) {
    m_MasterFiles.SetAt(0, NULL);
  }

  m_EventHandler.Destroy();
  m_UndoItems.Destroy();
  m_NewRecords.Destroy();
  m_TopFileGroup.Destroy();
  m_NewGroups.Destroy();
  m_FormIdMap.Destroy();
  m_EditorIdMap.Destroy();
  m_ActiveFile.Destroy();
  m_MasterFiles.Destroy();

  m_DuplicateFormIDs.Destroy();
  m_DuplicateEditorIDs.Destroy();

  m_GroupAllocator.Destroy();
  m_TypeGroupAllocator.Destroy();
  m_FormIDGroupAllocator.Destroy();
  m_BlockGroupAllocator.Destroy();
  m_GridGroupAllocator.Destroy();

}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObEspFile* AddMaster (void);
 *
 * Create and return a new master file. The new file is not initialized.
 *
 *=========================================================================*/
CObEspFile* CObMultiRecordHandler::AddMaster (void) {
  CObEspFile* pNewFile;

  pNewFile = new CObEspFile;
  if (pNewFile == NULL) return (NULL);

  m_MasterFiles.Add(pNewFile);
  pNewFile->SetParent(this);
  return (pNewFile);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::AddMaster()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - dword ChangeFormIDIndex (NewID, OldID, StartMasterIndex);
 *
 *=========================================================================*/
dword CObMultiRecordHandler::ChangeFormIDIndex (const obformid_t NewID, const obformid_t OldID, const dword StartMasterIndex) {
  dword Index;
  dword Count = 0;

  for (Index = StartMasterIndex; Index < m_MasterFiles.GetSize(); ++Index) {
    Count += m_MasterFiles[Index]->ChangeFormID(NewID, OldID);
  }

  if (StartMasterIndex <= m_MasterFiles.GetSize()) {
    Count += m_ActiveFile.ChangeFormID(NewID, OldID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ChangeFormIDIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - dword ChangeEditorIDIndex (pNewID, pOldID, StartModIndex);
 *
 *=========================================================================*/
dword CObMultiRecordHandler::ChangeEditorIDIndex (const SSCHAR* pNewID, const SSCHAR* pOldID, const dword StartModIndex) {
  dword Index;
  dword Count = 0;

  for (Index = StartModIndex; Index < m_MasterFiles.GetSize(); ++Index) {
    Count += m_MasterFiles[Index]->ChangeEditorID(pNewID, pOldID);
  }

  if (StartModIndex <= m_MasterFiles.GetSize()) {
    Count += m_ActiveFile.ChangeEditorID(pNewID, pOldID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ChangeEditorIDIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CheckDuplicateFormId (pRecord);
 *
 * Checks if the given record's formid is a duplicate according to the
 * current content and handles it accordingly if it is. Returns true
 * if it is a duplicate.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CheckDuplicateFormId (CObRecord* pRecord) {
  CObRecord*   pRecord2;
  bool         Result;

	/* Ensure valid input */
  if (pRecord == NULL) return (false);

	/* Find an existing formid */
  Result = m_FormIdMap.Lookup(pRecord->GetFormID(), pRecord2);
  if (!Result) return (false);

	/* See the records are the same type */
  if (pRecord2->GetRecordType() == pRecord->GetRecordType()) {
    return (false);
  }

  SystemLog.Printf("Found duplicate formid 0x%X!", pRecord->GetFormID());
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CheckDuplicateFormId()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CheckDuplicateEditorId (pRecord);
 *
 * Checks if the given record's editorid is a duplicate according to
 * the current content. Returns true if it is a duplicate.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CheckDuplicateEditorId (CObIdRecord* pRecord) {
  CObIdRecord*  pIdRecord2;
  bool		Result;

  	/* Ensure valid input */
  if (pRecord == NULL) return (false);

	/* Find an existing formid */
  Result = m_EditorIdMap.Lookup(pRecord->GetEditorID(), pIdRecord2);
  if (!Result) return (false);
  
	/* See the records have the same formid */
  if (pIdRecord2->GetFormID() == pRecord->GetFormID()) {
    return (false);
  }

  SystemLog.Printf("Found duplicate editorid '%s'!", pRecord->GetEditorID());
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CheckDuplicateEditorId()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* CleanRecord (pRecord);
 *
 * Removes the given record from the active file returning the next
 * instance of the record if it exists, or NULL. Returns the given
 * record if it is not active.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::CleanRecord (CObRecord* pRecord) {
  CObRecord*   pPrevRecord;
  CObUndoItem* pUndoItem;

	/* Ignore invalid input */
  if (pRecord == NULL) return (NULL);

	/* Ignore if not active */
  if (!pRecord->IsActive()) return (pRecord);

	/* Update all listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Create the undo item */
  pUndoItem = CreateUndoClean(pRecord);

	/* Find any previous version of the record */
  pPrevRecord = FindNonActiveRecord(pRecord);

	/* Update the overall record tree */
  UpdateRecordTree(pPrevRecord, pRecord);

	/* Update the index */
  RemoveFromIndex(pRecord);
  if (pPrevRecord != NULL) IndexRecord(pPrevRecord);

	/* Update all listeners */
  m_EventHandler.SendCleanEvent(pPrevRecord, pRecord);

	/* Delete the record from the active file */
  m_ActiveFile.DeleteRecord(pRecord);
  return (pPrevRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CleanRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - dword CountAllRecords (void);
 *
 * Count and return the records in all current files.
 *
 *=========================================================================*/
dword CObMultiRecordHandler::CountAllRecords (void) {
  dword Count = 0;
  dword Index;

  for (Index = 0; Index < m_MasterFiles.GetSize(); ++Index) {
    Count += m_MasterFiles[Index]->GetRecordCount();
  }

  Count += m_ActiveFile.GetRecordCount();
  return (Count);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CountAllRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateFormidFixup (FixupArray, pFile, ModIndex);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateFormidFixup (CObFormidFixupArray& FixupArray, CObEspFile* pFile, const byte ModIndex) {
  CObTes4Record*      pHeader = pFile->GetHeader();
  CObSubrecord*       pSubrecord;
  const SSCHAR*	      pMasterString;
  bool		      Result = true;
  int		      Position;
  int		      FileModIndex = 0;
  int		      ResultModIndex;

  if (pHeader == NULL) return (false);
  SystemLog.Printf("===== Performing modindex fixups on file '%s', with current modindex %d...", pFile->GetShortFilename(), (dword) ModIndex);

	/* Loop through all master subrecords in header */
  pSubrecord = pHeader->FindFirstSubrecord(OB_NAME_MAST, Position);

  while (pSubrecord != NULL) {
    pMasterString  = (const SSCHAR *) pSubrecord->GetData();
    ResultModIndex = FindModIndex(pMasterString);

    if (ResultModIndex >= 0) {
      FixupArray.Add((byte) ResultModIndex);
      SystemLog.Printf("\tMaster modindex fixup %d to %d in file '%s'.", FileModIndex, ResultModIndex, pMasterString);
    }
    else {
      AddObGeneralError("Missing master file '%s' with current modindex %d!", pMasterString, FileModIndex);
      FixupArray.Add(FileModIndex);
      //Result = false;
    }

    pSubrecord = pHeader->FindNextSubrecord(OB_NAME_MAST, Position);
    ++FileModIndex;
  }

	/* Special case for first master with no fixups */
  if (ModIndex == 0 && FileModIndex == 0) {
    SystemLog.Printf("\tNo master dependancies to fix!");
    return (true);
  }
  
	/* Don't change the active file modindex if we don't need to */
  if (FileModIndex >= ModIndex) {
    FixupArray.Add(FileModIndex);
    SystemLog.Printf("\tCurrent modindex fixup %d to %d.", FileModIndex, FileModIndex);
    pFile->SetModIndex(FileModIndex);
    ++FileModIndex;
  }
	/* Add the current file fixup */
  else {
    FixupArray.Add(ModIndex);
    SystemLog.Printf("\tCurrent modindex fixup %d to %d.", FileModIndex, ModIndex);
    pFile->SetModIndex(ModIndex);
    ++FileModIndex;
  }
  
  
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateFormidFixup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObBaseRecord* CreateNewRecord (Type);
 *
 * Creates and adds a new record to the active file as given by the input
 * record type. The new record is returned.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::CreateNewRecord (const obrectype_t Type) {
  return m_ActiveFile.CreateNewRecord(Type);
 }
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObIdRecord* CreateIDRecordFromCsvRow (CsvInfo, Row, pOldRecord);
 *
 * Creates a new record, or reuses an existing record, for the given
 * CSV row. Returns NULL on any error.
 *
 *=========================================================================*/
CObIdRecord* CObMultiRecordHandler::CreateIDRecordFromCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row, CObIdRecord*& pOldRecord) {
  CSString*      pEditorID;
  CSString*      pRecordName;
  CObIdRecord*   pIdRecord;
  CObBaseRecord* pBaseRecord;
  CObIdRecord*   pNewRecord;
  bool		 Result;
  
	/* Get the required column data */
  pEditorID   = Row.GetAt(CsvInfo.pEditorID->ColIndex);
  pRecordName = Row.GetAt(CsvInfo.pRecordName->ColIndex);
  pOldRecord  = NULL;

  if (pEditorID   == NULL) {
    AddObGeneralError("Missing 'EditorID' field in row %d of CSV file!", CsvInfo.CurrentLine);
    return (NULL);
  }

  if (pRecordName == NULL) {
    AddObGeneralError("Missing 'RecordName' field in row %d of CSV file!", CsvInfo.CurrentLine);
    return (NULL);
  }

	/* Prepare the strings */
  pEditorID->Unescape();
  pRecordName->Unescape();
  ObPrepareEditorID(*pEditorID);

  	/* Does the record already exist? */
  pIdRecord = FindEditorID(pEditorID->c_str());

  if (pIdRecord != NULL) {

		/* Ensure the record types match */
    if (pIdRecord->GetRecordType() != pRecordName->c_str()) {
      AddObGeneralError("Existing record '%s' type (%4.4s) does not match desired type %s!", pEditorID->c_str(), pIdRecord->GetRecordType().Name, pRecordName->c_str());
      return (NULL);
    }

		/* Update any listeners */
    m_EventHandler.SendPreUpdateEvent(pIdRecord);
    pOldRecord = pIdRecord;

		/* Ensure an active record */
    pBaseRecord = MakeRecordActivePriv(pIdRecord, false);
    if (pBaseRecord == NULL) return (NULL);
    pNewRecord = ObCastClass(CObIdRecord, pBaseRecord);
    if (pNewRecord == NULL) return (NULL);

		/* Update the record indices */
    RemoveFromIndex(pIdRecord);
    pNewRecord->SetEditorID(pEditorID->c_str());
    IndexRecord(pNewRecord);
  }
	/* Must create a new record */
  else {

		/* Ensure it is a known record name */
    if (FindObRecCreate(pRecordName->c_str()) == NULL) {
      AddObGeneralError("Unknown record type '%s' found in row %d!", pRecordName->c_str(), CsvInfo.CurrentLine);
      return (NULL);
    }
     
    pBaseRecord = CreateObRecord(pRecordName->c_str());
    if (pBaseRecord == NULL) return (NULL);
    pNewRecord = ObCastClass(CObIdRecord, pBaseRecord);

    if (pNewRecord == NULL) {
      delete pBaseRecord;
      return (NULL);
    }

	  	/* Move the record into the active file and record tree */
    Result = MoveNewRecord(pNewRecord);
    if (!Result) return (false);

		/* Select unused formID */
    pNewRecord->SetFormID(GetActiveFreeFormID());
    pNewRecord->SetEditorID(pEditorID->c_str());

    IndexRecord(pNewRecord);
  }

  return (pNewRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateIDRecordFromCsvRow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateRecordTree (pCallback);
 *
 * Creates the full record tree for all current files.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateRecordTree (CObCallback* pCallback) {
  bool  Result;
  dword Index;

	/* Set the initialize array size */
  m_NewGroups.SetAllocatedSize(OBE_DEFAULT_NEWGROUP_SIZE);

  if (pCallback != NULL) {
    dword Count = m_FormIdMap.GetRecordCount();
    pCallback->SetTotalRecords(Count);
    pCallback->SetCallbackInterval(Count/100);
    pCallback->Reset();
    pCallback->ForceCallback(0);
  }

	/* Add records from all master files */
  for (Index = 0; Index < m_MasterFiles.GetSize(); ++Index) {
    Result = CreateRecordTree(m_MasterFiles.GetAt(Index), pCallback);
    if (!Result) return (false);
  }

	/* Add in records from the active file */
  Result = CreateRecordTree(&m_ActiveFile, pCallback);

  SystemLog.Printf("New groups size = %u", m_NewGroups.GetSize());
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateRecordTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateRecordTree (pFile, pCallback);
 *
 * Fills in the overall record tree for the given file.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateRecordTree (CObEspFile* pFile, CObCallback* pCallback) {

  if (pCallback != NULL) {
    pCallback->SetLabel("Creating record tree for file '%s'...", pFile->GetShortFilename());
    //pCallback->Reset();
    //pCallback->ForceCallback(0);
    //pCallback->SetCallbackInterval(1);
  }

  return CreateRecordTree(&m_TopFileGroup, &pFile->GetRecords(), pCallback);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateRecordTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateRecordTree (pDestGroup, pSourceGroup, pCallback);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateRecordTree (CObGroup* pDestGroup, CObGroup* pSourceGroup, CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  CObGroup*      pGroup;
  CObGroup*      pNextGroup;
  dword		 Index;
  bool           Result;
  bool		 FirstFile = (pDestGroup->GetNumRecords() == 0);

  for (Index = 0; Index < pSourceGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pSourceGroup->GetRecord(Index);
    pRecord = ObCastRecord(pBaseRecord);

    if (pRecord != NULL) {
      Result = CreateTreeAddRecord(pDestGroup, pRecord, FirstFile);
      if (!Result) return (false);

      if (pCallback != NULL) {
        int iResult = pCallback->UpdateCallback(pCallback->GetProcessRecords() + 1);
        if (iResult < 0) return (false);
      }
    }
    else {
      pGroup = ObCastGroup(pBaseRecord);
      if (pGroup == NULL) continue;

      pNextGroup = CreateTreeFindGroup(pDestGroup, pGroup, FirstFile);

      if (pNextGroup != NULL) {
        Result = CreateRecordTree(pNextGroup, pGroup, pCallback);
	if (!Result) return (false);
      }
    }

  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateRecordTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateTreeAddRecord (pDestGroup, pNewRecord, FirstFile);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateTreeAddRecord (CObGroup* pDestGroup, CObRecord* pNewRecord, const bool FirstFile) {

	/* Special case for a first file */
  if (FirstFile) {
    pDestGroup->GetRecords().Add(pNewRecord);
    return (true);
  }

  return pDestGroup->AddExistingRecord(pNewRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateTreeAddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObGroup* CreateTreeFindGroup (pDestGroup, pNewGroup, FirstFile);
 *
 *=========================================================================*/
CObGroup* CObMultiRecordHandler::CreateTreeFindGroup (CObGroup* pDestGroup, CObGroup* pNewGroup, const bool FirstFile) {
  CObGroup* pGroup;

	/* Find an existing group */
  if (!FirstFile) {
    //SystemLog.Printf("test");
    pGroup = pDestGroup->FindSubGroup(pNewGroup);
    if (pGroup != NULL) return (pGroup);
  }
	
	/* Create a new group */
  pGroup = pDestGroup->CreateSubGroup(pNewGroup);

/*
  pGroup = m_GroupAllocator.CreateObject();
  pDestGroup->GetRecords().Add(pGroup);
  pGroup->GetHeader().Data.ParentFormID = pNewGroup->GetHeader().Data.ParentFormID;

  pGroup->GetRecords().SetAllocatedSize((int)((pNewGroup->GetNumRecords() + 40))); //*/

  m_NewGroups.Add(pGroup);
  return (pGroup);

#if FALSE
  CObBaseRecord* pBaseRecord;
  CObGroup*      pGroup;
  dword          Index;
  static dword Count = 0;
  static double TimeSum = 0;
  static double TimeSum1 = 0;
  static double TimeSum2 = 0;
  static double TimeSum3 = 0;

	/* Don't search when the first file is added */
  if (!FirstFile) {
    for (Index = 0; Index < pDestGroup->GetNumRecords(); ++Index) {
      pBaseRecord = pDestGroup->GetRecord(Index);
      pGroup      = ObCastGroup(pBaseRecord);
      if (pGroup == NULL) continue;

      if (pGroup->Compare(pNewGroup)) return (pGroup);
    }
  }

  obtimer_t Timer;
  ObStartTimer(Timer);
/*
  switch (pNewGroup->GetType()) {
    case OB_GROUP_TYPE:
	pGroup = m_TypeGroupAllocator.CreateObject();
	break;
    case OB_GROUP_WORLDCHILD:
    case OB_GROUP_CELLCHILD:
    case OB_GROUP_TOPICCHILD:
    case OB_GROUP_CELLPERSIST:
    case OB_GROUP_CELLTEMP:
    case OB_GROUP_CELLDISTANT:
    	pGroup = m_FormIDGroupAllocator.CreateObject();
	break;
    case OB_GROUP_INTCELL:	
    case OB_GROUP_INTSUBCELL:
	pGroup = m_BlockGroupAllocator.CreateObject();
	break;
    case OB_GROUP_EXTCELL:
    case OB_GROUP_EXTSUBCELL:
	pGroup = m_GridGroupAllocator.CreateObject();
	break;
    default:
        pGroup = m_GroupAllocator.CreateObject();
    	break;
  } //*/
  //pGroup = m_GroupAllocator.CreateObject();

  pGroup = CreateObRefGroup(pNewGroup->GetType());
  m_NewGroups.Add(pGroup);

  TimeSum += ObEndTimer(Timer);
  ObStartTimer(Timer);

  pDestGroup->GetRecords().Add(pGroup);

  TimeSum1 += ObEndTimer(Timer);
  ObStartTimer(Timer);

  pGroup->GetHeader().Data.ParentFormID = pNewGroup->GetHeader().Data.ParentFormID;

  TimeSum2 += ObEndTimer(Timer);
  ObStartTimer(Timer);
  
  //pGroup->GetRecords().SetAllocatedSize((int)((pNewGroup->GetNumRecords() + 4)));

  TimeSum3 += ObEndTimer(Timer);
  //ObStartTimer(Timer);

  
  ++Count;

  if ((Count % 10000) == 0) {
    SystemLog.Printf("CreateTreeFindGroup(): New count = %u, Time = %f s, Time = %f s, Time = %f s, Time = %f s", Count, TimeSum, TimeSum1, TimeSum2, TimeSum3);
  }

  return (pGroup);
#endif
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateTreeFindGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool DeleteRecord (pRecord);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::DeleteRecord (CObRecord* pRecord) {
  CObIdRecord* pIdRecord;
  bool         Result;

  if (pRecord == NULL) return (false);

	/* Delete record from the index maps */
  m_FormIdMap.Delete(pRecord);

  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord != NULL) m_EditorIdMap.Delete(pIdRecord);

  Result = m_ActiveFile.DeleteRecord(pRecord);

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::DeleteRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool DeleteMaster (CObEspFile* pMaster);
 *
 * Attempt to delete the given master. Also removes all records from
 * the master if found. Returns false if the given master is not valid.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::DeleteMaster (CObEspFile* pMaster) {
  int Index;
  
	/* Ensure the master file exists in the master array */
  Index = m_MasterFiles.Find(pMaster);
  if (Index < 0) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::DeleteMaster()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - dword Find (FindData, pCallback);
 *
 *=========================================================================*/
dword CObMultiRecordHandler::Find (obfinddata_t& FindData, CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  CObTypeGroup*	 pGroup;
  dword          FindCount = 0;
  dword          Index;
  dword		 Count;
  bool		 IsExcluded;
  bool		 FindText = (FindData.Flags & OB_FIND_COMPARETEXT) != 0;
  bool		 Result;
  int            iResult;

  if (pCallback != NULL) {
    pCallback->SetTotalRecords(CountAllRecords());
    pCallback->SetCallbackInterval(pCallback->GetTotalRecords()/1000);
    pCallback->Reset();
  }

  ++FindData.FileCount;
  
  for (Index = 0; Index < m_TopFileGroup.GetNumRecords(); ++Index) {
    pBaseRecord = m_TopFileGroup.GetRecord(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pRecord) {
      if ((FindData.Flags & OB_FIND_NOHEADER) != 0 && pRecord->GetRecordType() == OB_NAME_TES4)
        IsExcluded = true;
      else
        IsExcluded = ObContainsRecordType(pRecord->GetRecordType(), FindData.pExcludeRecords);
    }
    else {
      pGroup = ObCastClass(CObTypeGroup, pBaseRecord);
      if (pGroup != NULL) IsExcluded = ObContainsRecordType(pGroup->GetContainsType(), FindData.pExcludeRecords);
    }
    
    if (pRecord == NULL || !IsExcluded) {
      if (FindText)
        Result = pBaseRecord->FindText(Count, FindData, pCallback);
      else
        Result = pBaseRecord->Find(Count, FindData, pCallback);

      FindCount += Count;
      if (!Result) return (FindCount);
    }

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(pCallback->GetProcessRecords() + 1);
      if (iResult < 0) return (FindCount);
    }
  }

  return (FindCount);
 }
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* FindFormID (FormID);
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::FindFormID (const obformid_t FormID) {
  CObRecord* pRecord;
  bool	     Result;

	/* Ignore invalid input */
  if (FormID == OB_FORMID_NULL) return (NULL);

  Result = m_FormIdMap.Lookup(FormID, pRecord);
  if (!Result) return (NULL);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FindFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObIdRecord* FindEditorID (pString);
 *
 *=========================================================================*/
CObIdRecord* CObMultiRecordHandler::FindEditorID (const SSCHAR* pString) {
  CObIdRecord* pRecord;
  bool	       Result;

	/* Ignore invalid input */
  if (pString == NULL) return (NULL);

  Result = m_EditorIdMap.Lookup(pString, pRecord);
  if (!Result) return (NULL);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FindEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - int FindModIndex (pFilename);
 *
 * Attempt to find and return the current mod index of the given filename
 * (no path). Returns -1 if not found.
 *
 *=========================================================================*/
int CObMultiRecordHandler::FindModIndex (const SSCHAR* pFilename) {
  CSString Buffer;
  dword    Index;

  for (Index = 0; Index < m_MasterFiles.GetSize(); ++Index) {
    Buffer = m_MasterFiles[Index]->GetFilename();
    Buffer.ReverseTruncate(":\\/");

    if (Buffer.IsEmpty()) continue;
    if (Buffer.CompareNoCase(pFilename) == 0) return (Index);
  }

  Buffer = m_ActiveFile.GetFilename();
  Buffer.ReverseTruncate(":\\/");
  if (Buffer.IsEmpty()) return (-1);
  if (Buffer.CompareNoCase(pFilename) == 0) return (Index);

  return (-1);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FindModIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* FindNonActiveRecord (pRecord);
 *
 * Finds the instance of given record not in the active file. Returns
 * NULL if no match was found.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::FindNonActiveRecord (CObRecord* pRecord) {
  CObEspFile*    pFile;
  CObRecord*     pOldRecord;
  CObBaseRecord* pBaseRecord;
  int            Index;

	/* Search all master files in reverse order */
  for (Index = m_MasterFiles.GetSize() - 1; Index >= 0; --Index) {
    pFile = m_MasterFiles.GetAt(Index);

    pBaseRecord = pFile->GetRecords().FindFormID(pRecord->GetFormID());
    if (pBaseRecord == NULL) continue;

    pOldRecord = ObCastRecord(pBaseRecord);
    if (pOldRecord != NULL) return (pOldRecord);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FindNonActiveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool FixupFormids (void);
 *
 * Fixes the formids of all mods.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::FixupFormids (void) {
  CSString Buffer;
  dword	   ModIndex;
  bool     Result = true;

  for (ModIndex = 0; ModIndex < m_MasterFiles.GetSize(); ++ModIndex) {
    Result &= FixupFormids(m_MasterFiles[ModIndex], ModIndex);   
  }

	/* Fixup the active file */
  Result &= FixupFormids(&m_ActiveFile, ModIndex);
  //m_ActiveFile.SetModIndex(ModIndex);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FixupFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool FixupFormids (pFile, ModIndex);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::FixupFormids (CObEspFile* pFile, const byte ModIndex) {
  CObFormidFixupArray   FixupArray;
  bool			Result;

	/* Create the fixup array */
  Result = CreateFormidFixup(FixupArray, pFile, ModIndex);
  if (!Result) return (false);

	/* Ignore if nothing needs to change */
  Result = HasFixupChanged(FixupArray);

  if (!Result) {
    SystemLog.Printf("\tNo modindex fixups needed in file %s!", pFile->GetShortFilename());
    return (true);
  }

	/* Perform the fixup */
  Result = pFile->FixupFormids(FixupArray);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::FixupFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool GetEditorID (Buffer, FormID);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::GetEditorID (CSString& Buffer, const obformid_t FormID) {
  CObRecord*   pRecord;
  CObIdRecord* pIdRecord;
  
  Buffer.Empty();
  if (FormID == OB_FORMID_NULL) return (true);

  pRecord = FindFormID(FormID);
  if (pRecord == NULL) return (false);

  pIdRecord = ObCastClass(CObIdRecord, pRecord);

  if (pIdRecord == NULL) { 
    CObSubrecord* pSubrecord = pRecord->FindSubrecord(OB_NAME_EDID);
    if (pSubrecord == NULL) return (false);
    Buffer = (char *) pSubrecord->GetData();
  }
  else {
    Buffer = pIdRecord->GetEditorID();
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::GetEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class SSCHAR* CObMultiRecordHandler Method - const GetEditorID (FormID);
 *
 *=========================================================================*/
const SSCHAR* CObMultiRecordHandler::GetEditorID (const obformid_t FormID) {
  CObRecord*   pRecord;
  CObIdRecord* pIdRecord;
    
  if (FormID == OB_FORMID_NULL) return (NULL);

  pRecord = FindFormID(FormID);
  if (pRecord == NULL) return (NULL);

  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord != NULL) return pIdRecord->GetEditorID();

  CObSubrecord* pSubrecord = pRecord->FindSubrecord(OB_NAME_EDID);
  if (pSubrecord == NULL) return (NULL);
  return (const char *) pSubrecord->GetData();
}
/*===========================================================================
 *		End of Class Method SSCHAR* CObMultiRecordHandler::GetEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - const SSCHAR* GetFreeEditorID (void);
 *
 *=========================================================================*/
const SSCHAR* CObMultiRecordHandler::GetFreeEditorID (void) {
  static CSString s_Buffer;
  dword NumOverFlows = 0;
  
  do {
    s_Buffer.Format("obeditid%08X", m_NextFreeEditorID);
    ++m_NextFreeEditorID;

		/* Check for an overflow */
    if (m_NextFreeEditorID > OBESPFILE_LAST_EDITORID) {
      ++NumOverFlows;
      m_NextFreeEditorID = OBESPFILE_FIRST_EDITORID;

		/* Prevent an infinite loop in the worst case */
      if (NumOverFlows > 1) {
        m_NextFreeEditorID = 0;
	AddObGeneralError("GetFreeEditorID(): All form IDs are in use!");
	break;
      }
    }

  } while (FindEditorID(s_Buffer) != NULL);

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::GetFreeEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - obformid_t GetFreeFormID (ModIndex);
 *
 * Returns the next available form ID not currently in use by the mod.
 *
 *=========================================================================*/
obformid_t CObMultiRecordHandler::GetFreeFormID (const byte ModIndex) {
  dword      NumOverFlows = 0;
  obformid_t FormID;

  do {
    FormID = OB_MAKEFORMID(m_NextFreeFormID, ModIndex);
    ++m_NextFreeFormID;

		/* Check for an overflow */
    if (m_NextFreeFormID > MAX_OBFORMID) {
      ++NumOverFlows;
      m_NextFreeFormID = OBESPFILE_FIRST_FORMID;

		/* Prevent an infinite loop in the worst case */
      if (NumOverFlows > 1) {
        m_NextFreeFormID = 0;
	AddObGeneralError("GetFreeFormID(): All form IDs are in use!");
	break;
      }
    }

  } while (FindFormID(FormID) != NULL);

  if (m_ActiveFile.GetHeader() != NULL) {
    m_ActiveFile.GetHeader()->SetFileType(FormID & 0x00ffffff);
  }

  return (FormID);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::GetFreeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool HandleDuplicateFormIDs (void);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::HandleDuplicateFormIDs (void) {
  obdupformidinfo_t* pDupFormID;
  obformid_t	     OldFormID;
  obformid_t	     NewFormID;
  dword		     Index;
  //dword		     Count;

  for (Index = 0; Index < m_DuplicateFormIDs.GetSize(); ++Index) {
    pDupFormID = m_DuplicateFormIDs.GetAt(Index);

    OldFormID  = pDupFormID->pRecord->GetFormID();
    NewFormID  = GetFreeFormID(pDupFormID->ModIndex);
    if (NewFormID == OB_FORMID_NULL) return (false);

    //Count = ChangeFormIDIndex(NewFormID, OldFormID, pDupFormID->ModIndex);
    //SystemLog.Printf("Changed %d occurences of the formid 0x%X to 0x%X!", Count, OldFormID, NewFormID);

    pDupFormID->pRecord->ChangeFormID(NewFormID, OldFormID);
    AddObGeneralError("Duplicate formid 0x%X changed to 0x%X! Any dependant records were NOT updated!", OldFormID, NewFormID);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::HandleDuplicateFormIDs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool HandleDuplicateEditorIDs (void);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::HandleDuplicateEditorIDs (void) {
  obdupeditoridinfo_t*  pDupEditorID;
  CSString		OldEditorID;
  CSString		NewEditorID;
  dword			Index;
  //dword			Count;

  for (Index = 0; Index < m_DuplicateEditorIDs.GetSize(); ++Index) {
    pDupEditorID = m_DuplicateEditorIDs.GetAt(Index);

    OldEditorID  = pDupEditorID->pRecord->GetEditorID();
    NewEditorID  = GetFreeEditorID();
    if (NewEditorID.IsEmpty()) return (false);
    
    //Count = ChangeEditorIDIndex(NewEditorID, OldEditorID, pDupEditorID->ModIndex);
    //SystemLog.Printf("Changed %d occurences of the editorid %s to %s!", Count, OldEditorID.c_str(), NewEditorID.c_str());

    pDupEditorID->pRecord->ChangeEditorID(NewEditorID, OldEditorID);
    AddObGeneralError("Duplicate editor '%s' changed to '%s'! Any dependant records were NOT updated!", OldEditorID.c_str(), NewEditorID.c_str());
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::HandleDuplicateEditorIDs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool HasFixupChanged (FixupArray);
 *
 * Returns true if the given formid fixup array contains any changes to the
 * modindex.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::HasFixupChanged (CObFormidFixupArray& FixupArray) {
  dword Index;

  for (Index = 0; Index < FixupArray.GetSize(); ++Index) {
    if (FixupArray[Index] != (byte) Index) return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::HasFixupChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool ImportCsvRow (CsvInfo, Row);
 *
 * Attempts to import the given row from a CSV as a new record or modify
 * an existing record.  Returns true if the import was successful.
 * Assumes the the input CSV is valid and contains the necessary information
 * for importing.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::ImportCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row) {
  CObIdRecord* pNewRecord;
  CObIdRecord* pOldRecord;

	/* Create or reuse an existing record */
  pNewRecord = CreateIDRecordFromCsvRow(CsvInfo, Row, pOldRecord);
  if (pNewRecord == NULL) return (false);

	/* Set the record values */
  pNewRecord->ImportCsvRow(CsvInfo, Row);

	/* Update any listeners */
  if (pOldRecord == NULL) {
    m_EventHandler.SendAddEvent(pNewRecord, NULL);
  }
  else {
    m_EventHandler.SendUpdateEvent(pNewRecord, pOldRecord);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ImportCsvRow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool ImportCsv (NewRecords, CsvFile);
 *
 * Attempt to import records from the given CSV file. Returns false
 * on any error. Returns the number of new records created in the
 * given parameter.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::ImportCsv (dword& NewRecords, CCsvFile& CsvFile) {
  obcsvinfo_t    CsvInfo;
  CCsvRow*       pRow;
  dword          Index;
  bool           Result;

	/* Check if there's anything to import */
  NewRecords = 0;
  if (CsvFile.GetNumRows() <= 1) return (true);

  Result = ObPrepareImportCsvInfo(CsvInfo, CsvFile);
  if (!Result) return (false);
  
	/* Attempt to import all rows */
  for (Index = 1; Index < CsvFile.GetNumRows(); ++Index) {
    pRow = CsvFile.GetRow(Index);
    if (pRow == NULL) continue;

    CsvInfo.CurrentLine = Index;

    Result = ImportCsvRow(CsvInfo, *pRow);
    if (Result) ++NewRecords;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ImportCsv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool IndexDuplicates (void);
 *
 * Indexes any records with a duplicate formid/editorid after being
 * handler.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::IndexDuplicates (void) {
  obdupeditoridinfo_t*  pDupEditorID;
  obdupformidinfo_t*    pDupFormID;
  dword			Index;

  for (Index = 0; Index < m_DuplicateFormIDs.GetSize(); ++Index) {
    pDupFormID = m_DuplicateFormIDs.GetAt(Index);
    IndexRecord(pDupFormID->pRecord);
  }

  for (Index = 0; Index < m_DuplicateEditorIDs.GetSize(); ++Index) {
    pDupEditorID = m_DuplicateEditorIDs.GetAt(Index);
    IndexRecord(pDupEditorID->pRecord);
  }

  m_DuplicateFormIDs.Destroy();
  m_DuplicateEditorIDs.Destroy();
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IndexDuplicates()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - void IndexRecord (pRecord);
 *
 * Indexes the record with no duplicate checks.
 *
 *=========================================================================*/
void CObMultiRecordHandler::IndexRecord (CObRecord* pRecord) {
  CObIdRecord* pIdRecord;
  
  if (pRecord != NULL) {
    m_FormIdMap.SetAt(pRecord);

    pIdRecord = ObCastClass(CObIdRecord, pRecord);
    if (pIdRecord != NULL) m_EditorIdMap.SetAt(pIdRecord);
  }

}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IndexRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool IndexCheckRecord (pRecord, ModIndex);
 *
 * Indexes the record with duplicate checks.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::IndexCheckRecord (CObRecord* pRecord, const dword ModIndex) {
  obdupformidinfo_t*	pFormIDInfo;
  obdupeditoridinfo_t*	pEditorIDInfo;
  CObIdRecord*		pIdRecord;
  bool			Result;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  Result = CheckDuplicateFormId(pRecord);

  if (Result) {
    pFormIDInfo = new obdupformidinfo_t;
    m_DuplicateFormIDs.Add(pFormIDInfo);
    pFormIDInfo->pRecord  = pRecord;
    pFormIDInfo->ModIndex = ModIndex;
  }
  else {
    m_FormIdMap.SetAt(pRecord);
  }

	/* Find an existing editorid */
  pIdRecord = ObCastClass(CObIdRecord, pRecord);

  if (pIdRecord != NULL) {
    Result = CheckDuplicateEditorId(pIdRecord);

    if (Result) {
      pEditorIDInfo = new obdupeditoridinfo_t;
      m_DuplicateEditorIDs.Add(pEditorIDInfo);
      pEditorIDInfo->pRecord  = pIdRecord;
      pEditorIDInfo->ModIndex = ModIndex;
    }
    else {
      m_EditorIdMap.SetAt(pIdRecord);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IndexCheckRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_IndexFileCallback (pRecord, UserData, pUserPtr);
 *
 * Callback used by the IndexFile() method.
 *
 *=========================================================================*/
int l_IndexFileCallback (CObRecord* pRecord, const dword UserData, void* pUserPtr) {
  obindexinfo_t* pInfo = (obindexinfo_t *) pUserPtr;
  int		 Result;

  if (pInfo == NULL) return (0);

  ++pInfo->RecordCount;

  if (pInfo->pCallback != NULL) {
    Result = pInfo->pCallback->UpdateCallback(pInfo->RecordCount);
    if (Result < 0) return (Result);
  }

  if (pInfo->FirstFile) 
    pInfo->pHandler->IndexCheckRecord(pRecord, pInfo->ModIndex);
  else
    pInfo->pHandler->IndexRecord(pRecord);

  return (0);
}
/*===========================================================================
 *		End of Function l_IndexFileCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool IndexFile (pFile, FirstFile, ModIndex, pCallback);
 *
 * Index all records in the given file. Also checks for, and handles, 
 * duplicate IDs if not the FirstFile.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::IndexFile (CObEspFile* pFile, const bool FirstFile, const dword ModIndex, CObCallback* pCallback) {
  obindexinfo_t IndexInfo;
  int		Result;

  IndexInfo.FirstFile   = FirstFile;
  IndexInfo.pHandler    = this;
  IndexInfo.ModIndex    = ModIndex;
  IndexInfo.pCallback   = pCallback;
  IndexInfo.RecordCount = 0;

  Result = pFile->ForEachRecord(l_IndexFileCallback, 0, &IndexInfo);
  if (Result < 0) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IndexFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool IndexRecords (pCallback);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::IndexRecords (CObCallback* pCallback) {
  dword MapSize;
  dword Index;
  bool  Result;

	/* Clear the current maps */
  m_FormIdMap.Destroy();
  m_EditorIdMap.Destroy();
  
  if (pCallback != NULL) {
    dword Count = CountAllRecords();
    pCallback->Reset();
    pCallback->SetLabel("Indexing records...");
    pCallback->SetTotalRecords(Count);
    pCallback->SetCallbackInterval(Count/100);
    pCallback->ForceCallback(0);
  }

	/* Get an estimated size for the maps */
  MapSize = (dword) ((CountAllRecords() + 1031) * 1.21);
  //MapSize /= 10;
  m_FormIdMap.InitHashTable(MapSize);
  m_EditorIdMap.InitHashTable(MapSize);

	/* Add special pseudo-records */
  m_FormIdMap.SetAt(&m_PlayerRef);

	/* Index all masters */
  for (Index = 0; Index < m_MasterFiles.GetSize(); ++Index) {
    Result = IndexFile(m_MasterFiles.GetAt(Index), Index == 0, Index, pCallback);
    if (!Result) return (false);
  }

	/* Index the active file */
  IndexFile(&m_ActiveFile, Index == 0, Index, pCallback);

	/* Handle any duplicates */
  HandleDuplicateFormIDs();
  HandleDuplicateEditorIDs();
  IndexDuplicates();

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IndexRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool LoadMasterFile (pFilename, ModIndex, pCallback);
 *
 * Attempts to load a new master file. Performs no other initialization.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::LoadMasterFile (const SSCHAR* pFilename, const dword ModIndex, CObCallback* pCallback) {
  CSString    Buffer;
  CObEspFile* pFile;
  bool        Result;

	/* Extract just the filename from the input full filename */
  Buffer = pFilename;
  Buffer.ReverseTruncate("\\:/");

	/* Special case for caching Oblivion.esm */
  if (ModIndex == 0 && Buffer.CompareNoCase(OB_GAME_MASTER) == 0) {
    m_MasterFiles.Add(&m_OblivionMaster);
    m_OblivionMaster.SetModIndex(0);
    m_OblivionMaster.SetParent(this);

    if (GetOptions().EnableCaching) {
      m_OblivionMaster.SetCacheFlags(OB_CACHE_DEFERLOAD);
    }

		/* Load the master if required */
    if (m_OblivionMaster.GetHeader() == NULL) {
      Result = m_OblivionMaster.Load(pFilename, pCallback);

      if (!Result) {
        m_OblivionMaster.Destroy();
        return (false);
      }
    }

    return (true);
  }

	/* Load a regular master file */
  pFile = AddMaster();
  if (pFile == NULL) return (false);
  //pFile->SetModIndex(ModIndex);

  Result = pFile->Load(pFilename);

  if (!Result) {
    m_MasterFiles.Delete(pFile); 
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::LoadMasterFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool Load (LoadInfo, pCallback);
 *
 * Loads a new set of masters and active plugin according to the input
 * information. Returns false on any error.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::Load (obfileloadinfo_t& LoadInfo, CObCallback* pCallback) {
  obtimer_t   Timer;
  obtimer_t   AllTimer;
  dword       Index;
  bool        Result;

	/* Clear the current information */
  Destroy();
  ObStartTimer(AllTimer);

	/* Load all masters, if any */
  for (Index = 0; Index < LoadInfo.m_MasterFilenames.GetSize(); ++Index) {
    Result = LoadMasterFile(*LoadInfo.m_MasterFilenames[Index], Index, pCallback);
    if (!Result) return (false);
  }

	/* Load the active plugin, if any */
  if (!LoadInfo.m_ActiveFilename.IsEmpty()) {
    m_ActiveFile.SetParent(this);

    Result = m_ActiveFile.Load(LoadInfo.m_ActiveFilename, pCallback);

    m_ActiveFile.SetActive(true);
    if (!Result) return (false);
  }
  else {
    m_ActiveFile.InitializeNew();
    m_ActiveFile.SetParent(this);
    m_ActiveFile.SetActive(true);
    SetActiveMasters();
  }

  ObStartTimer(Timer);

	/* Fixup the modindex of all formids */
  Result = FixupFormids();
  if (!Result) return (false);

  ObEndTimer(Timer, "Fixed up formids in ");
  ObStartTimer(Timer);

	/* Index all records */
  Result = IndexRecords(pCallback);
  if (!Result) return (false);

  ObEndTimer(Timer, "Indexed all records in ");
  ObStartTimer(Timer);

	/* Create the overall record tree */
  Result = CreateRecordTree(pCallback);
  if (!Result) return (false);

  ObEndTimer(Timer, "Created primary record/group tree in ");
  ObEndTimer(AllTimer, "Loaded and initialized all files in ");
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool MoveNewRecord (pRecord);
 *
 * Moves a new, unattached record, to the active file and record tree.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::MoveNewRecord (CObRecord* pRecord) {
  CObRefGroupArray GroupArray;
  CObGroup*        pMatchGroup;
  CObGroup*        pCurrentGroup;
  CObGroup*        pGroup;
  int  		   Index;
  bool		   Result;

	/* Attempt to move the given record in to the active file 
	   TODO: Won't work for all record types */
  Result = m_ActiveFile.AddRecord(pRecord);

  if (!Result) {
    SystemLog.Printf("Error adding record 0x%X to active file!", pRecord->GetFormID());
  }

  pRecord->SetParent(&m_ActiveFile);

  	/* Get the group heirarchy of the existing record */
  pGroup = pRecord->GetParentGroup();

  while (pGroup != NULL) {
    GroupArray.Add(pGroup);
    pGroup = pGroup->GetParentGroup();
  }

	/* Recreate the group heirarchy in the top level tree */
  pCurrentGroup = &m_TopFileGroup;

  for (Index = GroupArray.GetSize() -  1; Index >= 0; --Index) {
    pMatchGroup = GroupArray[Index];

    pGroup = pCurrentGroup->FindSubGroup(pMatchGroup);
    if (pGroup == NULL) pGroup = pCurrentGroup->CreateSubGroup(pMatchGroup);

    if (pGroup == NULL) {
      AddObGeneralError("Failed to recreate group heirarchy in overall group for new active record 0x%X!", pRecord->GetFormID());
      return (true); /* Must return true at this point */
    }

    pCurrentGroup = pGroup;
  }

	/* Add the record to the last created group */	
  pCurrentGroup->AddRecord(pRecord);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::MoveNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* MakeRecordActivePriv (pRecord, IndexRecord);
 *
 * Ensures the given record exists in the active file. If it already
 * does it is merely returned. It not, a copy of it is created in the 
 * active file and the index updated if needed.
 *
 * This is a protected class member. MakeRecordActive() is the public
 * accessible method.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::MakeRecordActivePriv (CObRecord* pRecord, const bool IndexRecord) {
  CObRecord*       pNewRecord;
  CObRefGroupArray GroupArray;
  CObGroup*        pMatchGroup;
  CObGroup*        pGroup;
  CObGroup*        pCurrentGroup;
  CObGroup*        pOverallGroup;
  CObGroup*        pGroup1;
  int		   Index;

	/* Ignore if already active */
  if (pRecord->IsActive()) return (pRecord);

	/* Create a copy of the given record */
  pNewRecord = CreateObRecord(pRecord->GetRecordType());
  pNewRecord->Copy(pRecord);
  pNewRecord->SetParent(&m_ActiveFile);
  pNewRecord->SetParentGroup(NULL);

	/* Get the group heirarchy of the existing record */
  pGroup = pRecord->GetParentGroup();

  while (pGroup != NULL) {
    GroupArray.Add(pGroup);
    pGroup = pGroup->GetParentGroup();
  }

	/* Recreate the group heirarchy in the active file and top level tree */
  pCurrentGroup = &m_ActiveFile.GetRecords();
  pOverallGroup = &m_TopFileGroup;

  for (Index = GroupArray.GetSize() -  1; Index >= 0; --Index) {
    pMatchGroup = GroupArray[Index];

    pGroup = pCurrentGroup->FindSubGroup(pMatchGroup);
    if (pGroup == NULL) pGroup = pCurrentGroup->CreateSubGroup(pMatchGroup);

    if (pGroup == NULL) {
      AddObGeneralError("Failed to recreate group heirarchy in active file for new active record 0x%X!", pNewRecord->GetFormID());
      delete pNewRecord;
      return (NULL);
    }

    if (pOverallGroup != NULL) {
      pGroup1 = pOverallGroup->FindSubGroup(pMatchGroup);
      if (pGroup1 == NULL) pGroup1 = pOverallGroup->CreateSubGroup(pMatchGroup);

      if (pGroup1 == NULL) {
        SystemLog.Printf("Failed to recreate group heirarchy in overall record tree for new active record 0x%X!",  pNewRecord->GetFormID());
      }
    }

    pCurrentGroup = pGroup;
    pOverallGroup = pGroup1;
  }

	/* Add the record to the last created group */	
  pCurrentGroup->GetRecords().Add(pNewRecord);
  pNewRecord->SetParentGroup(pCurrentGroup);

	/* Update the overall record tree if valid */
  if (pOverallGroup != NULL) {
    pOverallGroup->AddExistingRecord(pNewRecord);
  }
  
  m_ActiveFile.ModRecordCount(1);

	/* Update the index if needed */
  if (IndexRecord) {
    RemoveFromIndex(pRecord);
    this->IndexRecord(pNewRecord);
  }

  return (pNewRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::MakeRecordActivePriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool NewFile (void);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::NewFile (void) {
  Destroy();

  m_ActiveFile.InitializeNew();
  m_ActiveFile.SetActive(true);
  m_ActiveFile.AddMaster(OB_GAME_MASTER, 0);
  m_ActiveFile.SetModIndex(1);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::NewFile()
 *========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool DeleteNewRecord (pRecord);
 *
 * Deletes the given new record.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::DeleteNewRecord (CObRecord* pRecord) {
  return m_NewRecords.Delete(pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::DeleteNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool RemoveNewRecord (pRecord);
 *
 * Deletes the given new record.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::RemoveNewRecord (CObRecord* pRecord) {
  return (m_NewRecords.Remove(pRecord) != NULL);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::RemoveNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* PrepareNewRecord (RecordType);
 *
 * Prepares a new record for editing. Does not add the record to the
 * active file or the record tree. Returns NULL on any error.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::PrepareNewRecord (const obrectype_t RecordType) {
  CObRecord* pRecord;

  pRecord = CreateObRecord(RecordType);
  if (pRecord == NULL) return (NULL);

  m_NewRecords.Add(pRecord);

  pRecord->InitializeNew();
  pRecord->SetFormID(GetActiveFreeFormID());
  pRecord->SetParent(&m_ActiveFile);

  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PrepareNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Event - int OnCancelEditRecord (EditInfo);
 *
 *=========================================================================*/
int CObMultiRecordHandler::OnCancelEditRecord (obeditrecinfo_t& EditInfo) {

	/* Delete a new record that was cancelled */
  if (EditInfo.IsNew && !EditInfo.IsHandled) {
    DeleteNewRecord(EditInfo.pOldRecord);
    EditInfo.pOldRecord = NULL;
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObMultiRecordHandler::OnCancelEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Event - int OnPreSaveCheckEditorID (EditInfo);
 *
 *=========================================================================*/
int CObMultiRecordHandler::OnPreSaveCheckEditorID (obeditrecinfo_t& EditInfo) {
  CObIdRecord* pIdRecord;
  bool         Result;

	/* Prepare the editor ID string */
  Result = ObPrepareEditorID(EditInfo.NewEditorID);

  if (EditInfo.NewEditorID.IsEmpty()) {
    AddObGeneralError("Blank editor IDs are not allowed!");
    return (OB_RESULT_ERROR);
  }
  else if (!Result) {
    AddObGeneralError("The editor ID '%s' is not valid!", EditInfo.NewEditorID.c_str());
    return (OB_RESULT_ERROR);
  }

	/* Has the editor ID changed for an existing record? */
  if (EditInfo.pOldRecord != NULL && !EditInfo.IsNew) {
    pIdRecord = ObCastClass(CObIdRecord, EditInfo.pOldRecord);
    Result    = pIdRecord->IsEditorID(EditInfo.NewEditorID);
    EditInfo.HasUpdatedID = !Result;
  }

	/* Check for duplicate IDs */
  if ((EditInfo.HasUpdatedID || EditInfo.IsNew) && !EditInfo.IsHandled) {
    pIdRecord = FindEditorID(EditInfo.NewEditorID);

    if (pIdRecord != NULL && pIdRecord != EditInfo.pOldRecord) {
      AddObGeneralError("The editor ID '%s' is already in use!", EditInfo.NewEditorID.c_str());
      return (OB_RESULT_ERROR);
    }

		/* Prompt to rename or copy if required */
    if (EditInfo.HasUpdatedID && !EditInfo.IsNew && !EditInfo.IsHandled) return (OB_RESULT_PROMPTRENAMECOPY);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObMultiRecordHandler::OnPreSaveCheckEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Event - int OnPreSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CObMultiRecordHandler::OnPreSaveRecord (obeditrecinfo_t& EditInfo) {
  bool Result;

	/* Ensure the new record is active */
  if (EditInfo.pNewRecord == NULL) {
    Result = UpdateNewEditRecord(EditInfo);
    if (!Result) return (OB_RESULT_ERROR);
  }

	/* Create the undo action for the update */
  if (EditInfo.IsNew || EditInfo.IsCopy) {
    CreateUndoAdd(EditInfo);
  }
  else {
    CreateUndoUpdate(EditInfo);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObMultiRecordHandler::OnPreSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Event - int OnPostSaveRecord (EditInfo);
 *
 *=========================================================================*/
int CObMultiRecordHandler::OnPostSaveRecord (obeditrecinfo_t& EditInfo) {

	/* Update any indices if required */
  if (EditInfo.NeedsIndex) {
    RemoveFromIndex(EditInfo.pOldRecord);
    IndexRecord(EditInfo.pNewRecord);
  }

	/* Call update listeners */
  if (EditInfo.IsNew || EditInfo.IsCopy) {
    m_EventHandler.SendAddEvent(EditInfo.pNewRecord, EditInfo.pOldRecord);
  }
  else {
    m_EventHandler.SendUpdateEvent(EditInfo.pNewRecord, EditInfo.pOldRecord);
  }

  return (OB_RESULT_OK);
}
/*===========================================================================
 *		End of Class Event CObMultiRecordHandler::OnPostSaveRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool RemoveFromIndex (pRecord);
 *
 * Removes the given record from all indexes.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::RemoveFromIndex (CObRecord* pRecord) {
  CObIdRecord* pIdRecord;

  if (pRecord == NULL) return (true);
  pIdRecord = ObCastClass(CObIdRecord, pRecord);

  m_FormIdMap.Delete(pRecord);
  if (pIdRecord != NULL) m_EditorIdMap.Delete(pIdRecord);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::RemoveFromIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool RenameIDRecord(pRecord, pNewEditorID);
 *
 * Renames the editorid for the given ID record. Public method that calls
 * the necessary listeneres and creates an undo item. Returns false on
 * any error.
 *
 * Assumes a valid editorid input.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::RenameIDRecord (CObIdRecord* pRecord, const SSCHAR* pNewEditorID) {
  CObIdRecord* pNewRecord;
  
	/* Ignore invalid input */
  if (pRecord == NULL || pNewEditorID == NULL) return (false);

	/* Preupdate the listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord, 0);

	/* Rename the record */
  pNewRecord = RenameIDRecordPriv(pRecord, pNewEditorID, true);
  if (pNewRecord == NULL) return (false);

  	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::RenameIDRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObIdRecord* RenameIDRecordPriv (pRecord, pNewEditorID, CreateUndo);
 *
 * Renames the editorid for the given record. Assumes a valid editorid input.
 * Protected class method.
 *
 *=========================================================================*/
CObIdRecord* CObMultiRecordHandler::RenameIDRecordPriv (CObIdRecord* pRecord, const SSCHAR* pNewEditorID, const bool CreateUndo) {
  CObRecord*      pNewRecord;
  CObIdRecord*    pNewIdRecord;
  obeditrecinfo_t EditInfo;

  	/* Remove the record from the current index */
  RemoveFromIndex(pRecord);

	/* Ensure the given record exists the active file */
  pNewRecord = MakeRecordActivePriv(pRecord, false);
  if (pNewRecord == NULL) return (NULL);
  pNewIdRecord = ObCastClass(CObIdRecord, pNewRecord);
  
  	/* Create the undo item */
  if (CreateUndo) {
    EditInfo.pNewRecord   = pNewRecord;
    EditInfo.pOldRecord   = pRecord;
    EditInfo.NewEditorID  = pNewEditorID;
    EditInfo.HasUpdatedID = true;
    EditInfo.IsRenamed    = true;
    CreateUndoUpdate(EditInfo);
  }

	/* Update the record and re-index */
  if (pNewIdRecord != NULL) pNewIdRecord->SetEditorID(pNewEditorID);
  IndexRecord(pNewRecord);

  return (pNewIdRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::RenameIDRecordPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool SetActiveMasters (void);
 *
 * Sets the masters of the active file according to the current list.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::SetActiveMasters (void) {
  CObTes4Record* pHeader;
  CSString	 Buffer;
  dword		 Index;

  pHeader = m_ActiveFile.GetHeader();
  if (pHeader == NULL) return (false);
  pHeader->DeleteMasters();

	/* Add all masters in their current order */
  for (Index = 0; Index < m_MasterFiles.GetSize(); ++Index) {
    Buffer = m_MasterFiles[Index]->GetFilename();
    Buffer.ReverseTruncate(":\\/");
    pHeader->AddMaster(Buffer, 0);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::SetActiveMasters()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* ToggleQuestFlag (pRecord);
 *
 * Toggles the quest flag on the given record. Returns the updated record
 * or NULL on any error.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::ToggleQuestFlag (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Create the undo event */
  CreateUndoUpdate(pRecord);

  	/* Update listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Ensure the record is in the active file */
  pNewRecord = MakeRecordActivePriv(pRecord, true);
  if (pNewRecord == NULL) return (NULL);

	/* Toggle the flag */
  pNewRecord->SetQuestItem(!pNewRecord->IsQuestItem());

	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (pNewRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ToggleQuestFlag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* ToggleDeleteFlag (pRecord);
 *
 * Toggles the deleted flag on the given record. Returns the updated record
 * or NULL on any error.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::ToggleDeleteFlag (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Create the undo event */
  CreateUndoUpdate(pRecord);

	/* Update listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Ensure the record is in the active file */
  pNewRecord = MakeRecordActivePriv(pRecord, true);
  if (pNewRecord == NULL) return (NULL);

	/* Toggle the flag */
  pNewRecord->SetDeleted(!pNewRecord->IsDeleted());

	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ToggleDeleteFlag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObRecord* ToggleIgnoreFlag (pRecord);
 *
 * Toggles the ignored flag on the given record. Returns the updated record
 * or NULL on any error.
 *
 *=========================================================================*/
CObRecord* CObMultiRecordHandler::ToggleIgnoreFlag (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Create the undo event */
  CreateUndoUpdate(pRecord);

	/* Update listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Ensure the record is in the active file */
  pNewRecord = MakeRecordActivePriv(pRecord, true);
  if (pNewRecord == NULL) return (NULL);

	/* Toggle the flag */
  pNewRecord->SetIgnored(!pNewRecord->IsIgnored());

	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::ToggleIgnoreFlag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool UpdateRecordTree (pNewRecord, pOldRecord);
 *
 * Updates the overall record tree item for the given record. If the new
 * record is NULL the record is removed from the tree.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::UpdateRecordTree (CObRecord* pNewRecord, CObRecord* pOldRecord) {
  CObRefGroupArray GroupArray;
  CObGroup*        pCurrentGroup;
  CObGroup*        pMatchGroup;
  CObGroup*        pGroup;
  int              Index;
  bool		   Result;

	/* Ignore invalid input */
  if (pOldRecord == NULL) return (false);

	/* Get the group heirarchy of the old record */
  pGroup = pOldRecord->GetParentGroup();

  while (pGroup != NULL) {
    GroupArray.Add(pGroup);
    pGroup = pGroup->GetParentGroup();
  }

	/* Find the record in the overall record tree */
  pCurrentGroup = &m_TopFileGroup;

  for (Index = GroupArray.GetSize() -  1; Index >= 0; --Index) {
    pMatchGroup = GroupArray[Index];

    pGroup = pCurrentGroup->FindSubGroup(pMatchGroup);
    if (pGroup == NULL) pGroup = pCurrentGroup->CreateSubGroup(pMatchGroup);

    if (pGroup == NULL) {
      return AddObGeneralError("Failed to update group heirarchy for record 0x%X!", pOldRecord->GetFormID());
    }

    pCurrentGroup = pGroup;
  }

	/* Remove the old record from the group */
  Result = pCurrentGroup->DeleteRecord(pOldRecord);
  if (!Result) AddObGeneralError("Failed to delete the old version of record 0x%X!", pOldRecord->GetFormID());
  
	/* Add the new record if it exists */
  if (pNewRecord != NULL) pCurrentGroup->AddRecord(pNewRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::UpdateRecordTree()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool UpdateNewEditRecord (EditRecInfo);
 *
 * Creates or updates the new record in the given edit structure depending
 * on how the record is being updated. Returns false on any error.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::UpdateNewEditRecord (obeditrecinfo_t& EditRecInfo) {
  bool Result;

	/* Ignore if the record has already been handled */
  if (EditRecInfo.IsHandled) return (true);

	/* Create a new record */
  if (EditRecInfo.IsNew) {

    	 	/* Move new record into the active file and tree */
    Result = MoveNewRecord(EditRecInfo.pOldRecord);
    if (!Result) return (false);

    m_NewRecords.Remove(EditRecInfo.pOldRecord);
    EditRecInfo.pNewRecord   = EditRecInfo.pOldRecord;
    EditRecInfo.IsNew        = true;
    EditRecInfo.HasUpdatedID = true;
    EditRecInfo.IsHandled    = true;
    EditRecInfo.NeedsIndex   = true;
  }
  else if (EditRecInfo.IsCopy) {
    EditRecInfo.pNewRecord = CreateObRecord(EditRecInfo.pOldRecord->GetRecordType());
    m_NewRecords.Add(EditRecInfo.pNewRecord);

    EditRecInfo.pNewRecord->Copy(EditRecInfo.pOldRecord);
    EditRecInfo.pNewRecord->SetFormID(GetActiveFreeFormID());

    Result = MoveNewRecord(EditRecInfo.pNewRecord);

    if (!Result) {
      EditRecInfo.pNewRecord = NULL;
      m_NewRecords.Delete(EditRecInfo.pNewRecord);
      return (false);
    }

    m_NewRecords.Remove(EditRecInfo.pNewRecord);
    EditRecInfo.IsHandled  = true;
    EditRecInfo.NeedsIndex = true;
  }
	/* Ensure the record is active */
  else {
    EditRecInfo.pNewRecord = MakeRecordActivePriv(EditRecInfo.pOldRecord, false);
    if (EditRecInfo.pNewRecord == NULL) return (false);

    if (EditRecInfo.pNewRecord != EditRecInfo.pOldRecord) EditRecInfo.NeedsIndex = true;
    if (EditRecInfo.HasUpdatedID) EditRecInfo.NeedsIndex = true;
    EditRecInfo.IsHandled = true;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::UpdateNewEditRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObUndoItem* CreateUndoClean (pRecord);
 *
 *=========================================================================*/
CObUndoItem* CObMultiRecordHandler::CreateUndoClean (CObRecord* pRecord) {
  CObUndoItem* pUndoItem;

	/* Ignore invalid input or if not undoing */
  if (pRecord == NULL || !m_Options.Undo.EnableUndo) return (NULL);

	/* Create a new undo object */
  pUndoItem = new CObUndoItem;
  m_UndoItems.Add(pUndoItem);

	/* Initialize the undo object */
  pUndoItem->SetActionType(OB_UNDOTYPE_CLEANRECORD);
  pUndoItem->CopyRecord(pRecord);

  TrimUndoItems();
  return (pUndoItem);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateUndoClean()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObUndoItem* CreateUndoAdd (EditInfo);
 *
 *=========================================================================*/
CObUndoItem* CObMultiRecordHandler::CreateUndoAdd (obeditrecinfo_t& EditInfo) {
  CObUndoItem* pUndoItem;

	/* Ignore invalid input or if not undoing */
  if (EditInfo.pNewRecord == NULL || !m_Options.Undo.EnableUndo) return (NULL);

	/* Create a new undo object */
  pUndoItem = new CObUndoItem;
  m_UndoItems.Add(pUndoItem);

	/* Initialize the undo object */
  pUndoItem->SetActionType(OB_UNDOTYPE_ADDRECORD);
  pUndoItem->CopyRecord(EditInfo.pNewRecord);
  pUndoItem->SetNewEditorID(EditInfo.NewEditorID);

  TrimUndoItems();
  return (pUndoItem);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateUndoAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObUndoItem* CreateUndoAdd (pRecord, pNewEditorID);
 *
 *=========================================================================*/
CObUndoItem* CObMultiRecordHandler::CreateUndoAdd (CObRecord* pRecord, const char* pNewEditorID) {
  CObUndoItem* pUndoItem;

	/* Ignore invalid input or if not undoing */
  if (pRecord == NULL || pNewEditorID == NULL || !m_Options.Undo.EnableUndo) return (NULL);

	/* Create a new undo object */
  pUndoItem = new CObUndoItem;
  m_UndoItems.Add(pUndoItem);

	/* Initialize the undo object */
  pUndoItem->SetActionType(OB_UNDOTYPE_ADDRECORD);
  pUndoItem->CopyRecord(pRecord);
  pUndoItem->SetNewEditorID(pNewEditorID);

  TrimUndoItems();
  return (pUndoItem);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateUndoAdd()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObUndoItem* CreateUndoUpdate (pRecord);
 *
 *=========================================================================*/
CObUndoItem* CObMultiRecordHandler::CreateUndoUpdate (CObRecord* pRecord) {
  CObUndoItem* pUndoItem;

	/* Ignore invalid input or if not undoing */
  if (pRecord == NULL || !m_Options.Undo.EnableUndo) return (NULL);

	/* Create a new undo object */
  pUndoItem = new CObUndoItem;
  m_UndoItems.Add(pUndoItem);

	/* Initialize the undo object */
  pUndoItem->SetActionType(OB_UNDOTYPE_UPDATERECORD);
  pUndoItem->CopyRecord(pRecord);

  TrimUndoItems();
  return (pUndoItem);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateUndoUpdate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - CObUndoItem* CreateUndoUpdate (EditRecInfo);
 *
 *=========================================================================*/
CObUndoItem* CObMultiRecordHandler::CreateUndoUpdate (obeditrecinfo_t& EditRecInfo) {
  CObUndoItem* pUndoItem;

	/* Ignore invalid input or if not undoing */
  if (!m_Options.Undo.EnableUndo) return (NULL);

  	/* Create a new undo object */
  pUndoItem = new CObUndoItem;
  m_UndoItems.Add(pUndoItem);

	/* Initialize the undo object */
  pUndoItem->CreateUndoInfo(EditRecInfo);
  pUndoItem->SetActionType(OB_UNDOTYPE_UPDATERECORD);

  TrimUndoItems();
  return (pUndoItem);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateUndoUpdate()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformUndo (void);
 *
 * Performs the last undo item if any. Returns true if the undo was
 * performed successfully.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformUndo (void) {
  CObUndoItem*  pUndoItem;
  bool		Result;

	/* Ignore if nothing to undo */
  if (m_UndoItems.GetSize() == 0) return (false);

  pUndoItem = m_UndoItems.Remove(m_UndoItems.GetSize() - 1);

  Result = PerformUndo(pUndoItem);

  delete pUndoItem;
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformUndo (pUndoItem);
 *
 * Performs the given undo action and returns true if successful.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformUndo (CObUndoItem* pUndoItem) {

	/* Ignore invalid input */
  if (pUndoItem == NULL) return (false);

  switch (pUndoItem->GetActionType()) {
    case OB_UNDOTYPE_ADDRECORD:    return PerformAddUndo(pUndoItem);
    case OB_UNDOTYPE_CLEANRECORD:  return PerformCleanUndo(pUndoItem);
    case OB_UNDOTYPE_UPDATERECORD: return PerformUpdateUndo(pUndoItem);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformAddUndo (pUndoItem);
 *
 * Attempts to perform the given add undo item, returning true on success.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformAddUndo (CObUndoItem* pUndoItem) {
  CObRecord* pRecord;

	/* Ignore invalid input */
  if (pUndoItem == NULL) return (false);

  if (pUndoItem->GetRecord() != NULL) {
    pRecord = FindFormID(pUndoItem->GetRecord()->GetFormID());

    if (pRecord == NULL) {
      AddObGeneralError("Failed to find the record 0x%X for the undo add command!", pUndoItem->GetRecord()->GetFormID());
      return (false);
    }

		/* Update listeners */
    m_EventHandler.SendPreUpdateEvent(pRecord);

    RemoveFromIndex(pRecord);
    UpdateRecordTree(NULL, pRecord);

		/* Update listeners */
    m_EventHandler.SendCleanEvent(NULL, pRecord);

    m_ActiveFile.DeleteRecord(pRecord);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformAddUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformCleanUndo (pUndoItem);
 *
 * Attempts to perform the given clean undo item, returning true on success.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformCleanUndo (CObUndoItem* pUndoItem) {
  CObRecord* pRecord;
  CObRecord* pNewRecord;
  bool       Result;

	/* Ignore invalid input */
  if (pUndoItem == NULL) return (false);
  if (pUndoItem->GetRecord() == NULL) return (false);

	/* Find an existing version of the record */
  pRecord = FindFormID(pUndoItem->GetRecord()->GetFormID()); 

	/* Add a new record */
  if (pRecord == NULL) {
    pRecord = pUndoItem->GetRecord();

    Result = MoveNewRecord(pRecord);
    if (!Result) return (false);

    IndexRecord(pRecord);
    pUndoItem->SetRecord(NULL);

    		/* Update listeners */
    m_EventHandler.SendAddEvent(pRecord, NULL);
    return (true);
  }

	/* Update all listeners */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Update an existing record */
  RemoveFromIndex(pRecord);

  pNewRecord = MakeRecordActivePriv(pRecord, false);
  pNewRecord->Destroy();
  pNewRecord->Copy(pUndoItem->GetRecord());

  IndexRecord(pNewRecord);

	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformCleanUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformUpdateUndo (pUndoItem);
 *
 * Attempts to perform the given update undo item, returning true on success.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformUpdateUndo (CObUndoItem* pUndoItem) {
  CObRecord* pRecord;
  CObRecord* pOldRecord;

	/* Ignore invalid input */
  if (pUndoItem == NULL) return (false);
  
	/* Delete a record copy (must be a new record) */
  if (pUndoItem->IsCopy()) {
    pRecord = FindFormID(pUndoItem->GetNewFormID());
    if (pRecord == NULL) return AddObGeneralError("Cannot find copied record 0x%X to undo!", pUndoItem->GetNewFormID());

		/* Update listeners */
    m_EventHandler.SendPreUpdateEvent(pRecord);
    
    RemoveFromIndex(pRecord);
    UpdateRecordTree(NULL, pRecord);

		/* Update listeners */
    m_EventHandler.SendCleanEvent(NULL, pRecord);

    m_ActiveFile.DeleteRecord(pRecord);
    return (true);
  }

	/* Ensure a valid record to undo */
  if (pUndoItem->GetRecord() == NULL) return (false);
  pRecord = FindFormID(pUndoItem->GetRecord()->GetFormID());

  if (pRecord == NULL) {
    AddObGeneralError("Cannot find updated record 0x%X to undo!", pUndoItem->GetRecord()->GetFormID());
    return (false);
  }

	/* Undo from active to active */
  if (pUndoItem->GetRecord()->IsActive()) {

    		/* Update listeners */
    m_EventHandler.SendPreUpdateEvent(pRecord);

    RemoveFromIndex(pRecord);
    pRecord->Copy(pUndoItem->GetRecord());
    IndexRecord(pRecord);

	/* Update listeners */
    m_EventHandler.SendUpdateEvent(pRecord, pRecord);
    return (true);
  }
  
	/* Update from active to non-active */
  m_EventHandler.SendPreUpdateEvent(pRecord);

  pOldRecord = FindNonActiveRecord(pRecord);
  RemoveFromIndex(pRecord);
  UpdateRecordTree(pOldRecord, pRecord);
  if (pOldRecord != NULL) IndexRecord(pOldRecord);

  	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pOldRecord, pRecord);

  m_ActiveFile.DeleteRecord(pRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformUpdateUndo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool PerformUndoTo (pUndoItem);
 *
 *=========================================================================*/
bool CObMultiRecordHandler::PerformUndoTo (CObUndoItem* pUndoItem) {
  CObUndoItem* pItem;
  int	       Index;
  int          ItemIndex;
  
	/* Find the item in the list */
  ItemIndex = m_UndoItems.Find(pUndoItem);
  if (ItemIndex < 0) return (false);

  for (Index = (int) m_UndoItems.GetSize() - 1; Index >= ItemIndex; --Index) {
    pItem = m_UndoItems.Remove(Index);

    PerformUndo(pItem);

    delete pItem;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::PerformUndoTo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - void TrimUndoItems (void);
 *
 * Removes any undo items over the undo limit.
 *
 *=========================================================================*/
void CObMultiRecordHandler::TrimUndoItems (void) {

	/* Special case for a very low limit */
  if (GetOptions().Undo.UndoLimit <= 2 && m_UndoItems.GetSize() <= 2) return;
  if (m_UndoItems.GetSize() < GetOptions().Undo.UndoLimit) return;

	/* Just remove the first item in the list */
  m_UndoItems.Delete((dword)0);
  
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::TrimUndoItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool MakeRecordActive (pRecord);
 *
 * Moves the given record to the active file if required. Listeners
 * are updated as needed. False is returned on any error.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::MakeRecordActive (CObRecord* pRecord) {
  CObRecord* pNewRecord;

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

	/* Ignore a record that is already active */
  if (pRecord->IsActive()) return (true);

	/* Update listeneres */
  m_EventHandler.SendPreUpdateEvent(pRecord);

	/* Create undo item */
  CreateUndoUpdate(pRecord);

	/* Perform the move */
  pNewRecord = MakeRecordActivePriv(pRecord, true);
  if (pNewRecord == NULL) return (false);

	/* Update listeners */
  m_EventHandler.SendUpdateEvent(pNewRecord, pRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::MakeRecordActive()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool IsValidNewEditorID (pEditorID);
 *
 * Returns true if the given editorid is valid and not currently in use.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::IsValidNewEditorID (const char* pEditorID) {
  CObIdRecord* pRecord;

	/* Ensure a non-empty string */
  if (pEditorID == NULL || *pEditorID == NULL_CHAR) {
    return AddObGeneralError("Null or empty editorids are not allowed!");
  }

	/* Find an existing record */
  pRecord = FindEditorID(pEditorID);

  if (pRecord != NULL) {
    return AddObGeneralError("The editorid '%s' is already in use (record 0x%08X, type %4.4s)!", pEditorID, pRecord->GetFormID(), pRecord->GetRecordType().Name);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::IsValidNewEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMultiRecordHandler Method - bool CreateIDRecordCopy (pRecord, pEditorID);
 *
 * Creates a new copy of the given record. Assumes the input editorid is
 * valid.
 *
 *=========================================================================*/
bool CObMultiRecordHandler::CreateIDRecordCopy (CObIdRecord* pRecord, const char* pEditorID) {
  CObRecord*	pNewRecord;
  CObIdRecord*	pNewIdRecord;
  bool		Result;

	/* Ensure valid input */
  if (pRecord == NULL || pEditorID == NULL) return (false);

	/* Create the new record */
  pNewRecord = CreateObRecord(pRecord->GetRecordType());
  if (pNewRecord == NULL) return (false);
  pNewIdRecord = ObCastClass(CObIdRecord, pNewRecord);

  	/* Create the copy */
  pNewRecord->Copy(pRecord);
  
	/* Move the record into the active file and record tree */
  Result = MoveNewRecord(pNewRecord);
  if (!Result) return (false);

	/* Update the new record IDs */
  pNewRecord->SetFormID(GetActiveFreeFormID());

  if (pNewIdRecord != NULL) {
    pNewIdRecord->SetEditorID(pEditorID);
  }

  IndexRecord(pNewRecord);

  CreateUndoAdd(pNewRecord, pEditorID);
  m_EventHandler.SendAddEvent(pNewRecord, NULL, 0);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObMultiRecordHandler::CreateIDRecordCopy()
 *=========================================================================*/



