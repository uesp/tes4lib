/*===========================================================================
 *
 * File:	Obexport.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obexport.h"


/*===========================================================================
 *
 * Begin Export Field Arrays
 *
 * These arrays define what fields to output for various export types.
 *
 *=========================================================================*/
obfieldid_t g_ExteriorTeleportExportFieldList[] = {
	OB_FIELD_FORMID, OB_FIELD_EDITORID, OB_FIELD_RECORDTYPE, OB_FIELD_WORLDSPACE,
	OB_FIELD_FULLNAME, OB_FIELD_LOCATIONX, OB_FIELD_LOCATIONY, OB_FIELD_LOCATIONZ,
	OB_FIELD_ANGLEX, OB_FIELD_ANGLEY, OB_FIELD_ANGLEZ, 
	OB_FIELD_TELEPORTFORMID, OB_FIELD_TELEPORTNAME, 
	OB_FIELD_TELEPORTLOCX, OB_FIELD_TELEPORTLOCY, OB_FIELD_TELEPORTLOCZ,
	OB_FIELD_TELEPORTANGLEX, OB_FIELD_TELEPORTANGLEY, OB_FIELD_TELEPORTANGLEZ, 
	OB_FIELD_NONE };

obfieldid_t g_PlantExportFieldList[] = {
	OB_FIELD_FORMID, OB_FIELD_EDITORID, OB_FIELD_RECORDTYPE, OB_FIELD_WORLDSPACE,
	OB_FIELD_FULLNAME, OB_FIELD_LOCATIONX, OB_FIELD_LOCATIONY, OB_FIELD_LOCATIONZ,
	OB_FIELD_ANGLEX, OB_FIELD_ANGLEY, OB_FIELD_ANGLEZ, 
	OB_FIELD_BASEFORMID, OB_FIELD_BASEEDITORID, OB_FIELD_BASENAME,
	OB_FIELD_NONE };

obfieldid_t g_MapMarkerExportFieldList[] = {
	OB_FIELD_FORMID, OB_FIELD_EDITORID, OB_FIELD_RECORDTYPE, OB_FIELD_WORLDSPACE,
	OB_FIELD_FULLNAME, OB_FIELD_LOCATIONX, OB_FIELD_LOCATIONY, OB_FIELD_LOCATIONZ,
	OB_FIELD_ANGLEX, OB_FIELD_ANGLEY, OB_FIELD_ANGLEZ, 
	OB_FIELD_MARKERTYPE, OB_FIELD_MARKERTYPEID,
	OB_FIELD_NONE };
/*===========================================================================
 *		End of Export Field Arrays
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CSV Export Information Structures
 *
 * Holds information on how to export various CSV files.
 *
 *=========================================================================*/
obexportinfo_t g_ExportCsvExtLocations = {
	&OB_NAME_WRLD,
	OB_FORMID_NULL,
	true,
	IsObTeleportReference,
	g_ExteriorTeleportExportFieldList
};

obexportinfo_t g_ExportCsvMapMarkers = {
	&OB_NAME_WRLD,
	OB_FORMID_NULL,
	true,
	IsObMarkerReference,
	g_MapMarkerExportFieldList
};

obexportinfo_t g_ExportCsvPlants = {
	&OB_NAME_WRLD,
	OB_FORMID_NULL,
	true,
	IsObPlantReference,
	g_PlantExportFieldList
};
/*===========================================================================
 *		End of CSV Export Information Structures
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool PrepareObCsvExport (CsvInfo, pStartFieldMap);
 *
 * Prepares the given CsvInfo object using the given information. Returns
 * false on any error.
 *
 *=========================================================================*/
bool PrepareObCsvExport (obcsvinfo_t& CsvInfo, const obrecfieldmap_t* pStartFieldMap) {
  const obrecfieldmap_t* pFieldMap;
  obcsvcolinfo_t*	 pColInfo;
  CSString*		 pString;
  CCsvRow*		 pRow;
  dword			 Index;

	/* Ensure valid input */
  if (pStartFieldMap == NULL || CsvInfo.pCsvFile == NULL) return (false);
  
  CsvInfo.pEditorID   = NULL;
  CsvInfo.pRecordName = NULL;

  pRow = CsvInfo.pCsvFile->AddRow();
  assert (pRow != NULL);

	/* Enumerate all fields in class and all base classes */
  for (pFieldMap = pStartFieldMap; pFieldMap != NULL; pFieldMap = pFieldMap->pBaseFieldMap) {
    assert(pFieldMap != pFieldMap->pBaseFieldMap);

    for (Index = 0; pFieldMap->pField[Index].GetMethod != NULL; ++Index) {

		/* Ignore field if required */
      if (pFieldMap->pField[Index].IsNoCSV()) continue;
      
      pColInfo = new obcsvcolinfo_t;
      CsvInfo.ColInfos.Add(pColInfo);
      pString  = new CSString(GetObFieldString(pFieldMap->pField[Index].FieldID));
      pRow->Add(pString);

      pColInfo->ColIndex = pRow->GetSize() - 1;
      pColInfo->FieldID  = pFieldMap->pField[Index].FieldID;
      pColInfo->Process  = true;
      pColInfo->pValue   = pString;
      pColInfo->pField   = &pFieldMap->pField[Index];
      pColInfo->UserData = 0;

      if (pFieldMap->pField[Index].FieldID == OB_FIELD_EDITORID)   CsvInfo.pEditorID   = pColInfo;
      if (pFieldMap->pField[Index].FieldID == OB_FIELD_RECORDTYPE) CsvInfo.pRecordName = pColInfo;
    }
  }

	/* Ensure required fields */
  assert(CsvInfo.pEditorID   != NULL);
  assert(CsvInfo.pRecordName != NULL);

  return (true);
}
/*===========================================================================
 *		End of Function PrepareObCsvExport()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool PrepareObCsvExportFromList (CsvInfo, pFieldList);
 *
 * Initializes a CsvInfo structure in preparation for export.
 *
 *=========================================================================*/
