/*===========================================================================
 *
 * File:	Obtestformid.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "modfile/obespfile.h"
#include "common/obutils.h"
#include "ctype.h"
#include "windows.h"
#include "common/obtime.h"
#include "common/dl_map.h"
#include "common/obarray.h"
#include "modfile/obsimplerecordhandler.h"
#include "modfile/obmultirecordhandler.h"


/*===========================================================================
 *
 * Begin Global Definitions
 *
 *=========================================================================*/

	/* Input buffer used when comparing files (bigger is faster) */
  const dword BUFFER_SIZE = 1256000;

	/* Command line parameters */
  CSString	g_InputFilename;
  CSString	g_OutputFilename;
  bool		g_OverwriteOutput = false;

	/* File for input and output */
  CObSimpleRecordHandler	g_InputFile;

	/* Temporary buffers */
  byte		Buffer1[BUFFER_SIZE + 64];
  byte		Buffer2[BUFFER_SIZE + 64];

	/* Times in seconds */
  double	g_LoadTime;	
  double	g_SaveTime;

	/* Formid tests to perform */
  bool		g_TestFixupFormid     = true;
  bool		g_TestCheckFormidLocs = true;

	/* Maximum modindex to test */
  #define OB_MAX_TEST_MODINDEX 5

	/* Used to check data that is not always a formid */
  typedef bool (*FORMIDCHECKFUNC) (byte* pData, const dword Size);
  bool CheckCTDA1Data (byte* pData, const dword Size);
  bool CheckCTDA2Data (byte* pData, const dword Size);
  bool CheckPLDTData  (byte* pData, const dword Size);
  bool CheckPTDTData  (byte* pData, const dword Size);

	/* Used to hold formid locations for testing */
  struct obformidloc_t {
	const obrectype_t*	RecordType;
	const obrectype_t*	SubrecordType;
	dword			ByteOffset;
	int			ArraySize;
	FORMIDCHECKFUNC		CheckFunc;
  };

  dword		g_CheckLocationErrors = 0;
  dword		g_CheckLocationCount  = 0;

/*===========================================================================
 *		End of Global Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Formid Locations
 *
 *=========================================================================*/
