/*===========================================================================
 *
 * File:	Obcallback.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 29, 2006
 *
 * Defines the CObCallback class used for a variety of callback purposes.
 *
 *=========================================================================*/
#ifndef __OBCALLBACK_H
#define __OBCALLBACK_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberrorhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Callback return values */
  #define OBCALLBACK_USERABORT    -2
  #define OBCALLBACK_ERROR	  -1
  #define OBCALLBACK_OK		   0
  #define OBCALLBACK_WARNING	   1
  #define OBCALLBACK_NOFUNCTION	   2
  #define OBCALLBACK_NOTPROCESSED  3
  #define OBCALLBACK_INVALIDINPUT  4

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definition */
  class CObCallback;

	/* Callback function definition */
  typedef int (*OBCALLBACK_FUNC) (CObCallback* pCallback);

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObCallback Definition
 *
 * A general purpose callback implementation.
 *
 *=========================================================================*/
class CObCallback {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  OBCALLBACK_FUNC	m_Function;		/* The callback function */

  bool			m_Enabled;		/* Sets whether to use the callback or not */

  CSString		m_Title;		/* Various default callback texts */
  CSString		m_Label;
  bool			m_UpdateTitle;
  bool			m_UpdateLabel;

  void*			m_pUserPtr;		/* User defined data */
  long			m_UserData;			

  int64			m_TotalRecords;		/* Used to compute percent complete */
  int64			m_ProcessRecords;
  int64			m_LastCallbackRecords;	/* Last time the callback was called */

  int64			m_TotalRecords1;		
  int64			m_ProcessRecords1;
  int64			m_LastCallbackRecords1;

  int64			m_CallbackInterval;	/* How often the callback is called */
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObCallback();
  void Destroy (void);

	/* Get class members */
  void*         GetUserPtr        (void) { return (m_pUserPtr); }
  long          GetUserData       (void) { return (m_UserData); }
  int64         GetTotalRecords   (void) { return (m_TotalRecords); }
  int64         GetProcessRecords (void) { return (m_ProcessRecords); }
  float         GetPercentDone    (void);
  const SSCHAR* GetTitle          (void) { return (m_Title); }
  const SSCHAR* GetLabel          (void) { return (m_Label); }
  bool		GetUpdateTitle    (void) { return (m_UpdateTitle); }
  bool		GetUpdateLabel    (void) { return (m_UpdateLabel); }

	/* Check if the callback object is valid or not */
  bool IsValid (void) { return (m_Function != NULL && m_Enabled); }

	/* Reset the callback progress */
  void Reset (void);
  
	/* Set class members */
  void SetUserData         (const long       Data) { m_UserData = Data; }
  void SetUserPtr          (      void*     pData) { m_pUserPtr = pData; }
  void SetFunction         (OBCALLBACK_FUNC  Func) { m_Function = Func; }
  void SetEnable           (const bool      Value) { m_Enabled  = Value; }
  void SetUpdateTitle      (const bool      Value) { m_UpdateTitle = Value; }
  void SetUpdateLabel      (const bool      Value) { m_UpdateLabel = Value; }
  void SetCallbackInterval (const int64     Value) { m_CallbackInterval = Value; }
  void SetTotalRecords     (const int64     Value) { m_TotalRecords     = Value; }
  void SetTotalRecords1    (const int64     Value) { m_TotalRecords1    = Value; }
  void SetLabel	           (const SSCHAR* pString, ...);
  void SetTitle	           (const SSCHAR* pString, ...);

	/* Update the callback if required */
  int ForceCallback   (const int64 ProcessRecords);
  int UpdateCallback  (const int64 ProcessRecords);
  int UpdateCallback1 (const int64 ProcessRecords);

};
/*===========================================================================
 *		End of Class CObCallback Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obcallback.H
 *=========================================================================*/
