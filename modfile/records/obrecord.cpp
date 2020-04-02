/*===========================================================================
 *
 * File:	Obbaserecord.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "ctype.h"
#include "obrecord.h"
#include "../../common/zlib/zlib.h"
#include "../subrecords/obformidsubrecord.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Static buffers used when loading and saving */
  CObMemFile	CObRecord::s_MemFile;
  byte*		CObRecord::s_pTempBuffer    = NULL;
  dword		CObRecord::s_TempBufferSize = 0;

  #define OBRECORD_DEBUG_OUTPUT 0

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
const obsubreccreate_t   CObRecord::s_SubrecCreate = {
	NULL, CObRecord::s_SubrecEntries
 };

const obsubrecentries_t  CObRecord::s_SubrecEntries[] = {
	{ NULL,		 NULL }	/* Must be last record */
 };
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDBASEMAP(CObRecord)
	ADD_OBFIELDALL("FormID",      OB_FIELD_FORMID,   OBRF_NOCSV, CObRecord, FieldFormID)
	ADD_OBFIELDALL("RecordType",  OB_FIELD_RECORDTYPE,	  0, CObRecord, FieldName)
	ADD_OBFIELDALL("Flags",       OB_FIELD_FLAGS,		  0, CObRecord, FieldRecordFlags)
	//ADD_OBFIELDALL("User Data", OB_FIELD_USERDATA,	  0, CObRecord, FieldUserData)
	ADD_OBFIELDALL("Level",	      OB_FIELD_USERDATA,	  0, CObRecord, FieldUserData)	/* TODO: */
	ADD_OBFIELDALL("Quest",	      OB_FIELD_QUESTITEM,	  0, CObRecord, FieldQuestItem)
	ADD_OBFIELDALL("Dangerous",   OB_FIELD_DANGEROUS,	  0, CObRecord, FieldDangerous)
	ADD_OBFIELDALL("Ignored",     OB_FIELD_IGNORED,		  0, CObRecord, FieldIgnored)
	ADD_OBFIELDALL("Deleted",     OB_FIELD_DELETED,		  0, CObRecord, FieldDeleted)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Constructor
 *
 *=========================================================================*/
CObRecord::CObRecord () {
  memset(&m_Header, 0, sizeof(m_Header));
  m_UserData   = 0;
}
/*===========================================================================
 *		End of Class CObRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Destructor
 *
 *=========================================================================*/
CObRecord::~CObRecord () {
} 
/*===========================================================================
 *		End of Class CObRecord Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - void Destroy (void);
 *
 * Clear content data.
 *
 *=========================================================================*/
