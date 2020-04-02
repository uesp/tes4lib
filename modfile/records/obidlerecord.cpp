/*===========================================================================
 *
 * File:	ObIdleRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObIdleRecord class for idle animation records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obidlerecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObIdleRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_DATA, CObIdleDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDA, CObCtdaSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDT, CObCtdtSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdleRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObIdleRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObIdleRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObIdleRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdleRecord Constructor
 *
 *=========================================================================*/
CObIdleRecord::CObIdleRecord () {
}
/*===========================================================================
 *		End of Class CObIdleRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdleRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObIdleRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObIdleRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdleRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObIdleRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObIdleRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdleRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObIdleRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObIdleRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObIdleRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObIdleRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObIdleRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdleRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObIdleRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObIdleRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObIdleRecord Set Field Methods
 *=========================================================================*/

