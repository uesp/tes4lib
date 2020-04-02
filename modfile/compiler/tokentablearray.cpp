/*===========================================================================
 *
 * File:	Tokentablearray.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentablearray.h"


/*===========================================================================
 *
 * Class CTokenTableArray Constructor
 *
 *=========================================================================*/
CTokenTableArray::CTokenTableArray() {
  m_pMainTable = NULL;
}
/*===========================================================================
 *		End of Class CTokenTableArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenTableArray::Destroy (void) {
  m_pMainTable = NULL;

  m_Tables.Destroy();
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - CTokenTable* GetTable (pName);
 *
 *=========================================================================*/
CTokenTable* CTokenTableArray::GetTable (const char* pName) {
  CTokenTable*	pTable;
  dword		Index;

  for (Index = 0; Index < m_Tables.GetSize(); ++Index) {
    pTable = m_Tables.GetAt(Index);
    if (pTable->IsName(pName)) return (pTable);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::GetTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - bool LoadNewTable (File, pTableName);
 *
 *=========================================================================*/
bool CTokenTableArray::LoadNewTable (CObFile& File, const char* pTableName) {
  CTokenTable* pTable;

  pTable = new CTokenTable;
  m_Tables.Add(pTable);

  if (pTableName == NULL) {
    m_pMainTable = pTable;
  }
  else {
    pTable->SetName(pTableName);
  }

  return pTable->Load(File);
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::LoadNewTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - bool ResolveRowReferences (pRow, pTable, TokenArray, CharArray);
 *
 *=========================================================================*/
bool CTokenTableArray::ResolveRowReferences (CTokenTableRow* pRow, CTokenTable* pTable, CTokenTypeArray& TokenArray, CCharClassArray& CharArray) {
  CTokenTable*	  pFindTable;
  CCharClass*	  pCharClass;
  CTokenType*	  pTokenType;
  bool		  Result = true;

	/* Resolve the character class of the row if needed */
  if (pRow->GetMatchType() == TOKEN_MATCHTYPE_CHARCLASS) {
    pCharClass = CharArray.GetCharClass(pRow->GetCharClassName());
    pRow->SetCharClass(pCharClass);

    if (pCharClass == NULL) {
      AddObGeneralError("Unknown character class '%s' used in table %s!", pRow->GetCharClassName(), pTable->GetName());
      Result = false;
    }
  }

	/* Resolve the token type of the row result if required */
  if (pRow->GetResult().GetAction() == TOKEN_RESULT_RETURN ||
      pRow->GetResult().GetAction() == TOKEN_RESULT_JMPRETURN) {
    pTokenType = TokenArray.GetTokenType(pRow->GetResult().GetTokenName());
    pRow->GetResult().SetTokenType(pTokenType);

    if (pTokenType == NULL) {
      AddObGeneralError("Unknown token type '%s' used in table %s!", pRow->GetResult().GetTokenName(), pTable->GetName());
      Result = false;
    }	
  }  
	/* Resolve the table of the row result if required */
  else if (pRow->GetResult().GetAction() == TOKEN_RESULT_MOVETO ||
	   pRow->GetResult().GetAction() == TOKEN_RESULT_JUMPTO ) {
    pFindTable = GetTable(pRow->GetResult().GetTableName());
    pRow->GetResult().SetTable(pFindTable);

    if (pFindTable == NULL) {
      AddObGeneralError("Unknown table '%s' used in table %s!", pRow->GetResult().GetTableName(), pTable->GetName());
      Result = false;
    }
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::ResolveRowReferences()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - bool ResolveTableReferences (pTable, TokenArray, CharArray);
 *
 *=========================================================================*/
bool CTokenTableArray::ResolveTableReferences (CTokenTable* pTable, CTokenTypeArray& TokenArray, CCharClassArray& CharArray) {
  CTokenTableRow* pRow;
  dword		  Index;
  bool		  Result = true;

  for (Index = 0; Index < pTable->GetNumRows(); ++Index) {
    pRow    = pTable->GetRow(Index);
    Result &= ResolveRowReferences(pRow, pTable, TokenArray, CharArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::ResolveTableReferences()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTableArray Method - bool ResolveReferences (TokenArray, CharArray);
 *
 *=========================================================================*/
bool CTokenTableArray::ResolveReferences (CTokenTypeArray& TokenArray, CCharClassArray& CharArray) {
  CTokenTable*	  pTable;
  dword		  Index;
  bool		  Result = true;

  for (Index = 0; Index < m_Tables.GetSize(); ++Index) {
    pTable  = m_Tables.GetAt(Index);
    Result &= ResolveTableReferences(pTable, TokenArray, CharArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CTokenTableArray::ResolveReferences()
 *=========================================================================*/


