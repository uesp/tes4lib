/*===========================================================================
 *
 * File:	ObSounRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Implements the CObSounRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obsounrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObSounRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_FNAM, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNDX, CObSndxSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNDD, CObSndxSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObSounRecord, CObIdRecord)
	ADD_OBFIELDALL("Sound File",         OB_FIELD_SOUNDFILE,         0, CObSounRecord, FieldSoundFile)
	ADD_OBFIELDALL("Min Attenuation",    OB_FIELD_MINATTENUATION,    0, CObSounRecord, FieldMinAttenuation)
	ADD_OBFIELDALL("Max Attenuation",    OB_FIELD_MAXATTENUATION,    0, CObSounRecord, FieldMaxAttenuation)
	ADD_OBFIELDALL("Static Attenuation", OB_FIELD_STATICATTENUATION, 0, CObSounRecord, FieldStaticAttenuation)
	ADD_OBFIELDALL("Freq Adjustment",    OB_FIELD_FREQADJUSTMENT,    0, CObSounRecord, FieldFreqAdjustment)
	ADD_OBFIELDALL("Start Time",         OB_FIELD_STARTTIME,         0, CObSounRecord, FieldStartTime)
	ADD_OBFIELDALL("Stop Time",          OB_FIELD_STOPTIME,          0, CObSounRecord, FieldStopTime)
	ADD_OBFIELDALL("Random Freq Shift",  OB_FIELD_RANDOMFREQSHIFT,   0, CObSounRecord, FieldRandomFreqShift)
	ADD_OBFIELDALL("Random Play",        OB_FIELD_RANDOMPLAY,        0, CObSounRecord, FieldRandomPlay)
	ADD_OBFIELDALL("Random Location",    OB_FIELD_RANDOMLOCATION,    0, CObSounRecord, FieldRandomLocation)
	ADD_OBFIELDALL("Loop",               OB_FIELD_LOOP,              0, CObSounRecord, FieldLoop)
	ADD_OBFIELDALL("Menu Sound",         OB_FIELD_MENUSOUND,         0, CObSounRecord, FieldMenuSound)
	ADD_OBFIELDALL("Ignore Env",         OB_FIELD_IGNOREENVIRONMENT, 0, CObSounRecord, FieldIgnoreEnvironment)
	ADD_OBFIELDALL("2D Sound",           OB_FIELD_2DSOUND,           0, CObSounRecord, Field2DSound)
	ADD_OBFIELDALL("360 LFE",            OB_FIELD_360LFE,            0, CObSounRecord, Field360LFE)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Constructor
 *
 *=========================================================================*/
CObSounRecord::CObSounRecord () {
  m_pSoundFile   = NULL;
  m_pData        = NULL;
}
/*===========================================================================
 *		End of Class CObSounRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSounRecord::Destroy (void) {
  m_pSoundFile = NULL;
  m_pData        = NULL;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObSounRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObSounRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_SNDX);
  if (m_pData != NULL) m_pData->InitializeNew();

  AddNewSubrecord(OB_NAME_FNAM);
  if (m_pSoundFile != NULL) m_pSoundFile->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObSounRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSounRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FNAM) {
   m_pSoundFile = ObCastClass(CObStringSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SNDX) {
   m_pData = ObCastClass(CObSndxSubrecord, pSubrecord);
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObSounRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSounRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pSoundFile == pSubrecord)
    m_pSoundFile = NULL;
  else if (m_pData == pSubrecord)
    m_pData = NULL;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObSounRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSounRecord Method - void SetSoundFile (pString);
 *
 *=========================================================================*/
