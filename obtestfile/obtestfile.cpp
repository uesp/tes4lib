/*===========================================================================
 *
 * File:	Obtestfile.CPP
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


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Default hash map table sizes */
  #define OB_SUBRECFORMID_HASHMAPSIZE 31
  #define OB_SUBRECSIZE_HASHMAPSIZE   1001
  #define OB_SUBRECORD_HASHMAPSIZE    101
  #define OB_RECORD_HASHMAPSIZE       101

	/* Maximum number of sizes to display per subrecord */
  #define OB_MAX_SUBRECORD_SIZES 50

	/* Ignore formids below this value, except for the 0 value */
  #define OB_MIN_FORMID	128

	/* Number of possible formids to check in subrecord data */
  #define OB_MAX_FORMID_CHECKSIZE     20

	/* Holds information on possible formid fields in subrecords */
  struct obsubrecformid_t {
	obrectype_t	RecordType;
	dword		Count;
	dword		MinValue;
	dword		MaxValue;
  };

  typedef TGenPtrMap<dword, obsubrecformid_t, dword> CSubrecordFormids;

  struct obformiddata_t {
	CSubrecordFormids	Formids;
	bool			IsFormid;
	dword			Count;
	dword			TotalCount;
	dword			MinFormid;
	dword			MaxFormid;
  };

	/* Holds count of subrecords of a given byte size */
  struct obsubrecsize_t {
	dword Size;
	dword Count;
  };

  typedef TGenPtrMap<dword, obsubrecsize_t, dword> CSubrecordSizes;

	/* Hold statistics on a subrecord type within a record */
  struct obsubrecstat_t {
	obrectype_t	RecordType;	/* Subrecord type */
	dword		RecordCount;	/* Number of records it occurs in */
	dword		TotalCount;	/* Total count of the subrecord in the file */
	dword		MaxRecordCount; /* Maximum number of time it occurs in a single record */
	dword		CurRecCount;	/* Used to get the maximum count */
	dword		AlphaCount;	/* Number of subrecords that are only alpha-numeric */
	dword		NullTermCount;	/* For text fields, the number of null terminated strings */
	CSubrecordSizes	Sizes;		/* Sizes of subrecords */
	CObRecord*	pLastRecord;	/* Last record this was found in */
	dword		MinSize;
	dword		MaxSize;
	bool		IsFormid;	/* Data possibly contains a formid */

	obformiddata_t  FormidData[OB_MAX_FORMID_CHECKSIZE];
  };

  typedef TGenPtrMap<dword, obsubrecstat_t, dword> CObSubrecordStats;

	/* Holds statistics on a single record type */
  struct obrecstat_t {
	obrectype_t		RecordType;	/* Type of record */
	dword			Count;		/* Number of records found */
	CObSubrecordStats	SubrecordStats;
  };

  typedef TGenPtrMap<dword, obrecstat_t, dword> CObRecordStats;
  CObRecordStats g_RecordStats;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


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
  bool		g_DoStats = false;

	/* File for input and output */
  //CObEspFile	g_InputFile;
  CObSimpleRecordHandler	g_InputFile;

	/* Temporary buffers */
  byte		Buffer1[BUFFER_SIZE + 64];
  byte		Buffer2[BUFFER_SIZE + 64];

	/* Times in seconds */
  double	g_LoadTime;	
  double	g_SaveTime;

	/* Global statistics */
  dword		g_MinBinarySubrecordSize = 0;
  dword		g_MaxBinarySubrecordSize = 0;
  dword		g_MinAlphaSubrecordSize  = 0;
  dword		g_MaxAlphaSubrecordSize  = 0;

