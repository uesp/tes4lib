/*===========================================================================
 *
 * File:	Obitem1record.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Implements the CObItem1Record class for inventory type records with:
 *
 *	FULL - Item Name
 *	MODL - Model filename
 *	ICON - Icon filename
 *	SCRI - Script
 *
 *=========================================================================*/

	/* Include Files */
#include "obitem1record.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObItem1Record, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MODL, CObModlSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ICON, CObIconSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRI, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObItem1Record, CObIdRecord)
	ADD_OBFIELDALL("Item Name", OB_FIELD_ITEMNAME, 0, CObItem1Record, FieldItemName)
	ADD_OBFIELDALL("Model",     OB_FIELD_MODEL,    0, CObItem1Record, FieldModel)
	ADD_OBFIELDALL("Icon",      OB_FIELD_ICON,     0, CObItem1Record, FieldIcon)
	ADD_OBFIELDALL("Script",    OB_FIELD_SCRIPT,   0, CObItem1Record, FieldScript)
	ADD_OBFIELDALL("ScriptID",  OB_FIELD_SCRIPTID, 0, CObItem1Record, FieldScriptID)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Constructor
 *
 *=========================================================================*/
CObItem1Record::CObItem1Record () {
  m_pItemName   = NULL;
  m_pModel      = NULL;
  m_pIcon       = NULL;
  m_pScript     = NULL;
 }
/*===========================================================================
 *		End of Class CObItem1Record Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void Destroy (void);
 *
 *=========================================================================*/
void CObItem1Record::Destroy (void) {
  m_pItemName = NULL;
  m_pModel    = NULL;
  m_pIcon     = NULL;
  m_pScript   = NULL;

  CObIdRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObItem1Record::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObItem1Record::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

	/* Create a new item name subrecords if required */
  if (HasFullItemName()) {
    AddNewSubrecord(OB_NAME_FULL);
    if (m_pItemName != NULL) m_pItemName->InitializeNew();
   }

 }
/*===========================================================================
 *		End of Class Method CObItem1Record::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObItem1Record::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FULL)
   m_pItemName = ObCastClass(CObFullSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_MODL)
    m_pModel = ObCastClass(CObModlSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_ICON)
    m_pIcon = ObCastClass(CObIconSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_SCRI) {
    m_pScript = ObCastClass(CObFormidSubrecord, pSubrecord);
    //TEST_INTVALUE(pSubrecord->GetRecordSize(), 0x04);
   }
  else
    CObIdRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObItem1Record::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObItem1Record::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pItemName == pSubrecord)
    m_pItemName = NULL;
  else if (m_pModel == pSubrecord)
    m_pModel = NULL;
  else if (m_pIcon == pSubrecord)
    m_pIcon = NULL;
  else if (m_pScript == pSubrecord)
    m_pScript = NULL;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObItem1Record::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void SetItemName (pString);
 *
 *=========================================================================*/
void CObItem1Record::SetItemName (const SSCHAR* pString) {

  if (m_pItemName == NULL) {
     AddNewSubrecord(OB_NAME_FULL);
     if (m_pItemName == NULL) return;
     m_pItemName->InitializeNew();
   }

  m_pItemName->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObItem1Record::SetItemName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void SetModel (pString);
 *
 *=========================================================================*/
void CObItem1Record::SetModel (const SSCHAR* pString) {

  if (m_pModel == NULL) {
     AddNewSubrecord(OB_NAME_MODL);
     if (m_pModel == NULL) return;
     m_pModel->InitializeNew();
   }

  m_pModel->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObItem1Record::SetModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void SetIcon (pString);
 *
 *=========================================================================*/
void CObItem1Record::SetIcon (const SSCHAR* pString) {

  if (m_pIcon == NULL) {
     AddNewSubrecord(OB_NAME_ICON);
     if (m_pIcon == NULL) return;
     m_pIcon->InitializeNew();
   }

  m_pIcon->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObItem1Record::SetIcon()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObItem1Record Method - void SetScript (FormID);
 *
 *=========================================================================*/
void CObItem1Record::SetScript (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL) {
    DeleteSubrecords(OB_NAME_SCRI);
    return;
  }

  if (m_pScript == NULL) {
     AddNewSubrecord(OB_NAME_SCRI);
     if (m_pScript == NULL) return;
     m_pScript->InitializeNew();
   }

  m_pScript->SetValue(FormID);
 }
/*===========================================================================
 *		End of Class Method CObItem1Record::SetScript()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem1Record Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObItem1Record::GetFieldItemName, String.Format("%s", GetItemName()))
DEFINE_OBGETFIELD(CObItem1Record::GetFieldModel,    String.Format("%s", GetModel()))
DEFINE_OBGETFIELD(CObItem1Record::GetFieldIcon,     String.Format("%s", GetIcon()))
DEFINE_OBGETFIELD(CObItem1Record::GetFieldScriptID, GetScript() ? String.Format("0x%08X", GetScript()) : String.Empty())

BEGIN_OBGETFIELD(CObItem1Record::GetFieldScript)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetScript());
        String.Format("0x%08X", GetScript());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObItem1Record Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem1Record Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObItem1Record, CompareFieldItemName, GetItemName)
DEFINE_OBCOMPFIELDSTRING(CObItem1Record, CompareFieldModel, GetModel)
DEFINE_OBCOMPFIELDSTRING(CObItem1Record, CompareFieldIcon, GetIcon)
DEFINE_OBCOMPFIELDEDITORID(CObItem1Record, CompareFieldScript, GetScript)
DEFINE_OBCOMPFIELDDWORD(CObItem1Record, CompareFieldScriptID, GetScript)
/*===========================================================================
 *		End of CObItem1Record Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObItem1Record Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObItem1Record::SetFieldItemName)
  SetItemName(pString);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem1Record::SetFieldModel)
  SetModel(pString);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem1Record::SetFieldIcon)
  SetIcon(pString);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem1Record::SetFieldScriptID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetScript(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObItem1Record::SetFieldScript)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetScript(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The script '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SCPT) return AddObGeneralError("The record '%s' is not a script (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetScript(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the script '%s'!", pString);
  }

END_OBSETFIELD()
/*===========================================================================
 *		End of CObRecord Set Field Methods
 *=========================================================================*/
