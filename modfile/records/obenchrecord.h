/*===========================================================================
 *
 * File:	Obenchrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObEnchRecord class for enchantment records.
 *
 *=========================================================================*/
#ifndef __OBENCHRECORD_H
#define __OBENCHRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obeffitemrecord.h"
  #include "../subrecords/obenitsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEnchRecord Definition
 *
 * Holds enchantment data.
 *
 *=========================================================================*/
class CObEnchRecord : public CObEffectItemRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObEnchRecord, CObEffectItemRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObEnitSubrecord*	m_pEnchantData;
  dword			m_EffectCount;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEnchRecord();
  //virtual ~CObEnchRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObEnchRecord; }

	/* Get class members */
  obenitdata_t* GetEnchantData  (void) { return (m_pEnchantData ? &m_pEnchantData->GetEnchantData()  : NULL); }
  dword		GetType    (void) { return (m_pEnchantData ?  m_pEnchantData->GetType()    : 0); }
  dword		GetCharge  (void) { return (m_pEnchantData ?  m_pEnchantData->GetCharge()  : 0); }
  dword		GetCost    (void) { return (m_pEnchantData ?  m_pEnchantData->GetCost()    : 0); }
  bool          IsAutoCalc (void) { return (m_pEnchantData ?  m_pEnchantData->IsAutoCalc() : false); }

  	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetType     (const dword Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetType(Value); }
  void SetCharge   (const dword Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetCharge(Value); }
  void SetCost     (const dword Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetCost(Value); }
  void SetAutoCalc (const bool  Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetAutoCalc(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldType)
  DECLARE_OBFIELD(FieldCharge)
  DECLARE_OBFIELD(FieldCost)
  DECLARE_OBFIELD(FieldAutoCalc)

 };
/*===========================================================================
 *		End of Class CObEnchRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obenchrecord.H
 *=========================================================================*/
