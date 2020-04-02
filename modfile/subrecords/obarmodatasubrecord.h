/*===========================================================================
 *
 * File:	Obarmodatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBARMODATASUBRECORD_H
#define __OBARMODATASUBRECORD_H


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

	/* Standard ARMO-DATA subrecord size in bytes */
  #define OB_ARMODATA_SUBRECORD_SIZE	14
   
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Armo DATA structure */
  struct obarmodata_t {
	word    Armor;
	dword	Value;
	dword   Health;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObArmoDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObArmoDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObArmoDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obarmodata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_ARMODATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_ARMODATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObArmoDataSubrecord() { }
  //virtual ~CObArmoDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObArmoDataSubrecord* pSubrecord1 = ObCastClassNull(CObArmoDataSubrecord, pSubrecord);
	m_RecordSize = OB_ARMODATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetArmorData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObArmoDataSubrecord); }

	/* Get class members */
  obarmodata_t& GetArmorData  (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  float         GetWeight     (void) { return (m_Data.Weight); }
  dword         GetValue      (void) { return (m_Data.Value); }
  word          GetArmor      (void) { return (m_Data.Armor); }
  dword         GetHealth     (void) { return (m_Data.Health); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_ARMODATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue  (const dword Value)   { m_Data.Value  = Value; }
  void SetWeight (const float Value)   { m_Data.Weight = Value; }
  void SetArmor  (const word  Value)   { m_Data.Armor  = Value; }
  void SetHealth (const dword Value)   { m_Data.Health = Value; }

 };
/*===========================================================================
 *		End of Class CObArmoDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obarmodatasubrecord.H
 *=========================================================================*/
