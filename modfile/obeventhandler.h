/*===========================================================================
 *
 * File:	Obeventhandler.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 29, 2006
 *
 * Defines the CObEventHandler class.
 *
 *=========================================================================*/
#ifndef __OBEVENTHANDLER_H
#define __OBEVENTHANDLER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oblistener.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEventHandler Definition
 *
 *=========================================================================*/
class CObEventHandler {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRefListenerArray	m_Listeners;
  CObEventArray		m_QueuedEvents;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEventHandler();
  virtual ~CObEventHandler() { Destroy(); }
  virtual void Destroy (void);

	/* Add/remove a listener */
  void AddListener    (IObListener* pListener) { if (pListener != NULL) m_Listeners.Add(pListener); }
  void RemoveListener (IObListener* pListener) { m_Listeners.Delete(pListener); }

	/* Combine any similar queued events */
  void CombineQueuedEvents (void); 

	/* Queue an event to send later */
  void QueueEvent (CObListenEvent* pEvent) { if (pEvent != NULL) m_QueuedEvents.Add(pEvent); }

	/* Send an event immediately */
  void SendEvent          (CObListenEvent* pEvent);
  void SendAddEvent       (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags = 0);
  void SendCleanEvent     (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags = 0);
  void SendUpdateEvent    (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags = 0);
  void SendPreUpdateEvent (CObRecord* pRecord, const dword Flags = 0, long Source = 0);
  
        /* Send all queued events */
  void SendQueuedEvents (void);


};
/*===========================================================================
 *		End of Class CObEventHandler Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obeventhandler.H
 *=========================================================================*/
