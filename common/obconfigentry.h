/*===========================================================================
 *
 * File:	Obconfigentry.H
 * Author:	Dave Humphrey (uesp@symaptico.ca)
 * Created On:	September 28, 2006
 *
 * Defines the CObConfigEntry class, a single entry value in a config file.
 *
 *=========================================================================*/
#ifndef __OBCONFIGENTRY_H
#define __OBCONFIGENTRY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberrorhandler.h"
  #include "obfile.h"
  #include "sstring.h"
  #include "obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Options for a config file */
  struct obcfgoptions_t {
  	char	SeperatorChar;
	char	CommentChar;
	bool	ParseQuotes;

		/* Default options */
	obcfgoptions_t() {
		SeperatorChar = '=';
		CommentChar   = ';';
		ParseQuotes   = false;
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObConfigEntry Definition
 *
 *=========================================================================*/
class CObConfigEntry {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString		m_Line;		/* Entire line of entry */

  CSString		m_Variable;	/* Parsed variable string */
  CSString		m_Value;	/* Parsed value string */

  obcfgoptions_t&	m_Options;	/* Options of the parent file */


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Updates the line text with the current variable/value strings */
  void UpdateLine (void);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObConfigEntry();
  CObConfigEntry(obcfgoptions_t& Options);
  virtual ~CObConfigEntry() { Destroy(); }
  virtual void Destroy (void);

	/* Get class members */
  const char* GetLine     (void) { return (m_Line); }
  const char* GetVariable (void) { return (m_Variable); }
  const char* GetValue    (void) { return (m_Value); }
  bool        IsEmpty     (void) { return (m_Line.IsEmpty()); }

	/* Check for a matching variable value */
  bool IsVariable (const char* pString) { return m_Variable.CompareNoCase(pString) == 0; }

	/* Parse an input string */
  bool ParseLine (const char* pString);

	/* Set class members */
  void Set             (const char* pVar, const char* pVal);
  void SetNew          (const char* pVar, const char* pVal);
  void SetNewFormat    (const char* pVar, const char* pVal, ...);
  void SetNewFormatV   (const char* pVar, const char* pVal, va_list Args);

  void SetLine         (const char* pString) { m_Line     = pString; }
  void SetValue        (const char* pString) { m_Value    = pString; UpdateLine(); }
  void SetVariable     (const char* pString) { m_Variable = pString; UpdateLine(); }
  void SetValueFormat  (const char* pString, ...);
  void SetValueFormatV (const char* pString, va_list Args);

};

	/* Array of entry pointers */
  typedef CObPtrArray<CObConfigEntry> CObConfigEntryArray;

/*===========================================================================
 *		End of Class CObConfigEntry Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obconfigentry.H
 *=========================================================================*/
