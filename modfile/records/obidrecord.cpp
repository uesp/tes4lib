/*===========================================================================
 *
 * File:	Obidrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obidrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObIdRecord, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_EDID, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObIdRecord, CObRecord)
	ADD_OBFIELDALL("EditorID", OB_FIELD_EDITORID, OBRF_ALNUM, CObIdRecord, FieldEditorID)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObIdRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdRecord Constructor
 *
 *=========================================================================*/
CObIdRecord::CObIdRecord () {
  m_pEditorID = NULL;

 }
/*===========================================================================
 *		End of Class CObIdRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObIdRecord::Destroy (void) {

  m_pEditorID = NULL;

  CObRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObIdRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObIdRecord::InitializeNew (void) {

  CObRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_EDID);
  if (m_pEditorID != NULL) m_pEditorID->InitializeNew();
 }
/*===========================================================================
 *		End of Class Method CObIdRecord::InitializeNew()
 *=========================================================================*/

  
/*===========================================================================
 *
 * Class CObIdRecord Event - void OnAddSubrecord (pSubRecord);
 *
 *=========================================================================*/
void CObIdRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_EDID)
    m_pEditorID = ObCastClass(CObStringSubrecord, pSubrecord);
  else
    CObRecord::OnAddSubrecord(pSubrecord);
  
 }
/*===========================================================================
 *		End of Class Event CObIdRecord::OnAddSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObIdRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pEditorID == pSubrecord)
    m_pEditorID = NULL;
  else
    CObRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObIdRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdRecord Method - void SetEditorID (pString);
 *
 *=========================================================================*/
void CObIdRecord::SetEditorID (const SSCHAR* pString) {

	/* Ensure the subrecord exists */
  if (m_pEditorID == NULL) {
    AddNewSubrecord(OB_NAME_EDID);
    if (m_pEditorID == NULL) return;
   }

  m_pEditorID->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObIdRecord::SetEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdRecord Get Field Methods
 *
 *=========================================================================*/
BEGIN_OBGETFIELD(CObIdRecord::GetFieldEditorID)
	const SSCHAR* pString = GetEditorID();
	if (pString != NULL) String.Format("%s", pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObEnchRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObIdRecord, CompareFieldEditorID, GetEditorID)
/*===========================================================================
 *		End of CObIdRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObIdRecord::SetFieldEditorID)
  AddObGeneralError("Cannot set the editorID of a record from its SetField method!");
  return (false);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObIdRecord Set Field Methods
 *=========================================================================*/
