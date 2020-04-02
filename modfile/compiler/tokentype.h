/*===========================================================================
 *
 * File:	Tokentype.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Defines the CTokenType class for handling a single token definition.
 *
 *=========================================================================*/
#ifndef __TOKENTYPE_H
#define __TOKENTYPE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/oberrorhandler.h"
  #include "../../common/sstring.h"
  #include "../../common/oblogfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Predefined token IDs */
  #define TOKEN_ID_UNKNOWN	0

	/* Token flags */
  #define TOKEN_FLAG_KEEP	1
  #define TOKEN_FLAG_SIMPLE	2
  #define TOKEN_FLAG_IGNORE	4
  #define TOKEN_FLAG_TRIMFIRST	8
  #define TOKEN_FLAG_TRIMLAST	16
  #define TOKEN_FLAG_ENDTOKEN	32

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenType Definition
 *
 *=========================================================================*/
class CTokenType {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  int		m_ID;		/* Unique ID for this token */
  CSString	m_Name;		/* Token name */
  dword		m_Flags;	/* Token flags */

  dword     m_ForeColor;	/* Used for script syntax highlighting */
  dword     m_BackColor;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenType();
  ~CTokenType() { Destroy(); }
  void Destroy (void);

	/* Get class members */
  const char* GetName      (void) { return (m_Name); }
  int         GetID        (void) { return (m_ID); }
  dword       GetForeColor (void) { return (m_ForeColor); }
  dword       GetBackColor (void) { return (m_BackColor); }
  dword&      GetForeColorRef (void) { return (m_ForeColor); }
  dword&      GetBackColorRef (void) { return (m_BackColor); }
  bool        IsSingleType (void) { return (m_Flags & TOKEN_FLAG_SIMPLE) != 0; }
  bool        IsKeepType   (void) { return (m_Flags & TOKEN_FLAG_KEEP) != 0; }
  bool        IsIgnoreType (void) { return (m_Flags & TOKEN_FLAG_IGNORE) != 0; }
  bool	      IsTrimFirst  (void) { return (m_Flags & TOKEN_FLAG_TRIMFIRST) != 0; }
  bool	      IsTrimLast   (void) { return (m_Flags & TOKEN_FLAG_TRIMLAST) != 0; }
  bool	      IsEndToken   (void) { return (m_Flags & TOKEN_FLAG_ENDTOKEN) != 0; }

	/* Compare the token type name */
  bool IsName (const char* pString) { return m_Name.CompareNoCase(pString) == 0; }

  	/* Set a token definition from a string */
  bool SetDefinition (const char* pString);

	/* Set class members */
  void SetName      (const char* pString) { m_Name = pString; }
  void SetForeColor (const dword Color)   { m_ForeColor = Color; }
  void SetBackColor (const dword Color)   { m_BackColor = Color; }

};
/*===========================================================================
 *		End of Class CTokenType Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Tokentype.H
 *=========================================================================*/
