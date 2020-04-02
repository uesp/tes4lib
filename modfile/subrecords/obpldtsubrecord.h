/*===========================================================================
 *
 * File:	ObPldtsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 16, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPLDTSUBRECORD_H
#define __OBPLDTSUBRECORD_H


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

  #define OBPLDT_SUBRECORD_SIZE	12

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obpldtdata_t {
	dword	Type;
	long	Parameter1;
	long	Parameter2;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPldtSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObPldtSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObPldtSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obpldtdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data, OBPLDT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBPLDT_SUBRECORD_SIZE);  }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPldtSubrecord() { }
  //virtual ~CObPldtSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.Type <= 4 && (obformid_t)m_Data.Parameter1 == OldID) {
	  m_Data.Parameter1 = (long) NewID;
	  return (1);
	}
	return (0); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObPldtSubrecord* pSubrecord1 = ObCastClassNull(CObPldtSubrecord, pSubrecord);
	m_RecordSize = OBPLDT_SUBRECORD_SIZE;
	
	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetPldtData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObPldtSubrecord); }

    	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
        if (m_Data.Type <= 4) {
	  return ObFixupFormid(*(obformid_t *)&m_Data.Parameter1, *(obformid_t *)&m_Data.Parameter1, FixupArray);
	}
	return (true);
  }

	/* Get class members */
  obpldtdata_t& GetPldtData (void) { return (m_Data); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Data); }
   
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBPLDT_SUBRECORD_SIZE; }

	/* Set class members */

};
/*===========================================================================
 *		End of Class CObPldtSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCtdasubrecord.H
 *=========================================================================*/
