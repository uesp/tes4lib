/*===========================================================================
 *
 * File:	ObLtexRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObLtexRecord class for land texture records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obltexrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLtexRecord, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_GNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLtexRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLtexRecord, CObRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObLtexRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObLtexRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLtexRecord Constructor
 *
 *=========================================================================*/
CObLtexRecord::CObLtexRecord () {
}
/*===========================================================================
 *		End of Class CObLtexRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLtexRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLtexRecord::Destroy (void) {

  CObRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLtexRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLtexRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLtexRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObLtexRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLtexRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLtexRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObLtexRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLtexRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLtexRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObLtexRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLtexRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLtexRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLtexRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLtexRecord Set Field Methods
 *=========================================================================*/

