/*===========================================================================
 *
 * File:	ObSnamsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 16, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSNAMSUBRECORD_H
#define __OBSNAMSUBRECORD_H


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
  #define OBSNAM_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obsnamdata_t {
	obformid_t  FormID;
	dword	    Unknown;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSnamSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSnamSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSnamSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obsnamdata_t	m_Data;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data, m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSnamSubrecord() { }
  //virtual ~CObSnamSubrecord() { Destroy(); }
  //virtual void Destroy (void);
  
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
	CObSnamSubrecord* pSubrecord1 = ObCastClassNull(CObSnamSubrecord, pSubrecord);
	m_RecordSize = OBSNAM_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSnamData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }
  	
  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSnamSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_Data.FormID, FixupArray);
  }

	/* Get class members */
  obsnamdata_t&     GetSnamData  (void) { return (m_Data); }
  virtual byte*	    GetData      (void) { return (byte *)(&m_Data); }
  obformid_t        GetFormID    (void) { return (m_Data.FormID); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBSNAM_SUBRECORD_SIZE; }

	/* Set class members */
  void SetFormID  (const obformid_t Value) { m_Data.FormID = Value; }
  
 };
/*===========================================================================
 *		End of Class CObSnamSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObSnamSubrecord.H
 *=========================================================================*/
