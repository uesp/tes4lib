/*===========================================================================
 *
 * File:	Obgroup.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obgroup.h"
#include "../records/obrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Class CObGroup Constructor
 *
 *=========================================================================*/
CObGroup::CObGroup (const bool UseRef) {
  //SystemLog.Printf("pRecords = %p", m_pRecords);
  m_IsReferenced = UseRef;

  if (UseRef)
    m_pRecords = new CObRefBaseRecordCont;
  else
    m_pRecords = new CObBaseRecordCont;

  if (m_pRecords == NULL) throw "Invalid Record Array";

  memset(&m_Header, 0, sizeof(m_Header));
  m_Header.RecordType = OB_NAME_GRUP;
}
/*===========================================================================
 *		End of Class CObGroup Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Destructor
 *
 *=========================================================================*/
CObGroup::~CObGroup () {

  if (m_pRecords != NULL) {
    m_pRecords->Destroy();
    delete m_pRecords;
    m_pRecords = NULL;
  }

}
/*===========================================================================
 *		End of Class CObGroup Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - void Destroy (void);
 *
 * Delete object contents.
 *
 *=========================================================================*/
void CObGroup::Destroy (void) {

  memset(&m_Header, 0, sizeof(m_Header));
  m_pRecords->Destroy();

}
/*===========================================================================
 *		End of Class Method CObGroup::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool AddExistingRecord (pNewRecord);
 *
 * Adds a record to the group that may already exist in the group. If it
 * does already exist the existing record is updated and the previous record
 * deleted if required. If not, a new record is added to the end of the group.
 *
 *=========================================================================*/
