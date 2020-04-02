/*===========================================================================
 *
 * File:	ObVtexsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObVtexSubrecord class.
 *
 *=========================================================================*/
#ifndef __OBVTEXSUBRECORD_H
#define __OBVTEXSUBRECORD_H


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
 * Begin Definitions
 *
 *=========================================================================*/

	/* Standard subrecord size in bytes */
  #define OBVTEX_SUBRECORD_SIZE	256

  #define OBVTEX_SUBRECORD_ARRAYSIZE 64

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* ENIT data structure */
  struct obvtexdata_t {
	obformid_t Formids[OBVTEX_SUBRECORD_ARRAYSIZE];
  };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObVtexSubrecord Definition
 *
 *=========================================================================*/
class CObVtexSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObVtexSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obvtexdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBVTEX_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBVTEX_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObVtexSubrecord() { }
  //virtual void Destroy (void) { }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
	dword Count = 0;
        for (dword Index = 0; Index < OBVTEX_SUBRECORD_ARRAYSIZE; ++Index ) {
  		if (m_Data.Formids[Index] == OldID) {
			m_Data.Formids[Index] = NewID;
			++Count;
		}
	}
	return (Count); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObVtexSubrecord* pSubrecord1 = ObCastClassNull(CObVtexSubrecord, pSubrecord);
	m_RecordSize = OBVTEX_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetVtexData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObVtexSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	bool Result = true;
        for (dword Index = 0; Index < OBVTEX_SUBRECORD_ARRAYSIZE; ++Index ) {
  		Result &= ObFixupFormid(m_Data.Formids[Index], m_Data.Formids[Index], FixupArray);
	}
	return (Result);
  }

	/* Initialize a new record */
  virtual void InitializeNew (void) { 
	CObSubrecord::InitializeNew();
	m_RecordSize = OBVTEX_SUBRECORD_SIZE; 
	memset(&m_Data, 0, sizeof(m_Data));
  }

	/* Get class members */
  obvtexdata_t& GetVtexData   (void) { return (m_Data); }
  virtual byte* GetData       (void) { return (byte *)(&m_Data); }

  	/* Set class methods */

 
};
/*===========================================================================
 *		End of Class CObVtexSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFormidArraySubrecord.H
 *=========================================================================*/