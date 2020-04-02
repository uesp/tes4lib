/*===========================================================================
 *
 * File:	Obspelrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obspelrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObSpelRecord, CObEffectItemRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SPIT, CObSpitSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObSpelRecord, CObEffectItemRecord)
	ADD_OBFIELDALL("Cost",              OB_FIELD_COST,          0, CObSpelRecord, FieldCost)
	ADD_OBFIELDALL("Type",              OB_FIELD_TYPE,          0, CObSpelRecord, FieldType)
	ADD_OBFIELDALL("Level",             OB_FIELD_LEVEL,         0, CObSpelRecord, FieldLevel)
	ADD_OBFIELDALL("AutoCalc",          OB_FIELD_AUTOCALC,	    0, CObSpelRecord, FieldAutoCalc)
	ADD_OBFIELDALL("PlayerStart",       OB_FIELD_PLAYERSTART,   0, CObSpelRecord, FieldPlayerStart)
	ADD_OBFIELDALL("SilenceImmune",     OB_FIELD_SILENCEIMMUNE, 0, CObSpelRecord, FieldSilenceImmune)
	ADD_OBFIELDALL("IgnoreLOS",         OB_FIELD_IGNORELOS,     0, CObSpelRecord, FieldIgnoreLOS)
	ADD_OBFIELDALL("AlwaysApplyScript", OB_FIELD_ALWAYSAPPLY,   0, CObSpelRecord, FieldAlwaysApplyScript)
	ADD_OBFIELDALL("AbsorbReflect",     OB_FIELD_ABSORBREFLECT, 0, CObSpelRecord, FieldAbsorbReflect)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpelRecord Constructor
 *
 *=========================================================================*/
CObSpelRecord::CObSpelRecord () {
  m_pSpellData = NULL;
 }
/*===========================================================================
 *		End of Class CObSpelRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpelRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSpelRecord::Destroy (void) {
  m_pSpellData = NULL;

  CObEffectItemRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObSpelRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpelRecord Method - void InitializeNew (void);
 *
 * Initialize a new spell record.
 *
 *=========================================================================*/
void CObSpelRecord::InitializeNew (void) {

  CObEffectItemRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_SPIT);
  if (m_pSpellData != NULL) m_pSpellData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObSpelRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpelRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSpelRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_SPIT) {
    m_pSpellData = ObCastClass(CObSpitSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), OBSPIT_SUBRECORD_SIZE, OB_NAME_SPIT);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 24, OB_NAME_MODT);
   }
  else
    CObEffectItemRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObSpelRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpelRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSpelRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pSpellData == pSubrecord)
    m_pSpellData = NULL;
  else
    CObEffectItemRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObSpelRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSpelRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldCost,              String.Format("%u", GetCost()))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldType,              String.Format("%s", GetObSpellTypeString(GetType()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldLevel,             String.Format("%s", GetObSpellLevelString(GetLevel()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldAutoCalc,          String.Format("%s", BooleanToString(IsAutoCalc()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldPlayerStart,       String.Format("%s", BooleanToString(IsPlayerStart()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldSilenceImmune,     String.Format("%s", BooleanToString(IsSilenceImmune()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldIgnoreLOS,         String.Format("%s", BooleanToString(IsIgnoreLOS()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldAlwaysApplyScript, String.Format("%s", BooleanToString(IsAlwaysApplyScript()) ))
DEFINE_OBGETFIELD(CObSpelRecord::GetFieldAbsorbReflect,     String.Format("%s", BooleanToString(IsAbsorbReflect()) ))
/*===========================================================================
 *		End of CObScptRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSpelRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObSpelRecord, CompareFieldCost, GetCost)
DEFINE_OBCOMPFIELDDWORD(CObSpelRecord, CompareFieldType, GetType)
DEFINE_OBCOMPFIELDDWORD(CObSpelRecord, CompareFieldLevel, GetLevel)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldAutoCalc, IsAutoCalc)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldPlayerStart, IsPlayerStart)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldSilenceImmune, IsSilenceImmune)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldIgnoreLOS, IsIgnoreLOS)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldAlwaysApplyScript, IsAlwaysApplyScript)
DEFINE_OBCOMPFIELDINT(CObSpelRecord, CompareFieldAbsorbReflect, IsAbsorbReflect)
/*===========================================================================
 *		End of CObScptRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSpelRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObSpelRecord::SetFieldCost)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetCost(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldType)
  int Value;

  if (!GetObSpellTypeValue(Value, pString)) return (false);
  SetType(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldLevel)
  int Value;

  if (!GetObSpellLevelValue(Value, pString)) return (false);
  SetLevel(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldAutoCalc)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAutoCalc(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldPlayerStart)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetPlayerStart(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldSilenceImmune)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetSilenceImmune(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldIgnoreLOS)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetIgnoreLOS(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldAlwaysApplyScript)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAlwaysApplyScript(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSpelRecord::SetFieldAbsorbReflect)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetAbsorbReflect(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObSpelRecord Set Field Methods
 *=========================================================================*/