bool PrepareObCsvExportFromList (obcsvinfo_t& CsvInfo, obfieldid_t* pFieldList) {
  obcsvcolinfo_t* pColInfo;
  CSString*       pString;
  CCsvRow*        pRow;
  dword           Index;

	/* Ensure valid input */
  if (pFieldList       == NULL) return AddObGeneralError("No CSV field list supplied!");
  if (CsvInfo.pCsvFile == NULL) return AddObGeneralError("No CSV file supplied!");

  pRow = CsvInfo.pCsvFile->AddRow();
  if (pRow == NULL) return (false);

  for (Index = 0; pFieldList[Index] != OB_FIELD_NONE; ++Index) {
    pColInfo = new obcsvcolinfo_t;
    CsvInfo.ColInfos.Add(pColInfo);
    pString  = new CSString(GetObFieldString(pFieldList[Index]));
    pRow->Add(pString);

    pColInfo->ColIndex = pRow->GetSize() - 1;
    pColInfo->FieldID  = pFieldList[Index];
    pColInfo->Process  = true;
    pColInfo->pValue   = pString;
    pColInfo->pField   = NULL;
    pColInfo->UserData = 0;

    if (pFieldList[Index] == OB_FIELD_EDITORID)   CsvInfo.pEditorID   = pColInfo;
    if (pFieldList[Index] == OB_FIELD_RECORDTYPE) CsvInfo.pRecordName = pColInfo;
  }

  return (true);
}
/*===========================================================================
 *		End of Function PrepareObCsvExportFromList()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCsvExportCsvGroup (pGroup, CsvInfo, ExportInfo);
 *
 * Exports matching records/groups within the given group to the given
 * CSV file. Local function assumes valid inputs.
 *
 *=========================================================================*/
bool ObCsvExportCsvGroup (CObGroup* pGroup, obcsvinfo_t& CsvInfo, obexportinfo_t& ExportInfo) {
  CObBaseRecord*  pBaseRecord;
  CObRecord*      pRecord;
  CObGroup*       pChildGroup;
  dword		  Index;
  bool            Result;
  
  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pChildGroup = ObCastClass(CObGroup, pBaseRecord);
    pRecord     = ObCastClass(CObRecord, pBaseRecord);

    if (pChildGroup != NULL) {
      Result = ObCsvExportCsvGroup(pChildGroup, CsvInfo, ExportInfo);
      if (!Result) return (false);
    }
    else if (pRecord != NULL && ExportInfo.CheckFunction) {
      Result = ExportInfo.CheckFunction(pRecord, 0);

      if (Result) {
        Result = pRecord->ExportCsv(CsvInfo);
        if (!Result) return (false);
      }
    }
    else if (pRecord != NULL) {
      Result = pRecord->ExportCsv(CsvInfo);
      if (!Result) return (false);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObCsvExportCsvGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCsvExport (pFilename, pRecordHandler, ExportInfo);
 *
 * Attempts to export records to a CSV file using the given information.
 *
 *=========================================================================*/
bool ObCsvExport (const SSCHAR* pFilename, CObEspFile& EspFile, obexportinfo_t& ExportInfo) {
  CObTypeGroup*   pTypeGroup;
  CObGroup*       pGroup;
  obcsvinfo_t     CsvInfo;
  CCsvFile        CsvFile;
  int		  GroupPos;
  bool            Result;

	/* Ensure valid input */
  if (pFilename == NULL) return (false);

	/* Initialize the CsvInfo structure */
  CsvInfo.pEditorID   = NULL;
  CsvInfo.pRecordName = NULL;
  CsvInfo.pCsvFile    = &CsvFile;

  Result = PrepareObCsvExportFromList(CsvInfo, ExportInfo.pFieldList);
  if (!Result) return (false);

	/* Find all records to export */
  pTypeGroup = EspFile.GetTypeGroup(*ExportInfo.pRecordType);
  if (pTypeGroup == NULL) return (true);

  pGroup = pTypeGroup->FindFirstGroup(ExportInfo.GroupFormID, GroupPos);

  while (pGroup != NULL) {
    Result = ObCsvExportCsvGroup(pGroup, CsvInfo, ExportInfo);
    if (!Result) return (false);
   
    pGroup = pTypeGroup->FindNextGroup(ExportInfo.GroupFormID, GroupPos);
  }

  return CsvFile.Save(pFilename);
}
/*===========================================================================
 *		End of Function ObCsvExport()
 *=========================================================================*/
