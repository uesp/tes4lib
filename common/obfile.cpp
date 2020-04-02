/*===========================================================================
 *
 * File:	ObFile.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 5, 2006
 *
 * Implements the CObFile class for handling basic file I/O. The main purpose
 * of this class is to handle low-level I/O operations along with basic
 * error handling conditions. This greatly simplifies the higher level code
 * that uses it as it just has to know an operation failed.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdlib.h"
#include "stdio.h"
#include "obfile.h"
#include "oblogfile.h"
#include "direct.h"
#include "windows.h"
#include "io.h"


/*===========================================================================
 *
 * Class CObFile Constructor
 *
 *=========================================================================*/
CObFile::CObFile () {
  m_pFile     = NULL;
  m_LineCount = 0;
}
/*===========================================================================
 *		End of Class CObFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Destructor
 *
 *=========================================================================*/
CObFile::~CObFile () {

	/* Ensure the file is closed */
  Close();

}
/*===========================================================================
 *		End of Class CObFile Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - void Destroy (void);
 *
 * Delete class contents.
 *
 *=========================================================================*/
void CObFile::Destroy (void) {

	/* Close file if open */
  Close();

  m_Filename.Empty();
}
/*===========================================================================
 *		End of Class Method CObFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - void Close (void);
 *
 * Closes the file if currently open. Ignores if not open.
 *
 *=========================================================================*/
void CObFile::Close (void) {

	/* Close handle if in use */
  if (m_pFile != NULL) {
    fclose(m_pFile);
    m_pFile = NULL;
    m_Filename.Empty();
   }

 m_LineCount = 0;
}
/*===========================================================================
 *		End of Class Method CObFile::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool GetFileSize (Size);
 *
 *=========================================================================*/
bool CObFile::GetFileSize (int& Size) {
  long OldOffset;
  long Offset;
  long Result;

  OldOffset = ftell(m_pFile);
  if (OldOffset < 0) return AddObSystemError("Failed to read file position!");

  Result = fseek(m_pFile, 0, SEEK_END);
  Offset = ftell(m_pFile);
  
  Result |= fseek(m_pFile, OldOffset, SEEK_SET);
  if (Offset  < 0) return AddObSystemError("Failed to get file position!");
  if (Result != 0) return AddObSystemError("Failed to reset file position!");

  Size = (dword) Offset;
  return (true);
 }


