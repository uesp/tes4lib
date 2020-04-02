/*===========================================================================
 *
 * File:	ObWatrRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	20 September, 2006
 *
 * Implements the CObWatrRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obwatrrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObWatrRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWatrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObWatrRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObWatrRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObWatrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWatrRecord Constructor
 *
 *=========================================================================*/
CObWatrRecord::CObWatrRecord () {
}
/*===========================================================================
 *		End of Class CObWatrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWatrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObWatrRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObWatrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWatrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObWatrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObWatrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWatrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWatrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObWatrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWatrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWatrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObWatrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWatrRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObWatrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWatrRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObWatrRecord Set Field Methods
 *=========================================================================*/