obformidloc_t g_FormidLocations[] = {
	{ &OB_NAME_ACHR,   &OB_NAME_XESP,  0, -1, NULL },
	{ &OB_NAME_ACHR,   &OB_NAME_XPCI,  0, -1, NULL },
	{ &OB_NAME_ACHR,   &OB_NAME_XMRC,  0, -1, NULL },
	{ &OB_NAME_ACHR,   &OB_NAME_NAME,  0, -1, NULL },
	{ &OB_NAME_ACHR,   &OB_NAME_XHRS,  0, -1, NULL },
	{ &OB_NAME_ACRE,   &OB_NAME_XOWN,  0, -1, NULL },
	{ &OB_NAME_ACRE,   &OB_NAME_XESP,  0, -1, NULL },
	{ &OB_NAME_ACRE,   &OB_NAME_NAME,  0, -1, NULL },
	{ &OB_NAME_ACTI,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_ACTI,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_ALCH,   &OB_NAME_SCIT,  0, -1, NULL },
	{ &OB_NAME_ALCH,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_AMMO,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_ANIO,   &OB_NAME_DATA,  0, -1, NULL },
	{ &OB_NAME_APPA,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_ARMO,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_ARMO,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_BOOK,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_BOOK,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_BSGN,   &OB_NAME_SPLO,  0, -1, NULL },
	{ &OB_NAME_CELL,   &OB_NAME_XOWN,  0, -1, NULL },
	{ &OB_NAME_CELL,   &OB_NAME_XCCM,  0, -1, NULL },
	{ &OB_NAME_CELL,   &OB_NAME_XGLB,  0, -1, NULL },
	{ &OB_NAME_CELL,   &OB_NAME_XCWT,  0, -1, NULL },
	{ &OB_NAME_CELL,   &OB_NAME_XCLR,  0,  4, NULL },
	{ &OB_NAME_CLMT,   &OB_NAME_WLST,  0,  8, NULL },
	{ &OB_NAME_CLOT,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_CLOT,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_CONT,   &OB_NAME_CNTO,  0, -1, NULL },
	{ &OB_NAME_CONT,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_CONT,   &OB_NAME_QNAM,  0, -1, NULL },
	{ &OB_NAME_CONT,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_SPLO,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_CNTO,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_PKID,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_CSCR,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_CSDI,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_INAM,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_ZNAM,  0, -1, NULL },
	{ &OB_NAME_CREA,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_DIAL,   &OB_NAME_QSTI,  0, -1, NULL },
	{ &OB_NAME_DOOR,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_DOOR,   &OB_NAME_BNAM,  0, -1, NULL },
	{ &OB_NAME_DOOR,   &OB_NAME_ANAM,  0, -1, NULL },
	{ &OB_NAME_DOOR,   &OB_NAME_TNAM,  0, -1, NULL },
	{ &OB_NAME_DOOR,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_ENCH,   &OB_NAME_SCIT,  0, -1, NULL },
	{ &OB_NAME_FACT,   &OB_NAME_XNAM,  0, -1, NULL },
	{ &OB_NAME_FLOR,   &OB_NAME_PFIG,  0, -1, NULL },
	{ &OB_NAME_FLOR,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_FURN,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_IDLE,   &OB_NAME_DATA,  0, -1, NULL },
	{ &OB_NAME_IDLE,   &OB_NAME_DATA,  4, -1, NULL },
	{ &OB_NAME_IDLE,   &OB_NAME_CTDA, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_IDLE,   &OB_NAME_CTDA, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_INFO,   &OB_NAME_CTDT, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_INFO,   &OB_NAME_CTDT, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_INFO,   &OB_NAME_CTDA, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_INFO,   &OB_NAME_CTDA, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_INFO,   &OB_NAME_SCRO,  0, -1, NULL },
	{ &OB_NAME_INFO,   &OB_NAME_QSTI,  0, -1, NULL },
	{ &OB_NAME_INFO,   &OB_NAME_TCLT,  0, -1, NULL },
	{ &OB_NAME_INFO,   &OB_NAME_TCLF,  0, -1, NULL },
	{ &OB_NAME_INFO,   &OB_NAME_NAME,  0, -1, NULL },
	{ &OB_NAME_INGR,   &OB_NAME_SCIT,  0, -1, NULL },
	{ &OB_NAME_INGR,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_KEYM,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_LAND,   &OB_NAME_ATXT,  0, -1, NULL },
	{ &OB_NAME_LAND,   &OB_NAME_BTXT,  0, -1, NULL },
	{ &OB_NAME_LAND,   &OB_NAME_VTEX,  0,  4, NULL },
	{ &OB_NAME_LIGH,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_LIGH,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_LSCR,   &OB_NAME_LNAM,  0, -1, NULL },
	{ &OB_NAME_LSCR,   &OB_NAME_LNAM,  4, -1, NULL },
	{ &OB_NAME_LTEX,   &OB_NAME_GNAM,  0, -1, NULL },
	{ &OB_NAME_LVLC,   &OB_NAME_LVLO,  4, -1, NULL },
	{ &OB_NAME_LVLC,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_LVLC,   &OB_NAME_TNAM,  0, -1, NULL },
	{ &OB_NAME_LVLI,   &OB_NAME_LVLO,  4, -1, NULL },
	{ &OB_NAME_LVSP,   &OB_NAME_LVLO,  4, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 24, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 32, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 36, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 40, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 44, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 48, -1, NULL },
	{ &OB_NAME_MGEF,   &OB_NAME_DATA, 52, -1, NULL },
	{ &OB_NAME_MISC,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_SPLO,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_CNTO,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_PKID,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_HNAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_CNAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_RNAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_INAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_ZNAM,  0, -1, NULL },
	{ &OB_NAME_NPC_,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_PACK,   &OB_NAME_CTDA, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_PACK,   &OB_NAME_CTDA, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_PACK,   &OB_NAME_CTDT, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_PACK,   &OB_NAME_CTDT, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_PACK,   &OB_NAME_PLDT,  4, -1, CheckPLDTData },
	{ &OB_NAME_PACK,   &OB_NAME_PTDT,  4, -1, CheckPTDTData },
	{ &OB_NAME_PGRD,   &OB_NAME_PGRL,  0, -1, NULL },
	{ &OB_NAME_QUST,   &OB_NAME_CTDA, 12, -1, CheckCTDA1Data },
	{ &OB_NAME_QUST,   &OB_NAME_CTDA, 16, -1, CheckCTDA2Data },
	{ &OB_NAME_QUST,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_QUST,   &OB_NAME_QSTA,  0, -1, NULL },
	{ &OB_NAME_QUST,   &OB_NAME_SCRO,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_SPLO,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_DNAM,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_DNAM,  4, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_ENAM,  8, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_VNAM,  0, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_VNAM,  4, -1, NULL },
	{ &OB_NAME_RACE,   &OB_NAME_XNAM,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XRTM,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XTEL,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XLOC,  4, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XOWN,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XESP,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XGLB,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XPCI,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_XTRG,  0, -1, NULL },
	{ &OB_NAME_REFR,   &OB_NAME_NAME,  0, -1, NULL },
	{ &OB_NAME_REGN,   &OB_NAME_RDWT,  0,  8, NULL },
	{ &OB_NAME_REGN,   &OB_NAME_RDGS,  0,  8, NULL },
	{ &OB_NAME_REGN,   &OB_NAME_RDOT,  0, 52, NULL },
	{ &OB_NAME_REGN,   &OB_NAME_RDSD,  0, 12, NULL },
	{ &OB_NAME_REGN,   &OB_NAME_WNAM,  0, -1, NULL },
	{ &OB_NAME_SCPT,   &OB_NAME_SCRO,  0, -1, NULL },
	{ &OB_NAME_SGST,   &OB_NAME_SCIT,  0, -1, NULL },
	{ &OB_NAME_SLGM,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_SPEL,   &OB_NAME_SCIT,  0, -1, NULL },
	{ &OB_NAME_WATR,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_WEAP,   &OB_NAME_SCRI,  0, -1, NULL },
	{ &OB_NAME_WEAP,   &OB_NAME_ENAM,  0, -1, NULL },
	{ &OB_NAME_WRLD,   &OB_NAME_NAM2,  0, -1, NULL },
	{ &OB_NAME_WRLD,   &OB_NAME_CNAM,  0, -1, NULL },
	{ &OB_NAME_WRLD,   &OB_NAME_WNAM,  0, -1, NULL },
	{ &OB_NAME_WTHR,   &OB_NAME_SNAM,  0, -1, NULL },
	{ &OB_NAME_NULL,   &OB_NAME_NULL,  0, -1, NULL }
};
/*===========================================================================
 *		End of Formid Locations
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckCTDA1Data (pData, const Size);
 *
 *=========================================================================*/
