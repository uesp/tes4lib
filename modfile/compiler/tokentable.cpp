/*===========================================================================
 *
 * File:	Tokentable.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "tokentable.h"


/*===========================================================================
 *
 * Class CTokenTable Constructor
 *
 *=========================================================================*/
CTokenTable::CTokenTable() {
  m_pDefaultRow = NULL;
}
/*===========================================================================
 *		End of Class CTokenTable Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTable Method - void Destroy (void);
 *
 *=========================================================================*/
void CTokenTable::Destroy (void) {
  m_pDefaultRow = NULL;

  m_Name.Empty();
  m_Rows.Destroy();
}
/*===========================================================================
 *		End of Class Method CTokenTable::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CTokenTable Method - bool Load (File);
 *
 * Attempt to load a table definition from the given file. Returns false
 * on any error. 
 *
 * Expects a format of the type:
 *
 *	[RowValue] = [RowResult]
 *		...
 *	end
 *
 *=========================================================================*/
bool CTokenTable::Load (CObFile& File) {
  CTokenTableRow* pRow;
  CSString	  LineBuffer;
  CSString	  Variable;
  CSString	  Value;
  bool		  Result;

  while (!File.IsEOF()) {
    Result = File.ReadLine(LineBuffer);
    if (!Result) return (false);

    Result = LineBuffer.SeperateVarValueNQ(Variable, Value, '=', 0);

    if (Result) {
      pRow = new CTokenTableRow;
      m_Rows.Add(pRow);

      if (Variable.CompareNoCase("default") == 0) {
        Variable.Empty();
	m_pDefaultRow = pRow;
      }

      Result = pRow->SetDefinition(Variable, Value);
    }
    else if (Variable.CompareNoCase("end") == 0) {
      break;
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CTokenTable::Load()
 *=========================================================================*/




