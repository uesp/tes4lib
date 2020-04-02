/*===========================================================================
 *
 * File:	ObSlgmRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obslgmrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObSlgmRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObSlgmDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SOUL, CObByteSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SLCP, CObByteSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObSlgmRecord, CObItem1Record)
	ADD_OBFIELDALL("Value",    OB_FIELD_VALUE,    0, CObSlgmRecord, FieldValue)
	ADD_OBFIELDALL("Weight",   OB_FIELD_WEIGHT,   0, CObSlgmRecord, FieldWeight)
	ADD_OBFIELDALL("Soul",     OB_FIELD_SOUL,     0, CObSlgmRecord, FieldSoul)
	ADD_OBFIELDALL("Capacity", OB_FIELD_CAPACITY, 0, CObSlgmRecord, FieldCapacity)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmRecord Constructor
 *
 *=========================================================================*/
CObSlgmRecord::CObSlgmRecord () {
  m_pSoulGemData = NULL;
  m_pCapacity    = NULL;
  m_pSoul        = NULL;
} 
/*===========================================================================
 *		End of Class CObSlgmRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSlgmRecord::Destroy (void) {
  m_pSoulGemData = NULL;
  m_pCapacity    = NULL;
  m_pSoul        = NULL;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObSlgmRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObSlgmRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pSoulGemData != NULL) m_pSoulGemData->InitializeNew();

  AddNewSubrecord(OB_NAME_SOUL);
  if (m_pSoul != NULL) m_pSoul->InitializeNew();

  AddNewSubrecord(OB_NAME_SLCP);

  if (m_pCapacity != NULL) {
    m_pCapacity->InitializeNew();
    m_pCapacity->SetValue(1);
  }

}
/*===========================================================================
 *		End of Class Method CObSlgmRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSlgmRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pSoulGemData = ObCastClass(CObSlgmDataSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SOUL) {
    m_pSoul = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_SLCP) {
    m_pCapacity = ObCastClass(CObByteSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObSlgmRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSlgmRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSlgmRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pSoulGemData == pSubrecord)
    m_pSoulGemData = NULL;
  else if (m_pSoul == pSubrecord)
    m_pSoul = NULL;
  else if (m_pCapacity == pSubrecord)
    m_pCapacity = NULL;
  else
    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObSlgmRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSlgmRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObSlgmRecord::GetFieldValue,    String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObSlgmRecord::GetFieldWeight,   String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
DEFINE_OBGETFIELD(CObSlgmRecord::GetFieldSoul,     String.Format("%s", GetObSoulGemString(GetSoul())))
DEFINE_OBGETFIELD(CObSlgmRecord::GetFieldCapacity, String.Format("%s", GetObSoulGemString(GetCapacity())))
/*===========================================================================
 *		End of CObSlgmRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSlgmRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObSlgmRecord, CompareFieldValue,    GetValue)
DEFINE_OBCOMPFIELDFLOAT(CObSlgmRecord, CompareFieldWeight,   GetWeight, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObSlgmRecord, CompareFieldSoul,     GetSoul)
DEFINE_OBCOMPFIELDDWORD(CObSlgmRecord, CompareFieldCapacity, GetCapacity)
/*===========================================================================
 *		End of CObSlgmRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSlgmRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObSlgmRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSlgmRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSlgmRecord::SetFieldSoul)
  int Value;

  if (!GetObSoulGemValue(Value, pString)) return (false);
  SetSoul(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSlgmRecord::SetFieldCapacity)
  int Value;

  if (!GetObSoulGemValue(Value, pString)) return (false);
  SetCapacity(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObSlgmRecord Set Field Methods
 *=========================================================================*/
