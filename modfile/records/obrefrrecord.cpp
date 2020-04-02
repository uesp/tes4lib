/*===========================================================================
 *
 * File:	ObRefrrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Implements the CObRefrRecord class for reference type records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obrefrrecord.h"
#include "../obrecordhandler.h"
#include "../groups/obformidgroup.h"
#include "obcellrecord.h"
#include "obwrldrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObRefrRecord, CObBaseRefrRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_FULL, CObFullSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XTEL, CObXtelSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_TNAM, CObWordSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XTRG, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XRTM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XLOC, CObXlocSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XOWN, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XESP, CObXespSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XGLB, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XPCI, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRefrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObRefrRecord, CObBaseRefrRecord)
	ADD_OBFIELDMAP("Item Name",	 OB_FIELD_ITEMNAME,	  0, &CObRefrRecord::GetFieldItemName,		&CObRefrRecord::SetFieldItemName,&CObRefrRecord::CompareFieldItemName)
	ADD_OBFIELDMAP("TeleportFormID", OB_FIELD_TELEPORTFORMID, 0, &CObRefrRecord::GetFieldTeleportFormID,	NULL,				&CObRefrRecord::CompareFieldTeleportFormID)
	ADD_OBFIELDMAP("TeleportName",	 OB_FIELD_TELEPORTNAME,   0, &CObRefrRecord::GetFieldTeleportName,	NULL,				NULL)
	ADD_OBFIELDMAP("TeleportLocX",	 OB_FIELD_TELEPORTLOCX,   0, &CObRefrRecord::GetFieldTeleportLocX,	NULL,				&CObRefrRecord::CompareFieldTeleportLocX)
	ADD_OBFIELDMAP("TeleportLocY",	 OB_FIELD_TELEPORTLOCY,   0, &CObRefrRecord::GetFieldTeleportLocY,	NULL,				&CObRefrRecord::CompareFieldTeleportLocY)
	ADD_OBFIELDMAP("TeleportLocZ",	 OB_FIELD_TELEPORTLOCZ,   0, &CObRefrRecord::GetFieldTeleportLocZ,	NULL,				&CObRefrRecord::CompareFieldTeleportLocZ)
	ADD_OBFIELDMAP("TeleportAngleX", OB_FIELD_TELEPORTANGLEX, 0, &CObRefrRecord::GetFieldTeleportAngleX,	NULL,				&CObRefrRecord::CompareFieldTeleportAngleX)
	ADD_OBFIELDMAP("TeleportAngleY", OB_FIELD_TELEPORTANGLEY, 0, &CObRefrRecord::GetFieldTeleportAngleY,	NULL,				&CObRefrRecord::CompareFieldTeleportAngleY)
	ADD_OBFIELDMAP("TeleportAngleZ", OB_FIELD_TELEPORTANGLEZ, 0, &CObRefrRecord::GetFieldTeleportAngleZ,	NULL,				&CObRefrRecord::CompareFieldTeleportAngleZ)
	ADD_OBFIELDMAP("MarkerType",     OB_FIELD_MARKERTYPE,     0, &CObRefrRecord::GetFieldMarkerType,	NULL,				&CObRefrRecord::CompareFieldMarkerType)
	ADD_OBFIELDMAP("MarkerTypeID",   OB_FIELD_MARKERTYPEID,   0, &CObRefrRecord::GetFieldMarkerTypeID,	NULL,				&CObRefrRecord::CompareFieldMarkerTypeID)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRefrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Constructor
 *
 *=========================================================================*/
CObRefrRecord::CObRefrRecord () {
  m_pItemName   = NULL;
  m_pTeleport   = NULL;
  m_pMarkerType = NULL;
}
/*===========================================================================
 *		End of Class CObRefrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRefrRecord::Destroy (void) {
  m_pItemName   = NULL;
  m_pTeleport   = NULL;
  m_pMarkerType = NULL;

  CObBaseRefrRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRefrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObRefrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObBaseRefrRecord::InitializeNew();

	/* Create a new item name subrecords if required */
  if (HasFullItemName()) {
    AddNewSubrecord(OB_NAME_FULL);
    if (m_pItemName != NULL) m_pItemName->InitializeNew();
   }

}
/*===========================================================================
 *		End of Class Method CObRefrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRefrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_FULL) {
    m_pItemName = ObCastClass(CObFullSubrecord, pSubrecord);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_XTEL) {
    m_pTeleport = ObCastClass(CObXtelSubrecord, pSubrecord);
    TEST_INTVALUE1(pSubrecord->GetRecordSize(), OB_XTEL_SUBRECORD_SIZE, OB_NAME_XTEL);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_TNAM) {
    m_pMarkerType = ObCastClass(CObWordSubrecord, pSubrecord);
    TEST_INTVALUE1(pSubrecord->GetRecordSize(), 2, OB_NAME_TNAM);
  }
  else {
    CObBaseRefrRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObRefrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRefrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pItemName == pSubrecord) {
    m_pItemName = NULL;
  }
  else if (m_pTeleport == pSubrecord) {
    m_pTeleport = NULL;
  }
  else if (m_pMarkerType == pSubrecord) {
    m_pMarkerType = NULL;
  }
  else {
    CObBaseRefrRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObRefrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefrRecord Method - void SetItemName (pString);
 *
 *=========================================================================*/