void CObSounRecord::SetSoundFile (const SSCHAR* pString) {

  if (m_pSoundFile == NULL) {
     AddNewSubrecord(OB_NAME_FNAM);
     if (m_pSoundFile == NULL) return;
     m_pSoundFile->InitializeNew();
  }

  m_pSoundFile->SetString(pString);
}
/*===========================================================================
 *		End of Class Method CObSounRecord::SetSoundFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSounRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObSounRecord::GetFieldSoundFile, String.Format("%s", GetSoundFile()) )
DEFINE_OBGETFIELD(CObSounRecord::GetFieldMinAttenuation, String.Format("%u", GetMinAttenuationUnits()) )
DEFINE_OBGETFIELD(CObSounRecord::GetFieldMaxAttenuation, String.Format("%u", GetMaxAttenuationUnits()) )
DEFINE_OBGETFIELD(CObSounRecord::GetFieldStaticAttenuation, String.Format("%.2f", GetStaticAttenuationDB()) )
DEFINE_OBGETFIELD(CObSounRecord::GetFieldFreqAdjustment, String.Format("%d", (int) GetFreqAdjustment()) )
DEFINE_OBGETFIELD(CObSounRecord::GetFieldRandomFreqShift, String.Format("%s", BooleanToString(IsRandomFreqShift()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetFieldRandomPlay, String.Format("%s", BooleanToString(IsRandomPlay()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetFieldRandomLocation, String.Format("%s", BooleanToString(IsRandomLocation()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetFieldLoop, String.Format("%s", BooleanToString(IsLoop()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetFieldMenuSound, String.Format("%s", BooleanToString(IsMenuSound()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetFieldIgnoreEnvironment, String.Format("%s", BooleanToString(IsIgnoreEnvironment()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetField2DSound, String.Format("%s", BooleanToString(Is2DSound()) ))
DEFINE_OBGETFIELD(CObSounRecord::GetField360LFE, String.Format("%s", BooleanToString(Is360LFE()) ))

BEGIN_OBGETFIELD(CObSounRecord::GetFieldStartTime)
	dword Minutes = GetStartTimeMinutes();
	String.Format("%u:%02u", Minutes / 60 , Minutes % 60);
END_OBGETFIELD()


BEGIN_OBGETFIELD(CObSounRecord::GetFieldStopTime)
	dword Minutes = GetStopTimeMinutes();
	String.Format("%u:%02u", Minutes / 60 , Minutes % 60);
END_OBGETFIELD()
/*===========================================================================
 *		End of CObSounRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSounRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObSounRecord, CompareFieldSoundFile, GetSoundFile)

DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldMinAttenuation, GetMinAttenuation)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldMaxAttenuation, GetMaxAttenuation)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldStaticAttenuation, GetStaticAttenuation)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldFreqAdjustment, GetFreqAdjustment)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldStartTime, GetStartTime)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldStopTime, GetStopTime )

DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldRandomFreqShift, IsRandomFreqShift)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldRandomPlay, IsRandomPlay)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldRandomLocation, IsRandomLocation)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldLoop, IsLoop)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldMenuSound, IsMenuSound)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareFieldIgnoreEnvironment, IsIgnoreEnvironment)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareField2DSound, Is2DSound)
DEFINE_OBCOMPFIELDINT(CObSounRecord, CompareField360LFE, Is360LFE)
/*===========================================================================
 *		End of CObSounRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSounRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObSounRecord::SetFieldSoundFile)
  SetSoundFile(pString);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldMinAttenuation)
  dword Value;
  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetMinAttenuationUnits(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldMaxAttenuation)
  int Value;
  if (!ObFieldConvertInt(pString, Value)) return (false);
  SetMaxAttenuationUnits(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldStaticAttenuation)
  float Value;
  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetStaticAttenuationDB(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldFreqAdjustment)
  dword Value;
  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetFreqAdjustment(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldStartTime)
  const char* pParse = pString;
  dword Minutes = 0;

  while (*pParse != 0) {
    if (*pParse == ':') break;
    ++pParse;
  }

  if (*pParse == ':') {
    ++pParse;
    Minutes = atoi(pString) * 60 + atoi(pParse);
  }
  else {
    Minutes = atoi(pString);
  }
  
  SetStartTimeMinutes(Minutes);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldStopTime)
  const char* pParse = pString;
  dword Minutes = 0;

  while (*pParse != 0) {
    if (*pParse == ':') break;
    ++pParse;
  }

  if (*pParse == ':') {
    ++pParse;
    Minutes = atoi(pString) * 60 + atoi(pParse);
  }
  else {
    Minutes = atoi(pString);
  }
  
  SetStopTimeMinutes(Minutes);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldRandomFreqShift)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetRandomFreqShift(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldRandomLocation)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetRandomLocation(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldRandomPlay)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetRandomPlay(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldLoop)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetLoop(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldMenuSound)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetMenuSound(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetFieldIgnoreEnvironment)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetIgnoreEnvironment(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetField2DSound)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  Set2DSound(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObSounRecord::SetField360LFE)
  bool Value;
  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  Set360LFE(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObSounRecord Set Field Methods
 *=========================================================================*/
