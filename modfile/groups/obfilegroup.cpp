/*===========================================================================
 *
 * File:	ObFilegroup.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obfilegroup.h"


/*===========================================================================
 *
 * Class CObFileGroup Method - bool Write (File, pCallback);
 *
 * Writes group data to the current location in the given file. Returns
 * false on any error.
 *
 *=========================================================================*/
bool CObFileGroup::Write (CObFile& File, CObCallback* pCallback) {
  CObBaseRecord* pRecord;
  dword		 Index;
  bool		 Result;
  int		 StartOffset;
  int		 iResult;

  if (pCallback != NULL) {
    pCallback->SetTotalRecords(GetRecords().GetSize());
    iResult = pCallback->ForceCallback(0);
    if (iResult < 0) return (false);
  } 

	/* Save the start position of the group */
  Result = File.Tell(StartOffset);
  if (!Result) return (false); 

	/* Output all group content */
  for (Index = 0; Index < GetRecords().GetSize(); ++Index) {
    pRecord = GetRecords()[Index];
    assert(pRecord != NULL);
    
    Result = pRecord->Write(File);
    if (!Result) return (false); 

    if (pCallback != NULL) {
      iResult = pCallback->UpdateCallback(Index);
      if (iResult < 0) return (false);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFileGroup::Write()
 *=========================================================================*/