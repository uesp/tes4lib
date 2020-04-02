/*===========================================================================
 *
 * File:	Obspitsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obspitsubrecord.h"


/*===========================================================================
 *
 * Class CObSpitSubrecord Constructor
 *
 *=========================================================================*/
CObSpitSubrecord::CObSpitSubrecord () {

 }
/*===========================================================================
 *		End of Class CObSpitSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpitSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObSpitSubrecord::Destroy (void) {

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObSpitSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSpitSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObSpitSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  memset(&m_Data, 0, sizeof(m_Data));

  m_RecordSize = OBSPIT_SUBRECORD_SIZE;
 }
/*===========================================================================
 *		End of Class Method CObSpitSubrecord::InitializeNew()
 *=========================================================================*/

