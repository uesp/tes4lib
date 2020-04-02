/*===========================================================================
 *
 * File:	Obitem1record.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObItem2Record class for records with:
 *
 *	ANAM - Enchantment pts
 *	ENAM - Enchantment formid
 *
 * In addition to all standard CObItem1Record subrecords.
 *
 *=========================================================================*/

	/* Include Files */
#include "obitem2record.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObItem2Record, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ANAM, CObWordSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObItem2Record, CObItem1Record)
	ADD_OBFIELDALL("Enchant Pts", OB_FIELD_ENCHANTPOINTS,	       0, CObItem2Record, FieldEnchantPoints)
	ADD_OBFIELDALL("Enchantment", OB_FIELD_ENCHANTMENT,            0, CObItem2Record, FieldEnchantment)
	ADD_OBFIELDALL("EnchantID",   OB_FIELD_ENCHANTMENTID, OBRF_NOCSV, CObItem2Record, FieldEnchantmentID)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Constructor
 *
 *=========================================================================*/
CObItem2Record::CObItem2Record () {
  m_pEnchantment   = NULL;
  m_pEnchantPoints = NULL;
 }
/*===========================================================================
 *		End of Class CObItem2Record Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Method - void Destroy (void);
 *
 *=========================================================================*/
void CObItem2Record::Destroy (void) {
  m_pEnchantment   = NULL;
  m_pEnchantPoints = NULL;

  m_CachedEnchantID.Empty();

  CObItem1Record::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObItem2Record::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Method - const SSCHAR* GetEnchantEditorID (void);
 *
 * TODO:
 *
 *=========================================================================*/
const SSCHAR* CObItem2Record::GetEnchantEditorID (void) {

  if (!m_CachedEnchantID.IsEmpty()) return m_CachedEnchantID;
  return m_CachedEnchantID;
 }
/*===========================================================================
 *		End of Class Method SSCHAR* CObItem2Record::GetEnchantEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObItem2Record::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

 }
/*===========================================================================
 *		End of Class Method CObItem2Record::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObItem2Record::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_ENAM)
    m_pEnchantment = ObCastClass(CObFormidSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_ANAM)
    m_pEnchantPoints = ObCastClass(CObWordSubrecord, pSubrecord);
  else
    CObItem1Record::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObItem2Record::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObItem2Record::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pEnchantment == pSubrecord)
    m_pEnchantment = NULL;
  else if (m_pEnchantPoints == pSubrecord)
    m_pEnchantPoints = NULL;
  else
    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObItem2Record::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Method - void SetEnchantment (FormID);
 *
 *=========================================================================*/
void CObItem2Record::SetEnchantment (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL && m_pEnchantment != NULL) {
    DeleteSubrecords(OB_NAME_ENAM);
    m_pEnchantment = NULL;
    return;
  }

  if (m_pEnchantment == NULL) {
     AddNewSubrecord(OB_NAME_ENAM);
     if (m_pEnchantment == NULL) return;
     m_pEnchantment->InitializeNew();
   }

  m_pEnchantment->SetValue(FormID);
 } 
/*===========================================================================
 *		End of Class Method CObItem2Record::SetEnchantment()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem2Record Method - void SetEnchantPoints (Points);
 *
 *=========================================================================*/
void CObItem2Record::SetEnchantPoints (const word Points) {

  if (m_pEnchantPoints == NULL) {
     AddNewSubrecord(OB_NAME_ANAM);
     if (m_pEnchantPoints == NULL) return;
     m_pEnchantPoints->InitializeNew();
   }

  m_pEnchantPoints->SetValue(Points);
 } 
/*===========================================================================
 *		End of Class Method CObItem2Record::SetEnchantPoints()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem2Record Get Field Methods
 *
 *=========================================================================*/
BEGIN_OBGETFIELD(CObItem2Record::GetFieldEnchantment)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetEnchantment());
        String.Format("0x%08X", GetEnchantment());
END_OBGETFIELD()

DEFINE_OBGETFIELD(CObItem2Record::GetFieldEnchantmentID, GetEnchantment() ? String.Format("0x%08X", GetEnchantment()) : String.Empty() )
DEFINE_OBGETFIELD(CObItem2Record::GetFieldEnchantPoints, String.Format("%u", (dword) GetEnchantPoints()))
/*===========================================================================
 *		End of CObItem2Record Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem2Record Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDEDITORID(CObItem2Record, CompareFieldEnchantment, GetEnchantment)
DEFINE_OBCOMPFIELDDWORD(CObItem2Record, CompareFieldEnchantmentID, GetEnchantment)
DEFINE_OBCOMPFIELDDWORD(CObItem2Record, CompareFieldEnchantPoints, GetEnchantPoints)
/*===========================================================================
 *		End of CObItem2Record Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem2Record Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObItem2Record::SetFieldEnchantment)
  CObIdRecord* pIdRecord = NULL;

  if (m_pParent != NULL) {
   
    if (pString == NULL || *pString == NULL_CHAR) {
      SetEnchantment(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The enchantment '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_ENCH) return AddObGeneralError("The record '%s' is not an enchantment (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetEnchantment(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the enchantment '%s'!", pString);
  }

END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem2Record::SetFieldEnchantPoints)
  word Value;

  if (!ObFieldConvertWord(pString, Value)) return (false);
  SetEnchantPoints(Value);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem2Record::SetFieldEnchantmentID)
	obformid_t FormID;
	if (!ObFieldConvertDword(pString, FormID)) return (false);
	SetEnchantment(FormID);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObItem2Record Field Methods
 *=========================================================================*/
