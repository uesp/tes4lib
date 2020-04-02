/*===========================================================================
 *
 * File:	Obresourcehandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRESOURCEHANDLER_H
#define __OBRESOURCEHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obresourcefolder.h"
  #include "obresourcefile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceHandler Definition
 *
 *=========================================================================*/
class CObResourceHandler {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObResourceFolder	m_RootFolder;

  CSString		m_BasePath;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

  bool AddBsaFileRecord (CObBsaFileRecord* pRecord);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObResourceHandler();
  virtual ~CObResourceHandler() { Destroy(); }
  virtual void Destroy (void);

	/* Add the contents of the given BSA file */
  bool AddBsaFile (CObBsaFile* pBsaFile);

	/* Add contents of a path and all contained subpaths */
  bool AddPathContents    (const char* pRootPath, const bool IncludeRootFiles = true);
  bool AddPathContents    (CObResourceFolder* pFolder, const char* pPath, const bool IncludeFiles);

	/* Find the file with the given path */
  CObResourceFile* FindFile (const char* pFilename);
  CObResourceBase* FindName (const char* pFilename);

	/* Get class members */
  CObResourceFolder& GetRootFolder (void) { return m_RootFolder; }
  const char*        GetBasePath   (void) { return m_BasePath; }

	/* Set class members */
  void SetBasePath      (const char* pString) { m_BasePath      = pString; }
  


};
/*===========================================================================
 *		End of Class CObResourceHandler Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obresourcehandler.H
 *=========================================================================*/
