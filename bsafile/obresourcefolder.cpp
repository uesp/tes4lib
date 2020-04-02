/*===========================================================================
 *
 * File:	Obresourcefolder.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obresourcefolder.h"
#include "obresourcehandler.h"


/*===========================================================================
 *
 * Class CObResourceFolder Constructor
 *
 *=========================================================================*/
CObResourceFolder::CObResourceFolder() {
  m_pParent        = NULL;
  m_pParentHandler = NULL;

  m_Resources.InitHashTable(203);
}
/*===========================================================================
 *		End of Class CObResourceFolder Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - void Destroy (void);
 *
 *=========================================================================*/
void CObResourceFolder::Destroy (void) {
  m_Resources.Destroy();
  
  m_pParent        = NULL;
  m_pParentHandler = NULL; 

  CObResourceBase::Destroy();
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFile* FindFile (pFilename);
 *
 *=========================================================================*/
CObResourceFile* CObResourceFolder::FindFile (const char* pFilename) {
  CObResourceBase*   pBase;

  pBase = m_Resources.Lookup(pFilename);
  if (pBase == NULL) return (NULL);

  if (!pBase->IsFolder()) return (CObResourceFile *) pBase;
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::FindFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFile* FindFullFile (pFilename);
 *
 *=========================================================================*/
CObResourceFile* CObResourceFolder::FindFullFile (const char* pFilename) {
  CObResourceBase* pBase;
  CSString         Buffer(pFilename);
  int              Index;

  Index = Buffer.FindChar('\\');

	/* Find a file if no more path left */
  if (Index < 0) {
    pBase = FindFile(Buffer);
    if (pBase == NULL || pBase->IsFolder()) return (NULL);
    return (CObResourceFile *) pBase;
  }

  CSString SubPath(Buffer);
  SubPath.Truncate(Index);
  Buffer.Delete(0, Index + 1);

  pBase = FindSubFolder(SubPath);
  if (pBase == NULL || !pBase->IsFolder()) return (NULL);
    
  return ((CObResourceFolder *) pBase)->FindFullFile(Buffer);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::FindFullFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFile* FindFullName (pFilename);
 *
 *=========================================================================*/
CObResourceBase* CObResourceFolder::FindFullName (const char* pFilename) {
  CObResourceBase* pBase;
  CSString         Buffer(pFilename);
  int              Index;

  Index = Buffer.FindChar('\\');

	/* Find a file if no more path left */
  if (Index < 0) {
    pBase = FindFile(Buffer);
    return pBase;
  }

  CSString SubPath(Buffer);
  SubPath.Truncate(Index);
  Buffer.Delete(0, Index + 1);

  pBase = FindSubFolder(SubPath);
  if (pBase == NULL) return (NULL);
   
  if (Buffer.IsEmpty()) return (pBase);
  return ((CObResourceFolder *) pBase)->FindFullName(Buffer);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::FindFullName()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFolder* FindSubFolder (pPath);
 *
 *=========================================================================*/
CObResourceFolder* CObResourceFolder::FindSubFolder (const char* pPath) {
  CObResourceBase*   pBase;
      
  pBase = m_Resources.Lookup(pPath);
  if (pBase == NULL) return (NULL);

  if (pBase->IsFolder()) return (CObResourceFolder *) pBase;
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::FindSubFolder()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObResourceFolder Method - const GetBasePath (void);
 *
 *=========================================================================*/
const char* CObResourceFolder::GetBasePath (void) { 
   return (m_pParentHandler ? m_pParentHandler->GetBasePath() : "");
}
/*===========================================================================
 *		End of Class Method char* CObResourceFolder::GetBasePath()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFile* GetFileCreate (pFilename);
 *
 *=========================================================================*/
CObResourceFile* CObResourceFolder::GetFileCreate (const char* pFilename) {
  CObResourceFile* pFile;

	/* Ignore invalid or empty path strings */
  if (pFilename == NULL || *pFilename == NULL_CHAR) {
    AddObGeneralError("Invalid or empty resource filename string!");
    return (NULL);
  }

	/* Find an existing folder */
  pFile = FindFile(pFilename);
  if (pFile != NULL) return (pFile);

	/* Create a new one */
  pFile = new CObResourceFile;
  m_Resources.SetAt(pFilename, pFile);

  pFile->SetParent(this);
  pFile->SetName(pFilename);
  
  return (pFile);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::GetFileCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceFolder Method - CObResourceFolder* GetFolderCreate (pPath);
 *
 *=========================================================================*/
CObResourceFolder* CObResourceFolder::GetFolderCreate (const char* pPath) {
  CObResourceFolder* pFolder;

	/* Ignore invalid or empty path strings */
  if (pPath == NULL || *pPath == NULL_CHAR) {
    AddObGeneralError("Invalid or empty resource path string!");
    return (NULL);
  }

	/* Find an existing folder */
  pFolder = FindSubFolder(pPath);
  if (pFolder != NULL) return (pFolder);

	/* Create a new one */
  pFolder = new CObResourceFolder;
  m_Resources.SetAt(pPath, pFolder);

  pFolder->SetParentHandler(m_pParentHandler);
  pFolder->SetParent(this);
  pFolder->SetName(pPath);

  return (pFolder);
}
/*===========================================================================
 *		End of Class Method CObResourceFolder::GetFolderCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObResourceFolder Method - const GetFullName (void);
 *
 *=========================================================================*/
const char* CObResourceFolder::GetFullName (void) {
  static CSString s_Buffer;

  if (m_pParent != NULL) {
    s_Buffer = m_pParent->GetFullName();
  }
  else {
    s_Buffer.Empty();
  }
  
  if (!m_Name.IsEmpty()) {
    s_Buffer += GetName();
    s_Buffer += "\\";
  }

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObResourceFolder::GetFullName()
 *=========================================================================*/
