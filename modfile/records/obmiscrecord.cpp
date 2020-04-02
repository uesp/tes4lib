/*===========================================================================
 *
 * File:	Obmiscrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obmiscrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObMiscRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObMiscDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObMiscRecord, CObItem1Record)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,  0, CObMiscRecord, FieldValue)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT, 0, CObMiscRecord, FieldWeight)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscRecord Constructor
 *
 *=========================================================================*/
CObMiscRecord::CObMiscRecord () {
  m_pMiscData = NULL;
 }
/*===========================================================================
 *		End of Class CObMiscRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObMiscRecord::Destroy (void) {
  m_pMiscData = NULL;

  CObItem1Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObMiscRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObMiscRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pMiscData != NULL) m_pMiscData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObMiscRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObMiscRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pMiscData = ObCastClass(CObMiscDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pMiscData->GetRecordSize(), 8, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MODT);
   }
  else
    CObItem1Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObMiscRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMiscRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObMiscRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pMiscData == pSubrecord)
    m_pMiscData = NULL;
  else
    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObMiscRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMiscRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObMiscRecord::GetFieldValue,  String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObMiscRecord::GetFieldWeight, String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
/*===========================================================================
 *		End of CObMiscRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMiscRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObMiscRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDFLOAT(CObMiscRecord, CompareFieldWeight, GetWeight, 100.0f)
/*===========================================================================
 *		End of CObMiscRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMiscRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObMiscRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObMiscRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObMiscRecord Set Field Methods
 *=========================================================================*/
