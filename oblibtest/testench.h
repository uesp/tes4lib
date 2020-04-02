/*===========================================================================
 *
 * File:	TestEnch.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTENCH_H
#define __TESTENCH_H


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

  struct testeff_t {
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

  struct testench_t {
	obformid_t	FormID;
	obenitdata_t	Data;
	const SSCHAR*	pEditorID;
	testeff_t*	Effects[5];
  };

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  bool TestEnch_Output (CObEspFile& File);
  bool TestEnch_Input  (CObEspFile& File);

  bool TestEnch_SetGet (void);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TestEnch.H
 *=========================================================================*/
