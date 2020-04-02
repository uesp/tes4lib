/*===========================================================================
 *
 * File:	Obingrrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obingrrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObIngrRecord, CObEffectItemRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObFloatSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENIT, CObIngrEnitSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObIngrRecord, CObEffectItemRecord)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT,   0, CObIngrRecord, FieldWeight)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,    0, CObIngrRecord, FieldValue)
	ADD_OBFIELDALL("Auto",   OB_FIELD_AUTOCALC, 0, CObIngrRecord, FieldAutoCalc)
	ADD_OBFIELDALL("Food",   OB_FIELD_FOOD,     0, CObIngrRecord, FieldFoodItem)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIngrRecord Constructor
 *
 *=========================================================================*/
CObIngrRecord::CObIngrRecord () {
  m_pEnchantData = NULL;
  m_pIngrData    = NULL;
 }
/*===========================================================================
 *		End of Class CObIngrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIngrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObIngrRecord::Destroy (void) {
  m_pEnchantData = NULL;
  m_pIngrData    = NULL;

  CObEffectItemRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObIngrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIngrRecord Method - void InitializeNew (void);
 *
 * Initialize a new enchantment record.
 *
 *=========================================================================*/
void CObIngrRecord::InitializeNew (void) {

  CObEffectItemRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pIngrData != NULL) m_pIngrData->InitializeNew();

  AddNewSubrecord(OB_NAME_ENIT);
  if (m_pEnchantData != NULL) m_pEnchantData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObIngrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIngrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObIngrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pIngrData = ObCastClass(CObFloatSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_ENIT) {
    m_pEnchantData = ObCastClass(CObIngrEnitSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 8, OB_NAME_ENIT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 24, OB_NAME_MODT);
   }
  else
    CObEffectItemRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObIngrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIngrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObIngrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pIngrData == pSubrecord) {
    m_pIngrData = NULL;
  }
  else if (m_pEnchantData == pSubrecord) {
    m_pEnchantData = NULL;
  }
  else {
    CObEffectItemRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObIngrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIngrRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObIngrRecord::GetFieldWeight,   String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObIngrRecord::GetFieldValue,    String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObIngrRecord::GetFieldAutoCalc, String.Format("%s",   BooleanToString(IsAutoCalc()) ))
DEFINE_OBGETFIELD(CObIngrRecord::GetFieldFoodItem, String.Format("%s",   BooleanToString(IsFoodItem()) ))
/*===========================================================================
 *		End of CObIngrRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIngrRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObIngrRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObIngrRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObIngrRecord, CompareFieldAutoCalc, IsAutoCalc)
DEFINE_OBCOMPFIELDINT(CObIngrRecord, CompareFieldFoodItem, IsFoodItem)
/*===========================================================================
 *		End of CObIngrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIngrRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObIngrRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObIngrRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObIngrRecord::SetFieldAutoCalc)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAutoCalc(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObIngrRecord::SetFieldFoodItem)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetFoodItem(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObIngrRecord Set Field Methods
 *=========================================================================*/
