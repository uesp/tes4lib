/*===========================================================================
 *
 * File:	ObKeymRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obkeymrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObKeymRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObKeymDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObKeymRecord, CObItem1Record)
	ADD_OBFIELDALL("Weight",  OB_FIELD_WEIGHT,  0, CObKeymRecord, FieldWeight)
	ADD_OBFIELDALL("Value",   OB_FIELD_VALUE,   0, CObKeymRecord, FieldValue)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObKeymRecord Constructor
 *
 *=========================================================================*/
CObKeymRecord::CObKeymRecord () {
  m_pKeyData = NULL;
}
/*===========================================================================
 *		End of Class CObKeymRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObKeymRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObKeymRecord::Destroy (void) {
  m_pKeyData = NULL;  

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObKeymRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObKeymRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObKeymRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pKeyData != NULL) m_pKeyData->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObKeymRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObKeymRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObKeymRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pKeyData = ObCastClass(CObKeymDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 13, OB_NAME_DATA);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_2INTVALUE1(pSubrecord->GetRecordSize(), 24, 48, OB_NAME_MODT);
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

} 
/*===========================================================================
 *		End of Class Event CObKeymRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObKeymRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObKeymRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pKeyData == pSubrecord) {
    m_pKeyData = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObKeymRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObKeymRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObKeymRecord::GetFieldWeight,  String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObKeymRecord::GetFieldValue,   String.Format("%u", GetValue()))
/*===========================================================================
 *		End of CObKeymRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObKeymRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObKeymRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObKeymRecord, CompareFieldValue, GetValue)
/*===========================================================================
 *		End of CObKeymRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObKeymRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObKeymRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObKeymRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObKeymRecord Set Field Methods
 *=========================================================================*/
