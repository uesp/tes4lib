/*===========================================================================
 *
 * File:	ObBsgnRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	10 September, 2006
 *
 * Implements the ObBsgnRecord class for birth sign type records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obbsgnrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObBsgnRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SPLO, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ICON, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DESC, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBsgnRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObBsgnRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObBsgnRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObBsgnRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Constructor
 *
 *=========================================================================*/
CObBsgnRecord::CObBsgnRecord () {
  m_pFullName = NULL;
}
/*===========================================================================
 *		End of Class CObBsgnRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBsgnRecord::Destroy (void) {
  m_pFullName = NULL;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObBsgnRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObBsgnRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_FULL);
  if (m_pFullName != NULL) m_pFullName->InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObBsgnRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBsgnRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    m_pFullName = ObCastClass(CObFullSubrecord, pSubrecord);
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

 }
/*===========================================================================
 *		End of Class Event CObBsgnRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBsgnRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pFullName == pSubrecord) {
    m_pFullName = NULL;
  }
  else {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObBsgnRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsgnRecord Method - void SetFullName (pString);
 *
 *=========================================================================*/
void CObBsgnRecord::SetFullName (const SSCHAR* pString) {

  if (m_pFullName == NULL) {
     AddNewSubrecord(OB_NAME_FULL);
     if (m_pFullName == NULL) return;
     m_pFullName->InitializeNew();
   }

  m_pFullName->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObBsgnRecord::SetFullName()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBsgnRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObBsgnRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBsgnRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObBsgnRecord Set Field Methods
 *=========================================================================*/

