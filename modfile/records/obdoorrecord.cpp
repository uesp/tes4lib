/*===========================================================================
 *
 * File:	ObDoorRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObDoorRecord class for activator records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obdoorrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObDoorRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_BNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ANAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_TNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDoorRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObDoorRecord, CObItem1Record)
	//ADD_OBFIELDALL("Name", OB_FIELD_FULL, 0, &CObDoorRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObDoorRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDoorRecord Constructor
 *
 *=========================================================================*/
CObDoorRecord::CObDoorRecord () {
}
/*===========================================================================
 *		End of Class CObDoorRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDoorRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObDoorRecord::Destroy (void) {

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObDoorRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDoorRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObDoorRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObDoorRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDoorRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObDoorRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

    CObItem1Record::OnAddSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObDoorRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDoorRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObDoorRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObDoorRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDoorRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObDoorRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDoorRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObDoorRecord Set Field Methods
 *=========================================================================*/

