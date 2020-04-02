/*===========================================================================
 *
 * File:	ObRdgsSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObRdgsSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBRDGSSUBRECORD_H
#define __OBRDGSSUBRECORD_H


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
  
  struct obrdgsdata_t {
	obformid_t FormID;
	dword	   Unknown;
   };

#pragma pack(pop)

  typedef TObArray<obrdgsdata_t> CObRdgsArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRdgsSubrecord Definition
 *
 *=========================================================================*/
class CObRdgsSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObRdgsSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRdgsArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRdgsSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObRdgsSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obrdgsdata_t* GetRdgsData   (const dword Index) { return (m_Values.IsValidIndex(Index) ? &m_Values[Index] : NULL); }
  virtual byte*	GetData       (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(obrdgsdata_t)); }
  CObRdgsArray& GetRdgsArray  (void) { return (m_Values); }

  	/* Set class methods */
  void SetValue (const dword Index, const obrdgsdata_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObRdgsSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRdwtSubrecord.H
 *=========================================================================*/