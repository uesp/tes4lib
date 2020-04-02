/*===========================================================================
 *
 * File:	Obeventhandler.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 29, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obeventhandler.h"


/*===========================================================================
 *
 * Class CObEventHandler Constructor
 *
 *=========================================================================*/
CObEventHandler::CObEventHandler () {

}
/*===========================================================================
 *		End of Class CObEventHandler Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEventHandler::Destroy (void) {
  m_QueuedEvents.Destroy();
  m_Listeners.Destroy();
}
/*===========================================================================
 *		End of Class Method CObEventHandler::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void CombineQueuedEvents (void);
 *
 * Combine all similar queued events.
 *
 *=========================================================================*/
void CObEventHandler::CombineQueuedEvents (void) {
  /* TODO? */
}
/*===========================================================================
 *		End of Class Method CObEventHandler::CombineQueuedEvents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void SendEvent (pEvent);
 *
 *=========================================================================*/
void CObEventHandler::SendEvent (CObListenEvent* pEvent) {
  IObListener*	pListener;
  dword		Index;

	/* Ignore invalid input */
  if (pEvent == NULL) return;

  for (Index = 0; Index < m_Listeners.GetSize(); ++Index) {
    pListener = m_Listeners[Index];

    if ((pEvent->GetType() & pListener->GetListenEvents()) != 0) {
       switch (pEvent->GetType()) {
         case OB_EVENT_ADDRECORD:	pListener->OnListenAddRecord(pEvent);       break;
	 case OB_EVENT_CLEANRECORD:	pListener->OnListenCleanRecord(pEvent);     break;
	 case OB_EVENT_UPDATERECORD:	pListener->OnListenUpdateRecord(pEvent);    break;
	 case OB_EVENT_PREUPDATERECORD:	pListener->OnListenPreUpdateRecord(pEvent); break;
	 default: assert(false); break;
       }
    }
  }

}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendEvent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void SendQueuedEvents (void);
 *
 * Send all queued events to listeners.
 *
 *=========================================================================*/
void CObEventHandler::SendQueuedEvents (void) {
  dword Index;

  for (Index = 0; Index < m_QueuedEvents.GetSize(); ++Index) {
    SendEvent(m_QueuedEvents[Index]);
  }

  m_QueuedEvents.Destroy();
}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendQueuedEvents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void SendAddEvent (pNewRecord, pOldRecord, Flags);
 *
 *=========================================================================*/
void CObEventHandler::SendAddEvent (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags) {
  CObListenEvent Event;

  Event.SetType(OB_EVENT_ADDRECORD);
  Event.SetNewRecord(pNewRecord);
  Event.SetOldRecord(pOldRecord);
  Event.SetFlags(Flags);

  SendEvent(&Event);
}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendAddEvent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void SendCleanEvent (pNewRecord, pOldRecord, Flags);
 *
 *=========================================================================*/
void CObEventHandler::SendCleanEvent (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags) {
  CObListenEvent Event;

  Event.SetType(OB_EVENT_CLEANRECORD);
  Event.SetNewRecord(pNewRecord);
  Event.SetOldRecord(pOldRecord);
  Event.SetFlags(Flags);

  SendEvent(&Event);
}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendCleanEvent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEventHandler Method - void SendUpdateEvent (pNewRecord, pOldRecord, Flags);
 *
 *=========================================================================*/
void CObEventHandler::SendUpdateEvent (CObRecord* pNewRecord, CObRecord* pOldRecord, const dword Flags) {
  CObListenEvent Event;

  Event.SetType(OB_EVENT_UPDATERECORD);
  Event.SetNewRecord(pNewRecord);
  Event.SetOldRecord(pOldRecord);
  Event.SetFlags(Flags);

  SendEvent(&Event);
}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendUpdateEvent()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Class CObEventHandler Method - void SendPreUpdateEvent (pRecord, Flags, Source);
 *
 *=========================================================================*/
void CObEventHandler::SendPreUpdateEvent (CObRecord* pRecord, const dword Flags, const long Source) {
  CObListenEvent Event;

  Event.SetType(OB_EVENT_PREUPDATERECORD);
  Event.SetOldRecord(pRecord);
  Event.SetFlags(Flags);
  Event.SetSource(Source);

  SendEvent(&Event);
}
/*===========================================================================
 *		End of Class Method CObEventHandler::SendPreUpdateEvent()
 *=========================================================================*/