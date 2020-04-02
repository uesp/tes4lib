/*===========================================================================
 *
 * File:	ObSubrecord.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSUBRECORD_H
#define __OBSUBRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/obfile.h"
  #include "../../common/oblogfile.h"
  #include "../obmoddefs.h"
  #include "../obfields.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Subrecord header size in bytes */
  #define OB_SUBRECORD_HEADERSIZE 6

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Subrecord header type */
  struct obsubrecheader_t {
	obrectype_t	Type;
	word		Size;
   };

#pragma pack(pop)

	/* Pointer to a class method to create a sub-record object */
  class CObSubrecord;
  typedef CObSubrecord* (*OBSUBREC_CREATEFUNC) (void);

	/* Structure to hold information on subrecord creation */
  struct obsubrecentries_t {
	const obrectype_t*	pName;
	OBSUBREC_CREATEFUNC	CreateMethod;
   };

  struct obsubreccreate_t {
	const obsubreccreate_t*  pBaseCreate;
	const obsubrecentries_t* pEntries;
   };

	/* Shortcut comparison operators */
  inline bool operator== (const obsubrecentries_t& Rec, const obrectype_t& Type) { return (Rec.pName != NULL && *Rec.pName == Type); }
   
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSubrecord {
  DECLARE_OBBASE(CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obrectype_t	m_RecordType;			/* Subrecord header data */
  dword		m_RecordSize;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Output the raw subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSubrecord();
  virtual ~CObSubrecord();
  virtual void Destroy (void);

	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { return (0); }

	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Count uses of the given form */
  virtual dword CountUses (const obformid_t FormID) { return (0); }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSubrecord); }

	/* Find data in the subrecord */
  virtual dword Find     (obfinddata_t& FindData);
  virtual dword FindText (obfinddata_t& FindData);

	/* Fix any form id in the subrecord */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) { return (true); }

  	/* Used when reading records */
  void Initialize (const obsubrecheader_t Header) { m_RecordType = Header.Type; m_RecordSize = Header.Size; }
  void Initialize (const obrectype_t Type, const dword Size) { m_RecordType = Type; m_RecordSize = Size; }

  	/* Get a string representation of a subrecord field */
  virtual bool GetField (CSString& Buffer, const int FieldID);

	/* Get size when output to file */
  virtual dword GetOutputSize (void) { return (GetRecordSize() + OB_SUBRECORD_HEADERSIZE); }

	/* Get class members */
  obrectype_t	GetRecordType (void)       { return (m_RecordType); }
  virtual dword	GetRecordSize (void) const { return (m_RecordSize); }
  virtual byte*	GetData       (void)       { return (NULL); }

	/* Initialize a new record */
  virtual void InitializeNew (void) { }
 
	/* Input/Output the subrecord to a file */
  virtual bool Read  (CObFile& File);
  virtual bool Write (CObFile& File);
  
	/* Set class members */
  void SetSpecialSize (const dword Size = 0) { m_RecordSize = Size; }

};

  typedef CObPtrArray<CObSubrecord>    CObSubrecordArray;
  typedef CObRefPtrArray<CObSubrecord> CObRefSubrecordArray;

/*===========================================================================
 *		End of Class CObSubrecord Definition
 *=========================================================================*/
 

/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

  bool ReadObSubRecordHeader (CObFile& File, obsubrecheader_t& Header);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obbasesubrec.H
 *=========================================================================*/
