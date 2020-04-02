/*===========================================================================
 *
 * File:	ObLightrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 22, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "oblighrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLighRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObLighDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_FNAM, CObFloatSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLighRecord, CObItem1Record)
	ADD_OBFIELDALL("Fade",		OB_FIELD_FADE,			 0, CObLighRecord, FieldFade)
	ADD_OBFIELDALL("Time",		OB_FIELD_TIME,			 0, CObLighRecord, FieldTime)
	ADD_OBFIELDALL("Radius",	OB_FIELD_RADIUS,		 0, CObLighRecord, FieldRadius)
	ADD_OBFIELDALL("Color",		OB_FIELD_COLOR,			 0, CObLighRecord, FieldColor)
	ADD_OBFIELDALL("Red",		OB_FIELD_REDCOLOR,		 0, CObLighRecord, FieldRedColor)
	ADD_OBFIELDALL("Green",		OB_FIELD_GREENCOLOR,		 0, CObLighRecord, FieldGreenColor)
	ADD_OBFIELDALL("Blue",		OB_FIELD_BLUECOLOR,		 0, CObLighRecord, FieldBlueColor)
	ADD_OBFIELDALL("Falloff",	OB_FIELD_FALLOFF,		 0, CObLighRecord, FieldFalloff)
	ADD_OBFIELDALL("FOV",		OB_FIELD_FOV,			 0, CObLighRecord, FieldFOV)
	ADD_OBFIELDALL("Type",		OB_FIELD_TYPE,			 0, CObLighRecord, FieldType)
	ADD_OBFIELDALL("Carried",	OB_FIELD_CARRIED,		 0, CObLighRecord, FieldCarried)
	ADD_OBFIELDALL("Dynamic",	OB_FIELD_DYNAMIC,		 0, CObLighRecord, FieldDynamic)
	ADD_OBFIELDALL("Negative",	OB_FIELD_NEGATIVE,		 0, CObLighRecord, FieldNegative)
	ADD_OBFIELDALL("Off",		OB_FIELD_DEFAULTOFF,		 0, CObLighRecord, FieldDefaultOff)
	ADD_OBFIELDALL("SpotLight",	OB_FIELD_SPOTLIGHT,		 0, CObLighRecord, FieldSpotLight)
	ADD_OBFIELDALL("SpotShadow",	OB_FIELD_SPOTSHADOW,		 0, CObLighRecord, FieldSpotShadow)
	ADD_OBFIELDALL("Value",		OB_FIELD_VALUE,			 0, CObLighRecord, FieldValue)
	ADD_OBFIELDALL("Weight",	OB_FIELD_WEIGHT,		 0, CObLighRecord, FieldWeight)
	ADD_OBFIELDALL("SoundID",	OB_FIELD_SOUNDID,	OBRF_NOCSV, CObLighRecord, FieldSoundID)
	ADD_OBFIELDALL("Sound",		OB_FIELD_SOUND,			 0, CObLighRecord, FieldSound)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Constructor
 *
 *=========================================================================*/
CObLighRecord::CObLighRecord () {
  m_pLighData  = NULL;
  m_pSound     = NULL;
  m_pFadeData  = NULL;
}
/*===========================================================================
 *		End of Class CObLighRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLighRecord::Destroy (void) {
  m_pLighData  = NULL;
  m_pSound     = NULL;
  m_pFadeData  = NULL;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLighRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLighRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pLighData != NULL) m_pLighData->InitializeNew();

  AddNewSubrecord(OB_NAME_FNAM);
  if (m_pFadeData != NULL) m_pFadeData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObLighRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLighRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pLighData = ObCastClass(CObLighDataSubrecord, pSubrecord);
    //TEST_2INTVALUE1(m_pLighData->GetRecordSize(), 24, 32, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MODT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SNAM) {
    m_pSound = ObCastClass(CObFormidSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_FNAM) {
    m_pFadeData = ObCastClass(CObFloatSubrecord, pSubrecord);
   }
  else
    CObItem1Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObLighRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLighRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pLighData == pSubrecord)
    m_pLighData = NULL;
  else if (m_pSound == pSubrecord)
    m_pSound = NULL;
  else if (m_pFadeData == pSubrecord)
    m_pFadeData = NULL;
  else
    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObLighRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLighRecord Method - void SetSound (FormID);
 *
 *=========================================================================*/
