/*===========================================================================
 *
 * File:	ObMultirecordhandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Handles a multiple ESM/ESM files.
 *
 *=========================================================================*/
#ifndef __OBMULTIRECORDHANDLER_H
#define __OBMULTIRECORDHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecordhandler.h"
  #include "obespfile.h"
  #include "../common/obarray.h"
  #include "../common/obblockallocator.h"
  #include "obeventhandler.h"
  #include "obundoitem.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return values for duplicate checking */
  #define OBE_DUPLICATE_FALSE	0
  #define OBE_DUPLICATE_TRUE	1
  #define OBE_DUPLICATE_ERROR	-1

	/* Default size of the new groups array */
  #define OBE_DEFAULT_NEWGROUP_SIZE 150000
  
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definitions */
  class CObMultiRecordHandler;

	/* Used to load an active plugin and multiple masters */
  struct obfileloadinfo_t {
	CSStringArray	m_MasterFilenames;
	CSString	m_ActiveFilename;
  };

	/* Used when indexing records */
  struct obindexinfo_t {
    CObMultiRecordHandler* pHandler;
    bool		   FirstFile;
    dword		   ModIndex;
    CObCallback*	   pCallback;
    dword		   RecordCount;
  };

	/* Used to handle duplicate IDs */
  struct obdupformidinfo_t {
	CObRecord*	pRecord;
	dword		ModIndex;
  };

  struct obdupeditoridinfo_t {
	CObIdRecord*	pRecord;
	dword		ModIndex;
  };

  typedef CObPtrArray<obdupformidinfo_t>   CObDupFormIdArray;
  typedef CObPtrArray<obdupeditoridinfo_t> CObDupEditorIdArray;

	/* Test block allocators */
  typedef TObBlockAllocator<CObRefGroup>       CObRefGroupAllocator;
  typedef TObBlockAllocator<CObRefTypeGroup>   CObRefTypeGroupAllocator;
  typedef TObBlockAllocator<CObRefFormIDGroup> CObRefFormIDGroupAllocator;
  typedef TObBlockAllocator<CObRefBlockGroup>  CObRefBlockGroupAllocator;
  typedef TObBlockAllocator<CObRefGridGroup>   CObRefGridGroupAllocator;

	/* Record handler options */
  struct obmultirecoptions_t {
	obundooptions_t Undo;

	bool		EnableBackup;

	bool		EnableBackupOnSave;
	int		MaxBackupCount;
	int		MaxBackupSize;
	CSString	BackupPath;
	CSString	FullBackupPath;

	bool		EnableAutoBackup;
	int		AutoBackupTime;

	bool		EnableCaching;


	obmultirecoptions_t() {
		BackupPath     = "backup\\";
		EnableBackup   = true;

		EnableBackupOnSave = true;
		MaxBackupCount     = 0;
		MaxBackupSize      = 0;

		EnableAutoBackup   = false;
		AutoBackupTime     = 10;

		EnableCaching      = true;
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObMultiRecordHandler Definition
 *
 * Description
 *
 *=========================================================================*/
class CObMultiRecordHandler : public CObRecordHandler {
  friend int l_IndexFileCallback (CObRecord* pRecord, const dword UserData, void* pUserPtr);

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CEspFileArray			m_MasterFiles;		/* Master dependancies */
  CObEspFile			m_ActiveFile;		/* The active file */

  CObRefFileGroup		m_TopFileGroup;		/* Head of overall record tree */
  CObGroupArray			m_NewGroups;

  CObRecordArray		m_NewRecords;		/* Temporary array for new records before saving */

  CObFullFormIdRecordMap	m_FormIdMap;		/* Fast lookup maps */
  CObEditorIdRecordMap		m_EditorIdMap;

  dword				m_NextFreeFormID;	/* Used to find a free ID */
  dword				m_NextFreeEditorID;

  CObDupFormIdArray		m_DuplicateFormIDs;	/* Used during loading */
  CObDupEditorIdArray		m_DuplicateEditorIDs;

  CObEventHandler		m_EventHandler;

  CObUndoItemArray		m_UndoItems;		/* Records undo actions */
  
  CObRefGroupAllocator		m_GroupAllocator;	/* Test block allocators */
  CObRefTypeGroupAllocator	m_TypeGroupAllocator;
  CObRefFormIDGroupAllocator	m_FormIDGroupAllocator;
  CObRefBlockGroupAllocator	m_BlockGroupAllocator;
  CObRefGridGroupAllocator	m_GridGroupAllocator;

  static obmultirecoptions_t	m_Options;		/* Handler options */

  CObRefrRecord			m_PlayerRef;		/* Special pseudo-records */


public:
  static CObEspFile	 m_OblivionMaster;	/* One global copy of Oblivion.esm */


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Attempt to create a new master file */
  CObEspFile* AddMaster (void);

  	/* Check and handle duplicate IDs */
  bool CheckDuplicateFormId   (CObRecord*   pRecord);
  bool CheckDuplicateEditorId (CObIdRecord* pRecord);

  	/* Create a new record of the given type to the file */
  CObRecord* CreateNewRecord (const obrectype_t Type);

	/* Create the top level record tree */
  bool      CreateRecordTree    (CObCallback* pCallback);
  bool      CreateRecordTree    (CObEspFile* pFile, CObCallback* pCallback);
  bool      CreateRecordTree    (CObGroup* pDestGroup, CObGroup* pSourceGroup, CObCallback* pCallback);
  bool      CreateTreeAddRecord (CObGroup* pDestGroup, CObRecord* pRecord, const bool FirstFile);
  CObGroup* CreateTreeFindGroup (CObGroup* pDestGroup, CObGroup*  pGroup,  const bool FirstFile);

  	/* Csv import/export helper routines */
  CObIdRecord* CreateIDRecordFromCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row, CObIdRecord*& pOldRecord);
  
  	/* Deletes the specified record */
  virtual bool DeleteRecord    (CObRecord* pRecord);
  virtual bool DeleteNewRecord (CObRecord* pRecord);
  virtual bool RemoveNewRecord (CObRecord* pRecord);

	/* Fixup the formids of all mods currently loaded */
  bool CreateFormidFixup (CObFormidFixupArray& FixupArray, CObEspFile* pFile, const byte ModIndex);
  bool FixupFormids      (void);
  bool FixupFormids      (CObEspFile* pFile, const byte ModIndex);
  bool HasFixupChanged   (CObFormidFixupArray& FixupArray);

	/* Find a version of the given record in a master file */
  CObRecord* FindNonActiveRecord (CObRecord* pRecord);

	/* Handle any duplicates found during an indexing */
  bool HandleDuplicateFormIDs   (void);
  bool HandleDuplicateEditorIDs (void);

	/* Index records in a file */
  virtual bool IndexFile       (CObEspFile* pFile, const bool FirstFile, const dword ModIndex, CObCallback* pCallback);
          bool IndexDuplicates (void);

	  	/* Adds the given record to the record indexes */
  virtual void IndexRecord      (CObRecord* pRecord);
  virtual bool IndexRecords     (CObCallback* pCallback);
  virtual bool IndexCheckRecord (CObRecord* pRecord, const dword ModIndex);

	/* Helper input/output methods */
  bool LoadMasterFile (const SSCHAR* pFilename, const dword ModIndex, CObCallback* pCallback);

  	/* Moves the given new record into the active file and record tree */
  bool MoveNewRecord (CObRecord* pRecord);

	/* Remove a record from any indexes */
  bool RemoveFromIndex (CObRecord* pRecord);

  	/* Rename the editorid of a record */
  CObIdRecord* RenameIDRecordPriv (CObIdRecord* pRecord, const SSCHAR* pNewEditorID, const bool CreateUndo = false);

  	/* Updates the masters of the active file */
  bool SetActiveMasters (void);

	/* Remove undo items over the limit */
  void TrimUndoItems (void);

	/* Updates the overall record tree for the given record */
  bool UpdateRecordTree (CObRecord* pNewRecord, CObRecord* pOldRecord); 

	/* Helper record update method */
  bool UpdateNewEditRecord (obeditrecinfo_t& EditRecInfo);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObMultiRecordHandler (const dword HashMapSize = OBESPFILE_DEFAULT_MAPSIZE);
  virtual ~CObMultiRecordHandler() { Destroy(); }
  virtual void Destroy (void);

  	/* Change one ID for another */
  virtual dword ChangeFormID        (const obformid_t NewID, const obformid_t OldID) { return ChangeFormIDIndex(NewID, OldID, 0); }
  virtual dword ChangeEditorID      (const SSCHAR*   pNewID, const SSCHAR*   pOldID) { return ChangeEditorIDIndex(pNewID, pOldID, 0); }
  virtual dword ChangeFormIDIndex   (const obformid_t NewID, const obformid_t OldID, const dword StartModIndex);
  virtual dword ChangeEditorIDIndex (const SSCHAR*   pNewID, const SSCHAR*   pOldID, const dword StartModIndex);

	/* Removes the given record from the active file */
  CObRecord* CleanRecord (CObRecord* pRecord);

  	/* Count records in current files */
  dword CountAllRecords (void);

	/* Creates a new copy of the given record */
  bool CreateIDRecordCopy (CObIdRecord* pRecord, const char* pEditorID);
  
  	/* Create new undo actions */
  CObUndoItem* CreateUndoClean  (CObRecord* pRecord);
  CObUndoItem* CreateUndoAdd    (obeditrecinfo_t& EditInfo);
  CObUndoItem* CreateUndoAdd    (CObRecord* pRecord, const char* pNewEditorID);
  CObUndoItem* CreateUndoUpdate (CObRecord* pRecord);
  CObUndoItem* CreateUndoUpdate (obeditrecinfo_t& EditRecInfo);

	/* Deletes the specified master file */
  bool DeleteMaster (CObEspFile* pMaster);

	/* Find data operations */
  virtual dword Find (obfinddata_t& FindData, CObCallback* pCallback);

  	/* Find records */
  virtual CObRecord*   FindFormID   (const obformid_t FormID);
  virtual CObIdRecord* FindEditorID (const SSCHAR*    pString);

	/* Find the mod index of the given file */
  int FindModIndex (const SSCHAR* pFilename);

	/* Access the static options member */
  static obmultirecoptions_t& GetOptions (void) { return (m_Options); }

	/* Access the event handler member */
  CObEventHandler& GetEventHandler (void) { return (m_EventHandler); }

	/* Get the editorID from a formID */
  virtual bool          GetEditorID (CSString& Buffer, const obformid_t FormID);
  virtual const SSCHAR* GetEditorID (const obformid_t FormID);

  	/* Iterate through records/groups */
  virtual CObRecord* GetFirstRecord (OBMAPPOS& RecordPos) { return m_FormIdMap.GetFirstRecord(RecordPos); }
  virtual CObRecord* GetNextRecord  (OBMAPPOS& RecordPos) { return m_FormIdMap.GetNextRecord(RecordPos); }
  virtual dword      GetNumRecords  (void)                { return m_FormIdMap.GetRecordCount(); }
  virtual CObGroup*  GetTopGroup    (void)                { return (&m_TopFileGroup); }

	/* Access a top level type group */
  virtual CObTypeGroup* GetTypeGroup (const obrectype_t Type) { return m_TopFileGroup.GetTypeGroup(Type); }

	/* Get the next available formID that is not currently in use */
  virtual obformid_t    GetFreeFormID       (const byte ModIndex = 0);
  virtual obformid_t    GetActiveFreeFormID (void) { return GetFreeFormID(m_ActiveFile.GetModIndex()); }
  virtual const SSCHAR* GetFreeEditorID     (void);

	/* Get class members */
  dword          GetNumMaster       (void) { return (m_MasterFiles.GetSize()); }
  CEspFileArray& GetMasterFiles     (void) { return (m_MasterFiles); }
  CObEspFile&    GetActiveFile      (void) { return (m_ActiveFile); }
  CObRefrRecord* GetPlayerReference (void) { return (&m_PlayerRef); }

    	/* Get undo information */
  dword             GetNumUndoItems (void) { return (m_UndoItems.GetSize() > 0); }
  CObUndoItem*      GetTopUndoItem  (void) { return (m_UndoItems.GetSize() == 0 ? NULL : m_UndoItems.GetAt(m_UndoItems.GetSize() - 1)); }
  CObUndoItemArray& GetUndoItems    (void) { return (m_UndoItems); }

	/* Check a new editorid for validity */
  bool IsValidNewEditorID (const char* pEditorID);

	/* Import routines */
  bool ImportCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row);
  bool ImportCsv    (dword& NewRecords, CCsvFile& CsvFile);

	/* Is the parent the active file or not */
  virtual bool IsActive (void) const { return (false); }

  	/* Load masters and active plugins */
  bool Load (obfileloadinfo_t& LoadInfo, CObCallback* pCallback = NULL);

    	/* Move the given record to the active file */
  bool       MakeRecordActive     (CObRecord* pRecord);
  CObRecord* MakeRecordActivePriv (CObRecord* pRecord, const bool Index);

	/* Prepare for a new file */
  bool NewFile (void);

	/* Events that occurs before/after a record is updated */
  virtual int OnPreSaveCheckEditorID (obeditrecinfo_t& EditRecInfo);
  virtual int OnPreSaveRecord        (obeditrecinfo_t& EditRecInfo);
  virtual int OnPostSaveRecord       (obeditrecinfo_t& EditRecInfo);
  virtual int OnCancelEditRecord     (obeditrecinfo_t& EditRecInfo);

	/* Prepares a new record for editing */
  CObRecord* PrepareNewRecord (const obrectype_t RecordType);

	/* Rename a record's editorid */
  bool RenameIDRecord (CObIdRecord* pRecord, const SSCHAR* pNewEditorID);

	/* Perform an undo */
  bool PerformUndo       (void);
  bool PerformUndo       (CObUndoItem* pUndoItem);
  bool PerformAddUndo    (CObUndoItem* pUndoItem);
  bool PerformCleanUndo  (CObUndoItem* pUndoItem);
  bool PerformUpdateUndo (CObUndoItem* pUndoItem);
  bool PerformUndoTo     (CObUndoItem* pUndoItem);

	/* Save the active file */
  bool Save (const SSCHAR* pFilename, CObCallback* pCallback = NULL) { return m_ActiveFile.Save(pFilename, pCallback); }

	/* Toggle record flags */
  CObRecord* ToggleIgnoreFlag (CObRecord* pRecord);
  CObRecord* ToggleDeleteFlag (CObRecord* pRecord);
  CObRecord* ToggleQuestFlag  (CObRecord* pRecord);

};
/*===========================================================================
 *		End of Class CObMultiRecordHandler Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObMultiRecordhandler.H
 *=========================================================================*/
