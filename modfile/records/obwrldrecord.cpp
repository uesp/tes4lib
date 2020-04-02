/*===========================================================================
 *
 * File:	ObWlrdRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Implements the CObWrldRecord class for worldspace records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obwrldrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObWrldRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_NAM2, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_WNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWrldRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObWrldRecord, CObIdRecord)
	ADD_OBFIELDALL("Full Name",	 OB_FIELD_FULLNAME,	  0, CObWrldRecord, FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRefrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Constructor
 *
 *=========================================================================*/
CObWrldRecord::CObWrldRecord () {
  m_pFullName   = NULL;
 }
/*===========================================================================
 *		End of Class CObCellRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObWrldRecord::Destroy (void) {
  m_pFullName   = NULL;

  CObIdRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObWrldRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObWrldRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

	/* Create a new item name subrecords if required */
  if (HasFullItemName()) {
    AddNewSubrecord(OB_NAME_FULL);
    if (m_pFullName != NULL) m_pFullName->InitializeNew();
   }

 }
/*===========================================================================
 *		End of Class Method CObWrldRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWrldRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    m_pFullName = ObCastClass(CObFullSubrecord, pSubrecord);
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

 }
/*===========================================================================
 *		End of Class Event CObWrldRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWrldRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pFullName == pSubrecord) {
    m_pFullName = NULL;
  }
  else {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObWrldRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWrldRecord Method - void SetFullName (pString);
 *
 *=========================================================================*/
void CObWrldRecord::SetFullName (const SSCHAR* pString) {

  if (m_pFullName == NULL) {
     AddNewSubrecord(OB_NAME_FULL);
     if (m_pFullName == NULL) return;
     m_pFullName->InitializeNew();
   }

  m_pFullName->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObWrldRecord::SetCellName()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWrldRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObWrldRecord::GetFieldFullName, String.Format("%s", GetFullName()))
/*===========================================================================
 *		End of CObWrldRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWrldRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObWrldRecord, CompareFieldFullName, GetFullName)
/*===========================================================================
 *		End of CObWrldRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWrldRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObWrldRecord::SetFieldFullName)
  SetFullName(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObWrldRecord Field Methods
 *=========================================================================*/


