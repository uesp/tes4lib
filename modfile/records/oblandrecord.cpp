/*===========================================================================
 *
 * File:	ObLandRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObLandRecord class for land records.
 *
 *=========================================================================*/

	/* Include Files */
#include "oblandrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObLandRecord, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_ATXT, CObAtxtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_BTXT, CObAtxtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_VTEX, CObVtexSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLandRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObLandRecord, CObRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObLandRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObLandRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLandRecord Constructor
 *
 *=========================================================================*/
CObLandRecord::CObLandRecord () {
}
/*===========================================================================
 *		End of Class CObLandRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLandRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObLandRecord::Destroy (void) {

  CObRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObLandRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLandRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObLandRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObLandRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLandRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLandRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObLandRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObLandRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObLandRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObLandRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLandRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLandRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObLandRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObLandRecord Set Field Methods
 *=========================================================================*/

