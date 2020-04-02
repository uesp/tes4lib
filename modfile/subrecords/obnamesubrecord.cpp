/*===========================================================================
 *
 * File:	Obnamesubrec.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obnamesubrecord.h"


/*===========================================================================
 *
 * Class CObNameSubrecord Constructor
 *
 *=========================================================================*/
CObNameSubrecord::CObNameSubrecord () {


 }
/*===========================================================================
 *		End of Class CObNameSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNameSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObNameSubrecord::Destroy (void) {

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObNameSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNameSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObNameSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  m_RecordSize = OB_RECTYPE_SIZE;
  m_Data       = OB_NAME_NULL;
 }
/*===========================================================================
 *		End of Class Method CObNameSubrecord::InitializeNew()
 *=========================================================================*/
