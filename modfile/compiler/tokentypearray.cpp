/*===========================================================================
 *
 * File:	TokenTypeArray.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentypearray.h"


/*===========================================================================
 *
 * Class CTokenTypeArray Constructor
 *
 *=========================================================================*/
CTokenTypeArray::CTokenTypeArray () {

}
/*===========================================================================
 *		End of Class CTokenTypeArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenTypeArray::Destroy (void) {
  m_Records.Destroy();
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - int FindTokenID (pName);
 *
 *=========================================================================*/
int CTokenTypeArray::FindTokenID (const char* pName) {
  CTokenType* pTokenType;
  
  pTokenType = GetTokenType(pName);
  if (pTokenType != NULL) return pTokenType->GetID();
  return (TOKEN_ID_UNKNOWN);
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::FindTokenID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - CTokenType* GetEndToken (void);
 *
 *=========================================================================*/
CTokenType* CTokenTypeArray::GetEndToken (void) {
  CTokenType*	pTokenType;
  dword		Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pTokenType = m_Records.GetAt(Index);
    if (pTokenType->IsEndToken()) return (pTokenType);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::GetEndToken()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - CTokenType* GetTokenType (ID);
 *
 *=========================================================================*/
CTokenType* CTokenTypeArray::GetTokenType (const int ID) {
  CTokenType*	pTokenType;
  dword		Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pTokenType = m_Records.GetAt(Index);
    if (pTokenType->GetID() == ID) return (pTokenType);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::GetTokenType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - CTokenType* GetTokenType (pName);
 *
 *=========================================================================*/
CTokenType* CTokenTypeArray::GetTokenType (const char* pName) {
  CTokenType*	pTokenType;
  dword		Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pTokenType = m_Records.GetAt(Index);
    if (pTokenType->IsName(pName)) return (pTokenType);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::GetTokenType()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTypeArray Method - bool Load (File);
 *
 *=========================================================================*/
bool CTokenTypeArray::Load (CObFile& File) {
  CTokenType* pTokenType;
  CSString    LineBuffer;
  CSString    Variable;
  CSString    Value;
  bool        Result;

	/* Read and parse entire file */
  while (!File.IsEOF()) {
    Result = File.ReadLine(LineBuffer);
    if (!Result) return (false);

    Result = LineBuffer.SeperateVarValueNQ(Variable, Value, '=', 0);

		/* Add a new class if required */
    if (Result) {
      pTokenType = new CTokenType;
      m_Records.Add(pTokenType);

      pTokenType->SetName(Variable);
      Result = pTokenType->SetDefinition(Value);
    }
    else if (Variable.CompareNoCase("end") == 0) {
      break;
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CTokenTypeArray::Load()
 *=========================================================================*/
