/*===========================================================================
 *
 * File:	Obbaserecord.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 10, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obbaserecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Class CObBaseRecord Constructor
 *
 *=========================================================================*/
CObBaseRecord::CObBaseRecord () {
  m_pParent      = NULL;
  m_pParentGroup = NULL;

  m_CacheFlags   = 0;
}
/*===========================================================================
 *		End of Class CObBaseRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecord Destructor
 *
 *=========================================================================*/
CObBaseRecord::~CObBaseRecord () {
  Destroy();
}
/*===========================================================================
 *		End of Class CObBaseRecord Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecord Method - void Destroy (void);
 *
 * Destroy object contents.
 *
 *=========================================================================*/
void CObBaseRecord::Destroy (void) {
  m_pParentGroup = NULL;
  m_CacheFlags   = 0;
}
/*===========================================================================
 *		End of Class Method CObBaseRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecord Method - bool IsActive (void) const;
 *
 *=========================================================================*/
bool CObBaseRecord::IsActive (void) const { 
   return (m_pParent ? m_pParent->IsActive() : false); 
}
/*===========================================================================
 *		End of Class Method CObBaseRecord::IsActive()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ReadObBaseHeader (File, Header);
 *
 * Helper function to read base header data for a group or record
 * from the current location in the given file.
 *
 *=========================================================================*/
bool ReadObBaseHeader (CObFile& File, obbaseheader_t& Header) {
  return File.Read(&Header, OB_BASEHEADER_SIZE);
 }
/*===========================================================================
 *		End of Function ReadObBaseHeader()
 *=========================================================================*/
