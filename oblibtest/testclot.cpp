/*===========================================================================
 *
 * File:	TestClot.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testclot.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
testclot_t g_TestData = {
	0x00170000,
	{ 1, 2.3f },
	OB_CLOTFLAG_HIDEAMULET,
	120,
	0x00170001,
	"cloth_test",
	"Clothing Name",
	"model1.nif",
	"model2.nif",
	"model3.nif",
	"model4.nif",
	"icon1.dds",
	"icon2.dds",
	0x00170002
 };

static testclot_t g_TestValues[] = {
	{ 0x00170000, { 1, 2.3f }, 
		0, 120, 0x00123,
		"cloth_test", "Clothing Name", "model1.nif", "model2.nif", "model3.nif", "model4.nif", "icon1.dds", "icon2.dds", 0x00040002 },
	{ 0x00170002, { 1, 2 }, 
		OB_BIPEDFLAG_HEAD, 
		5, 0, "cloth_head", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170003, { 1, 2 }, 
		OB_BIPEDFLAG_HAIR, 
		5, 0, "cloth_hair", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170004, { 1, 2 }, 
		OB_BIPEDFLAG_UPPERBODY, 
		5, 0, "cloth_upperbody", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170005, { 1, 2 }, 
		OB_BIPEDFLAG_LOWERBODY, 
		5, 0, "cloth_lowerbody", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170006, { 1, 2 }, 
		OB_BIPEDFLAG_HAND, 
		5, 0, "cloth_hand", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170007, { 1, 2 }, 
		OB_BIPEDFLAG_FOOT, 
		5, 0, "cloth_foot", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170008, { 1, 2 }, 
		OB_BIPEDFLAG_RIGHTRING, 
		5, 0, "cloth_rightring", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170009, { 1, 2 }, 
		OB_BIPEDFLAG_LEFTRING, 
		5, 0, "cloth_leftring", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000A, { 1, 2 }, 
		OB_BIPEDFLAG_AMULET, 
		5, 0, "cloth_amulet", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000B, { 1, 2 }, 
		OB_BIPEDFLAG_WEAPON, 
		5, 0, "cloth_weapon", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000C, { 1, 2 }, 
		OB_BIPEDFLAG_BACKWEAPON, 
		5, 0, "cloth_backweapon", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000D, { 1, 2 }, 
		OB_BIPEDFLAG_SIDEWEAPON, 
		5, 0, "cloth_sideweapon", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000E, { 1, 2 }, 
		OB_BIPEDFLAG_QUIVER, 
		5, 0, "cloth_quiver", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0017000F, { 1, 2 }, 
		OB_BIPEDFLAG_SHIELD, 
		5, 0, "cloth_shield", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170010, { 1, 2 }, 
		OB_BIPEDFLAG_TORCH, 
		5, 0, "cloth_torch", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170011, { 1, 2 }, 
		OB_BIPEDFLAG_TAIL, 
		5, 0, "cloth_tail", "Clothing Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170012, { 1, 2 }, 
		OB_CLOTFLAG_HIDEAMULET, 
		5, 0, "cloth_hideamulet", "Clothing Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170013, { 1, 2 }, 
		OB_CLOTFLAG_HIDERINGS, 
		5, 0, "cloth_hiderings", "Clothing Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170014, { 1, 2 }, 
		OB_CLOTFLAG_NONPLAYABLE,
		5, 0, "cloth_nonplayable", "Clothing Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00170014, { 0, 0 }, 
		0,
		5, 0, "cloth_null", NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 },
	
	{ 0, { 0, 0 }, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestClot_SetGet (void);
 *
 * Tests basic set/get methods of an CLOT record.
 *
 *=========================================================================*/
