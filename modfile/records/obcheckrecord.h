/*===========================================================================
 *
 * File:	Obcheckrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 11, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCHECKRECORD_H
#define __OBCHECKRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Function type used to check records for various purposes */
  typedef bool (*OBCHECKRECORDFUNC) (CObRecord* pRecord, const long UserData);

	/* Used to export various file types */
  struct obexportinfo_t {
	const obrectype_t*	pRecordType;
	obformid_t		GroupFormID;
	bool			RecurseGroups;
	OBCHECKRECORDFUNC	CheckFunction;
	obfieldid_t*		pFieldList;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
  bool IsObMarkerReference   (CObRecord* pRecord, const long UserData);
  bool IsObPlantReference    (CObRecord* pRecord, const long UserData);
  bool IsObTeleportReference (CObRecord* pRecord, const long UserData);
/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obcheckrecord.H
 *=========================================================================*/

