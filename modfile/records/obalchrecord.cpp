/*===========================================================================
 *
 * File:	ObAlchrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obalchrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAlchRecord, CObEffectItemRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENIT, CObEnit8Subrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObFloatSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAlchRecord, CObEffectItemRecord)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT,   0, CObAlchRecord, FieldWeight)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,    0, CObAlchRecord, FieldValue)
	ADD_OBFIELDALL("Auto",   OB_FIELD_AUTOCALC, 0, CObAlchRecord, FieldAutoCalc)
	ADD_OBFIELDALL("Food",   OB_FIELD_FOOD,     0, CObAlchRecord, FieldFoodItem)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAlchRecord Constructor
 *
 *=========================================================================*/
CObAlchRecord::CObAlchRecord () {
  m_pData       = NULL;
  m_pWeightData = NULL;
}
/*===========================================================================
 *		End of Class CObAlchRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAlchRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAlchRecord::Destroy (void) {
  m_pData       = NULL;
  m_pWeightData = NULL;

  CObEffectItemRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObAlchRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAlchRecord Method - void InitializeNew (void);
 *
 * Initialize a new enchantment record.
 *
 *=========================================================================*/
void CObAlchRecord::InitializeNew (void) {

  CObEffectItemRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pWeightData != NULL) m_pWeightData->InitializeNew();

  AddNewSubrecord(OB_NAME_ENIT);
  if (m_pData != NULL) m_pData->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObAlchRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAlchRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAlchRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pWeightData = ObCastClass(CObFloatSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_ENIT) {
    m_pData = ObCastClass(CObEnit8Subrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 8, OB_NAME_ENIT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 24, OB_NAME_MODT);
   }
  else {
    CObEffectItemRecord::OnAddSubrecord(pSubrecord);
  }
}
/*===========================================================================
 *		End of Class Event CObAlchRecord::OnAddSubRecord()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObAlchRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAlchRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pData == pSubrecord) {
    m_pData = NULL;
  }
  else if (m_pWeightData == pSubrecord) {
    m_pWeightData = NULL;
  }
  else {
    CObEffectItemRecord::OnDeleteSubrecord(pSubrecord);
  }


}
/*===========================================================================
 *		End of Class Event CObAlchRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAlchRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObAlchRecord::GetFieldWeight,   String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObAlchRecord::GetFieldValue,    String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObAlchRecord::GetFieldAutoCalc, String.Format("%s",   BooleanToString(IsAutoCalc()) ))
DEFINE_OBGETFIELD(CObAlchRecord::GetFieldFoodItem, String.Format("%s",   BooleanToString(IsFoodItem()) ))
/*===========================================================================
 *		End of CObAlchRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAlchRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObAlchRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObAlchRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObAlchRecord, CompareFieldAutoCalc, IsAutoCalc)
DEFINE_OBCOMPFIELDINT(CObAlchRecord, CompareFieldFoodItem, IsFoodItem)
/*===========================================================================
 *		End of CObAlchRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAlchRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObAlchRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAlchRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAlchRecord::SetFieldAutoCalc)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAutoCalc(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAlchRecord::SetFieldFoodItem)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetFoodItem(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObAlchRecord Set Field Methods
 *=========================================================================*/
