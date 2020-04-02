/*===========================================================================
 *
 * File:	Obscriptfunctions.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSCRIPTFUNCTIONS_H
#define __OBSCRIPTFUNCTIONS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obscriptfunction.h"
  #include "../../common/dl_map.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Function map type definitions */
   typedef TGenRefPtrMap<const char*, CObScriptFunction, const char* > CObScriptFuncNameMap;
   typedef TGenRefPtrMap<const char*, CObScriptFunction, word>         CObScriptFuncOpcodeMap;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScriptFunctions Definition
 *
 * Description
 *
 *=========================================================================*/
class CObScriptFunctions {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObScriptFuncArray	 m_Functions;

  CObScriptFuncNameMap	 m_FunctionNameMap;
  CObScriptFuncNameMap	 m_ConsoleNameMap;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

  void IndexFunction (CObScriptFunction* pFunction);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScriptFunctions();
  virtual ~CObScriptFunctions() { Destroy(); }
  virtual void Destroy (void);

	/* Access functions */
  CObScriptFunction* GetFunction        (const char* pString);
  CObScriptFunction* GetConsoleFunction (const char* pString);

	/* Get class members */
  CObScriptFuncArray& GetFunctions    (void) { return (m_Functions); }
  dword               GetNumFunctions (void) { return (m_Functions.GetSize()); }
  dword               GetSize         (void) { return (m_Functions.GetSize()); }
  CObScriptFunction*  GetFunction     (const dword Index) { return (m_Functions.GetAt(Index)); }

	/* Load function definitions from a text file */
  bool Load (const char* pFilename, const dword CustomFlags = 0);


};
/*===========================================================================
 *		End of Class CObScriptFunctions Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obscriptfunctions.H
 *=========================================================================*/
