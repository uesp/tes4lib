/*===========================================================================
 *
 * File:	Obtes4record.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obtes4record.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObTes4Record, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_HEDR, CObHedrSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNAM, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_MAST, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObInt64Subrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObTes4Record, CObRecord)
	ADD_OBFIELDMAP("Summary",  OB_FIELD_SUMMARY,		  0, &CObTes4Record::GetFieldSummary,	  &CObTes4Record::SetFieldSummary,	&CObTes4Record::CompareFieldSummary)
	ADD_OBFIELDMAP("Author",   OB_FIELD_AUTHOR,		  0, &CObTes4Record::GetFieldAuthor,	  &CObTes4Record::SetFieldAuthor,	&CObTes4Record::CompareFieldAuthor)
	ADD_OBFIELDMAP("Version",  OB_FIELD_VERSION,     OBRF_NOCSV, &CObTes4Record::GetFieldVersion,	  NULL,					&CObTes4Record::CompareFieldVersion)
	ADD_OBFIELDMAP("Records",  OB_FIELD_RECORDCOUNT, OBRF_NOCSV, &CObTes4Record::GetFieldRecordCount, NULL,					&CObTes4Record::CompareFieldRecordCount)
	ADD_OBFIELDMAP("FileType", OB_FIELD_FILETYPE,    OBRF_NOCSV, &CObTes4Record::GetFieldFileType,	  NULL,					&CObTes4Record::CompareFieldFileType)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Constructor
 *
 *=========================================================================*/
CObTes4Record::CObTes4Record () {

  m_pHeader    = NULL;
  m_pCreatedBy = NULL;
  m_pSummary   = NULL;

 }
/*===========================================================================
 *		End of Class CObTes4Record Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void Destroy (void);
 *
 *=========================================================================*/
void CObTes4Record::Destroy (void) {

  m_pHeader    = NULL;
  m_pCreatedBy = NULL;
  m_pSummary   = NULL;

  CObRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObTes4Record::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void AddMaster (pMaster, Size);
 *
 *=========================================================================*/
void CObTes4Record::AddMaster (const SSCHAR* pMaster, const int64 Size) {
  CObSubrecord*        pSubrecord;
  CObStringSubrecord*  pMast;
  CObInt64Subrecord*   pData;
  
	/* Set the master filename */
  pSubrecord = AddNewSubrecord(OB_NAME_MAST);
  pSubrecord->InitializeNew();

  pMast = ObCastClass(CObStringSubrecord, pSubrecord);
  if (pMast != NULL) pMast->SetString(pMaster);

	/* Add the master data subrecord */
  pSubrecord = AddNewSubrecord(OB_NAME_DATA);
  pSubrecord->InitializeNew();

  pData = ObCastClass(CObInt64Subrecord, pSubrecord);
  if (pData != NULL) pData->SetValue(Size);
  
 }
/*===========================================================================
 *		End of Class Method CObTes4Record::AddMaster()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void DeleteMasters (void);
 *
 * Deletes all masters from the header.
 *
 *=========================================================================*/
void CObTes4Record::DeleteMasters (void) {
  DeleteSubrecords(OB_NAME_MAST);
  DeleteSubrecords(OB_NAME_DATA);
}
/*===========================================================================
 *		End of Class Method CObTes4Record::DeleteMasters()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObTes4Record::InitializeNew (void) {

  CObRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_HEDR);
  if (m_pHeader != NULL) m_pHeader->InitializeNew();

  AddNewSubrecord(OB_NAME_CNAM);

  if (m_pCreatedBy != NULL) {
    m_pCreatedBy->InitializeNew();
    m_pCreatedBy->SetString("DEFAULT");
   }

 }
/*===========================================================================
 *		End of Class Method CObTes4Record::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObTes4Record::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_HEDR)
    m_pHeader = ObCastClass(CObHedrSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_CNAM)
    m_pCreatedBy = ObCastClass(CObStringSubrecord, pSubrecord);
  else if (pSubrecord->GetRecordType() == OB_NAME_SNAM)
    m_pSummary = ObCastClass(CObStringSubrecord, pSubrecord);
  else
    CObRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObTes4Record::OnAddSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObTes4Record::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pHeader == pSubrecord)
    m_pHeader = NULL;
  else if (m_pCreatedBy == pSubrecord)
    m_pCreatedBy = NULL;
  else if (m_pSummary == pSubrecord)
    m_pSummary = NULL;
  else
    CObRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObTes4Record::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void SetAuthor (pString);
 *
 *=========================================================================*/
void CObTes4Record::SetAuthor (const SSCHAR* pString) { 

  if (m_pCreatedBy == NULL) {
    AddNewSubrecord(OB_NAME_CNAM);
    if (m_pCreatedBy == NULL) return;
    m_pCreatedBy->InitializeNew();
   } 

  m_pCreatedBy->SetString(pString); 
 }
/*===========================================================================
 *		End of Class Method CObTes4Record::SetAuthor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObTes4Record Method - void SetSummary (pString);
 *
 *=========================================================================*/
void CObTes4Record::SetSummary (const SSCHAR* pString) { 

  if (m_pSummary == NULL) {
    AddNewSubrecord(OB_NAME_SNAM);
    if (m_pSummary == NULL) return;
    m_pSummary->InitializeNew();
   } 

  m_pSummary->SetString(pString); 
 }
/*===========================================================================
 *		End of Class Method CObTes4Record::SetSummary()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObTes4Record Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObTes4Record::GetFieldSummary,     String.Format("%s",     GetSummary()))
DEFINE_OBGETFIELD(CObTes4Record::GetFieldAuthor,      String.Format("%s",     GetAuthor()))
DEFINE_OBGETFIELD(CObTes4Record::GetFieldVersion,     String.Format("%.1f",   GetVersion()))
DEFINE_OBGETFIELD(CObTes4Record::GetFieldRecordCount, String.Format("%d",     GetRecordCount()))
DEFINE_OBGETFIELD(CObTes4Record::GetFieldFileType,    String.Format("0x%08X", GetFileType()))
/*===========================================================================
 *		End of CObTes4Record Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObTes4Record Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObTes4Record, CompareFieldSummary, GetSummary)
DEFINE_OBCOMPFIELDSTRING(CObTes4Record, CompareFieldAuthor, GetAuthor)
DEFINE_OBCOMPFIELDFLOAT(CObTes4Record, CompareFieldVersion, GetVersion, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObTes4Record, CompareFieldRecordCount, GetRecordCount)
DEFINE_OBCOMPFIELDDWORD(CObTes4Record, CompareFieldFileType, GetFileType)
/*===========================================================================
 *		End of CObTes4Record Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObTes4Record Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObTes4Record::SetFieldSummary)
  SetSummary(pString);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObTes4Record::SetFieldAuthor)
  SetAuthor(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObTes4Record Set Field Methods
 *=========================================================================*/