bool CheckCTDA1Data (byte* pData, const dword Size) {
  if (Size < 12) return (false);
  return CObCtdaSubrecord::IsRefParam1(*(long *)(pData + 8));
}
/*===========================================================================
 *		End of Function CheckCTDA1Data()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckCTDA2Data (pData, Size);
 *
 *=========================================================================*/
bool CheckCTDA2Data (byte* pData, const dword Size) {
  if (Size < 12) return (false);
  return CObCtdaSubrecord::IsRefParam2(*(long *)(pData + 8));
}
/*===========================================================================
 *		End of Function CheckCTDA2Data()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckPLDTData (pData, Size);
 *
 *=========================================================================*/
bool CheckPLDTData (byte* pData, const dword Size) {
  if (Size < 4) return (false);
  return ((*(long *)(pData)) <= 4);
}
/*===========================================================================
 *		End of Function CheckPLDTData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckPTDTData (pData, Size);
 *
 *=========================================================================*/
bool CheckPTDTData (byte* pData, const dword Size) {
  if (Size < 4) return (false);
  return ((*(long *)(pData)) <= 1);
}
/*===========================================================================
 *		End of Function CheckPTDTData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool MatchSubrecordFormidArray (pSubrecord, pRecord, FormidLocation);
 *
 *=========================================================================*/
