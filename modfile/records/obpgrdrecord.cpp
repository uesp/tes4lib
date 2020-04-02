/*===========================================================================
 *
 * File:	ObPgrdRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	16 September, 2006
 *
 * Implements the CObPgrdRecord class for path grid records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obpgrdrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObPgrdRecord, CObRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_PGRL, CObPgrlSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPgrdRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObPgrdRecord, CObRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObPgrdRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObPgrdRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrdRecord Constructor
 *
 *=========================================================================*/
CObPgrdRecord::CObPgrdRecord () {
}
/*===========================================================================
 *		End of Class CObPgrdRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrdRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObPgrdRecord::Destroy (void) {

  CObRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObPgrdRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrdRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObPgrdRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObPgrdRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrdRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObPgrdRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObPgrdRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrdRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObPgrdRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObPgrdRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPgrdRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObPgrdRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObPgrdRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObPgrdRecord Set Field Methods
 *=========================================================================*/

