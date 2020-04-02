/*===========================================================================
 *
 * File:	ObWlstSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWlstSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBWLSTSUBRECORD_H
#define __OBWLSTSUBRECORD_H


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
  
  struct obwlstdata_t {
	obformid_t FormID;
	dword	   Unknown;
   };

#pragma pack(pop)

  typedef TObArray<obwlstdata_t> CObWlstArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObWlstSubrecord Definition
 *
 *=========================================================================*/
class CObWlstSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObWlstSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObWlstArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObWlstSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

   	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObWlstSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obwlstdata_t* GetWlstData   (const dword Index) { return (m_Values.IsValidIndex(Index) ? &m_Values[Index] : NULL); }
  virtual byte*	GetData       (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(obwlstdata_t)); }
  CObWlstArray& GetWlstArray  (void) { return (m_Values); }

  	/* Set class methods */
  void SetValue (const dword Index, const obwlstdata_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObWlstSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFormidArraySubrecord.H
 *=========================================================================*/