/*===========================================================================
 *		End of Global Definitions
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
  printf("    ObTestFile [inputfile] [outputfile] [/o] [/m]\n");
  printf("        [inputfile]  - Existing ESP/ESM file to load\n");
  printf("        [outputfile] - File to save. If omitted inputfile.tmp will be used.\n");
  printf("        [/o]         - Overwrite output file. If omitted the test will abort\n");
  printf("                       if the output file already exists.\n");
  printf("        [/m]         - Use the Oblivion.esm file in the current Oblivion\n");
  printf("                       install path as the input file.\n");
  printf("        [/s]         - Output statistics on the loaded plugin to the log file.\n");
  printf("\n");
  printf("    This program will attempt to load the input mod file and then save it to\n");
  printf("    the given output file. If successfuly the two files will be compared and\n");
  printf("    any differences noted. If the comparison is not perfect it is likely due\n");
  printf("    to a library bug and should be investigated.\n");
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
      else if (tolower(pArgs[Index][1]) == 's') {
        g_DoStats = true;
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
bool CompareFiles (const SSCHAR* pInput, const SSCHAR* pOutput) {
  CObFile File1;
  CObFile File2;
  int64   Size1 = 0;
  int64   Size2 = 0;
  dword   InputSize1;
  dword   InputSize2;
  bool    Result;
  bool    FailedOutput = false;
  int	  CmpResult;
  dword   Index;
  dword   MismatchCount = 0;
  
	/* Open files */
  Result  = File1.Open(pInput, "rb");
  Result &= File2.Open(pOutput, "rb");
  if (!Result) return (false);

	/* Do filesize check first */
  Size1 = File1.GetFileSize();
  Size2 = File2.GetFileSize();

  if (Size1 < Size2) {
    printf("Failed!\n      The output file is %I64d bytes longer than the input file!\n", Size2 - Size1);
    FailedOutput = true;
   }
  else if (Size1 > Size2) {
    printf("Failed!\n      The input file is %I64d bytes longer than the output file!\n", Size1 - Size2);
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
      printf("      The input file is %I64d bytes longer than the output file!\n", Size1 - Size2);
      return (true);
     }
    else if (InputSize1 < InputSize2) {
      Size1 = File1.GetFileSize();
      Size2 = File2.GetFileSize();
      if (!FailedOutput) printf("Failed!\n");
      printf("      The output file is %I64d bytes longer than the input file!\n", Size2 - Size1);
      return (true);
     }

    //CmpResult = memcmp(Buffer1, Buffer2, InputSize1);
    CmpResult = 1;

    if (CmpResult != 0) {    
      for (Index = 0; Index < InputSize1; ++Index) {
        if (Buffer1[Index] != Buffer2[Index]) {
          if (!FailedOutput) printf("Failed!\n");
          printf ("      Mismatch found at offset 0x%08I64X (0x%02X != 0x%02X)\n", Size1 + Index, (int)Buffer1[Index], (int)Buffer2[Index]);
	  ++MismatchCount;
	  if (MismatchCount > 100) return (true);
         }
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
    printf("      The output file is %I64d bytes longer than the input file!\n", Size2 - Size1);
   }
  else if (!File1.IsEOF() && File2.IsEOF()) {
    Size1 = File1.GetFileSize();
    Size2 = File2.Tell();
    if (!FailedOutput) printf("Failed!\n");
    printf("      The input file is %I64d bytes longer than the output file!\n", Size1 - Size2);
   }

  printf ("Success!\n      Files are an exact match (%I64d bytes)!\n", Size1);
  return (true);
 }
/*===========================================================================
 *		End of Function CompareFiles()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obrecstat_t* GetSubrecordStat (RecordType);
 *
 *=========================================================================*/
obsubrecstat_t* GetSubrecordStat (const obrectype_t RecordType, CObSubrecordStats& SubrecordStats) {
  obsubrecstat_t* pSubrecordStat;
  dword		  Index;

	/* Find an existing statistic record */
  pSubrecordStat = SubrecordStats.Lookup(RecordType.Value);
  if (pSubrecordStat != NULL) return (pSubrecordStat);

	/* Create a new statistic record */
  pSubrecordStat = new obsubrecstat_t;
  //pSubrecordStat->Multiple       = false;
  //pSubrecordStat->Required       = false;
  pSubrecordStat->RecordCount    = 0;
  pSubrecordStat->TotalCount     = 0;
  pSubrecordStat->MaxRecordCount = 0;
  pSubrecordStat->CurRecCount    = 0;
  pSubrecordStat->AlphaCount     = 0;
  pSubrecordStat->NullTermCount  = 0;
  pSubrecordStat->RecordType     = RecordType;
  pSubrecordStat->MinSize        = 0;
  pSubrecordStat->MaxSize        = 0;
  pSubrecordStat->IsFormid       = true;
  pSubrecordStat->pLastRecord    = NULL;
  pSubrecordStat->Sizes.InitHashTable(OB_SUBRECSIZE_HASHMAPSIZE);
  SubrecordStats.SetAt(RecordType.Value, pSubrecordStat);

  for (Index = 0; Index < OB_MAX_FORMID_CHECKSIZE; ++Index) {
    pSubrecordStat->FormidData[Index].Formids.InitHashTable(OB_SUBRECFORMID_HASHMAPSIZE);
    pSubrecordStat->FormidData[Index].IsFormid   = true;
    pSubrecordStat->FormidData[Index].Count      = 0;
    pSubrecordStat->FormidData[Index].TotalCount = 0;
    pSubrecordStat->FormidData[Index].MinFormid  = 0;
    pSubrecordStat->FormidData[Index].MaxFormid  = 0;
  }

  return (pSubrecordStat);
}
/*===========================================================================
 *		End of Function GetRecordStat()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obrecstat_t* GetRecordStat (RecordType);
 *
 *=========================================================================*/
