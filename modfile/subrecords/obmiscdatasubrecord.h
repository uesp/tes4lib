/*===========================================================================
 *
 * File:	Obmiscdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBMISCDATASUBRECORD_H
#define __OBMISCDATASUBRECORD_H


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

	/* Standard AMMO-DATA subrecord size in bytes */
  #define OB_MISCDATA_SUBRECORD_SIZE	8

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Misc DATA structure */
  struct obmiscdata_t {
	dword	Value;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObMiscDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObMiscDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObMiscDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obmiscdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_MISCDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_MISCDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObMiscDataSubrecord() { }
  //virtual ~CObMiscDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObMiscDataSubrecord* pSubrecord1 = ObCastClassNull(CObMiscDataSubrecord, pSubrecord);
	m_RecordSize = OB_MISCDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetMiscData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObMiscDataSubrecord); }

	/* Get class members */
  obmiscdata_t& GetMiscData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float         GetWeight    (void) { return (m_Data.Weight); }
  dword         GetValue     (void) { return (m_Data.Value); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_MISCDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue  (const dword Value)   { m_Data.Value  = Value; }
  void SetWeight (const float Value)   { m_Data.Weight = Value; }

 };
/*===========================================================================
 *		End of Class CObMiscDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obmiscdatasubrecord.H
 *=========================================================================*/
