/*===========================================================================
 *
 * File:	ObClmtRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObClmtRecord class for climate records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obclmtrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObClmtRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_WLST, CObWlstSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClmtRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObClmtRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObClmtRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObClmtRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClmtRecord Constructor
 *
 *=========================================================================*/
CObClmtRecord::CObClmtRecord () {
}
/*===========================================================================
 *		End of Class CObClmtRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClmtRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObClmtRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObClmtRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClmtRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObClmtRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObClmtRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClmtRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObClmtRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObClmtRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObClmtRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObClmtRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {
    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObClmtRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClmtRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObClmtRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObClmtRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObClmtRecord Set Field Methods
 *=========================================================================*/