obrecstat_t* GetRecordStat (const obrectype_t RecordType) {
  obrecstat_t* pRecordStat;

	/* Find an existing statistic record */
  pRecordStat = g_RecordStats.Lookup(RecordType.Value);
  if (pRecordStat != NULL) return (pRecordStat);

	/* Create a new statistic record */
  pRecordStat = new obrecstat_t;
  pRecordStat->Count      = 0;
  pRecordStat->RecordType = RecordType;
  pRecordStat->SubrecordStats.InitHashTable(OB_SUBRECORD_HASHMAPSIZE);
  g_RecordStats.SetAt(RecordType.Value, pRecordStat);

  return (pRecordStat);
}
/*===========================================================================
 *		End of Function GetRecordStat()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsAlphaNumData (pData, Size, NullTerm);
 *
 *=========================================================================*/
bool IsAlphaNumData (const byte* pData, const dword Size, bool& NullTerm) {
  dword Index;

  NullTerm = false;
  if (pData == NULL || Size == 0) return (true);

  for (Index = 0; Index < Size - 1; ++Index, ++pData) {
    if (!isprint(*pData)) return (false);
  }

  if (*pData == 0) {
    NullTerm = true;
    return (true);
  }

  if (isprint(*pData)) return (true);
  return (false);
}
/*===========================================================================
 *		End of Function IsAlphaNumData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obsubrecformid_t* GetSubrecFormidData (Type, Formids);
 *
 *=========================================================================*/
obsubrecformid_t* GetSubrecFormidData (const obrectype_t Type, CSubrecordFormids& Formids) {
  obsubrecformid_t* pFormid;

  pFormid = Formids.Lookup(Type.Value);
  if (pFormid != NULL) return (pFormid);

  pFormid = new obsubrecformid_t;
  Formids.SetAt(Type.Value, pFormid);
  pFormid->Count      = 0;
  pFormid->MaxValue   = 0;
  pFormid->MinValue   = 0;
  pFormid->RecordType = Type;

  return (pFormid);
}
/*===========================================================================
 *		End of Function GetSubrecFormidData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CheckFormids (CObSubrecord* pSubrecord, pFormidData);
 *
 *=========================================================================*/
