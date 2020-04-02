/*===========================================================================
 *
 * File:	Obresourcefolder.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Defines the CObResourceFolder class for handling a folder of resources.
 *
 *=========================================================================*/
#ifndef __OBRESOURCEFOLDER_H
#define __OBRESOURCEFOLDER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obresourcebase.h"
  #include "obresourcefile.h"
  #include "obbsafile.h"
  #include "../common/dl_map.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definitions */
  class CObResourceHandler;

  	/* File/folder map */
  typedef TGenPtrMap<CSString, CObResourceBase, const char*> CObResourceMap;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceFolder Definition
 *
 *=========================================================================*/
class CObResourceFolder : public CObResourceBase {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  //CObResourceArray	m_Resources;		/* Child resources */
  CObResourceMap	m_Resources;

  CObResourceFolder*	m_pParent;
  CObResourceHandler*	m_pParentHandler;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObResourceFolder();
  virtual ~CObResourceFolder() { Destroy(); }
  virtual void Destroy (void);

	/* Find a subfolder in the current path */
  CObResourceFolder* FindSubFolder (const char* pPath);
  CObResourceFile*   FindFile      (const char* pFilename);
  CObResourceFile*   FindFullFile  (const char* pFilename);
  CObResourceBase*   FindFullName  (const char* pFilename);

	/* Access or create a new sub-folder or file */
  CObResourceFolder* GetFolderCreate (const char* pPath);
  CObResourceFile*   GetFileCreate   (const char* pFilename);

	/* Get class members */
  //CObResourceArray&   GetResources     (void) { return (m_Resources); }
  CObResourceMap&     GetResources     (void) { return (m_Resources); }
  dword               GetNumResources  (void) { return (m_Resources.GetSize()); }
  CObResourceFolder*  GetParent        (void) { return (m_pParent); }
  CObResourceHandler* GetParentHandler (void) { return (m_pParentHandler); }
  const char*         GetBasePath      (void);

	/* Get the full filename of the resource */
  const char* GetFullName (void);

	/* Abstract methods */
  virtual bool IsFolder (void) const { return (true); }

	/* Set class members */
  void SetParent        (CObResourceFolder*  pParent) { m_pParent        = pParent; }
  void SetParentHandler (CObResourceHandler* pParent) { m_pParentHandler = pParent; }



};
/*===========================================================================
 *		End of Class CObResourceFolder Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obresourcefolder.H
 *=========================================================================*/
