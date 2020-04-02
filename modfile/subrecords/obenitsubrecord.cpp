/*===========================================================================
 *
 * File:	Obenitsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obenitsubrecord.h"


/*===========================================================================
 *
 * Class CObEnitSubrecord Constructor
 *
 *=========================================================================*/
CObEnitSubrecord::CObEnitSubrecord () {

 }
/*===========================================================================
 *		End of Class CObEnitSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnitSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEnitSubrecord::Destroy (void) {

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObEnitSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnitSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObEnitSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  m_Data.Type         = OB_ENCHTYPE_SCROLL;
  m_Data.ChargeAmount = 0;
  m_Data.EnchantCost  = 0;
  m_Data.Flags        = 0;

  m_RecordSize = OBENIT_SUBRECORD_SIZE;
 }
/*===========================================================================
 *		End of Class Method CObEnitSubrecord::InitializeNew()
 *=========================================================================*/

