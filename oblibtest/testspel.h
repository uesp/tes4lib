/*===========================================================================
 *
 * File:	TestSpel.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTSPEL_H
#define __TESTSPEL_H


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

  struct testeffspel_t {
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

  struct testspel_t {
	obformid_t	FormID;
	obspitdata_t	Data;
	const SSCHAR*	pEditorID;
	const SSCHAR*	pName;
	testeffspel_t*	Effects[5];
  };

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  bool TestSpel_Output (CObEspFile& File);
  bool TestSpel_Input  (CObEspFile& File);

  bool TestSpel_SetGet (void);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TestSpel.H
 *=========================================================================*/