void CObLighRecord::SetSound (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL) {
    DeleteSubrecords(OB_NAME_SNAM);
    return;
  }

  if (m_pSound == NULL) {
     AddNewSubrecord(OB_NAME_SNAM);
     if (m_pSound == NULL) return;
     m_pSound->InitializeNew();
   }

  m_pSound->SetValue(FormID);
} 
/*===========================================================================
 *		End of Class Method CObLighRecord::SetSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLighRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObLighRecord::GetFieldSpotShadow,	String.Format("%s",   BooleanToString(IsSpotShadow())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldSpotLight,	String.Format("%s",   BooleanToString(IsSpotLight())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldDefaultOff,	String.Format("%s",   BooleanToString(IsDefaultOff())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldNegative,	String.Format("%s",   BooleanToString(IsNegative())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldDynamic,	String.Format("%s",   BooleanToString(IsDynamic())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldCarried,	String.Format("%s",   BooleanToString(IsCarried())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldType,		String.Format("%s",   GetObLightTypeString(GetLightType())))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldFOV,		String.Format("%g",   GetFOV()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldFalloff,	String.Format("%g",   GetFalloff()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldColor,		String.Format("%02X%02X%02X", GetColor().R, GetColor().G, GetColor().B))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldRedColor,	String.Format("%u", (dword) GetRedColor()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldGreenColor,	String.Format("%u", (dword) GetGreenColor()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldBlueColor,	String.Format("%u", (dword) GetBlueColor()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldRadius,	String.Format("%d",   GetRadius()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldFade,		String.Format("%g",   GetFade()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldTime,		String.Format("%d",   GetTime()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldValue,		String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObLighRecord::GetFieldWeight,	String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))

BEGIN_OBGETFIELD(CObLighRecord::GetFieldSound)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetSound());
        String.Format("0x%08X", GetSound());
END_OBGETFIELD()

BEGIN_OBGETFIELD(CObLighRecord::GetFieldSoundID)
	obformid_t SoundID = GetSound();
	String.Empty();
	if (SoundID != OB_FORMID_NULL) String.Format("0x%08X", GetSound());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObLighRecord Get Field Methods
 *=========================================================================*/



/*===========================================================================
 *
 * Begin CObLighRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldSpotShadow, IsSpotShadow)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldSpotLight, IsSpotLight)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldDefaultOff, IsDefaultOff)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldNegative, IsNegative)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldDynamic, IsDynamic)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldCarried, IsCarried)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldType, GetLightType)
DEFINE_OBCOMPFIELDFLOAT(CObLighRecord, CompareFieldFOV, GetFOV, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObLighRecord, CompareFieldFalloff, GetFalloff, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldColor, GetColor)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldRedColor, GetRedColor)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldGreenColor, GetGreenColor)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldBlueColor, GetBlueColor)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldRadius, GetRadius)
DEFINE_OBCOMPFIELDFLOAT(CObLighRecord, CompareFieldFade, GetFade, 100.0f)
DEFINE_OBCOMPFIELDINT(CObLighRecord, CompareFieldTime, GetTime)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDFLOAT(CObLighRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObLighRecord, CompareFieldSoundID, GetSound)
DEFINE_OBCOMPFIELDEDITORID(CObLighRecord, CompareFieldSound, GetSound)
/*===========================================================================
 *		End of CObLighRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLighRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObLighRecord::SetFieldSpotShadow)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetSpotShadow(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldSpotLight)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetSpotLight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldDefaultOff)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetDefaultOff(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldNegative)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetNegative(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldDynamic)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetDynamic(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldCarried)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetCarried(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldType)
  int Value;

  if (!GetObLightTypeValue(Value, pString)) return (false);
  SetLightType(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldFOV)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetFOV(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldFalloff)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetFalloff(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldColor)
  obrgba_t Value;

  if (!ObFieldConvertColor(pString, Value)) return (false);
  SetColor(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObLighRecord::SetFieldRedColor)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetRedColor(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObLighRecord::SetFieldGreenColor)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetGreenColor(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObLighRecord::SetFieldBlueColor)
  byte Value;

  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetBlueColor(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldRadius)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetRadius(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldFade)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetFade(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldTime)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetTime(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObLighRecord::SetFieldSound)
  CObIdRecord* pIdRecord = NULL;

  if (m_pParent == NULL)  return AddObGeneralError("Unable to find the formID for the sound '%s'!", pString);

  if (pString != NULL && *pString != 0) {
    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The sound '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SOUN) return AddObGeneralError("The record '%s' is not a sound (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetSound(pIdRecord->GetFormID());
  }
  else {
    SetSound(OB_FORMID_NULL);
  }

END_OBGETFIELD()

BEGIN_OBSETFIELD(CObLighRecord::SetFieldSoundID)
	AddObGeneralError("Cannot set the sound ID of an item from its SetField method!");
	return (false);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObLighRecord Set Field Methods
 *=========================================================================*/
