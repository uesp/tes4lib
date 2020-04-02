/*===========================================================================
 *
 * File:	TokenTypeArray.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __TOKENTYPEARRAY_H
#define __TOKENTYPEARRAY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "tokentype.h"
  #include "../../common/obptrarray.h"
  #include "../../common/obfile.h"
  #include "scansource.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Defines a single token instance */
  struct tokeninstance_t {
	CTokenType*	pToken;
	sourcepos_t	StartPos;
	sourcepos_t	EndPos;
	CSString	Value;
  };

  typedef CObPtrArray<tokeninstance_t>    CTokenInstanceArray;
  typedef CObRefPtrArray<tokeninstance_t> CRefTokenInstanceArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CTokenTypeArray Definition
 *
 *=========================================================================*/
class CTokenTypeArray {

  /*---------- Begin protected Class Members --------------------*/
protected:
  CObPtrArray<CTokenType>	m_Records;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CTokenTypeArray();
  ~CTokenTypeArray() { Destroy(); }
  void Destroy (void);

	/* Find a token ID */
  int FindTokenID (const char* pName);

  CTokenType* GetTokenType  (const int ID);
  CTokenType* GetTokenType  (const char* pName);
  CTokenType* GetRecord     (const dword Index) { return m_Records.GetAt(Index); }

	/* Get class members */
  CTokenType* GetEndToken   (void);
  dword       GetNumRecords (void) { return (m_Records.GetSize()); }

	/* Load character class definitions from a file */
  bool Load (CObFile& File);

};
/*===========================================================================
 *		End of Class CTokenTypeArray Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File TokenTypearray.H
 *=========================================================================*/

