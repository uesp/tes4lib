/*===========================================================================
 *
 * File:	Testappa.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testappa.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *	obformid_t	FormID;
 *	obappadata_t	Data;
 *		byte	Type;
 *		dword	Value;
 *		float	Weight;
 *		float	Quality;
 *	obformid_t	ScriptID;
 *	const SSCHAR*	pEditorID;
 *	const SSCHAR*	pItemName;
 *	const SSCHAR*	pModel;
 *	const SSCHAR*	pIcon;
 *
 *=========================================================================*/
testappa_t g_TestData = {
	0x00160000,
	{ 0, 1, 2.0f, 3.0f }, 
	0x567,
	"appa_test",
	"Apparatus Name",
	"model.nif",
	"icon.dds",
 };

testappa_t g_TestValues[] = {
	{ 0x00160001, { 0, 1, 2.0f, 3.0f }, 0x567,
		"appa_test", "Apparatus Name", "model.nif", "icon.dds" },
	{ 0x00160002, { OB_APPATYPE_MORTAR, 1, 2.0f, 3.0f }, 0x567,
		"appa_mortar", "Apparatus Name", "model.nif", "icon.dds" },
	{ 0x00160003, { OB_APPATYPE_RETORT, 1, 2.0f, 3.0f }, 0,
		"appa_retort", "Apparatus Name", "model.nif", "icon.dds" },
	{ 0x00160004, { OB_APPATYPE_ALEMBIC, 1, 2.0f, 3.0f }, 0,
		"appa_alembic", "Apparatus Name", "model.nif", "icon.dds" },
	{ 0x00160005, { OB_APPATYPE_CALCINATOR, 1, 2.0f, 3.0f }, 0,
		"appa_calcinator", "Apparatus Name", "model.nif", "icon.dds" },
	{ 0x00160006, { 0, 0, 0, 0 }, 0,
		"appa_null", NULL, NULL, NULL },
	{ 0, { 0, 0, 0, 0 }, 0, NULL, NULL, NULL, NULL },
  };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAppa_SetGet (void);
 *
 * Tests basic set/get methods of an APPA record.
 *
 *=========================================================================*/
bool TestAppa_SetGet (void) {
  CObAppaRecord Record;

  OBTEST_LEVEL("APPA Set/Get")
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

  OBTEST_START_TEST("Quality")
	Record.SetQuality(g_TestData.Data.Quality);
	OBTEST_DOINTCOMPARE(Record.GetQuality(), ==, g_TestData.Data.Quality)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

    OBTEST_START_TEST("Type")
	Record.SetWeight(g_TestData.Data.Type);
	OBTEST_DOINTCOMPARE(Record.GetType(), ==, g_TestData.Data.Type)
  OBTEST_END_TEST()
  
  return (true);
 }
/*===========================================================================
 *		End of Function TestAppa_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAppa_Output (File);
 *
 * Outputs basic APPA records to the given file.
 *
 *=========================================================================*/
bool TestAppa_Output (CObEspFile& File) {
  CObAppaRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("APPA Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_APPA);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObAppaRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);
    if (g_TestValues[Index].ScriptID  != OB_FORMID_NULL) pRecord->SetScript(g_TestValues[Index].ScriptID);

    pRecord->SetQuality(g_TestValues[Index].Data.Quality);
    pRecord->SetType(g_TestValues[Index].Data.Type);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestAppa_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAppa_Input (File);
 *
 * Checks the values of APPA records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestAppa_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObAppaRecord* pRecord;
  dword		 Index;

  OBTEST_LEVEL("APPA Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_APPA)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_APPA) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObAppaRecord, pBase);
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

    OBTEST_START_TEST("Check quality")
	OBTEST_DOINTCOMPARE(pRecord->GetQuality(), ==, g_TestValues[Index].Data.Quality);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check type")
	OBTEST_DOINTCOMPARE(pRecord->GetType(), ==, g_TestValues[Index].Data.Type);
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
 *		End of Function TestAppa_Input()
 *=========================================================================*/

