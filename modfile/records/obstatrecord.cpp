/*===========================================================================
 *
 * File:	ObStatRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obstatrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObStatRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_MODL, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObStatRecord, CObIdRecord)
	ADD_OBFIELDALL("Model",  OB_FIELD_MODEL,  0, CObStatRecord, FieldModel)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Constructor
 *
 *=========================================================================*/
CObStatRecord::CObStatRecord () {
  m_pModel = NULL;
}
/*===========================================================================
 *		End of Class CObStatRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObStatRecord::Destroy (void) {
  m_pModel = NULL;

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObStatRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObStatRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  AddNewSubrecord(OB_NAME_MODL);
  if (m_pModel != NULL) m_pModel->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObStatRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObStatRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_MODL) {
    m_pModel = ObCastClass(CObStringSubrecord, pSubrecord);
    //TEST_INTVALUE1(m_pMiscData->GetRecordSize(), 8, OB_NAME_DATA);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODB) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x04, OB_NAME_MODB);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_MODT) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 0x18, OB_NAME_MODT);
   }
  else {
    CObIdRecord::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObStatRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObStatRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pModel == pSubrecord)
    m_pModel = NULL;
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObStatRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStatRecord Method - void SetModel (pString);
 *
 *=========================================================================*/
void CObStatRecord::SetModel (const SSCHAR* pString) {

  if (m_pModel == NULL) {
     AddNewSubrecord(OB_NAME_MODL);
     if (m_pModel == NULL) return;
     m_pModel->InitializeNew();
  }

  m_pModel->SetString(pString);
}
/*===========================================================================
 *		End of Class Method CObStatRecord::SetModel()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObStatRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObStatRecord::GetFieldModel,  String.Format("%s", GetModel()))
/*===========================================================================
 *		End of CObStatRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObStatRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObStatRecord, CompareFieldModel, GetModel)
/*===========================================================================
 *		End of CObStatRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObStatRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObStatRecord::SetFieldModel)
  SetModel(pString);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObStatRecord Set Field Methods
 *=========================================================================*/
