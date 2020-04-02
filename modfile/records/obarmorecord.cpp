/*===========================================================================
 *
 * File:	ObArmorecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obarmorecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObArmoRecord, CObItem2Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_ICO2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD3, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD4, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_BMDT, CObBmdtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObArmoDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObArmoRecord, CObItem2Record)
	ADD_OBFIELDALL("Weight",    OB_FIELD_WEIGHT,	 0, CObArmoRecord, FieldWeight)
	ADD_OBFIELDALL("Value",     OB_FIELD_VALUE,	 0, CObArmoRecord, FieldValue)
	ADD_OBFIELDALL("Biped",     OB_FIELD_BIPED,	 0, CObArmoRecord, FieldBipedParts)
	ADD_OBFIELDALL("Amulet",    OB_FIELD_HIDEAMULET, 0, CObArmoRecord, FieldHideAmulet)
	ADD_OBFIELDALL("Rings",     OB_FIELD_HIDERINGS,  0, CObArmoRecord, FieldHideRings)
	ADD_OBFIELDALL("Model2",    OB_FIELD_MODEL2,	 0, CObArmoRecord, FieldModel2)
	ADD_OBFIELDALL("Model3",    OB_FIELD_MODEL3,	 0, CObArmoRecord, FieldModel3)
	ADD_OBFIELDALL("Model4",    OB_FIELD_MODEL4,	 0, CObArmoRecord, FieldModel4)
	ADD_OBFIELDALL("Icon2",     OB_FIELD_ICON2,	 0, CObArmoRecord, FieldIcon2)
	ADD_OBFIELDALL("Health",    OB_FIELD_HEALTH,	 0, CObArmoRecord, FieldHealth)
	ADD_OBFIELDALL("Type",      OB_FIELD_TYPE,	 0, CObArmoRecord, FieldType)
	ADD_OBFIELDALL("ArmorData", OB_FIELD_ARMOR,	 0, CObArmoRecord, FieldArmor)
	ADD_OBFIELDALL("Armor",     OB_FIELD_REALARMOR,	 0, CObArmoRecord, FieldRealArmor)
	ADD_OBFIELDALL("Playable",  OB_FIELD_PLAYABLE,	 0, CObArmoRecord, FieldPlayable)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Constructor
 *
 *=========================================================================*/
CObArmoRecord::CObArmoRecord () {
  m_pArmorData = NULL;
  m_pFlags     = NULL;
  m_pIcon2     = NULL;
  m_pModel2    = NULL;
  m_pModel3    = NULL;
  m_pModel4    = NULL;
 }
/*===========================================================================
 *		End of Class CObArmoRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObArmoRecord::Destroy (void) {
  m_pArmorData = NULL;
  m_pFlags     = NULL;
  m_pIcon2     = NULL;
  m_pModel2    = NULL;
  m_pModel3    = NULL;
  m_pModel4    = NULL;

  CObItem2Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObArmoRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem2Record::InitializeNew();

  AddNewSubrecord(OB_NAME_BMDT);
  if (m_pFlags != NULL) m_pFlags->InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pArmorData != NULL) m_pArmorData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObArmoRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pArmorData = ObCastClass(CObArmoDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pArmorData->GetRecordSize(), 14, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_BMDT) {
    m_pFlags = ObCastClass(CObBmdtSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_BMDT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_ICO2) {
    m_pIcon2 = ObCastClass(CObStringSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MOD2) {
    m_pModel2 = ObCastClass(CObStringSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MOD3) {
    m_pModel3 = ObCastClass(CObStringSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MOD4) {
    m_pModel4 = ObCastClass(CObStringSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO2B) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MO2B);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO3B) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MO3B);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO4B) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MO4B);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MODT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO2T) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MO2T);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO3T) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MO3T);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MO4T) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MO4T);
   }
  else
    CObItem2Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObArmoRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObArmoRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pArmorData == pSubrecord) {
    m_pArmorData = NULL;
  }
  else if (m_pFlags == pSubrecord) {
    m_pFlags = NULL;
  }
  else if (m_pIcon2 == pSubrecord) {
    m_pIcon2 = NULL;
  }
  else if (m_pModel2 == pSubrecord) {
    m_pModel2 = NULL;
  }
  else if (m_pModel3 == pSubrecord) {
    m_pModel3 = NULL;
  }
  else if (m_pModel4 == pSubrecord) {
    m_pModel4 = NULL;
  }
  else {
    CObItem2Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObArmoRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void SetIcon2 (pString);
 *
 *=========================================================================*/
