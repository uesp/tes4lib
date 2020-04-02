/*===========================================================================
 *
 * File:	ObCellRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Implements the CObCellRecord class for cell records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obcellrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObCellRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XOWN, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XGLB, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XRNK, CObLongSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XCCM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XCWT, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XCLW, CObFloatSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XCLR, CObFormidArraySubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRefrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObCellRecord, CObIdRecord)
	ADD_OBFIELDALL("Cell Name", OB_FIELD_FULLNAME, 0, CObCellRecord, FieldCellName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRefrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Constructor
 *
 *=========================================================================*/
CObCellRecord::CObCellRecord () {
  m_pCellName   = NULL;
 }
/*===========================================================================
 *		End of Class CObCellRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObCellRecord::Destroy (void) {
  m_pCellName   = NULL;

  CObIdRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObCellRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObCellRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

	/* Create a new item name subrecords if required */
  if (HasFullItemName()) {
    AddNewSubrecord(OB_NAME_FULL);
    if (m_pCellName != NULL) m_pCellName->InitializeNew();
  }

}
/*===========================================================================
 *		End of Class Method CObCellRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObCellRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    m_pCellName = ObCastClass(CObFullSubrecord, pSubrecord);
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObCellRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObCellRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pCellName == pSubrecord) {
    m_pCellName = NULL;
  }
  else {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObCellRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCellRecord Method - void SetCellName (pString);
 *
 *=========================================================================*/
void CObCellRecord::SetCellName (const SSCHAR* pString) {

  if (m_pCellName == NULL) {
     AddNewSubrecord(OB_NAME_FULL);
     if (m_pCellName == NULL) return;
     m_pCellName->InitializeNew();
   }

  m_pCellName->SetString(pString);
 }
/*===========================================================================
 *		End of Class Method CObCellRecord::SetCellName()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCellRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObCellRecord::GetFieldCellName, String.Format("%s", GetCellName()))
/*===========================================================================
 *		End of CObCellRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCellRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObCellRecord, CompareFieldCellName, GetCellName)
/*===========================================================================
 *		End of CObCellRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCellRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObCellRecord::SetFieldCellName)
  SetCellName(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObCellRecord Field Methods
 *=========================================================================*/

