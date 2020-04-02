/*===========================================================================
 *
 * File:	ObDialRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObDialRecord class for dialogue records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obdialrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObDialRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_QSTI, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDialRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObDialRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObDialRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObDialRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDialRecord Constructor
 *
 *=========================================================================*/
CObDialRecord::CObDialRecord () {
}
/*===========================================================================
 *		End of Class CObDialRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDialRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObDialRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObDialRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDialRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObDialRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObDialRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDialRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObDialRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObDialRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDialRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObDialRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObDialRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDialRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObDialRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObDialRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObDialRecord Set Field Methods
 *=========================================================================*/

