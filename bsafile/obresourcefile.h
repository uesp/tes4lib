/*===========================================================================
 *
 * File:	Obresourcefile.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Defines the CObResourceFile class for a single resource file.
 *
 *=========================================================================*/
#ifndef __OBRESOURCEFILE_H
#define __OBRESOURCEFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obresourcebase.h"
  #include "obresourceinstance.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definition */
  class CObResourceFolder;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceFile Definition
 *
 *=========================================================================*/
class CObResourceFile : public CObResourceBase {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObResourceInstanceArray	m_Instances;
  int				m_ResourceType;
  
  CObResourceFolder*		m_pParent;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObResourceFile();
  virtual ~CObResourceFile() { Destroy(); }
  virtual void Destroy (void);

  	/* Add a new instance */
  CObResourceInstance* AddInstance (CObBsaFileRecord* pRecord);
  CObResourceInstance* AddInstance (const char* pFilename);

	/* Abstract methods */
  virtual bool IsFolder (void) const { return (false); }

	/* Get class members */
  CObResourceInstanceArray& GetInstances    (void) { return (m_Instances); }
  dword                     GetNumInstances (void) { return (m_Instances.GetSize()); }
  CObResourceInstance*	    GetMainInstance (void) { return (m_Instances.GetAt(0)); }
  CObResourceFolder*        GetParent       (void) { return (m_pParent); }
  const char*               GetBasePath     (void);
  int64			    GetFilesize     (void);
  dword64		    GetFiletime     (void);
  int			    GetResourceType (void) { return (m_ResourceType); }

	/* Get the full filename of the resource */
  const char* GetFullName (void);
  const char* GetCSName   (void);

	/* Checks if the resource is in the given path or not */
  bool IsInPath (const char* pPath);
  
	/* Set which resource instance is the main one */
  void SetMainInstances (CObResourceInstance* pInstance);

	/* Set class members */
  void SetParent (CObResourceFolder* pFolder) { m_pParent = pFolder; }

};
/*===========================================================================
 *		End of Class CObResourceFile Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obresourcefile.H
 *=========================================================================*/
