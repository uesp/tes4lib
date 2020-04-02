/*===========================================================================
 *
 * File:	Testammo.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testammo.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
testammo_t g_TestData = {
	0x00130000,
	{ 1.2f, 0, 12345, 90.1f, 300 }, 
	"AmmoTestID_123",
	"Ammo Item Name",
	"modelfile.nif",
	"iconfile.dds"
 };

static testammo_t g_TestValues[] = {
	{ 0x00130001, { 1.0f, 0, 2, 3.0f, 4 }, "test_ammo",	"Ammo Item Name",	"model1.nif",	"icon.dds" },
	{ 0x00130002, { 1.0f, OB_AMMOFLAG_IGNORERESIST, 2, 3.0f, 4 }, "test_ammo_ignoreresist",	"Ammo Ignore Resist",	"model2.nif",	"icon.dds" },
	{ 0x00130003, { 1.0f, 0, 2, 3.0f, 4 }, "test_ammo",	"Ammo Item Name",	NULL,	NULL },
	{ 0, { 0, 0, 0, 0, 0 }, NULL, NULL, NULL, NULL }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAmmo_SetGet (void);
 *
 * Tests basic set/get methods of an AMMO record.
 *
 *=========================================================================*/
bool TestAmmo_SetGet (void) {
  CObAmmoRecord Record;

  OBTEST_LEVEL("AMMO Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Item Name")
	Record.SetItemName(g_TestData.pItemName);
	OBTEST_DOSTRCOMPARE(Record.GetItemName(), ==, g_TestData.pItemName)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Speed")
	Record.SetSpeed(g_TestData.Data.Speed);
	OBTEST_DOFLTCOMPARE(Record.GetSpeed(), ==, g_TestData.Data.Speed)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Damage")
	Record.SetDamage(g_TestData.Data.Damage);
	OBTEST_DOINTCOMPARE(Record.GetDamage(), ==, g_TestData.Data.Damage)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Damage (0)")
	Record.SetDamage(0);
	OBTEST_DOINTCOMPARE(Record.GetDamage(), ==, 0)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Damage (255)")
	Record.SetDamage(255);
	OBTEST_DOINTCOMPARE(Record.GetDamage(), ==, 255)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Damage (1000)")
	Record.SetDamage(1000);
	OBTEST_DOINTCOMPARE(Record.GetDamage(), ==, 1000)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Ignore Resist (true)")
	Record.SetIgnoreResist(true);
	OBTEST_DOINTCOMPARE(Record.IsIgnoreResist(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Ignore Resist (false)")
	Record.SetIgnoreResist(false);
	OBTEST_DOINTCOMPARE(Record.IsIgnoreResist(), ==, false)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestAmmo_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAmmo_Output (File);
 *
 * Outputs basic ammo records to the given file.
 *
 *=========================================================================*/
bool TestAmmo_Output (CObEspFile& File) {
  CObAmmoRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("AMMO Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
  
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_AMMO);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObAmmoRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);

    pRecord->SetDamage(g_TestValues[Index].Data.Damage);
    pRecord->SetSpeed(g_TestValues[Index].Data.Speed);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);

    pRecord->SetIgnoreResist ((g_TestValues[Index].Data.Flags & OB_AMMOFLAG_IGNORERESIST)  != 0);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestAmmo_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestAmmo_Input (File);
 *
 * Checks the values of ammo records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestAmmo_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObAmmoRecord* pRecord;
  dword		 Index;
  bool		 Flag;

  OBTEST_LEVEL("AMMO Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_AMMO)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_AMMO) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObAmmoRecord, pBase);
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

    OBTEST_START_TEST("Check ignore resist flag")
        Flag = (g_TestValues[Index].Data.Flags & OB_AMMOFLAG_IGNORERESIST) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsIgnoreResist(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check damage")
	OBTEST_DOINTCOMPARE(pRecord->GetDamage(), ==, g_TestValues[Index].Data.Damage);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check speed")
	OBTEST_DOFLTCOMPARE(pRecord->GetSpeed(), ==, g_TestValues[Index].Data.Speed);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check weight")
	OBTEST_DOFLTCOMPARE(pRecord->GetWeight(), ==, g_TestValues[Index].Data.Weight);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check value")
	OBTEST_DOINTCOMPARE(pRecord->GetValue(), ==, g_TestValues[Index].Data.Value);
    OBTEST_END_TEST()

   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestAmmo_Input()
 *=========================================================================*/

