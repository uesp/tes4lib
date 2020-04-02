/*===========================================================================
 *
 * File:	ObCtdasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCTDASUBRECORD_H
#define __OBCTDASUBRECORD_H


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

  #define OB_CTDA_SUBRECORD_SIZE	24

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obctdadata_t {
	byte	CompareType;
	byte	Unknown[3];
	float	Value;
	dword	Function;
	long	Parameter1;
	long	Parameter2;
	long	Unknown3;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObCtdaSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObCtdaSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObCtdaSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obctdadata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
		/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data, OB_CTDA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_CTDA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObCtdaSubrecord() { }
  //virtual ~CObCtdaSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID);

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObCtdaSubrecord* pSubrecord1 = ObCastClassNull(CObCtdaSubrecord, pSubrecord);
	m_RecordSize = OB_CTDA_SUBRECORD_SIZE;
	
	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetCtdaData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObCtdaSubrecord); }

    	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray);

	/* Get class members */
  obctdadata_t& GetCtdaData (void) { return (m_Data); }
  virtual byte*	GetData     (void) { return (byte *)(&m_Data); }
   
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_CTDA_SUBRECORD_SIZE; }

  static bool IsRefParam1 (const int FunctionCode);
  static bool IsRefParam2 (const int FunctionCode);


	/* Set class members */

};
/*===========================================================================
 *		End of Class CObCtdaSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCtdasubrecord.H
 *=========================================================================*/
