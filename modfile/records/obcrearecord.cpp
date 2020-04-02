/*===========================================================================
 *
 * File:	ObCreaRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	15 September, 2006
 *
 * Implements the CObCreaRecord class for creature records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obcrearecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObCreaRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObSnamSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SPLO, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNTO, CObCntoSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CSCR, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CSDI, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_INAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ZNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_PKID, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCreaRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObCreaRecord, CObItem1Record)
	//ADD_OBFIELDALL("Name", OB_FIELD_FULL, 0, &CObCreaRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObCreaRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCreaRecord Constructor
 *
 *=========================================================================*/
CObCreaRecord::CObCreaRecord () {
}
/*===========================================================================
 *		End of Class CObCreaRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCreaRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObCreaRecord::Destroy (void) {

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObCreaRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCreaRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObCreaRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObCreaRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCreaRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObCreaRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

    CObItem1Record::OnAddSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObCreaRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCreaRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObCreaRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

    CObItem1Record::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObCreaRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCreaRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObCreaRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObCreaRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObCreaRecord Set Field Methods
 *=========================================================================*/

