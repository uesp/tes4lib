/*===========================================================================
 *
 * File:	ObMgefRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObMgefRecord class for land texture records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obmgefrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObMgefRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObMgefDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMgefRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObMgefRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObMgefRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObMgefRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMgefRecord Constructor
 *
 *=========================================================================*/
CObMgefRecord::CObMgefRecord () {
  m_pData     = NULL;
  m_pFullName = NULL;
}
/*===========================================================================
 *		End of Class CObMgefRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMgefRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObMgefRecord::Destroy (void) {
  m_pData     = NULL;
  m_pFullName = NULL;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObMgefRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMgefRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObMgefRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObMgefRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMgefRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObMgefRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pData = ObCastClass(CObMgefDataSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    m_pFullName = ObCastClass(CObStringSubrecord, pSubrecord);
  }
  else {  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObMgefRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMgefRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObMgefRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pData == pSubrecord) {
    m_pData = NULL;
  }
  else if (m_pFullName == pSubrecord) {
    m_pFullName = NULL;
  } else {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObMgefRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMgefRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObMgefRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObMgefRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObMgefRecord Set Field Methods
 *=========================================================================*/

