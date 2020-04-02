/*===========================================================================
 *
 * File:	Obresourceinstance.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Defines the CObResourceInstance class
 *
 *=========================================================================*/
#ifndef __OBRESOURCEINSTANCE_H
#define __OBRESOURCEINSTANCE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbsafile.h"
  #include "../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Resource types */
  #define OB_RESOURCETYPE_UNKNOWN 0
  #define OB_RESOURCETYPE_TEXT	  1
  #define OB_RESOURCETYPE_HTML	  2
  #define OB_RESOURCETYPE_XML	  3
  #define OB_RESOURCETYPE_IMAGE	  4
  #define OB_RESOURCETYPE_NIF	  5
  #define OB_RESOURCETYPE_SOUND	  6

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definitions */
  class CObResourceFile;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceInstance Definition
 *
 *=========================================================================*/
class CObResourceInstance {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObBsaFileRecord*	m_pBsaRecord;		/* Parent record if in a BSA file */

  CSString		m_Filename;		/* Just the filename for a non-BSA file */
  CSString		m_FullFilename;		/* Complete path+filename for a non-BSA file */

  int64			m_Filesize;
  bool			m_HasFilesize;

  dword64		m_Filetime;
  bool			m_HasFiletime;

  CObResourceFile*	m_pParent;

  long			m_UserData;
  void*			m_pUserData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	

  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObResourceInstance();
  virtual ~CObResourceInstance() { Destroy(); }
  virtual void Destroy (void);

	/* Get class members */
  CObBsaFileRecord* GetBsaRecord       (void) { return (m_pBsaRecord); }
  const char*       GetFilename        (void);
  const char*       GetFullFilename    (void);
  const char*       GetFullFilenameAbs (void);
  CObResourceFile*  GetParent          (void) { return (m_pParent); }
  const char*       GetBasePath        (void);

	/* Determine the type of the resource */
  int GetResourceType (void);

  bool	HasFilesize (void) const { return (m_HasFilesize); }
  bool	HasFiletime (void) const { return (m_HasFiletime); }

	/* Get the filesize/time of a resource */
  bool    GetFilesize (int64& Filesize);
  int64   GetFilesize (void);
  bool    GetFiletime (dword64& Filetime);
  dword64 GetFiletime (void);

	/* Set class members */
  void SetBsaRecord (CObBsaFileRecord* pRecord) { m_pBsaRecord = pRecord; }
  void SetFilename  (const char*       pString);
  void SetParent    (CObResourceFile*    pFile) { m_pParent = pFile; }
  void SetFilesize  (const int64          Size) { m_Filesize = Size; m_HasFilesize = true; }
  void SetFiletime  (const dword64        Time) { m_Filetime = Time; m_HasFiletime = true; }

  void SetFilesize  (const dword Low, const dword High) { 
	m_Filesize    = (int64) (((dword64)Low) | ((dword64)High)<<32);
	m_HasFilesize = true; }

  void SetFiletime  (const dword Low, const dword High) { 
	m_Filetime    = (dword64) (((dword64)Low) | ((dword64)High)<<32);
	m_HasFiletime = true; }
    
	/* Update the filesize of the resource instance */
  bool UpdateFileInfo (void);

};


	/* Arrays of resource instances */
  typedef CObPtrArray<CObResourceInstance>     CObResourceInstanceArray;
  typedef CObRefPtrArray<CObResourceInstance>  CObRefResourceInstanceArray;

/*===========================================================================
 *		End of Class CObResourceInstance Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obresourceinstance.H
 *=========================================================================*/
