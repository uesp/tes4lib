/*===========================================================================
 *
 * File:	ObNpcRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	10 September, 2006
 *
 * Implements the CObNpcRecord class for NPC records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obnpcrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObNpcRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SPLO, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNTO, CObCntoSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_PKID, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRI, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_HNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_CNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_RNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_INAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ZNAM, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObSnamSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObNpcRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObNpcRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObNpcRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObNpcRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNpcRecord Constructor
 *
 *=========================================================================*/
CObNpcRecord::CObNpcRecord () {
}
/*===========================================================================
 *		End of Class CObNpcRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNpcRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObNpcRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObNpcRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNpcRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObNpcRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObNpcRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNpcRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObNpcRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObNpcRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNpcRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObNpcRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObNpcRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObNpcRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObNpcRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObNpcRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObNpcRecord Set Field Methods
 *=========================================================================*/

