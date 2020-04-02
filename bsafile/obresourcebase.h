/*===========================================================================
 *
 * File:	Obresourcebase.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 4, 2006
 *
 * Defines the CObResourceBase base abstract class.
 *
 *=========================================================================*/
#ifndef __OBRESOURCEBASE_H
#define __OBRESOURCEBASE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../common/oberrorhandler.h"
  #include "../common/obptrarray.h"
  #include "../common/sstring.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObResourceBase Definition
 *
 *=========================================================================*/
class CObResourceBase {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString	m_Name;

  long		m_UserData;
  void*		m_pUserData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObResourceBase() { m_UserData = 0; m_pUserData = NULL; }
  virtual ~CObResourceBase() { Destroy();  }
  virtual void Destroy (void) { m_Name.Empty();  }

	/* Abstract methods */
  virtual bool IsFolder (void) const = 0;

  	/* Check the resource name */
  bool IsName (const char* pString) { return stricmp(m_Name, pString) == 0; }  

  long	      GetUserData     (void) { return (m_UserData); }
  void*	      GetUserDataPtr  (void) { return (m_pUserData); }
  const char* GetName         (void) { return (m_Name); }

	/* Get the full filename with path for the resource */
  virtual const char* GetFullName (void) = 0;

	/* Set class members */
  void SetUserData    (const long    Value) { m_UserData  = Value; }
  void SetUserDataPtr (void*        pValue) { m_pUserData = pValue; }
  void SetName        (const char* pString) { m_Name      = pString; }

};

	/* Arrays of resources */
  typedef CObPtrArray<CObResourceBase>    CObResourceArray;
  typedef CObRefPtrArray<CObResourceBase> CObRefResourceArray;

/*===========================================================================
 *		End of Class CObResourceBase Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obresourcebase.H
 *=========================================================================*/
