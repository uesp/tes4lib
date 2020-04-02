/*===========================================================================
 *
 * File:	Obtest.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obtest.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Holds the current testing level */
  CSString g_ObTestLevel;

	/* Count of tests and successes */
  dword g_ObTestCount         = 0;
  dword g_ObSuccessCount      = 0;

	/* Various output options */
  bool  g_ObAbortTestOnFail   = false;
  bool  g_ObOutputTestDetails = false;
  bool  g_ObOutputTestSuccess = true;
  bool  g_ObOutputTestFail    = true;

	/* Used to generate unique form IDs */
  obformid_t g_ObNextFormID = 1;

  LARGE_INTEGER g_CounterFreq;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObTestOutputSuccess (pTest, pDetails, DeltaTime);
 *
 * Outputs a test success message to the log file and optionally to stdout.
 *
 *=========================================================================*/
void ObTestOutputSuccess (const char* pTest, const char* pDetails, const LONGLONG DeltaTime) {
  double Time = (double)DeltaTime / (double) g_CounterFreq.QuadPart;

	/* Output to stdout as required */
  if (g_ObOutputTestSuccess) {
    if (g_ObOutputTestDetails)
      printf ("SUCCESS (%d/%d): %s -- %s (%s)\n", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest, pDetails);
    else
      printf ("SUCCESS (%d/%d): %s -- %s\n", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest);
   }

	/* Output to the log file */
  SystemLog.Printf("SUCCESS (%d/%d): %s -- %s (%s) (%.3g ms)", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest, pDetails, Time * 1000.0);
 }
/*===========================================================================
 *		End of Function ObTestOutputSuccess()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void ObTestOutputFailure (pTest, pDetails, DeltaTime);
 *
 * Outputs a test failure message to the log file and optionally to stdout.
 *
 *=========================================================================*/
void ObTestOutputFailure (const char* pTest, const char* pDetails, const LONGLONG ) {

	/* Output to stdout as required */
  if (g_ObOutputTestFail) {
    if (g_ObOutputTestDetails)
      printf ("FAILED (%d/%d): %s -- %s (%s)\n", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest, pDetails);
    else
      printf ("FAILED (%d/%d): %s -- %s\n", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest);
   }

	/* Output to the log file */
  SystemLog.Printf ("FAILED (%d/%d): %s -- %s (%s)", g_ObSuccessCount, g_ObTestCount, g_ObTestLevel.c_str(), pTest, pDetails);
 }
/*===========================================================================
 *		End of Function ObTestOutputFailure()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void OnTestOutputNote (pString, ...);
 *
 * Outputs a test note to the log file and possibly stdout.
 *
 *=========================================================================*/
void OnTestOutputNote (const char* pString, ...) {
  va_list Args;

  va_start(Args, pString);

  if (g_ObOutputTestDetails) {
    printf ("     ");
    vprintf(pString, Args);
    printf ("\n");
   }

  va_end(Args);

  va_start(Args, pString);
  SystemLog.PrintfV(pString, Args);
  va_end(Args);
 }
/*===========================================================================
 *		End of Function OnTestOutputNote()
 *=========================================================================*/

