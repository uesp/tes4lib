/*===========================================================================
 *
 * File:	TestSgst.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTSGST_H
#define __TESTSGST_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obtest.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

  struct testeffsgst_t {
	const obrectype_t*	pName;
	dword		Type;
	dword		Magnitude;
	dword		Area;
	dword		Duration;
	dword		ActorValue;

	obformid_t	ScriptID;
	dword		School;
	const obrectype_t*	pVisualEffect;
	dword		Flags;
	const SSCHAR*	pScript;
   };

  struct testsgst_t {
	obformid_t	FormID;
	obsgstdata_t	Data;
	const SSCHAR*	pEditorID;
	const SSCHAR*	pItemName;
	const SSCHAR*	pModel;
	const SSCHAR*	pIcon;
	obformid_t	ScriptID;
	testeffsgst_t*	Effects[5];
  };

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  bool TestSgst_Output (CObEspFile& File);
  bool TestSgst_Input  (CObEspFile& File);

  bool TestSgst_SetGet (void);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TestSgst.H
 *=========================================================================*/
