/*===========================================================================
 *
 * File:	Obbsafilerecord.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbsafilerecord.h"
#include "obbsafolder.h"
#include "obbsafile.h"
#include "../common/zlib/zlib.h"


/*===========================================================================
 *
 * Class CObBsaFileRecord Constructor
 *
 *=========================================================================*/
CObBsaFileRecord::CObBsaFileRecord() {
  m_Header.NameHash = 0;
  m_Header.Filesize = 0;
  m_Header.Offset   = 0;
  m_InputOffset     = 0;

  m_pFolder  = NULL;
  m_Filesize = 0;
  m_Flags    = 0;
}
/*===========================================================================
 *		End of Class CObBsaFileRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBsaFileRecord::Destroy (void) {
  m_Header.NameHash = 0;
  m_Header.Filesize = 0;
  m_Header.Offset   = 0;
  m_InputOffset     = 0;

  m_pFolder  = NULL;
  m_Filesize = 0;
  m_Flags    = 0;

  m_Filename.Empty();
  m_TmpFilename.Empty();
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - CObBsaFile* GetParentFile (void);
 *
 *=========================================================================*/
CObBsaFile* CObBsaFileRecord::GetParentFile (void) {
  if (m_pFolder == NULL) return (NULL);
  return (m_pFolder->GetBsaFile()); 
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::GetParentFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - uint64 GetFiletime (void);
 *
 *=========================================================================*/
dword64 CObBsaFileRecord::GetFiletime (void) {
  if (m_pFolder == NULL) return (0);
  return (m_pFolder->GetFiletime());
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::GetFiletime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObBsaFileRecord Method - const GetFullFilename (void);
 *
 *=========================================================================*/
const char* CObBsaFileRecord::GetFullFilename (void) {
  static CSString s_Buffer;

  if (m_pFolder == NULL) return GetFilename();

  s_Buffer = m_pFolder->GetFolderName();

  if (s_Buffer.GetLength() > 0 && s_Buffer[s_Buffer.GetLength() - 1] != '\\') {
    s_Buffer += "\\";
  }

  s_Buffer += m_Filename;
  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObBsaFileRecord::GetFullFilename()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObBsaFileRecord Method - const GetFullPath (void);
 *
 *=========================================================================*/
const char* CObBsaFileRecord::GetFullPath (void) {
  static CSString s_Buffer;
  if (m_pFolder == NULL) return ("");

  s_Buffer = m_pFolder->GetFolderName();
  if (!s_Buffer.IsEmpty()) s_Buffer += '\\';

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObBsaFileRecord::GetFullPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool IsCompressed (void);
 *
 *=========================================================================*/
bool CObBsaFileRecord::IsCompressed (void) {
  bool CompressFlag = false;

  if (m_pFolder != NULL && m_pFolder->GetBsaFile() != NULL) {
    CompressFlag = m_pFolder->GetBsaFile()->IsCompressed();
  }

  if (CompressFlag) return !IsCompressToggle();
  return IsCompressToggle();
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::IsCompressed()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool ReadHeader (File);
 *
 *=========================================================================*/
bool CObBsaFileRecord::ReadHeader (CObFile& File) {
  return File.Read((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::ReadHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool Read (File);
 *
 *=========================================================================*/
bool CObBsaFileRecord::Read (CObFile& File) { 
  bool Result;

  //SystemLog.Printf("\t\tRead BsaRecord: 0x%08I64X", File.Tell64());
  
  Result = ReadHeader(File);
  if (!Result) return (false);

  m_InputOffset = m_Header.Offset;
  m_Filesize    = m_Header.Filesize & OB_BSAFILEREC_SIZEMASK;
  m_Flags       = m_Header.Filesize & OB_BSAFILEREC_FLAGMASK;

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool MakeTempFilename (OutputFilename, pTempPath);
 *
 *=========================================================================*/
bool CObBsaFileRecord::MakeTempFilename (CSString& OutputFilename, const char* pTempPath) {
  char     Buffer[512];
  char     BareFilename[_MAX_FNAME + 8];
  char     Extension[_MAX_EXT + 8];
  CSString FullPath(GetFullPath());
  int      Index = 1;
 
  _splitpath(GetFilename(), NULL, NULL, BareFilename, Extension);

	/* Try the default */
  _snprintf(Buffer, 500, "%s%s%s%s", pTempPath, FullPath, BareFilename, Extension);
  Index = 0;

  while (FileExists(Buffer)) {
    ++Index;
    _snprintf(Buffer, 500, "%s%s%s%d%s", pTempPath, FullPath, BareFilename, Index, Extension);

    if (Index > 100000) {
      OutputFilename.Empty();
      return (false);
    }
  }

  OutputFilename = Buffer;
  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::MakeTempFilename()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool GetExistingTempFile (Filename, pTempPath);
 *
 *=========================================================================*/
bool CObBsaFileRecord::GetExistingTempFile (CSString& Filename, const char* pTempPath) {
  bool Create = false;
  bool Result;
  
  if (m_TmpFilename.IsEmpty())    Create = true;
  if (Create && !FileExists(m_TmpFilename)) Create = true;

  if (Create) {
    if (GetFileSize(m_TmpFilename) != (long) m_Filesize) Create = true;
  }

  if (!Create) {
    Filename = m_TmpFilename;
    return (true);
  }

  Result = SaveTempFile(Filename, pTempPath);
  if (Result) m_TmpFilename = Filename;

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::GetExistingTempFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool MakeFilePathEx (pFilename);
 *
 *=========================================================================*/
bool MakeFilePathEx (const char* pFilename) {
  char     Drive[_MAX_DRIVE + 8];
  char     Path[_MAX_PATH + 8];
  char     Filename[_MAX_FNAME + 8];
  char     Extension[_MAX_EXT + 8];
  CSString FullPath;

  _splitpath(pFilename, Drive, Path, Filename, Extension);

  FullPath  = Drive;
  TerminatePath(Path);
  FullPath += Path;
  
  return MakePathEx(FullPath);
}
/*===========================================================================
 *		End of Function MakeFilePathEx()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool SaveTempFile (OutputFilename, pTempPath);
 *
 *=========================================================================*/
bool CObBsaFileRecord::SaveTempFile (CSString& OutputFilename, const char* pTempPath) {
  bool Result;

  if (pTempPath == NULL) {
    OutputFilename = tmpnam(NULL);
  }
  else {
    Result = MakeTempFilename(OutputFilename, pTempPath);
    if (!Result) return (false);

    MakeFilePathEx(OutputFilename);
  }

  return SaveFile(OutputFilename);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::SaveTempFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool SaveFileData (OutputFile, InputFile);
 *
 *=========================================================================*/
bool CObBsaFileRecord::SaveFileData (CObFile& OutputFile, CObFile& InputFile) {
  static char s_Buffer[100100];
  dword	      OutputBytes = 0;
  dword	      ReadSize;
  bool        Result;

  while (OutputBytes < m_Header.Filesize) {
    ReadSize = 100000;
    if (ReadSize + OutputBytes > m_Header.Filesize) ReadSize = m_Header.Filesize - OutputBytes;

    Result = InputFile.Read(s_Buffer, ReadSize);
    if (!Result) return (false);

    Result = OutputFile.Write(s_Buffer, ReadSize);
    if (!Result) return (false);

    OutputBytes += ReadSize;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::SaveFileData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool SaveCompressedFileData (OutputFile, InputFile);
 *
 *=========================================================================*/
bool CObBsaFileRecord::SaveCompressedFileData (CObFile& OutputFile, CObFile& InputFile) {
  static byte s_InputBuffer[33000];
  static byte s_OutputBuffer[33000];

  dword	        InputBytes = 0;
  dword		OutputBytes = 0;
  dword	        ReadSize;
  dword		DeflatedSize;
  dword         WriteSize;
  
  z_stream	Stream;
  bool		Result;
  int		zResult;
  
	/* Read the compressed data */
  Result = InputFile.Read(&DeflatedSize, 4);
  if (!Result) return (false);

	/* Initialize the zLib stream */
  Stream.zalloc   = Z_NULL;
  Stream.zfree    = Z_NULL;
  Stream.opaque   = Z_NULL;
  Stream.avail_in = 0;
  Stream.next_in  = Z_NULL;

  zResult = inflateInit(&Stream);
  if (zResult != Z_OK) return AddObZLibError(zResult, Stream.msg);


  while (InputBytes < m_Header.Filesize) {
    ReadSize = 32000;
    if (ReadSize + InputBytes > m_Header.Filesize) ReadSize = m_Header.Filesize - InputBytes;

    Result = InputFile.Read(s_InputBuffer, ReadSize);
    if (!Result) return (false);
    InputBytes += ReadSize;

	/* Uncompress the data  */
    Stream.next_in   = s_InputBuffer;
    Stream.avail_in  = ReadSize;

    do {
      Stream.avail_out = 32000;
      Stream.next_out  = s_OutputBuffer;

      zResult = inflate(&Stream, Z_NO_FLUSH);

      switch (zResult) {
            case Z_NEED_DICT:
                zResult = Z_DATA_ERROR;     /* and fall through */
            case Z_STREAM_ERROR:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
	        AddObZLibError(zResult, Stream.msg);
		inflateEnd(&Stream);
		return (false);
      }

      WriteSize    = 32000 - Stream.avail_out;
      Result = OutputFile.Write(s_OutputBuffer, WriteSize);

      if (!Result) {
        inflateEnd(&Stream);
        return (false);
      }

      OutputBytes += WriteSize;
    } while (Stream.avail_out == 0);

  }

  inflateEnd(&Stream);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::SaveCompressedFileData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool SaveFile (pOutput);
 *
 * TODO: Compressed input
 *
 *=========================================================================*/
bool CObBsaFileRecord::SaveFile (const char* pOutput) {
  CObBsaFile* pBsa = GetParentFile();
  CObFile     OutputFile;
  CObFile     InputFile;
  bool        Result;

  if (pBsa == NULL) return (false);

  Result = OutputFile.Open(pOutput, "wb");
  if (!Result) return (false);

  Result = InputFile.Open(pBsa->GetFilename(), "rb");
  if (!Result) return (false);

  Result = InputFile.Seek(m_Header.Offset);
  if (!Result) return (false);

  if (IsCompressed()) {
    Result = SaveCompressedFileData(OutputFile, InputFile);
  }
  else {
    Result = SaveFileData(OutputFile, InputFile);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::SaveFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool Write (File);
 *
 *=========================================================================*/
bool CObBsaFileRecord::Write (CObFile& File) {
  //m_Header.NameHash = ObHashString64(m_Filename);
  //m_Header.Filesize = (m_Filesize & OB_BSAFILEREC_SIZEMASK) | (m_Flags & OB_BSAFILEREC_FLAGMASK);

  return WriteHeader(File);
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFileRecord Method - bool WriteHeader (File);
 *
 *=========================================================================*/
bool CObBsaFileRecord::WriteHeader (CObFile& File) {
  return File.Write((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFileRecord::WriteHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int64 ObHashString64 (pString);
 *
 * Hash a string into a 64-bit value. 
 *
 * Reference:
 * http://www34.brinkster.com/ghostwheel/TES3_BSA_File_Format.htm
 *
 *=========================================================================*/
int64 ObHashString64 (const char* pString) {
  dword hash1;
  dword hash2;
  dword full_len;
  dword half_len;
  dword sum;
  dword off;
  dword temp;
  dword i;
  dword n;

  if (pString == NULL) return (0);
  full_len = (dword) strlen(pString);
  half_len = (full_len >> 1);
  sum      = 0;
  off      = 0;

  for(i = 0; i < half_len; ++i) {
    temp = ( ((dword)(pString[i])) << (off & 0x1F) );
    sum  = sum ^ temp;
    off += off;
  }

  hash1 = sum;
  sum   = 0;
  off   = 0;

  for(; i < full_len;  ++i) {
    temp = ( ((dword)(pString[i])) << (off & 0x1F) );
    sum  = sum ^ temp;
    n    = temp & 0x1F;
    sum  = (sum << (32-n)) | (sum >> n);
    off += off;
  }

  hash2 = sum;

  return ((int64)hash2 << 32) | (int64)hash1;
}
/*===========================================================================
 *		End of Function ObHashString64()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObReadBString (String, File);
 *
 * Reads a string of form:
 *	[byte length] [string data of length]
 *
 *=========================================================================*/
bool ObReadBString (CSString& String, CObFile& File) {
  byte Length;
  bool Result;

  Result = File.Read((char *)&Length, 1);
  if (!Result) return (false);

  if (Length == 0) {
    String.Empty();
    return (true);
  }

  String.SetSize(Length + 1);

  Result = File.Read((char *)(const char*) String, Length);
  String.UpdateLength();
  String.SetSize(Length - 1);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Function ObReadBString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObWriteBString (String, File);
 *
 * Writes a string of form:
 *	[byte length] [string data of length]
 *
 *=========================================================================*/
bool ObWriteBString (CSString& String, CObFile& File) {
  byte Length;
  bool Result;

  if (String.GetLength() >= 255) {
    AddObGeneralError("Cannot output a BString longer than 254 characters!");
    return (false);
  }

  Length = String.GetLength() + 1;
  Result = File.Write((char *)&Length, 1);
  if (!Result) return (false);

  Result = File.Write((const char*) String, Length);
  return (Result);
}
/*===========================================================================
 *		End of Function ObWriteBString()
 *=========================================================================*/
