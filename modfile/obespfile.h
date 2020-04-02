/*===========================================================================
 *
 * File:	Obespfile.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObEspFile class for handling ESP files. The ESM file class
 * is derived from this.
 *
 *=========================================================================*/
#ifndef __OBESPFILE_H
#define __OBESPFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "records/obbasereccont.h"
  #include "records/obreccont.h"
  #include "records/obrecordmap.h"

  #include "groups/obgroup.h"
  #include "groups/obtypegroup.h"
  #include "groups/obformidgroup.h"
  #include "groups/obblockgroup.h"
  #include "groups/obgridgroup.h"

  #include "records/obachrrecord.h"
  #include "records/obacrerecord.h"
  #include "records/obactirecord.h"
  #include "records/obalchrecord.h"
  #include "records/obammorecord.h"
  #include "records/obaniorecord.h"
  #include "records/obarmorecord.h"
  #include "records/obapparecord.h"
  #include "records/obbookrecord.h"
  #include "records/obbsgnrecord.h"
  #include "records/obcellrecord.h"
  #include "records/obclmtrecord.h"
  #include "records/obclotrecord.h"
  #include "records/obcontrecord.h"
  #include "records/obcrearecord.h"
  #include "records/obdialrecord.h"
  #include "records/obdoorrecord.h"
  #include "records/obenchrecord.h"
  #include "records/obfactrecord.h"
  #include "records/obflorrecord.h"
  #include "records/obfurnrecord.h"
  #include "records/obidlerecord.h"
  #include "records/obingrrecord.h"
  #include "records/obinforecord.h"
  #include "records/obkeymrecord.h"
  #include "records/oblandrecord.h"
  #include "records/oblighrecord.h"
  #include "records/oblscrrecord.h"
  #include "records/obltexrecord.h"
  #include "records/oblvlcrecord.h"
  #include "records/oblvlirecord.h"
  #include "records/oblvsprecord.h"
  #include "records/obmgefrecord.h"
  #include "records/obmiscrecord.h"
  #include "records/obnpcrecord.h"
  #include "records/obpackrecord.h"
  #include "records/obpgrdrecord.h"
  #include "records/obqustrecord.h"
  #include "records/obracerecord.h"
  #include "records/obrefrrecord.h"
  #include "records/obregnrecord.h"
  #include "records/obscptrecord.h"
  #include "records/obslgmrecord.h"
  #include "records/obsounrecord.h"
  #include "records/obspelrecord.h"
  #include "records/obsgstrecord.h"
  #include "records/obstatrecord.h"
  #include "records/obtes4record.h"
  #include "records/obwatrrecord.h"
  #include "records/obweaprecord.h"
  #include "records/obwrldrecord.h"
  #include "records/obwthrrecord.h"

  #include "groups/obfilegroup.h"

  #include "obrecordhandler.h"

/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* First automatic form ID used */
  #define OBESPFILE_FIRST_FORMID   0x1000
  #define OBESPFILE_FIRST_EDITORID 1
  #define OBESPFILE_LAST_EDITORID  900000000

	/* Default size of record maps */
  #define OBESPFILE_DEFAULT_MAPSIZE 1300001

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEspFile Definition
 *
 * Handles a single ESP plugin file for Oblivion. An ESP is simply defined 
 * to be a collection of records and groups.
 *
 *=========================================================================*/
class CObEspFile : public CObRecordHandler {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObFile		m_File;			/* File object used for I/O operations */
  CSString		m_Filename;		/* Filename as last loaded/saved */
  CSString		m_ShortFilename;

  byte			m_ModIndex;
  bool			m_IsActive;
  dword			m_CacheFlags;

  CObFileGroup		m_Records;  		/* Collection of groups and records */
 
  CObTes4Record*	m_pHeader;		/* Reference to the file header */

  CObRecordHandler*	m_pParent;		/* Parent record handler */


  /*---------- Begin Protected Class Methods --------------------*/
protected:

    	/* Create a top level group record */
  bool          CreateTopLevelGroup (CObBaseRecord* pNewRecord);
  CObTypeGroup* CreateTopLevelGroup (const obrectype_t Type);

	/* Find a position to insert a top level group at */
  CObBaseRecord* FindTopGroupInsertPos (const obrectype_t Type);

	/* Input/output helper methods */
  virtual bool Read  (CObCallback* pCallback = NULL);
  virtual bool Write (CObCallback* pCallback = NULL);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEspFile();
  virtual ~CObEspFile();
  virtual void Destroy (void);

	/* Add the given record to the file */
  virtual bool AddRecord (CObRecord* pRecord);

	/* Add a master file definition */
  virtual void AddMaster (const SSCHAR* pMaster, const int64 FileSize) { if (m_pHeader != NULL) m_pHeader->AddMaster(pMaster, FileSize); }

