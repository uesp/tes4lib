/*===========================================================================
 *
 * File:	ObAlchRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObAlchRecord class for enchantment records.
 *
 *=========================================================================*/
#ifndef __OBALCHRECORD_H
#define __OBALCHRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obeffitemrecord.h"
  #include "../subrecords/obenit8subrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObAlchRecord Definition
 *
 * Holds alchemy (potion) data.
 *
 *=========================================================================*/
class CObAlchRecord : public CObEffectItemRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObAlchRecord, CObEffectItemRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObEnit8Subrecord*	m_pData;
  CObFloatSubrecord*	m_pWeightData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAlchRecord();
  //virtual ~CObAlchRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObAlchRecord; }

	/* Get class members */
  obenit8data_t*    GetAlchData    (void) { return (m_pData ? &m_pData->GetEnitData()  : NULL); }
  float		    GetWeight      (void) { return (m_pWeightData ?  m_pWeightData->GetValue()           : 0); }
  dword		    GetValue       (void) { return (m_pData ?  m_pData->GetValue()        : 0); }
  bool              IsAutoCalc     (void) { return (m_pData ?  m_pData->IsAutoCalc()      : false); }
  bool              IsFoodItem     (void) { return (m_pData ?  m_pData->IsFoodItem()      : false); }

  	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (true); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetWeight   (const float Value) { if (m_pWeightData != NULL) m_pWeightData->SetValue(Value); }
  void SetValue    (const dword Value) { if (m_pData != NULL) m_pData->SetValue(Value); }
  void SetAutoCalc (const bool  Value) { if (m_pData != NULL) m_pData->SetAutoCalc(Value); }
  void SetFoodItem (const bool  Value) { if (m_pData != NULL) m_pData->SetFoodItem(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldAutoCalc)
  DECLARE_OBFIELD(FieldFoodItem)

};
/*===========================================================================
 *		End of Class CObAlchRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAkchRecord.H
 *=========================================================================*/
