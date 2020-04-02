/*===========================================================================
 *
 * File:	Oberrorhandler.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 5, 2006
 *
 * Implements the CObErrorHandler class used to record library errors.
 *
 *=========================================================================*/

	/* Include Files */
#include "stdlib.h"
#include "oberrorhandler.h"
#include "oblogfile.h"
#include "windows.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* The global error handler object */
  CObErrorHandler  g_ObErrorHandler;
  CObErrorHandler* ObErrorHandler = &g_ObErrorHandler;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Constructor
 *
 *=========================================================================*/
CObErrorHandler::CObErrorHandler () {
  m_NumRecords   = 0;
  m_NumCallbacks = 0;

 }
/*===========================================================================
 *		End of Class CObErrorHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Destructor
 *
 *=========================================================================*/
CObErrorHandler::~CObErrorHandler () {
  DeleteErrors();
 }
/*===========================================================================
 *		End of Class CObErrorHandler Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void Destroy (void);
 *
 * Clears the contents of the object.
 *
 *=========================================================================*/
void CObErrorHandler::Destroy (void) {
  DeleteErrors();
  m_NumCallbacks = 0;
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - bool AddCallback (Function, UserData);
 *
 * Attempts to add the callback to the error handler.
 *
 *=========================================================================*/
bool CObErrorHandler::AddCallback (FNOBERRORCALLBACK Function, const dword UserData) {

  if (m_NumCallbacks > OB_MAX_ERROR_CALLBACKS) return (false);

  m_Callbacks[m_NumCallbacks].Function = Function;
  m_Callbacks[m_NumCallbacks].UserData = UserData;

  ++m_NumCallbacks;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::AddCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void AddErrorV (Type, Code, SubCode, Level, pString, ...);
 *
 * Adds a new error to the end of the array.
 *
 *=========================================================================*/
void CObErrorHandler::AddError (const int Type, const int Code, const int SubCode, 
				const int Level, const SSCHAR* pString, ...) {
  va_list Args;

  va_start(Args, pString);
  AddErrorV(Type, Code, SubCode, Level, pString, Args);
  va_end(Args);
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::AddErrorV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void AddErrorV (Type, Code, SubCode, Level, pString, Args);
 *
 * Adds a new error to the end of the array.
 *
 *=========================================================================*/
void CObErrorHandler::AddErrorV (const int Type, const int Code, const int SubCode,
				 const int Level, const SSCHAR* pString, va_list Args) {

	/* Free old errors as needed */
  if (m_NumRecords >= OB_MAX_ERRORS) DeleteHalf();

  m_pRecords[m_NumRecords] = new CObError;
  ++m_NumRecords;

  if (m_MsgPrefix.IsEmpty()) {
    CSString Buffer(m_MsgPrefix);
    Buffer += pString;
    m_pRecords[m_NumRecords - 1]->CreateV(Type, Code, SubCode, Level, Buffer, Args);
  }
  else
    m_pRecords[m_NumRecords - 1]->CreateV(Type, Code, SubCode, Level, pString, Args);

	/* Output log message */
  SystemLog.ErrPrintf("*** %s ***", m_pRecords[m_NumRecords - 1]->GetErrorTypeString().c_str());
  SystemLog.ErrPrintf("               Code = %d (%d)", Code, SubCode);
  SystemLog.ErrPrintf("              Level = %s", m_pRecords[m_NumRecords - 1]->GetErrorLevelString().c_str());
  SystemLog.ErrPrintf("       User Message = %s", m_pRecords[m_NumRecords - 1]->GetErrorMessage());
  SystemLog.ErrPrintf("        Description = %s", m_pRecords[m_NumRecords - 1]->GetErrorString().c_str());

	/* Call any registered callback functions */
  DoCallbacks(m_pRecords[m_NumRecords - 1]);
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::AddErrorV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void DeleteErrors (void);
 *
 * Protected class method to delete all currently stored errors.
 *
 *=========================================================================*/
void CObErrorHandler::DeleteErrors (void) {
  dword Index;

  for (Index = 0; Index < m_NumRecords; ++Index) {
    delete m_pRecords[Index];
   }

  m_NumRecords = 0;
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::DeleteErrors()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void DeleteHalf (void);
 *
 * Protected class method that ensures there is at least OB_MAX_ERRORS/2
 * free records. Deletes the oldest records to make room as needed.
 *
 *=========================================================================*/
void CObErrorHandler::DeleteHalf (void) {
  dword HalfCount = OB_MAX_ERRORS / 2;
  dword Index;

	/* Ignore if there aren't enough records yet */
  if (m_NumRecords <= HalfCount) return;

	/* Delete some of the older records */
  for (Index = 0; Index < m_NumRecords - HalfCount; ++Index) {
    delete m_pRecords[Index];
    m_pRecords[Index] = NULL;
   }

	/* Shift array to compensate for deleted records */
  for (Index = 0; Index < HalfCount; ++Index) {
    m_pRecords[Index] = m_pRecords[m_NumRecords - HalfCount + Index];
   }

  m_NumRecords = HalfCount;
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::DeleteHalf()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void DoCallbacks (pError);
 *
 * Calls any registered callbacks for the given error.
 *
 *=========================================================================*/
void CObErrorHandler::DoCallbacks (CObError* pError) {
  dword Index;

  for (Index = 0; Index < m_NumCallbacks; ++Index) {
    m_Callbacks[Index].Function(pError, m_Callbacks[Index].UserData);
   }

 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::DoCallbacks()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - bool RemoveCallback (Function);
 *
 *=========================================================================*/
bool CObErrorHandler::RemoveCallback (FNOBERRORCALLBACK Function) {
  dword Index;

  for (Index = 0; Index < m_NumCallbacks; ++Index) {
    if (m_Callbacks[Index].Function == Function) {
      memmove(m_Callbacks + Index, m_Callbacks + Index + 1, sizeof(oberror_callback_t) * (m_NumCallbacks - Index - 1)); 
      --m_NumCallbacks;
      return (true);
     }
   }

  return (false);
 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::RemoveCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObErrorHandler Method - void RemoveLastError (void);
 *
 * Removes the last error that occurred from the list (if any). 
 *
 *=========================================================================*/
void CObErrorHandler::RemoveLastError (void) {

  if (m_NumRecords > 0) {
    delete m_pRecords[m_NumRecords - 1];
    --m_NumRecords;
   }

 }
/*===========================================================================
 *		End of Class Method CObErrorHandler::RemoveLastError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddObSystemError (pString, ...);
 *
 * Add the last system error. Returns false so it can be used in the 
 * following manner:
 *
 *	if (SomethingWrong) return AddObSystemError("Message");
 *
 *=========================================================================*/
bool AddObSystemError (const SSCHAR* pString, ...) {
  va_list Args;
  int     ErrorCode = errno;

  va_start(Args, pString);
  ObErrorHandler->AddErrorV(OBERR_TYPE_SYSTEM, ErrorCode, 0, OBERR_LEVEL_ERROR, pString, Args);
  va_end(Args);

  return (false);
 }
/*===========================================================================
 *		End of Function AddObSystemError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddObUserError (Code, pString, ...);
 *
 * Add a user defined error. Returns false.
 *
 *=========================================================================*/
bool AddObUserError (const int Code, const SSCHAR* pString, ...) {
  va_list Args;
  
  va_start(Args, pString);
  ObErrorHandler->AddErrorV(OBERR_TYPE_USER, Code, 0, OBERR_LEVEL_ERROR, pString, Args);
  va_end(Args);

  return (false);
 }
/*===========================================================================
 *		End of Function AddObUserError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddObGeneralError (pString, ...);
 *
 * Add a user defined error. Returns false.
 *
 *=========================================================================*/
bool AddObGeneralError (const SSCHAR* pString, ...) {
  va_list Args;
  
  va_start(Args, pString);
  ObErrorHandler->AddErrorV(OBERR_TYPE_GENERAL, -1, 0, OBERR_LEVEL_ERROR, pString, Args);
  va_end(Args);

  return (false);
 }
/*===========================================================================
 *		End of Function AddObGeneralError()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool AddObZLibError (const int Code, const SSCHAR* pString = NULL, ...);
 *
 * Adds a new zLib error. Returns false.
 *
 *=========================================================================*/
bool AddObZLibError (const int Code, const SSCHAR* pString, ...) {
  va_list Args;
  
  va_start(Args, pString);
  ObErrorHandler->AddErrorV(OBERR_TYPE_ZLIB, Code, errno, OBERR_LEVEL_ERROR, pString, Args);
  va_end(Args);

  return (false);
 }
/*===========================================================================
 *		End of Function AddObZLibError()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - bool AddObWindowsError (const SSCHAR* pString, ...);
 *
 * Adds the last recorded windows error message.
 *
 *=========================================================================*/
bool AddObWindowsError (const SSCHAR* pString, ...) {
  va_list Args;
  dword   Code = GetLastError();
  
  va_start(Args, pString);
  ObErrorHandler->AddErrorV(OBERR_TYPE_WINDOWS, Code, 0, OBERR_LEVEL_ERROR, pString, Args);
  va_end(Args);

  return (false);
}
/*===========================================================================
 *		End of Function AddObWindowsError()
 *=========================================================================*/
