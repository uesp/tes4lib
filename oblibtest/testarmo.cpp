/*===========================================================================
 *
 * File:	Testarmo.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testarmo.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
testarmo_t g_TestData = {
	0x00140000,
	{ 123, 9018, 12002, 108.3f },
	OB_ARMOFLAG_HIDEAMULET,
	120,
	0x00140001,
	"armortestID_123",
	"Armo Item Name",
	"model1file.nif",
	"model2file.nif",
	"model3file.nif",
	"model4file.nif",
	"icon1file.dds",
	"icon2file.dds",
	0x00140002
 };

static testarmo_t g_TestValues[] = {
	{ 0x00140000, { 123, 9018, 12002, 108.3f }, 
		0, 
		120, 0x00140001,	
		"armortest_123", "Armor Item Name", "model1file.nif", "model2file.nif",	"model3file.nif", "model4file.nif", "icon1file.dds", "icon2file.dds", 0x00140002 },
	{ 0x00140001, { 123, 9018, 12002, 108.3f }, 
		0, 
		120, 0x00140001,	
		"armortest_123", "Armor Item Name", "model1file.nif", "model2file.nif",	"model3file.nif", "model4file.nif", "icon1file.dds", "icon2file.dds", 0 },
	{ 0x00140002, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_HEAD, 
		5, 0, "armor_head", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140003, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_HAIR, 
		5, 0, "armor_hair", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140004, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_UPPERBODY, 
		5, 0, "armor_upperbody", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140005, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_LOWERBODY, 
		5, 0, "armor_lowerbody", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140006, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_HAND, 
		5, 0, "armor_hand", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140007, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_FOOT, 
		5, 0, "armor_foot", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140008, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_RIGHTRING, 
		5, 0, "armor_rightring", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140009, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_LEFTRING, 
		5, 0, "armor_leftring", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000A, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_AMULET, 
		5, 0, "armor_amulet", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000B, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_WEAPON, 
		5, 0, "armor_weapon", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000C, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_BACKWEAPON, 
		5, 0, "armor_backweapon", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000D, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_SIDEWEAPON, 
		5, 0, "armor_sideweapon", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000E, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_QUIVER, 
		5, 0, "armor_quiver", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x0014000F, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_SHIELD, 
		5, 0, "armor_shield", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140010, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_TORCH, 
		5, 0, "armor_torch", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140011, { 1, 2, 3, 4 }, 
		OB_BIPEDFLAG_TAIL, 
		5, 0, "armor_tail", "Armor Test", "model1.nif", NULL,	NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140012, { 1, 2, 3, 4 }, 
		OB_ARMOFLAG_HIDEAMULET, 
		5, 0, "armor_hideamulet", "Armor Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140013, { 1, 2, 3, 4 }, 
		OB_ARMOFLAG_HIDERINGS, 
		5, 0, "armor_hiderings", "Armor Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140014, { 1, 2, 3, 4 }, 
		OB_ARMOFLAG_NONPLAYABLE,
		5, 0, "armor_nonplayable", "Armor Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0x00140015, { 1, 2, 3, 4 }, 
		OB_ARMOFLAG_HEAVYARMOR, 
		5, 0, "armor_heavyarmor", "Armor Test", "model1.nif", NULL, NULL, NULL, "icon1.dds", NULL, 0 },
	{ 0, { 0, 0, 0, 0 }, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0 }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestArmo_SetGet (void);
 *
 * Tests basic set/get methods of an ARMO record.
 *
 *=========================================================================*/
bool TestArmo_SetGet (void) {
  CObArmoRecord Record;

  OBTEST_LEVEL("ARMO Set/Get")
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

  OBTEST_START_TEST("Armor")
	Record.SetArmor(g_TestData.Data.Armor);
	OBTEST_DOFLTCOMPARE(Record.GetArmor(), ==, g_TestData.Data.Armor)
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

  OBTEST_START_TEST("Set Heavy Armor (true)")
	Record.SetHeavyArmor(true);
	OBTEST_DOINTCOMPARE(Record.IsHeavyArmor(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Heavy Armor (false)")
	Record.SetHeavyArmor(false);
	OBTEST_DOINTCOMPARE(Record.IsHeavyArmor(), ==, false)
  OBTEST_END_TEST()  

  OBTEST_START_TEST("Set Light Armor (true)")
	Record.SetLightArmor(true);
	OBTEST_DOINTCOMPARE(Record.IsLightArmor(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Light Armor (false)")
	Record.SetLightArmor(false);
	OBTEST_DOINTCOMPARE(Record.IsLightArmor(), ==, false)
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
 *		End of Function TestArmo_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestArmo_Output (File);
 *
 * Outputs basic ARMO records to the given file.
 *
 *=========================================================================*/
bool TestArmo_Output (CObEspFile& File) {
  CObArmoRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("ARMO Output")

  for (Index = 0; g_TestValues[Index].pItemName != NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_ARMO);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObArmoRecord, pBase);
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
    pRecord->SetHealth(g_TestValues[Index].Data.Health);
    pRecord->SetArmor(g_TestValues[Index].Data.Armor);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);

    pRecord->SetHeavyArmor((g_TestValues[Index].Flags & OB_ARMOFLAG_HEAVYARMOR)  != 0);
    pRecord->SetHideRings((g_TestValues[Index].Flags & OB_ARMOFLAG_HIDERINGS)  != 0);
    pRecord->SetHideAmulet((g_TestValues[Index].Flags & OB_ARMOFLAG_HIDEAMULET)  != 0);
    pRecord->SetPlayable((g_TestValues[Index].Flags & OB_ARMOFLAG_NONPLAYABLE)  == 0);

    pRecord->ClearBipedFlags();
    pRecord->SetBipedFlags(g_TestValues[Index].Flags & OB_BIPEDFLAG_MASK);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestArmo_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestArmo_Input (File);
 *
 * Checks the values of ARMO records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestArmo_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObArmoRecord* pRecord;
  dword		 Index;

  OBTEST_LEVEL("ARMO Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_ARMO)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_ARMO) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObArmoRecord, pBase);
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

    OBTEST_START_TEST("Check health")
	OBTEST_DOINTCOMPARE(pRecord->GetHealth(), ==, g_TestValues[Index].Data.Health);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Armor")
	OBTEST_DOINTCOMPARE(pRecord->GetArmor(), ==, g_TestValues[Index].Data.Armor);
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
	OBTEST_DOINTCOMPARE(pRecord->IsHideAmulet(), ==, ((g_TestValues[Index].Flags & OB_ARMOFLAG_HIDEAMULET) != 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check hide rings")
	OBTEST_DOINTCOMPARE(pRecord->IsHideRings(), ==, ((g_TestValues[Index].Flags & OB_ARMOFLAG_HIDERINGS) != 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check heavy armor")
	OBTEST_DOINTCOMPARE(pRecord->IsHeavyArmor(), ==, ((g_TestValues[Index].Flags & OB_ARMOFLAG_HEAVYARMOR) != 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check light armor")
	OBTEST_DOINTCOMPARE(pRecord->IsLightArmor(), ==, ((g_TestValues[Index].Flags & OB_ARMOFLAG_HEAVYARMOR) == 0));
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check playable")
	OBTEST_DOINTCOMPARE(pRecord->IsPlayable(), ==, ((g_TestValues[Index].Flags & OB_ARMOFLAG_NONPLAYABLE) == 0));
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
 *		End of Function TestArmo_Input()
 *=========================================================================*/



