/*===========================================================================
 *
 * File:	ObXlocsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBXLOCSUBRECORD_H
#define __OBXLOCSUBRECORD_H


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

	/* Standard CNTO subrecord size in bytes */
  #define OB_XLOC_SUBRECORD_SIZE 16

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obxlocdata_t {
	dword		U1;
	obformid_t	FormID;
	dword		U2;
	dword		U3;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObXlocSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObXlocSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObXlocSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obxlocdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { memset(&m_Data, 0, sizeof(m_Data)); return File.Read(&m_Data, m_RecordSize);  }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObXlocSubrecord() { }
  //virtual ~CObXlocSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.FormID == OldID) {
	  m_Data.FormID = NewID;
	  return (1);
	}
	return (0); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObXlocSubrecord* pSubrecord1 = ObCastClassNull(CObXlocSubrecord, pSubrecord);
	m_RecordSize = OB_XLOC_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetXlocData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObXlocSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_Data.FormID, FixupArray);
  }

	/* Get class members */
  obxlocdata_t& GetXlocData   (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  obformid_t    GetFormID     (void) { return (m_Data.FormID); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_XLOC_SUBRECORD_SIZE; }

	/* Set class members */
  void SetFormID     (const obformid_t Value) { m_Data.FormID = Value; }

 };
/*===========================================================================
 *		End of Class CObXlocSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObXespsubrecord.H
 *=========================================================================*/
