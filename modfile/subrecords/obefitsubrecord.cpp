/*===========================================================================
 *
 * File:	Obefitsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obefitsubrecord.h"


/*===========================================================================
 *
 * Class CObEfitSubrecord Constructor
 *
 *=========================================================================*/
CObEfitSubrecord::CObEfitSubrecord () {

 }
/*===========================================================================
 *		End of Class CObEfitSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEfitSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObEfitSubrecord::Destroy (void) {

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObEfitSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEfitSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObEfitSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  m_Data.Name       = OB_NAME_NULL;
  m_Data.Magnitude  = 0;
  m_Data.Area       = 0;
  m_Data.Duration   = 0;
  m_Data.Type       = OB_EFFECTTYPE_SELF;
  m_Data.ActorValue = 0;

  m_RecordSize = OBEFIT_SUBRECORD_SIZE;
 }
/*===========================================================================
 *		End of Class Method CObEfitSubrecord::InitializeNew()
 *=========================================================================*/

