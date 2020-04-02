/*===========================================================================
 *
 * File:	Obtypegroup.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obtypegroup.h"




/*===========================================================================
 *
 * Class CObTypeGroup Method - bool AddChildRecord (pNewRecord);
 *
 * Attempts to add the given record to the group or its children. If
 * the record does not belong in the group it is not added and false
 * is returned. On success true is returned.
 *
 * Type groups can only accept records of the same type.
 *
 *=========================================================================*/
bool CObTypeGroup::AddChildRecord (CObBaseRecord* pNewRecord) {

  if (pNewRecord->GetRecordType() == GetContainsType()) {
    m_pRecords->Add(pNewRecord);
    pNewRecord->SetParentGroup(this);
    return (true);
   }

  return (false);
 }
/*===========================================================================
 *		End of Class Method CObTypeGroup::AddChildRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTypeGroup Method - bool DeleteChildRecord (pNewRecord);
 *
 * Attempts to delete the given record from the group or its children. If
 * the record does not belong in the group it is not deleted and false
 * is returned. On success true is returned.
 *
 *=========================================================================*/
bool CObTypeGroup::DeleteChildRecord (CObBaseRecord* pRecord) {
  return m_pRecords->Delete(pRecord);
 }
/*===========================================================================
 *		End of Class Method CObTypeGroup::DeleteChildRecord()
 *=========================================================================*/

