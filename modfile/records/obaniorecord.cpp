/*===========================================================================
 *
 * File:	ObAnioRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObAnioRecord class for NPC reference records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obaniorecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAnioRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAnioRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAnioRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObAnioRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObAnioRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAnioRecord Constructor
 *
 *=========================================================================*/
CObAnioRecord::CObAnioRecord () {
}
/*===========================================================================
 *		End of Class CObAnioRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAnioRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAnioRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObAnioRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAnioRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObAnioRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObAnioRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAnioRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAnioRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObAnioRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAnioRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAnioRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObAnioRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAnioRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAnioRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAnioRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAnioRecord Set Field Methods
 *=========================================================================*/

