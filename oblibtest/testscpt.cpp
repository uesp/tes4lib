/*===========================================================================
 *
 * File:	TestScpt.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testscpt.h"

/*===========================================================================
 *
 * Begin Local Definitions
 *
 *
 *=========================================================================*/
testscpt_t g_TestData = {
	0x00210000,
	"script_test",
	"scriptname script_test"
 };

testscpt_t g_TestValues[] = {
	{ 0x00210001,"script_test", "scriptname script_test" },
	{ 0x00210002,"script_empty", NULL },
	{ 0, NULL, NULL },
  };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestScpt_SetGet (void);
 *
 * Tests basic set/get methods of a SCPT record.
 *
 *=========================================================================*/
bool TestScpt_SetGet (void) {
  CObScptRecord Record;

  OBTEST_LEVEL("SCPT Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Script text")
	Record.SetScriptText(g_TestData.pText);
	OBTEST_DOSTRCOMPARE1(Record.GetScriptText(), ==, g_TestData.pText)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestScpt_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestScpt_Output (File);
 *
 * Outputs basic SCPT records to the given file.
 *
 *=========================================================================*/
bool TestScpt_Output (CObEspFile& File) {
  CObScptRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("SCPT Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_SCPT);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObScptRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pText     != NULL) pRecord->SetScriptText(g_TestValues[Index].pText);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestScpt_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestScpt_Input (File);
 *
 * Checks the values of SCPT records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestScpt_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObScptRecord* pRecord;
  dword		 Index;

  OBTEST_LEVEL("SCPT Input")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
    OnTestOutputNote("Testing Record (%d, '%s')", g_TestValues[Index].FormID, g_TestValues[Index].pEditorID);

    OBTEST_START_TEST("Find record by formID")
        pBase = File.FindFormID(g_TestValues[Index].FormID);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()
    if (pBase == NULL) continue;
    
    OBTEST_START_TEST("Check record type")
	OBTEST_DOCOMPARE(pBase->IsRecord(), ==, true)
    OBTEST_END_TEST()
    if (!pBase->IsRecord()) continue;

    OBTEST_START_TEST("Check record name")
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_SCPT)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_SCPT) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObScptRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script text")
	OBTEST_DOSTRCOMPARE1(pRecord->GetScriptText(), ==, g_TestValues[Index].pText);
    OBTEST_END_TEST()
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestScpt_Input()
 *=========================================================================*/

