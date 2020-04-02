/*===========================================================================
 *
 * File:	ObFormidArraysubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObFormidArraySubrecord used for storing an array of formids.
 *
 *=========================================================================*/
#ifndef __OBFORMIDARRAYSUBRECORD_H
#define __OBFORMIDARRAYSUBRECORD_H


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
 * Begin Class CObFormidArraySubrecord Definition
 *
 *=========================================================================*/
class CObFormidArraySubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObFormidArraySubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFormidArray m_Values;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFormidArraySubrecord();
  virtual void Destroy (void);

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

    	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObFormidArraySubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = 0; 
  }

	/* Get class members */
  obformid_t      GetFormID      (const dword Index) { return (m_Values.IsValidIndex(Index) ? m_Values[Index] : OB_FORMID_NULL); }
  virtual byte*	  GetData        (void) { return (byte *)(m_Values.GetRecords()); }
  virtual dword	  GetRecordSize  (void) const { return (m_Values.GetSize() * sizeof(obformid_t)); }
  CObFormidArray& GetFormIDArray (void) { return m_Values; }

  	/* Set class methods */
  void SetValue (const dword Index, const obformid_t Value) { m_Values[Index] = Value; }
  void SetSize  (const dword Size) { m_Values.SetSize(Size); }
 
};
/*===========================================================================
 *		End of Class CObFormidArraySubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFormidArraySubrecord.H
 *=========================================================================*/