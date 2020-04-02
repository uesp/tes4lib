/*===========================================================================
 *
 * File:	TestMisc.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testmisc.h"

/*===========================================================================
 *
 * Begin Local Definitions
 *
 *
 *=========================================================================*/
testmisc_t g_TestData = {
	0x00200000,
	{ 1, 2.0f }, 
	0x1234,
	"misc_test",
	"Misc Name",
	"model.nif",
	"icon.dds"
 };

testmisc_t g_TestValues[] = {
	{ 0x00200001, { 1, 2.0f }, 0x1234, "misc_test",	"Misc Name", "model.nif", "icon.dds" },
	{ 0x00200002, { 0, 0 }, 0, "misc_null",	NULL, NULL, NULL },
	{ 0, { 0, 0 }, 0, NULL, NULL, NULL, NULL },
  };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestMisc_SetGet (void);
 *
 * Tests basic set/get methods of a MISC record.
 *
 *=========================================================================*/
bool TestMisc_SetGet (void) {
  CObMiscRecord Record;

  OBTEST_LEVEL("MISC Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Script ID")
	Record.SetScript(g_TestData.ScriptID);
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, g_TestData.ScriptID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Item Name")
	Record.SetItemName(g_TestData.pItemName);
	OBTEST_DOSTRCOMPARE(Record.GetItemName(), ==, g_TestData.pItemName)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestMisc_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestMisc_Output (File);
 *
 * Outputs basic MISC records to the given file.
 *
 *=========================================================================*/
bool TestMisc_Output (CObEspFile& File) {
  CObMiscRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("MISC Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_MISC);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObMiscRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);
    if (g_TestValues[Index].ScriptID  != OB_FORMID_NULL) pRecord->SetScript(g_TestValues[Index].ScriptID);

    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);

   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestMisc_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestMisc_Input (File);
 *
 * Checks the values of MISC records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestMisc_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObMiscRecord* pRecord;
  dword		 Index;

  OBTEST_LEVEL("MISC Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_MISC)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_MISC) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObMiscRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check item name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetItemName(), ==, g_TestValues[Index].pItemName);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check model")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel(), ==, g_TestValues[Index].pModel);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check icon")
	OBTEST_DOSTRCOMPARE1(pRecord->GetIcon(), ==, g_TestValues[Index].pIcon);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script")
	OBTEST_DOINTCOMPARE(pRecord->GetScript(), ==, g_TestValues[Index].ScriptID);
    OBTEST_END_TEST()
    
    OBTEST_START_TEST("Check weight")
	OBTEST_DOINTCOMPARE(pRecord->GetWeight(), ==, g_TestValues[Index].Data.Weight);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check value")
	OBTEST_DOINTCOMPARE(pRecord->GetValue(), ==, g_TestValues[Index].Data.Value);
    OBTEST_END_TEST()

   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestMisc_Input()
 *=========================================================================*/

