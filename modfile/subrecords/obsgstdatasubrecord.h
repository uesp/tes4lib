/*===========================================================================
 *
 * File:	Obsgstdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSGSTDATASUBRECORD_H
#define __OBSGSTDATASUBRECORD_H


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
  #define OB_SGSTDATA_SUBRECORD_SIZE	9

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* SGST DATA structure */
  struct obsgstdata_t {
	byte	Uses;
	dword	Value;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSgstDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSgstDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSgstDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obsgstdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_SGSTDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_SGSTDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSgstDataSubrecord() { }
  //virtual ~CObSgstDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSgstDataSubrecord* pSubrecord1 = ObCastClassNull(CObSgstDataSubrecord, pSubrecord);
	m_RecordSize = OB_SGSTDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSigilData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSgstDataSubrecord); }

	/* Get class members */
  obsgstdata_t& GetSigilData (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float         GetWeight    (void) { return (m_Data.Weight); }
  dword         GetValue     (void) { return (m_Data.Value); }
  byte          GetUses      (void) { return (m_Data.Uses); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_SGSTDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue   (const dword Value)   { m_Data.Value   = Value; }
  void SetUses    (const byte  Value)   { m_Data.Uses    = Value; }
  void SetWeight  (const float Value)   { m_Data.Weight  = Value; }

 };
/*===========================================================================
 *		End of Class CObSgstDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obsgstdatasubrecord.H
 *=========================================================================*/
