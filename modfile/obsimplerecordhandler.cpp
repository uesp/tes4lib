/*===========================================================================
 *
 * File:	Obsimplerecordhandler.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obsimplerecordhandler.h"


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Constructor
 *
 *=========================================================================*/
CObSimpleRecordHandler::CObSimpleRecordHandler (const dword HashMapSize) {
  m_NextFreeFormID   = OBESPFILE_FIRST_FORMID;
  m_NextFreeEditorID = OBESPFILE_FIRST_EDITORID;

  m_FormIdMap.InitHashTable(HashMapSize);
  m_EditorIdMap.InitHashTable(HashMapSize);

  	/* Initialize the special player reference */
  m_PlayerRef.Initialize(OB_NAME_REFR);
  m_PlayerRef.InitializeNew();
  m_PlayerRef.SetFormID(OB_PLAYERREF_FORMID);
  m_PlayerRef.SetBaseFormID(OB_PLAYER_FORMID);
  m_PlayerRef.SetParent(this);
  m_PlayerRef.SetQuestItem(true);

  m_EspFile.SetParent(this);
}
/*===========================================================================
 *		End of Class CObSimpleRecordHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSimpleRecordHandler::Destroy (void) {
  m_NextFreeFormID   = OBESPFILE_FIRST_FORMID;
  m_NextFreeEditorID = OBESPFILE_FIRST_EDITORID;

  m_FormIdMap.Destroy();
  m_EditorIdMap.Destroy();
  m_EspFile.Destroy();
 }
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - CObRecord* CreateNewRecord (Type);
 *
 * Creates and adds a new record to the file as given by the input
 * record type. The new record is returned.
 *
 *=========================================================================*/
CObRecord* CObSimpleRecordHandler::CreateNewRecord (const obrectype_t Type) {
  return m_EspFile.CreateNewRecord(Type);
 }
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::CreateNewRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - bool DeleteRecord (pRecord);
 *
 *=========================================================================*/
bool CObSimpleRecordHandler::DeleteRecord (CObRecord* pRecord) {
  CObIdRecord* pIdRecord;

  if (pRecord == NULL) return (false);

	/* Delete record from the index maps */
  m_FormIdMap.Delete(pRecord);

  pIdRecord = ObCastClass(CObIdRecord, pRecord);
  if (pIdRecord != NULL) m_EditorIdMap.Delete(pIdRecord);

  return m_EspFile.DeleteRecord(pRecord);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::DeleteRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - CObRecord* FindFormID (FormID);
 *
 *=========================================================================*/
CObRecord* CObSimpleRecordHandler::FindFormID (const obformid_t FormID) {
  CObRecord* pRecord;
  bool	     Result;

	/* Ignore invalid input */
  if (FormID == OB_FORMID_NULL) return (NULL);

  Result = m_FormIdMap.Lookup(FormID, pRecord);
  if (!Result) return (NULL);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::FindFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - CObIdRecord* FindEditorID (pString);
 *
 *=========================================================================*/
CObIdRecord* CObSimpleRecordHandler::FindEditorID (const SSCHAR* pString) {
  CObIdRecord* pRecord;
  bool	       Result;

	/* Ignore invalid input */
  if (pString == NULL) return (NULL);

  Result = m_EditorIdMap.Lookup(pString, pRecord);
  if (!Result) return (NULL);
  return (pRecord);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::FindEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - bool GetEditorID (Buffer, FormID);
 *
 *=========================================================================*/
bool CObSimpleRecordHandler::GetEditorID (CSString& Buffer, const obformid_t FormID) {
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
 *		End of Class Method CObSimpleRecordHandler::GetEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class SSCHAR* CObSimpleRecordHandler Method - const GetEditorID (FormID);
 *
 *=========================================================================*/
const SSCHAR* CObSimpleRecordHandler::GetEditorID (const obformid_t FormID) {
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
 *		End of Class Method SSCHAR* CObSimpleRecordHandler::GetEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - const SSCHAR* GetFreeEditorID (void);
 *
 *=========================================================================*/
const SSCHAR* CObSimpleRecordHandler::GetFreeEditorID (void) {
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
 *		End of Class Method CObSimpleRecordHandler::GetFreeEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - obformid_t GetFreeFormID (ModIndex);
 *
 * Returns the next available form ID not currently in use by the mod.
 *
 *=========================================================================*/
obformid_t CObSimpleRecordHandler::GetFreeFormID (const byte ModIndex) {
  dword       NumOverFlows = 0;
  obformid_t  NewID;

  do {
    NewID = (m_NextFreeFormID & 0x00ffffff) | (ModIndex << 24);
    ++m_NextFreeFormID;

		/* Check for an overflow */
    if (m_NextFreeFormID > MAX_OBFORMID) {
      ++NumOverFlows;
      m_NextFreeFormID = OBESPFILE_FIRST_FORMID;

		/* Prevent an infinite loop in the worst case */
      if (NumOverFlows > 1) {
        m_NextFreeFormID = 0;
	AddObGeneralError("GetFreeFormID(): All form IDs are in use!");
	return (OB_FORMID_NULL);
      }
    }

  } while (FindFormID(NewID) != NULL);

  return (NewID);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::GetFreeFormID()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - void IndexRecord (pRecord);
 *
 *=========================================================================*/
void CObSimpleRecordHandler::IndexRecord (CObRecord* pRecord) {
  CObIdRecord* pIdRecord;
  
  if (pRecord != NULL) {
    m_FormIdMap.SetAt(pRecord);

    pIdRecord = ObCastClass(CObIdRecord, pRecord);
    if (pIdRecord != NULL) m_EditorIdMap.SetAt(pIdRecord);
  }

}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::IndexRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int l_IndexCallback (pRecord, UserData, pUserPtr);
 *
 * Callback used by the IndexRecords() method.
 *
 *=========================================================================*/
int l_IndexCallback (CObRecord* pRecord, const dword UserData, void* pUserPtr) {
  CObSimpleRecordHandler* pHandler = (CObSimpleRecordHandler *) pUserPtr;

  if (pHandler != NULL) pHandler->IndexRecord(pRecord);
  return (0);
}
/*===========================================================================
 *		End of Function l_IndexCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - bool IndexRecords (pCallback);
 *
 * Index all records in the file.
 *
 *=========================================================================*/
bool CObSimpleRecordHandler::IndexRecords (CObCallback* pCallback) {
  dword MapSize;

	/* Clear the current indices */
  m_FormIdMap.Destroy();
  m_EditorIdMap.Destroy();

	/* Set the hash map size */
  MapSize = (dword) ((m_EspFile.GetRecordCount() + 1031) * 1.21);
  m_FormIdMap.InitHashTable(MapSize);
  m_EditorIdMap.InitHashTable(MapSize);

  	/* Add special pseudo-records */
  m_FormIdMap.SetAt(&m_PlayerRef);
  
	/* Index all records in the file */
  m_EspFile.ForEachRecord(l_IndexCallback, 0, this);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::IndexRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleRecordHandler Method - bool Load (pFilename, pCallback);
 *
 *=========================================================================*/
bool CObSimpleRecordHandler::Load (const SSCHAR* pFilename, CObCallback* pCallback) {
  bool Result;

	/* Clear the current information */
  Destroy();

	/* Attempt to load the single file */
  Result = m_EspFile.Load(pFilename, pCallback);
  if (!Result) return (false);

	/* Index all records */
  IndexRecords(NULL);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObSimpleRecordHandler::Load()
 *=========================================================================*/