bool MatchSubrecordFormidArray (CObSubrecord* pSubrecord, CObRecord* pRecord, obformidloc_t& FormidLocation) {
  CObRecord*    pFindRecord;
  obformid_t    FormID;
  dword         ByteOffset;
  dword         DataSize = pSubrecord->GetRecordSize();

  for (ByteOffset = 0; ByteOffset < DataSize; ByteOffset += FormidLocation.ArraySize) {
    ++g_CheckLocationCount;
    FormID = *(obformid_t *)(pSubrecord->GetData() + ByteOffset + FormidLocation.ByteOffset);
    if (FormID == 0) continue;

    pFindRecord = g_InputFile.FindFormID(FormID);

    if (pFindRecord == NULL) {
      SystemLog.Printf("%4.4s(0x%08X) -- %4.4s (offset 0x%04X): Failed to find the formid 0x%X!", FormidLocation.RecordType->Name,  pRecord->GetFormID(), pSubrecord->GetRecordType().Name, ByteOffset + FormidLocation.ByteOffset, FormID);
      ++g_CheckLocationErrors;
    }
  } 

  return (true);
}
/*===========================================================================
 *		End of Function MatchSubrecordFormidArray()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool MatchSubrecordFormid (pSubrecord, pRecord, FormidLocation);
 *
 *=========================================================================*/
