/*===========================================================================
 *
 * File:	ObRdwtSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObRdwtSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBRDWTSUBRECORD_H
#define __OBRDWTSUBRECORD_H


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
  
  struct obrdwtdata_t {
	obformid_t FormID;
	dword	   Unknown;
   };

#pragma pack(pop)

  typedef TObArray<obrdwtdata_t> CObRdwtArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRdwtSubrecord Definition
 *
 *=========================================================================*/
class CObRdwtSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObRdwtSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRdwtArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRdwtSubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObRdwtSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obrdwtdata_t* GetRdwtData   (const dword Index) { return (m_Values.IsValidIndex(Index) ? &m_Values[Index] : NULL); }
  virtual byte*	GetData       (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	GetRecordSize (void) const { return (m_Values.GetSize() * sizeof(obrdwtdata_t)); }
  CObRdwtArray& GetRdwtArray  (void) { return (m_Values); }

  	/* Set class methods */
  void SetValue (const dword Index, const obrdwtdata_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObRdwtSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRdwtSubrecord.H
 *=========================================================================*/