/*===========================================================================
 *
 * File:	ObLibtest.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 28, 2006
 *
 * Used to test the operation of the library builds.
 *
 *=========================================================================*/

	/* Include Files */
#include "../tes4lib/tes4lib.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

  CObMultiRecordHandler		g_MultiHandler;
  CObSimpleRecordHandler	g_SimpleHandler;
  CObEspFile			g_EspFile;

  
	/* Input buffer used when comparing files (bigger is faster) */
  const dword BUFFER_SIZE = 1256000;

	/* Command line parameters */
  CSString	g_InputFilename;
  CSString	g_OutputFilename;
  bool		g_OverwriteOutput = false;

	/* File for input and output */
  //CObEspFile	g_InputFile;
  CObSimpleRecordHandler	g_InputFile;

	/* Temporary buffers */
  byte		Buffer1[BUFFER_SIZE + 64];
  byte		Buffer2[BUFFER_SIZE + 64];

	/* Times in seconds */
  double	g_LoadTime;	
  double	g_SaveTime;

/*===========================================================================
 *		End of Local Definitions
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
  printf("    ObLibTest [inputfile] [outputfile] [/o] [/m]\n");
  printf("        [inputfile]  - Existing ESP/ESM file to load\n");
  printf("        [outputfile] - File to save. If omitted inputfile.tmp will be used.\n");
  printf("        [/o]         - Overwrite output file. If omitted the test will abort\n");
  printf("                       if the output file already exists.\n");
  printf("        [/m]         - Use the Oblivion.esm file in the current Oblivion\n");
  printf("                       install path as the input file.\n");
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
 * Function - bool DoCompare (void);
 *
 * Main comparison function. Returns false on any error.
 *
 *=========================================================================*/
bool DoCompare (void) {
  obtimer_t Timer;
  bool	    Result;
  
  	/* Attempt to open and load the mod file */
  printf ("   Loading '%s'...", g_InputFilename.c_str());

  ObStartTimer(Timer);
  Result = g_InputFile.Load(g_InputFilename);
  g_LoadTime = ObEndTimer(Timer);

  printf ("%s (%.3f sec)!\n", Result ? "Success" : "Failed", g_LoadTime);
  if (!Result) return (false);

	/* Attempt to save the mod file */
  printf ("   Saving '%s'...", g_OutputFilename.c_str());

  ObStartTimer(Timer);
  Result = g_InputFile.GetEspFile().Save(g_OutputFilename);
  g_SaveTime = ObEndTimer(Timer);

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

	/* Output simple title */
  printf ("ObLibTest - Loads and saves a given ESP/ESM file and confirms the two match.\n");
  printf ("            Uses the library version of Tes4Lib.\n");
  SystemLog.Open("oblibtest.log");

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
