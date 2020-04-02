/*===========================================================================
 *
 * File:	Obutils.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Various Oblivion related utility functions and definitions.
 *
 *=========================================================================*/
#ifndef __OBUTILS_H
#define __OBUTILS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberrorhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Registry keys */
  #define OB_REG_SUBKEY      "SOFTWARE\\Bethesda Softworks\\Oblivion"
  #define OB_REG_INSTALLPATH "Installed Path"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Attempt to find the Oblivion install path in the registry */
  bool GetObInstallPath (CSString& Buffer);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obutils.H
 *=========================================================================*/