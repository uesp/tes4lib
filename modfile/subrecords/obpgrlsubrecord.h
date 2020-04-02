/*===========================================================================
 *
 * File:	ObPgrlSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObPgrlSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBPGRLSUBRECORD_H
#define __OBPGRLSUBRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)
  

#pragma pack(pop)

  typedef TObArray<long> CObPgrlArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPgrlSubrecord Definition
 *
 *=========================================================================*/
class CObPgrlSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObPgrlSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obformid_t   m_FormID;
  CObPgrlArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPgrlSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObPgrlSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_Values.Destroy();
	m_RecordSize = 4; 
  }

	/* Get class members */
  virtual byte*	GetData       (void) { return (byte *)(&m_FormID); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(long) + 4); }
  obformid_t    GetFormID     (void) { return (m_FormID); }
  CObPgrlArray& GetPgrlArray  (void) { return (m_Values); }

  	/* Set class methods */
 
};
/*===========================================================================
 *		End of Class CObPgrlSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFormidArraySubrecord.H
 *=========================================================================*/