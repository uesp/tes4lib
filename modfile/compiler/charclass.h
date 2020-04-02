/*===========================================================================
 *
 * File:	Charclass.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 18, 2006
 *
 * Defines the CCharClass class which defines a custom character class
 * used for matching token and other symbols in a text stream.
 *
 *=========================================================================*/
#ifndef __CHARCLASS_H
#define __CHARCLASS_H



/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../../common/sstring.h"
  #include "../../common/obfile.h"
  #include "../../common/oblogfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Size of matching table to match character size */
  #define CHARCLASS_TABLESIZE 256

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CCharClass Definition
 *
 * Description
 *
 *=========================================================================*/
class CCharClass {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  bool		m_CharTable[CHARCLASS_TABLESIZE];
  CSString	m_Name;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper input methods */
  bool ParseRange (const byte* pStartRange, const byte* pEndRange, const bool SetValue);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CCharClass();
  ~CCharClass() { Destroy(); }
  void Destroy (void);

	/* Does a byte pr character value match this class? */
  bool DoesMatch (const byte Value) { return m_CharTable[Value]; }
  bool DoesMatch (const char Value) { return m_CharTable[(byte)Value]; }

  	/* Compare the token type name */
  bool IsName (const char* pString) { return m_Name.CompareNoCase(pString) == 0; }

	/* Set a class definition from a string */
  bool SetDefinition (const char* pString);

	/* Set class members */
  void SetName (const char* pString) { m_Name = pString; }

};
/*===========================================================================
 *		End of Class CCharClass Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Charclass.H
 *=========================================================================*/
