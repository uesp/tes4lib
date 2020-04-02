/*===========================================================================
 *
 * File:	Obimport.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 30, 2006
 *
 * General import helper routines.
 *
 *=========================================================================*/

	/* Include Files */
#include "obimport.h"


/*===========================================================================
 *
 * Function - bool ObPrepareImportCsvInfo (CsvInfo, CsvFile);
 *
 * Prepares the given CSV info structure for the input file. Returns false
 * on any error. 
 *
 *=========================================================================*/
bool ObPrepareImportCsvInfo (obcsvinfo_t& CsvInfo, CCsvFile& CsvFile) {
  obcsvcolinfo_t* pColInfo;
  CSString*       pString;
  CCsvRow*        pHeaderRow;
  dword           Index;
  int		  FieldID;
  bool		  Result;
  
	/* Clear the current information */
  CsvInfo.ColInfos.Empty();
  CsvInfo.pEditorID   = NULL;
  CsvInfo.pRecordName = NULL;
  CsvInfo.pCsvFile    = &CsvFile;

	/* Ignore if no header row */
  pHeaderRow = CsvFile.GetRow(0);
  if (pHeaderRow == NULL) return AddObGeneralError("CSV file has no header row!");
  
  for (Index = 0; Index < pHeaderRow->GetSize(); ++Index) {
    pColInfo = new obcsvcolinfo_t;
    CsvInfo.ColInfos.Add(pColInfo);

    pColInfo->ColIndex = Index;
    pColInfo->FieldID  = OB_FIELD_UNKNOWN;
    pColInfo->pField   = NULL;
    pColInfo->Process  = false;
    pColInfo->UserData = 0;
    pColInfo->pValue   = NULL;

    pString = pHeaderRow->GetAt(Index);
    if (pString == NULL) continue;
    pColInfo->pValue = pString;

    Result = GetObFieldValue(FieldID, *pString);

    if (!Result) {
      AddObGeneralError("Unknown field '%s' found in column %d of CSV file!", pString->c_str(), Index);
      continue;
    }

    pColInfo->FieldID = FieldID;
    pColInfo->Process = true;

    switch (FieldID) {
      case OB_FIELD_EDITORID:
        CsvInfo.pEditorID = pColInfo;
        pColInfo->Process = false;
	break;
     case OB_FIELD_RECORDTYPE:
        CsvInfo.pRecordName = pColInfo;
        pColInfo->Process   = false;
	break;
    }
    
  }

	/* Ensure the required columns exist */
  if (CsvInfo.pEditorID   == NULL) return AddObGeneralError("Missing required 'EditorID' column in CSV file!");
  if (CsvInfo.pRecordName == NULL) return AddObGeneralError("Missing required 'RecordType' column in CSV file!");

  return (true);
}
/*===========================================================================
 *		End of Function ObPrepareImportCsvInfo()
 *=========================================================================*/
