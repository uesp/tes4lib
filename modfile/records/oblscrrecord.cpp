/*===========================================================================
 *
 * File:	ObLscrRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObLscrRecord class for load screen records.
 *
 *=========================================================================*/

	/* Include Files */
#include "oblscrrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLscrRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_LNAM, CObLnamSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLscrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLscrRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObLscrRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObLscrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLscrRecord Constructor
 *
 *=========================================================================*/
CObLscrRecord::CObLscrRecord () {
}
/*===========================================================================
 *		End of Class CObLscrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLscrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLscrRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLscrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLscrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLscrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObLscrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLscrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLscrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObLscrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLscrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLscrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObLscrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLscrRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLscrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLscrRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLscrRecord Set Field Methods
 *=========================================================================*/

