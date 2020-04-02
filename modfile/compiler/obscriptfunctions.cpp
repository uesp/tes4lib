/*===========================================================================
 *
 * File:	Obscriptfunctions.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscriptfunctions.h"


/*===========================================================================
 *
 * Class CObScriptFunctions Constructor
 *
 *=========================================================================*/
CObScriptFunctions::CObScriptFunctions() {
  m_FunctionNameMap.InitHashTable(1001);
  m_ConsoleNameMap.InitHashTable(1001);
}
/*===========================================================================
 *		End of Class CObScriptFunctions Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunctions Method - void Destroy (void);
 *
 *=========================================================================*/
void CObScriptFunctions::Destroy (void) {
  m_FunctionNameMap.Destroy();
  m_ConsoleNameMap.Destroy();
  m_Functions.Destroy();
}
/*===========================================================================
 *		End of Class Method CObScriptFunctions::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunctions Method - CObScriptFunction* GetFunction (pString);
 *
 *=========================================================================*/
CObScriptFunction* CObScriptFunctions::GetFunction (const char* pString) {
  CObScriptFunction* pFunction;
  bool               Result;

  Result = m_FunctionNameMap.Lookup(pString, pFunction);
  if (!Result) return (NULL);

  return (pFunction);
}
/*===========================================================================
 *		End of Class Method CObScriptFunctions::GetFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunctions Method - CObScriptFunction* GetConsoleFunction (pString);
 *
 *=========================================================================*/
CObScriptFunction* CObScriptFunctions::GetConsoleFunction (const char* pString) {
  CObScriptFunction* pFunction;
  bool               Result;

  Result = m_ConsoleNameMap.Lookup(pString, pFunction);
  if (!Result) return (NULL);

  return (pFunction);
}
/*===========================================================================
 *		End of Class Method CObScriptFunctions::GetConsoleFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunctions Method - void IndexFunction (pFunction);
 *
 *=========================================================================*/
void CObScriptFunctions::IndexFunction (CObScriptFunction* pFunction) {

	/* Check for an existing function */
  if (pFunction->IsConsoleFunction()) {
    if (GetConsoleFunction(pFunction->GetName()) != NULL) {
      AddObGeneralError("Overwriting existing console function '%s' definition!", pFunction->GetName());
    }
  
    if (pFunction->GetName()[0] != NULL_CHAR) m_ConsoleNameMap.SetAt(pFunction->GetName(), pFunction);
    if (pFunction->HasShortName()) m_ConsoleNameMap.SetAt(pFunction->GetShortName(), pFunction);
  }
  else {
    if (GetFunction(pFunction->GetName()) != NULL) {
      AddObGeneralError("Overwriting existing function '%s' definition!", pFunction->GetName());
    }
  
    if (pFunction->GetName()[0] != NULL_CHAR) m_FunctionNameMap.SetAt(pFunction->GetName(), pFunction);
    if (pFunction->HasShortName()) m_FunctionNameMap.SetAt(pFunction->GetShortName(), pFunction);
  }

}
/*===========================================================================
 *		End of Class Method CObScriptFunctions::IndexFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScriptFunctions Method - bool Load (pFilename, CustomFlags);
 *
 *=========================================================================*/
bool CObScriptFunctions::Load (const char* pFilename, const dword CustomFlags) {
  CObScriptFunction* pFunction;
  CObFile            File;
  CSString           Buffer;
  bool               Result;

  Result = File.Open(pFilename, "rt");
  if (!Result) return (false);

  while (!File.IsEOF()) {
    Result = File.ReadLine(Buffer);
    if (!Result) return (false);

    Buffer.Trim();

    if (Buffer.CompareNoCase("function") == 0) {
      pFunction = new CObScriptFunction;
      m_Functions.Add(pFunction);
      pFunction->SetCustomFlags(CustomFlags);

      pFunction->Read(File);
      IndexFunction(pFunction);
    }
    else if (!Buffer.IsEmpty()) {
      AddObGeneralError("%5u: Unknown function data '%s'!", File.GetLineCount(), Buffer.c_str());
    }

  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObScriptFunctions::Load()
 *=========================================================================*/

