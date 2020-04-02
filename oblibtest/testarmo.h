/*===========================================================================
 *
 * File:	Testarmo.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTARMO_H
#define __TESTARMO_H


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

  struct testarmo_t {
	obformid_t	FormID;
	obarmodata_t	Data;
	dword		Flags;
	word		EnchantPts;
	dword		EnchantFormID;
	const SSCHAR*	pEditorID;
	const SSCHAR*	pItemName;
	const SSCHAR*	pModel1;
	const SSCHAR*	pModel2;
	const SSCHAR*	pModel3;
	const SSCHAR*	pModel4;
	const SSCHAR*	pIcon1;
	const SSCHAR*	pIcon2;
	obformid_t	ScriptFormID;
  };

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  bool TestArmo_Output (CObEspFile& File);
  bool TestArmo_Input  (CObEspFile& File);

  bool TestArmo_SetGet (void);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Testammo.H
 *=========================================================================*/
