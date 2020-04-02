/*===========================================================================
 *
 * File:	Obconfigfile.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 28, 2006
 *
 * Defines the CObConfigFile class for handling general text config files.
 *
 *=========================================================================*/
#ifndef __OBCONFIGFILE_H
#define __OBCONFIGFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obconfigentry.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObConfigFile Definition
 *
 * Used to managed the contents of a general config text file.
 *
 *=========================================================================*/
class CObConfigFile {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObConfigEntryArray	m_Records;	/* Config file content by line */

  obcfgoptions_t	m_Options;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObConfigFile();
  virtual ~CObConfigFile() { Destroy(); }
  virtual void Destroy (void);

	/* Delete an entry */
  bool Delete (const char* pVariable);

	/* Get class members */
  obcfgoptions_t& GetOptions (void) { return (m_Options); }

	/* Gets values */
  const char* Get      (const char* pVariable);
  const char* Get      (const char* pVariable, const char* pDefault);
  bool        HasEntry (const char* pVariable) { return FindEntry(pVariable) != NULL; }

	/* Get typed values */
  bool GetInteger (int&      Value, const char* pVariable, const int   Default = 0);
  bool GetDword   (dword&    Value, const char* pVariable, const dword Default = 0);
  bool GetFloat   (float&    Value, const char* pVariable, const float Default = 0);
  bool GetBoolean (bool&     Value, const char* pVariable, const bool  Default = false);
  bool GetString  (CSString& Value, const char* pVariable, const char* Default = "");

	/* Find a matching entry */
  CObConfigEntry* FindEntry (const char* pVariable);

	/* Load/save a config file */
  bool Load (const char* pFilename);
  bool Save (const char* pFilename);

	/* Sets the value of the given variable */
  void SetValue       (const char* pVariable, const char* pValue);
  void SetValueFormat (const char* pVariable, const char* pValue, ...);

	/* Set typed values */
  void SetValueInteger (const char* pVariable, const int   Value) { SetValueFormat(pVariable, "%d", Value); }
  void SetValueDword   (const char* pVariable, const dword Value) { SetValueFormat(pVariable, "%u", Value); }
  void SetValueFloat   (const char* pVariable, const float Value) { SetValueFormat(pVariable, "%f", Value); }
  void SetValueBoolean (const char* pVariable, const bool  Value) { SetValueFormat(pVariable, "%s", BooleanToString(Value)); }

	/* Read or write values */
  bool UpdateInteger (const bool Set, const char* pVariable, int&      Value) { if (Set) { SetValueInteger(pVariable, Value); return (true); } return GetInteger(Value, pVariable, Value); }
  bool UpdateDword   (const bool Set, const char* pVariable, dword&    Value) { if (Set) { SetValueDword  (pVariable, Value); return (true); } return GetDword  (Value, pVariable, Value); }
  bool UpdateFloat   (const bool Set, const char* pVariable, float&    Value) { if (Set) { SetValueFloat  (pVariable, Value); return (true); } return GetFloat  (Value, pVariable, Value); }
  bool UpdateBoolean (const bool Set, const char* pVariable, bool&     Value) { if (Set) { SetValueBoolean(pVariable, Value); return (true); } return GetBoolean(Value, pVariable, Value); }
  bool UpdateString  (const bool Set, const char* pVariable, CSString& Value) { if (Set) { SetValue       (pVariable, Value); return (true); } return GetString (Value, pVariable, Value); }

  bool UpdateDword   (const bool Set, const char* pVariable, unsigned long& Value) { if (Set) { SetValueDword(pVariable, *(dword *)&Value); return (true); } return GetDword(*(dword *)&Value, pVariable, Value); }

};
/*===========================================================================
 *		End of Class CObConfigFile Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obconfigfile.H
 *=========================================================================*/
