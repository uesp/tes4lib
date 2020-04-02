/*===========================================================================
 *
 * File:	Obexport.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 11, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBEXPORT_H
#define __OBEXPORT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "records/obrecord.h"
  #include "records/obcheckrecord.h"
  #include "obrecordhandler.h"
  #include "obespfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

	/* Export a CSV file */
  bool ObCsvExport (const SSCHAR* pFilename, CObEspFile& EspFile, obexportinfo_t& ExportInfo);

  bool PrepareObCsvExport         (obcsvinfo_t& CsvInfo, const obrecfieldmap_t* pStartFieldMap);
  bool PrepareObCsvExportFromList (obcsvinfo_t& CsvInfo, obfieldid_t* pFieldList);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/
  extern obfieldid_t g_ExteriorTeleportExportFieldList[];
  extern obfieldid_t g_PlantExportFieldList[];
  extern obfieldid_t g_MapMarkerExportFieldList[];

  extern obexportinfo_t g_ExportCsvExtLocations;
  extern obexportinfo_t g_ExportCsvMapMarkers;
  extern obexportinfo_t g_ExportCsvPlants;
/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obexport.H
 *=========================================================================*/
