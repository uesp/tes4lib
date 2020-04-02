/*===========================================================================
 *
 * File:	ObEspFile.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObEspFile for loading, handling, and saving ESP plugin files.
 * Note that ESM files are considered to be a special case of ESP files so
 * is derived from this class. 
 *
 *=========================================================================*/

	/* Include Files */
#include "obespfile.h"
#include "obrecordhandler.h"
#include "../common/obtime.h"


/*===========================================================================
 *
 * Class CObEspFile Constructor
 *
 *=========================================================================*/
CObEspFile::CObEspFile (void) {
  m_pParent = NULL;
  m_pHeader = NULL;

  m_IsActive   = false;
  m_ModIndex   = 0;
  m_CacheFlags = 0;

  m_Records.SetParent(NULL);
  m_Records.SetParentGroup(NULL);
 }
/*===========================================================================
 *		End of Class CObEspFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Destructor
 *
 *=========================================================================*/
CObEspFile::~CObEspFile () {

  Destroy();
 }
/*===========================================================================
 *		End of Class CObEspFile Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - void Destroy (void);
 *
 * Delete object contents.
 *
 *=========================================================================*/
void CObEspFile::Destroy (void) {
  m_pHeader    = NULL;
  m_IsActive   = false;

  m_Filename.Empty();
  m_ShortFilename.Empty();

  m_File.Close();

  m_Records.Destroy();
 }
/*===========================================================================
 *		End of Class Method CObEspFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool AddRecord (pNewRecord);
 *
 * Adds a record/group to the file determining where in the group
 * heirarchy to add it. Returns false on any error.
 *
 *=========================================================================*/
