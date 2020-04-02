/*===========================================================================
 *
 * File:	Obscriptfunction.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 17, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSCRIPTFUNCTION_H
#define __OBSCRIPTFUNCTION_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/obfile.h"
  #include "../../common/oblogfile.h"
  #include "../../common/obptrarray.h"
  #include "../obfields.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Custom function flag definitions */
  #define OB_FUNCFLAG_USESREF		1
  #define OB_FUNCFLAG_NOSCRIPT		2	/* Don't use in regular scripts */

	/* Custom function parameter flags */
  #define OB_FUNCPARAMFLAG_OPTIONAL	1

	/* Maximum parameters (arbitrary) */
  #define OB_FUNCTION_MAXPARAMS		8

	/* Limit for various function types */
  #define OB_FUNCTION_MAX_CONSOLE_OPCODE	0x0fff
  #define OB_FUNCTION_MAX_BEGIN_OPCODE		0x001F

	/* Special function opcodes */
  #define OB_FUNCOPCODE_GETSCRIPTVARIABLE 0x1035
  #define OB_FUNCOPCODE_GETQUESTVARIABLE  0x104F
  #define OB_FUNCOPCODE_MESSAGE           0x1059
  #define OB_FUNCOPCODE_MESSAGEBOX        0x1000
  #define OB_FUNCOPCODE_STOPCOMBAT        0x1017
  #define OB_FUNCOPCODE_GETGAMESETTING	  0x1100

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Function parameter information */
  struct obscriptfuncparam_t {
	short Type;		/* Same as Oblivion type */
	short Flags;		/* Custom flags */

	bool IsOptional (void) { return ((Flags & OB_FUNCPARAMFLAG_OPTIONAL) != 0); }
  };

  typedef CObRefPtrArray<obscriptfuncparam_t> CObRefFuncParamArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScriptFunction Definition
 *
 * Holds information on a single script function.
 *
 *=========================================================================*/
class CObScriptFunction {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString		m_Name;
  CSString		m_ShortName;
  CSString		m_HelpText;
  int			m_Index;
  word			m_OpCode;
  dword			m_Flags;
  dword			m_CustomFlags;

  obscriptfuncparam_t	m_Parameters[OB_FUNCTION_MAXPARAMS];
  word			m_NumParameters;			


  /*---------- Begin Protected Class Methods --------------------*/
protected:

  bool ParseParameter (CSString& Buffer);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScriptFunction();
  virtual ~CObScriptFunction() { Destroy(); }
  virtual void Destroy (void);

	/* Access parameters */
  obscriptfuncparam_t* GetParameter (const dword Index) { return ((Index < m_NumParameters) ? &m_Parameters[Index] : NULL); }

	/* Get class members */
  const char* GetName           (void) { return (m_Name); }
  const char* GetFullName       (void) { return (m_Name); }
  const char* GetShortName      (void) { return (m_ShortName); }
  const char* GetHelpText       (void) { return (m_HelpText); }
  bool        HasShortName      (void) { return (!m_ShortName.IsEmpty()); }
  int	      GetIndex          (void) { return (m_Index); }
  word	      GetOpCode         (void) { return (m_OpCode); }
  dword       GetFlags          (void) { return (m_Flags); }
  dword       GetCustomFlags    (void) { return (m_CustomFlags); }
  bool        IsUsesReference   (void) { return (m_CustomFlags & OB_FUNCFLAG_USESREF)  != 0; }
  bool        IsNoScript        (void) { return (m_CustomFlags & OB_FUNCFLAG_NOSCRIPT) != 0; }
  dword       GetNumParameters  (void) { return (m_NumParameters); }
  bool	      IsConsoleFunction (void) { return (m_OpCode <= OB_FUNCTION_MAX_CONSOLE_OPCODE); }
  bool	      IsBeginFunction   (void) { return (m_OpCode <= OB_FUNCTION_MAX_BEGIN_OPCODE); }

	/* Input function data from a file */
  bool Read (CObFile& File);

	/* Set class members */
  void SetCustomFlags (const dword Flags) { m_CustomFlags = Flags; }

};

	/* Arrays of functions */
  typedef CObPtrArray<CObScriptFunction>     CObScriptFuncArray;
  typedef CObRefPtrArray<CObScriptFunction>  CObRefScriptFuncArray;

/*===========================================================================
 *		End of Class CObScriptFunction Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obscriptfunction.H
 *=========================================================================*/
