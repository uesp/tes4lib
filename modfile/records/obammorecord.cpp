/*===========================================================================
 *
 * File:	Obammorecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obammorecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAmmoRecord, CObItem2Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObAmmoDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAmmoRecord, CObItem2Record)
	ADD_OBFIELDALL("Speed",  OB_FIELD_SPEED,	0, CObAmmoRecord, FieldSpeed)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT,	0, CObAmmoRecord, FieldWeight)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,	0, CObAmmoRecord, FieldValue)
	ADD_OBFIELDALL("Damage", OB_FIELD_DAMAGE,	0, CObAmmoRecord, FieldDamage)
	ADD_OBFIELDALL("Ignore", OB_FIELD_IGNORERESIST, 0, CObAmmoRecord, FieldIgnoreResist)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoRecord Constructor
 *
 *=========================================================================*/
CObAmmoRecord::CObAmmoRecord () {
  m_pAmmoData = NULL;
 }
/*===========================================================================
 *		End of Class CObAmmoRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAmmoRecord::Destroy (void) {
  m_pAmmoData = NULL;

  CObItem2Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObAmmoRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObAmmoRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem2Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pAmmoData != NULL) m_pAmmoData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObAmmoRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAmmoRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pAmmoData = ObCastClass(CObAmmoDataSubrecord, pSubrecord);
    //TEST_INTVALUE(m_pAmmoData->GetRecordSize(), 0x12);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    TEST_INTVALUE(pSubrecord->GetRecordSize(), 0x04);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    TEST_INTVALUE(pSubrecord->GetRecordSize(), 0x18);
   }
  else
    CObItem2Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObAmmoRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAmmoRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAmmoRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pAmmoData == pSubrecord) {
    m_pAmmoData = NULL;
  }
  else {
    CObItem2Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObAmmoRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAmmoRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObAmmoRecord::GetFieldSpeed,        String.Format("%g", GetSpeed()))
DEFINE_OBGETFIELD(CObAmmoRecord::GetFieldWeight,       String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObAmmoRecord::GetFieldValue,        String.Format("%u", GetValue()))
DEFINE_OBGETFIELD(CObAmmoRecord::GetFieldDamage,       String.Format("%u", (dword) GetDamage()))
DEFINE_OBGETFIELD(CObAmmoRecord::GetFieldIgnoreResist, String.Format("%s", BooleanToString(IsIgnoreResist()) ))
/*===========================================================================
 *		End of CObAmmoRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAmmoRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObAmmoRecord, CompareFieldSpeed, GetSpeed, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObAmmoRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObAmmoRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDDWORD(CObAmmoRecord, CompareFieldDamage, GetDamage)
DEFINE_OBCOMPFIELDINT(CObAmmoRecord, CompareFieldIgnoreResist, IsIgnoreResist)
/*===========================================================================
 *		End of CObAmmoRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAmmoRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObAmmoRecord::SetFieldSpeed)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetSpeed(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAmmoRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAmmoRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAmmoRecord::SetFieldDamage)
  word Value;

  if (!ObFieldConvertWord(pString, Value)) return (false);
  SetDamage(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObAmmoRecord::SetFieldIgnoreResist)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetIgnoreResist(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObAmmoRecord Set Field Methods
 *=========================================================================*/

