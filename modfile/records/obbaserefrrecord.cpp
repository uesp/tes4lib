/*===========================================================================
 *
 * File:	ObBaseRefrrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	November 8, 2006
 *
 * Implements the CObBaseRefrRecord class for reference type records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obbaserefrrecord.h"
#include "../obrecordhandler.h"
#include "../groups/obformidgroup.h"
#include "obcellrecord.h"
#include "obwrldrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObBaseRefrRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_NAME, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObRefrDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XOWN, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XSCL, CObFloatSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBaseRefrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObBaseRefrRecord, CObIdRecord)
	ADD_OBFIELDMAP("LocationX",	 OB_FIELD_LOCATIONX,	  0, &CObBaseRefrRecord::GetFieldLocationX,		NULL,		&CObBaseRefrRecord::CompareFieldLocationX)
	ADD_OBFIELDMAP("LocationY",	 OB_FIELD_LOCATIONY,	  0, &CObBaseRefrRecord::GetFieldLocationY,		NULL,		&CObBaseRefrRecord::CompareFieldLocationY)
	ADD_OBFIELDMAP("LocationZ",	 OB_FIELD_LOCATIONZ,	  0, &CObBaseRefrRecord::GetFieldLocationZ,		NULL,		&CObBaseRefrRecord::CompareFieldLocationZ)
	ADD_OBFIELDMAP("AngleX",	 OB_FIELD_ANGLEX,	  0, &CObBaseRefrRecord::GetFieldAngleX,		NULL,		&CObBaseRefrRecord::CompareFieldAngleX)
	ADD_OBFIELDMAP("AngleY",	 OB_FIELD_ANGLEY,	  0, &CObBaseRefrRecord::GetFieldAngleY,		NULL,		&CObBaseRefrRecord::CompareFieldAngleY)
	ADD_OBFIELDMAP("AngleZ",	 OB_FIELD_ANGLEZ,	  0, &CObBaseRefrRecord::GetFieldAngleZ,		NULL,		&CObBaseRefrRecord::CompareFieldAngleZ)
	ADD_OBFIELDMAP("WorldSpace",     OB_FIELD_WORLDSPACE,     0, &CObBaseRefrRecord::GetFieldWorldSpace,		NULL,		NULL)
	ADD_OBFIELDMAP("BaseFormID",	 OB_FIELD_BASEFORMID,	  0, &CObBaseRefrRecord::GetFieldBaseFormID,		NULL,		&CObBaseRefrRecord::CompareFieldBaseFormID)
	ADD_OBFIELDMAP("BaseEditorID",	 OB_FIELD_BASEEDITORID,	  0, &CObBaseRefrRecord::GetFieldBaseEditorID,		NULL,		&CObBaseRefrRecord::CompareFieldBaseEditorID)
	ADD_OBFIELDMAP("BaseName",	 OB_FIELD_BASENAME,	  0, &CObBaseRefrRecord::GetFieldBaseName,		NULL,		NULL)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObBaseRefrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Constructor
 *
 *=========================================================================*/
CObBaseRefrRecord::CObBaseRefrRecord () {
  m_pData       = NULL;
  m_pName       = NULL;
}
/*===========================================================================
 *		End of Class CObBaseRefrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObBaseRefrRecord::Destroy (void) {
  m_pData       = NULL;
  m_pName       = NULL;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObBaseRefrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_NAME);
  if (m_pName != NULL) m_pName->InitializeNew();

  AddNewSubrecord(OB_NAME_DATA);
  if (m_pData != NULL) m_pData->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - bool IsActor (void);
 *
 *=========================================================================*/
bool CObBaseRefrRecord::IsActor (void) {
  CObRecord* pRecord;

  if (GetRecordType() == OB_NAME_ACRE) return (true);
  if (GetRecordType() == OB_NAME_ACHR) return (true);

  if (m_pName == NULL || m_pParent == NULL) return (false);
  
  pRecord = m_pParent->FindFormID(m_pName->GetValue());
  if (pRecord == NULL) return (false);

  if (pRecord->GetRecordType() == OB_NAME_NPC_ || pRecord->GetRecordType() == OB_NAME_CREA || pRecord->GetRecordType() == OB_NAME_LVLC) return (true);
  return (false);
}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::IsActor()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - bool IsContainer (void);
 *
 *=========================================================================*/
bool CObBaseRefrRecord::IsContainer (void) {
  CObRecord* pRecord;

  if (GetRecordType() == OB_NAME_ACRE) return (true);
  if (GetRecordType() == OB_NAME_ACHR) return (true);

  if (m_pName == NULL || m_pParent == NULL) return (false);
  
  pRecord = m_pParent->FindFormID(m_pName->GetValue());
  if (pRecord == NULL) return (false);

  if (pRecord->GetRecordType() == OB_NAME_CONT) return (true);
  if (pRecord->GetRecordType() == OB_NAME_NPC_ || pRecord->GetRecordType() == OB_NAME_CREA || pRecord->GetRecordType() == OB_NAME_LVLC) return (true);
  return (false);
}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::IsContainer()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - bool IsFormType (Type);
 *
 *=========================================================================*/
