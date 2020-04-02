/*===========================================================================
 *
 * File:	Oberrorhandler.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 5, 2006
 *
 * Defines the CObErrorHandler class for recording library errors.
 *
 *=========================================================================*/
#ifndef __OBERRORHANDLER_H
#define __OBERRORHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberror.h"

	/* Platform specific includes */  
#ifdef _WIN32
#else
  #include "sys/errno.h"
#endif

/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
	
	/* Number of error records saved at any one time (arbitrary) */
  #define OB_MAX_ERRORS	32

	/* Number of callbacks allowed at one time */
  #define OB_MAX_ERROR_CALLBACKS 10

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Error callbacks */
  typedef void (*FNOBERRORCALLBACK) (CObError* pError, const dword UserData);

  struct oberror_callback_t {
	dword		  UserData;
	FNOBERRORCALLBACK Function;
   };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObErrorHandler Definition
 *
 * A simple error handler for recording errors occuring during this
 * libraries execution.
 *
 *=========================================================================*/
class CObErrorHandler {

  /*---------- Begin Protected Class Members --------------------*/
protected:

	/* Use a very simple array of pointers for storing errors */
  CObError*		m_pRecords[OB_MAX_ERRORS];
  dword			m_NumRecords;		

  oberror_callback_t	m_Callbacks[OB_MAX_ERROR_CALLBACKS];
  dword			m_NumCallbacks;

  CSString		m_MsgPrefix;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper method to clear the array */
  void DeleteErrors (void);
  void DeleteHalf   (void);

	/* Perform any required callbacks for he given error */
  void DoCallbacks (CObError* pError);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObErrorHandler();
  virtual ~CObErrorHandler();
  virtual void Destroy (void);

	/* Attempt to add a an error callback function */
  bool AddCallback (FNOBERRORCALLBACK Function, const dword UserData);

	/* General add error methods */
  void AddError  (const int Type, const int Code, const int SubCode, const int Level, const SSCHAR* pString, ...);
  void AddErrorV (const int Type, const int Code, const int SubCode, const int Level, const SSCHAR* pString, va_list Args);

	/* Clear all errors */
  void ClearErrors (void) { DeleteErrors(); }

	/* Get class members */
  CObError* GetError     (const dword Index) { return ((Index < m_NumRecords) ? m_pRecords[Index]: NULL); }
  CObError* GetLastError (void)              { return ((m_NumRecords > 0) ? m_pRecords[m_NumRecords - 1]: NULL); }
  dword     GetNumErrors (void) const        { return (m_NumRecords); }

	/* Remove a previously set callback */
  bool RemoveCallback (FNOBERRORCALLBACK Function);

	/* Removes the last error, if any, from the list */
  void RemoveLastError (void);

	/* Set class members */
  void SetMessagePrefix (const char* pString) { m_MsgPrefix = pString; }

};
/*===========================================================================
 *		End of Class CObErrorHandler Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Global Definitions
 *
 *=========================================================================*/

	/* The global error handler object (must be valid) */
  extern CObErrorHandler* ObErrorHandler;

  bool AddObUserError    (const int Code, const SSCHAR* pString = NULL, ...);
  bool AddObSystemError  (const SSCHAR* pString = NULL, ...);
  bool AddObZLibError    (const int Code, const SSCHAR* pString = NULL, ...);
  bool AddObGeneralError (const SSCHAR* pString = NULL, ...);
  bool AddObWindowsError (const SSCHAR* pString = NULL, ...);


/*===========================================================================
 *		End of Global Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oberrorhandler.H
 *=========================================================================*/

