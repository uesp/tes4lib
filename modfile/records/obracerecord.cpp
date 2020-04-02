/*===========================================================================
 *
 * File:	ObRaceRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	20 September, 2006
 *
 * Implements the CObRaceRecord class.
 *
 *=========================================================================*/

	/* Include Files */
#include "obracerecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObRaceRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SPLO, CObFormidSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_DNAM, CObDnamSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_VNAM, CObVnamSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_ENAM, CObEnamSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_XNAM, CObXnamSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRaceRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObRaceRecord, CObIdRecord)
	//ADD_OBFIELDALL("Name",	 OB_FIELD_FULL, 0, &CObRaceRecord::FieldFullName)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRaceRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRaceRecord Constructor
 *
 *=========================================================================*/
CObRaceRecord::CObRaceRecord () {
}
/*===========================================================================
 *		End of Class CObRaceRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRaceRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRaceRecord::Destroy (void) {

  CObIdRecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRaceRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRaceRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObRaceRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObIdRecord::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObRaceRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRaceRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRaceRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  
    CObIdRecord::OnAddSubrecord(pSubrecord);
  

 }
/*===========================================================================
 *		End of Class Event CObRaceRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRaceRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObRaceRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {


    CObIdRecord::OnDeleteSubrecord(pSubrecord);


}
/*===========================================================================
 *		End of Class Event CObRaceRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRaceRecord Get Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObRaceRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRaceRecord Set Field Methods
 *
 *=========================================================================*/
/*===========================================================================
 *		End of CObRaceRecord Set Field Methods
 *=========================================================================*/

