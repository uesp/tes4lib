/*===========================================================================
 *
 * File:	ObRdotSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObRdotSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBRDOTSUBRECORD_H
#define __OBRDOTSUBRECORD_H


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
  
  struct obrdotdata_t {
	obformid_t FormID;
	dword	   Unknown1;
	dword	   Unknown2;
	dword	   Unknown3;
	dword	   Unknown4;
	dword	   Unknown5;
	dword	   Unknown6;
	dword	   Unknown7;
	dword	   Unknown8;
	dword	   Unknown9;
	dword	   Unknown10;
	dword	   Unknown11;
	dword	   Unknown12;
   };

#pragma pack(pop)

  typedef TObArray<obrdotdata_t> CObRdotArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRdotSubrecord Definition
 *
 *=========================================================================*/
class CObRdotSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObRdotSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRdotArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRdotSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObRdotSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obrdotdata_t* GetRdotData   (const dword Index) { return (m_Values.IsValidIndex(Index) ? &m_Values[Index] : NULL); }
  virtual byte*	GetData       (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(obrdotdata_t)); }
  CObRdotArray& GetRdotArray  (void) { return (m_Values); }

  	/* Set class methods */
  void SetValue (const dword Index, const obrdotdata_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObRdotSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRdotSubrecord.H
 *=========================================================================*/