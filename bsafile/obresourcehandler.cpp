/*===========================================================================
 *
 * File:	Obresourcehandler.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obresourcehandler.h"
#include "windows.h"


/*===========================================================================
 *
 * Class CObResourceHandler Constructor
 *
 *=========================================================================*/
CObResourceHandler::CObResourceHandler() {
  m_RootFolder.SetParentHandler(this);
}
/*===========================================================================
 *		End of Class CObResourceHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CObResourceHandler::Destroy (void) {
  m_RootFolder.Destroy();
  m_RootFolder.SetParentHandler(this);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - bool AddBsaFileRecord (pRecord);
 *
 *=========================================================================*/
bool CObResourceHandler::AddBsaFileRecord (CObBsaFileRecord* pRecord) {
  CObResourceFolder* pFolder = &m_RootFolder;
  CObResourceFolder* pNextFolder;
  CObResourceFile*   pFile;
  char               PathBuffer[256];
  char*		     pParse;

	/* Parse out the full path */
  strnncpy(PathBuffer, pRecord->GetFullPath(), 250);
  pParse = strtok(PathBuffer, "\\");

  while (pParse != NULL) {
    pNextFolder = pFolder->GetFolderCreate(pParse);
    if (pNextFolder == NULL) return (false);

    pParse  = strtok(NULL, "\\");
    pFolder = pNextFolder;
  }

	/* Add the resource to the folder */
  pFile = pFolder->GetFileCreate(pRecord->GetFilename());
  if (pFile == NULL) return (false);

  pFile->AddInstance(pRecord);

  return (true);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::AddBsaFileRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - bool AddPathContents (pRootPath, IncludeRootFiles);
 *
 *=========================================================================*/
bool CObResourceHandler::AddPathContents (const char* pRootPath, const bool IncludeRootFiles) {
  return AddPathContents(&m_RootFolder, pRootPath, IncludeRootFiles);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::AddPathContents()
 *=========================================================================*/


typedef CObPtrArray<WIN32_FIND_DATA> CFindDataArray;
/*===========================================================================
 *
 * Class CObResourceHandler Method - bool AddPathContents (pFolder, pRootPath, IncludeRootFiles);
 *
 *=========================================================================*/
bool CObResourceHandler::AddPathContents (CObResourceFolder* pFolder, const char* pPath, const bool IncludeRootFiles) {
  WIN32_FIND_DATA    FindData;
  WIN32_FIND_DATA*   pNewPath;
  CFindDataArray     FindPaths;
  CObResourceFolder* pNewFolder;
  CObResourceFile*   pFile;
  CObResourceInstance* pInstance;
  CSString           FindSpec(pPath);
  HANDLE	     hFind;
  BOOL		     FindResult;
  dword		     Index;
  bool		     ReturnResult = true;

  TerminatePath(FindSpec);
  FindSpec += "*.*";

	/* Add all matching files and find all sub-paths */
  hFind = FindFirstFile(FindSpec, &FindData);
  if (hFind == INVALID_HANDLE_VALUE) return (true);

  do {
    if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
      pNewPath = new WIN32_FIND_DATA;
      FindPaths.Add(pNewPath);
      *pNewPath = FindData;
    }
    else if (IncludeRootFiles) {
      pFile = pFolder->GetFileCreate(FindData.cFileName);

		/* TODO: Set filesize/time here from find data */
      if (pFile != NULL) {
        pInstance = pFile->AddInstance(FindData.cFileName);

	if (pInstance != NULL) {
	  pInstance->SetFiletime(FindData.ftLastWriteTime.dwLowDateTime, FindData.ftLastWriteTime.dwHighDateTime);
	  pInstance->SetFilesize(FindData.nFileSizeLow, FindData.nFileSizeHigh);
	}
      }
      else
        ReturnResult = false;
    }

    FindResult = FindNextFile(hFind, &FindData);
  } while (FindResult);

  FindClose(hFind);

	/* Recursively iterate through all found sub-paths */
  for (Index = 0; Index < FindPaths.GetSize(); ++Index) {
    pNewPath = FindPaths.GetAt(Index);
    if (strcmp(pNewPath->cFileName, ".") == 0) continue;
    if (strcmp(pNewPath->cFileName, "..") == 0) continue;

    pNewFolder = pFolder->GetFolderCreate(pNewPath->cFileName);

    if (pNewFolder != NULL) {
      FindSpec  = pPath;
      FindSpec += pNewPath->cFileName;
      FindSpec += "\\";
      ReturnResult &= AddPathContents(pNewFolder, FindSpec, true);
    }
    else {
      ReturnResult = false;
    }
  }

  FindPaths.Destroy();
  return (ReturnResult);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::AddPathContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - bool AddBsaFile (pBsaFile);
 *
 *=========================================================================*/
bool CObResourceHandler::AddBsaFile (CObBsaFile* pBsaFile) {
  CObBsaFileRecord* pRecord;
  BSAPOSITION       FilePos;

	/* Ignore invalid input */
  if (pBsaFile == NULL) return (false);

	/* Add all files in the BSA archive */
  pRecord = pBsaFile->GetFirstFile(FilePos);

  while (pRecord != NULL) {
    AddBsaFileRecord(pRecord);
    pRecord = pBsaFile->GetNextFile(FilePos);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::AddBsaFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - CObResourceFile* FindFile (pFilename);
 *
 *=========================================================================*/
CObResourceFile* CObResourceHandler::FindFile (const char* pFilename) {
  return m_RootFolder.FindFullFile(pFilename);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::FindFile()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObResourceHandler Method - CObResourceBase* FindName (pFilename);
 *
 *=========================================================================*/
CObResourceBase* CObResourceHandler::FindName (const char* pFilename) {
  return m_RootFolder.FindFullName(pFilename);
}
/*===========================================================================
 *		End of Class Method CObResourceHandler::FindName()
 *=========================================================================*/


