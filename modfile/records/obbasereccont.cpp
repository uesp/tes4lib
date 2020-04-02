/*===========================================================================
 *
 * File:	ObBaseRecCont.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbasereccont.h"



/*===========================================================================
 *
 * Class CObBaseRecordCont Method - bool Delete (pObject);
 *
 *=========================================================================*/
bool CObBaseRecordCont::Delete (CObBaseRecord* pObject) { 
  CObBaseRecord* pRecord;
  dword		 Index;
  bool		 Result;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pRecord = m_Records[Index];

    if (pRecord == pObject) {
      m_Records.Delete(Index);
      return (true);
     }

    Result = pRecord->DeleteChildRecord(pObject);
    if (Result) return (true);
   }

  return (false);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordCont::Delete()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObRefBaseRecordCont Method - bool Delete (pObject);
 *
 *=========================================================================*/
bool CObRefBaseRecordCont::Delete (CObBaseRecord* pObject) { 
  CObBaseRecord* pRecord;
  dword		 Index;
  bool		 Result;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pRecord = m_Records[Index];

    if (pRecord == pObject) {
      m_Records.Delete(Index);
      return (true);
     }

    Result = pRecord->DeleteChildRecord(pObject);
    if (Result) return (true);
   }

  return (false);
 }
/*===========================================================================
 *		End of Class Method CObRefBaseRecordCont::Delete()
 *=========================================================================*/
