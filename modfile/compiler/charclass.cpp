/*===========================================================================
 *
 * File:	Charclass.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 18, 2006
 *
 * Implements the CCharClass class.
 *
 *=========================================================================*/

	/* Include Files */
#include "charclass.h"


/*===========================================================================
 *
 * Class CCharClass Constructor
 *
 *=========================================================================*/
CCharClass::CCharClass () {
  memset(&m_CharTable, 0, CHARCLASS_TABLESIZE);
}
/*===========================================================================
 *		End of Class CCharClass Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClass Method - void Destroy (void);
 *
 *=========================================================================*/
void CCharClass::Destroy (void) {
  memset(&m_CharTable, 0, CHARCLASS_TABLESIZE);
}
/*===========================================================================
 *		End of Class Method CCharClass::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClass Method - bool ParseRange (pStartRange, pEndRange, SetValue);
 *
 * Protected class method that parses an input character class range.
 *
 *=========================================================================*/
bool CCharClass::ParseRange (const byte* pStartRange, const byte* pEndRange, const bool SetValue) {
  dword Index;

  if (pStartRange == NULL || pEndRange == NULL) {
    AddObGeneralError("Invalid NULL character range received!");
    return (false);
  }

  if (pEndRange[1] != NULL_CHAR) {
    AddObGeneralError("Unknown end range character '%s'!", pEndRange);
    return (false);
  }

  if (*pStartRange > *pEndRange) {
    AddObGeneralError("Start character range is larger than the end (%c..%c)!", *pStartRange, *pEndRange);
    return (false);
  }

  if (*pEndRange >= CHARCLASS_TABLESIZE) {
    AddObGeneralError("End character range is too large!");
    return (false);
  }

  for (Index = *pStartRange; Index <= *pEndRange; ++Index) {
    m_CharTable[(byte)Index] = SetValue;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CCharClass::ParseRange()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClass Method - bool SetDefinition (pString)
 *
 * Set a class definition from the given string. Returns false on any
 * error.
 *
 * The expected string format is:
 *	pString = [Class1] [Class2] ... [ClassN]
 *		Multiple classes seperated by spaces
 *	[Class] := [Range]
 *	[Class] := [SingleChar]
 *	[Class] := [SlashCode]
 *	[Class] := ![Class]
 *		Remove the given character class from the matching set	
 *	[Class] := any
 *	[Class] := space
 *	[Class] := null
 *	[Range] := [StartChar]..[EndChar]
 *		All characters in that range, start/end inclusive
 *	[SlashCode] := \n \t \r \!
 *		Special characters
 *
 * Examples:
 *	Digit:		0..9
 *	Alpha:		a..z A..Z
 *	Whitespace:	\t \n \r space
 *	StartID:	a..z A..Z _
 *	ContinueID:	a..z A..Z _ 0..9
 *	StartString:	"
 *	EndString:	Any !" !\n
 *
 *=========================================================================*/
bool CCharClass::SetDefinition (const char* pString) {
  char*  pNewString;
  char*  pParse;
  char*  pLastParse;
  int    Length;
  bool   NotClass;
  dword  Index;
  
	/* Ignore invalid input */
  if (pString  == NULL) return (true);
  if (*pString ==    0) return (true);

  Length     = (int) strlen(pString);
  if (Length < 0) return (false);
  pNewString = new char[Length + 4];
  strcpy((char *) pNewString, pString);

  pParse      = strtok(pNewString, " ");
  pLastParse  = NULL;

  while (pParse != NULL) {
    NotClass = false;

    if (*pParse == '!') {
      ++pParse;
      NotClass = true;
    }

    if (*pParse == '\\') {
      ++pParse;
      
      switch (*pParse) {
        case 'n':  *pParse = '\n'; break; 
	case 't':  *pParse = '\t'; break;
	case 'r':  *pParse = '\r'; break;
      };
    }
    
    if (stricmp(pParse, "any") == 0) {
      for (Index = 0; Index < CHARCLASS_TABLESIZE; ++Index) {
        m_CharTable[Index] = !NotClass;
      }
    }
    else if (stricmp(pParse, "space") == 0) {
      m_CharTable[' '] = !NotClass;
    }
    else if (stricmp(pParse, "null") == 0) {
      m_CharTable[0] = !NotClass;
    }
    else if (pParse[1] == '.' && pParse[2] == '.') {
      ParseRange((byte *) pParse, (byte *) pParse + 3, !NotClass);
      pParse = NULL;
    }
    else if (pParse[1] == NULL_CHAR) {
      m_CharTable[*pParse] = !NotClass;
    }
    else {
      AddObGeneralError("Unknown character class '%s' found!", pParse);
    }

    pLastParse = pParse;
    pParse     = strtok(NULL, " ");
  }

  delete[] pNewString;
  return (true);
}
/*===========================================================================
 *		End of Class Method CCharClass::SetDefinition()
 *=========================================================================*/
