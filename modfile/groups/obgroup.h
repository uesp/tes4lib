/*===========================================================================
 *
 * File:	Obgroup.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObGroup class from which all other group classes will
 * be derived from.
 *
 *=========================================================================*/
#ifndef __OBGROUP_H
#define __OBGROUP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/oberrorhandler.h"
  #include "../subrecords/obsubrecord.h"
  #include "../records/obbaserecord.h"
  #include "../records/obbasereccont.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions 
 *
 *=========================================================================*/

	/* Group types */
  #define OB_GROUP_NONE		-1		/* Custom type, not official used */
  #define OB_GROUP_TYPE		0
  #define OB_GROUP_WORLDCHILD	1
  #define OB_GROUP_INTCELL	2
  #define OB_GROUP_INTSUBCELL	3
  #define OB_GROUP_EXTCELL	4
  #define OB_GROUP_EXTSUBCELL	5
  #define OB_GROUP_CELLCHILD	6
  #define OB_GROUP_TOPICCHILD	7
  #define OB_GROUP_CELLPERSIST	8
  #define OB_GROUP_CELLTEMP	9
  #define OB_GROUP_CELLDISTANT	10

/*===========================================================================
 *		End of Definitions 
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Group header data that depends on the group type */
  union obgrupheaderdata_t {
	char	ContainsType[OB_RECTYPE_SIZE];
	int	Block;

	struct {
		short XGrid;
		short YGrid;
	 };

	dword ParentFormID;
   };

	/* Group header type */
  struct obgrupheader_t {
	obrectype_t		RecordType;		/* Must be 'GRUP' */
	dword			Size;
	obgrupheaderdata_t	Data;
	int			GroupType;
	dword			Stamp;

		/* Copy operators */
	const obgrupheader_t& operator= (const obbaseheader_t Header) { *this = *(obgrupheader_t *) &Header; return (*this); }
   };

#pragma pack(pop)

	/* Pointer to a class method to create a record object */
  class CObGroup;
  class CObTypeGroup;
  typedef CObGroup* (*OBGROUP_CREATEFUNC) (void);

	/* Structure to hold creation information on groups */
  struct obgroupcreate_t {
	int			GroupType;	/* Group type */
	OBGROUP_CREATEFUNC	CreateMethod;	/* The creation function or static method */
   };

	/* Arrays of groups */
  typedef CObPtrArray<CObGroup>    CObGroupArray;
  typedef CObRefPtrArray<CObGroup> CObRefGroupArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObGroup : public CObBaseRecord {
  DECLARE_OBCLASS(CObGroup, CObBaseRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obgrupheader_t	 m_Header;

  CObBaseRecordContBase* m_pRecords;		/* Child records and groups */
  bool			 m_IsReferenced;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper input/output methods */
  bool WriteGroupSize (CObFile& File, const dword Offset);

  
  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObGroup(const bool UseRef = false);
  virtual ~CObGroup();
  virtual void Destroy (void);

	/* Attempt to add a child record (undefined for a base group) */
  virtual bool AddChildRecord (CObBaseRecord* ) { return (false); }

	/* Add a record that may already exist in the group */
  bool AddExistingRecord (CObRecord* pNewRecord);

	/* Simply adds the given record */
  void AddRecord (CObRecord* pRecord) { m_pRecords->Add((CObBaseRecord *) pRecord); }
   
	/* Change one ID for another */
  virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID);
  virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID);

	/* Compares a group to see if it is the same type */
  virtual bool Compare (CObGroup* pGroup);

  	/* Return a new instance of the class */
  static CObGroup* Create (void) { return new CObGroup; }

	/* Creates a new matching subgroup */
  CObGroup* CreateSubGroup (CObGroup* pMatchGroup);

  	/* Delete a child record */
  virtual bool DeleteChildRecord (CObBaseRecord* pRecord) { return m_pRecords->Delete(pRecord); }

  	/* Simply deletes the given record */
  bool DeleteRecord (CObRecord* pRecord) { return m_pRecords->Delete((CObBaseRecord *) pRecord); }
     
	/* Find information in the record */
  virtual bool Find     (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL);
  virtual bool FindText (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL);

  	/* Find a child record based on its formID */
  CObBaseRecord* FindFormID (const obformid_t FormID);

	/* Find child groups based on type and content */
  CObGroup* FindFirstGroup (const obformid_t FormID, int& GroupPos) { GroupPos = -1; return FindNextGroup(FormID, GroupPos); }
  CObGroup* FindNextGroup  (const obformid_t FormID, int& GroupPos);

	/* Find a matching subgroup */
  CObGroup* FindSubGroup (CObGroup* pMatchGroup);

  	/* Fixup the modindex of formids */
  virtual bool FixupFormids (CObFormidFixupArray& FixupArray);

  	/* Record interation methods */
  int ForEachBaseRecord (OBBASERECORDCALLBACK Callback, const dword UserData, void* pUserPtr);
  int ForEachRecord     (OBRECORDCALLBACK     Callback, const dword UserData, void* pUserPtr);

	/* Get class members */
  const obrectype_t      GetRecordType (void) const { return (m_Header.RecordType); }
  int		         GetType       (void) const { return (m_Header.GroupType); }
  dword		         GetStamp      (void) const { return (m_Header.Stamp); }
  bool                   IsGroup       (void) const { return (true); }
  obgrupheader_t&        GetHeader     (void)       { return (m_Header); }
  dword		         GetNumRecords (void)              { return (m_pRecords->GetSize()); }
  CObBaseRecord*         GetRecord     (const dword Index) { return (m_pRecords->GetAt(Index)); }
  CObBaseRecordContBase& GetRecords    (void)       { return (*m_pRecords); }

  	/* Access groups */
  CObTypeGroup* GetTypeGroup (const obrectype_t Type);
    	
  	/* Initialize the record with the given header */
  virtual void Initialize (const obbaseheader_t Header) { m_Header = Header; }
  virtual void Initialize (const int            Type)   { m_Header.RecordType = OB_NAME_GRUP; m_Header.GroupType = Type; m_Header.Size = 0; m_Header.Stamp = 0; m_Header.Data.ParentFormID = 0; }

  	/* Initialize a new file */
  virtual void InitializeNew (void) { }

	/* Read in group data */
  virtual bool ReadData (CObFile& File) { return ReadData(File, NULL); }
  virtual bool ReadData (CObFile& File, CObCallback* pCallback);

  	/* Output the group to a file */
  virtual bool Write (CObFile& File) { return Write(File, NULL); }
  virtual bool Write (CObFile& File, CObCallback* pCallback);

 };
/*===========================================================================
 *		End of Class CObGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefGroup : public CObGroup {

public:

  CObRefGroup() : CObGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefGroup); }

};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obgroup.H
 *=========================================================================*/
