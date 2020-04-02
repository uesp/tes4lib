/*===========================================================================
 *
 * File:	Obbsafile.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbsafile.h"


/*===========================================================================
 *
 * Class CObBsaFile Constructor
 *
 *=========================================================================*/
CObBsaFile::CObBsaFile() {
  ObBsaDefaultHeader(m_Header);

  m_FilenameOffset = 0;
  m_FileDataOffset = 0;

  m_Filetime       = 0;
  m_Filesize       = 0;
}
/*===========================================================================
 *		End of Class CObBsaFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBsaFile::Destroy (void) {
  ObBsaDefaultHeader(m_Header);

  m_FilenameOffset = 0;
  m_FileDataOffset = 0;

  m_Filetime       = 0;
  m_Filesize       = 0;
}
/*===========================================================================
 *		End of Class Method CObBsaFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - CObBsaFileRecord* GetNextFile (Position);
 *
 *=========================================================================*/
CObBsaFileRecord* CObBsaFile::GetNextFile (BSAPOSITION& Position) {
  CObBsaFileRecord* pFile;

  if (Position.FolderIndex >= (int) m_Folders.GetSize()) return (NULL);
  
  do {
    pFile = m_Folders[Position.FolderIndex]->GetNextFile(Position);
    if (pFile != NULL) return (pFile);

    ++Position.FolderIndex;
    Position.FileIndex = -1;
  } while (Position.FolderIndex < (int) m_Folders.GetSize());

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::GetNextFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool Load (pFilename);
 *
 *=========================================================================*/
bool CObBsaFile::Load (const char* pFilename) {
  CObFile  File;
  bool     Result;

  Destroy();

  Result = File.Open(pFilename, "rb");
  if (!Result) return (false);

  Result = Read(File);
  File.Close();

  if (Result) {
    m_Filename = pFilename;
    GetFileInfo(pFilename, m_Filesize, m_Filetime);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool Save (pFilename);
 *
 *=========================================================================*/
bool CObBsaFile::Save (const char* pFilename) {
  CObFile File;
  bool     Result;

  Result = File.Open(pFilename, "wb");
  if (!Result) return (false);

  Result = Write(File);

  if (Result) m_Filename = pFilename;
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::Save()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool ReadHeader (File);
 *
 *=========================================================================*/
bool CObBsaFile::ReadHeader (CObFile& File) {
  return File.Read((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFile::ReadHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool Read (File);
 *
 *=========================================================================*/
bool CObBsaFile::Read (CObFile& File) {
  bool Result;

  Result = ReadHeader(File);
  if (!Result) return (false);

  Result = ReadFolders(File);
  if (!Result) return (false);

  Result = ReadFilenames(File);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool ReadFilenames (File);
 *
 *=========================================================================*/
bool CObBsaFile::ReadFilenames (CObFile& File) {
  CObBsaFolder*     pFolder;
  CObBsaFileRecord* pFile;
  BSAPOSITION	    FilePos;
  char*		    pBuffer;
  char*		    pParse;
  dword		    Index;
  dword		    TotalLength;
  int		    Length;
  bool              Result;
  bool		    ReturnResult;

  if (m_Header.FileNameLength == 0) return (true);

  Result = File.Seek(m_FilenameOffset);
  if (!Result) return (false);

	/* Read the entire filename buffer */
  pBuffer = new char[m_Header.FileNameLength + 8];
  Result = File.Read(pBuffer, m_Header.FileNameLength);

  if (!Result) {
    delete[] pBuffer;
    return (false);
  }

  pParse       = pBuffer;
  TotalLength  = 0;
  ReturnResult = true;
  pFolder      = NULL;

  pFile = GetFirstFile(FilePos);
 
	/* Parse the filename buffer */
  for (Index = 0; Index < m_Header.FileCount; ++Index) {

    if (pFile == NULL) {
      AddObGeneralError("Mismatch of filename and file record counts!");
      ReturnResult = false;
      break;
    }

    if (TotalLength >= m_Header.FileNameLength) {
      AddObGeneralError("Exceeded the filename buffer size!");
      ReturnResult = false;
      break;
    }

    Length = (int) strlen(pParse);
    pFile->SetFilename(pParse);
    //SystemLog.Printf("File: '%s', %d", pFile->GetFilename(), pFile->GetFilenameSize() + 1);

    TotalLength += Length + 1;
    pParse      += Length + 1;
   
    pFile = GetNextFile(FilePos);
  }

  File.Tell(m_FileDataOffset);

  delete[] pBuffer;
  return (ReturnResult);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::ReadFilenames()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool ReadFolders (File);
 *
 *=========================================================================*/
bool CObBsaFile::ReadFolders (CObFile& File) {
  CObBsaFolder* pFolder;
  dword		Index;
  int		LastPos;
  bool          Result;

	/* Jump to start of folder record data */
  Result = File.Seek(m_Header.FolderRecordOffset);
  if (!Result) return (false);

	/* Read the folder headers */
  for (Index = 0; Index < m_Header.FolderCount; ++Index) {
    pFolder = new CObBsaFolder;
    m_Folders.Add(pFolder);
    pFolder->SetBsaFile(this);

    Result = pFolder->Read(File);
    if (!Result) return (false);
  }

  m_FilenameOffset = 0;

	/* Read the folder contents */
  for (Index = 0; Index < m_Header.FolderCount; ++Index) {
    pFolder = m_Folders[Index];
    if (pFolder == NULL) return (false);

    if (pFolder->GetOffset() < m_Header.FileNameLength) {
      AddObGeneralError("Bad folder offset in BSA file!");
      return (false);
    }

    Result = File.Seek(pFolder->GetOffset() - m_Header.FileNameLength);
    if (!Result) return (false);
   
    Result = pFolder->ReadContents(File);
    if (!Result) return (false);

    Result = File.Tell(LastPos);
    if (!Result) return (false);

    if (m_FilenameOffset < LastPos) m_FilenameOffset = LastPos;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::ReadFolders()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool Write (File);
 *
 *=========================================================================*/
bool CObBsaFile::Write (CObFile& File) {
  bool Result;

  m_Header.FileCount          = 0;
  m_Header.FileNameLength     = 0;
  m_Header.FolderCount        = m_Folders.GetSize();
  m_Header.FolderNameLength   = 0;

  Result = WriteHeader(File);
  if (!Result) return (false);

  Result = WriteFolders(File);
  if (!Result) return (false);

  Result = WriteFilenames(File);
  if (!Result) return (false);
  	
	/* Update the header again */
  Result = File.Seek(0);
  if (!Result) return (false);

  Result = WriteHeader(File);
  if (!Result) return (false);

	/* Output the file data */
  Result = WriteData(File);
  if (!Result) return (false);

	/* Update the file/folder offset data */
  UpdateFolderOffsets();
  Result = WriteFolders(File);
  if (!Result) return (false);

  UpdateFileOffsets();
  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - void UpdateFileOffsets (void);
 *
 *=========================================================================*/
void CObBsaFile::UpdateFileOffsets (void) {
  CObBsaFileRecord* pFile;
  BSAPOSITION       FilePos;
  
  pFile = GetFirstFile(FilePos);

  while (pFile != NULL) {
    pFile->SetInputOffset(pFile->GetOffset());  
    pFile = GetNextFile(FilePos);
  }

}
/*===========================================================================
 *		End of Class Method CObBsaFile::UpdateFileOffsets()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObBsaFile::WriteData (CObFile& File) {
  CObFile	    InputFile;
  CObBsaFileRecord* pFile;
  BSAPOSITION       FilePos;
  bool	            Result;

  Result = InputFile.Open(m_Filename, "rb");

  if (!Result) {
    AddObGeneralError("Failed to open the source BSA file!");
    return (false);
  }

	/* Jump to start of file data output */
  Result = File.Seek(m_FileDataOffset);
  if (!Result) return (false);

  pFile = GetFirstFile(FilePos);

  while (pFile != NULL) {
        
    Result = CopyFileData(pFile, InputFile, File);
    if (!Result) return (false);

    pFile = GetNextFile(FilePos);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::WriteData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool CopyFileData (pFile, InputFile, OutputFile);
 *
 *=========================================================================*/
bool CObBsaFile::CopyFileData (CObBsaFileRecord* pFile, CObFile& InputFile, CObFile& OutputFile) {
  static char s_Buffer[32100];
  int   Offset;
  int   Size;
  dword TotalOutput;
  bool  Result;

  Result = OutputFile.Tell(Offset);
  if (!Result) return (false);

  pFile->SetOffset((dword)Offset);

  Result = InputFile.Seek(pFile->GetInputOffset());
  if (!Result) return (false);

  TotalOutput = 0;

  while (TotalOutput < pFile->GetFilesize()) {
    Size = 32000;
    if (TotalOutput + Size > pFile->GetFilesize()) Size = pFile->GetFilesize() - TotalOutput;

    Result = InputFile.Read(s_Buffer, Size);
    if (!Result) return (false);

    Result = OutputFile.Write(s_Buffer, Size);
    if (!Result) return (false);

   TotalOutput += Size;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::CopyFileData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool WriteFolderHeaders (File);
 *
 *=========================================================================*/
bool CObBsaFile::WriteFolderHeaders (CObFile& File) {
  CObBsaFolder* pFolder;
  dword	        Index;
  bool	        Result;

	/* Jump to start of folder record data */
  Result = File.Seek(m_Header.FolderRecordOffset);
  if (!Result) return (false);

	/* Write the folder headers */
  for (Index = 0; Index < m_Folders.GetSize(); ++Index) {
    pFolder = m_Folders[Index];

    Result = pFolder->Write(File);
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::WriteFolderHeaders()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool WriteFolders (File);
 *
 *=========================================================================*/
bool CObBsaFile::WriteFolders (CObFile& File) {
  CObBsaFolder* pFolder;
  dword		Index;
  bool          Result;

	/* Output the initial header data */	
  Result = WriteFolderHeaders(File);
  if (!Result) return (false);

  Result = File.Tell(m_FilenameOffset);
  if (!Result) return (false);

	/* Write the folder contents */
  for (Index = 0; Index < m_Folders.GetSize(); ++Index) {
    pFolder = m_Folders[Index];
    if (pFolder == NULL) return (false);

    m_Header.FolderNameLength += (int) pFolder->GetFolderNameSize() + 1;
    pFolder->SetOffset((dword)m_FilenameOffset);

    Result = pFolder->WriteContents(File);
    if (!Result) return (false);

    Result = File.Tell(m_FilenameOffset);
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::WriteFolders()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - void UpdateFolderOffsets (void);
 *
 *=========================================================================*/
void CObBsaFile::UpdateFolderOffsets (void) {
  CObBsaFolder* pFolder;
  dword		Index;
  
  for (Index = 0; Index < m_Folders.GetSize(); ++Index) {
    pFolder = m_Folders[Index];
    pFolder->SetOffset(pFolder->GetOffset() + m_Header.FileNameLength);
  }

}
/*===========================================================================
 *		End of Class Method CObBsaFile::UpdateFolderOffsets()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool WriteFilenames (File);
 *
 *=========================================================================*/
bool CObBsaFile::WriteFilenames (CObFile& File) {
  CObBsaFileRecord* pFile;
  BSAPOSITION       FilePos;
  bool		    Result;

	/* Jump to start of filename data */
  Result = File.Seek(m_FilenameOffset);
  if (!Result) return (false);

  m_Header.FileCount      = 0;
  m_Header.FileNameLength = 0;
  pFile = GetFirstFile(FilePos);

  while (pFile != NULL) {
    ++m_Header.FileCount;
    m_Header.FileNameLength += pFile->GetFilenameSize() + 1;
    //SystemLog.Printf("File: '%s', %d", pFile->GetFilename(), pFile->GetFilenameSize() + 1);

    Result = File.Write(pFile->GetFilename(), pFile->GetFilenameSize() + 1);
    if (!Result) return (false);

    pFile = GetNextFile(FilePos);
  }

  File.Tell(m_FileDataOffset);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFile::WriteFilenames()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFile Method - bool WriteHeader (File);
 *
 *=========================================================================*/
bool CObBsaFile::WriteHeader (CObFile& File) {
  return File.Write((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFile::WriteHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObBsaDefaultHeader (Header);
 *
 *=========================================================================*/
void ObBsaDefaultHeader (obbsaheader_t& Header) {
  memcpy(&Header.FileID, OB_BSAHEADER_FILEID, 4);

  Header.Version            = OB_BSAHEADER_VERSION;
  Header.FolderRecordOffset = sizeof(Header);
  Header.ArchiveFlags       = 0;
  Header.FolderCount        = 0;
  Header.FileCount          = 0;
  Header.FolderNameLength   = 0;
  Header.FileNameLength     = 0;
  Header.FileFlags          = 0;
}
/*===========================================================================
 *		End of Function ObBsaDefaultHeader()
 *=========================================================================*/

