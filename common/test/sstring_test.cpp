/*===========================================================================
 *
 * File:	Sstring_test.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "../sstring.h"
#include "stdlib.h"
#include "../oblogfile.h"


/*===========================================================================
 *
 * Function - void CreateRandomString (CSString& Buffer);
 *
 * Helper function that creates a random string.
 *	Length: 0 to RAND_MAX (32768) bytes 
 *	Characters: ASCII, 0 to 255 (mostly alpha-numeric)
 *
 *=========================================================================*/
void CreateRandomString (CSString& Buffer) {
  int    Length;
  int    Index;
  SSCHAR OutputChar;

  Length = rand();
  Buffer.Empty();
  Buffer.SetSize(Length);
  if (Length == 0) return;

  for(Index = 0; Index < Length; Index++) {

    if (rand() % 10 == 0) {
      OutputChar = ((int)(((float)rand() / (float)RAND_MAX) * (127-32))) & 0xFF + 32;
     }
    else {
      OutputChar = ((int)(((float)rand() / (float)RAND_MAX) * 256.0)) & 0xFF;
     }

    Buffer.SetAt(Index, OutputChar);
   }
   
 }
/*===========================================================================
 *		End of Function CreateRandomString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int Test_sstring_RandomStress (NumTests);
 *
 * Runs a number of tests with random string content the given number of 
 * times. Asserts in debug builds on failure. Returns the number of failed 
 * tests in release builds (0 == success).
 *
 *=========================================================================*/
int Test_sstring_RandomStress (const int NumTests) {
  CSString TestString;
  int      FailCount = 0;
  int      TestIndex;
  int      OldLength;
  int      Result;

  for (TestIndex = 0; TestIndex < NumTests; ++TestIndex) {
     CreateRandomString(TestString);

		/* Test updating the string length */
     OldLength = TestString.GetLength();
     TestString.UpdateLength();
     SystemLog.Printf("%d) Old/New Length = %d/%d", TestIndex + 1, OldLength, TestString.GetLength());

		/* Test a simple append */
     OldLength = TestString.GetLength();
     TestString.Append("test", 4);

     if (OldLength + 4 != TestString.GetLength()) {
       assert(false);
       SystemLog.Printf("     Append(): Failed to correctly append string!");
       ++FailCount;
      }

     		/* Test the find operation */
     Result = TestString.Find("test");
     
     if (Result < 0) {
       assert(false);
       SystemLog.Printf("     Find(): Failed to find seeded string!");
       ++FailCount;
      }

     Result = TestString.FindI("TEST");

     if (Result < 0) {
       assert(false);
       SystemLog.Printf("     FindI(): Failed to find seeded string!");
       ++FailCount;
      }

		/* Test self-appending */
    OldLength   = TestString.GetLength();
    TestString += TestString;

    if (OldLength*2 != TestString.GetLength()) {
       assert(false);
       SystemLog.Printf("     +=(): Failed to double string!");
       ++FailCount;
     }

	     	/* Test character appending */
    OldLength   = TestString.GetLength();
    TestString += 'c';

    if (OldLength + 1 != TestString.GetLength()) {
       assert(false);
       SystemLog.Printf("     Append(char): Failed to append character!");
       ++FailCount;
     }

		/* Self assignment */
    TestString = TestString;
    TestString = (const SSCHAR*) TestString;
   }

  return (FailCount);
 }
/*===========================================================================
 *		End of Function Test_sstring_RandomStress()
 *=========================================================================*/
