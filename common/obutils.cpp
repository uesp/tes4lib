/*===========================================================================
 *
 * File:	Obutils.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obutils.h"
#include "windows.h"


/*===========================================================================
 *
 * Function - bool GetObInstallPath (Buffer);
 *
 * Attempt to find Oblivion's install path in the registry. On success true
 * is returned and the path copied to the given buffer. On error false is
 * returned.
 *
 *=========================================================================*/
bool GetObInstallPath (CSString& OutputBuffer) {
  HKEY  hKey;
  BYTE  Buffer[300];
  DWORD Size = 256;
  DWORD Type;
  int   Result;

  OutputBuffer.Empty();
  Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, OB_REG_SUBKEY, 0, KEY_READ, &hKey);

  if (Result != ERROR_SUCCESS) {
    AddObGeneralError("Failed to find Oblivion's install path in the Windows registry!");
    return (false);
   }

  Result = RegQueryValueEx(hKey, OB_REG_INSTALLPATH, NULL, &Type, Buffer, &Size);

  if (Result == ERROR_SUCCESS && Type == REG_SZ) {
    OutputBuffer = (char *)Buffer;
   }
  else {
    AddObGeneralError("Failed to find Oblivion's install path in the Windows registry!");
    RegCloseKey(hKey);
    return (false);
   }
     
  RegCloseKey(hKey);
  return (true);
 }
/*===========================================================================
 *		End of Function GetObInstallPath()
 *=========================================================================*/
