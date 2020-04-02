/*===========================================================================
 *
 * File:	ObRdsdSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObRdsdSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBRDSDSUBRECORD_H
#define __OBRDSDSUBRECORD_H


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
  
  struct obrdsddata_t {
	obformid_t FormID;
	dword	   Unknown1;
	dword	   Unknown2;
   };

#pragma pack(pop)

  typedef TObArray<obrdsddata_t> CObRdsdArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRdsdSubrecord Definition
 *
 *=========================================================================*/
class CObRdsdSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObRdsdSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRdsdArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRdsdSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObRdsdSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obrdsddata_t* GetRdsdData   (const dword Index) { return (m_Values.IsValidIndex(Index) ? &m_Values[Index] : NULL); }
  virtual byte*	GetData       (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(obrdsddata_t)); }
  CObRdsdArray& GetRdsdArray  (void) { return (m_Values); }

  	/* Set class methods */
  void SetValue (const dword Index, const obrdsddata_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObRdsdSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRdsdSubrecord.H
 *=========================================================================*/