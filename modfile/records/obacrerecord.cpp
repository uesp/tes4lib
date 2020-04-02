/*===========================================================================
 *
 * File:	ObAcreRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	10 September, 2006
 *
 * Implements the CObAcreRecord class for creature referece records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obacrerecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAcreRecord, CObBaseRefrRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_XESP, CObXespSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XGLB, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XRNK, CObLongSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAcreRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAcreRecord, CObBaseRefrRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObAcreRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObAcreRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAcreRecord Constructor
 *
 *=========================================================================*/
CObAcreRecord::CObAcreRecord () {
}
/*===========================================================================
 *		End of Class CObAcreRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAcreRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAcreRecord::Destroy (void) {

  CObBaseRefrRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObAcreRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAcreRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObAcreRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObBaseRefrRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObAcreRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAcreRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAcreRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObBaseRefrRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObAcreRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAcreRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAcreRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObBaseRefrRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObAcreRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAcreRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAcreRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAcreRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAcreRecord Set Field Methods
 *=========================================================================*/