int CObFile::GetFileSize (void) {
  int Result;
  GetFileSize(Result);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObFile::GetFileSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool GetFileSize64 (Size);
 *
 *=========================================================================*/
bool CObFile::GetFileSize64 (int64& Size) {
  long  OldOffset;
  int64 Offset;
  int64 Result;

  Size = 0;
  OldOffset = ftell(m_pFile);
  if (OldOffset < 0) return AddObSystemError("Failed to read file position!");

  Result = _lseeki64(fileno(m_pFile), 0, SEEK_END);
  if (Result < 0) return AddObSystemError("Failed to move file position!");

  Offset = _telli64(fileno(m_pFile));  
  if (Offset < 0) return AddObSystemError("Failed to get file position!");
  
  Result = fseek(m_pFile, OldOffset, SEEK_SET);
  if (Result != 0) return AddObSystemError("Failed to reset file position!");
  
  Size = Offset;
  return (true);
 }


int64 CObFile::GetFileSize64 (void) {
  int64 Result;
  GetFileSize64(Result);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObFile::GetFileSize64()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObFile Method - bool IsOpen (void) const;
 *
 * Returns true if the file is currently open.
 *
 *=========================================================================*/
bool CObFile::IsOpen (void) const {
  return (m_pFile != NULL);
 }
/*===========================================================================
 *		End of Class Method CObFile::IsOpen()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Open (pFilename, pFileMode);
 *
 * Attempts to open a file for input or output. The current file is closed
 * if open. Returns false on any error and updates the global error handler.
 * Invalid input is ignored.
 *
 *=========================================================================*/
bool CObFile::Open (const SSCHAR* pFilename, const SSCHAR* pFileMode) {

	/* Close the current if required */
  if (IsOpen()) Close();

	/* Ignore invalid input */
  if (pFilename == NULL) return AddObUserError(OBERR_USER_NULL, "Input filename cannot be NULL!");
  if (pFileMode == NULL) return AddObUserError(OBERR_USER_NULL, "Input file mode cannot be NULL!");

  SystemLog.Printf("Opening '%s' in mode '%s'...", pFilename, pFileMode);

	/* Attempt to open the file */
  m_pFile = fopen(pFilename, pFileMode);
  if (m_pFile == NULL) return AddObSystemError("Failed to open the file '%s' in mode '%s'!", pFilename, pFileMode);

  m_Filename = pFilename;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Open()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Printf (pString, ...);
 *
 *=========================================================================*/
bool CObFile::Printf  (const SSCHAR* pString, ...) {
  va_list Args;
  bool    Result;

  va_start(Args, pString);
  Result = VPrintf(pString, Args);
  va_end(Args);

  return (Result);
 }


bool CObFile::VPrintf (const SSCHAR* pString, va_list Args) {
  int Result;

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  Result = vfprintf(m_pFile, pString, Args);
  if (Result < 0) return AddObSystemError("Failed to output formatted string to file!");

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Printf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Read (pBuffer, Size);
 *
 * Attempts to input a buffer of raw data from the file. Returns false
 * on any error.
 *
 *=========================================================================*/
bool CObFile::Read (void* pBuffer, const int Size, dword& InputBytes) { 
  size_t Result;
  size_t uSize = (size_t) Size;

  InputBytes = 0;

	/* Check valid input and state */
  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (Size == 0) return (true);
  if (pBuffer == NULL) return AddObUserError(OBERR_USER_NULL, "File input buffer cannot be NULL!");
  if (Size < 0) return AddObUserError(OBERR_USER_BADINPUT, "File input buffer size must be positive!");

	/* Check for overflows */
  if ((int)uSize != Size) return AddObUserError(OBERR_USER_OVERFLOW, "Requested file input was too large!");

	/* Attempt to input buffer */
  Result = fread(pBuffer, 1, uSize, m_pFile);
  InputBytes = (dword) Result;
  if (Result != uSize) return AddObSystemError("Failed to read data from file! Only %u of %d bytes input.", Result, Size);
  return (true);
 }


bool CObFile::Read (void* pBuffer, const int Size) {
  size_t Result;
  size_t uSize = (size_t) Size;

	/* Check valid input and state */
  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (Size == 0) return (true);
  if (pBuffer == NULL) {
    return AddObUserError(OBERR_USER_NULL, "File input buffer cannot be NULL!");
  }
  if (Size < 0) return AddObUserError(OBERR_USER_BADINPUT, "File input buffer size must be positive!");

	/* Check for overflows */
  if ((int)uSize != Size) return AddObUserError(OBERR_USER_OVERFLOW, "Requested file input was too large!");

	/* Attempt to input buffer */
  Result = fread(pBuffer, 1, uSize, m_pFile);

  if (Result != uSize) {

    if (HasError())
      return AddObSystemError("Failed to read data from file! Only %u of %d bytes input.", Result, Size);
    else 
      return AddObUserError(OBERR_USER_EOF);
   }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool ReadLine (Buffer);
 *
 * Inputs a line of text from a text file.
 *
 *=========================================================================*/
bool CObFile::ReadLine (CSString& Buffer) {
  byte    Value;
  size_t  Result;
  //SSCHAR  TempBuffer[256];
  //SSCHAR* pResult;

	/* Set some initial string size */
  Buffer.SetSizeEmpty(64);
  //Buffer.Empty();

  while (!IsEOF()) {
 
     		/* Attempt to input buffer */
    Result = fread(&Value, 1, 1, m_pFile);

    if (Result != 1) {
      if (HasError()) return AddObSystemError("Failed to read byte from file!");
      return (true);
    }

    if (Value == '\n') {
      ++m_LineCount;
      return (true);
     }
    else {
      Buffer += Value;
     }
   }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObFile::ReadLine()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Seek (Offset);
 *
 * Description
 *
 *=========================================================================*/
bool CObFile::Seek (const int Offset) {
  int Result;

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  Result = fseek(m_pFile, (long)Offset, SEEK_SET);
  if (Result) return AddObSystemError("Failed to set the absolute file position to %lu!", Offset);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Seek()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool SeekCur (Offset);
 *
 *=========================================================================*/
bool CObFile::SeekCur (const int Offset) {
  int Result;

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  Result = fseek(m_pFile, (long)Offset, SEEK_CUR);
  if (Result) return AddObSystemError("Failed to set the relative file position to %lu!", Offset);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::SeekCur()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Seek64 (Offset);
 *
 *=========================================================================*/
bool CObFile::Seek64 (const int64 Offset) {
  int64 Result;

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  //fseek(m_pFile, (long)Offset, SEEK_SET);
  fflush(m_pFile);

  Result = _lseeki64(fileno(m_pFile), Offset, SEEK_SET);
  if (Result < 0) return AddObSystemError("Failed to set the file position to %I64d!", Offset);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Seek64()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Tell (Offset);
 *
 * Read the current file position.
 *
 *=========================================================================*/
bool CObFile::Tell (int& Offset) {
  long Result;

	/* Check valid object state */
  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  Result = ftell(m_pFile);
  if (Result < 0) return AddObSystemError("Failed to get current file position!");

  Offset = (dword)Result;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Tell()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Tell64 (Offset);
 *
 * Read the current file position.
 *
 *=========================================================================*/
bool CObFile::Tell64 (int64& Offset) {

	/* Check valid object state */
  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);

  //ftell(m_pFile);
  //fflush(m_pFile);

  Offset = _telli64(fileno(m_pFile));
  if (Offset < 0) return AddObSystemError("Failed to get current file position!");

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::\()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - int64 Tell64 (void);
 *
 * Read the current file position.
 *
 *=========================================================================*/
int64 CObFile::Tell64 (void) {
  int64 Offset;

  if (!Tell64(Offset)) return (0);
  return (Offset);
 }
/*===========================================================================
 *		End of Class Method CObFile::Tell64()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFile Method - bool Write (pBuffer, Size);
 *
 * Attempts to output a buffer of raw bytes to the file. Returns false
 * on any error.
 *
 *=========================================================================*/
bool CObFile::Write (const void* pBuffer, const int Size) {
  size_t Result;
  size_t uSize = (size_t) Size;

	/* Check valid input and state */
  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (Size == 0) return (true);
  if (pBuffer == NULL) return AddObUserError(OBERR_USER_NULL, "File output buffer cannot be NULL!");
  if (Size < 0) return AddObUserError(OBERR_USER_BADINPUT, "File output buffer size must be positive!");

	/* Check for overflows */
  if ((int)uSize != Size) return AddObUserError(OBERR_USER_OVERFLOW, "Requested file output was too large!");

	/* Attempt to output buffer */
  Result = fwrite(pBuffer, 1, uSize, m_pFile);
  if (Result != uSize) return AddObSystemError("Failed to write data to file! Only %u of %d bytes output.", Result, Size);

  fflush(m_pFile);
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFile::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObFileExists (pFilename);
 *
 * Simple check if a file already exists. Returns true if it exists and
 * false otherwise.
 *
 *=========================================================================*/
bool ObFileExists (const SSCHAR* pFilename) {
  FILE* pFile;

  pFile = fopen(pFilename, "rb");
  if (pFile == NULL) return (false);

  fclose(pFile);
  return (true);
 }
/*===========================================================================
 *		End of Function ObFileExists()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCheckExtension (pFilename, pExt);
 *
 * Returns true if the given file has the given extension (without the
 * leading period).
 *
 *=========================================================================*/
bool ObCheckExtension (const SSCHAR* pFilename, const SSCHAR* pExt) {
  int Index;

	/* Ensure valid input */
  if (pFilename == NULL || pExt == NULL) return (false);
  Index = (int) strlen(pFilename);

	/* Find the trailing file extension */
  while (Index >= 0) {
    switch (pFilename[Index]) {
      case '.': return (stricmp(pFilename + Index + 1, pExt) == 0);
      case '\\':
      case ':':
	return (false);
     }

    --Index;
   }

  return (false);
 }
/*===========================================================================
 *		End of Function ObCheckExtension()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool MakePathEx (pPath);
 *
 * Creates multiple levels of paths. Returns false on any error.
 *
 *=========================================================================*/
bool MakePathEx (const SSCHAR* pPath) {
  SSCHAR  TempPath[_MAX_PATH+1];
  SSCHAR  TempDrive[8] = "c:\\";
  SSCHAR  InitialPath[_MAX_PATH+1];
  SSCHAR* pParse;
  int     iResult;

	/* Ignore invalid input */
  if (pPath == NULL) return (false);
  strnncpy(TempPath, pPath, _MAX_PATH);
  
	/* Save the initial directory */
  _getcwd(InitialPath, _MAX_PATH - 2);
  TerminatePath(InitialPath);
  pParse = strtok(TempPath, "\\");

  while (pParse != NULL && *pParse != NULL_CHAR) {

    		/* Does the given directory/drive exist? */
    if (pParse[1] == ':') {
      TempDrive[0] = pParse[0];
      iResult = _chdir(TempDrive);
    }
    else {
      iResult = _chdir(pParse);
    }

		/* Attempt to make the given directory */
    if (iResult != 0) {
      iResult = _mkdir(pParse);
      
      if (iResult < 0) {
        AddObGeneralError("Failed to create the directory '%s'!", pParse);
	return (false);
      }

      iResult = _chdir(pParse);      
      if (iResult != 0) return (false);
    }

    pParse = strtok(NULL, "\\");
  }

	/* Restore the initial path and return success */
  _chdir(InitialPath);
  return (true);
}
/*===========================================================================
 *		End of Function MakePathEx()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - TCHAR* TerminatePath (TCHAR* pPath);
 *
 * Ensures the given path string terminates in the current LocalPathChar
 * character.  Returns a pointer to the given string.  ASSERTs if the 
 * input string is invalid.  Assumes that the string has been allocated
 * to allow an additional TCHARacter to be added to it.
 *
 *=========================================================================*/
SSCHAR* TerminatePath (SSCHAR* pPath) {
  size_t PathLength;

	/* Ensure the input path is valid */
  if (pPath == NULL) return (NULL);
  PathLength = strlen(pPath);

	/* Ensure the string ends in the current path character */
  if (PathLength != 0 && pPath[PathLength-1] != '\\') {
    pPath[PathLength]   = '\\';
    pPath[PathLength+1] = NULL_CHAR;
   }

  return (pPath);
 }
/*===========================================================================
 *		End of Function TerminatePath()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const SSCHAR* TerminatePath (Path);
 *
 *=========================================================================*/
const SSCHAR* TerminatePath (CSString& Path) {

	/* Ensure the input path is valid */
  if (Path.IsEmpty()) return Path.c_str();
  
	/* Ensure the string ends in the current path character */
  if (Path[Path.GetLength() - 1] != '\\') {
    Path += '\\';
  }

  return Path.c_str();
}
/*===========================================================================
 *		End of Function TerminatePath()
 *=========================================================================*/


/*=========================================================================
 *
 * Function - bool FileExists (pFilename);
 *
 * Returns TRUE if the specified file exists and can be opened for 
 * reading. 
 *
 *=======================================================================*/
bool FileExists (const SSCHAR* pFilename) {
  FILE* pFileHandle;

	/* Ensure valid input */
  if (pFilename == NULL) return (false);

	/* Test for empty string (prevents _wfopen() from asserting in UNICODE debug builds */
  if (pFilename[0] == NULL_CHAR) return (false);

	/* Attempt to open file for reading */
  pFileHandle = fopen(pFilename, "r");
  if (pFileHandle == NULL) return(false);

	/* File was opened and therefore exists, close and return success */
  fclose(pFileHandle);
  return(true);
 }
/*=========================================================================
 *		End of Function FileExists()
 *=======================================================================*/

 
/*===========================================================================
 *
 * Function - int64 GetFileSize (pFilename);
 *
 * Returns the size of the give filename.  Returns -1 on any error and
 * sets the appropiate error code. 
 *
 *=========================================================================*/
int64 GetFileSize (const char* pFilename) {
  //DEFINE_FUNCTION("GetFileSize(TCHAR*)");
  int64 FileSize;
  bool  Result;

  Result = GetFileSize(FileSize, pFilename);
  if (!Result) return (-1);
  return (FileSize);
 }
/*===========================================================================
 *		End of Function GetFileSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool GetFileSize (FileSize, pFilename);
 *
 * Attempts to retrieve the size in bytes of the given filename. Returns
 * FALSE on any error (setting the appropiate error), or TRUE on success.
 *
 *=========================================================================*/
bool GetFileSize (int64& FileSize, const char* pFilename) {
  FILE*  pFileHandle;
  int    Result;

	/* Ensure valid input */
  FileSize = 0;
  if (pFilename != NULL || *pFilename == NULL_CHAR) return (false);

  pFileHandle = fopen(pFilename, "rb");

  if (pFileHandle == NULL) {
    AddObSystemError("Could not open the file '%s'!", pFilename);
    return (false);
   }

  Result = fseek(pFileHandle, 0, SEEK_END);

  if (Result) {
    FileSize = _telli64(fileno(pFileHandle));

    if (FileSize < 0) {
      FileSize = 0;
      Result   = 0;
    }
  }

  fclose (pFileHandle);
  return (Result != 0);
 }
/*===========================================================================
 *		End of Function GetFileSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool GetFileInfo (pFilename, Filesize, Filetime);
 *
 *=========================================================================*/
bool GetFileInfo (const char* pFilename, int64& Filesize, dword64& Filetime) {
  HANDLE   hFile;
  DWORD	   Size;
  FILETIME WriteTime;
  DWORD    Result;
  bool	   ReturnResult = true;

  Filesize = 0;
  Filetime = 0;
  if (pFilename == NULL) return (false);

	/* Attempt to open file */  
  hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

  if (hFile == INVALID_HANDLE_VALUE) {
    return (false);
  }

	/* Get filesize */
  Result = GetFileSize(hFile, &Size);

  if (!(Result == -1 && GetLastError() != NO_ERROR)) {
    Filesize = (int64)(((unsigned __int64) Result) | (((unsigned __int64) Size) << 32));
  }
  else {
    ReturnResult = false;
  }

  Result = GetFileTime(hFile, NULL, NULL, &WriteTime);

  if (Result) {
    Filetime = ((dword64)WriteTime.dwLowDateTime | (((dword64) WriteTime.dwHighDateTime) << 32));
  }
  else {
    ReturnResult = false;
  }

  CloseHandle(hFile);
  return (ReturnResult);
}
/*===========================================================================
 *		End of Function GetFileInfo()
 *=========================================================================*/