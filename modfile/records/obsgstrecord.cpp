/*===========================================================================
 *
 * File:	ObSgstrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obsgstrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObSgstRecord, CObEffectItemRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObSgstDataSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObSgstRecord, CObEffectItemRecord)
	ADD_OBFIELDALL("Uses",   OB_FIELD_USES,   0, CObSgstRecord, FieldUses)
	ADD_OBFIELDALL("Weight", OB_FIELD_WEIGHT, 0, CObSgstRecord, FieldWeight)
	ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,  0, CObSgstRecord, FieldValue)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstRecord Constructor
 *
 *=========================================================================*/
CObSgstRecord::CObSgstRecord () {
  m_pSigilData    = NULL;
 }
/*===========================================================================
 *		End of Class CObIngrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSgstRecord::Destroy (void) {
  m_pSigilData    = NULL;

  CObEffectItemRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObSgstRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstRecord Method - void InitializeNew (void);
 *
 * Initialize a new sigil stone record.
 *
 *=========================================================================*/
void CObSgstRecord::InitializeNew (void) {

  CObEffectItemRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pSigilData != NULL) m_pSigilData->InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObSgstRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSgstRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pSigilData = ObCastClass(CObSgstDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 9, OB_NAME_DATA);
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
 *		End of Class Event CObSgstRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSgstRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObSgstRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pSigilData == pSubrecord)
    m_pSigilData = NULL;
  else
    CObEffectItemRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObSgstRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSgstRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObSgstRecord::GetFieldUses,   String.Format("%u",   GetUses()))
DEFINE_OBGETFIELD(CObSgstRecord::GetFieldValue,  String.Format("%u",   GetValue()))
DEFINE_OBGETFIELD(CObSgstRecord::GetFieldWeight, String.Format(OB_FORMATSTR_WEIGHT, GetWeight()))
/*===========================================================================
 *		End of CObScptRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSgstRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObSgstRecord, CompareFieldUses, GetUses)
DEFINE_OBCOMPFIELDDWORD(CObSgstRecord, CompareFieldValue, GetValue)
DEFINE_OBCOMPFIELDFLOAT(CObSgstRecord, CompareFieldWeight, GetWeight, 100.0f)
/*===========================================================================
 *		End of CObScptRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObSgstRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObSgstRecord::SetFieldUses)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetUses(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSgstRecord::SetFieldValue)
  dword Value;

  if (!ObFieldConvertDword(pString, Value)) return (false);
  SetValue(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObSgstRecord::SetFieldWeight)
  float fValue;

  if (!ObFieldConvertFloat(pString, fValue)) return (false);
  SetWeight(fValue);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObSgstRecord Set Field Methods
 *=========================================================================*/
