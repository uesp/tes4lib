/*===========================================================================
 *
 * File:	Obslgmdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSLGMDATASUBRECORD_H
#define __OBSLGMDATASUBRECORD_H


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
  #define OB_SLGMDATA_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obslgmdata_t {
	dword	Value;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSlgmDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSlgmDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSlgmDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obslgmdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_SLGMDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_SLGMDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSlgmDataSubrecord() { }
  //virtual ~CObSlgmDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSlgmDataSubrecord* pSubrecord1 = ObCastClassNull(CObSlgmDataSubrecord, pSubrecord);
	m_RecordSize = OB_SLGMDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSoulGemData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSlgmDataSubrecord); }

	/* Get class members */
  obslgmdata_t& GetSoulGemData (void) { return (m_Data); }
  virtual byte*	GetData        (void) { return (byte *)(&m_Data); }
  float         GetWeight      (void) { return (m_Data.Weight); }
  dword         GetValue       (void) { return (m_Data.Value); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_SLGMDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue  (const dword Value)   { m_Data.Value  = Value; }
  void SetWeight (const float Value)   { m_Data.Weight = Value; }

 };
/*===========================================================================
 *		End of Class CObSlgmDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obslgmdatasubrecord.H
 *=========================================================================*/
