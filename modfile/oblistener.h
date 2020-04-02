/*===========================================================================
 *
 * File:	Oblistener.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 29, 2006
 *
 * Defines the IObListener interface.
 *
 *=========================================================================*/
#ifndef __OBLISTENER_H
#define __OBLISTENER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oblistenevent.h"
  #include "../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class IObListener Definition
 *
 *=========================================================================*/
class IObListener {

  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Events */
  virtual int OnListenAddRecord       (CObListenEvent* pEvent) = 0;
  virtual int OnListenCleanRecord     (CObListenEvent* pEvent) = 0;
  virtual int OnListenUpdateRecord    (CObListenEvent* pEvent) = 0;
  virtual int OnListenPreUpdateRecord (CObListenEvent* pEvent) = 0;
   
  virtual int GetListenEvents (void) = 0;   //Which events the listener wants

};

	/* Array of listeners */
  typedef CObPtrArray<IObListener>    CObListenerArray;
  typedef CObRefPtrArray<IObListener> CObRefListenerArray;

/*===========================================================================
 *		End of Class IObListener Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oblistener.H
 *=========================================================================*/