bool CObEspFile::AddRecord (CObRecord* pNewRecord) {
  CObBaseRecord* pRecord;
  dword		 Index;
  bool		 Result;

	/* Special case for a TES4 record */
  if (pNewRecord->GetRecordType() == OB_NAME_TES4) {
    m_Records.GetRecords().Add(pNewRecord);
    pNewRecord->SetParentGroup(NULL);
    return (true);
  }

  for (Index = 0; Index < m_Records.GetNumRecords(); ++Index) {
    pRecord = m_Records.GetRecord(Index);

    Result = pRecord->AddChildRecord(pNewRecord);

    if (Result) {
      ModRecordCount(1);
      return (true);
    }
  }

	/* If we reached here we didn't find any place to add the record */
  Result = CreateTopLevelGroup(pNewRecord);

	/* Couldn't add a new group to contain record either */
  if (!Result) {
    AddObGeneralError("Failed to find the correct insert location for record 0x%X!", pNewRecord->GetFormID());
    m_Records.GetRecords().Add(pNewRecord);
    pNewRecord->SetParentGroup(NULL);
    ModRecordCount(1);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObEspFile::AddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - CObRecord* CreateNewRecord (Type);
 *
 * Creates and adds a new record to the file as given by the input
 * record type. The new record is returned.
 *
 *=========================================================================*/
CObRecord* CObEspFile::CreateNewRecord (const obrectype_t Type) {
  CObRecord* pRecord;
  bool	     Result;
  
  pRecord = CreateObRecord(Type);
  pRecord->InitializeNew();
  pRecord->SetParent(this);

  Result = AddRecord(pRecord);
  if (!Result) return (NULL);
  
	/* Set the header record reference */
  if (pRecord->GetRecordType() == OB_NAME_TES4) {
    m_pHeader = ObCastClass(CObTes4Record, pRecord);
   }
   	/* Update the overall record count */
  else if (m_pHeader != NULL) {
    m_pHeader->ModRecordCount(1);
   }

  return (pRecord);
 }
/*===========================================================================
 *		End of Class Method CObEspFile::CreateNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool CreateTopLevelGroup (pNewRecord);
 *
 * Creates a top level group for the given record and adds the record
 * to the group. Returns false if the group could not be created or
 * the record not added.
 *
 *=========================================================================*/
bool CObEspFile::CreateTopLevelGroup (CObBaseRecord* pNewRecord) {
  CObTypeGroup* pGroup;
  bool          Result;

  if (pNewRecord == NULL) return (false);
  pGroup = CreateTopLevelGroup(pNewRecord->GetRecordType());
  if (pGroup == NULL) return (false);

  Result = pGroup->AddChildRecord(pNewRecord);
  if (Result) ModRecordCount(1);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObEspFile::CreateTopLevelGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - int FindTopGroupInsertPos (Type);
 *
 *=========================================================================*/
CObBaseRecord* CObEspFile::FindTopGroupInsertPos (const obrectype_t Type) {
  CObBaseRecord* pBase;
  CObBaseRecord* pLastInsert = NULL;
  CObTypeGroup*  pTypeGroup;
  dword		 Index;
  dword		 TypeIndex = 0;
  
  for (Index = 0; Index < m_Records.GetNumRecords(); ++Index) {
    pBase = m_Records.GetRecord(Index);

    if (pBase->IsRecord()) {
      if (Index == 0) pLastInsert = pBase;
      continue;
    }

    pTypeGroup = ObCastClass(CObTypeGroup, pBase);
    if (pTypeGroup == NULL) continue;

    for (; s_TopLevelTypeOrder[TypeIndex] != NULL; ++TypeIndex) {
      if (Type == *s_TopLevelTypeOrder[TypeIndex]) return (pLastInsert);
      if (pTypeGroup->GetContainsType() == *s_TopLevelTypeOrder[TypeIndex]) break;
    }

    pLastInsert = pTypeGroup;
  }

  return (pLastInsert);
}
/*===========================================================================
 *		End of Class Method CObEspFile::FindTopGroupInsertPos()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - CObTypeGroup* CreateTopLevelGroup (Type);
 *
 * Create and return a top level type group for the given type. Returns 
 * NULL on any error.
 *
 *=========================================================================*/
CObTypeGroup* CObEspFile::CreateTopLevelGroup (const obrectype_t Type) {
  CObTypeGroup*  pGroup;
  CObBaseRecord* pNewRecord;
  CObBaseRecord* pInsert;

	/* See if the given record is a valid top level group type */
  if (!IsObTopLevelGroup(Type)) return (NULL);
  
	/* Create new group */
  pNewRecord = CreateObGroup(OB_GROUP_TYPE);
  if (pNewRecord == NULL) return (NULL);

	/* Add group to records */
  pInsert = FindTopGroupInsertPos(Type);
  m_Records.GetRecords().InsertAfter(pNewRecord, pInsert);
  if (m_pHeader != NULL) m_pHeader->ModRecordCount(1);

	/* Initialize new group */
  pGroup = ObCastClass(CObTypeGroup, pNewRecord);
  if (pGroup == NULL) return (NULL);
  pGroup->SetContainsType(Type);

  return (pGroup);
 }
/*===========================================================================
 *		End of Class Method CObEspFile::CreateTopLevelGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool DeleteRecord (pRecord);
 *
 * Attempts to delete a record from the file.
 *
 *=========================================================================*/
bool CObEspFile::DeleteRecord (CObRecord* pRecord) {
  bool Result;

  if (pRecord == NULL) return (false);

  Result = m_Records.GetRecords().Delete(pRecord);
  if (Result && m_pHeader != NULL) m_pHeader->ModRecordCount(-1);

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObEspFile::DeleteRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - dword Find (FindData, pCallback);
 *
 *=========================================================================*/
dword CObEspFile::Find (obfinddata_t& FindData, CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  CObTypeGroup*	 pGroup;
  dword          FindCount = 0;
  dword          Index;
  dword          Count;
  bool		 FindText = (FindData.Flags & OB_FIND_COMPARETEXT) != 0;
  bool		 IsExcluded;
  bool		 Result;
  int            iResult;

  if (pCallback != NULL) {
    pCallback->SetTotalRecords(m_Records.GetNumRecords());
    pCallback->SetTotalRecords1(0);
    pCallback->Reset();
  }

  ++FindData.FileCount;
  
  for (Index = 0; Index < m_Records.GetNumRecords(); ++Index) {
    pBaseRecord = m_Records.GetRecord(Index);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pRecord) {
      IsExcluded = ObContainsRecordType(pRecord->GetRecordType(), FindData.pExcludeRecords);
    }
    else {
      pGroup = ObCastClass(CObTypeGroup, pBaseRecord);
      if (pGroup != NULL) IsExcluded = ObContainsRecordType(pGroup->GetContainsType(), FindData.pExcludeRecords);
    }
    
    if (pRecord == NULL || !IsExcluded) {
      if (FindText)
        Result = pBaseRecord->FindText(Count, FindData);
      else
        Result = pBaseRecord->Find(Count, FindData);

      FindCount += Count;
      if (!Result) return (FindCount);
    
      if (pCallback != NULL) {
        iResult = pCallback->UpdateCallback(Index);
        if (iResult < 0) return (FindCount);
      }
    }
  }

  return (FindCount);
 }
/*===========================================================================
 *		End of Class Method CObEspFile::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - CObTypeGroup* GetTypeGroup (Type);
 *
 *=========================================================================*/
CObTypeGroup* CObEspFile::GetTypeGroup (const obrectype_t Type) {
  CObBaseRecord* pRecord;
  CObGroup*	 pGroup;
  CObTypeGroup*	 pTypeGroup;
  dword		 Index;

	/* Search all top level groups for a match */
  for (Index = 0; Index < m_Records.GetNumRecords(); ++Index) {
    pRecord = m_Records.GetRecords().GetAt(Index);

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
 *		End of Class Method CObEspFile::GetTypeGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - void InitializeNew (void);
 *
 * Initialies a new file with any required records/groups. Any existing
 * content is destroyed.
 *
 *=========================================================================*/
void CObEspFile::InitializeNew (void) {
  
	/* Clear the current data */
  Destroy();
  m_Records.SetParent(this);

	/* Add the TES4 record */
  CreateNewRecord(OB_NAME_TES4);
  assert(m_pHeader != NULL);


  SetFilename("noname.esp");
}
/*===========================================================================
 *		End of Class Method CObEspFile::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool Load (pFilename, pCallback);
 *
 * Description
 *
 *=========================================================================*/
bool CObEspFile::Load (const SSCHAR* pFilename, CObCallback* pCallback) {
  obtimer_t Timer;  
  bool      Result;

	/* Update the callback label */
  if (pCallback) {
    pCallback->SetLabel("Loading %s...", pFilename);
  }

	/* Clear the current object contents */
  Destroy();
  SetFilename(pFilename);
  m_Records.SetParent(this);
  
  ObStartTimer(Timer);

  Result = CObRecord::InitIOBuffers();
  if (!Result) return (false);

  Result = m_File.Open(pFilename, "rb");
  if (!Result) return (false);

  Result = Read(pCallback);
  m_File.Close();

  CObRecord::DestroyIOBuffers();

  ObEndTimer(Timer, "\tLoaded file in");

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObEspFile::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool Read (pCallback);
 *
 * Read data from the current position in the opened file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObEspFile::Read (CObCallback* pCallback) {
  CObBaseRecord* pBaseRecord;
  obbaseheader_t Header;
  int64		 FileSize;
  int 		 CurrentOffset;
  bool           Result;
  int		 iResult;

  Result  = m_File.GetFileSize64(FileSize);
  Result |= m_File.Tell(CurrentOffset);
  if (!Result) return (false);

	/* Perform the initial callback if required */
  if (pCallback != NULL) {
    pCallback->SetTotalRecords(FileSize);

    iResult = pCallback->ForceCallback(CurrentOffset);
    if (iResult < 0) return (false);
  } 

	/* Read until the end of the file if reached */
  while (CurrentOffset < FileSize) {

		/* Input the record header */
    Result = ReadObBaseHeader(m_File, Header);
    if (!Result) return (false); 

    //SystemLog.Printf ("0x%08lX: %4.4s (%d bytes left)", CurrentOffset, Header.RecordType.Name, FileSize - CurrentOffset);

		/* Create record/group based on input header */
    pBaseRecord = CreateObRecordGroup(Header);
    assert(pBaseRecord != NULL);
    m_Records.GetRecords().Add(pBaseRecord);
    pBaseRecord->SetParent(this);

    if (pBaseRecord->GetRecordType() == OB_NAME_TES4) {
      m_pHeader = ObCastClass(CObTes4Record, pBaseRecord);
    }

    if ((m_CacheFlags & OB_CACHE_DEFERLOAD) != 0 && (Header.Type == OB_NAME_LAND || Header.Type == OB_NAME_GRUP)) {
      pBaseRecord->SetCacheFlags(m_CacheFlags);
    }

		/* Read the rest of the record/group */
    Result = pBaseRecord->ReadData(m_File, pCallback);
    if (!Result) return (false);

		/* Update current file position */
    Result = m_File.Tell(CurrentOffset);
    if (!Result) return (false);

		/* Update the callback if required */
    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(CurrentOffset);
      if (iResult < 0) return (false);
    }
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObEspFile::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool Save (pFilename, pCallback);
 *
 * Saves the mod data to the given file (overwritten if it exists). Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObEspFile::Save (const SSCHAR* pFilename, CObCallback* pCallback) {
  obtimer_t Timer;  
  bool      Result;

  ObStartTimer(Timer);
  
  Result = CObRecord::InitIOBuffers();
  if (!Result) return (false);

  SetFilename(pFilename);
  
  Result = m_File.Open(pFilename, "wb");
  if (!Result) return (false);

  Result = Write(pCallback);
  m_File.Close();

  CObRecord::DestroyIOBuffers();

  ObEndTimer(Timer, "\tSaved file in");
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObEspFile::Save()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEspFile Method - bool Write (pCallback);
 *
 * Write the file data to the current opened file. Returns false on any error.
 *
 *=========================================================================*/
bool CObEspFile::Write (CObCallback* pCallback) {
  bool Result;

  Result = m_Records.Write(m_File, pCallback);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObEspFile::Write()
 *=========================================================================*/
