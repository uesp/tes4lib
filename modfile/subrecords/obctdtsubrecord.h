/*===========================================================================
 *
 * File:	ObCtdtsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCTDTSUBRECORD_H
#define __OBCTDTSUBRECORD_H


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

  #define OB_CTDT_SUBRECORD_SIZE	20

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obctdtdata_t {
	byte	CompareType;
	byte	Unknown[3];
	float	Value;
	dword	Function;
	long	Parameter1;
	long	Parameter2;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObCtdtSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObCtdtSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObCtdtSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obctdtdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

  bool IsRefParam1 (const int FunctionCode);
  bool IsRefParam2 (const int FunctionCode);

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_CTDT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_CTDT_SUBRECORD_SIZE); }

  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObCtdtSubrecord() { }
  //virtual ~CObCtdtSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);
  
	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObCtdtSubrecord* pSubrecord1 = ObCastClassNull(CObCtdtSubrecord, pSubrecord);
	m_RecordSize = OB_CTDT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetCtdtData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObCtdtSubrecord); }

    	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Get class members */
  obctdtdata_t& GetCtdtData (void) { return (m_Data); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Data); }
   
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_CTDT_SUBRECORD_SIZE; }

	/* Set class members */

};
/*===========================================================================
 *		End of Class CObCtdtSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCtdasubrecord.H
 *=========================================================================*/
