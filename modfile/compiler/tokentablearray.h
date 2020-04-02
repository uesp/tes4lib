/*===========================================================================
 *
 * File:	Tokentablearray.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TOKENTABLEARRAY_H
#define __TOKENTABLEARRAY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentable.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenTableArray Definition
 *
 *=========================================================================*/
class CTokenTableArray {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObPtrArray<CTokenTable>	m_Tables;
  CTokenTable*			m_pMainTable;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper resolve methods */
  bool ResolveRowReferences   (CTokenTableRow* pRow, CTokenTable* pTable, CTokenTypeArray& TokenArray, CCharClassArray& CharArray);
  bool ResolveTableReferences (CTokenTable*  pTable, CTokenTypeArray& TokenArray, CCharClassArray& CharArray);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenTableArray();
  ~CTokenTableArray() { Destroy(); }
  void Destroy (void);

	/* Find a table by its name */
  CTokenTable* GetTable     (const char* pName);
  CTokenTable* GetMainTable (void) { return (m_pMainTable); }

	/* Load a new table from the given file */
  bool LoadNewTable (CObFile& File, const char* pTableName);

	/* Resolve references to external objects */
  bool ResolveReferences (CTokenTypeArray& TokenArray, CCharClassArray& CharArray);


};
/*===========================================================================
 *		End of Class CTokenTableArray Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Tokentablearray.H
 *=========================================================================*/
