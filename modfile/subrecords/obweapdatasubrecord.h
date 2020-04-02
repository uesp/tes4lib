/*===========================================================================
 *
 * File:	Obweapdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBWEAPDATASUBRECORD_H
#define __OBWEAPDATASUBRECORD_H


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

	/* Standard WEAP-DATA subrecord size in bytes */
  #define OB_WEAPDATA_SUBRECORD_SIZE	30
  
	/* Weapon data flags */
  #define OB_WEAPFLAG_IGNORERESIST	0x00000001

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Weapon DATA structure */
  struct obweapdata_t {
	dword   Type;
	float	Speed;
	float	Reach;
	dword	Flags;
	dword	Value;
	dword   Health;
	float	Weight;
	word    Damage;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObWeapDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObWeapDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObWeapDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obweapdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_WEAPDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_WEAPDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObWeapDataSubrecord() { }
  //virtual ~CObWeapDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObWeapDataSubrecord* pSubrecord1 = ObCastClassNull(CObWeapDataSubrecord, pSubrecord);
	m_RecordSize = OB_WEAPDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetWeaponData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObWeapDataSubrecord); }

	/* Get class members */
  obweapdata_t& GetWeaponData (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  float         GetWeight     (void) { return (m_Data.Weight); }
  float         GetReach      (void) { return (m_Data.Reach); }
  float         GetSpeed      (void) { return (m_Data.Speed); }
  dword         GetValue      (void) { return (m_Data.Value); }
  dword         GetHealth     (void) { return (m_Data.Health); }
  dword         GetType       (void) { return (m_Data.Type); }
  word          GetDamage     (void) { return (m_Data.Damage); }

  bool IsIgnoreResist (void) { return CheckFlagBits(m_Data.Flags, OB_WEAPFLAG_IGNORERESIST); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_WEAPDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue  (const dword Value)   { m_Data.Value  = Value; }
  void SetWeight (const float Value)   { m_Data.Weight = Value; }
  void SetSpeed  (const float Value)   { m_Data.Speed  = Value; }
  void SetReach  (const float Value)   { m_Data.Reach  = Value; }
  void SetDamage (const word  Value)   { m_Data.Damage = Value; }
  void SetHealth (const dword Value)   { m_Data.Health = Value; }
  void SetType   (const dword Value)   { m_Data.Type   = Value; }

  void SetIgnoreResist (const bool Value) { FlipFlagBits(m_Data.Flags, OB_WEAPFLAG_IGNORERESIST, Value); }
  
 };
/*===========================================================================
 *		End of Class CObWeapDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obweapdatasubrecord.H
 *=========================================================================*/
