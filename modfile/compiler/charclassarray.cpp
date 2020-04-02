/*===========================================================================
 *
 * File:	Charclassarray.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "charclassarray.h"


/*===========================================================================
 *
 * Class CCharClassArray Constructor
 *
 *=========================================================================*/
CCharClassArray::CCharClassArray () {

}
/*===========================================================================
 *		End of Class CCharClassArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClassArray Method - void Destroy (void);
 *
 *=========================================================================*/
void CCharClassArray::Destroy (void) {
  m_Records.Destroy();
}
/*===========================================================================
 *		End of Class Method CCharClassArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClassArray Method - CCharClass* GetCharClass (pName);
 *
 *=========================================================================*/
CCharClass* CCharClassArray::GetCharClass (const char* pName) {
  CCharClass*	pCharClass;
  dword		Index;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    pCharClass = m_Records.GetAt(Index);
    if (pCharClass->IsName(pName)) return (pCharClass);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CCharClassArray::GetCharClass()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CCharClassArray Method - bool Load (File);
 *
 *=========================================================================*/
bool CCharClassArray::Load (CObFile& File) {
  CCharClass* pCharClass;
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
      pCharClass = new CCharClass;
      m_Records.Add(pCharClass);

      pCharClass->SetName(Variable);
      Result = pCharClass->SetDefinition(Value);
    }
    else if (Variable.CompareNoCase("end") == 0) {
      break;
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CCharClassArray::Load()
 *=========================================================================*/
