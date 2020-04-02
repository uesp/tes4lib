/*===========================================================================
 *
 * File:	TestWeap.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testweap.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
	dword   Type;
	float	Speed;
	float	Reach;
	dword	Flags;
	dword	Value;
	dword   Health;
	float	Weight;
	word    Damage;
 *=========================================================================*/
testweap_t g_TestData = {
	0x00250000,
	{ 0, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, 
	"weap_test",
	"Weapon Name",
	"model.nif",
	"icon.dds",
	0x981,
	0x178,
	102
 };

static testweap_t g_TestValues[] = {
	{ 0x00250001, { 0, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_test", "Weapon Name", "model.nif", "icon.dds", 0x981, 0x178,	102 },
	{ 0x00250002, { 0, 1.0f, 2.0f, OB_WEAPFLAG_IGNORERESIST, 4, 5, 6.0f, 7 }, "weap_ignoreresist", "Weapon Name", NULL, NULL, 0, 0,	9 },
	{ 0x00250003, { OB_WEAPTYPE_BLADEONEHAND, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0x00250004, { OB_WEAPTYPE_BLADETWOHAND, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0x00250005, { OB_WEAPTYPE_BLUNTONEHAND, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0x00250006, { OB_WEAPTYPE_BLUNTTWOHAND, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0x00250007, { OB_WEAPTYPE_STAFF, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0x00250008, { OB_WEAPTYPE_BOW, 1.0f, 2.0f, 0, 4, 5, 6.0f, 7 }, "weap_1blade", "Weapon Name", NULL, NULL, 0, 0, 0 },
	{ 0, { 0, 0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, NULL, 0, 0, 0 }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestWeap_SetGet (void);
 *
 * Tests basic set/get methods of an WEAP record.
 *
 *=========================================================================*/
bool TestWeap_SetGet (void) {
  CObWeapRecord Record;

  OBTEST_LEVEL("WEAP Set/Get")
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

  OBTEST_START_TEST("Script")
	Record.SetScript(g_TestData.ScriptID);
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, g_TestData.ScriptID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchantment")
	Record.SetEnchantment(g_TestData.EnchantID);
	OBTEST_DOINTCOMPARE(Record.GetEnchantment(), ==, g_TestData.EnchantID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchantment points")
	Record.SetEnchantPoints(g_TestData.EnchantPts);
	OBTEST_DOINTCOMPARE(Record.GetEnchantPoints(), ==, g_TestData.EnchantPts)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Speed")
	Record.SetSpeed(g_TestData.Data.Speed);
	OBTEST_DOFLTCOMPARE(Record.GetSpeed(), ==, g_TestData.Data.Speed)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Reach")
	Record.SetReach(g_TestData.Data.Reach);
	OBTEST_DOFLTCOMPARE(Record.GetReach(), ==, g_TestData.Data.Reach)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Type")
	Record.SetType(g_TestData.Data.Type);
	OBTEST_DOFLTCOMPARE(Record.GetType(), ==, g_TestData.Data.Type)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Health")
	Record.SetHealth(g_TestData.Data.Health);
	OBTEST_DOFLTCOMPARE(Record.GetHealth(), ==, g_TestData.Data.Health)
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
 *		End of Function TestWeap_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestWeap_Output (File);
 *
 * Outputs basic WEAP records to the given file.
 *
 *=========================================================================*/
bool TestWeap_Output (CObEspFile& File) {
  CObWeapRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("WEAP Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
  
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_WEAP);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObWeapRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);
    if (g_TestValues[Index].ScriptID  !=    0) pRecord->SetScript(g_TestValues[Index].ScriptID);
    if (g_TestValues[Index].EnchantID !=    0) pRecord->SetEnchantment(g_TestValues[Index].EnchantID);
    if (g_TestValues[Index].EnchantPts !=   0) pRecord->SetEnchantPoints(g_TestValues[Index].EnchantPts);

    pRecord->SetDamage(g_TestValues[Index].Data.Damage);
    pRecord->SetType(g_TestValues[Index].Data.Type);
    pRecord->SetSpeed(g_TestValues[Index].Data.Speed);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetReach(g_TestValues[Index].Data.Reach);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);
    pRecord->SetHealth(g_TestValues[Index].Data.Health);

    pRecord->SetIgnoreResist ((g_TestValues[Index].Data.Flags & OB_AMMOFLAG_IGNORERESIST)  != 0);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestWeap_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestWeap_Input (File);
 *
 * Checks the values of ammo records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestWeap_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObWeapRecord* pRecord;
  dword		 Index;
  bool		 Flag;

  OBTEST_LEVEL("WEAP Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_WEAP)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_WEAP) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObWeapRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check item name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetItemName(), ==, g_TestValues[Index].pItemName);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script ID")
	OBTEST_DOINTCOMPARE(pRecord->GetScript(), ==, g_TestValues[Index].ScriptID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchantment ID")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantment(), ==, g_TestValues[Index].EnchantID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchantment points")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantPoints(), ==, g_TestValues[Index].EnchantPts);
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

    OBTEST_START_TEST("Check type")
	OBTEST_DOINTCOMPARE(pRecord->GetType(), ==, g_TestValues[Index].Data.Type);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check speed")
	OBTEST_DOFLTCOMPARE(pRecord->GetSpeed(), ==, g_TestValues[Index].Data.Speed);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check weight")
	OBTEST_DOFLTCOMPARE(pRecord->GetWeight(), ==, g_TestValues[Index].Data.Weight);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check reach")
	OBTEST_DOFLTCOMPARE(pRecord->GetReach(), ==, g_TestValues[Index].Data.Reach);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check value")
	OBTEST_DOINTCOMPARE(pRecord->GetValue(), ==, g_TestValues[Index].Data.Value);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check health")
	OBTEST_DOINTCOMPARE(pRecord->GetHealth(), ==, g_TestValues[Index].Data.Health);
    OBTEST_END_TEST()

   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestWeap_Input()
 *=========================================================================*/



