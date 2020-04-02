/*===========================================================================
 *
 * File:	Obammodatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBAMMODATASUBRECORD_H
#define __OBAMMODATASUBRECORD_H


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
  #define OB_AMMODATA_SUBRECORD_SIZE	0x12

	/* Ammo data flags */
  #define OB_AMMOFLAG_IGNORERESIST 0x01

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Ammo DATA structure */
  struct obammodata_t {
	float	Speed;
	dword	Flags;
	dword	Value;
	float	Weight;
	word	Damage;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObAmmoDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObAmmoDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObAmmoDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obammodata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_AMMODATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_AMMODATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAmmoDataSubrecord() { }
  //virtual ~CObAmmoDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObAmmoDataSubrecord* pSubrecord1 = ObCastClassNull(CObAmmoDataSubrecord, pSubrecord);
	m_RecordSize = OB_AMMODATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetAmmoData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObAmmoDataSubrecord); }

	/* Get class members */
  obammodata_t& GetAmmoData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float         GetSpeed     (void) { return (m_Data.Speed); }
  float         GetWeight    (void) { return (m_Data.Weight); }
  dword         GetValue     (void) { return (m_Data.Value); }
  dword         GetDamage    (void) { return (m_Data.Damage); }

  bool IsIgnoreResist (void) { return CheckFlagBits(m_Data.Flags, OB_AMMOFLAG_IGNORERESIST); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_AMMODATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue  (const dword Value)   { m_Data.Value  = Value; }
  void SetDamage (const word  Value)   { m_Data.Damage = Value; }
  void SetWeight (const float Value)   { m_Data.Weight = Value; }
  void SetSpeed  (const float Value)   { m_Data.Speed  = Value; }

  void SetIgnoreResist (const bool Value) { FlipFlagBits(m_Data.Flags, OB_AMMOFLAG_IGNORERESIST, Value); }

 };
/*===========================================================================
 *		End of Class CObAmmoDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obammodatasubrecord.H
 *=========================================================================*/