bool CheckFormids (CObSubrecord* pSubrecord, obformiddata_t* pFormidData) {
  obsubrecformid_t* pFormid;
  CObRecord*        pRecord;
  dword		    Index;
  dword             MaxSize = pSubrecord->GetRecordSize() / 4;
  obformid_t        FormID;

  for (Index = 0; Index < OB_MAX_FORMID_CHECKSIZE && Index < MaxSize; ++Index) {
    //if (!pFormidData[Index].IsFormid) continue;
    ++pFormidData[Index].TotalCount;

    FormID = *(obformid_t *) (pSubrecord->GetData() + Index*4);

    if (pFormidData[Index].MaxFormid == 0) {
      pFormidData[Index].MinFormid = FormID;
      pFormidData[Index].MaxFormid = FormID;
    }
    else if (pFormidData[Index].MinFormid > FormID) {
      pFormidData[Index].MinFormid = FormID;
    }
    else if (pFormidData[Index].MaxFormid < FormID) {
      pFormidData[Index].MaxFormid = FormID;
    }
    
    if (FormID == 0) {
      ++pFormidData[Index].Count;
      pFormid = GetSubrecFormidData(OB_NAME_NULL, pFormidData[Index].Formids);
      ++pFormid->Count;
    } 
    else {
      if (pSubrecord->GetRecordType() == OB_NAME_SCRO && FormID == 0x00000014)
        pRecord = g_InputFile.FindFormID(0x07);
      else
        pRecord = g_InputFile.FindFormID(FormID);
   
      if (pRecord == NULL) {
        //if (pSubrecord->GetRecordType() == OB_NAME_SCIT && Index == 0) SystemLog.Printf("%d) SCIT script %08X not found!", pFormidData[Index].TotalCount, FormID);
        //if (pSubrecord->GetRecordType() == OB_NAME_NAM2 && Index == 0) SystemLog.Printf("%d) NAM2 %08X not found!", pFormidData[Index].TotalCount, FormID);
        if (pSubrecord->GetRecordType() == OB_NAME_SCRO && Index == 0) {
          SystemLog.Printf("%d) SCRO %08X not found!", pFormidData[Index].TotalCount, FormID);
        }
        pFormidData[Index].IsFormid = false;
        continue;
      }

    /*
      if (pSubrecord->GetRecordType() == OB_NAME_SCIT && Index == 0) {
        const char* pEditorID = g_InputFile.GetEditorID(FormID);
        SystemLog.Printf("%d) SCIT script %08X = %4.4s (%s)!", pFormidData[Index].TotalCount, FormID, pRecord->GetRecordType().Name, pEditorID);
      } 

      if (pSubrecord->GetRecordType() == OB_NAME_NAM2 && Index == 0) {
        const char* pEditorID = g_InputFile.GetEditorID(FormID);
        SystemLog.Printf("%d) NAM2 %08X = %4.4s (%s)!", pFormidData[Index].TotalCount, FormID, pRecord->GetRecordType().Name, pEditorID);
      } //*/

      ++pFormidData[Index].Count;
      pFormid = GetSubrecFormidData(pRecord->GetRecordType(), pFormidData[Index].Formids);
      ++pFormid->Count;
    }

    if (pFormid->MaxValue == 0) {
      pFormid->MinValue = FormID;
      pFormid->MaxValue = FormID;
    }
    else if (pFormid->MinValue > FormID) {
      pFormid->MinValue = FormID;
    }
    else if (pFormid->MaxValue < FormID) {
      pFormid->MaxValue = FormID;
    }
   
  }

  return (true);
}
/*===========================================================================
 *		End of Function CheckFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddStats (pRecord);
 *
 * Adds stats for the given record and all its subrecords.
 *
 *=========================================================================*/
