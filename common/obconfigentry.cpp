/*===========================================================================
 *
 * File:	Obconfigentry.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 28, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obconfigentry.h"
#include "ctype.h"
#include "oblogfile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/

	/* Used when no explicit options are given */
  obcfgoptions_t g_DefaultCfgOptions;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Constructor
 *
 *=========================================================================*/
CObConfigEntry::CObConfigEntry() : m_Options(g_DefaultCfgOptions) {
  
}
/*===========================================================================
 *		End of Class CObConfigEntry Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Constructor
 *
 *=========================================================================*/
CObConfigEntry::CObConfigEntry(obcfgoptions_t& Options) : m_Options(Options) {
  
}
/*===========================================================================
 *		End of Class CObConfigEntry Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void Destroy (void);
 *
 *=========================================================================*/
void CObConfigEntry::Destroy (void) {
  m_Line.Destroy();
  m_Variable.Destroy();
  m_Value.Destroy();
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - bool ParseLine (pString);
 *
 * Parse the given input line into variable/values returning true on success.
 * Expects an input string of the format:
 *
 *	Variable = Value    # Comment
 *
 * Whitespace is ignored for the variable and value parts.
 *
 *=========================================================================*/
bool CObConfigEntry::ParseLine (const char* pString) {
  CSString Variable;
  CSString Value;

  Destroy();

  m_Line = pString;
  if (m_Line.IsEmpty()) return (true);

  m_Line.SeperateVarValueNQ(m_Variable, m_Value, m_Options.SeperatorChar, m_Options.CommentChar);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::ParseLine()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void Set (pVar, pVal);
 *
 *=========================================================================*/
void CObConfigEntry::Set (const char* pVar, const char* pVal) {
  m_Variable = pVar;
  m_Value    = pVal;

  UpdateLine();
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::Set()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void SetNew (pVar, pVal);
 *
 *=========================================================================*/
void CObConfigEntry::SetNew (const char* pVar, const char* pVal) {

  m_Variable = pVar;
  m_Value    = pVal;

  m_Line.Format("%s %c %s", m_Variable, m_Options.SeperatorChar, m_Value);
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::SetNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void SetNewFormat (pVar, pVal, ...);
 *
 *=========================================================================*/
void CObConfigEntry::SetNewFormat (const char* pVar, const char* pVal, ...) {
  va_list Args;
 
  va_start(Args, pVal);
  SetNewFormatV(pVar, pVal, Args);
  va_end(Args);
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::SetNewFormat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void SetNewFormatV (pVar, pVal, Args);
 *
 *=========================================================================*/
void CObConfigEntry::SetNewFormatV (const char* pVar, const char* pVal, va_list Args) {
  m_Variable = pVar;
  m_Value.FormatV(pVal, Args);
  m_Line.Format("%s %c %s", m_Variable.c_str(), m_Options.SeperatorChar, m_Value.c_str());
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::SetNewFormatV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void SetValueFormat (pString, ...);
 *
 * Extended method to set the value to the given printf() formated string.
 *
 *=========================================================================*/
void CObConfigEntry::SetValueFormat (const char* pString, ...) {
  va_list Args;

  va_start(Args, pString);
  SetValueFormatV(pString, Args);
  va_end(Args);
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::SetValueFormat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void SetValueFormatV (pString, Args);
 *
 * Extended method to set the value to the given vprintf() formated string.
 *
 *=========================================================================*/
void CObConfigEntry::SetValueFormatV (const char* pString, va_list Args) {
  char    Buffer[256];

  _vsnprintf(Buffer, 250, pString, Args);
  m_Value = Buffer;

  UpdateLine();
}
/*===========================================================================
 *		End of Class Method FormatValueV::SetValueFormatV()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigEntry Method - void UpdateLine (void);
 *
 * Updates the overall line string buffer with the current variable/value
 * strings.
 *
 *=========================================================================*/
void CObConfigEntry::UpdateLine (void) {
  const char*	pParse;
  CSString	m_NewLine;
  CSString	m_Space;
  bool		Found;
    
	/* Parse the current line string  */
  pParse     = m_Line;
  Found      = false;
  
  //m_NewLine.SetSize(m_Line.GetLength() + 8);
  //m_Space.SetSize(64);
  
	/* Parse the variable */
  while (*pParse != NULL_CHAR) {
    if (*pParse == m_Options.CommentChar) break;
    if (*pParse == m_Options.SeperatorChar) break;

    if (Found) {
      if (isspace(*pParse)) break;
    }
    else if (!isspace(*pParse)) {
      Found = true;
      m_NewLine += m_Variable;
    }
    else {
      m_NewLine += *pParse;
    }

    pParse++;
  }

  if (!Found) m_NewLine += m_Variable;

	/* Parse up to the = */
  while (*pParse != NULL_CHAR) {
    if (*pParse == m_Options.CommentChar) break;
    if (*pParse == m_Options.SeperatorChar) break;

    m_NewLine += *pParse;
    pParse++;
  }

  if (*pParse != m_Options.SeperatorChar) {
    if (!m_Value.IsEmpty()) m_NewLine += m_Options.SeperatorChar;
  }
  else {
    m_NewLine += *pParse;
    ++pParse;
  }

	/* Parse the value */
  Found = false;

  while (*pParse != NULL_CHAR) {
    if (*pParse == m_Options.CommentChar) break;
    
    if (Found) {
      if (isspace(*pParse)) 
        m_Space += *pParse;
      else
        m_Space.Empty();
    }
    else if (!isspace(*pParse)) {
      Found = true;
      m_NewLine += m_Space;
      m_NewLine += m_Value;
      m_Space.Empty();
    }
    else {
      m_Space += *pParse;
    }
    
    pParse++;
  }
  
  if (!Found) m_NewLine += m_Value;
  m_NewLine += m_Space;

	/* Output the remaining string */
  m_NewLine += pParse;

  //SystemLog.Printf("Var/Value: '%s' = '%s'", m_Variable, m_Value);
  //SystemLog.Printf("\tOld line:%s", m_Line);
  //SystemLog.Printf("\tNew line:%s", m_NewLine);

  m_Line = m_NewLine;
}
/*===========================================================================
 *		End of Class Method CObConfigEntry::UpdateLine()
 *=========================================================================*/


