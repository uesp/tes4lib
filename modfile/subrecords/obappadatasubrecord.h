/*===========================================================================
 *
 * File:	Obappadatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBAPPADATASUBRECORD_H
#define __OBAPPADATASUBRECORD_H


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

	/* Standard APPA-DATA subrecord size in bytes */
  #define OB_APPADATA_SUBRECORD_SIZE	13

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* APPA DATA structure */
  struct obappadata_t {
	byte	Type;
	dword	Value;
	float	Weight;
	float	Quality;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObAppaDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObAppaDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObAppaDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obappadata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_APPADATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_APPADATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAppaDataSubrecord() { }
  //virtual ~CObAppaDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObAppaDataSubrecord* pSubrecord1 = ObCastClassNull(CObAppaDataSubrecord, pSubrecord);
	m_RecordSize = OB_APPADATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetAppaData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObAppaDataSubrecord); }

	/* Get class members */
  obappadata_t& GetAppaData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float         GetQuality   (void) { return (m_Data.Quality); }
  float         GetWeight    (void) { return (m_Data.Weight); }
  dword         GetValue     (void) { return (m_Data.Value); }
  byte          GetType      (void) { return (m_Data.Type); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_APPADATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue   (const dword Value)   { m_Data.Value   = Value; }
  void SetType    (const byte  Value)   { m_Data.Type    = Value; }
  void SetWeight  (const float Value)   { m_Data.Weight  = Value; }
  void SetQuality (const float Value)   { m_Data.Quality = Value; }

 };
/*===========================================================================
 *		End of Class CObAppaDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obappadatasubrecord.H
 *=========================================================================*/
