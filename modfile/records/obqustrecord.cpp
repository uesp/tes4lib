/*===========================================================================
 *
 * File:	ObQuestRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	20 September, 2006
 *
 * Implements the CObQustRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obqustrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObQustRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_CTDA, CObCtdaSubrecord::Create)
	//DEFINE_OBSUBRECCREATE(OB_NAME_CTDT, CObCtdtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRI, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRO, CObScroSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_QSTA, CObQstaSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObQustRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObQustRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObQustRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObQustRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObQustRecord Constructor
 *
 *=========================================================================*/
CObQustRecord::CObQustRecord () {
}
/*===========================================================================
 *		End of Class CObQustRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObQustRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObQustRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObQustRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObQustRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObQustRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObQustRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObQustRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObQustRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObQustRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObQustRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObQustRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObQustRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObQustRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObQustRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObQustRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObQustRecord Set Field Methods
 *=========================================================================*/