bool CObBaseRefrRecord::IsFormType (const int Type) {

	/* Test against known simple types */
  switch (Type) {
    case OB_FUNCPARAM_MAPMARKER:
        return IsMapMarker();
    case OB_FUNCPARAM_ACTOR:
	return IsActor();
    case OB_FUNCPARAM_CONTAINER:
	return IsContainer();
    case OB_FUNCPARAM_OBJECTREF:
	return (true);
  }

	/* Default */
  return CObIdRecord::IsFormType(Type);
}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::IsFormType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBaseRefrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_DATA) {
    m_pData = ObCastClass(CObRefrDataSubrecord, pSubrecord);
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), OB_REFRDATA_SUBRECORD_SIZE, OB_NAME_DATA);
  }
  else if (pSubrecord->GetRecordType() == OB_NAME_NAME) {
    m_pName = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

 }
/*===========================================================================
 *		End of Class Event CObBaseRefrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObBaseRefrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pData == pSubrecord) {
    m_pData = NULL;
  }
  else if (m_pName == pSubrecord) {
    m_pName = NULL;
  }
  else {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObBaseRefrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRefrRecord Method - void SetBaseFormID (FormID);
 *
 *=========================================================================*/
void CObBaseRefrRecord::SetBaseFormID (const obformid_t FormID) {

  if (m_pName == NULL) {
    AddNewSubrecord(OB_NAME_NAME);
    if (m_pName == NULL) return;
    m_pName->InitializeNew();
  }

  m_pName->SetValue(FormID);
}
/*===========================================================================
 *		End of Class Method CObBaseRefrRecord::SetBaseFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBaseRefrRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldBaseFormID, String.Format("0x%08X", GetBaseFormID()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldLocationX, String.Format("%g", GetLocationX()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldLocationY, String.Format("%g", GetLocationY()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldLocationZ, String.Format("%g", GetLocationZ()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldAngleX, String.Format("%g", GetAngleX()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldAngleY, String.Format("%g", GetAngleY()))
DEFINE_OBGETFIELD(CObBaseRefrRecord::GetFieldAngleZ, String.Format("%g", GetAngleZ()))

BEGIN_OBGETFIELD(CObBaseRefrRecord::GetFieldBaseEditorID)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetBaseFormID());
        String.Format("0x%08X", GetBaseFormID());
END_OBGETFIELD()

BEGIN_OBGETFIELD(CObBaseRefrRecord::GetFieldBaseName)
	CObBaseRecord* pBaseRecord = NULL;
	CObRecord*     pRecord = NULL;
	CObSubrecord*  pName = NULL;

	if (m_pParent   != NULL) pBaseRecord = m_pParent->FindFormID(GetBaseFormID());
	if (pBaseRecord != NULL) pRecord     = ObCastClass(CObRecord, pBaseRecord);
	if (pRecord     != NULL) pName       = pRecord->FindSubrecord(OB_NAME_FULL);

	if (pName != NULL) {
		String.Format("%s", pName->GetData());
	}
	else {
		String.Format("0x%08X", GetBaseFormID());
		return (true);
	}
END_OBGETFIELD()


BEGIN_OBGETFIELD(CObBaseRefrRecord::GetFieldWorldSpace)
	CObGroup*       pGroup;
	CObBaseRecord*  pRecord = NULL;
	CObWrldRecord*  pWorld  = NULL;
	
	pGroup = GetParentGroup();
	
	while (pGroup != NULL) {
	  if (pGroup->GetType() == OB_GROUP_WORLDCHILD) break;
	  pGroup = pGroup->GetParentGroup();
	}

	if (pGroup != NULL) {
	  obformid_t FormID = pGroup->GetHeader().Data.ParentFormID;

	  if (m_pParent != NULL) {
	    pRecord = m_pParent->FindFormID(FormID);
	    if (pRecord != NULL) pWorld = ObCastClass(CObWrldRecord, pRecord);
	  }

          if (pWorld == NULL)
	    String.Format("0x%08X", FormID);
	  else {
	    const SSCHAR* pString = pWorld->GetFullName();
	    if (pString[0] == NULL_CHAR) pString = pWorld->GetEditorID();
	    String.Format("%s", pString);
	  }
	}
END_OBGETFIELD()
/*===========================================================================
 *		End of CObBaseRefrRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObBaseRefrRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDDWORD(CObBaseRefrRecord, CompareFieldBaseFormID, GetBaseFormID)
DEFINE_OBCOMPFIELDEDITORID(CObBaseRefrRecord, CompareFieldBaseEditorID, GetBaseFormID)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldLocationX, GetLocationX, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldLocationY, GetLocationY, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldLocationZ, GetLocationZ, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldAngleX, GetAngleX, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldAngleY, GetAngleY, 100.0f)
DEFINE_OBCOMPFIELDFLOAT(CObBaseRefrRecord, CompareFieldAngleZ, GetAngleZ, 100.0f)
/*===========================================================================
 *		End of CObBaseRefrRecord Compare Field Methods
 *=========================================================================*/

