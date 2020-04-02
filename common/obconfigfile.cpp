/*===========================================================================
 *
 * File:	Obconfigfile.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 28, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obconfigfile.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Constructor
 *
 *=========================================================================*/
CObConfigFile::CObConfigFile() {

}
/*===========================================================================
 *		End of Class CObConfigFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CObConfigFile::Destroy (void) {
  m_Records.Destroy();
}
/*===========================================================================
 *		End of Class Method CObConfigFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool Delete (pVariable);
 *
 * Attempts to delete the given config entry. Returns true on success or
 * false if it was not found.
 *
 *=========================================================================*/
bool CObConfigFile::Delete (const char* pVariable) {
  CObConfigEntry* pEntry;

  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (false);

  m_Records.Delete(pEntry);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - CObConfigEntry* FindEntry (pVariable);
 *
 * Find and return the first config entry with the matching variable name.
 * Returns NULL if not found.
 *
 *=========================================================================*/
CObConfigEntry* CObConfigFile::FindEntry (const char* pVariable) {
  CObConfigEntry* pEntry;
  dword		  Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pEntry = m_Records.GetAt(Index);
    if (pEntry->IsVariable(pVariable)) return (pEntry);
  }  

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::FindEntry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObConfigFile Method - const Get (pVariable);
 *
 * Returns the value of the given config entry or NULL if not found.
 *
 *=========================================================================*/
const char* CObConfigFile::Get (const char* pVariable) {
  CObConfigEntry* pEntry;

  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (NULL);

  return pEntry->GetValue();
}
/*===========================================================================
 *		End of Class Method char* CObConfigFile::Get()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObConfigFile Method - const Get (pVariable, pDefault);
 *
 * Returns the value of the given config entry or the default value
 * if not found.
 *
 *=========================================================================*/
const char* CObConfigFile::Get (const char* pVariable, const char* pDefault) {
  CObConfigEntry* pEntry;

  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (pDefault);

  return pEntry->GetValue();
}
/*===========================================================================
 *		End of Class Method char* CObConfigFile::Get()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool GetInteger (Value, pVariable, Default);
 *
 *=========================================================================*/
bool CObConfigFile::GetInteger (int& Value, const char* pVariable, const int Default) {
  CObConfigEntry* pEntry;
  char*		  pError;

  Value  = Default;
  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (false);

  Value = strtol(pEntry->GetValue(), &pError, 0);

  if (*pError != NULL_CHAR) return (false);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::GetInteger()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool GetDword (Value, pVariable, Default);
 *
 *=========================================================================*/
bool CObConfigFile::GetDword (dword& Value, const char* pVariable, const dword Default) {
  CObConfigEntry* pEntry;
  char*		  pError;

  Value  = Default;
  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (false);

  Value = strtoul(pEntry->GetValue(), &pError, 0);

  if (*pError != NULL_CHAR) return (false);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::GetDword()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool GetFloat (Value, pVariable, Default);
 *
 *=========================================================================*/
bool CObConfigFile::GetFloat (float& Value, const char* pVariable, const float Default) {
  CObConfigEntry* pEntry;
  char*		  pError;

  Value  = Default;
  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (false);

  Value = (float) strtod(pEntry->GetValue(), &pError);

  if (*pError != NULL_CHAR) return (false);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::GetFloat()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool GetBoolean (Value, pVariable, Default);
 *
 *=========================================================================*/
bool CObConfigFile::GetBoolean (bool& Value, const char* pVariable, const bool Default) {
  CObConfigEntry* pEntry;
  char*		  pError;

  Value  = Default;
  pEntry = FindEntry(pVariable);
  if (pEntry == NULL) return (false);

  if (stricmp(pEntry->GetValue(), "true") == 0)
    Value = true;
  else if (stricmp(pEntry->GetValue(), "false") == 0)
    Value = false;
  else if (stricmp(pEntry->GetValue(), "yes") == 0)
    Value = true;
  else if (stricmp(pEntry->GetValue(), "no") == 0)
    Value = false;
  else {
    Value = (strtol(pEntry->GetValue(), &pError, 0) != 0);
    if (*pError != NULL_CHAR) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::GetBoolean()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool GetString (Value, pVariable, Default);
 *
 *=========================================================================*/
bool CObConfigFile::GetString (CSString& Value, const char* pVariable, const char* Default) {
  CObConfigEntry* pEntry;

  pEntry = FindEntry(pVariable);

  if (pEntry == NULL) {
    Value = Default;
    return (false);
  }

  Value = pEntry->GetValue();;
  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::GetString()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool Load (pFilename);
 *
 *=========================================================================*/
bool CObConfigFile::Load (const char* pFilename) {
  CObFile         File;
  CObConfigEntry* pEntry = NULL;
  CSString        Buffer;
  bool            Result;

	/* Clear the current contents */
  Destroy();

	/* Attempt to open file for input */
  Result = File.Open(pFilename, "rt");
  if (!Result) return (false);

	/* Read entire line line by line */
  while (!File.IsEOF()) {
    Result = File.ReadLine(Buffer);
    if (!Result) return (false);

    pEntry = new CObConfigEntry(m_Options);
    m_Records.Add(pEntry);

    pEntry->ParseLine(Buffer);
  }

	/* Remove the last entry if it is empty */
  if (pEntry != NULL && pEntry->IsEmpty()) {
    m_Records.Delete(pEntry);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::Load()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - bool Save (pFilename);
 *
 *=========================================================================*/
bool CObConfigFile::Save (const char* pFilename) {
  CObFile  File;
  dword    Index;
  bool     Result;

  Result = File.Open(pFilename, "wt");
  if (!Result) return (false);

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    Result = File.Printf("%s\n", m_Records.GetAt(Index)->GetLine());
    if (!Result) return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::Save()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - void SetValue (pVariable, pValue);
 *
 * Sets the value of the given config entry. Creates the entry if it 
 * doesn't already exist.
 *
 *=========================================================================*/
void CObConfigFile::SetValue (const char* pVariable, const char* pValue) {
  CObConfigEntry* pEntry;
 
  pEntry = FindEntry(pVariable);

  if (pEntry == NULL) { 
    pEntry = new CObConfigEntry(m_Options);
    m_Records.Add(pEntry);
    pEntry->SetNew(pVariable, pValue);
  }
  else {
    pEntry->Set(pVariable, pValue);
  }

}
/*===========================================================================
 *		End of Class Method CObConfigFile::SetValue()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObConfigFile Method - void SetValueFormat (pVariable, pValue, ...);
 *
 * Sets the value of the given config entry in with a printf() formatted
 * string. Creates the entry if it doesn't already exist.
 *
 *=========================================================================*/
void CObConfigFile::SetValueFormat (const char* pVariable, const char* pValue, ...) {
  CObConfigEntry* pEntry;
  va_list	  Args;

  pEntry = FindEntry(pVariable);
  va_start(Args, pValue);

  if (pEntry == NULL) { 
    pEntry = new CObConfigEntry(m_Options);
    m_Records.Add(pEntry);

    pEntry->SetNewFormatV(pVariable, pValue, Args);
  }
  else {
    pEntry->SetVariable(pVariable);
    pEntry->SetValueFormatV(pValue, Args);
  }
  
  va_end(Args);
}
/*===========================================================================
 *		End of Class Method CObConfigFile::SetValueFormat()
 *=========================================================================*/

