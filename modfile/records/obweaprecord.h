/*===========================================================================
 *
 * File:	Obweaprecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWeapRecord class for weapon records.
 *
 *=========================================================================*/
#ifndef __OBWEAPRECORD_H
#define __OBWEAPRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem2record.h"
  #include "../subrecords/obweapdatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObWeapRecord Definition
 *
 * Holds weapon data.
 *
 *=========================================================================*/
class CObWeapRecord : public CObItem2Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObWeapRecord, CObItem2Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObWeapDataSubrecord*	m_pWeaponData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObWeapRecord();
  //virtual ~CObWeapRecord() { Destroy(); }
  virtual void Destroy (void);

    	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObWeapRecord; }

	/* Get class members */
  obweapdata_t* GetWeaponData (void) { return (m_pWeaponData ? &m_pWeaponData->GetWeaponData() : NULL); }
  float         GetWeight     (void) { return (m_pWeaponData ?  m_pWeaponData->GetWeight()     : 0.0f); }
  float         GetSpeed      (void) { return (m_pWeaponData ?  m_pWeaponData->GetSpeed()      : 0.0f); }
  float         GetReach      (void) { return (m_pWeaponData ?  m_pWeaponData->GetReach()      : 0.0f); }
  dword         GetValue      (void) { return (m_pWeaponData ?  m_pWeaponData->GetValue()      : 0); }
  dword         GetHealth     (void) { return (m_pWeaponData ?  m_pWeaponData->GetHealth()     : 0); }
  dword         GetType       (void) { return (m_pWeaponData ?  m_pWeaponData->GetType()       : 0); }
  word          GetDamage     (void) { return (m_pWeaponData ?  m_pWeaponData->GetDamage()     : 0); }

  bool IsIgnoreResist (void) { return (m_pWeaponData ?  m_pWeaponData->IsIgnoreResist() : false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight (const float Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetWeight(Value); }
  void SetSpeed  (const float Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetSpeed(Value); }
  void SetReach  (const float Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetReach(Value); }
  void SetValue  (const dword Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetValue(Value); }
  void SetHealth (const dword Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetHealth(Value); }
  void SetType   (const dword Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetType(Value); }
  void SetDamage (const word  Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetDamage(Value); }

  void SetIgnoreResist (const bool Value) { if (m_pWeaponData != NULL) m_pWeaponData->SetIgnoreResist(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldSpeed)
  DECLARE_OBFIELD(FieldReach)
  DECLARE_OBFIELD(FieldType)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldHealth)
  DECLARE_OBFIELD(FieldDamage)
  DECLARE_OBFIELD(FieldIgnoreResist)
 };
/*===========================================================================
 *		End of Class CObWeapRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  const SSCHAR* GetObWeaponTypeString (const int Value);
  bool GetObWeaponTypeValue (int& Value, const SSCHAR* pString);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obweaprecord.H
 *=========================================================================*/