void CObRefrRecord::SetItemName (const SSCHAR* pString) {

  if (m_pItemName == NULL) {
     AddNewSubrecord(OB_NAME_FULL);
     if (m_pItemName == NULL) return;
     m_pItemName->InitializeNew();
  }

  m_pItemName->SetString(pString);
}
/*===========================================================================
 *		End of Class Method CObRefrRecord::SetItemName()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRefrRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldItemName, String.Format("%s", GetItemName()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportFormID, String.Format("0x%08X", GetTeleportFormID()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportLocX, String.Format("%g", GetTeleportLocX()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportLocY, String.Format("%g", GetTeleportLocY()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportLocZ, String.Format("%g", GetTeleportLocZ()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportAngleX, String.Format("%g", GetTeleportAngleX()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportAngleY, String.Format("%g", GetTeleportAngleY()))
DEFINE_OBGETFIELD(CObRefrRecord::GetFieldTeleportAngleZ, String.Format("%g", GetTeleportAngleZ()))

BEGIN_OBGETFIELD(CObRefrRecord::GetFieldMarkerTypeID)
	if (!IsMapMarker()) {
	  String = "(null)";
	}
	else {
	  String.Format("%d", GetMarkerType());
	}
END_OBGETFIELD()

BEGIN_OBGETFIELD(CObRefrRecord::GetFieldMarkerType)
	if (!IsMapMarker()) {
	  String.Empty();
	}
	else {
	  String.Format("%s", GetObMapMarkerTypeString(GetMarkerType()));
	}
END_OBGETFIELD()

BEGIN_OBGETFIELD(CObRefrRecord::GetFieldTeleportName)
	CObBaseRecord*  pRecord;
	CObFormIDGroup* pGroup = NULL;
	CObCellRecord*  pCell  = NULL;
	obformid_t      FormID = GetTeleportFormID();
	obformid_t	CellFormID;
	
	if (FormID == OB_FORMID_NULL) {
	  String.Empty();
	  return (true);
	 }
	else if (m_pParent != NULL) {
	  pRecord = m_pParent->FindFormID(FormID);
	  if (pRecord != NULL && pRecord->GetParentGroup() != NULL) pGroup = ObCastClass(CObFormIDGroup, pRecord->GetParentGroup());
	 }

	if (pGroup != NULL) {
	  CellFormID = pGroup->GetParentFormID();
	  pRecord = m_pParent->FindFormID(CellFormID);
	  if (pRecord != NULL) pCell = ObCastClass(CObCellRecord, pRecord);
	}

	if (pCell == NULL) {
	  String.Format("0x08%X", CellFormID);
	  return (true);
	}

	const SSCHAR* pString = pCell->GetCellName();

	if (pString == NULL || pString[0] == NULL_CHAR) {
	  pString = pCell->GetEditorID(); 
	  if (pString == NULL) pString = "";
	}

	String.Format("%s", pString);
END_OBGETFIELD()
/*===========================================================================
 *		End of CObRefrRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRefrRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObRefrRecord, CompareFieldItemName, GetItemName)
DEFINE_OBCOMPFIELDDWORD(CObRefrRecord, CompareFieldTeleportFormID, GetTeleportFormID)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportLocX, GetTeleportLocX, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportLocY, GetTeleportLocY, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportLocZ, GetTeleportLocZ, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportAngleX, GetTeleportAngleX, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportAngleY, GetTeleportAngleY, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObRefrRecord, CompareFieldTeleportAngleZ, GetTeleportAngleZ, 100.0f)
DEFINE_OBCOMPFIELDDWORD(CObRefrRecord, CompareFieldMarkerType, GetMarkerType)
DEFINE_OBCOMPFIELDDWORD(CObRefrRecord, CompareFieldMarkerTypeID, GetMarkerType)
/*===========================================================================
 *		End of CObRefrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRefrRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObRefrRecord::SetFieldItemName)
  SetItemName(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObRefrRecord Set Field Methods
 *=========================================================================*/

