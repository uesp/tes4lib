/*===========================================================================
 *
 * File:	Obclotrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obclotrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObClotRecord, CObItem2Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_ICO2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD2, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD3, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MOD4, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_BMDT, CObDwordSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObClotDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObClotRecord, CObItem2Record)
	ADD_OBFIELDALL("Weight",    OB_FIELD_WEIGHT,	0, CObClotRecord, FieldWeight)
	ADD_OBFIELDALL("Value",     OB_FIELD_VALUE,	0, CObClotRecord, FieldValue)
	ADD_OBFIELDALL("Biped",     OB_FIELD_BIPED,	0, CObClotRecord, FieldBipedParts)
	ADD_OBFIELDALL("Amulet",    OB_FIELD_HIDEAMULET,0, CObClotRecord, FieldHideAmulet)
	ADD_OBFIELDALL("Rings",     OB_FIELD_HIDERINGS,	0, CObClotRecord, FieldHideRings)
	ADD_OBFIELDALL("Playable",  OB_FIELD_PLAYABLE,	0, CObClotRecord, FieldPlayable)
	ADD_OBFIELDALL("Model2",    OB_FIELD_MODEL2,	0, CObClotRecord, FieldModel2)
	ADD_OBFIELDALL("Model3",    OB_FIELD_MODEL3,	0, CObClotRecord, FieldModel3)
	ADD_OBFIELDALL("Model4",    OB_FIELD_MODEL4,	0, CObClotRecord, FieldModel4)
	ADD_OBFIELDALL("Icon2",     OB_FIELD_ICON2,	0, CObClotRecord, FieldIcon2)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Constructor
 *
 *=========================================================================*/
CObClotRecord::CObClotRecord () {
  m_pClothingData = NULL;
  m_pFlags        = NULL;
  m_pIcon2        = NULL;
  m_pModel2       = NULL;
  m_pModel3       = NULL;
  m_pModel4       = NULL;
 }
/*===========================================================================
 *		End of Class CObClotRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObClotRecord::Destroy (void) {
  m_pClothingData = NULL;
  m_pFlags        = NULL;
  m_pIcon2        = NULL;
  m_pModel2       = NULL;
  m_pModel3       = NULL;
  m_pModel4       = NULL;

  CObItem2Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObClotRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObClotRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem2Record::InitializeNew();

  AddNewSubrecord(OB_NAME_BMDT);
  if (m_pFlags != NULL) m_pFlags->InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pClothingData != NULL) m_pClothingData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObClotRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObClotRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pClothingData = ObCastClass(CObClotDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pClothingData->GetRecordSize(), 8, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_BMDT) {
    m_pFlags = ObCastClass(CObDwordSubrecord, pSubrecord);
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
 *		End of Class Event CObClotRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObClotRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pClothingData == pSubrecord) {
    m_pClothingData = NULL;
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
 *		End of Class Event CObClotRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void SetIcon2 (pString);
 *
 *=========================================================================*/
void CObClotRecord::SetIcon2 (const SSCHAR* pString) {

  if (m_pIcon2 == NULL) {
     AddNewSubrecord(OB_NAME_ICO2);
     if (m_pIcon2 == NULL) return;
     m_pIcon2->InitializeNew();
   }

  m_pIcon2->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObClotRecord::SetIcon2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void SetModel2 (pString);
 *
 *=========================================================================*/
void CObClotRecord::SetModel2 (const SSCHAR* pString) {

  if (m_pModel2 == NULL) {
     AddNewSubrecord(OB_NAME_MOD2);
     if (m_pModel2 == NULL) return;
     m_pModel2->InitializeNew();
   }

  m_pModel2->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObClotRecord::SetModel2()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void SetModel3 (pString);
 *
 *=========================================================================*/
void CObClotRecord::SetModel3 (const SSCHAR* pString) {

  if (m_pModel3 == NULL) {
     AddNewSubrecord(OB_NAME_MOD3);
     if (m_pModel3 == NULL) return;
     m_pModel3->InitializeNew();
   }

  m_pModel3->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObClotRecord::SetModel3()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClotRecord Method - void SetModel4 (pString);
 *
 *=========================================================================*/
void CObClotRecord::SetModel4 (const SSCHAR* pString) {

  if (m_pModel4 == NULL) {
     AddNewSubrecord(OB_NAME_MOD4);
     if (m_pModel4 == NULL) return;
     m_pModel4->InitializeNew();
   }

  m_pModel4->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObClotRecord::SetModel4()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClotRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObClotRecord::GetFieldWeight,     String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldValue,      String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldPlayable,   String.Format("%s",   BooleanToString(IsPlayable()) ))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldBipedParts, MakeObBipedFlagString(String, GetBipedFlags(), ", ") )
DEFINE_OBGETFIELD(CObClotRecord::GetFieldHideAmulet, String.Format("%s",   BooleanToString(IsHideAmulet()) ))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldHideRings,  String.Format("%s",   BooleanToString(IsHideRings()) ))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldModel2,     String.Format("%s",   GetModel2()))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldModel3,     String.Format("%s",   GetModel3()))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldModel4,     String.Format("%s",   GetModel4()))
DEFINE_OBGETFIELD(CObClotRecord::GetFieldIcon2,      String.Format("%s",   GetIcon2()))
/*===========================================================================
 *		End of CObClotRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClotRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObClotRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObClotRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObClotRecord, CompareFieldPlayable, IsPlayable)
DEFINE_OBCOMPFIELDDWORD(CObClotRecord, CompareFieldBipedParts, GetBipedFlags)
DEFINE_OBCOMPFIELDINT(CObClotRecord, CompareFieldHideAmulet, IsHideAmulet)
DEFINE_OBCOMPFIELDINT(CObClotRecord, CompareFieldHideRings, IsHideRings)
DEFINE_OBCOMPFIELDSTRING(CObClotRecord, CompareFieldModel2, GetModel2)
DEFINE_OBCOMPFIELDSTRING(CObClotRecord, CompareFieldModel3, GetModel3)
DEFINE_OBCOMPFIELDSTRING(CObClotRecord, CompareFieldModel4, GetModel4)
DEFINE_OBCOMPFIELDSTRING(CObClotRecord, CompareFieldIcon2, GetIcon2)
/*===========================================================================
 *		End of CObClotRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClotRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObClotRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObClotRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObClotRecord::SetFieldPlayable)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetPlayable(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObClotRecord::SetFieldBipedParts)
  dword Value;

  Value = ParseObBipedFlagString(pString, ",");
  SetBipedFlags(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObClotRecord::SetFieldHideAmulet)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetHideAmulet(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObClotRecord::SetFieldHideRings)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetHideRings(Value);
END_OBSETFIELD()



BEGIN_OBSETFIELD(CObClotRecord::SetFieldModel2)
  SetModel2(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObClotRecord::SetFieldModel3)
  SetModel3(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObClotRecord::SetFieldModel4)
  SetModel4(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObClotRecord::SetFieldIcon2)
  SetIcon2(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObRecord Set Field Methods
 *=========================================================================*/
