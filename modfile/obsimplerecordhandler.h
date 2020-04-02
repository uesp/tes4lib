/*===========================================================================
 *
 * File:	Obsimplerecordhandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Handles a single file of records.
 *
 *=========================================================================*/
#ifndef __OBSIMPLERECORDHANDLER_H
#define __OBSIMPLERECORDHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecordhandler.h"
  #include "obespfile.h"
  #include "../common/obarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSimpleRecordHandler Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSimpleRecordHandler : public CObRecordHandler {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObEspFile		 m_EspFile;		/* The single file */

  CObFullFormIdRecordMap m_FormIdMap;		/* Fast lookup maps */
  CObEditorIdRecordMap	 m_EditorIdMap;

  dword			 m_NextFreeFormID;	/* Used to find a free ID */
  dword			 m_NextFreeEditorID;

  CObRefrRecord		 m_PlayerRef;		/* Special pseudo-records */


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSimpleRecordHandler (const dword HashMapSize = OBESPFILE_DEFAULT_MAPSIZE);
  virtual ~CObSimpleRecordHandler() { Destroy(); }
  virtual void Destroy (void);

  	/* Change one ID for another */
  virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID) { return m_EspFile.ChangeFormID(NewID, OldID); }
  virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID) { return m_EspFile.ChangeEditorID(pNewID, pOldID); }

  	/* Create a new record of the given type to the file */
  CObRecord* CreateNewRecord (const obrectype_t Type);

  	/* Deletes the specified record */
  virtual bool DeleteRecord (CObRecord* pRecord);

  	/* Find data operations */
  virtual dword Find (obfinddata_t& FindData, CObCallback* pCallback) { return m_EspFile.Find(FindData, pCallback); }

  	/* Find records */
  virtual CObRecord*   FindFormID   (const obformid_t FormID);
  virtual CObIdRecord* FindEditorID (const SSCHAR*    pString);

	/* Get the editorID from a formID */
  virtual bool          GetEditorID (CSString& Buffer, const obformid_t FormID);
  virtual const SSCHAR* GetEditorID (const obformid_t FormID);

  	/* Iterate through records/groups */
  virtual CObRecord* GetFirstRecord (OBMAPPOS& RecordPos) { return m_FormIdMap.GetFirstRecord(RecordPos); }
  virtual CObRecord* GetNextRecord  (OBMAPPOS& RecordPos) { return m_FormIdMap.GetNextRecord(RecordPos); }
  virtual dword      GetNumRecords  (void)                { return m_FormIdMap.GetRecordCount(); }
  virtual CObGroup*  GetTopGroup    (void)		  { return &m_EspFile.GetRecords(); }

	/* Get the next available formID that is not currently in use */
  virtual obformid_t    GetFreeFormID   (const byte ModIndex = 0);
  virtual const SSCHAR* GetFreeEditorID (void);

	/* Get class members */
  CObEspFile&    GetEspFile         (void) { return (m_EspFile); }
  CObRefrRecord* GetPlayerReference (void) { return (&m_PlayerRef); }

	/* Adds the given record to the record indexes */
  virtual void IndexRecord  (CObRecord*     pRecord);
  virtual bool IndexRecords (CObCallback* pCallback);

	/* Is the parent the active file or not */
  virtual bool IsActive (void) const { return (true); }

	/* Load the given file */
  bool Load (const SSCHAR* pFilename, CObCallback* pCallback = NULL);

 };
/*===========================================================================
 *		End of Class CObSimpleRecordHandler Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obsimplerecordhandler.H
 *=========================================================================*/
