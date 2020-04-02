/*===========================================================================
 *
 * File:	ObInfoRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObInfoRecord class for dialogue info records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obinforecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObInfoRecord, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDT, CObCtdtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDA, CObCtdaSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRO, CObScroSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_QSTI, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_TCLT, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_TCLF, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_NAME, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObInfoRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObInfoRecord, CObRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObInfoRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObInfoRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObInfoRecord Constructor
 *
 *=========================================================================*/
CObInfoRecord::CObInfoRecord () {
}
/*===========================================================================
 *		End of Class CObInfoRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObInfoRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObInfoRecord::Destroy (void) {

  CObRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObInfoRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObInfoRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObInfoRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObInfoRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObInfoRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObInfoRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObInfoRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObInfoRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObInfoRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObInfoRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObInfoRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObInfoRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObInfoRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObInfoRecord Set Field Methods
 *=========================================================================*/

