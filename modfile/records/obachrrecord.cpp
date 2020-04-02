/*===========================================================================
 *
 * File:	ObAchrRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	10 September, 2006
 *
 * Implements the CObAchrRecord class for NPC reference records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obachrrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObAchrRecord, CObBaseRefrRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_XESP, CObXespSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XHRS, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XMRC, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XPCI, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAchrRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObAchrRecord, CObBaseRefrRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObAchrRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObAchrRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAchrRecord Constructor
 *
 *=========================================================================*/
CObAchrRecord::CObAchrRecord () {
}
/*===========================================================================
 *		End of Class CObAchrRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAchrRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObAchrRecord::Destroy (void) {

  CObBaseRefrRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObAchrRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAchrRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObAchrRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObBaseRefrRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObAchrRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAchrRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAchrRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObBaseRefrRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObAchrRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObAchrRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObAchrRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {
    CObBaseRefrRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObAchrRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAchrRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAchrRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObAchrRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObAchrRecord Set Field Methods
 *=========================================================================*/

