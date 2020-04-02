/*===========================================================================
 *
 * File:	Testtes4.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testtes4.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

tes4test_t g_Tes4TestValues = {
	{ 0.8f, 1, OBHEDR_FILETYPE_MASTER },
	"author text",
	"summary text"
 };

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - bool TestTes4_SetGet (void);
 *
 * Tests the basic set/get methods of a TES4 record.
 *
 *=========================================================================*/
bool TestTes4_SetGet (void) {
  CObTes4Record Record;

  OBTEST_LEVEL("TES4 Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Version")
	Record.SetVersion(g_Tes4TestValues.Data.Version);
	OBTEST_DOINTCOMPARE(Record.GetVersion(), ==, g_Tes4TestValues.Data.Version)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Filetype")
	Record.SetFileType(g_Tes4TestValues.Data.FileType);
	OBTEST_DOINTCOMPARE(Record.GetFileType(), ==, g_Tes4TestValues.Data.FileType)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Record count")
	Record.SetRecordCount(g_Tes4TestValues.Data.RecordCount);
	OBTEST_DOINTCOMPARE(Record.GetRecordCount(), ==, g_Tes4TestValues.Data.RecordCount)
	Record.SetRecordCount(1);
  OBTEST_END_TEST()

  OBTEST_START_TEST("Record count mod(0)")
        Record.SetRecordCount(1);
	Record.ModRecordCount(0);
	OBTEST_DOINTCOMPARE(Record.GetRecordCount(), ==, 1)
	Record.SetRecordCount(1);
  OBTEST_END_TEST()

  OBTEST_START_TEST("Record count mod(10)")
        Record.SetRecordCount(1);
	Record.ModRecordCount(123);
	OBTEST_DOINTCOMPARE(Record.GetRecordCount(), ==, 124)
	Record.SetRecordCount(1);
  OBTEST_END_TEST()

  OBTEST_START_TEST("Record count mod(-100)")
        Record.SetRecordCount(1);
	Record.ModRecordCount(-100);
	OBTEST_DOINTCOMPARE(Record.GetRecordCount(), ==, 0)
	Record.SetRecordCount(1);
  OBTEST_END_TEST()

  OBTEST_START_TEST("Summary text")
	Record.SetSummary(g_Tes4TestValues.pSummary);
	OBTEST_DOSTRCOMPARE(Record.GetSummary(), ==, g_Tes4TestValues.pSummary)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Author text")
	Record.SetAuthor(g_Tes4TestValues.pAuthor);
	OBTEST_DOSTRCOMPARE(Record.GetAuthor(), ==, g_Tes4TestValues.pAuthor)
  OBTEST_END_TEST()

  return (true);
 }
/*===========================================================================
 *		End of Function TestTes4_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestTes4_Output (File);
 *
 * Outputs current values to the given file.
 *
 *=========================================================================*/
bool TestTes4_Output (CObEspFile& File) {
  CObTes4Record* pRecord;

  OBTEST_LEVEL("TES4 Output New")

	/* Start with a fresh file */
  File.Destroy();
  File.InitializeNew();

  OBTEST_START_TEST("Get header in new file")
	pRecord = File.GetHeader();
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check header record count for new file")
	OBTEST_DOINTCOMPARE(pRecord->GetRecordCount(), ==, 0)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check new header formID")
	OBTEST_DOINTCOMPARE(pRecord->GetFormID(), ==, 0)
  OBTEST_END_TEST()


	/* Set values for output */
  pRecord->SetVersion(g_Tes4TestValues.Data.Version);
  pRecord->SetFileType(g_Tes4TestValues.Data.FileType);
  pRecord->SetAuthor(g_Tes4TestValues.pAuthor);
  pRecord->SetSummary(g_Tes4TestValues.pSummary);

  return (true);
 }
/*===========================================================================
 *		End of Function TestTes4_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestTes4_Input (File);
 *
 * Tests the values of the given file and ensures it matches the current
 * set of output values.
 *
 *=========================================================================*/
bool TestTes4_Input (CObEspFile& File) {
  CObTes4Record* pRecord = File.GetHeader();

  OBTEST_LEVEL("TES4 Output/Input")

  OBTEST_START_TEST("Version")
	OBTEST_DOINTCOMPARE(pRecord->GetVersion(), ==, g_Tes4TestValues.Data.Version)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Filetype")
	OBTEST_DOINTCOMPARE(pRecord->GetFileType(), ==, g_Tes4TestValues.Data.FileType)
  OBTEST_END_TEST()

    OBTEST_START_TEST("Summary text")
	pRecord->SetSummary(g_Tes4TestValues.pSummary);
	OBTEST_DOSTRCOMPARE(pRecord->GetSummary(), ==, g_Tes4TestValues.pSummary)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Author text")
	pRecord->SetAuthor(g_Tes4TestValues.pAuthor);
	OBTEST_DOSTRCOMPARE(pRecord->GetAuthor(), ==, g_Tes4TestValues.pAuthor)
  OBTEST_END_TEST()


  return (true);
 }
/*===========================================================================
 *		End of Function TestTes4_Input()
 *=========================================================================*/