void CObRecord::Destroy (void) {
  
  m_Subrecords.Destroy();
  
  m_Header.Flags1 = 0;
  m_Header.Flags2 = 0;
  m_Header.FormID = 0;
  m_Header.Size   = 0;

  CObBaseRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CObRecord* AddNewSubrecord (Type);
 *
 * Allocates and adds a subrecord based on the input name. Creates a 
 * default CObSubrecord object if the type is not known.
 *
 *=========================================================================*/
CObSubrecord* CObRecord::AddNewSubrecord (const obrectype_t Type) {
  obsubrecheader_t Header;
  
  Header.Type = Type;
  Header.Size = 0;

  return AddNewSubrecord(Header);
 }
/*===========================================================================
 *		End of Class Method CObRecord::AddNewSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CEsmRecord Method - CObRecord* AddNewSubrecord (Header);
 *
 * Allocates and adds a subrecord based on the input header. Creates a 
 * default CObSubrecord object if the type is not known.
 *
 *=========================================================================*/
CObSubrecord* CObRecord::AddNewSubrecord (const obsubrecheader_t Header) {
  CObSubrecord* pSubrecord;

	/* Allocate the correct type of subrecord */
  pSubrecord = CreateSubrecord(Header);
  
	/* Add the subrecord to the record's collection */
  m_Subrecords.Add(pSubrecord);

  	/* Call the add event */
  OnAddSubrecord(pSubrecord);  

  return (pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObRecord::AddNewSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword ChangeFormidSubrecords (Type, NewID, OldID);
 *
 * Changes any occurence of the old formid for the new formid in all
 * formid subrecords of the given type.
 *
 *=========================================================================*/
dword CObRecord::ChangeFormidSubrecords (const obrectype_t Type, const obformid_t NewID, const obformid_t OldID) {
  CObSubrecord*		pSubrecord;
  CObFormidSubrecord*	pFormid;
  dword			Count = 0;
  dword			Index;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    if (pSubrecord->GetRecordType() != Type) continue;

    pFormid = ObCastClass(CObFormidSubrecord, pSubrecord);
    if (pFormid == NULL) continue;

    if (pFormid->GetValue() == NewID) {
      ++Count;
      pFormid->SetValue(NewID);
      pFormid->SetOrigValue(NewID);
    }
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecord::ChangeFormidSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword ChangeFormidSubrecords (Type, NewID, OldID);
 *
 * Changes any occurence of the old formid for the new formid in all
 * subrecords.
 *
 *=========================================================================*/
dword CObRecord::ChangeFormidSubrecords (const obformid_t NewID, const obformid_t OldID) {
  dword	Count = 0;
  dword	Index;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    Count += m_Subrecords.GetAt(Index)->ChangeFormID(NewID, OldID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecord::ChangeFormidSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword ChangeFormid (NewID, OldID);
 *
 * Changes any occurence of the given Old formid in the record to the
 * new formid.
 *
 *=========================================================================*/
dword CObRecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
  dword Count = 0;

  if (m_Header.FormID == OldID) {
    m_Header.FormID = NewID;
    Count = 1;
  }

  return Count + ChangeFormidSubrecords(NewID, OldID);
}
/*===========================================================================
 *		End of Class Method CObRecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword ChangeEditorID (pNewID, pOldID);
 *
 * Changes any occurence of the given Old editorid in the record to the
 * new editorid.
 *
 *=========================================================================*/
dword CObRecord::ChangeEditorID (const SSCHAR* pNewID, const SSCHAR* pOldID) {
  return (0);
}
/*===========================================================================
 *		End of Class Method CObRecord::ChangeEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool Copy (pRecord);
 *
 * Copy the contents of the given record.
 *
 *=========================================================================*/
bool CObRecord::Copy (CObRecord* pRecord) {
  CObSubrecord* pSubrecord;
  CObSubrecord* pNewSubrecord;
  dword         Index;

	/* Clear the current record contents */
  Destroy();

	/* Ignore invalid input */
  if (pRecord == NULL) return (false);

  m_pParent      = pRecord->GetParent();
  m_pParentGroup = pRecord->GetParentGroup();
  m_UserData     = pRecord->GetUserData();

	/* Copy the record header, except for the record type and size */
  m_Header.Flags1 = pRecord->GetHeader().Flags1;
  m_Header.Flags2 = pRecord->GetHeader().Flags2;
  m_Header.FormID = pRecord->GetHeader().FormID;

	/* Copy all subrecords */
  for (Index = 0; Index < pRecord->GetNumSubrecords(); ++Index) {
    pSubrecord = pRecord->GetSubrecord(Index);

    pNewSubrecord = AddNewSubrecord(pSubrecord->GetRecordType());
    if (pNewSubrecord == NULL) continue;

    pNewSubrecord->Copy(pSubrecord);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - int CompareFields (FieldID, pRecord);
 *
 * Attempts to compare the given field values of the current and the given
 * record. Returns 0 on any error.
 *
 *=========================================================================*/
int CObRecord::CompareFields (const obrecfieldid_t FieldID, CObRecord* pRecord) {
  const obrecfield_t* pField;

  if (pRecord == NULL) return (0);

  pField = FindField(FieldID);
  if (pField == NULL || pField->CompareMethod == NULL) return (0);

  return (this->*pField->CompareMethod)(pRecord, 0);
 }
/*===========================================================================
 *		End of Class Method CObRecord::GetField()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword CountUses (FormID);
 *
 *=========================================================================*/
dword CObRecord::CountUses (const obformid_t FormID) {
  CObSubrecord* pSubrecord;
  dword         Count = 0;
  dword         Index;

	/* Ignore if this record is the given form (??) */
  if (GetFormID() == FormID) return (0);

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    Count += pSubrecord->CountUses(FormID);
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecord::CountUses()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - CObSubrecord* CreateSubrecord (Header);
 *
 * Allocates and returns a new child subrecord of the given Header. The
 * subrecord is not added to the record.
 *
 *=========================================================================*/
CObSubrecord* CObRecord::CreateSubrecord (const obsubrecheader_t Header) {
  CObSubrecord*	pSubrecord;
  
	/* Create and initialize the new record */
  pSubrecord = FindSubrecCreate(Header.Type)();
  pSubrecord->Initialize(Header);

  return (pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObRecord::CreateSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - CObSubrecord* CreateSubrecord (Type);
 *
 *=========================================================================*/
CObSubrecord* CObRecord::CreateSubrecord (const obrectype_t Type) {
  CObSubrecord*	pSubrecord;
  
	/* Create and initialize the new record */
  pSubrecord = FindSubrecCreate(Type)();
  pSubrecord->Initialize(Type, 0);

  return (pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObRecord::CreateSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - int DeleteSubrecords (Type);
 *
 * Deletes all subrecords of the given type. Returns the number deleted.
 *
 *=========================================================================*/
int CObRecord::DeleteSubrecords (const obrectype_t Type) {
  CObSubrecord* pSubrecord;
  int		Count = 0;
  int		Index;

  for (Index = m_Subrecords.GetSize() - 1; Index >= 0; --Index) {
    pSubrecord = m_Subrecords[Index];

    if (pSubrecord->GetRecordType() == Type) {
      OnDeleteSubrecord(pSubrecord);
      m_Subrecords.Delete(Index);
      ++Count;
    }
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecord::DeleteSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - void DestroyIOBuffers (void);
 *
 * Static class method to delete the current temporary input/output buffers.
 *
 *=========================================================================*/
void CObRecord::DestroyIOBuffers (void) {

	/* Ignore if not initialized */
  if (s_pTempBuffer != NULL) {
    delete[] s_pTempBuffer;
    s_pTempBuffer    = NULL;
    s_TempBufferSize = 0;
   }

  if (s_MemFile.IsOpen()) {
    s_MemFile.Close();
   }
 }
/*===========================================================================
 *		End of Class Method CObRecord::DestroyIOBuffers()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool ExportCsv (CsvInfo);
 *
 * Exports the record to a single row in the given CSV information.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::ExportCsv (obcsvinfo_t& CsvInfo) {
  obcsvcolinfo_t* pColInfo;
  CSString*       pString;
  CCsvRow*        pRow;
  dword           Index;

  pRow = CsvInfo.pCsvFile->AddRow();
  assert(pRow != NULL);

  for (Index = 0; Index < CsvInfo.ColInfos.GetSize(); ++Index) {
    pColInfo = CsvInfo.ColInfos[Index];

    pString = new CSString;
    pRow->Add(pString);

    if (!pColInfo->Process) continue;

    GetField(*pString, pColInfo->FieldID);
    pString->Escape();
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::ExportCsv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool Find (FindCount, FindData, pCallback);
 *
 *=========================================================================*/
bool CObRecord::Find (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback) {
  dword Count;
  dword Index;

  FindCount = 0;
  ++FindData.RecordCount;

	/* Look in the record header */
  if ((FindData.Flags & OB_FIND_RECORDHEADER) != 0) {
    Count      = ObFindData((const byte*)&m_Header, sizeof(m_Header), FindData);
    FindCount += Count;

    if (Count > 0 && (FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("'%4.4s' -- 0x%08X: Found %u match(s) in record header", GetRecordType().Name, GetFormID(), Count); 
  }

	/* Look in all subrecords */
  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    Count      = m_Subrecords[Index]->Find(FindData);
    FindCount += Count;

    if (Count > 0) {
      ++FindData.FoundSubrecords;
      if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("'%4.4s' -- 0x%08X: Found %u match(s) in subrecord '%4.4s'",  GetRecordType().Name, GetFormID(), Count, m_Subrecords[Index]->GetRecordType().Name); 
      if ((FindData.Flags & OB_FIND_FINDALL) == 0) break;
    }
  }

  if (FindCount > 0) {
    if ((FindData.Flags & OB_FIND_ADDRECORDS) != 0 && FindData.pFindRecords != NULL) FindData.pFindRecords->Add(this);
    ++FindData.FoundRecords;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool FindText (FindCount, FindData, pCallback);
 *
 *=========================================================================*/
bool CObRecord::FindText (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback) {
  dword Count;
  dword Index;

  FindCount = 0;
  ++FindData.RecordCount;

	/* Look in the record header */
  if ((FindData.Flags & OB_FIND_RECORDHEADER) != 0) {
    Count      = ObFindTextData((const byte*)&m_Header, sizeof(m_Header), FindData);
    FindCount += Count;

    if (Count > 0 && (FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("'%4.4s' -- 0x%08X: Found %u match(s) in record header", GetRecordType().Name, GetFormID(), Count); 
  }

	/* Look in all subrecords */
  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    Count      = m_Subrecords[Index]->FindText(FindData);
    FindCount += Count;

    if (Count > 0) {
      ++FindData.FoundSubrecords;
      if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("'%4.4s' -- 0x%08X: Found %u match(s) in subrecord '%4.4s'",  GetRecordType().Name, GetFormID(), Count, m_Subrecords[Index]->GetRecordType().Name); 
      if ((FindData.Flags & OB_FIND_FINDALL) == 0) break;
    }
  }

  if (FindCount > 0) {
    if ((FindData.Flags & OB_FIND_ADDRECORDS) != 0 && FindData.pFindRecords != NULL) FindData.pFindRecords->Add(this);
    ++FindData.FoundRecords;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::FindText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - CObSubrecord* FindNextSubrecord (Type, Position);
 *
 *=========================================================================*/
CObSubrecord* CObRecord::FindNextSubrecord  (const obrectype_t Type, int& Position) {
  CObSubrecord* pSubrecord;
  dword         Index;

  ++Position;
  if (Position < 0) return (NULL);

  for (Index = (dword) Position; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];
    if (pSubrecord->GetRecordType() == Type) return (pSubrecord);

    ++Position;
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObRecord::FindNextSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - OBSUBREC_CREATEFUNC FindSubrecCreate (Type);
 *
 * Protected class method to find the creation method in this classes
 * or its base classes subrecord creation data. Returns the base class
 * CObSubrecord method by default (does not return NULL). 
 *
 *=========================================================================*/
OBSUBREC_CREATEFUNC CObRecord::FindSubrecCreate (const obrectype_t Type) {
  const obsubreccreate_t* pCreate;
  int		          Index;

	/* Loop through this class followed by all base classes */
  for (pCreate = GetSubrecCreate(); pCreate != NULL; pCreate = pCreate->pBaseCreate) {
    assert(pCreate != pCreate->pBaseCreate);

    for (Index = 0; pCreate->pEntries[Index].CreateMethod != NULL; ++Index) {
      if (*pCreate->pEntries[Index].pName == Type) return (pCreate->pEntries[Index].CreateMethod); 
     }
   }

	/* No match found, return default creation method */
  return (CObDataSubrecord::Create);
 }
/*===========================================================================
 *		End of Class Method CObRecord::FindSubrecCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - CObSubrecord* FindSubrecord (Type);
 *
 * Finds the fist subrecord matching the given type.
 *
 *=========================================================================*/
CObSubrecord* CObRecord::FindSubrecord (const obrectype_t Type) {
  CObSubrecord* pSubrecord;
  dword		Index;

	/* Find the subrecord */
  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];
    if (pSubrecord->GetRecordType() == Type) return (pSubrecord);
   }
  
	/* Not found */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecord::FindSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool FixupFormids (FixupArray);
 *
 *=========================================================================*/
inline bool CObRecord::FixupFormids (CObFormidFixupArray& FixupArray) {
  return ObFixupFormid(m_Header.FormID, m_Header.FormID, FixupArray) && FixupFormidSubrecords(FixupArray);
}
/*===========================================================================
 *		End of Class Method CObRecord::FixupFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool FixupFormidSubrecords (Type, FixupArray);
 *
 * Fixes the formid of all formid type subrecords of the given type
 * in the record.
 *
 *=========================================================================*/
bool CObRecord::FixupFormidSubrecords (const obrectype_t Type, CObFormidFixupArray& FixupArray) {
  CObSubrecord*		pSubrecord;
  CObFormidSubrecord*	pFormid;
  bool			Result = true;
  dword			Index;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords.GetAt(Index);
    if (pSubrecord->GetRecordType() != Type) continue;

    pFormid = ObCastClass(CObFormidSubrecord, pSubrecord);
    if (pFormid == NULL) continue;

    Result &= ObFixupFormid(*(obformid_t *)pFormid->GetData(), pFormid->GetOrigValue(), FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRecord::FixupFormidSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool FixupFormidSubrecords (FixupArray);
 *
 * Fixes the formid of all all subrecords in the record.
 *
 *=========================================================================*/
bool CObRecord::FixupFormidSubrecords (CObFormidFixupArray& FixupArray) {
  bool	Result = true;
  dword	Index;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    Result &= m_Subrecords.GetAt(Index)->FixupFormID(FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRecord::FixupFormidSubrecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool GetField (Buffer, FieldID);
 *
 * Attempts to get a string representation of the given record field.
 * Returns false if the field was not found.
 *
 *=========================================================================*/
bool CObRecord::GetField (CSString& Buffer, const obrecfieldid_t FieldID) {
  const obrecfield_t* pField;

  Buffer.Empty();
  pField = FindField(FieldID);

  if (pField == NULL || pField->GetMethod == NULL) return (false);
  return (this->*pField->GetMethod)(Buffer, 0);
 }
/*===========================================================================
 *		End of Class Method CObRecord::GetField()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - CObSubrecord* GetSubrecord (pSubrecord, Offset, Type);
 *
 * Accesses a subrecord relative to another subrecord within the record.
 *
 * Verifies:
 *		- The input subrecord exists in the record
 *		- The offset to the next subrecord is valid
 *		- The offset subrecord is the correct type.
 *
 * If any of these steps fail NULL is returned. The offset subrecord is
 * returned on success.
 *
 *=========================================================================*/
CObSubrecord* CObRecord::GetSubrecord (CObSubrecord* pSubrecord, const int Offset, const obrectype_t Type) {
  CObSubrecord* pDestSubrecord;
  int		Index;

	/* Find the subrecord */
  Index = m_Subrecords.Find(pSubrecord);

  if (Index < 0) {
    AddObUserError(OBERR_USER_SUBRECNOTFOUND);
    return (NULL);
   }

	/* Ensure the offset subrecord exists */
  pDestSubrecord = m_Subrecords.GetAt(Index + Offset);

  if (pDestSubrecord == NULL) {
    //AddObUserError(OBERR_USER_SUBRECNOTFOUND, "Subrecord index %d ([%d]+%d) is not valid!", Index + Offset, Index, Offset);
    return (NULL);
   }

	/* Ensure the subrecord is the correct type */
  if (pDestSubrecord->GetRecordType() != Type) {
    //AddObUserError(OBERR_USER_SUBRECNOTFOUND, "The requested subrecord (%4.4s) is not the correct type (%4.4s)!", pDestSubrecord->GetRecordType().Name, Type.Name);
    return (NULL);
   }

  return (pDestSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObRecord::GetSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - dword GetSubrecordSize (void);
 *
 * Protected class method that returns the size, in bytes, needed to output
 * all subrecords.
 *
 *=========================================================================*/
dword CObRecord::GetSubrecordSize (void) {
  dword Size = 0;
  dword Index;

  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    Size += m_Subrecords[Index]->GetOutputSize();
   }

  return (Size);
 }
/*===========================================================================
 *		End of Class Method CObRecord::GetSubrecordSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool IsFormType (Type);
 *
 * OB_FUNCPARAM_ACTORVALUE
 * OB_FUNCPARAM_ANIMATIONGROUP
 * OB_FUNCPARAM_TESOBJECT
 * OB_FUNCPARAM_QUESTSTAGE
 * OB_FUNCPARAM_FORMTYPE
 *
 *=========================================================================*/
bool CObRecord::IsFormType (const int Type) {

	/* Test against known simple types */
  switch (Type) {
    case OB_FUNCPARAM_INVENTORYOBJECT:
        return IsInventoryItem();
    case OB_FUNCPARAM_TESOBJECT:
	return IsObject();
    case OB_FUNCPARAM_OBJECTREF:
	return (GetRecordType() == OB_NAME_REFR);
    case OB_FUNCPARAM_SPELLITEM:
	return (GetRecordType() == OB_NAME_SPEL) || (GetRecordType() == OB_NAME_BOOK);
    case OB_FUNCPARAM_CELL:
	return (GetRecordType() == OB_NAME_CELL);
    case OB_FUNCPARAM_MAGICITEM:
	return (GetRecordType() == OB_NAME_SPEL);	/* Unsure if this is the intended definition */
    case OB_FUNCPARAM_SOUND:
	return (GetRecordType() == OB_NAME_SOUN);
    case OB_FUNCPARAM_TOPIC:
	return (GetRecordType() == OB_NAME_DIAL);
    case OB_FUNCPARAM_QUEST:
	return (GetRecordType() == OB_NAME_QUST);
    case OB_FUNCPARAM_RACE:
	return (GetRecordType() == OB_NAME_RACE);
    case OB_FUNCPARAM_CLASS:
	return (GetRecordType() == OB_NAME_CLAS);
    case OB_FUNCPARAM_FACTION:
	return (GetRecordType() == OB_NAME_FACT);
    case OB_FUNCPARAM_GLOBAL:
	return (GetRecordType() == OB_NAME_GLOB);
    case OB_FUNCPARAM_FURNITURE:
	return (GetRecordType() == OB_NAME_FURN);
    case OB_FUNCPARAM_CONTAINER:
	return (GetRecordType() == OB_NAME_CONT);
    case OB_FUNCPARAM_WORLDSPACE:
	return (GetRecordType() == OB_NAME_WRLD);
    case OB_FUNCPARAM_AIPACKAGE:
	return (GetRecordType() == OB_NAME_PACK);
    case OB_FUNCPARAM_MAGICEFFECT:
	return (GetRecordType() == OB_NAME_MGEF);
    case OB_FUNCPARAM_BIRTHSIGN:
	return (GetRecordType() == OB_NAME_BSGN);
    case OB_FUNCPARAM_WEATHER:
	return (GetRecordType() == OB_NAME_WTHR);
    case OB_FUNCPARAM_NPC:
	return (GetRecordType() == OB_NAME_NPC_);
    case OB_FUNCPARAM_OWNER:
	return (GetRecordType() == OB_NAME_FACT || GetRecordType() == OB_NAME_NPC_);
    case OB_FUNCPARAM_EFFECTSHADER:
	return (GetRecordType() == OB_NAME_EFSH);
    case OB_FUNCPARAM_COMBATSTYLE:
    	return (GetRecordType() == OB_NAME_CSTY);
    case OB_FUNCPARAM_ACTORBASE:
	return (GetRecordType() == OB_NAME_NPC_ || GetRecordType() == OB_NAME_CREA || GetRecordType() == OB_NAME_LVLC);
  }

	/* Default */
  return (false);
}
/*===========================================================================
 *		End of Class Method CObRecord::IsFormType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool ImportCsvRow (CsvInfo, Row);
 *
 * Sets the record values from the gievn csv row. 
 *
 *=========================================================================*/
bool CObRecord::ImportCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row) {
  obcsvcolinfo_t* pColInfo;
  CSString*       pString;
  dword           Index;
  bool		  Result;

	/* Import all columns in the given CSV row */
  for (Index = 0; Index < CsvInfo.ColInfos.GetSize(); ++Index) {
    pColInfo = CsvInfo.ColInfos[Index];
    if (pColInfo == NULL)   continue;
    if (!pColInfo->Process) continue;
    if (pColInfo->pField == NULL) pColInfo->pField = FindField(pColInfo->FieldID);

    pString = Row[pColInfo->ColIndex];
    if (pString == NULL) continue;

		/* Prepare the string as required */
    pString->Unescape();

    if (pColInfo->pField != NULL && pColInfo->pField->IsAlNum()) {
      pString->RemoveCharsToMatch(isalnum);
    }

    Result = SetField(pColInfo->FieldID, pString->c_str());
    if (!Result) AddObGeneralError("Error setting field %s value '%s', row %d, column %d!", pColInfo->pValue->c_str(), pString->c_str(), CsvInfo.CurrentLine, pColInfo->ColIndex);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::ImportCsvRow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool InitializeFieldMap (s_FieldIDMap);
 *
 * Initializes the class's field map into the given map container.
 *
 *=========================================================================*/
bool CObRecord::InitializeFieldMap (CObRecFieldIDMap& s_FieldIDMap) {
  const obrecfield_t*     pField;
  const obrecfieldmap_t*  pFieldMap;
  const obrecfieldmap_t*  pStartMap = GetFieldMap();
  dword		          Index;

	/* Loop through this class followed by all base classes */
  for (pFieldMap = pStartMap; pFieldMap != NULL; pFieldMap = pFieldMap->pBaseFieldMap) {
    assert(pFieldMap != pFieldMap->pBaseFieldMap);

    for (Index = 0; pFieldMap->pField[Index].GetMethod != NULL; ++Index) {
      pField = &pFieldMap->pField[Index];
      s_FieldIDMap.SetAt(pField->FieldID, (obrecfield_t *) pField);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::InitializeFieldMap()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - void InitializeNew (void);
 *
 * Initializes a new record ensuring any required sub-records are
 * defined and properly initialized. 
 *
 *=========================================================================*/
void CObRecord::InitializeNew (void) {

  m_Header.Flags1 = 0;
  m_Header.Flags2 = 0;
  m_Header.FormID = 0;

}
/*===========================================================================
 *		End of Class Method CObRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool InitIOBuffers (void);
 *
 * Static class method to initialize the current temporary input/output 
 * buffers.
 *
 *=========================================================================*/
bool CObRecord::InitIOBuffers (void) {

	/* Ignore if already initialized */
  if (s_pTempBuffer == NULL) {
    s_pTempBuffer    = new byte[OB_ZLIB_BUFFERSIZE + 4];
    s_TempBufferSize = OB_ZLIB_BUFFERSIZE;
  }

  if (!s_MemFile.IsOpen()) {
    return s_MemFile.Open(OB_ZLIB_BUFFERSIZE+ 4);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecord::InitIOBuffers()
 *=========================================================================*/

   
/*===========================================================================
 *
 * Class CObRecord Event - void OnAddSubrecord (pSubRecord);
 *
 *=========================================================================*/
void CObRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

}
/*===========================================================================
 *		End of Class Event CObRecord::OnAddSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {
}
/*===========================================================================
 *		End of Class Event CObRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool ReadSubRecords (File);
 *
 * Reads all the subrecords starting from the current location in the 
 * given File. Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::ReadSubRecords (CObFile& File) {
  obsubrecheader_t  Header;
  CObSubrecord*     pSubrecord;
  CObSubrecord*     pLastRecord = NULL;
  bool		    Result;
  int		    CurrentOffset;
  int		    EndOffset;
  bool		    LastRecordSpecial = false;

	/* Get the start of the subrecord data */
  Result = File.Tell(CurrentOffset);
  if (!Result) return (false);
  EndOffset = CurrentOffset + m_Header.Size;    
  
	/* Read until the end of the subrecord data is reached */
  while (CurrentOffset < EndOffset) {

    Result = ReadObSubRecordHeader(File, Header);
    if (!Result) return (false);

#if OBRECORD_DEBUG_OUTPUT
    SystemLog.Printf ("0x%08lX: SubRecord %4.4s (%d bytes left)", CurrentOffset, Header.Type.Name, EndOffset - CurrentOffset);
#endif
    pSubrecord = AddNewSubrecord(Header);

		/* Special case */
    if (LastRecordSpecial) {
      pSubrecord->SetSpecialSize(*(dword *)pLastRecord->GetData());
      //pSubrecord->SetR
    }

		/* Don't read subrecord data if cached */
    if ((m_CacheFlags & OB_CACHE_DEFERLOAD) != 0 && Header.Type != OB_NAME_EDID && Header.Type != OB_NAME_FULL && Header.Type != OB_NAME_DATA && Header.Type != OB_NAME_XXXX) {
      if (LastRecordSpecial)
        Result = File.SeekCur(*(dword *)pLastRecord->GetData());
      else
        Result = File.SeekCur(Header.Size);

      if (!Result) return (false);
    }
    else {
      Result = pSubrecord->Read(File);
      if (!Result) return (false);
    }

    Result = File.Tell(CurrentOffset);
    if (!Result) return (false);

    if (Header.Type == OB_NAME_XXXX) {
       LastRecordSpecial = true;
     }
    else {
       LastRecordSpecial = false;
     }

    pLastRecord = pSubrecord;
  }
    
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecord::ReadSubRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool ReadCompressedData (File);
 *
 * Reads a compressed data record. Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::ReadCompressedData (CObFile& File) {
  dword		DeflatedSize;
  z_stream	Stream;
  dword		OldSize;
  bool		Result;
  int		zResult;

  	/* Initialize the temporary input buffer */
  if (s_TempBufferSize <= m_Header.Size) {
    delete[] s_pTempBuffer;
    s_TempBufferSize = m_Header.Size + 100;
    s_pTempBuffer = new byte[s_TempBufferSize + 4];
   }

	/* Read the compressed data */
  Result = File.Read(s_pTempBuffer, m_Header.Size);
  if (!Result) return (false);

  	/* Create the temporary buffer to hold the uncompressed data */
  DeflatedSize = *(long *)(byte *)s_pTempBuffer;

  	/* Initialize the temporary output memory file */
  if (s_MemFile.GetBufferSize() <= DeflatedSize) {
    s_MemFile.Close();
    Result = s_MemFile.Open(DeflatedSize + 100);
    if (!Result) return (false);
   }
  else {
    s_MemFile.Seek(0);
   }
  
	/* Initialize the zLib stream */
  Stream.zalloc   = Z_NULL;
  Stream.zfree    = Z_NULL;
  Stream.opaque   = Z_NULL;
  Stream.avail_in = 0;
  Stream.next_in  = Z_NULL;

  zResult = inflateInit(&Stream);
  if (zResult != Z_OK) return AddObZLibError(zResult, Stream.msg);
  
	/* Uncompress the data in the temp buffer into the memory file */
  Stream.next_in   = s_pTempBuffer + 4;
  Stream.avail_in  = m_Header.Size - 4;
  Stream.avail_out = DeflatedSize;
  Stream.next_out  = s_MemFile.GetBuffer();

  zResult = inflate(&Stream, Z_NO_FLUSH);
   
  if (zResult < 0) {
    AddObZLibError(zResult, Stream.msg);
    inflateEnd(&Stream);
    return (false);
   }

  inflateEnd(&Stream);

	/* Parse the uncompressed data into subrecords */
  OldSize       = m_Header.Size;
  m_Header.Size = DeflatedSize;

  Result = ReadSubRecords(s_MemFile);
  m_Header.Size = OldSize;

/*	//Debug/Test Stuff
  static dword BytesCompress = 0;
  static dword BytesDecompress = 0;
  static dword Count = 0;
  ++Count;
  BytesCompress   += m_Header.Size;
  BytesDecompress += BufferSize;
  SystemLog.Printf("%d) Bytes: %u to %u (%g%%), Total %lu to %lu (%g%%)", Count, m_Header.Size, BufferSize,  (float)m_Header.Size*100.0f/(float)BufferSize, BytesCompress, BytesDecompress, (float)BytesCompress*100.0f/(float)BytesDecompress); //*/

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecord::ReadCompressedData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool ReadData (File);
 *
 * Reads a record determining if it has subrecords or raw data.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::ReadData (CObFile& File) {
  
#if OBRECORD_DEBUG_OUTPUT
  SystemLog.Printf("\t%4.4s, 0x%08lX", m_Header.RecordType.Name, File.Tell());
#endif

	/* Special compressed records */
  if (IsCompressed()) return ReadCompressedData(File);
    
	/* Default record type */
  return ReadSubRecords(File);
 }
/*===========================================================================
 *		End of Class Method CObRecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool SetField (FieldID, pString);
 *
 * Attempts to set the given field from a string. Returns false on any
 * error, such as if the field was not found or for an invalid input.
 *
 *=========================================================================*/
bool CObRecord::SetField (const obrecfieldid_t FieldID, const SSCHAR* pString) {
  const obrecfieldmap_t* pMap;
  dword			 Index;

	/* Look for fields in class and all base classes */
  for (pMap = GetFieldMap(); pMap != NULL; pMap = pMap->pBaseFieldMap) {
    assert(pMap != pMap->pBaseFieldMap);

    for (Index = 0; pMap->pField[Index].GetMethod != NULL; ++Index) {

      if (pMap->pField[Index].FieldID == FieldID) {
        if (pMap->pField[Index].SetMethod == NULL) {
	  AddObGeneralError("Cannot set the field '%s' (%d)!", GetObFieldString(FieldID), FieldID);
	  return (false);
	}

        return (this->*pMap->pField[Index].SetMethod)(pString, 0);
      }
    }
  }

  AddObGeneralError("No set method was found for the field '%s' (%d)!", GetObFieldString(FieldID), FieldID);
  return (false);
 }
/*===========================================================================
 *		End of Class Method CObRecord::SetField()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool Write (File);
 *
 * Write the record starting from the current location in the given File.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::Write (CObFile& File) {
  int	StartOffset;
  bool  Result;
  
	/* Output the record header */
  Result = File.Write(&m_Header, OB_BASEHEADER_SIZE);
  if (!Result) return (false);

	/* Output compressed record data */
  if (IsCompressed()) return WriteCompressedData(File);

	/* Save the start location of the record data */
  Result = File.Tell(StartOffset);
  if (!Result) return (false);

	/* Default record type */
  Result = WriteSubRecords(File);
  if (!Result) return (false);

    	/* Update the record size */
  Result = WriteRecordSize(File, StartOffset);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecord::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool WriteCompressedData (File);
 *
 * Write a compressed data record. Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::WriteCompressedData (CObFile& File) {
  int        StartOffset;
  dword      DeflatedSize = GetSubrecordSize();
  bool       Result;

	/* Initialize the temporary output memory file */
  if (s_MemFile.GetBufferSize() <= DeflatedSize) {
    s_MemFile.Close();
    Result = s_MemFile.Open(DeflatedSize + 100);
    if (!Result) return (false);
   }
  else {
    s_MemFile.Seek(0);
   }
  
	/* Output the raw sub-record data to the temporary buffer */
  Result = WriteSubRecords(s_MemFile);
  if (!Result) return (false);

	/* Save the start location of the record data */
  Result = File.Tell(StartOffset);
  if (!Result) return (false);

	/* Compress data and output to file */
  Result = WriteDeflate(File, s_MemFile);
  if (!Result) return (false);
	
	/* Update the record size */
  Result = WriteRecordSize(File, StartOffset);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecord::WriteCompressedData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool WriteDeflate (File, RecordData);
 *
 * Protected class method that compresses the record data in the supplied
 * RecordData memory file and outputs the compressed data to the given
 * output file. Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::WriteDeflate (CObFile& File, CObMemFile& RecordData) {
  byte       TempBuffer[OB_ZLIBCOMPRESS_BUFFER + 4];
  z_stream   Stream;
  int	     Result;

	/* Output deflated buffer size */
  Result = File.WriteDWord(RecordData.Tell());
  if (!Result) return (false);

	/* Initialize the zLib stream */
  Stream.zalloc   = Z_NULL;
  Stream.zfree    = Z_NULL;
  Stream.opaque   = Z_NULL;
  Stream.avail_in = 0;
  Stream.next_in  = Z_NULL;

  Result = deflateInit(&Stream, OB_ZLIB_DEFLATELEVEL);
  if (Result = Z_OK) return AddObZLibError(Result, Stream.msg);

  Stream.next_in  = RecordData.GetBuffer();
  Stream.avail_in = RecordData.Tell();
  
	/* Compress entire data buffer and output to file */
  do {
    Stream.avail_out = OB_ZLIBCOMPRESS_BUFFER;
    Stream.next_out  = TempBuffer;

		/* Compress record data to temporary buffer */
    Result = deflate(&Stream, Z_FINISH);
   
    if (Result < 0) {
      AddObZLibError(Result, Stream.msg);
      deflateEnd(&Stream);
      return (false);
     }

		/* Output compressed data */
    Result = File.Write(TempBuffer, OB_ZLIBCOMPRESS_BUFFER - Stream.avail_out);

    if (!Result) {
      deflateEnd(&Stream);
      return (false);
     }

  } while (Stream.avail_out == 0);

  deflateEnd(&Stream);
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecord::WriteDeflate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - bool WriteRecordSize (File, Offset);
 *
 * Protected class method that updates the size of the record being output
 * assuming that the current location in the file is at the end of the
 * record. Returns false on any error. The input offset marks the start of
 * the record data in the file 
 *
 *=========================================================================*/
bool CObRecord::WriteRecordSize (CObFile& File, const int Offset) {
  bool  Result;
  int   CurrentOffset;
  dword RecordSize;

	/* Save the current file position */
  Result = File.Tell(CurrentOffset);
  if (!Result) return (false);

	/* Compute size of record data */
  assert(CurrentOffset >= Offset);
  RecordSize = CurrentOffset - Offset;

	/* Move to the record size position */
  Result = File.Seek(Offset - 16);
  if (!Result) return (false);

	/* Output the new record size */
  Result = File.WriteDWord(RecordSize);
  if (!Result) return (false);

	/* Return to end of output file */
  Result = File.Seek(CurrentOffset);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecord::WriteRecordSize()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObRecord Method - bool WriteSubRecords (File);
 *
 * Writes all the subrecords to the current location in the 
 * given File. Returns false on any error.
 *
 *=========================================================================*/
bool CObRecord::WriteSubRecords (CObFile& File) {
  CObSubrecord* pSubrecord;
  dword		Index;
  bool		Result;

	/* Output all subrecords */
  for (Index = 0; Index < m_Subrecords.GetSize(); ++Index) {
    pSubrecord = m_Subrecords[Index];
    assert(pSubrecord != NULL);

    Result = pSubrecord->Write(File);
    if (!Result) return (false);
   }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecord::WriteSubRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecord Method - obrecfield_t* FindObFieldEntry (FieldID);
 *
 * Find a field entry in the given field maps by its ID.
 *
 *=========================================================================*/
const obrecfield_t* FindObFieldEntry (const obrecfieldmap_t* pStartFieldMap, const obrecfieldid_t FieldID) {
  const obrecfieldmap_t*  pFieldMap;
  dword		          Index;

  if (pStartFieldMap == NULL) return (NULL);

	/* Loop through this class followed by all base classes */
  for (pFieldMap = pStartFieldMap; pFieldMap != NULL; pFieldMap = pFieldMap->pBaseFieldMap) {
    assert(pFieldMap != pFieldMap->pBaseFieldMap);

    for (Index = 0; pFieldMap->pField[Index].GetMethod != NULL; ++Index) {
      if (pFieldMap->pField[Index].FieldID == FieldID) return (&pFieldMap->pField[Index]);
     }
   }

	/* No match */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecord::FindField()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObRecord::GetFieldFormID,    String.Format("0x%08X", GetFormID()))
DEFINE_OBGETFIELD(CObRecord::GetFieldName,      String.Format("%4.4s", GetRecordType().Name))
DEFINE_OBGETFIELD(CObRecord::GetFieldUserData,  String.Format("%d", GetUserData()))
DEFINE_OBGETFIELD(CObRecord::GetFieldIgnored,   String.Format("%s", BooleanToString(IsIgnored()) ))
DEFINE_OBGETFIELD(CObRecord::GetFieldQuestItem, String.Format("%s", BooleanToString(IsQuestItem()) ))
DEFINE_OBGETFIELD(CObRecord::GetFieldDeleted,   String.Format("%s", BooleanToString(IsDeleted()) ))
DEFINE_OBGETFIELD(CObRecord::GetFieldDangerous, String.Format("%s", BooleanToString(IsDangerous()) ))

BEGIN_OBGETFIELD(CObRecord::GetFieldRecordFlags) 
	String.Format("%s%s%s%s", IsActive() ? "*" : "", IsIgnored() ? "I" : "", IsDeleted() ? "D" : "", IsQuestItem() ? "Q" : "", IsDangerous() ? "!" : "");
END_OBGETFIELD()
/*===========================================================================
 *		End of CObRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldFormID, GetFormID)
DEFINE_OBCOMPFIELDSTRING(CObRecord, CompareFieldName, GetRecordType)
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldUserData, GetUserData)
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldQuestItem, IsQuestItem)
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldDangerous, IsDangerous)
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldIgnored, IsIgnored)
DEFINE_OBCOMPFIELDINT(CObRecord, CompareFieldDeleted, IsDeleted)

BEGIN_OBCOMPFIELD(CObRecord::CompareFieldRecordFlags)
	if (pRecord == NULL) return (1);
	int IsActive1 = IsActive() ? 0x10000000 : 0;
	int IsActive2 = pRecord->IsActive() ? 0x10000000 : 0;

	return -((int)this->GetFlags() - (int) pRecord->GetFlags() + IsActive1 - IsActive2);
END_OBCOMPFIELD()
/*===========================================================================
 *		End of CObRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObRecord::SetFieldFormID)
  AddObGeneralError("Cannot set the formID of a record from its SetField method!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldName)
  AddObGeneralError("Cannot set the record type of a record from its SetField method!");
  return (false);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldUserData)
  return ObFieldConvertLong(pString, m_UserData);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldQuestItem)
  bool Result;
  bool Value;

  Result = ObFieldConvertBoolean(pString, Value);
  if (Result) SetQuestItem(Value);
  return (Result);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldDangerous)
  bool Result;
  bool Value;

  Result = ObFieldConvertBoolean(pString, Value);
  if (Result) SetDangerous(Value);
  return (Result);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldIgnored)
  bool Result;
  bool Value;

  Result = ObFieldConvertBoolean(pString, Value);
  if (Result) SetIgnored(Value);
  return (Result);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldDeleted)
  bool Result;
  bool Value;

  Result = ObFieldConvertBoolean(pString, Value);
  if (Result) SetDeleted(Value);
  return (Result);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObRecord::SetFieldRecordFlags) 
  const SSCHAR* pParse = pString;

	/* Clear known flags */
  SetDeleted(false);
  SetQuestItem(false);
  SetDangerous(false);

	/* Parse flags from input string */
  while (*pParse != NULL_CHAR) {
    switch (toupper(*pParse)) {
      case 'D':
        SetDeleted(true);
      	break;
      case 'Q':
        SetQuestItem(true);
	break;
      case '!':
        SetDangerous(true);
	break;
      case 'I':
        SetIgnored(true);
	break;
    }

    ++pParse;
  }

END_OBSETFIELD()
/*===========================================================================
 *		End of CObRecord Set Field Methods
 *=========================================================================*/
