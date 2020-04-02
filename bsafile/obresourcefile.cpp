/*===========================================================================
 *
 * File:	Obresourcefile.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obresourcefile.h"
#include "obresourcefolder.h"


/*===========================================================================
 *
 * Class CObResourceFile Constructor
 *
 *=========================================================================*/
CObResourceFile::CObResourceFile() {
  m_pParent      = NULL;
  m_ResourceType = OB_RESOURCETYPE_UNKNOWN;
}
/*===========================================================================
 *		End of Class CObResourceFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CObResourceFile::Destroy (void) {
  m_Instances.Destroy();

  m_pParent      = NULL;
  m_ResourceType = OB_RESOURCETYPE_UNKNOWN;

  CObResourceBase::Destroy();
}
/*===========================================================================
 *		End of Class Method CObResourceFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - CObResourceInstance* AddInstance (pRecord);
 *
 *=========================================================================*/
CObResourceInstance* CObResourceFile::AddInstance (CObBsaFileRecord* pRecord) {
  CObResourceInstance* pInstance;

  pInstance = new CObResourceInstance;
  m_Instances.Add(pInstance);

  pInstance->SetParent(this);
  pInstance->SetBsaRecord(pRecord);

  if (m_Instances.GetSize() == 1) m_ResourceType = pInstance->GetResourceType();
  pInstance->UpdateFileInfo();
  return (pInstance);
}
/*===========================================================================
 *		End of Class Method CObResourceFile::AddInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - CObResourceInstance* AddInstance (pFilename);
 *
 *=========================================================================*/
CObResourceInstance* CObResourceFile::AddInstance (const char* pFilename) {
  CObResourceInstance* pInstance;

  pInstance = new CObResourceInstance;
  m_Instances.Add(pInstance);

  pInstance->SetParent(this);
  pInstance->SetFilename(pFilename);

  if (m_Instances.GetSize() == 1) m_ResourceType = pInstance->GetResourceType();
  pInstance->UpdateFileInfo();
  return (pInstance);
}
/*===========================================================================
 *		End of Class Method CObResourceFile::AddInstance()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - const char* GetBasePath (void);
 *
 *=========================================================================*/
const char* CObResourceFile::GetBasePath (void) { 
   return (m_pParent ? m_pParent->GetBasePath() : ""); 
}
/*===========================================================================
 *		End of Class Method CObResourceFile::GetBasePath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - int64 GetFilesize (void);
 *
 *=========================================================================*/
int64 CObResourceFile::GetFilesize (void) {
  CObResourceInstance* pInstance = GetMainInstance();
  if (pInstance == NULL) return (-1);
  return pInstance->GetFilesize();
}
/*===========================================================================
 *		End of Class Method CObResourceFile::GetFilesize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - uint64 GetFiletime (void);
 *
 *=========================================================================*/
dword64 CObResourceFile::GetFiletime (void) {
  CObResourceInstance* pInstance = GetMainInstance();
  if (pInstance == NULL) return (0);
  return pInstance->GetFiletime();
}
/*===========================================================================
 *		End of Class Method CObResourceFile::GetFiletime()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - const char* GetFullName (void);
 *
 *=========================================================================*/
const char* CObResourceFile::GetFullName (void) {
  static CSString s_Buffer;

  if (m_pParent == NULL) return GetName();

  s_Buffer  = m_pParent->GetFullName();
  //s_Buffer += "\\";
  s_Buffer += GetName();

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method CObResourceFile::GetFullName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObResourceFile Method - const GetCSName (void);
 *
 * Removes the first path from the full path.
 *
 *=========================================================================*/
const char* CObResourceFile::GetCSName (void) {
  static CSString s_Buffer;
  int             Index;

  s_Buffer = GetFullName();

  Index = s_Buffer.FindChar('\\');
  if (Index >= 0) s_Buffer.Delete(0, Index + 1);

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObResourceFile::GetCSName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - bool IsInPath (pPath);
 *
 *=========================================================================*/
bool CObResourceFile::IsInPath (const char* pPath) { 
  const char* pFull = GetFullName();
  return (strnicmp(pFull, pPath, strlen(pPath)) == 0); 
}
/*===========================================================================
 *		End of Class Method CObResourceFile::IsInPath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFile Method - void SetMainInstances (pInstance);
 *
 *=========================================================================*/
void CObResourceFile::SetMainInstances (CObResourceInstance* pInstance) {
  CObResourceInstance*	pMainInstance;
  int			Index;

	/* Ignore if invalid or only one instance */
  if (pInstance == NULL || GetNumInstances() <= 1) return;

	/* Find the instance */
  Index = m_Instances.Find(pInstance);
  if (Index <= 0) return;

  pMainInstance = m_Instances.GetAt(0);
  if (pMainInstance == NULL) return;

	/* TODO: Swap instances */
  //m_Instances.SetAt(0, pInstance);
  //m_Instances.SetAt(Index, pMainInstance);
}
/*===========================================================================
 *		End of Class Method CObResourceFile::SetMainInstances()
 *=========================================================================*/


