/*===========================================================================
 *
 * File:	Bsatestfile.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "bsafile/obbsafile.h"


/*===========================================================================
 *
 * Function - bool CompareFiles (pInput, pOutput);
 *
 *=========================================================================*/
bool CompareFiles (const SSCHAR* pInput, const SSCHAR* pOutput) {
  const int BUFFER_SIZE = 100000;
  static byte Buffer1[BUFFER_SIZE];
  static byte Buffer2[BUFFER_SIZE];
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
          printf ("      Mismatch found at offset 0x%08I64X (0x%02X != 0x%02X)\n", Size1 + Index, (dword)Buffer1[Index], (dword)Buffer2[Index]);
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
 * Function - bool TestBsaFile (pFilename);
 *
 *=========================================================================*/
bool TestBsaFile (const char* pFilename) {
  CObBsaFile BsaFile;
  CSString   Buffer;
  bool       Result;

  printf("\tLoading '%s'...\n", pFilename);

  Result = BsaFile.Load(pFilename);
  if (!Result) return AddObGeneralError("Failed to load BSA file '%s'!", pFilename);

  Buffer  = pFilename;
  Buffer += ".tmp";

  printf("\tSaving '%s'...\n", Buffer);
  Result = BsaFile.Save(Buffer);
  if (!Result) return AddObGeneralError("Failed to save BSA file '%s'!", Buffer.c_str());

  printf("\tComparing files...\n", Buffer);
  Result = CompareFiles(pFilename, Buffer);
  
  return (true);
}
/*===========================================================================
 *		End of Function TestBsaFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Main Program
 *
 *=========================================================================*/
int main (int argc, char* argv[]) {
  bool Result;

  SystemLog.Open("bsatestfile.log");

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Misc.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Meshes.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Sounds.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Textures - Compressed.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Voices1.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  Result = TestBsaFile("h:\\oblivion\\data\\Oblivion - Voices2.bsa");
  if (!Result) printf("\t%s\n", ObErrorHandler->GetLastError()->GetErrorMessage());

  return (0);
}
/*===========================================================================
 *		End of Main Program
 *=========================================================================*/
