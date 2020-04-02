/*===========================================================================
 *
 * File:	TestClot.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 17, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTCLOT_H
#define __TESTCLOT_H


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

  struct testclot_t {
	obformid_t	FormID;
	obclotdata_t	Data;
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
  bool TestClot_Output (CObEspFile& File);
  bool TestClot_Input  (CObEspFile& File);

  bool TestClot_SetGet (void);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TestClot.H
 *=========================================================================*/
