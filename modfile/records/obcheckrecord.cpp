/*===========================================================================
 *
 * File:	Obcheckrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obcheckrecord.h"
#include "obrefrrecord.h"
#include "../obrecordhandler.h"



/*===========================================================================
 *
 * Function - bool IsObPlantReference (pRecord, UserData);
 *
 * Checks if the given reference is a plant.
 *
 *=========================================================================*/
bool IsObPlantReference (CObRecord* pRecord, const long UserData) {
  CObRefrRecord* pReference;
  CObBaseRecord* pBase;

  pReference = ObCastClassNull(CObRefrRecord, pRecord);
  if (pReference == NULL) return (false);
  if (pRecord->GetParent() == NULL) return (false);

  pBase = pRecord->GetParent()->FindFormID(pReference->GetBaseFormID());
  if (pBase == NULL) return (false);

	/* Is this reference a plant? */
  if (pBase->GetRecordType() == OB_NAME_FLOR) return (true);
  return (false);
}
/*===========================================================================
 *		End of Function IsObPlantReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsObMarkerReference (pRecord, UserData);
 *
 * Checks if the given reference is a marker.
 *
 *=========================================================================*/
bool IsObMarkerReference (CObRecord* pRecord, const long UserData) {
  CObRefrRecord* pReference;

  pReference = ObCastClassNull(CObRefrRecord, pRecord);
  if (pReference == NULL) return (false);

  if (pReference->IsMapMarker()) return (true);
  return (false);
}
/*===========================================================================
 *		End of Function IsObMarkerReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsObTeleportReference (pRecord, UserData);
 *
 * Checks if the given record is a reference that is a teleport location.
 *
 *=========================================================================*/
bool IsObTeleportReference (CObRecord* pRecord, const long UserData) {
  CObRefrRecord* pReference;

  pReference = ObCastClassNull(CObRefrRecord, pRecord);
  if (pReference == NULL) return (false);

  if (pReference->GetTeleportData() != NULL) return (true);
  return (false);
}
/*===========================================================================
 *		End of Function IsObTeleportReference()
 *=========================================================================*/




