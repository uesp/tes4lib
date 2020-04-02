/*===========================================================================
 *
 * File:	Testrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testrecord.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
static testrecord_t g_TestValues[] = {
	{ "No Flags",	"testnoflags",		0,			0x00120001 },
	{ "Dangerous",	"testdangerousflags",	OB_RECFLAG1_DANGEROUS,	0x00120002 },
	{ "Quest",	"testquestflags",	OB_RECFLAG1_QUESTITEM,	0x00120003 },
	{ "Compressed",	"testcompressedflags",	OB_RECFLAG1_COMPRESSED,	0x00120004 },
	{ "Deleted",	"testdeletedflags",	OB_RECFLAG1_DELETED,	0x00120005 },
	{ "Master",	"testmasterflags",	OB_RECFLAG1_MASTER,	0x00120006 },
	{ "All Flags",	"testallflags",		OB_RECFLAG1_MASTER | OB_RECFLAG1_DELETED | OB_RECFLAG1_COMPRESSED | OB_RECFLAG1_QUESTITEM | OB_RECFLAG1_DANGEROUS,	0x00120007 },
	{ NULL, 0, 0, 0 }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestRecord_Cast (void);
 *
 * Checks bnasic casting of record classes.
 *
 *=========================================================================*/
bool TestRecord_Cast (void) {
  CObBaseRecord*  pBaseRecord1;
  CObRecord*      pRecord1;
  CObIdRecord*    pIDRecord1;
  CObItem1Record* pItem1Record1;
  CObItem2Record* pItem2Record1;
  CObArmoRecord*  pArmorRecord1;
  CObMiscRecord*  pMiscRecord1;
  CObRecord	  Record;
  CObIdRecord	  IDRecord;
  CObItem1Record  Item1Record;
  CObItem2Record  Item2Record;
  CObArmoRecord	  ArmorRecord;
  CObMiscRecord	  MiscRecord;

  OBTEST_LEVEL("Record Cast")

  OBTEST_START_TEST("CObRecord -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &Record);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObRecord -> CObBaseRecord")
	pBaseRecord1 = ObCastClass(CObBaseRecord, &Record);
	OBTEST_DOCOMPARE(pBaseRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObIdRecord -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &IDRecord);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObIdRecord -> CObBaseRecord")
	pBaseRecord1 = ObCastClass(CObBaseRecord, &IDRecord);
	OBTEST_DOCOMPARE(pBaseRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObRecord -> CObIdRecord")
	pIDRecord1 = ObCastClass(CObIdRecord, &Record);
	OBTEST_DOCOMPARE(pIDRecord1, ==, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObItem1Record -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &Item1Record);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObItem2Record -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &Item2Record);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &ArmorRecord);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObIdRecord")
	pIDRecord1 = ObCastClass(CObIdRecord, &ArmorRecord);
	OBTEST_DOCOMPARE(pIDRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObItem1Record")
	pItem1Record1 = ObCastClass(CObItem1Record, &ArmorRecord);
	OBTEST_DOCOMPARE(pItem1Record1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObItem2Record")
	pItem2Record1 = ObCastClass(CObItem2Record, &ArmorRecord);
	OBTEST_DOCOMPARE(pItem2Record1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObArmoRecord")
	pArmorRecord1 = ObCastClass(CObArmoRecord, &ArmorRecord);
	OBTEST_DOCOMPARE(pArmorRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObMiscRecord -> CObRecord")
	pRecord1 = ObCastClass(CObRecord, &MiscRecord);
	OBTEST_DOCOMPARE(pRecord1, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObRecord -> CObMiscRecord")
	pMiscRecord1 = ObCastClass(CObMiscRecord, &Record);
	OBTEST_DOCOMPARE(pMiscRecord1, ==, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObArmoRecord -> CObMiscRecord")
	pMiscRecord1 = ObCastClass(CObMiscRecord, &ArmorRecord);
	OBTEST_DOCOMPARE(pMiscRecord1, ==, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("CObMiscRecord -> CObArmoRecord")
	pArmorRecord1 = ObCastClass(CObArmoRecord, &MiscRecord);
	OBTEST_DOCOMPARE(pArmorRecord1, ==, NULL)
  OBTEST_END_TEST()

  
  return (true);
 }
/*===========================================================================
 *		End of Function TestRecord_Cast()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestRecord_SetGet (void);
 *
 * Tests the basic set/get methods of a record.
 *
 *=========================================================================*/
bool TestRecord_SetGet (void) {
  CObRecord Record;

  OBTEST_LEVEL("Record Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Compressed Set")
	Record.SetCompressed(true);
	OBTEST_DOCOMPARE(Record.IsCompressed(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Compressed Clear")
	Record.SetCompressed(false);
	OBTEST_DOCOMPARE(Record.IsCompressed(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Dangerous Set")
	Record.SetDangerous(true);
	OBTEST_DOCOMPARE(Record.IsDangerous(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Dangerous Clear")
	Record.SetDangerous(false);
	OBTEST_DOCOMPARE(Record.IsDangerous(), ==, false)
  OBTEST_END_TEST()

 OBTEST_START_TEST("Deleted Set")
	Record.SetDeleted(true);
	OBTEST_DOCOMPARE(Record.IsDeleted(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Deleted Clear")
	Record.SetDeleted(false);
	OBTEST_DOCOMPARE(Record.IsDeleted(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Quest Item Set")
	Record.SetQuestItem(true);
	OBTEST_DOCOMPARE(Record.IsQuestItem(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Quest Item Clear")
	Record.SetQuestItem(false);
	OBTEST_DOCOMPARE(Record.IsQuestItem(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Master Set")
	Record.SetMaster(true);
	OBTEST_DOCOMPARE(Record.IsMaster(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Master Clear")
	Record.SetMaster(false);
	OBTEST_DOCOMPARE(Record.IsMaster(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("IsRecord Check")
	OBTEST_DOCOMPARE(Record.IsRecord(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("FormID")
	Record.SetFormID(0x12345678);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, 0x12345678)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Name Check")
	OBTEST_DOCOMPARE(Record.GetName(), ==, OB_NAME_NULL)
  OBTEST_END_TEST()



  return (true);
 }
/*===========================================================================
 *		End of Function TestRecord_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestRecord_Output (File);
 *
 * Outputs basic record types to the given file.
 *
 *=========================================================================*/
bool TestRecord_Output (CObEspFile& File) {
  CObMiscRecord* pRecord;
  dword		 Index;

  for (Index = 0; g_TestValues[Index].pItemName != NULL; ++Index) {
    pRecord = (CObMiscRecord *) File.AddNewRecord(OB_NAME_MISC);
    if (pRecord == NULL) return (false);
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    pRecord->SetItemName(g_TestValues[Index].pItemName);
    pRecord->SetEditorID(g_TestValues[Index].pEditorID);

    pRecord->SetDangerous ((g_TestValues[Index].Flags & OB_RECFLAG1_DANGEROUS)  != 0);
    pRecord->SetQuestItem ((g_TestValues[Index].Flags & OB_RECFLAG1_QUESTITEM)  != 0);
    pRecord->SetMaster    ((g_TestValues[Index].Flags & OB_RECFLAG1_MASTER)     != 0);
    pRecord->SetDeleted   ((g_TestValues[Index].Flags & OB_RECFLAG1_DELETED)    != 0);
    pRecord->SetCompressed((g_TestValues[Index].Flags & OB_RECFLAG1_COMPRESSED) != 0);
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestRecord_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestRecord_Input (File);
 *
 * Checks the values of records in the given file and ensures they match
 * those previously output.
 *
 *=========================================================================*/
bool TestRecord_Input (CObEspFile& File) {
  CObBaseRecord* pRecord;
  CObMiscRecord* pMiscRecord;
  dword		 Index;
  bool		 Flag;

  OBTEST_LEVEL("Record Output/Input")

  for (Index = 0; g_TestValues[Index].pItemName != NULL; ++Index) {
    OnTestOutputNote("Testing Record (%d, '%s')", g_TestValues[Index].FormID, g_TestValues[Index].pEditorID);

    OBTEST_START_TEST("Find record by formID")
        pRecord = File.FindFormID(g_TestValues[Index].FormID);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
    
    OBTEST_START_TEST("Check record type")
	OBTEST_DOCOMPARE(pRecord->IsRecord(), ==, true)
    OBTEST_END_TEST()
    if (!pRecord->IsRecord()) continue;

    OBTEST_START_TEST("Check record name")
	OBTEST_DOCOMPARE(pRecord->GetName(), ==, OB_NAME_MISC)
    OBTEST_END_TEST()
    if (pRecord->GetName() != OB_NAME_MISC) continue;
    pMiscRecord = (CObMiscRecord *) pRecord;

    OBTEST_START_TEST("Check item name")
	OBTEST_DOSTRCOMPARE(pMiscRecord->GetItemName(), ==, g_TestValues[Index].pItemName);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE(pMiscRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check dangerous flag")
        Flag = (g_TestValues[Index].Flags & OB_RECFLAG1_DANGEROUS) != 0;
	OBTEST_DOINTCOMPARE(pMiscRecord->IsDangerous(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check quest item flag")
        Flag = (g_TestValues[Index].Flags & OB_RECFLAG1_QUESTITEM) != 0;
	OBTEST_DOINTCOMPARE(pMiscRecord->IsQuestItem(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check master flag")
        Flag = (g_TestValues[Index].Flags & OB_RECFLAG1_MASTER) != 0;
	OBTEST_DOINTCOMPARE(pMiscRecord->IsMaster(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check deleted flag")
        Flag = (g_TestValues[Index].Flags & OB_RECFLAG1_DELETED) != 0;
	OBTEST_DOINTCOMPARE(pMiscRecord->IsDeleted(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check compressed flag")
        Flag = (g_TestValues[Index].Flags & OB_RECFLAG1_COMPRESSED) != 0;
	OBTEST_DOINTCOMPARE(pMiscRecord->IsCompressed(), ==, Flag);
    OBTEST_END_TEST()
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestRecord_Input()
 *=========================================================================*/



