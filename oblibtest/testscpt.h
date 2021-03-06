/*===========================================================================
 *
 * File:	TestScpt.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TESTSCPT_H
#define __TESTSCPT_H


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

  struct testscpt_t {
	obformid_t	FormID;
	const SSCHAR*	pEditorID;
	const SSCHAR*	pText;
  };

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  bool TestScpt_SetGet (void);
  bool TestScpt_Output (CObEspFile& File);
  bool TestScpt_Input  (CObEspFile& File);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TestScpt.H
 *=========================================================================*/
