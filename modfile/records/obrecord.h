/*===========================================================================
 *
 * File:	ObRecord.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObRecord class from which all main record classes 
 * will be derived from.
 *
 *=========================================================================*/
#ifndef __OBRECORD_H
#define __OBRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/obmemfile.h"
  #include "../subrecords/obdatasubrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/oblongsubrecord.h"
  #include "../subrecords/obwordsubrecord.h"
  #include "../subrecords/obformidsubrecord.h"
  #include "../subrecords/obsubreccont.h"
  #include "../subrecords/obstringsubrecord.h"
  #include "../subrecords/obfloatsubrecord.h"
  #include "obbaserecord.h"
  #include "obrecordfield.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Record flags */
  #define OB_RECFLAG_MASTER         0x00000001
  #define OB_RECFLAG_DELETED        0x00000020
  #define OB_RECFLAG_CASTSHADOWS    0x00000200
  #define OB_RECFLAG_QUESTITEM      0x00000400
  #define OB_RECFLAG_INITDISABLED   0x00000800
  #define OB_RECFLAG_IGNORED        0x00001000
  #define OB_RECFLAG_VISIBLEDISTANT 0x00008000
  #define OB_RECFLAG_DANGEROUS      0x00020000
  #define OB_RECFLAG_COMPRESSED     0x00040000
  #define OB_RECFLAG_CANTWAIT       0x00080000
  
	/* Used when compressing data for output (arbitrary) */
  #define OB_ZLIBCOMPRESS_BUFFER 8192

	/* The compression level to use */
  #define OB_ZLIB_DEFLATELEVEL 6

	/* Default buffer sizes used for input and output operations */
  #define OB_ZLIB_BUFFERSIZE 200000

  	/* Static array for creating the record's subrecords */
  #define DECLARE_OBSUBRECCREATE()	protected: \
		 static  const obsubreccreate_t   s_SubrecCreate; \
		 static  const obsubrecentries_t  s_SubrecEntries[]; \
		 virtual const obsubreccreate_t*  GetSubrecCreate     (void) const { return (&s_SubrecCreate); }

	/* Used to define a subrecord creation array */
  #define BEGIN_OBSUBRECCREATE(Class, BaseClass) \
	const obsubreccreate_t   Class::s_SubrecCreate = { &BaseClass::s_SubrecCreate, Class::s_SubrecEntries }; \
	const obsubrecentries_t  Class::s_SubrecEntries[] = {

  #define DEFINE_OBSUBRECCREATE(Name, Method) { &Name, Method }, 

  #define END_OBSUBRECCREATE() { NULL, NULL } }; 

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Record header type */
  struct obrecheader_t {
	obrectype_t	RecordType;
	dword		Size;
	dword		Flags1;
	obformid_t	FormID;
	dword		Flags2;

		/* Copy operators */
	const obrecheader_t& operator= (const obbaseheader_t& Header) { *this = *(obrecheader_t *) &Header; return (*this); }
   };


#pragma pack(pop)

	/* Pointer to a class method to create a record object */
  class CObRecord;
  typedef CObRecord* (*OBREC_CREATEFUNC) (void);

	/* Structure to hold information on record creation */
  struct obreccreate_t {
	const obrectype_t*	pType;
	OBREC_CREATEFUNC	CreateMethod;
   };

	/* Array of record pointers */
  typedef CObPtrArray<CObRecord>    CObRecordArray;
  typedef CObRefPtrArray<CObRecord> CObRefRecordArray;
  
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecord Definition
 *
 * The base record class from which all other record classes will be derived
 * from. The base class considers the record data as merely a collection
 * of sub-records and groups.
 *
 * sizeof(CObRecord) = 36
 *	Vtable		= 4
 *	Header		= 20
 *	Subrecords	= 12
 *	Members		= 0
 *	Total =========== 36
 *
 *=========================================================================*/
class CObRecord : public CObBaseRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObRecord, CObBaseRecord)


  /*---------- Begin Protected Class Members --------------------*/
