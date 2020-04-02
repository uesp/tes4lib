/*===========================================================================
 *
 * File:	Tokentable.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TOKENTABLE_H
#define __TOKENTABLE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentablerow.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Define an array of row objects */
  typedef CObPtrArray<CTokenTableRow> CTokenTableRowArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenTable Definition
 *
 *=========================================================================*/
class CTokenTable {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CTokenTableRowArray	m_Rows;
  CTokenTableRow*	m_pDefaultRow;

  CSString		m_Name;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenTable();
  ~CTokenTable() { Destroy(); }
  void Destroy (void);

	/* Get class members */
  dword		  GetNumRows    (void)              { return m_Rows.GetSize(); }
  CTokenTableRow* GetRow        (const dword Index) { return m_Rows.GetAt(Index); }
  CTokenTableRow* GetDefaultRow (void)              { return m_pDefaultRow; }
  const char*	  GetName       (void)		    { return m_Name; }

	/* Match the table name */
  bool IsName (const char* pString) { return (m_Name.CompareNoCase(pString) == 0); }

	/* Load the table definition from the given file */
  bool Load (CObFile& File);

	/* Set class members */
  void SetName (const char* pString) { m_Name = pString; }

};
/*===========================================================================
 *		End of Class CTokenTable Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Tokentable.H
 *=========================================================================*/
