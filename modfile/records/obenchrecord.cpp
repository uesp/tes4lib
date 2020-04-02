/*===========================================================================
 *
 * File:	Obenchrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obenchrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObEnchRecord, CObEffectItemRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENIT, CObEnitSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObEnchRecord, CObEffectItemRecord)
	ADD_OBFIELDALL("Type",   OB_FIELD_TYPE,     0, CObEnchRecord, FieldType)
	ADD_OBFIELDALL("Charge", OB_FIELD_CHARGE,   0, CObEnchRecord, FieldCharge)
	ADD_OBFIELDALL("Cost",   OB_FIELD_COST,	    0, CObEnchRecord, FieldCost)
	ADD_OBFIELDALL("Auto",   OB_FIELD_AUTOCALC, 0, CObEnchRecord, FieldAutoCalc)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnchRecord Constructor
 *
 *=========================================================================*/
CObEnchRecord::CObEnchRecord () {
  m_pEnchantData = NULL;
 }
/*===========================================================================
 *		End of Class CObEnchRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnchRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEnchRecord::Destroy (void) {
  m_pEnchantData = NULL;

  CObEffectItemRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObEnchRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnchRecord Method - void InitializeNew (void);
 *
 * Initialize a new enchantment record.
 *
 *=========================================================================*/
void CObEnchRecord::InitializeNew (void) {

  CObEffectItemRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_ENIT);
  if (m_pEnchantData != NULL) m_pEnchantData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObEnchRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnchRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObEnchRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_ENIT) {
    m_pEnchantData = ObCastClass(CObEnitSubrecord, pSubrecord);
   }
  else
    CObEffectItemRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObEnchRecord::OnAddSubRecord()
 *=========================================================================*/

 
/*===========================================================================
 *
 * Class CObEnchRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObEnchRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pEnchantData == pSubrecord) {
    m_pEnchantData = NULL;
  }
  else {
    CObEffectItemRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObEnchRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObEnchRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObEnchRecord::GetFieldType,     String.Format("%s", GetObEnchantTypeString(GetType()) ))
DEFINE_OBGETFIELD(CObEnchRecord::GetFieldCharge,   String.Format("%u", GetCharge() ))
DEFINE_OBGETFIELD(CObEnchRecord::GetFieldCost,     String.Format("%u", GetCost() ))
DEFINE_OBGETFIELD(CObEnchRecord::GetFieldAutoCalc, String.Format("%s", BooleanToString(IsAutoCalc()) ))
/*===========================================================================
 *		End of CObEnchRecord Get Field Methods
 *=========================================================================*/

 
/*===========================================================================
 *
 * Begin CObEnchRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObEnchRecord, CompareFieldType, GetType)
DEFINE_OBCOMPFIELDDWORD(CObEnchRecord, CompareFieldCharge, GetCharge)
DEFINE_OBCOMPFIELDDWORD(CObEnchRecord, CompareFieldCost, GetCost)
DEFINE_OBCOMPFIELDINT(CObEnchRecord, CompareFieldAutoCalc, IsAutoCalc)
/*===========================================================================
 *		End of CObEnchRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObEnchRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObEnchRecord::SetFieldType)
  int Value;

  if (!GetObEnchantTypeValue(Value, pString)) {
    AddObGeneralError("The string '%s' is not a valid enchantment type!", pString);
    return (false);
  }

  SetType(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObEnchRecord::SetFieldCharge)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetCharge(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObEnchRecord::SetFieldCost)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetCost(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObEnchRecord::SetFieldAutoCalc)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAutoCalc(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObEnchRecord Field Methods
 *=========================================================================*/
