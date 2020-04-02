/*===========================================================================
 *
 * File:	Obrecordhandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Abstract base class for handling a set of records.
 *
 *=========================================================================*/
#ifndef __OBRECORDHANDLER_H
#define __OBRECORDHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "records/obidrecord.h"
  #include "records/obrefrrecord.h"
  #include "groups/obtypegroup.h"
  #include "records/obrecordmap.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Return values from OnPre/OnPostSave events */
  #define OB_RESULT_USERABORT		-101
  #define OB_RESULT_ERROR		-1
  #define OB_RESULT_OK			0
  #define OB_RESULT_WARNING		1
  #define OB_RESULT_PROMPTRENAMECOPY	1000

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used to edit and update edited records */
  struct obeditrecinfo_t {
	CObRecord*	pOldRecord;		/* Initial version of the record */
	CObRecord*	pNewRecord;		/* Updated version of the record */
	CObRecord*	pRecordCopy;		/* Copy of the old record if available (for undo) */

	CSString	NewEditorID;		/* New editorid if changed */
	bool		HasUpdatedID;

	bool		IsNew;			/* Indicates a newly created record */
	bool		IsRenamed;		/* A record with a changed editorid that has been renamed */
	bool		IsCopy;			/* A record with a changed editorid that has been copied */

	bool		IsHandled;
	bool		NeedsIndex;

	obeditrecinfo_t() {
		pOldRecord  = NULL;
		pNewRecord  = NULL;
		pRecordCopy = NULL;

		HasUpdatedID = false;
		IsNew	     = false;
		IsRenamed    = false;
		IsCopy	     = false;
		IsHandled    = false;
		NeedsIndex   = false;
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecordHandler Definition
 *
 * Description
 *
 *=========================================================================*/
class CObRecordHandler {

  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //virtual void Destroy (void) = 0;

  	/* Change one ID for another */
  //virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID) = 0;
  //virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID) = 0;

  	/* Create a new record of the given type to the file */
  //virtual CObRecord* CreateNewRecord (const obrectype_t Type) = 0;

  	/* Deletes the specified record */
  //virtual bool DeleteRecord (CObRecord* pRecord) = 0;

  	/* Find data operations */
  //virtual dword Find (obfinddata_t& FindData, CObCallback* pCallback) = 0;

  	/* Find records */
  virtual CObRecord*   FindFormID   (const obformid_t FormID)  = 0;
  virtual CObIdRecord* FindEditorID (const SSCHAR*    pString) = 0;

	/* Get the editorID from a formID */
  virtual bool          GetEditorID (CSString& Buffer, const obformid_t FormID) = 0;
  virtual const SSCHAR* GetEditorID (const obformid_t FormID) = 0;

	/* Iterate through records/groups */
  virtual CObRecord* GetFirstRecord (OBMAPPOS& RecordPos) = 0;
  virtual CObRecord* GetNextRecord  (OBMAPPOS& RecordPos) = 0;
  virtual dword      GetNumRecords  (void) = 0;
  virtual CObGroup*  GetTopGroup    (void) = 0;

  	/* Returns the next form ID not currently used by the file */
  virtual obformid_t    GetFreeFormID   (const byte ModIndex = 0) = 0;
  virtual const SSCHAR* GetFreeEditorID (void) = 0;

	/* Access the special player reference */
  virtual CObRefrRecord* GetPlayerReference (void) = 0;

	/* Is the parent the active file or not */
  virtual bool IsActive (void) const = 0;

  	/* Events that occurs before/after a record is updated */
  virtual int OnPreSaveRecord    (obeditrecinfo_t& EditInfo) { return (OB_RESULT_OK); }
  virtual int OnPostSaveRecord   (obeditrecinfo_t& EditInfo) { return (OB_RESULT_OK); }
  virtual int OnCancelEditRecord (obeditrecinfo_t& EditInfo) { return (OB_RESULT_OK); }

  	/* Creates any required indexes */
  //virtual void IndexRecord  (CObRecord*     pRecord) = 0;
  //virtual bool IndexRecords (CObCallback* pCallback) = 0;

};
/*===========================================================================
 *		End of Class CObRecordHandler Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obrecordhandler.H
 *=========================================================================*/
