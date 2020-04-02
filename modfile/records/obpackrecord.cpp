/*===========================================================================
 *
 * File:	ObPackRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	16 September, 2006
 *
 * Implements the CObPackRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obpackrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObPackRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDA, CObCtdaSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDT, CObCtdtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_PLDT, CObPldtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_PTDT, CObPtdtSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPackRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObPackRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObPackRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObPackRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPackRecord Constructor
 *
 *=========================================================================*/
CObPackRecord::CObPackRecord () {
}
/*===========================================================================
 *		End of Class CObPackRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPackRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObPackRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObPackRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPackRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObPackRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObPackRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPackRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObPackRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObPackRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPackRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObPackRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObPackRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPackRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObPackRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPackRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObPackRecord Set Field Methods
 *=========================================================================*/

