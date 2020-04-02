/*===========================================================================
 *
 * File:	Obtime.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 30, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include <windows.h>
#include "obtime.h"
#include "oblogfile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Function - obhirestime_t ObGetTimerFrequency (void);
 *
 * Returns the high resolution timer frequency. Returns 1 on any error.
 *
 *=========================================================================*/
obhirestime_t ObGetTimerFrequency (void) {
  static LARGE_INTEGER  s_Freq = { 0 };
  BOOL			Result;

  if (s_Freq.QuadPart > 1) return (s_Freq.QuadPart);

  Result = QueryPerformanceFrequency(&s_Freq);
  if (!Result) return (1);

  return s_Freq.QuadPart;
}
/*===========================================================================
 *		End of Function ObGetTimerFrequency()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObStartTimer (Timer);
 *
 * Sets the start time of the given timer.
 *
 *=========================================================================*/
void ObStartTimer (obtimer_t& Timer) {
  LARGE_INTEGER Value;
  BOOL          Result;

  Timer.StartTime = 0;

  Result = QueryPerformanceCounter(&Value);
  if (!Result) return;

  Timer.StartTime = Value.QuadPart;
}
/*===========================================================================
 *		End of Function ObStartTimer()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - double ObEndTimer (Timer, pLogMessage);
 *
 * Sets the end time of the given timer and returns the time different
 * in seconds. Returns 0 on any error. If pMessage is not NULL a timer
 * message is output to the log file.
 *
 *=========================================================================*/
double ObEndTimer (obtimer_t& Timer, const SSCHAR* pLogMessage) {
  LARGE_INTEGER Value;
  BOOL          Result;

  Result = QueryPerformanceCounter(&Value);
  if (!Result) return (0);
  Timer.EndTime = Value.QuadPart;

  if (pLogMessage != NULL) ObOutputTimerLog(Timer, pLogMessage);
  return ObGetTimerDelta(Timer);
}
/*===========================================================================
 *		End of Function ObEndTimer()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - double ObGetTimerDelta (Timer);
 *
 * Returns the delta time of the given time in seconds. Returns 0 on
 * any error.
 *
 *=========================================================================*/
double ObGetTimerDelta (obtimer_t& Timer) {
  if (Timer.StartTime <= 1) return (0);
  if (Timer.EndTime   <= 1) return (0);
  return (double)(Timer.EndTime - Timer.StartTime) / (double) ObGetTimerFrequency(); 
}
/*===========================================================================
 *		End of Function ObGetTimerDelta()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObOutputTimerLog (Timer, pMessage);
 *
 * Outputs a standard timer message to the system log file with the given
 * message string.
 *
 *=========================================================================*/
void ObOutputTimerLog(obtimer_t& Timer, const SSCHAR* pMessage) {
  double DeltaTime = ObGetTimerDelta(Timer);

  SystemLog.Printf("%s %g seconds", pMessage ? pMessage : "Timer =", DeltaTime);
}
/*===========================================================================
 *		End of Function ObOutputTimerLog()
 *=========================================================================*/
