/*===========================================================================
 *
 * File:	Obbsafolder.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbsafolder.h"
#include "obbsafile.h"


/*===========================================================================
 *
 * Class CObBsaFolder Constructor
 *
 *=========================================================================*/
CObBsaFolder::CObBsaFolder() {
  m_Header.FileCount = 0;
  m_Header.NameHash  = 0;
  m_Header.Offset    = 0;
  m_pBsaFile         = NULL;
}
/*===========================================================================
 *		End of Class CObBsaFolder Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBsaFolder::Destroy (void) {
  m_Header.FileCount = 0;
  m_Header.NameHash  = 0;
  m_Header.Offset    = 0;
  m_pBsaFile         = NULL;

  m_FolderName.Empty();
  m_Files.Destroy();
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - uint64 GetFiletime (void);
 *
 *=========================================================================*/
dword64 CObBsaFolder::GetFiletime (void) {
  if (m_pBsaFile == NULL) return (0);
  return (m_pBsaFile->GetFiletime());
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::GetFiletime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - CObBsaFileRecord* GetNextFile (Position);
 *
 *=========================================================================*/
CObBsaFileRecord* CObBsaFolder::GetNextFile (BSAPOSITION& Position) {

  ++Position.FileIndex;
  if (Position.FileIndex >= (int) m_Files.GetSize()) return (NULL);

  return m_Files[Position.FileIndex];
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::GetNextFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool ReadHeader (File);
 *
 *=========================================================================*/
bool CObBsaFolder::ReadHeader (CObFile& File) {
  return File.Read((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::ReadHeader()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool Read (File);
 *
 *=========================================================================*/
bool CObBsaFolder::Read (CObFile& File) {
  bool Result;

  Result = ReadHeader(File);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool ReadContents (File);
 *
 *=========================================================================*/
bool CObBsaFolder::ReadContents (CObFile& File) {
  bool Result;

  Result = ObReadBString(m_FolderName, File);
  if (!Result) return (false);

  Result = ReadFiles(File);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::ReadContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool ReadFiles (File);
 *
 *=========================================================================*/
bool CObBsaFolder::ReadFiles (CObFile& File) {
  CObBsaFileRecord* pFile;
  dword		    Index;
  bool		    Result;

  for (Index = 0; Index < m_Header.FileCount; ++Index) {
    pFile = new CObBsaFileRecord;
    m_Files.Add(pFile);

    pFile->SetFolder(this);

    Result = pFile->Read(File);
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::ReadFiles()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool WriteFiles (File);
 *
 *=========================================================================*/
bool CObBsaFolder::WriteFiles (CObFile& File) {
  dword		    Index;
  bool		    Result;
  
  for (Index = 0; Index < m_Header.FileCount; ++Index) {
    Result = m_Files[Index]->Write(File);
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::WriteFiles()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool Write (File);
 *
 *=========================================================================*/
bool CObBsaFolder::Write (CObFile& File) {
  bool Result;

  //m_Header.NameHash = ObHashString64(m_FolderName);

  Result = WriteHeader(File);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool WriteContents (File);
 *
 *=========================================================================*/
bool CObBsaFolder::WriteContents (CObFile& File) {
  bool Result;

  Result = ObWriteBString(m_FolderName, File);
  if (!Result) return (false);

  Result = WriteFiles(File);
  if (!Result) return (false);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::WriteContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBsaFolder Method - bool WriteHeader (File);
 *
 *=========================================================================*/
bool CObBsaFolder::WriteHeader (CObFile& File) {
  return File.Write((char *)&m_Header, sizeof(m_Header));
}
/*===========================================================================
 *		End of Class Method CObBsaFolder::WriteHeader()
 *=========================================================================*/
