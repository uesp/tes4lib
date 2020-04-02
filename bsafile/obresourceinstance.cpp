/*===========================================================================
 *
 * File:	Obresourceinstance.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obresourceinstance.h"
#include "obresourcefile.h"
#include "sys/stat.h"
#include "windows.h"


/*===========================================================================
 *
 * Class CObResourceInstance Constructor
 *
 *=========================================================================*/
CObResourceInstance::CObResourceInstance() {
  m_pBsaRecord  = NULL;
  m_pParent     = NULL;
  m_HasFilesize = false;
  m_HasFiletime = false;
  m_Filesize    = 0;
  m_Filetime    = 0;
}
/*===========================================================================
 *		End of Class CObResourceInstance Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - void Destroy (void);
 *
 *=========================================================================*/
void CObResourceInstance::Destroy (void) {
  m_pBsaRecord  = NULL;
  m_pParent     = NULL;
  m_HasFilesize = false;
  m_HasFiletime = false;
  m_Filesize    = 0;
  m_Filetime    = 0;

  m_Filename.Empty();
  m_FullFilename.Empty();
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - const char* GetBasePath (void);
 *
 *=========================================================================*/
const char* CObResourceInstance::GetBasePath (void) {
  return (m_pParent ? m_pParent->GetBasePath() : ""); 
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetBasePath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - const char* GetFilename (void);
 *
 *=========================================================================*/
const char* CObResourceInstance::GetFilename (void) {

	/* If not a BSA file return the filename */
  if (m_pBsaRecord == NULL) return (m_Filename);

  return m_pBsaRecord->GetFilename();
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFilename()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - const char* GetFullFilename (void);
 *
 *=========================================================================*/
const char* CObResourceInstance::GetFullFilename (void) {

	/* If not a BSA file return the filename */
  if (m_pBsaRecord != NULL) return m_pBsaRecord->GetFullFilename();
  if (m_pParent    != NULL) return m_pParent->GetFullName();

  return GetFilename();
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFullFilename()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - const char* GetFullFilenameAbs (void);
 *
 *=========================================================================*/
const char* CObResourceInstance::GetFullFilenameAbs (void) {
  static CSString s_Buffer;

  s_Buffer  = GetBasePath();
  s_Buffer += GetFullFilename();
  
  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFullFilenameAbs()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - bool GetFilesize (Filesize);
 *
 *=========================================================================*/
bool CObResourceInstance::GetFilesize (int64& Filesize) {
  bool Result;

  if (!m_HasFilesize) {
    Result = UpdateFileInfo();
    if (!Result) return (false);
  }

  Filesize = m_Filesize;
  return (m_HasFilesize);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFilesize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - int64 GetFilesize (void);
 *
 *=========================================================================*/
int64 CObResourceInstance::GetFilesize (void) {
  int64 Size;

  if (GetFilesize(Size)) return (Size);
  return (-1);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFilesize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - bool GetFiletime (Filetime);
 *
 *=========================================================================*/
bool CObResourceInstance::GetFiletime (dword64& Filetime) {
  bool Result;

  if (!m_HasFiletime) {
    Result = UpdateFileInfo();
    if (!Result) return (false);
  }

  Filetime = m_Filetime;
  return (m_HasFiletime);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFiletime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - int64 GetFiletime (void);
 *
 *=========================================================================*/
dword64 CObResourceInstance::GetFiletime (void) {
  dword64 Time;

  if (GetFiletime(Time)) return (Time);
  return (0);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetFiletime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - int GetResourceType (void);
 *
 *=========================================================================*/
int CObResourceInstance::GetResourceType (void) {
  const char* pParse;
  
	/* Find the file extension */
  pParse = strrchr(GetFilename(), '.');
  if (pParse == NULL) return (OB_RESOURCETYPE_UNKNOWN);
  ++pParse;

  if (stricmp(pParse, "txt")   == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "h")     == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "c")     == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "cpp")   == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "bat")   == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "css")   == 0) return (OB_RESOURCETYPE_TEXT);
  if (stricmp(pParse, "htm")   == 0) return (OB_RESOURCETYPE_HTML);
  if (stricmp(pParse, "html")  == 0) return (OB_RESOURCETYPE_HTML);
  if (stricmp(pParse, "shtml") == 0) return (OB_RESOURCETYPE_HTML);
  if (stricmp(pParse, "xml")   == 0) return (OB_RESOURCETYPE_XML);
  if (stricmp(pParse, "nif")   == 0) return (OB_RESOURCETYPE_NIF);
  if (stricmp(pParse, "bmp")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "ico")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "dds")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "tga")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "jpg")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "gif")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "png")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "pcx")   == 0) return (OB_RESOURCETYPE_IMAGE);
  if (stricmp(pParse, "wav")   == 0) return (OB_RESOURCETYPE_SOUND);
  if (stricmp(pParse, "mp3")   == 0) return (OB_RESOURCETYPE_SOUND);

  return (OB_RESOURCETYPE_UNKNOWN);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::GetResourceType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - void SetFilename (pString);
 *
 *=========================================================================*/
void CObResourceInstance::SetFilename (const char* pString) {
  const char* pParse;

  m_FullFilename = pString;
  
  pParse = strrchr(pString, '\\');

  if (pParse != NULL)
    m_Filename = pParse + 1;
  else
    m_Filename = m_FullFilename;
    
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::SetFilename()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceInstance Method - bool UpdateFileInfo (void);
 *
 * TODO: Put windows specific calls into seperate functions.
 *
 *=========================================================================*/
bool CObResourceInstance::UpdateFileInfo (void) {
  const char*   pFilename = GetFullFilenameAbs();
  bool	        Result;
  
  m_HasFilesize = false;
  m_HasFiletime = false;
  m_Filetime    = 0;
  m_Filesize    = 0;

  if (m_pBsaRecord != NULL) {
    m_Filesize    = m_pBsaRecord->GetFilesize();
    m_Filetime    = m_pBsaRecord->GetFiletime();
    m_HasFilesize = true;
    m_HasFiletime = true;
    return (true);
  }

  Result = GetFileInfo(pFilename, m_Filesize, m_Filetime);
  m_HasFilesize = m_HasFiletime = Result;

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObResourceInstance::UpdateFileInfo()
 *=========================================================================*/


