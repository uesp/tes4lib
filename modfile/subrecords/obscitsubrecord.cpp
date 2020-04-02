/*===========================================================================
 *
 * File:	Obscitsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscitsubrecord.h"


/*===========================================================================
 *
 * Class CObScitSubrecord Constructor
 *
 *=========================================================================*/
CObScitSubrecord::CObScitSubrecord () {

 }
/*===========================================================================
 *		End of Class CObScitSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScitSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObScitSubrecord::Destroy (void) {

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObScitSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScitSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObScitSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  m_Data.ScriptFormID = OB_FORMID_NULL;
  m_Data.School       = OB_SCHOOL_ALTERATION;
  m_Data.VisualEffect = OB_NAME_NULL;
  m_Data.Flags        = 0;

  m_RecordSize = OBSCIT_SUBRECORD_SIZE;
 }
/*===========================================================================
 *		End of Class Method CObScitSubrecord::InitializeNew()
 *=========================================================================*/