protected:
  obrecheader_t		m_Header;	/* Record header data */
  //CObSubrecContainer	m_Subrecords;	/* Collection of subrecords */
  CObSubrecordArray	m_Subrecords;

  long			m_UserData;	/* Custom user data */

	/* Static buffers used when loading and saving */
  static CObMemFile	s_MemFile;
  static byte*		s_pTempBuffer;
  static dword		s_TempBufferSize;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Find a subrecord creation method from this and any any classes */
  OBSUBREC_CREATEFUNC FindSubrecCreate (const obrectype_t Type);

	/* Change all formid subrecords of the given type */
  virtual dword ChangeFormidSubrecords (const obrectype_t Type, const obformid_t NewID, const obformid_t OldID);
  virtual dword ChangeFormidSubrecords (const obformid_t NewID, const obformid_t OldID);

	/* Fixup all formid subrecords of the given type */
  virtual bool FixupFormidSubrecords (const obrectype_t Type, CObFormidFixupArray& FixupArray);
  virtual bool FixupFormidSubrecords (CObFormidFixupArray& FixupArray);

	/* Initialize a map of all class fields */
  bool InitializeFieldMap (CObRecFieldIDMap& s_FieldIDMap);

	/* Input and output helpers */
  bool ReadSubRecords      (CObFile& File);
  bool ReadCompressedData  (CObFile& File);
  bool WriteSubRecords     (CObFile& File);
  bool WriteCompressedData (CObFile& File);
  bool WriteRecordSize     (CObFile& File, const int Offset);
  bool WriteDeflate        (CObFile& File, CObMemFile& RecordData);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRecord();
  virtual ~CObRecord();
  virtual void Destroy (void);

	/* Records cannot contain other records */
  bool AddChildRecord    (CObBaseRecord* ) { return (false); }
  bool DeleteChildRecord (CObBaseRecord* ) { return (false); }

	/* Create a new subrecord */
  CObSubrecord* AddNewSubrecord (const obrectype_t      Type); 
  CObSubrecord* AddNewSubrecord (const obsubrecheader_t Header); 
  CObSubrecord* CreateSubrecord (const obsubrecheader_t Header);
  CObSubrecord* CreateSubrecord (const obrectype_t      Type);

	/* Static methods to initialize/destroy temporary input/output buffers */
  static bool InitIOBuffers    (void);
  static void DestroyIOBuffers (void);

	/* Change one ID for another */
  virtual dword ChangeFormID   (const obformid_t NewID, const obformid_t OldID);
  virtual dword ChangeEditorID (const SSCHAR*   pNewID, const SSCHAR*   pOldID);

	/* Compares fields in two records */
  virtual int CompareFields (const obrecfieldid_t FieldID, CObRecord* pRecord);

	/* Count the uses of the given form */
  virtual dword CountUses (const obformid_t FormID);

	/* Copy an existing record content */
  bool Copy (CObRecord* pRecord);
  
	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObRecord; }

	/* Deletes all subrecords of the given type */
  int DeleteSubrecords (const obrectype_t Type);

	/* Export/import the record to other formats */
  bool ExportCsv    (obcsvinfo_t& CsvInfo);
  bool ImportCsvRow (obcsvinfo_t& CsvInfo, CCsvRow& Row);

	/* Find information in the record */
  virtual bool Find     (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL);
  virtual bool FindText (dword& FindCount, obfinddata_t& FindData, CObCallback* pCallback = NULL);

	/* Find a subrecord */
  CObSubrecord* FindSubrecord      (const obrectype_t Type);
  CObSubrecord* FindFirstSubrecord (const obrectype_t Type, int& Position) { Position = -1; return FindNextSubrecord(Type, Position); }
  CObSubrecord* FindNextSubrecord  (const obrectype_t Type, int& Position);

	/* Find a record based on its formID */
  CObBaseRecord* FindFormID (const obformid_t FormID) { return (m_Header.FormID == FormID ? this : NULL); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormids (CObFormidFixupArray& FixupArray);
  
	/* Get a string representation of a record field */
  bool GetField (CSString& Buffer, const obrecfieldid_t FieldID);

  	/* Computes the size in bytes needed to output all sub-records */
  dword GetSubrecordSize (void);

	/* Access subrecords */
  CObSubrecord* GetSubrecord     (CObSubrecord* pSubrecord, const int Offset, const obrectype_t Type);
  CObSubrecord* GetSubrecord     (const dword Index) { return (m_Subrecords.GetAt(Index)); }
  dword         GetNumSubrecords (void) { return (m_Subrecords.GetSize()); }

	/* Get record members */
  obformid_t        GetFormID     (void) const { return (m_Header.FormID); }
  const obrectype_t GetRecordType (void) const { return (m_Header.RecordType); }
  dword	            GetFlags      (void) const { return (m_Header.Flags1); }
  bool              IsRecord      (void) const { return (true); }
  long		    GetUserData   (void) const { return (m_UserData); }
  obrecheader_t&    GetHeader     (void)       { return (m_Header); }

	/* Get record flags */
  bool IsCompressed		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_COMPRESSED); }
  bool IsDeleted		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_DELETED); }
  bool IsQuestItem		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_QUESTITEM); }
  bool IsDangerous		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_DANGEROUS); }
  bool IsMaster			(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_MASTER); }
  bool IsCastShadows		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_CASTSHADOWS); }
  bool IsIgnored		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_IGNORED); }
  bool IsInitiallyDisabled	(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_INITDISABLED); }
  bool IsVisibleDistant		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_VISIBLEDISTANT); }
  bool IsCantWait		(void) const { return CheckFlagBits(m_Header.Flags1, OB_RECFLAG_CANTWAIT); }

	/* Check the record against a form type (script function parameter) */
  virtual bool IsFormType      (const int Type);
  virtual bool IsInventoryItem (void) { return ObIsInventoryRecord(GetRecordType()); }
  virtual bool IsObject        (void) { return ObIsObjectRecord(GetRecordType()); }

  	/* Initialize the record with the given header */
  void Initialize (const obbaseheader_t Header) { m_Header = Header; }
  void Initialize (const obrectype_t    Type)   { m_Header.RecordType = Type; m_Header.Size = 0; m_Header.FormID = 0; }

	/* Initialize a new record */
  virtual void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Attempt to read the record data from a file */
  virtual bool ReadData (CObFile& File);

	/* Set record flags */
  void SetCompressed		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_COMPRESSED,		Flag); }
  void SetDeleted		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_DELETED,		Flag); }
  void SetQuestItem		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_QUESTITEM,		Flag); }
  void SetDangerous		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_DANGEROUS,		Flag); }
  void SetMaster		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_MASTER,		Flag); }
  void SetIgnored		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_IGNORED,		Flag); }
  void SetCastShadows		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_CASTSHADOWS,	Flag); }
  void SetInitiallyDisabled	(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_INITDISABLED,	Flag); }
  void SetVisibleDistant	(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_VISIBLEDISTANT,	Flag); }
  void SetCantWait		(const bool       Flag)  { FlipFlagBits(m_Header.Flags1, OB_RECFLAG_CANTWAIT,	Flag); }
  void SetFormID		(const obformid_t Value) { m_Header.FormID = Value; }
  void SetUserData		(const long       Value) { m_UserData      = Value; }

  	/* Set a  record field from a string value */
  bool SetField (const obrecfieldid_t FieldID, const SSCHAR* pString);
  
	/* Output the record to a file */
  bool Write (CObFile& File);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldFormID)
  DECLARE_OBFIELD(FieldName)
  DECLARE_OBFIELD(FieldRecordFlags)
  DECLARE_OBFIELD(FieldUserData)
  DECLARE_OBFIELD(FieldQuestItem)
  DECLARE_OBFIELD(FieldIgnored)
  DECLARE_OBFIELD(FieldDangerous)
  DECLARE_OBFIELD(FieldDeleted)

};
/*===========================================================================
 *		End of Class CObBaseRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin More Type Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Find a */
  const obrecfield_t* FindObFieldEntry (const obrecfieldmap_t* pFieldMap, const obrecfieldid_t FieldID);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRecord.H
 *=========================================================================*/