	/* Change one ID for another */
  virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID) { return m_Records.ChangeFormID(NewID, OldID); }
  virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID) { return m_Records.ChangeEditorID(pNewID, pOldID); }
  
  	/* Create a new record of the given type to the file */
  virtual CObRecord* CreateNewRecord (const obrectype_t Type); 

	/* Deletes the specified record */
  virtual bool DeleteRecord (CObRecord* pRecord);

  	/* Find information in the record */
  virtual dword Find (obfinddata_t& FindData, CObCallback* pCallback);
	
	/* Fixup the formids of all records in file */
  virtual bool FixupFormids (CObFormidFixupArray& FixupArray) { return m_Records.FixupFormids(FixupArray); }

	/* Record interation methods */
  virtual int ForEachBaseRecord (OBBASERECORDCALLBACK Callback, const dword UserData, void* pUserPtr) { return m_Records.ForEachBaseRecord(Callback, UserData, pUserPtr); }
  virtual int ForEachRecord     (OBRECORDCALLBACK     Callback, const dword UserData, void* pUserPtr) { return m_Records.ForEachRecord(Callback, UserData, pUserPtr); }

	/* Access the top level groups/records */
  CObBaseRecord* GetTopLevelRecord     (const dword Index) { return m_Records.GetRecord(Index); }
  dword          GetNumTopLevelRecords (void)              { return m_Records.GetNumRecords(); }

	/* Access groups */
  CObTypeGroup* GetTypeGroup (const obrectype_t Type);

	/* Get class methods */
  CObTes4Record*    GetHeader        (void) { return (m_pHeader); }
  const SSCHAR*     GetFilename      (void) { return (m_Filename); }
  const SSCHAR*     GetShortFilename (void) { return (m_ShortFilename); }
  CObRecordHandler* GetParent        (void) { return (m_pParent); }
  int		    GetRecordCount   (void) { return (m_pHeader ? m_pHeader->GetRecordCount() : 0); }
  byte		    GetModIndex      (void) { return (m_ModIndex); }
  CObFileGroup&     GetRecords       (void) { return (m_Records); }
  virtual CObGroup* GetTopGroup      (void) { return (&m_Records); }
  dword		    GetCacheFlags    (void) { return (m_CacheFlags); }

    	/* Initialize a new file */
  void InitializeNew (void);

	/* Main input/output methods */
  virtual bool Load (const SSCHAR* pFilename, CObCallback* pCallback = NULL);
  virtual bool Save (const SSCHAR* pFilename, CObCallback* pCallback = NULL);

	/* Set class members */
  void SetParent   (CObRecordHandler* pParent) { m_pParent  = pParent; }
  void SetFilename (const SSCHAR*     pString) { m_Filename = pString;  m_ShortFilename = m_Filename;  m_ShortFilename.ReverseTruncate("\\:/"); }
  void SetModIndex (const byte        Value)   { m_ModIndex = Value; }
  
  	/* CObRecordHandler virtual methds, just pass onto parent handler */
  virtual CObRecord* 	 FindFormID	    (const obformid_t FormID)			 { return (m_pParent ? m_pParent->FindFormID(FormID) : NULL); }
  virtual CObIdRecord*	 FindEditorID	    (const SSCHAR*    pString)			 { return (m_pParent ? m_pParent->FindEditorID(pString) : NULL); }
  virtual bool           GetEditorID	    (CSString& Buffer, const obformid_t FormID)	 { return (m_pParent ? m_pParent->GetEditorID(Buffer, FormID) : NULL); }
  virtual const SSCHAR*  GetEditorID	    (const obformid_t FormID)			 { return (m_pParent ? m_pParent->GetEditorID(FormID) : NULL); }
  virtual CObRecord*	 GetFirstRecord     (OBMAPPOS& RecordPos)			 { return (m_pParent ? m_pParent->GetFirstRecord(RecordPos) : NULL); }
  virtual CObRecord*	 GetNextRecord      (OBMAPPOS& RecordPos)			 { return (m_pParent ? m_pParent->GetNextRecord(RecordPos) : NULL); }
  virtual dword		 GetNumRecords      (void)					 { return (m_pParent ? m_pParent->GetNumRecords() : 0); }
  virtual obformid_t     GetFreeFormID      (const byte ModIndex = 0)			 { return (m_pParent ? m_pParent->GetFreeFormID(ModIndex) : 0); }
  virtual const SSCHAR*  GetFreeEditorID    (void)					 { return (m_pParent ? m_pParent->GetFreeEditorID() : ""); }
  virtual bool           IsActive           (void) const                                 { return (m_IsActive); }
  virtual CObRefrRecord* GetPlayerReference (void)                                       { return (m_pParent ? m_pParent->GetPlayerReference() : NULL); }

		/* Set class members */
  void SetActive      (const bool  Value) { m_IsActive = Value; }
  void ModRecordCount (const int   Delta) { if (m_pHeader) m_pHeader->ModRecordCount(Delta); }
  void SetCacheFlags  (const dword Flags) { m_CacheFlags = Flags; }

};
/*===========================================================================
 *		End of Class CObEspFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
  typedef CObPtrArray<CObEspFile>    CEspFileArray;
  typedef CObRefPtrArray<CObEspFile> CEspFileRefArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
  obreccreate_t* FindObRecCreate (const obrectype_t Type);
  obreccreate_t* FindObRecCreate (const SSCHAR*     pName);

  bool IsObTopLevelGroup (const obrectype_t Type);
  
  extern const obrectype_t* s_TopLevelTypeOrder[];
  extern const obrectype_t* s_TopLevelTypes[];

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obespfile.H
 *=========================================================================*/
