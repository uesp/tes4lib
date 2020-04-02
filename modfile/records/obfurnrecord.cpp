/*===========================================================================
 *
 * File:	ObFurnRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obfurnrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObFurnRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_MNAM, CObDwordSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObFurnRecord, CObItem1Record)
	//ADD_OBFIELDALL("Value",  OB_FIELD_VALUE,  0, CObFurnRecord, FieldValue)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnRecord Constructor
 *
 *=========================================================================*/
CObFurnRecord::CObFurnRecord () {
  m_pMarkers = NULL;
}
/*===========================================================================
 *		End of Class CObFurnRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObFurnRecord::Destroy (void) {
  m_pMarkers = NULL;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObFurnRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObFurnRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  AddNewSubrecord(OB_NAME_MNAM);
  if (m_pMarkers != NULL) m_pMarkers->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObFurnRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFurnRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_MNAM) {
    m_pMarkers = ObCastClass(CObDwordSubrecord, pSubrecord);
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObFurnRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFurnRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFurnRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pMarkers == pSubrecord) {
    m_pMarkers = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObFurnRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFurnRecord Get Field Methods
 *
 *=========================================================================*/

/*===========================================================================
 *		End of CObFurnRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFurnRecord Compare Field Methods
 *
 *=========================================================================*/

/*===========================================================================
 *		End of CObFurnRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFurnRecord Set Field Methods
 *
 *=========================================================================*/

/*===========================================================================
 *		End of CObFurnRecord Set Field Methods
 *=========================================================================*/
