/*===========================================================================
 *
 * File:	Testbook.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testbook.h"

/*===========================================================================
 *
 * Begin Local Definitions
 *
 *	obformid_t	FormID;
	obbookdata_t	Data;
	obformid_t	EnchantID;
	word		EnchantPts;
	obformid_t	ScriptID;
	const SSCHAR*	pEditorID;
	const SSCHAR*	pItemName;
	const SSCHAR*	pModel;
	const SSCHAR*	pIcon;
	const SSCHAR*	pText;
 *=========================================================================*/
testbook_t g_TestData = {
	0x00150000,
	{ 0, -1, 1, 2.0f }, 
	0x1234, 3, 0x567,
	"book_test",
	"Book Name",
	"modelfile.nif",
	"iconfile.dds",
	"book text...."
 };

testbook_t g_TestValues[] = {
	{ 0x00150001, { 0, -1, 1, 2.0f }, 0x1234, 3, 0x567,
		"book_test", "Book Name", "modelfile.nif", "iconfile.dds", "book text...." },
	{ 0x00150002, { OB_BOOKFLAG_NOTAKE, -1, 1, 2.0f }, 0x1234, 3, 0,
		"book_notake", "Book Name", "modelfile.nif", "iconfile.dds", "book text...." },
	{ 0x00150003, { OB_BOOKFLAG_SCROLL, -1, 1, 2.0f }, 0, 3, 0x567,
		"book_scroll", "Book Name", "modelfile.nif", "iconfile.dds", "book text Enter-\n-    Enter+CR-\n\r-   Tab-\t-   CR+Enter-\r\n-..." },
	{ 0x00150004, { 0, -1, 1, 2.0f }, 0, 3, 0,
		"book_null", "Book Name", NULL, NULL, NULL },
	{ 0, { 0, 0, 0, 0 }, 0, 0, 0, NULL, NULL, NULL, NULL, NULL },
  };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestBook_SetGet (void);
 *
 * Tests basic set/get methods of a BOOK record.
 *
 *=========================================================================*/
bool TestBook_SetGet (void) {
  CObBookRecord Record;

  OBTEST_LEVEL("BOOK Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchantment ID")
	Record.SetEnchantment(g_TestData.EnchantID);
	OBTEST_DOINTCOMPARE(Record.GetEnchantment(), ==, g_TestData.EnchantID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchantment Points")
	Record.SetEnchantPoints(g_TestData.EnchantPts);
	OBTEST_DOINTCOMPARE(Record.GetEnchantPoints(), ==, g_TestData.EnchantPts)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Script ID")
	Record.SetScript(g_TestData.ScriptID);
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, g_TestData.ScriptID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Item Name")
	Record.SetItemName(g_TestData.pItemName);
	OBTEST_DOSTRCOMPARE(Record.GetItemName(), ==, g_TestData.pItemName)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Teaches")
	Record.SetTeaches(g_TestData.Data.Teaches);
	OBTEST_DOINTCOMPARE(Record.GetTeaches(), ==, g_TestData.Data.Teaches)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Scroll (true)")
	Record.SetIsScroll(true);
	OBTEST_DOINTCOMPARE(Record.IsScroll(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set Scroll (false)")
	Record.SetIsScroll(false);
	OBTEST_DOINTCOMPARE(Record.IsScroll(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set NoTake (true)")
	Record.SetNoTake(true);
	OBTEST_DOINTCOMPARE(Record.IsNoTake(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set NoTake (false)")
	Record.SetNoTake(false);
	OBTEST_DOINTCOMPARE(Record.IsNoTake(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Book text")
	Record.SetBookText(g_TestData.pText);
	OBTEST_DOSTRCOMPARE(Record.GetBookText(), ==, g_TestData.pText)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestBook_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestBook_Output (File);
 *
 * Outputs basic book records to the given file.
 *
 *=========================================================================*/
bool TestBook_Output (CObEspFile& File) {
  CObBookRecord* pRecord;
  CObBaseRecord* pBase;
  dword		 Index;

  OBTEST_LEVEL("BOOK Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {

    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_BOOK);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObBookRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);

    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);
    if (g_TestValues[Index].pText     != NULL) pRecord->SetBookText(g_TestValues[Index].pText);
    if (g_TestValues[Index].ScriptID  != OB_FORMID_NULL) pRecord->SetScript(g_TestValues[Index].ScriptID);
    if (g_TestValues[Index].EnchantID != OB_FORMID_NULL) pRecord->SetEnchantment(g_TestValues[Index].EnchantID);

    pRecord->SetEnchantPoints(g_TestValues[Index].EnchantPts);
    pRecord->SetTeaches(g_TestValues[Index].Data.Teaches);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);

    pRecord->SetNoTake ((g_TestValues[Index].Data.Flags & OB_BOOKFLAG_NOTAKE)  != 0);
    pRecord->SetIsScroll ((g_TestValues[Index].Data.Flags & OB_BOOKFLAG_SCROLL)  != 0);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestBook_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestBook_Input (File);
 *
 * Checks the values of book records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestBook_Input (CObEspFile& File) {
  CObBaseRecord* pBase;
  CObBookRecord* pRecord;
  dword		 Index;
  bool		 Flag;

  OBTEST_LEVEL("BOOK Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_BOOK)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_BOOK) continue;
    
    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObBookRecord, pBase);
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

    OBTEST_START_TEST("Check book text")
	OBTEST_DOSTRCOMPARE1(pRecord->GetBookText(), ==, g_TestValues[Index].pText);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script")
	OBTEST_DOINTCOMPARE(pRecord->GetScript(), ==, g_TestValues[Index].ScriptID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchantment")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantment(), ==, g_TestValues[Index].EnchantID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check enchant points")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantPoints(), ==, g_TestValues[Index].EnchantPts);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check scroll flag")
        Flag = (g_TestValues[Index].Data.Flags & OB_BOOKFLAG_SCROLL) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsScroll(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check notake flag")
        Flag = (g_TestValues[Index].Data.Flags & OB_BOOKFLAG_NOTAKE) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsNoTake(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check teaches")
	OBTEST_DOINTCOMPARE(pRecord->GetTeaches(), ==, g_TestValues[Index].Data.Teaches);
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
 *		End of Function TestBook_Input()
 *=========================================================================*/