void CObArmoRecord::SetIcon2 (const SSCHAR* pString) {

  if (m_pIcon2 == NULL) {
     AddNewSubrecord(OB_NAME_ICO2);
     if (m_pIcon2 == NULL) return;
     m_pIcon2->InitializeNew();
   }

  m_pIcon2->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::SetIcon2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void SetModel2 (pString);
 *
 *=========================================================================*/
void CObArmoRecord::SetModel2 (const SSCHAR* pString) {

  if (m_pModel2 == NULL) {
     AddNewSubrecord(OB_NAME_MOD2);
     if (m_pModel2 == NULL) return;
     m_pModel2->InitializeNew();
   }

  m_pModel2->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::SetModel2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void SetModel3 (pString);
 *
 *=========================================================================*/
void CObArmoRecord::SetModel3 (const SSCHAR* pString) {

  if (m_pModel3 == NULL) {
    AddNewSubrecord(OB_NAME_MOD3);
    if (m_pModel3 == NULL) return;
    m_pModel3->InitializeNew();
   }

  m_pModel3->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::SetModel3()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObArmoRecord Method - void SetModel4 (pString);
 *
 *=========================================================================*/
void CObArmoRecord::SetModel4 (const SSCHAR* pString) {

  if (m_pModel4 == NULL) {
    AddNewSubrecord(OB_NAME_MOD4);
    if (m_pModel4 == NULL) return;
    m_pModel4->InitializeNew();
   }

  m_pModel4->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObArmoRecord::SetModel4()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObArmoRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldWeight,     String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldType,       String.Format("%s",   IsLightArmor() ? "Light" : "Heavy"))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldArmor,      String.Format("%u",   (dword) GetArmor()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldRealArmor,  String.Format("%.2f",   (float)GetArmor() / 100.0f))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldHealth,     String.Format("%u",   GetHealth()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldValue,      String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldPlayable,   String.Format("%s",   BooleanToString(IsPlayable()) ))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldBipedParts, MakeObBipedFlagString(String, GetBipedFlags(), ", ") )
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldHideAmulet, String.Format("%s",   BooleanToString(IsHideAmulet()) ))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldHideRings,  String.Format("%s",   BooleanToString(IsHideRings()) ))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldModel2,     String.Format("%s",   GetModel2()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldModel3,     String.Format("%s",   GetModel3()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldModel4,     String.Format("%s",   GetModel4()))
DEFINE_OBGETFIELD(CObArmoRecord::GetFieldIcon2,      String.Format("%s",   GetIcon2()))
/*===========================================================================
 *		End of CObArmoRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObArmoRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObArmoRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldType, IsLightArmor)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldArmor, GetArmor)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldRealArmor, GetArmor)
DEFINE_OBCOMPFIELDDWORD(CObArmoRecord, CompareFieldHealth, GetHealth)
DEFINE_OBCOMPFIELDDWORD(CObArmoRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldPlayable, IsPlayable)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldBipedParts, GetBipedFlags)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldHideAmulet, IsHideAmulet)
DEFINE_OBCOMPFIELDINT(CObArmoRecord, CompareFieldHideRings, IsHideRings)
DEFINE_OBCOMPFIELDSTRING(CObArmoRecord, CompareFieldModel2, GetModel2)
DEFINE_OBCOMPFIELDSTRING(CObArmoRecord, CompareFieldModel3, GetModel3)
DEFINE_OBCOMPFIELDSTRING(CObArmoRecord, CompareFieldModel4, GetModel4)
DEFINE_OBCOMPFIELDSTRING(CObArmoRecord, CompareFieldIcon2, GetIcon2)
/*===========================================================================
 *		End of CObArmoRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObArmoRecord Get Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObArmoRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldType)

  if (stricmp(pString, "light") == 0) {
    SetLightArmor(true);
  }
  else if (stricmp(pString, "heavy") == 0) {
    SetLightArmor(false);
  }
  else {
    AddObGeneralError("The string '%s' is not a valid armor type!", pString);
    return (false);
  }

END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldArmor)
  word Value;

  if (!ObFieldConvertWord(pString, Value)) return (false);
  SetArmor(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldRealArmor)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);

  Value = Value * 100;
  if (Value <     0) Value = 0;
  if (Value > 65535) Value = 65535;
  SetArmor((word)Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldHealth)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetHealth(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldPlayable)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetPlayable(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldBipedParts)
  dword Value;

  Value = ParseObBipedFlagString(pString, ",");
  SetBipedFlags(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldHideAmulet)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetHideAmulet(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldHideRings)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetHideRings(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObArmoRecord::SetFieldModel2)
  SetModel2(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObArmoRecord::SetFieldModel3)
  SetModel3(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObArmoRecord::SetFieldModel4)
  SetModel4(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObArmoRecord::SetFieldIcon2)
  SetIcon2(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObArmoRecord Get Field Methods
 *=========================================================================*/

