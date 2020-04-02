/*===========================================================================
 *
 * File:	ObIngrrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Defines the CObIngrRecord class for ingrediant records.
 *
 *=========================================================================*/
#ifndef __OBINGRRECORD_H
#define __OBINGRRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obeffitemrecord.h"
  #include "../subrecords/obingrenitsubrecord.h"
  #include "../subrecords/obfloatsubrecord.h"
  #include "../subrecords/obefitsubrecord.h"
  #include "../subrecords/obscitsubrecord.h"
  #include "../subrecords/obnamesubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObIngrRecord Definition
 *
 * Holds ingrediant data.
 *
 *=========================================================================*/
class CObIngrRecord : public CObEffectItemRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObIngrRecord, CObEffectItemRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObIngrEnitSubrecord*	m_pEnchantData;
  CObFloatSubrecord*	m_pIngrData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObIngrRecord();
  //virtual ~CObIngrRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObIngrRecord; }

	/* Get class members */
  obingrenitdata_t* GetEnchantData (void) { return (m_pEnchantData ? &m_pEnchantData->GetEnchantData()  : NULL); }
  float		    GetWeight      (void) { return (m_pIngrData    ?  m_pIngrData->GetValue()           : 0); }
  dword		    GetValue       (void) { return (m_pEnchantData ?  m_pEnchantData->GetValue()        : 0); }
  bool              IsAutoCalc     (void) { return (m_pEnchantData ?  m_pEnchantData->IsAutoCalc()      : false); }
  bool              IsFoodItem     (void) { return (m_pEnchantData ?  m_pEnchantData->IsFoodItem()      : false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetWeight   (const float Value) { if (m_pIngrData    != NULL) m_pIngrData->SetValue(Value); }
  void SetValue    (const dword Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetValue(Value); }
  void SetAutoCalc (const bool  Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetAutoCalc(Value); }
  void SetFoodItem (const bool  Value) { if (m_pEnchantData != NULL) m_pEnchantData->SetFoodItem(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldAutoCalc)
  DECLARE_OBFIELD(FieldFoodItem)

};
/*===========================================================================
 *		End of Class CObIngrRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObIngrrecord.H
 *=========================================================================*/
