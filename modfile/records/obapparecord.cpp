/*===========================================================================
 *
 * File:	ObAppaRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obapparecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAppaRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObAppaDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAppaRecord, CObItem1Record)
	ADD_OBFIELDALL("Weight",  OB_FIELD_WEIGHT,  0, CObAppaRecord, FieldWeight)
	ADD_OBFIELDALL("Quality", OB_FIELD_QUALITY, 0, CObAppaRecord, FieldQuality)
	ADD_OBFIELDALL("Value",   OB_FIELD_VALUE,   0, CObAppaRecord, FieldValue)
	ADD_OBFIELDALL("Type",    OB_FIELD_TYPE,    0, CObAppaRecord, FieldType)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaRecord Constructor
 *
 *=========================================================================*/
CObAppaRecord::CObAppaRecord () {
  m_pAppaData = NULL;
 }
/*===========================================================================
 *		End of Class CObAppaRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAppaRecord::Destroy (void) {
  m_pAppaData = NULL;  

  CObItem1Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObAppaRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObAppaRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pAppaData != NULL) m_pAppaData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObAppaRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAppaRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pAppaData = ObCastClass(CObAppaDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 13, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_2INTVALUE1(pSubrecord->GetRecordSize(), 24, 48, OB_NAME_MODT);
   }
  else
    CObItem1Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObAppaRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAppaRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAppaRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pAppaData == pSubrecord) {
    m_pAppaData = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObAppaRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAppaRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObAppaRecord::GetFieldWeight,  String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObAppaRecord::GetFieldQuality, String.Format("%g", GetQuality()))
DEFINE_OBGETFIELD(CObAppaRecord::GetFieldValue,   String.Format("%u", GetValue()))
DEFINE_OBGETFIELD(CObAppaRecord::GetFieldType,    String.Format("%s", GetObApparatusTypeString(GetType())))
/*===========================================================================
 *		End of CObAppaRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAppaRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObAppaRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObAppaRecord, CompareFieldQuality, GetQuality, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObAppaRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObAppaRecord, CompareFieldType, GetType)
/*===========================================================================
 *		End of CObAppaRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAppaRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObAppaRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAppaRecord::SetFieldQuality)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetQuality(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAppaRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAppaRecord::SetFieldType)
  int Value;

  if (!GetObApparatusTypeValue(Value, pString)) {
    AddObGeneralError("The string '%s' is not a valid apparatus type!", pString);
    return (false);
  }

  SetType((byte) Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObAppaRecord Set Field Methods
 *=========================================================================*/