bool MatchSubrecordFormid (CObSubrecord* pSubrecord, CObRecord* pRecord, obformidloc_t& FormidLocation) {
  CObRecord*    pFindRecord;
  obformid_t    FormID;
  bool		Result;

	/* Ignore if the subrecord data is too small */
  if (pSubrecord->GetRecordSize() < FormidLocation.ByteOffset + 4) return (true);

	/* Use the check function if present */
  if (FormidLocation.CheckFunc != NULL) {
    Result = FormidLocation.CheckFunc(pSubrecord->GetData(), pSubrecord->GetRecordSize());
    if (!Result) return (true);
  }

  ++g_CheckLocationCount;
  FormID = *(obformid_t *)(pSubrecord->GetData() + FormidLocation.ByteOffset);
  if (FormID == 0) return (true);

  pFindRecord = g_InputFile.FindFormID(FormID);

  if (pFindRecord == NULL) {
    SystemLog.Printf("%4.4s(0x%08X) -- %4.4s (offset 0x%04X): Failed to find the formid 0x%X!", FormidLocation.RecordType->Name, pRecord->GetFormID(), pSubrecord->GetRecordType().Name, FormidLocation.ByteOffset, FormID);
    ++g_CheckLocationErrors;

    if (pSubrecord->GetRecordType() == OB_NAME_CTDA) {
      dword FuncIndex = *(dword *)(pSubrecord->GetData() + 8);
      SystemLog.Printf("\tFunction Index = 0x%04X (%s, %s)", FuncIndex, CObCtdaSubrecord::IsRefParam1(FuncIndex) ? "yes" : "no", CObCtdaSubrecord::IsRefParam2(FuncIndex) ? "yes" : "no");
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Function MatchSubrecordFormid()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckFormidLocations (pRecord, FormidLocation);
 *
 *=========================================================================*/
bool CheckFormidLocations (CObRecord* pRecord, obformidloc_t& FormidLocation) {
  CObSubrecord* pSubrecord;
  dword         Index;
  bool          Result;

  for (Index = 0; Index < pRecord->GetNumSubrecords(); ++Index) {
    pSubrecord = pRecord->GetSubrecord(Index);
    if (pSubrecord->GetRecordType() != *FormidLocation.SubrecordType) continue;

    if (FormidLocation.ArraySize > 0)
      Result = MatchSubrecordFormidArray(pSubrecord, pRecord, FormidLocation);
    else
      Result = MatchSubrecordFormid(pSubrecord, pRecord, FormidLocation);

    if (!Result) return (false);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Function CheckFormidLocations()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckFormidLocations (pRecord);
 *
 *=========================================================================*/
bool CheckFormidLocations (CObRecord* pRecord) {
  CObRecord*    pFindRecord;
  dword		Index;
  bool		Result;

  	/* Find the record formid */
  pFindRecord = g_InputFile.FindFormID(pRecord->GetFormID());
  ++g_CheckLocationCount;

  if (pFindRecord == NULL) {
    SystemLog.Printf("%4.4s(0x%08X) -- Failed to find the formid 0x%X!", pRecord->GetRecordType().Name, pRecord->GetFormID(), pRecord->GetFormID());
    ++g_CheckLocationErrors;
  }

  for (Index = 0; *g_FormidLocations[Index].RecordType != OB_NAME_NULL; ++Index) {
    if (*g_FormidLocations[Index].RecordType != pRecord->GetRecordType()) continue;

   Result = CheckFormidLocations(pRecord, g_FormidLocations[Index]);
   if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Function CheckFormidLocations()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckFormidLocations (void);
 *
 *=========================================================================*/
bool CheckFormidLocations (void) {
  CObRecord* pRecord;
  OBMAPPOS   Position;
  obtimer_t  Timer;
  double     DeltaTime;
  bool       Result;

  SystemLog.Printf("Checking formid locations...");
  ObStartTimer(Timer);
  pRecord = g_InputFile.GetFirstRecord(Position);

  while (pRecord != NULL) {
    Result = CheckFormidLocations(pRecord);
    if (!Result) return (false);

    pRecord = g_InputFile.GetNextRecord(Position);
  }
  
  DeltaTime = ObEndTimer(Timer);
  SystemLog.Printf("Checked %u formid locations with %u errors in %f seconds.", g_CheckLocationCount, g_CheckLocationErrors, DeltaTime);
  return (true);
}
/*===========================================================================
 *		End of Function CheckFormidLocations()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CSString CreateOutputFile (pString);
 *
 * Create an output file from an input filename.
 *
 *=========================================================================*/
CSString CreateOutputFile (const SSCHAR* pString) {
  CSString Buffer;

  Buffer  = pString;
  Buffer += ".tmp";
  
  return (Buffer);
 }
/*===========================================================================
 *		End of Function CreateOutputFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckParameters (void);
 *
 * Checks the current parameter values registering any errors and returning
 * false if any of them are invalid.
 *
 *=========================================================================*/
bool CheckParameters (void) {

	/* No input file */
  if (g_InputFilename.IsEmpty()) {
    AddObGeneralError("No input ESP/ESM file specified!");
    return (false);
   }

	/* Ensure output file is set */
  if (g_OutputFilename.IsEmpty()) {
    g_OutputFilename = CreateOutputFile(g_InputFilename);
   }

	/* Ensure the input/output files are different */
  if (g_InputFilename.CompareNoCase(g_OutputFilename) == 0) {
    AddObGeneralError("The input and output files are the same!");
    return (false);
   }

	/* Check if output file exists */
  if (!g_OverwriteOutput && ObFileExists(g_OutputFilename)) {
    AddObGeneralError("The output file '%s' already exists!", g_OutputFilename.c_str());
    return (false);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function CheckParameters()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int DisplayError (void);
 *
 * Outputs the last error message to stdout. Returns the last set error 
 * code.
 *
 *=========================================================================*/
int DisplayError (void) {
  CObError* pLastError = ObErrorHandler->GetLastError();

	/* Special case for no error */
  if (pLastError == NULL) {
    printf ("No error occurred!\n");
    return (0);
   }

  if (pLastError->GetType() == OBERR_TYPE_GENERAL) {
    printf ("   ERROR: %s\n", pLastError->GetErrorMessage()); 
   }
  else {
    printf ("   ERROR: %s\n", pLastError->GetErrorMessage()); 
    printf ("          %s\n", pLastError->GetErrorString().c_str());
   }

  return pLastError->GetCode();
 }
/*===========================================================================
 *		End of Function DisplayError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void PrintHelp (void);
 *
 * Prints a simple help screen.
 *
 *=========================================================================*/
void PrintHelp (void) {
  printf("\n");
  printf("    ObTestFormid [inputfile] [outputfile] [/o] [/m]\n");
  printf("        [inputfile]  - Existing ESP/ESM file to load\n");
  printf("        [outputfile] - File to save. If omitted inputfile.tmp will be used.\n");
  printf("        [/o]         - Overwrite output file. If omitted the test will abort\n");
  printf("                       if the output file already exists.\n");
  printf("        [/m]         - Use the Oblivion.esm file in the current Oblivion\n");
  printf("                       install path as the input file.\n");
  printf("\n");
  printf("    Performs various formid tests on the supplied input file.\n");
  printf("\n");
  printf("    WARNING: Testing Oblivion.esm requires 800MB of memory and takes at least\n");
  printf("    a minute to complete. On lower end machines, especially those with less\n");
  printf("    than 1GB of RAM, the test will take considerably longer.\n");
  printf("\n");
 }
/*===========================================================================
 *		End of Function PrintHelp()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ParseCommandLine (ArgCount, pArgs);
 *
 * Parses input command line parameters. Returns false on any error.
 *
 *=========================================================================*/
bool ParseCommandLine (const int ArgCount, char* pArgs[]) {
  bool     Result;
  int      Index;

  for (Index = 1; Index < ArgCount; ++Index) {
    
    if (pArgs[Index][0] == '-' || pArgs[Index][0] == '/' || pArgs[Index][0] == '\\') {
      if (tolower(pArgs[Index][1]) == 'o') {
        g_OverwriteOutput = true;
       }
      else if (tolower(pArgs[Index][1]) == 'm') {
        Result = GetObInstallPath(g_InputFilename);
	if (Result) g_InputFilename += "data\\oblivion.esm";
       }
      else if (tolower(pArgs[Index][1]) == '?') {
        PrintHelp();
        exit(0);
       }
     }
    else if (g_InputFilename.IsEmpty()) {
      g_InputFilename = pArgs[Index];
      g_InputFilename.Trim();
     }
    else if (g_OutputFilename.IsEmpty()) {
      g_OutputFilename = pArgs[Index];
      g_OutputFilename.Trim();
     }

   }

  return (true);
 }
/*===========================================================================
 *		End of Function ParseCommandLine()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CompareFiles (pInput, pOutput);
 *
 *=========================================================================*/
bool CompareFiles (const SSCHAR* pInput, const SSCHAR* pOutput, CObFormidFixupArray& FixupArray) {
  CObFile File1;
  CObFile File2;
  int64   Size1 = 0;
  int64   Size2 = 0;
  dword   InputSize1;
  dword   InputSize2;
  bool    Result;
  bool    FailedOutput = false;
  dword   Index;
  dword   MismatchCount = 0;
  dword	  FormidCount   = 0;
  dword	  PlayeridCount = 0;
  
	/* Open files */
  Result  = File1.Open(pInput, "rb");
  Result &= File2.Open(pOutput, "rb");
  if (!Result) return (false);

	/* Do filesize check first */
  Size1 = File1.GetFileSize();
  Size2 = File2.GetFileSize();

  if (Size1 < Size2) {
    SystemLog.Printf("\tFailed! The output file is %I64d bytes longer than the input file!", Size2 - Size1);
    FailedOutput = true;
   }
  else if (Size1 > Size2) {
    SystemLog.Printf("\tFailed! The input file is %I64d bytes longer than the output file!", Size1 - Size2);
    FailedOutput = true;
   }
  else {
    //printf ("(%ld bytes)", Size1);
   }

  Size1 = 0;
  Size2 = 0;

	/* Read and compare data */
  while (!File1.IsEOF() && !File2.IsEOF()) {
    File1.Read(Buffer1, BUFFER_SIZE, InputSize1); 
    File2.Read(Buffer2, BUFFER_SIZE, InputSize2);

    if (InputSize1 > InputSize2) {
      Size1 = File1.GetFileSize();
      Size2 = File2.GetFileSize();
      if (!FailedOutput) printf("Failed!\n");
      SystemLog.Printf("\tThe input file is %I64d bytes longer than the output file!", Size1 - Size2);
      return (true);
     }
    else if (InputSize1 < InputSize2) {
      Size1 = File1.GetFileSize();
      Size2 = File2.GetFileSize();
      if (!FailedOutput) printf("Failed!\n");
      SystemLog.Printf("\tThe output file is %I64d bytes longer than the input file!", Size2 - Size1);
      return (true);
    }

      for (Index = 0; Index < InputSize1; ++Index) {
        if (Buffer1[Index] != Buffer2[Index]) {
          //if (!FailedOutput) printf("Failed!\n");

          if (Buffer1[Index] < FixupArray.GetSize()) {
	    if (FixupArray[Buffer1[Index]] == (int)Buffer2[Index]) {
              ++FormidCount;
	    }
	    else {
	      SystemLog.Printf ("\tFormid Mismatch found at offset 0x%08I64X (0x%02X != 0x%02X)", Size1 + Index, (dword)Buffer1[Index], (dword)Buffer2[Index]);
	      ++MismatchCount;
	    }
	  }
	  else {
	    if (Buffer1[Index] == 0x14 && Buffer2[Index] == 0x7 && Buffer1[Index+3] == 0 && Buffer2[Index+3] != 0) {
	      ++PlayeridCount;
	    }
	    else {
	      SystemLog.Printf ("\tMismatch found at offset 0x%08I64X (0x%02X != 0x%02X)", Size1 + Index, (dword)Buffer1[Index], (dword)Buffer2[Index]);
	      ++MismatchCount;
	    }
          }
	  if (MismatchCount > 10000) return (true);
        }
      }

    Size1 += InputSize1;
    Size2 += InputSize2;
  }

	/* Mismatch in file sizes */
  if (File1.IsEOF() && !File2.IsEOF()) {
    Size1 = File1.Tell();
    Size2 = File2.GetFileSize();
    if (!FailedOutput) printf("Failed!\n");
    SystemLog.Printf("\tThe output file is %I64u bytes longer than the input file!", Size2 - Size1);
  }
  else if (!File1.IsEOF() && File2.IsEOF()) {
    Size1 = File1.GetFileSize();
    Size2 = File2.Tell();
    if (!FailedOutput) printf("Failed!\n");
    SystemLog.Printf("\tThe input file is %I64u bytes longer than the output file!", Size1 - Size2);
   }

  if (MismatchCount > 0)
    SystemLog.Printf ("Failed! Files had at least %u mismatches in (%I64u bytes). Found %u matching formid fixups with %u player formid fixes.", MismatchCount, Size1, FormidCount, PlayeridCount);
  else
    SystemLog.Printf ("Success! Files are an exact match (%I64u bytes) considering %u formid fixups matched with %u player formid fixes.", Size1, FormidCount, PlayeridCount);

  return (true);
 }
/*===========================================================================
 *		End of Function CompareFiles()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool DoFixupFormidTest (void);
 *
 * Applies an arbitrary fixup to the given file and then tests to ensure
 * the formids have correctly changed.
 *
 *=========================================================================*/
bool DoFixupFormidTest (void) {
  CObFormidFixupArray   FixupArray;
  CObRecord*		pRecord;
  CObRecord*		pRecord1;
  OBMAPPOS		Position;
  bool			Result;
  obtimer_t		Timer;
  dword			Index;

	/* Initialize the fixup */
  for (Index = 0; Index < OB_MAX_TEST_MODINDEX; ++Index) {
    FixupArray.Add(Index + 1);
  }

  ObStartTimer(Timer);

	/* Perform the fixup */
  Result = g_InputFile.GetEspFile().FixupFormids(FixupArray);
  if (!Result) return (false);

  ObEndTimer(Timer, "Fixup formids in ");
  ObStartTimer(Timer);

	/* Save the file */
  SystemLog.Printf("Saving file...");
  Result = g_InputFile.GetEspFile().Save(g_OutputFilename);
  if (!Result) return (false);

  ObEndTimer(Timer, "Saved file in ");
  ObStartTimer(Timer);

	/* Compare the file */
  SystemLog.Printf("Comparing input/output files...");
  Result = CompareFiles(g_InputFilename, g_OutputFilename, FixupArray);
  if (!Result) return (false);

  ObEndTimer(Timer, "Compared files in ");
  ObStartTimer(Timer);

	/* Re-index the file */
  g_InputFile.IndexRecords(NULL);

  ObEndTimer(Timer, "Re-indexed file in ");
  ObStartTimer(Timer);

	/* Iterate through and check records */
  SystemLog.Printf("Checking all formids...");
  pRecord = g_InputFile.GetFirstRecord(Position);

  while (pRecord) {
    pRecord1 = g_InputFile.FindFormID(pRecord->GetFormID());

    if (pRecord1 == NULL) {
      SystemLog.Printf("Formid 0x%X not found!", pRecord->GetFormID());
    }
    else if (pRecord1 != pRecord) {
      SystemLog.Printf("Formid 0x%X mismatch!", pRecord->GetFormID());
    }

    pRecord = g_InputFile.GetNextRecord(Position);
  }

  ObEndTimer(Timer, "Checked formids in ");

  return (true);
}
/*===========================================================================
 *		End of Function DoFixupFormidTest()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool DoFormidTests (void);
 *
 *=========================================================================*/
bool DoFormidTests (void) {
  bool Result;

	/* Attempt to load the requested file */
  SystemLog.Printf ("Loading %s...", g_InputFilename.c_str());

  Result = g_InputFile.Load(g_InputFilename);
  if (!Result) return (false);

  if (g_TestFixupFormid) {
    Result = DoFixupFormidTest();
    if (!Result) return (false);
  }

  if (g_TestCheckFormidLocs) {
    Result = CheckFormidLocations();
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Function DoFormidTests()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void l_LogCallback (pString, Args, UserData);
 *
 *=========================================================================*/
void l_LogCallback (const SSCHAR* pString, va_list Args, const dword UserData) {
  printf("\t");
  vprintf(pString, Args);
  printf("\n");
}
/*===========================================================================
 *		End of Function l_LogCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Main Program
 *
 *=========================================================================*/
int main (int argc, char* argv[]) {
  bool Result;

	/* Output simple title */
  printf ("ObTestFormid - Perform various formid tests on a supplied file.\n");
  SystemLog.Open("obtestformid.log");
  SystemLog.SetCallback(l_LogCallback, 0);

  if (argc <= 1) {
    PrintHelp();
    return (0);
   }
  
	/* Parse the input parameters */
  Result = ParseCommandLine(argc, argv);
  if (!Result) return DisplayError();

	/* Ensure valid parameters */
  Result = CheckParameters();
  if (!Result) return DisplayError();

	/* Do the comparison */
  Result = DoFormidTests();
  if (!Result) return DisplayError();

  return (0);
 }
/*===========================================================================
 *		End of Main Program
 *=========================================================================*/

