/*===========================================================================
 *
 * File:	TestLevi.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testlevi.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
testlevi_t g_TestData = {
	0x00190000, 0, 100, "levi_test", NULL, NULL, NULL
 };

static testlevo_t g_TestItems [] = {
	{ 0x901, 24, 11 },
	{ 0x902, 25, 22 },
	{ 0x903, 26, 33 },
	{ 0x904, 27, 44 },
	{ 0x905, 28, 55 },
	{ 0x906, 29, 66 },
 };

static testlevi_t g_TestValues[] = {
	{ 0x00190001, 0, 100, "levi_empty", NULL, NULL, NULL },
	{ 0x00190002, 0, 0, "levi_chance0", NULL, NULL, NULL },
	{ 0x00190003, 0, 56, "levi_chance56", NULL, NULL, NULL },
	{ 0x00190004, OB_LVLIFLAG_CALCULATEALLLEVELS, 90, "levi_calculateall", NULL, NULL, NULL },
	{ 0x00190005, OB_LVLIFLAG_CALCULATEEACHITEM, 90, "levi_calculateeach", NULL, NULL, NULL },
	{ 0x00190006, 0, 56, "levi_item1", &g_TestItems[0], NULL, NULL },
	{ 0x00190007, 0, 56, "levi_item2", &g_TestItems[0], &g_TestItems[1], NULL },
	{ 0x00190008, 0, 56, "levi_item3", &g_TestItems[0], &g_TestItems[1], &g_TestItems[2] },
	{ 0, 0, 0, NULL, NULL, NULL, NULL }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestLevi_SetGet (void);
 *
 * Tests basic set/get methods of a LEVI record.
 *
 *=========================================================================*/
bool TestLevi_SetGet (void) {
  CObLvliRecord Record;

  OBTEST_LEVEL("LEVI Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Speed")
	Record.SetChanceNone(g_TestData.ChanceNone);
	OBTEST_DOFLTCOMPARE(Record.GetChanceNone(), ==, g_TestData.ChanceNone)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set CalculateAllLevels (false)")
	Record.SetCalculateAllLevels(false);
	OBTEST_DOINTCOMPARE(Record.IsCalculateAllLevels(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set CalculateAllLevels (true)")
	Record.SetCalculateAllLevels(true);
	OBTEST_DOINTCOMPARE(Record.IsCalculateAllLevels(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set CalculateEachItem (true)")
	Record.SetCalculateEachItem(true);
	OBTEST_DOINTCOMPARE(Record.IsCalculateEachItem(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set CalculateEachItem (false)")
	Record.SetCalculateEachItem(false);
	OBTEST_DOINTCOMPARE(Record.IsCalculateEachItem(), ==, false)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestLevi_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestLevi_Output (File);
 *
 * Outputs basic LEVI records to the given file.
 *
 *=========================================================================*/
bool TestLevi_Output (CObEspFile& File) {
  CObLvliRecord*    pRecord;
  CObBaseRecord*    pBase;
  CObLvloSubrecord* pItem;
  testlevo_t*	    pLevo;
  dword		    Index;
  dword		    Index1;

  OBTEST_LEVEL("LEVI Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
    
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_LVLI);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObLvliRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    pRecord->SetChanceNone(g_TestValues[Index].ChanceNone);
    pRecord->SetCalculateAllLevels((g_TestValues[Index].Flags & OB_LVLIFLAG_CALCULATEALLLEVELS) != 0);
    pRecord->SetCalculateEachItem((g_TestValues[Index].Flags & OB_LVLIFLAG_CALCULATEEACHITEM) != 0);

    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);

    for (Index1 = 0; g_TestValues[Index].Items[Index1] != NULL; ++Index1) {
      pLevo = g_TestValues[Index].Items[Index1];

      OBTEST_START_TEST("Add item")
	    pItem = pRecord->AddItem(pLevo->FormID, pLevo->Level, pLevo->Count);
	    OBTEST_DOCOMPARE(pItem, !=, NULL)
      OBTEST_END_TEST()
      if (pItem == NULL) continue;

      OBTEST_START_TEST("Check item type")
	    OBTEST_DOCOMPARE(pItem->GetName(), ==, OB_NAME_LVLO)
      OBTEST_END_TEST()
     }
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestLevi_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestLevi_Input (File);
 *
 * Checks the values of LEVI records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestLevi_Input (CObEspFile& File) {
  CObBaseRecord*    pBase;
  CObLvliRecord*    pRecord;
  CObLvloSubrecord* pItem;
  testlevo_t*	    pLevo;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;

  OBTEST_LEVEL("LEVI Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_LVLI)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_LVLI) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObLvliRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check chance none")
	OBTEST_DOINTCOMPARE(pRecord->GetChanceNone(), ==, g_TestValues[Index].ChanceNone);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check calculate all levels")
        Flag = (g_TestValues[Index].Flags & OB_LVLIFLAG_CALCULATEALLLEVELS) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsCalculateAllLevels(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check calculate each item")
        Flag = (g_TestValues[Index].Flags & OB_LVLIFLAG_CALCULATEEACHITEM) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsCalculateEachItem(), ==, Flag);
    OBTEST_END_TEST()

    for (Index1 = 0; g_TestValues[Index].Items[Index1] != NULL; ++Index1) {
      pLevo = g_TestValues[Index].Items[Index1];

      OBTEST_START_TEST("Find item")
	    pItem = pRecord->FindItem(Index1);
	    OBTEST_DOCOMPARE(pItem, !=, NULL)
      OBTEST_END_TEST()
      if (pItem == NULL) continue;

      OBTEST_START_TEST("Check item type")
	    OBTEST_DOCOMPARE(pItem->GetName(), ==, OB_NAME_LVLO)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check item formid")
	    OBTEST_DOINTCOMPARE(pItem->GetFormID(), ==, pLevo->FormID)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check item count")
	    OBTEST_DOINTCOMPARE(pItem->GetCount(), ==, pLevo->Count)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check item level")
	    OBTEST_DOINTCOMPARE(pItem->GetLevel(), ==, pLevo->Level)
      OBTEST_END_TEST()
     }

   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestLevi_Input()
 *=========================================================================*/





