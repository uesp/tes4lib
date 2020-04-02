/*===========================================================================
 *
 * File:	Obbookecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbookrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObBookRecord, CObItem2Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObBookDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DESC, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObBookRecord, CObItem2Record)
	ADD_OBFIELDALL("Weight",    OB_FIELD_WEIGHT,	0, CObBookRecord, FieldWeight)
	ADD_OBFIELDALL("Value",     OB_FIELD_VALUE,	0, CObBookRecord, FieldValue)
	ADD_OBFIELDALL("Teaches",   OB_FIELD_TEACHES,	0, CObBookRecord, FieldTeaches)
	ADD_OBFIELDALL("NoTake",    OB_FIELD_NOTAKE,	0, CObBookRecord, FieldNoTake)
	ADD_OBFIELDALL("Scroll",    OB_FIELD_SCROLL,	0, CObBookRecord, FieldIsScroll)
	ADD_OBFIELDALL("Text",      OB_FIELD_TEXT,	0, CObBookRecord, FieldBookText)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Constructor
 *
 *=========================================================================*/
CObBookRecord::CObBookRecord () {
  m_pBookData = NULL;
  m_pText     = NULL;
 }
/*===========================================================================
 *		End of Class CObBookRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBookRecord::Destroy (void) {
  m_pBookData = NULL;
  m_pText     = NULL;

  CObItem2Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObBookRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObBookRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem2Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pBookData != NULL) m_pBookData->InitializeNew();

  AddNewSubrecord(OB_NAME_DESC);
  if (m_pText != NULL) m_pText->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObBookRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBookRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pBookData = ObCastClass(CObBookDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pBookData->GetRecordSize(), 10, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_DESC) {
    m_pText = ObCastClass(CObStringSubrecord, pSubrecord);
    //TEST_INTVALUE(pSubrecord->GetRecordSize(), 0x04);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_DESC);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 48, OB_NAME_MODT);
    //TEST_2INTVALUE1(pSubrecord->GetRecordSize(), 24, 48, OB_NAME_MODT);
   }
  else
    CObItem2Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObBookRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBookRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pBookData == pSubrecord) {
    m_pBookData = NULL;
  }
  else if (m_pBookData == pSubrecord) {
    m_pText = NULL;
  }
  else {
    CObItem2Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObBookRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBookRecord Method - void SetBookText (pString);
 *
 *=========================================================================*/
void CObBookRecord::SetBookText (const SSCHAR* pString) {

  if (m_pText == NULL) {
     AddNewSubrecord(OB_NAME_DESC);
     if (m_pText == NULL) return;
     m_pText->InitializeNew();
   }

  m_pText->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObBookRecord::SetBookText()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBookRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObBookRecord::GetFieldWeight,   String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObBookRecord::GetFieldValue,    String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObBookRecord::GetFieldTeaches,  String.Format("%s",   GetObSkillString(GetTeaches()) ))
DEFINE_OBGETFIELD(CObBookRecord::GetFieldNoTake,   String.Format("%s",   BooleanToString(IsNoTake()) ))
DEFINE_OBGETFIELD(CObBookRecord::GetFieldIsScroll, String.Format("%s",   BooleanToString(IsScroll()) ))
DEFINE_OBGETFIELD(CObBookRecord::GetFieldBookText, String = GetBookText() )
/*===========================================================================
 *		End of CObBookRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBookRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDFLOAT(CObBookRecord, CompareFieldWeight, GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObBookRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDINT(CObBookRecord, CompareFieldTeaches, GetTeaches)
DEFINE_OBCOMPFIELDINT(CObBookRecord, CompareFieldNoTake, IsNoTake)
DEFINE_OBCOMPFIELDINT(CObBookRecord, CompareFieldIsScroll, IsScroll)
DEFINE_OBCOMPFIELDSTRING(CObBookRecord, CompareFieldBookText, GetBookText)
/*===========================================================================
 *		End of CObBookRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBookRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObBookRecord::SetFieldWeight)
  float Value;

  if (!ObFieldConvertFloat(pString, Value)) return (false);
  SetWeight(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObBookRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObBookRecord::SetFieldTeaches)
  int Value;

  if (!GetObSkillValue(Value, pString)) {
    AddObGeneralError("The string '%s' is not a valid teaches skill!", pString);
    return (false);
  }
  
  SetTeaches(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObBookRecord::SetFieldNoTake)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetNoTake(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObBookRecord::SetFieldIsScroll)
  bool Value;

  if (!ObFieldConvertBoolean(pString, Value)) return (false);
  SetIsScroll(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObBookRecord::SetFieldBookText)
  SetBookText(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObRecord Field Methods
 *=========================================================================*/
