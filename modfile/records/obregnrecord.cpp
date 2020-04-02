/*===========================================================================
 *
 * File:	ObRegnRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	20 September, 2006
 *
 * Implements the CObRegnRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obregnrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObRegnRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_RDWT, CObRdwtSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_RDGS, CObRdgsSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_RDOT, CObRdotSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_RDSD, CObRdsdSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_WNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRegnRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObRegnRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObRegnRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRegnRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRegnRecord Constructor
 *
 *=========================================================================*/
CObRegnRecord::CObRegnRecord () {
}
/*===========================================================================
 *		End of Class CObRegnRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRegnRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRegnRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRegnRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRegnRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObRegnRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObRegnRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRegnRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRegnRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObRegnRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRegnRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRegnRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObRegnRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRegnRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObRegnRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRegnRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObRegnRecord Set Field Methods
 *=========================================================================*/

