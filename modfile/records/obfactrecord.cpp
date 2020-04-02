/*===========================================================================
 *
 * File:	ObFactRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObFactRecord class for creature referece records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obfactrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObFactRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_XNAM, CObXnamSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFactRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObFactRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObFactRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObFactRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFactRecord Constructor
 *
 *=========================================================================*/
CObFactRecord::CObFactRecord () {
}
/*===========================================================================
 *		End of Class CObFactRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFactRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObFactRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObFactRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFactRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObFactRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObFactRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFactRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFactRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObFactRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFactRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObFactRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObFactRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFactRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObFactRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObFactRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObFactRecord Set Field Methods
 *=========================================================================*/

