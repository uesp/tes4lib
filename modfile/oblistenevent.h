/*===========================================================================
 *
 * File:	Oblistenevent.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 29, 2006
 *
 * Defines the CObListenEvent class.
 *
 *=========================================================================*/
#ifndef __OBLISTENEVENT_H
#define __OBLISTENEVENT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
   #include "records/obrecord.h"
   #include "../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Event types */
  #define OB_EVENT_NONE			0
  #define OB_EVENT_ADDRECORD		1
  #define OB_EVENT_CLEANRECORD		2
  #define OB_EVENT_UPDATERECORD		4
  #define OB_EVENT_PREUPDATERECORD	8

  #define OB_EVENTMASK_ALL	0xffff

	/* Return codes */
  #define OB_EVENT_RESULT_ERROR		-1
  #define OB_EVENT_RESULT_OK		0
  #define OB_EVENT_RESULT_WARNING	1

	/* Event flags */
  #define OB_EVENTFLAG_NOCLOSEPREUPDATE	1
  #define OB_EVENTFLAG_NONOTIFYSOURCE	2
  
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Class forward definition */
  //class IObListener;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObListenEvent Definition
 *
 *=========================================================================*/
class CObListenEvent {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRecord*	m_pOldRecord;
  CObRecord*	m_pNewRecord;
  dword		m_Type;
  dword		m_Flags;

  long          m_Source;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObListenEvent() {
	m_pOldRecord = NULL;
	m_pNewRecord = NULL;
	m_Type       = OB_EVENT_NONE;
	m_Flags	     = 0;
	m_Source     = 0;
  }

	/* Get class members */
  CObRecord*   GetOldRecord (void) { return (m_pOldRecord); }
  CObRecord*   GetNewRecord (void) { return (m_pNewRecord); }
  dword        GetType      (void) { return (m_Type); }
  dword        GetFlags     (void) { return (m_Flags); }
  long         GetSource    (void) { return (m_Source); }

	/* Check flag values */
  bool IsFlagNoClosePreUpdate (void) { return ((m_Flags & OB_EVENTFLAG_NOCLOSEPREUPDATE) != 0); }
  bool IsFlagNoNotifySource   (void) { return ((m_Flags & OB_EVENTFLAG_NONOTIFYSOURCE)   != 0); }

	/* Set class members */
  void SetOldRecord (CObRecord* pRecord) { m_pOldRecord = pRecord; }
  void SetNewRecord (CObRecord* pRecord) { m_pNewRecord = pRecord; }
  void SetType      (const dword   Type) { m_Type       = Type; }  
  void SetFlags     (const dword  Flags) { m_Flags      = Flags; }
  void SetSource    (const long     Src) { m_Source     = Src; }

};

	/* Arrays of events */
  typedef CObPtrArray<CObListenEvent>    CObEventArray;
  typedef CObRefPtrArray<CObListenEvent> CObRefEventArray;

/*===========================================================================
 *		End of Class CObListenEvent Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oblistenevent.H
 *=========================================================================*/

