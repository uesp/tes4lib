/*===========================================================================
 *
 * File:	Obtime.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 30, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBTIME_H
#define __OBTIME_H


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
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used to hold timing information */
  typedef int64 obhirestime_t;

	/* Used to measure the time of an event */
  struct obtimer_t {
	obhirestime_t	StartTime;
	obhirestime_t	EndTime;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Functions for accurately timing */
  obhirestime_t ObGetTimerFrequency (void);

  void		ObStartTimer     (obtimer_t& Timer);
  double	ObEndTimer       (obtimer_t& Timer, const SSCHAR* pLogMessage = NULL);
  double        ObGetTimerDelta  (obtimer_t& Timer);

  void	ObOutputTimerLog(obtimer_t& Timer, const SSCHAR* pMessage);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obtime.H
 *=========================================================================*/
