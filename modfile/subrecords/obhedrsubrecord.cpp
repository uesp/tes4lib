/*===========================================================================
 *
 * File:	Obhedrsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obhedrsubrecord.h"


/*===========================================================================
 *
 * Class CObHedrSubrecord Constructor
 *
 *=========================================================================*/
CObHedrSubrecord::CObHedrSubrecord () {


 }
/*===========================================================================
 *		End of Class CObHedrSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObHedrSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObHedrSubrecord::Destroy (void) {
  
  m_Data.RecordCount = 0;
  m_Data.Version     = OBHEDR_VERSION_DEFAULT;
  m_Data.FileType    = OBHEDR_FILETYPE_MASTER;

  CObSubrecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObHedrSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObHedrSubrecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObHedrSubrecord::InitializeNew (void) {
  CObSubrecord::InitializeNew();

  m_Data.RecordCount = 0;
  m_Data.Version     = OBHEDR_VERSION_DEFAULT;
  m_Data.FileType    = OBHEDR_FILETYPE_MASTER;

  m_RecordSize = OBHEDR_SUBRECORD_SIZE;
 }
/*===========================================================================
 *		End of Class Method CObHedrSubrecord::InitializeNew()
 *=========================================================================*/
