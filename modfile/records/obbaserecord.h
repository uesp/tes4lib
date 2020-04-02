/*===========================================================================
 *
 * File:	Obbaserecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 10, 2006
 *
 * Defines the CObBaseRecord class from which all record and group classes
 * will be derived from.
 *
 *=========================================================================*/
#ifndef __OBBASERECORD_H
#define __OBBASERECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../obmoddefs.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Group and record header size in bytes */
  #define OB_BASEHEADER_SIZE	20

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Generic header for groups and records */
  struct obbaseheader_t {
	obrectype_t	Type;		/* Record or group name field */
	dword		Size;		/* Record/group size */
	dword		Data1;		/* General data */
	int		GroupType;	/* Gives the basic group type */
	dword		Data2;		/* General data */
   };

#pragma pack(pop)

	/* Forward class definitions */
  class CObRecordHandler;
  class CObGroup;
  class CObRecord;
  class CObBaseRecord;

	/* Used for load/save callbacks */
  struct obespfilecallback_t {
	float   Progress;
	int64   ProcessRecords;
	int64   TotalRecords;
	int	CallbackInterval;
	dword   UserData;
	void*   pUserPtr;
  };

	/* Array of record pointers */
  typedef CObPtrArray<CObBaseRecord>    CObBaseRecordArray;
  typedef CObRefPtrArray<CObBaseRecord> CObRefBaseRecordArray;

	/* Callback function type */
  typedef int (*FNOBESPFILECALLBACK) (obespfilecallback_t* pData);

	/* Record callbacks */
  typedef int (*OBBASERECORDCALLBACK) (CObBaseRecord* pBaseRecord, const dword UserData, void* pUserPtr);
  typedef int (*OBRECORDCALLBACK)     (CObRecord*     pRecord,     const dword UserData, void* pUserPtr);
  
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Abstract Class CObBaseRecord Definition
 *
 * The base record/group class of a ESP/ESM file. All record and group
 * classes will be derived from this. 
 *
 *=========================================================================*/
class CObBaseRecord {
  DECLARE_OBBASE(CObBaseRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRecordHandler*	m_pParent;
  CObGroup*		m_pParentGroup;

  word			m_CacheFlags;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBaseRecord();
  virtual ~CObBaseRecord();
  virtual void Destroy (void);

	/* Try to add a child record if valid */
  virtual bool AddChildRecord (CObBaseRecord* pNewRecord) = 0;

  	/*  Change one ID for another */
  virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID) = 0;
  virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID) = 0;

	/* Try to delete a child record if valid */
  virtual bool DeleteChildRecord (CObBaseRecord* pRecord) = 0;

	/* Find binary data in the record */
  virtual bool Find     (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL) = 0;
  virtual bool FindText (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL) = 0;

	/* Find child records */
  virtual CObBaseRecord* FindFormID (const obformid_t FormID) = 0;

	/* Fixup the modindex of formids */
  virtual bool FixupFormids (CObFormidFixupArray& FixupArray) = 0;

	/* Get class members */
  virtual const obrectype_t GetRecordType  (void) const = 0;
  virtual       obformid_t  GetFormID      (void) const { return (OB_FORMID_NULL); }
  CObRecordHandler*         GetParent      (void)       { return (m_pParent); }
  CObGroup*                 GetParentGroup (void)       { return (m_pParentGroup); }
  word			    GetCacheFlags  (void)       { return (m_CacheFlags); }
	
	/* Initialize the record with the given data */
  virtual void Initialize (const obbaseheader_t Header) = 0;

  	/* Initialize a new record */
  virtual void InitializeNew (void) = 0;

  	/* Object classifiers */
  virtual bool IsRecord (void) const { return (false); }
  virtual bool IsGroup  (void) const { return (false); }
  virtual bool IsActive (void) const;

	/* Input/output record/group data from file */
  virtual bool ReadData (CObFile& File) = 0;
  virtual bool Write    (CObFile& File) = 0;

	/* Input/output with callback, default is to ignore callback */
  virtual bool ReadData      (CObFile& File, CObCallback* pCallback) { return ReadData(File); }
  virtual bool Write         (CObFile& File, CObCallback* pCallback) { return Write(File); }

	/* Set class members */
  void SetParent      (CObRecordHandler* pHandler) { m_pParent      = pHandler; }
  void SetParentGroup (CObGroup*         pGroup)   { m_pParentGroup = pGroup; }
  void SetCacheFlags  (const dword       Flags)    { m_CacheFlags   = Flags; }

};
/*===========================================================================
 *		End of Class CObBaseRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

  bool ReadObBaseHeader (CObFile& File, obbaseheader_t& Header);

	/* Record and group creation functions */
  CObRecord*     CreateObRecord      (const obbaseheader_t Header);
  CObRecord*     CreateObRecord      (const obrectype_t    Type);
  CObGroup*      CreateObGroup       (const obbaseheader_t Header);
  CObGroup*      CreateObGroup       (const int Type);
  CObGroup*      CreateObRefGroup    (const int Type);
  CObBaseRecord* CreateObRecordGroup (const obbaseheader_t Header);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/

	
#endif
/*===========================================================================
 *		End of File Obbaserecord.H
 *=========================================================================*/
