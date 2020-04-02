/*===========================================================================
 *
 * File:	Obweaprecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obweaprecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObWeapRecord, CObItem2Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_ICO2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD3, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD4, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObWeapDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObWeapRecord, CObItem2Record)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT,	0, CObWeapRecord, FieldWeight)
	ADD_OBFIELDALL("Speed",  OB_FIELD_SPEED,	0, CObWeapRecord, FieldSpeed)
	ADD_OBFIELDALL("Reach",  OB_FIELD_REACH,	0, CObWeapRecord, FieldReach)
	ADD_OBFIELDALL("Type",   OB_FIELD_TYPE,		0, CObWeapRecord, FieldType)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,	0, CObWeapRecord, FieldValue)
	ADD_OBFIELDALL("Health", OB_FIELD_HEALTH,	0, CObWeapRecord, FieldHealth)
	ADD_OBFIELDALL("Damage", OB_FIELD_DAMAGE,	0, CObWeapRecord, FieldDamage)
	ADD_OBFIELDALL("Ignore", OB_FIELD_IGNORERESIST, 0, CObWeapRecord, FieldIgnoreResist)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapRecord Constructor
 *
 *=========================================================================*/
CObWeapRecord::CObWeapRecord () {
  m_pWeaponData = NULL;
 }
/*===========================================================================
 *		End of Class CObWeapRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObWeapRecord::Destroy (void) {
  m_pWeaponData = NULL;

  CObItem2Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObWeapRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObWeapRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem2Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pWeaponData != NULL) m_pWeaponData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObWeapRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWeapRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pWeaponData = ObCastClass(CObWeapDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pWeaponData->GetRecordSize(), 30, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MODT);
   }
  else
    CObItem2Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObWeapRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWeapRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWeapRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pWeaponData == pSubrecord)
    m_pWeaponData = NULL;
  else
    CObItem2Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObWeapRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWeapRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldWeight,       String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldSpeed,        String.Format("%g", GetSpeed()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldReach,        String.Format("%g", GetReach()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldType,         String.Format("%s", GetObWeaponTypeString(GetType()) ))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldValue,        String.Format("%u", GetValue()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldHealth,       String.Format("%u", GetHealth()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldDamage,       String.Format("%d", (int)GetDamage()))
DEFINE_OBGETFIELD(CObWeapRecord::GetFieldIgnoreResist, String.Format("%s", BooleanToString(IsIgnoreResist())))
/*===========================================================================
 *		End of CObWeapRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWeapRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObWeapRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObWeapRecord, CompareFieldSpeed, GetSpeed, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObWeapRecord, CompareFieldReach, GetReach, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObWeapRecord, CompareFieldType, GetType)
DEFINE_OBCOMPFIELDDWORD(CObWeapRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDDWORD(CObWeapRecord, CompareFieldHealth, GetHealth)
DEFINE_OBCOMPFIELDINT(CObWeapRecord, CompareFieldDamage, GetDamage)
DEFINE_OBCOMPFIELDINT(CObWeapRecord, CompareFieldIgnoreResist, IsIgnoreResist)
/*===========================================================================
 *		End of CObWeapRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWeapRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObWeapRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldSpeed)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetSpeed(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldReach)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetReach(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldHealth)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetHealth(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldType)
  int Value;

  if (!GetObWeaponTypeValue(Value, pString)) return (false);
  SetType(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldDamage)
  word Value;

  if (!ObFieldConvertWord(pString, Value)) return (false);
  SetDamage(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObWeapRecord::SetFieldIgnoreResist)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetIgnoreResist(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObWeapRecord Set Field Methods
 *=========================================================================*/