bool TestClot_SetGet (void) {
  CObClotRecord Record;

  OBTEST_LEVEL("CLOT Set/Get")
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

  OBTEST_START_TEST("Model1")
	Record.SetModel(g_TestData.pModel1);
	OBTEST_DOSTRCOMPARE(Record.GetModel(), ==, g_TestData.pModel1)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Model2")
	Record.SetModel2(g_TestData.pModel2);
	OBTEST_DOSTRCOMPARE(Record.GetModel2(), ==, g_TestData.pModel2)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Model3")
	Record.SetModel3(g_TestData.pModel3);
	OBTEST_DOSTRCOMPARE(Record.GetModel3(), ==, g_TestData.pModel3)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Model4")
	Record.SetModel4(g_TestData.pModel4);
	OBTEST_DOSTRCOMPARE(Record.GetModel4(), ==, g_TestData.pModel4)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Icon1")
	Record.SetIcon(g_TestData.pIcon1);
	OBTEST_DOSTRCOMPARE(Record.GetIcon(), ==, g_TestData.pIcon1)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Icon2")
	Record.SetIcon2(g_TestData.pIcon2);
	OBTEST_DOSTRCOMPARE(Record.GetIcon2(), ==, g_TestData.pIcon2)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Hide Amulet (true)")
	Record.SetHideAmulet(true);
	OBTEST_DOINTCOMPARE(Record.IsHideAmulet(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Hide Amulet (false)")
	Record.SetHideAmulet(false);
	OBTEST_DOINTCOMPARE(Record.IsHideAmulet(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Hide Rings (true)")
	Record.SetHideRings(true);
	OBTEST_DOINTCOMPARE(Record.IsHideRings(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Hide Rings (false)")
	Record.SetHideRings(false);
	OBTEST_DOINTCOMPARE(Record.IsHideRings(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Playable (true)")
	Record.SetPlayable(true);
	OBTEST_DOINTCOMPARE(Record.IsPlayable(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Playable (false)")
	Record.SetPlayable(false);
	OBTEST_DOINTCOMPARE(Record.IsPlayable(), ==, false)
  OBTEST_END_TEST()
  
  OBTEST_START_TEST("Set Biped Flags")
	Record.SetBipedFlags(OB_BIPEDFLAG_HEAD);
	OBTEST_DOINTCOMPARE(Record.GetBipedFlags(), ==, OB_BIPEDFLAG_HEAD)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Clear Biped Flags")
	Record.ClearBipedFlags();
	OBTEST_DOINTCOMPARE(Record.GetBipedFlags(), ==, 0)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Biped Flags (all)")
	Record.SetBipedFlags(OB_BIPEDFLAG_MASK);
	OBTEST_DOINTCOMPARE(Record.GetBipedFlags(), ==, OB_BIPEDFLAG_MASK)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check Script (0)")
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, OB_FORMID_NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Script")
	Record.SetScript(0x1234);
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, 0x1234)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check Enchantment")
	OBTEST_DOINTCOMPARE(Record.GetEnchantment(), ==, OB_FORMID_NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Enchantment")
	Record.SetEnchantment(0x55668);
	OBTEST_DOINTCOMPARE(Record.GetEnchantment(), ==, 0x55668)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Enchantment Points")
	Record.SetEnchantPoints(101);
	OBTEST_DOINTCOMPARE(Record.GetEnchantPoints(), ==, 101)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestClot_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestClot_Output (File);
 *
 * Outputs basic CLOT records to the given file.
 *
 *=========================================================================*/
bool TestClot_Output (CObEspFile& File) {
  CObClotRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("CLOT Output")

  for (Index = 0; g_TestValues[Index].pItemName != NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_CLOT);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObClotRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel1   != NULL) pRecord->SetModel(g_TestValues[Index].pModel1);
    if (g_TestValues[Index].pModel2   != NULL) pRecord->SetModel2(g_TestValues[Index].pModel2);
    if (g_TestValues[Index].pModel3   != NULL) pRecord->SetModel3(g_TestValues[Index].pModel3);
    if (g_TestValues[Index].pModel4   != NULL) pRecord->SetModel4(g_TestValues[Index].pModel4);
    if (g_TestValues[Index].pIcon1    != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon1);
    if (g_TestValues[Index].pIcon2    != NULL) pRecord->SetIcon2(g_TestValues[Index].pIcon2);
    if (g_TestValues[Index].ScriptFormID  != 0) pRecord->SetScript(g_TestValues[Index].ScriptFormID);
    if (g_TestValues[Index].EnchantFormID != 0) pRecord->SetEnchantment(g_TestValues[Index].EnchantFormID);
    if (g_TestValues[Index].EnchantPts    != 0) pRecord->SetEnchantPoints(g_TestValues[Index].EnchantPts);

    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);

    pRecord->SetHideRings((g_TestValues[Index].Flags & OB_CLOTFLAG_HIDERINGS)  != 0);
    pRecord->SetHideAmulet((g_TestValues[Index].Flags & OB_CLOTFLAG_HIDEAMULET)  != 0);
    pRecord->SetPlayable((g_TestValues[Index].Flags & OB_CLOTFLAG_NONPLAYABLE)  == 0);

    pRecord->ClearBipedFlags();
    pRecord->SetBipedFlags(g_TestValues[Index].Flags & OB_BIPEDFLAG_MASK);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestClot_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestClot_Input (File);
 *
 * Checks the values of CLOT records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestClot_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObClotRecord* pRecord;
  dword		 Index;

  OBTEST_LEVEL("CLOT Input")

  for (Index = 0; g_TestValues[Index].pItemName != NULL; ++Index) {
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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_CLOT)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_CLOT) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObClotRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check item name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetItemName(), ==, g_TestValues[Index].pItemName);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check model1")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel(), ==, g_TestValues[Index].pModel1);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check model2")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel2(), ==, g_TestValues[Index].pModel2);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check model3")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel3(), ==, g_TestValues[Index].pModel3);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check model4")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel4(), ==, g_TestValues[Index].pModel4);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check icon1")
	OBTEST_DOSTRCOMPARE1(pRecord->GetIcon(), ==, g_TestValues[Index].pIcon1);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check icon2")
	OBTEST_DOSTRCOMPARE1(pRecord->GetIcon2(), ==, g_TestValues[Index].pIcon2);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check weight")
	OBTEST_DOINTCOMPARE(pRecord->GetWeight(), ==, g_TestValues[Index].Data.Weight);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check value")
	OBTEST_DOINTCOMPARE(pRecord->GetValue(), ==, g_TestValues[Index].Data.Value);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Biped Flags")
	OBTEST_DOINTCOMPARE(pRecord->GetBipedFlags(), ==, (g_TestValues[Index].Flags & OB_BIPEDFLAG_MASK));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check hide amulet")
	OBTEST_DOINTCOMPARE(pRecord->IsHideAmulet(), ==, ((g_TestValues[Index].Flags & OB_CLOTFLAG_HIDEAMULET) != 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check hide rings")
	OBTEST_DOINTCOMPARE(pRecord->IsHideRings(), ==, ((g_TestValues[Index].Flags & OB_CLOTFLAG_HIDERINGS) != 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check playable")
	OBTEST_DOINTCOMPARE(pRecord->IsPlayable(), ==, ((g_TestValues[Index].Flags & OB_CLOTFLAG_NONPLAYABLE) == 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script formID")
	OBTEST_DOINTCOMPARE(pRecord->GetScript(), ==, g_TestValues[Index].ScriptFormID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchantment formID")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantment(), ==, g_TestValues[Index].EnchantFormID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchant points")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantPoints(), ==, g_TestValues[Index].EnchantPts);
    OBTEST_END_TEST()
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestClot_Input()
 *=========================================================================*/



