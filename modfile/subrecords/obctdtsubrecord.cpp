/*===========================================================================
 *
 * File:	ObCtdtsubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 21, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obctdtsubrecord.h"


/*===========================================================================
 *
 * Class CObCtdtSubrecord Method - bool IsRefParam1 (FunctionCode);
 *
 * TODO: Proper function data.
 *
 *=========================================================================*/
bool CObCtdtSubrecord::IsRefParam1 (const int FunctionCode) {

  switch (FunctionCode) {
    case 122:
    case 84:
    case 45:
    case 180:
    case 76:
    case 1:
    case 182:
    case 73:
    case 60:
    case 288:
    case 74:
    case 99:
    case 67:
    case 230:
    case 71:
    case 32:
    case 310:
    case 68:
    case 228:
    case 161:
    case 149:
    case 72:
    case 224:
    case 69:
    case 136:
    case 246:
    case 47:
    case 27:
    case 193:
    case 199:
    case 195:
    case 197:
    case 201:
    case 132:
    case 129:
    case 130:
    case 56:
    case 79:
    case 53:
    case 66:
    case 58:
    case 59:
    case 172:
    case 214:
    case 280:
    case 163:
    case 162:
    case 278:
    case 223:
    case 42:
    case 43:
    case 44:
	return (true);	
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObCtdtSubrecord::IsRefParam1()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCtdtSubrecord Method - bool IsRefParam2 (FunctionCode);
 *
 * TODO: Proper function data.
 *
 *=========================================================================*/
bool CObCtdtSubrecord::IsRefParam2 (const int FunctionCode) {

  switch (FunctionCode) {
    case 60:
    case 280:
 	return (true);	
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObCtdtSubrecord::IsRefParam2()
 *=========================================================================*/




/*===========================================================================
 *
 * Class CObCtdtSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObCtdtSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
  dword Count = 0;

  if (IsRefParam1(m_Data.Function) && (obformid_t) m_Data.Parameter1 == OldID) {
    m_Data.Parameter1 = NewID;
   ++Count;
  }

  if (IsRefParam2(m_Data.Function) && (obformid_t) m_Data.Parameter2 == OldID) {
    m_Data.Parameter2 = NewID;
   ++Count;
  }

  return (Count); 
}
/*===========================================================================
 *		End of Class Method CObCtdtSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCtdtSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObCtdtSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  bool Result = true;

  if (IsRefParam1(m_Data.Function)) {
    Result &= ObFixupFormid(*(obformid_t *)&m_Data.Parameter1, m_Data.Parameter1, FixupArray);
  }

  if (IsRefParam2(m_Data.Function)) {
    Result &= ObFixupFormid(*(obformid_t *)&m_Data.Parameter2, m_Data.Parameter2, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObCtdtSubrecord::FixupFormID()
 *=========================================================================*/
