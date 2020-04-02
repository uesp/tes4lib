/*===========================================================================
 *
 * File:	ObWthrRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	20 September, 2006
 *
 * Implements the CObWthrRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obwthrrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObWthrRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObSnamSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWthrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObWthrRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObWthrRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObWthrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWthrRecord Constructor
 *
 *=========================================================================*/
CObWthrRecord::CObWthrRecord () {
}
/*===========================================================================
 *		End of Class CObWthrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWthrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObWthrRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObWthrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWthrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObWthrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObWthrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWthrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWthrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObWthrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWthrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObWthrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObWthrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWthrRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObWthrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObWthrRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObWthrRecord Set Field Methods
 *=========================================================================*/