bool CObGroup::AddExistingRecord (CObRecord* pNewRecord) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  dword          Index;

	/* Ignore invalid input */
  if (pNewRecord == NULL) return (false);

	/* Look for a matching existing record in the group by formid */
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    pRecord     = ObCastRecord(pBaseRecord);
    if (pRecord == NULL) continue;

    if (pRecord->GetFormID() == pNewRecord->GetFormID()) {

		/* Delete the existing record if needed */
      if (!m_IsReferenced) {
        delete pRecord;
      }

      m_pRecords->SetAt(Index, pNewRecord);
      return (true);
    }
  }

	/* Add a new record */
  m_pRecords->Add(pNewRecord);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObGroup::AddExistingRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObGroup::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
  CObBaseRecord* pBaseRecord;
  dword          Index;
  dword          Count = 0;

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    Count += pBaseRecord->ChangeFormID(NewID, OldID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObGroup::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - dword ChangeEditorID (pNewID, pOldID);
 *
 *=========================================================================*/
dword CObGroup::ChangeEditorID (const SSCHAR* pNewID, const SSCHAR* pOldID) {
  CObBaseRecord* pBaseRecord;
  dword          Index;
  dword          Count = 0;

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    Count += pBaseRecord->ChangeEditorID(pNewID, pOldID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObGroup::ChangeEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool Compare (pGroup);
 *
 *=========================================================================*/
bool CObGroup::Compare (CObGroup* pGroup) {

  if (pGroup == NULL) return (false);
  if (m_Header.GroupType != pGroup->GetType()) return (false);

	/* Just compare the raw 4 bytes of data */
  if (m_Header.Data.ParentFormID != pGroup->GetHeader().Data.ParentFormID) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObGroup::Compare()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - CObGroup* CreateSubGroup (pMatchGroup);
 *
 * Creates and returns a new subgroup that matches the input group.
 *
 *=========================================================================*/
CObGroup* CObGroup::CreateSubGroup (CObGroup* pMatchGroup) {
  CObGroup* pGroup;

	/* Ignore invalid input */
  if (pMatchGroup == NULL) return (NULL);

	/* Create a new subgroup */
  if (m_IsReferenced)
    pGroup = CreateObRefGroup(pMatchGroup->GetType());
  else
    pGroup = CreateObGroup(pMatchGroup->GetType());

  m_pRecords->Add(pGroup);

	/* Copy the group type specific header data */
  pGroup->GetHeader().Data.ParentFormID = pMatchGroup->GetHeader().Data.ParentFormID;

  return (pGroup);
}
/*===========================================================================
 *		End of Class Method CObGroup::CreateSubGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - dword Find (FindCount, FindData, pCallback);
 *
 *=========================================================================*/
bool CObGroup::Find (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  dword		 Count;
  dword		 Index;
  bool		 IsExcluded;
  bool		 Result;
  int		 iResult;

  FindCount = 0;
  ++FindData.GroupCount;

	/* Look in the group header if required */
  if ((FindData.Flags & OB_FIND_GROUPHEADER) != 0) {
    Count      = ObFindData((const byte *) &m_Header, sizeof(m_Header), FindData);
    if (Count && (FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\tFound match in group header!");
    FindCount += Count;
  }
  
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pRecord) IsExcluded = ObContainsRecordType(pRecord->GetRecordType(), FindData.pExcludeRecords);

    if (pRecord == NULL || !IsExcluded) {
       Result = pBaseRecord->Find(Count, FindData, pCallback);
       FindCount += Count;
       if (!Result) return (false);
    }

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(pCallback->GetProcessRecords() + 1);
      if (iResult < 0) return (false);
    }
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObGroup::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool FindText (FindCount, FindData, pCallback);
 *
 *=========================================================================*/
bool CObGroup::FindText (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  dword		 Count;
  dword		 Index;
  bool		 IsExcluded;
  bool		 Result;
  int		 iResult;

  FindCount = 0;
  ++FindData.GroupCount;

	/* Look in the group header if required */
  if ((FindData.Flags & OB_FIND_GROUPHEADER) != 0) {
    Count      = ObFindTextData((const byte *) &m_Header, sizeof(m_Header), FindData);
    if (Count && (FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\tFound match in group header!");
    FindCount += Count;
  }
  
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pRecord) IsExcluded = ObContainsRecordType(pRecord->GetRecordType(), FindData.pExcludeRecords);

    if (pRecord == NULL || !IsExcluded) {
       Result = pBaseRecord->FindText(Count, FindData, pCallback);
       FindCount += Count;
       if (!Result) return (false);
    }

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(pCallback->GetProcessRecords() + 1);
      if (iResult < 0) return (false);
    }
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObGroup::FindText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - CObBaseRecord* FindFormID (FormID);
 *
 * Find a child record based on its form ID. Returns NULL if not found.
 *
 *=========================================================================*/
CObBaseRecord* CObGroup::FindFormID (const obformid_t FormID) {
  CObBaseRecord* pRecord;
  dword		 Index;

	/* Ignore invalid input */
  if (FormID == OB_FORMID_NULL) return (NULL);

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    //SystemLog.Printf("      Record: %d = 0x%08lX (0x%08lX)", Index, m_Records[Index]->GetFormID(), FormID);

    pRecord = m_pRecords->GetAt(Index)->FindFormID(FormID);
    if (pRecord != NULL) return (pRecord);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObGroup::FindFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - CObGroup* FindNextGroup (FormID, GroupPos);
 *
 *=========================================================================*/
CObGroup* CObGroup::FindNextGroup (const obformid_t FormID, int& GroupPos) {
  CObGroup* pGroup;

  for (++GroupPos; GroupPos < (int) m_pRecords->GetSize(); ++GroupPos) {
    pGroup = ObCastClass(CObGroup, m_pRecords->GetAt(GroupPos));
    if (pGroup == NULL) continue;

    switch (pGroup->GetType()) {
	case OB_GROUP_WORLDCHILD:
	case OB_GROUP_CELLCHILD:
	case OB_GROUP_TOPICCHILD:
	case OB_GROUP_CELLPERSIST:
	case OB_GROUP_CELLTEMP:
	case OB_GROUP_CELLDISTANT:
		if (FormID == OB_FORMID_NULL) return (pGroup);
		if (pGroup->GetHeader().Data.ParentFormID == FormID) return (pGroup);
		break;
    }
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObGroup::FindNextGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - CObGroup* FindSubGroup (pMatchGroup);
 *
 * Find a subgroup in the current group that matches the given input. 
 * Returns NULL if not found.
 *
 *=========================================================================*/
CObGroup* CObGroup::FindSubGroup (CObGroup* pMatchGroup) {
  CObBaseRecord* pBaseRecord;
  CObGroup*      pGroup;
  dword          Index;

  	/* Ignore invalid input */
  if (pMatchGroup == NULL) return (NULL);

	/* Check all existing subgroups */
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    pGroup      = ObCastGroup(pBaseRecord);
    if (pGroup == NULL) continue;

    if (pGroup->Compare(pMatchGroup)) return (pGroup);
  }

	/* No match found */
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObGroup::FindSubGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool FixupFormids (FixupArray);
 *
 *=========================================================================*/
bool CObGroup::FixupFormids (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    Result &= m_pRecords->GetAt(Index)->FixupFormids(FixupArray);
  }
  
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObGroup::FixupFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - int ForEachBaseRecord (Callback, UserData, pUserPtr);
 *
 * Iterates through all base records in the file and calls the given 
 * callback function for each one. 
 *
 *=========================================================================*/
int CObGroup::ForEachBaseRecord (OBBASERECORDCALLBACK Callback, const dword UserData, void* pUserPtr) {
  CObBaseRecord* pBaseRecord;
  CObGroup*	 pGroup;
  dword          Index;
  int            Result;

	/* Ensure valid input */
  if (Callback == NULL) return (0);

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);

    Result = Callback(pBaseRecord, UserData, pUserPtr);
    if (Result < 0) return (Result);

		/* Call each record in the group record */
    pGroup = ObCastClass(CObGroup, pBaseRecord);

    if (pGroup != NULL) {
      Result = pGroup->ForEachBaseRecord(Callback, UserData, pUserPtr);
      if (Result < 0) return (Result);
    }
  }  

  return (0);
}
/*===========================================================================
 *		End of Class Method CObGroup::ForEachBaseRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - int ForEachRecord (Callback, UserData, pUserPtr);
 *
 * Iterates through all records in the file and calls the given 
 * callback function for each one. 
 *
 *=========================================================================*/
int CObGroup::ForEachRecord (OBRECORDCALLBACK Callback, const dword UserData, void* pUserPtr) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  CObGroup*	 pGroup;
  dword          Index;
  int            Result;

	/* Ensure valid input */
  if (Callback == NULL) return (0);

  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pBaseRecord = m_pRecords->GetAt(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pRecord != NULL) {
      Result = Callback(pRecord, UserData, pUserPtr);
      if (Result < 0) return (Result);
    }
    else {

		/* Call each record in the group record */
      pGroup = ObCastClass(CObGroup, pBaseRecord);

      if (pGroup != NULL) {
        Result = pGroup->ForEachRecord(Callback, UserData, pUserPtr);
        if (Result < 0) return (Result);
      }
    }

  }  

  return (0);
}
/*===========================================================================
 *		End of Class Method CObGroup::ForEachRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - CObTypeGroup* GetTypeGroup (Type);
 *
 *=========================================================================*/
CObTypeGroup* CObGroup::GetTypeGroup (const obrectype_t Type) {
  CObBaseRecord* pRecord;
  CObGroup*	 pGroup;
  CObTypeGroup*	 pTypeGroup;
  dword		 Index;

	/* Search all top level groups for a match */
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pRecord = m_pRecords->GetAt(Index);

    if (!pRecord->IsGroup()) continue;
    pGroup = ObCastClass(CObGroup, pRecord);
    if (pGroup == NULL) continue;
    if (pGroup->GetType() != OB_GROUP_TYPE) continue;
    pTypeGroup = ObCastClass(CObTypeGroup, pGroup);
    if (pTypeGroup == NULL) continue;

    if (Type == pTypeGroup->GetContainsType()) return (pTypeGroup);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObGroup::GetTypeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool ReadData (File, pCallback);
 *
 * Reads in group data from the current location in the given file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObGroup::ReadData (CObFile& File, CObCallback* pCallback) {
  obbaseheader_t    Header;
  CObBaseRecord*    pBaseRecord;
  bool		    Result;
  int		    CurrentOffset;
  int		    EndOffset;
  int		    iResult;

	/* Get the start of the data */
  Result = File.Tell(CurrentOffset);
  if (!Result) return (false);
  EndOffset = CurrentOffset + m_Header.Size - OB_BASEHEADER_SIZE;

	/* Read until the end of the data is reached */
  while (CurrentOffset < EndOffset) {
  
		/* Input the record header */
    Result = ReadObBaseHeader(File, Header);
    if (!Result) return (false); 

    //SystemLog.Printf ("0x%08lX: Group %4.4s (%d bytes left)", CurrentOffset, Header.Type.Name, EndOffset - CurrentOffset);

		/* Create record/group based on input header */
    pBaseRecord = CreateObRecordGroup(Header);
    assert(pBaseRecord != NULL);
    m_pRecords->Add(pBaseRecord);
    pBaseRecord->SetParent(m_pParent);
    pBaseRecord->SetParentGroup(this);

    if ((m_CacheFlags & OB_CACHE_DEFERLOAD) != 0 && (Header.Type == OB_NAME_LAND)) {
      pBaseRecord->SetCacheFlags(m_CacheFlags);

      Result = File.SeekCur(Header.Size);
      if (!Result) return (false);
    }//|| Header.Type == OB_NAME_PGRD || Header.Type == OB_NAME_REFR
    else if ((m_CacheFlags & OB_CACHE_DEFERLOAD) != 0 && Header.Type == OB_NAME_GRUP) {
      pBaseRecord->SetCacheFlags(m_CacheFlags);

      Result = pBaseRecord->ReadData(File, pCallback);
      if (!Result) return (false);
    }
    else {
      Result = pBaseRecord->ReadData(File, pCallback);
      if (!Result) return (false);
    }

    Result = File.Tell(CurrentOffset);
    if (!Result) return (false);

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(CurrentOffset);
      if (iResult < 0) return (false);
    }

  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObGroup::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool Write (File, pCallback);
 *
 * Writes group data to the current location in the given file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObGroup::Write (CObFile& File, CObCallback* pCallback) {
  CObBaseRecord* pRecord;
  dword		 Index;
  bool		 Result;
  int		 StartOffset;
  int		 iResult;

  if (pCallback != NULL) {
    pCallback->SetTotalRecords1(m_pRecords->GetSize());
  } 

	/* Save the start position of the group */
  Result = File.Tell(StartOffset);
  if (!Result) return (false); 

	/* Output the group header (group size may be incorrect) */
  Result = File.Write(&m_Header, OB_BASEHEADER_SIZE);
  if (!Result) return (false); 

	/* Output all group content */
  for (Index = 0; Index < m_pRecords->GetSize(); ++Index) {
    pRecord = m_pRecords->GetAt(Index);
    assert(pRecord != NULL);
    
    Result = pRecord->Write(File);
    if (!Result) return (false); 

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback1(Index);
      if (iResult < 0) return (false);
    }
  }

	/* Update the gorup size */
  return WriteGroupSize(File, StartOffset);
}
/*===========================================================================
 *		End of Class Method CObGroup::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObGroup Method - bool WriteGroupSize (File, Offset);
 *
 * Protected class method that updates the size of the group being output
 * assuming that the current location in the file is at the end of the
 * group. Returns false on any error. The input offset marks the start of
 * the group in the file 
 *
 *=========================================================================*/
bool CObGroup::WriteGroupSize (CObFile& File, const dword Offset) {
  bool  Result;
  int   CurrentOffset;
  dword GroupSize;

	/* Save the current file position */
  Result = File.Tell(CurrentOffset);
  if (!Result) return (false);

	/* Compute size of group data */
  assert(CurrentOffset >= (int)Offset);
  GroupSize = CurrentOffset - Offset;

	/* Move to the group size position */
  Result = File.Seek(Offset + 4);
  if (!Result) return (false);

	/* Output the new group size */
  Result = File.WriteDWord(GroupSize);
  if (!Result) return (false);

	/* Return to end of output file */
  Result = File.Seek(CurrentOffset);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObGroup::WriteRecordSize()
 *=========================================================================*/
