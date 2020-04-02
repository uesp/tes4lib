/*===========================================================================
 *
 * File:	ObFlorRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObFlorRecord class for flora records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obflorrecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObFlorRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_PFIG, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_PFPC, CObPfpcSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObFlorRecord, CObItem1Record)
	ADD_OBFIELDALL("Ingrediant",   OB_FIELD_INGREDIANT,   0, CObFlorRecord, FieldIngrediant)
	ADD_OBFIELDALL("IngrediantID", OB_FIELD_INGREDIANTID, 0, CObFlorRecord, FieldIngrediantID)
	ADD_OBFIELDALL("Spring",       OB_FIELD_SPRING,       0, CObFlorRecord, FieldSpring)
	ADD_OBFIELDALL("Summer",       OB_FIELD_SUMMER,       0, CObFlorRecord, FieldSummer)
	ADD_OBFIELDALL("Fall",         OB_FIELD_FALL,         0, CObFlorRecord, FieldFall)
	ADD_OBFIELDALL("Winter",       OB_FIELD_WINTER,       0, CObFlorRecord, FieldWinter)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObFlorRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Constructor
 *
 *=========================================================================*/
CObFlorRecord::CObFlorRecord () {
  m_pData       = NULL;
  m_pIngrediant = NULL;
}
/*===========================================================================
 *		End of Class CObFlorRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObFlorRecord::Destroy (void) {
  m_pData       = NULL;
  m_pIngrediant = NULL;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObFlorRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObFlorRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_PFPC);
  if (m_pData != NULL) m_pData->InitializeNew();

  AddNewSubrecord(OB_NAME_PFIG);
  if (m_pIngrediant != NULL) m_pIngrediant->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObFlorRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFlorRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_PFPC) {
    m_pData = ObCastClass(CObPfpcSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_PFIG) {
    m_pIngrediant = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObFlorRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFlorRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord == m_pData) {  
    m_pData = NULL;
  }
  else if (pSubrecord == m_pIngrediant) {  
    m_pIngrediant = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObFlorRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFlorRecord Method - void SetIngrediant (Value);
 *
 *=========================================================================*/
void CObFlorRecord::SetIngrediant (const obformid_t Value) {

  if (m_pIngrediant == NULL) {
     AddNewSubrecord(OB_NAME_PFIG);
     if (m_pIngrediant == NULL) return;
     m_pIngrediant->InitializeNew();
   }

  m_pIngrediant->SetValue(Value);
}
/*===========================================================================
 *		End of Class Method CObFlorRecord::SetIngrediant()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObFlorRecord::GetFieldSpring, String.Format("%u", (dword) GetSpring()))
DEFINE_OBGETFIELD(CObFlorRecord::GetFieldSummer, String.Format("%u", (dword) GetSummer()))
DEFINE_OBGETFIELD(CObFlorRecord::GetFieldFall,   String.Format("%u", (dword) GetFall()))
DEFINE_OBGETFIELD(CObFlorRecord::GetFieldWinter, String.Format("%u", (dword) GetWinter()))
DEFINE_OBGETFIELD(CObFlorRecord::GetFieldIngrediantID, GetIngrediant() ? String.Format("0x%08X", GetIngrediant()) : String.Empty())

BEGIN_OBGETFIELD(CObFlorRecord::GetFieldIngrediant)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetIngrediant());
        String.Format("0x%08X", GetIngrediant());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObFlorRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldSpring, GetSpring)
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldSummer, GetSummer)
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldFall,   GetFall)
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldWinter, GetWinter)
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldIngrediant,   GetIngrediant)
DEFINE_OBCOMPFIELDDWORD(CObFlorRecord, CompareFieldIngrediantID, GetIngrediant)
/*===========================================================================
 *		End of CObFlorRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFlorRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObFlorRecord::SetFieldSpring)
  byte Value;
  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetSpring(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObFlorRecord::SetFieldSummer)
  byte Value;
  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetSummer(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObFlorRecord::SetFieldFall)
  byte Value;
  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetFall(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObFlorRecord::SetFieldWinter)
  byte Value;
  if (!ObFieldConvertByte(pString, Value)) return (false);
  SetWinter(Value);
END_OBSETFIELD()

BEGIN_OBSETFIELD(CObFlorRecord::SetFieldIngrediantID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetIngrediant(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObFlorRecord::SetFieldIngrediant)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetIngrediant(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The ingrediant '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_INGR) return AddObGeneralError("The record '%s' is not an ingrediant (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetIngrediant(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the ingrediant '%s'!", pString);
  }

END_OBSETFIELD()
/*===========================================================================
 *		End of CObFlorRecord Set Field Methods
 *=========================================================================*/

