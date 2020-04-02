/*===========================================================================
 *
 * File:	Oblibtest.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testrecord.h"
#include "testtes4.h"
#include "testammo.h"
#include "testappa.h"
#include "testarmo.h"
#include "testbook.h"
#include "testclot.h"
#include "testench.h"
#include "testlevi.h"
#include "testmisc.h"
#include "testscpt.h"
#include "testsgst.h"
#include "testspel.h"
#include "testweap.h"


/*===========================================================================
 *
 * Begin Main Program
 *
 *=========================================================================*/
int main (void) {
  CObEspFile File;
  CObEspFile File2;
  bool       Result;
  /*
  CObRecord*	 pRecord;
  CObMiscRecord* pMiscRecord;
  CObBaseRecord* pBaseRecord;
  CObGroup*      pGroup; //*/

  //pRecord = (CObRecord *) pGroup;
  //pRecord = new CObMiscRecord;
  //pMiscRecord = dynamic_cast < CObMiscRecord* > ( pRecord );
  //return (0);

  SystemLog.Open("oblivtest.log");
  QueryPerformanceFrequency(&g_CounterFreq);

	/* Test record set/get methods */
  TestRecord_Cast();
  TestRecord_SetGet();
  TestTes4_SetGet();
  TestAmmo_SetGet();
  TestAppa_SetGet();
  TestArmo_SetGet();
  TestBook_SetGet();
  TestClot_SetGet();
  TestEnch_SetGet();
  TestLevi_SetGet();
  TestMisc_SetGet();
  TestScpt_SetGet();
  TestSgst_SetGet();
  TestSpel_SetGet();
  TestWeap_SetGet();

	/* Output test records to file */
  TestTes4_Output(File);
  TestRecord_Output(File);
  TestAmmo_Output(File);
  TestAppa_Output(File);
  TestArmo_Output(File);
  TestBook_Output(File);
  TestClot_Output(File);
  TestEnch_Output(File);
  TestLevi_Output(File);
  TestMisc_Output(File);
  TestScpt_Output(File);
  TestSgst_Output(File);
  TestSpel_Output(File);
  TestWeap_Output(File);
  
	/* Save and load file */
  OBTEST_LEVEL("ESP Save/Load")
  
  OBTEST_START_TEST("Save")
	Result = File.Save("testout.esp");
	OBTEST_DOCOMPARE(Result, ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Load")
	Result = File2.Load("testout.esp");
	OBTEST_DOCOMPARE(Result, ==, true)
  OBTEST_END_TEST()

  TestTes4_Input(File);
  TestRecord_Input(File2);
  TestAmmo_Input(File2);
  TestAppa_Input(File2);
  TestArmo_Input(File2);
  TestBook_Input(File2);
  TestClot_Input(File2);
  TestEnch_Input(File2);
  TestLevi_Input(File2);
  TestMisc_Input(File2);
  TestScpt_Input(File2);
  TestSgst_Input(File2);
  TestSpel_Input(File2);
  TestWeap_Input(File2);
 
  return (0);
 }
/*===========================================================================
 *		End of Main Program
 *=========================================================================*/
  