bool AddStats (CObRecord* pRecord) {
  CObSubrecord*    pSubrecord;
  obrecstat_t*     pRecordStat = GetRecordStat(pRecord->GetRecordType());
  obsubrecstat_t*  pSubrecordStat;
  obsubrecsize_t*  pSize;
  dword		   Size;
  dword	   	   Index;
  bool		   NullTerm;

  ++pRecordStat->Count;

  for (Index = 0; Index < pRecord->GetNumSubrecords(); ++Index) {
    pSubrecord     = pRecord->GetSubrecord(Index);
    pSubrecordStat = GetSubrecordStat(pSubrecord->GetRecordType(), pRecordStat->SubrecordStats);

		/* Update the subrecord counts */
    ++pSubrecordStat->TotalCount;

    if (pSubrecordStat->pLastRecord != pRecord) {
      ++pSubrecordStat->RecordCount;
      pSubrecordStat->pLastRecord = pRecord;
      pSubrecordStat->CurRecCount = 1;
      if (pSubrecordStat->CurRecCount > pSubrecordStat->MaxRecordCount) pSubrecordStat->MaxRecordCount = pSubrecordStat->CurRecCount;
    }
    else {
      ++pSubrecordStat->CurRecCount;
      if (pSubrecordStat->CurRecCount > pSubrecordStat->MaxRecordCount) pSubrecordStat->MaxRecordCount = pSubrecordStat->CurRecCount;
    }

		/* Update the subrecord size counts */
    Size = pSubrecord->GetRecordSize();
    pSize = pSubrecordStat->Sizes.Lookup(Size);
 
    if (pSize) {
      ++pSize->Count;
    }      
    else {
      pSize = new obsubrecsize_t;
      pSize->Size  = Size;
      pSize->Count = 1;
      pSubrecordStat->Sizes.SetAt(Size, pSize);
    }

    if (pSubrecordStat->MaxSize == 0) {
      pSubrecordStat->MaxSize = Size;
      pSubrecordStat->MinSize = Size;
    }
    else if (pSubrecordStat->MinSize > Size) {
      pSubrecordStat->MinSize = Size;
    }
    else if (pSubrecordStat->MaxSize < Size) {
      pSubrecordStat->MaxSize = Size;
    }

		/* Update the subrecord alpha count */
    if (IsAlphaNumData(pSubrecord->GetData(), pSubrecord->GetRecordSize(), NullTerm)) {
      ++pSubrecordStat->AlphaCount;
      if (NullTerm) ++pSubrecordStat->NullTermCount;
      pSubrecordStat->IsFormid = false;
    }

    if (pSubrecordStat->MinSize < 4 && pSubrecordStat->MinSize > 0) pSubrecordStat->IsFormid = false;

		/* Check formids if needed */
    if (pSubrecordStat->IsFormid) {
      CheckFormids(pSubrecord, pSubrecordStat->FormidData);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Function AddStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddStats (pGroup);
 *
 * Adds stats for the given group.
 *
 *=========================================================================*/
bool AddStats (CObGroup* pGroup) {

	/* Do nothing */

  return (true);
}
/*===========================================================================
 *		End of Function AddStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CreateStats (pInputGroup);
 *
 * Create stats for the given group (recursive).
 *
 *=========================================================================*/
bool CreateStats (CObGroup* pInputGroup) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  CObGroup*	 pGroup;
  dword		 Index;

  for (Index = 0; Index < pInputGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pInputGroup->GetRecord(Index);
    pRecord = ObCastRecord(pBaseRecord);

    if (pRecord != NULL) {
      AddStats(pRecord);
      continue;
    }
    
    pGroup = ObCastGroup(pBaseRecord);

    if (pGroup != NULL) {
      AddStats(pGroup);    
      CreateStats(pGroup);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Function CreateStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool CreateStats (void);
 *
 * Create basic stats for the current input file and output to the 
 * system log.
 *
 *=========================================================================*/
bool CreateStats (void) {
  obtimer_t Timer;
  
  ObStartTimer(Timer);
  SystemLog.Printf ("===== Creating stats for file %s...", g_InputFile.GetEspFile().GetShortFilename());

  CreateStats(&g_InputFile.GetEspFile().GetRecords());
  //OutputStats();

  ObEndTimer(Timer, "Created stats in ");

  return (true);
}
/*===========================================================================
 *		End of Function CreateStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OutputSubrecordSizes (Sizes, MinSize, MaxSize);
 *
 * Outputs the given subrecord sizes map to the system log.
 *
 *=========================================================================*/
bool OutputSubrecordSizes (CSubrecordSizes& Sizes, dword& MinSize, dword& MaxSize) {
  MAPPOSITION	  Position;
  obsubrecsize_t* pSize;

  pSize = Sizes.GetFirstRecord(Position);

  if (pSize != NULL && Sizes.GetNumRecords() == 1) {
    SystemLog.Printf("          Always %u bytes", pSize->Size);
    return (true);
  }
  
  SystemLog.Printf("          %u Subrecord Sizes", Sizes.GetNumRecords());

  if ( Sizes.GetNumRecords() < OB_MAX_SUBRECORD_SIZES) {
    while (pSize != NULL) {
      SystemLog.Printf("               %u bytes = %u", pSize->Size, pSize->Count);
      pSize = Sizes.GetNextRecord(Position);
    }
  }

  SystemLog.Printf("               Size Range %u to %u", MinSize, MaxSize);
  return (true);
}
/*===========================================================================
 *		End of Function OutputSubrecordSizes()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OutputSubrecordFormids (pFormidData);
 *
 *=========================================================================*/
bool OutputSubrecordFormids (obformiddata_t* pFormidData, const dword MaxSize, const dword TotalCount) {
  MAPPOSITION       Position;
  obsubrecformid_t* pFormid;
  dword		    Index;

  for (Index = 0; Index < OB_MAX_FORMID_CHECKSIZE && Index < MaxSize/4; ++Index) {
    //if (!pFormidData[Index].IsFormid) continue;
    if (pFormidData[Index].Count == 0) continue;

    if (pFormidData[Index].Count == TotalCount)
      SystemLog.Printf("               Formid #%u (always) (values %X to %X)", Index, pFormidData[Index].MinFormid, pFormidData[Index].MaxFormid);
    else
      SystemLog.Printf("               Formid #%u found %u of %u (values %X to %X)", Index, pFormidData[Index].Count, pFormidData[Index].TotalCount, pFormidData[Index].MinFormid, pFormidData[Index].MaxFormid);

    pFormid = pFormidData[Index].Formids.GetFirstRecord(Position);

    if (pFormid != NULL && pFormid->Count == pFormidData[Index].Count) {
      SystemLog.Printf("                    %4.4s (always) (values %X to %X)", pFormid->RecordType.Name, pFormid->MinValue, pFormid->MaxValue);
      continue;
    }

    while (pFormid != NULL) {
      SystemLog.Printf("                    %4.4s = %u (values %X to %X)", pFormid->RecordType.Name, pFormid->Count, pFormid->MinValue, pFormid->MaxValue);
      pFormid = pFormidData[Index].Formids.GetNextRecord(Position);
    }    
  }

  return (true);
}
/*===========================================================================
 *		End of Function OutputSubrecordFormids()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OutputSubrecordStats (pRecordStat);
 *
 * Outputs subrecord stats for the given record to the system log.
 *
 *=========================================================================*/
bool OutputSubrecordStats (obrecstat_t& RecordStat) {
  MAPPOSITION     Position;
  obsubrecstat_t* pSubrecordStat;
  bool		  Required;
  bool		  Multiple;
  bool		  OnlyAlpha;
  bool		  NullTerm;
  dword		  MinSize;
  dword		  MaxSize;

  pSubrecordStat = RecordStat.SubrecordStats.GetFirstRecord(Position);

  while (pSubrecordStat != NULL) {
    Required  = (pSubrecordStat->RecordCount == RecordStat.Count);
    Multiple  = (pSubrecordStat->MaxRecordCount > 1);
    OnlyAlpha = (pSubrecordStat->AlphaCount == pSubrecordStat->TotalCount);
    NullTerm  = (pSubrecordStat->AlphaCount == pSubrecordStat->NullTermCount) && (pSubrecordStat->NullTermCount > 0);

    SystemLog.Printf("     == %4.4s ==", pSubrecordStat->RecordType.Name);
    SystemLog.Printf("          TotalCount = %u", pSubrecordStat->TotalCount);
    SystemLog.Printf("          Required   = %s", Required  ? "Yes" : "No");
    SystemLog.Printf("          Multiple   = %s", Multiple  ? "Yes" : "No");
    SystemLog.Printf("          Text       = %s%s", OnlyAlpha ? "Yes" : "No", NullTerm ? " (always null terminated)" : "");
    SystemLog.Printf("          MaxCount   = %u", pSubrecordStat->MaxRecordCount);
    //SystemLog.Printf("          HasFormid  = %s", pSubrecordStat->IsFormid ? "Maybe" : "No");
    //if (pSubrecordStat->IsFormid) 
    if (!OnlyAlpha) {
      OutputSubrecordFormids(pSubrecordStat->FormidData, pSubrecordStat->MaxSize, pSubrecordStat->TotalCount);
    }
    //SystemLog.Printf("          AlphaCount = %u", pSubrecordStat->AlphaCount);
    //SystemLog.Printf("          NullTerm   = %u", pSubrecordStat->NullTermCount);
    MinSize = pSubrecordStat->MinSize;
    MaxSize = pSubrecordStat->MaxSize;

    if (!OnlyAlpha) {
      OutputSubrecordSizes(pSubrecordStat->Sizes, MinSize, MaxSize);
    }
    
    if (OnlyAlpha) {
      if (g_MaxAlphaSubrecordSize == 0) {
	g_MinAlphaSubrecordSize = MinSize;
        g_MaxAlphaSubrecordSize = MaxSize;
      }
      else if (g_MinAlphaSubrecordSize > MinSize) {
        g_MinAlphaSubrecordSize = MinSize;
      }
      else if (g_MaxAlphaSubrecordSize < MaxSize) {
        g_MaxAlphaSubrecordSize = MaxSize;
      }
    }
    else {
       if (g_MaxBinarySubrecordSize == 0) {
	g_MinBinarySubrecordSize = MinSize;
        g_MaxBinarySubrecordSize = MaxSize;
      }
      else if (g_MinBinarySubrecordSize > MinSize) {
        g_MinBinarySubrecordSize = MinSize;
      }
      else if (g_MaxBinarySubrecordSize < MaxSize) {
        g_MaxBinarySubrecordSize = MaxSize;
      }
    }
   
    pSubrecordStat = RecordStat.SubrecordStats.GetNextRecord(Position);
  }

  return (true);
}
/*===========================================================================
 *		End of Function OutputSubrecordStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool OutputStats (void);
 *
 * Outputs the current stats to the system log.
 *
 *=========================================================================*/
bool OutputStats (void) {
  MAPPOSITION  Position;
  obrecstat_t* pRecordStat;

  pRecordStat = g_RecordStats.GetFirstRecord(Position);

  while (pRecordStat != NULL) {

    SystemLog.Printf("===== %4.4s =====", pRecordStat->RecordType.Name);
    SystemLog.Printf("     Occurred = %u", pRecordStat->Count);
    OutputSubrecordStats(*pRecordStat);

    pRecordStat = g_RecordStats.GetNextRecord(Position);
  }

  SystemLog.Printf("Subrecord text sizes %u to %u", g_MinAlphaSubrecordSize, g_MaxAlphaSubrecordSize);
  SystemLog.Printf("Subrecord binary sizes %u to %u", g_MinBinarySubrecordSize, g_MaxBinarySubrecordSize);
  return (true);
}
/*===========================================================================
 *		End of Function OutputStats()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool DoCompare (void);
 *
 * Main comparison function. Returns false on any error.
 *
 *=========================================================================*/
bool DoCompare (void) {
  LARGE_INTEGER StartTime;
  LARGE_INTEGER EndTime;
  LARGE_INTEGER Frequency;
  bool		Result;
  DWORD		WinResult;

  WinResult = QueryPerformanceFrequency(&Frequency);

  	/* Attempt to open and load the mod file */
  printf ("   Loading '%s'...", g_InputFilename.c_str());

  WinResult = QueryPerformanceCounter(&StartTime);
  Result = g_InputFile.Load(g_InputFilename);
  WinResult = QueryPerformanceCounter(&EndTime);
  g_LoadTime = (double) (EndTime.QuadPart - StartTime.QuadPart) / (double) (Frequency.QuadPart); 

  printf ("%s (%.3f sec)!\n", Result ? "Success" : "Failed", g_LoadTime);
  if (!Result) return (false);

  if (g_DoStats) {
    printf ("   Creating stats...\n");
    CreateStats();
    printf ("   Outputting stats...\n");
    OutputStats();
    return (true);
  } 
  
	/* Attempt to save the mod file */
  printf ("   Saving '%s'...", g_OutputFilename.c_str());

  //g_InputFile.AddNewRecord(OB_NAME_AMMO);

  WinResult = QueryPerformanceCounter(&StartTime);
  Result = g_InputFile.GetEspFile().Save(g_OutputFilename);
  WinResult = QueryPerformanceCounter(&EndTime);
  g_SaveTime = (double) (EndTime.QuadPart - StartTime.QuadPart) / (double) (Frequency.QuadPart); 

  printf ("%s (%.3f sec)!\n", Result ? "Success" : "Failed", g_SaveTime);
  if (!Result) return (false);

/*	// Test to make sure the file comparison works
  CObFile File;

  if (File.Open(g_OutputFilename, "wb")) {
    File.Seek(201000000);
    File.WriteDWord(0x12345678);
    File.Close();
   } //*/

	/* Compare the two files */
  printf ("   Comparing files...");
  Result = CompareFiles(g_InputFilename, g_OutputFilename);
  if (!Result) return (false);
  
  return (true);
 }
/*===========================================================================
 *		End of Function DoCompare()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Main Program
 *
 *=========================================================================*/
int main (int argc, char* argv[]) {
  bool Result;

  g_RecordStats.InitHashTable(OB_RECORD_HASHMAPSIZE);

	/* Output simple title */
  printf ("ObTestFile - Loads and saves a given ESP/ESM file and confirms the two match.\n");
  SystemLog.Open("obtestfile.log");

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
  Result = DoCompare();
  if (!Result) return DisplayError();

  return (0);
 }
/*===========================================================================
 *		End of Main Program
 *=========================================================================*/
