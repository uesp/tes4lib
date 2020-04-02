/*===========================================================================
 *
 * File:	Obammorecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObAmmoRecord class for ammunition records.
 *
 *=========================================================================*/
#ifndef __OBAMMORECORD_H
#define __OBAMMORECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem2record.h"
  #include "../subrecords/obammodatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObAmmoRecord Definition
 *
 * Holds ammo data.
 *
 *=========================================================================*/
class CObAmmoRecord : public CObItem2Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObAmmoRecord, CObItem2Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObAmmoDataSubrecord*	m_pAmmoData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAmmoRecord();
  //virtual ~CObAmmoRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObAmmoRecord; }

	/* Get class members */
  obammodata_t* GetAmmoData (void) { return (m_pAmmoData ? &m_pAmmoData->GetAmmoData() : NULL); }
  float         GetSpeed    (void) { return (m_pAmmoData ?  m_pAmmoData->GetSpeed()    : 0.0f); }
  float         GetWeight   (void) { return (m_pAmmoData ?  m_pAmmoData->GetWeight()   : 0.0f); }
  dword         GetValue    (void) { return (m_pAmmoData ?  m_pAmmoData->GetValue()    : 0); }
  word          GetDamage   (void) { return (m_pAmmoData ?  m_pAmmoData->GetDamage()   : 0); }

  bool IsIgnoreResist (void) {return (m_pAmmoData ? m_pAmmoData->IsIgnoreResist() : false); }
 

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetSpeed  (const float Value) { if (m_pAmmoData != NULL) m_pAmmoData->SetSpeed(Value); }
  void SetWeight (const float Value) { if (m_pAmmoData != NULL) m_pAmmoData->SetWeight(Value); }
  void SetValue  (const dword Value) { if (m_pAmmoData != NULL) m_pAmmoData->SetValue(Value); }
  void SetDamage (const word  Value) { if (m_pAmmoData != NULL) m_pAmmoData->SetDamage(Value); }

  void SetIgnoreResist (const bool Value) { if (m_pAmmoData != NULL) m_pAmmoData->SetIgnoreResist(Value); }

  	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldSpeed)
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldDamage)
  DECLARE_OBFIELD(FieldIgnoreResist)
 };
/*===========================================================================
 *		End of Class CObAmmoRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obammorecord.H
 *=========================================================================*/
