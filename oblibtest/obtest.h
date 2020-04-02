/*===========================================================================
 *
 * File:	Obtest.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBTEST_H
#define __OBTEST_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "windows.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

  #define OBTEST_LEVEL(String) g_ObTestLevel = String;

  #define OBTEST_START_TEST(String) { \
	const char* l_TestName = String; \
	bool l_TestResult = false; \
	CSString l_TestDetails; \
	LARGE_INTEGER l_StartTime; \
	LARGE_INTEGER l_EndTime; \
	QueryPerformanceCounter(&l_StartTime); \
	++g_ObTestCount;

  #define OBTEST_END_TEST() \
	QueryPerformanceCounter(&l_EndTime); \
	if (l_TestResult) { \
		++g_ObSuccessCount; \
		ObTestOutputSuccess(l_TestName, l_TestDetails, l_EndTime.QuadPart - l_StartTime.QuadPart); \
	 } else { \
		ObTestOutputFailure(l_TestName, l_TestDetails, l_EndTime.QuadPart - l_StartTime.QuadPart); \
		if (g_ObAbortTestOnFail) return (false); \
	 } }


  #define OBTEST_DOCOMPARE(Value1, CmpOp, Value2) \
	l_TestDetails = #Value1 " " #CmpOp " " #Value2; \
	l_TestResult = (Value1) CmpOp (Value2); 

  #define OBTEST_DOINTCOMPARE(Value1, CmpOp, Value2) \
	l_TestDetails.Format("%s %s %d", #Value1, #CmpOp, Value2); \
	l_TestResult = (Value1) CmpOp (Value2); 

  #define OBTEST_DOFLTCOMPARE(Value1, CmpOp, Value2) \
	l_TestDetails.Format("%s %s %g", #Value1, #CmpOp, Value2); \
	l_TestResult = (Value1) CmpOp (Value2); 

  #define OBTEST_DOSTRCOMPARE(Value1, CmpOp, Value2)  \
	l_TestDetails.Format("%s %s \"%s\"", #Value1, #CmpOp, Value2); \
	l_TestResult = (strcmp((Value1), (Value2)) CmpOp 0);

  #define OBTEST_DOSTRCOMPARE1(Value1, CmpOp, Value2)  \
	if (Value2 == NULL) { \
	  l_TestDetails.Format("%s %s \"\"", #Value1, #CmpOp); \
	  l_TestResult = (strcmp((Value1), ("")) CmpOp 0);	 } \
	else { \
	  l_TestDetails.Format("%s %s \"%s\"", #Value1, #CmpOp, Value2); \
	  l_TestResult = (strcmp((Value1), (Value2)) CmpOp 0); 	 }


/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

  void ObTestOutputFailure (const char* pTest, const char* pDetails, const LONGLONG DeltaTime);
  void ObTestOutputSuccess (const char* pTest, const char* pDetails, const LONGLONG DeltaTime);
  void OnTestOutputNote (const char* pString, ...);

 
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/
  extern CSString   g_ObTestLevel;
  extern dword      g_ObTestCount;
  extern dword      g_ObSuccessCount;
  extern obformid_t g_ObNextFormID;
  extern bool       g_ObAbortTestOnFail;
  extern bool       g_ObOutputTestDetails;
  extern bool       g_ObOutputTestSuccess;
  extern bool       g_ObOutputTestFail;
  extern LARGE_INTEGER g_CounterFreq;

  inline obformid_t GetNextObFormID (void) { return (g_ObNextFormID++); }
  
/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obtest.H
 *=========================================================================*/
