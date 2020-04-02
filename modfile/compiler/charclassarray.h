/*===========================================================================
 *
 * File:	Charclassarray.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __CHARCLASSARRAY_H
#define __CHARCLASSARRAY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "charclass.h"
  #include "../../common/obptrarray.h"
  #include "../../common/obfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CCharClassArray Definition
 *
 *=========================================================================*/
class CCharClassArray {

  /*---------- Begin protected Class Members --------------------*/
protected:
  CObPtrArray<CCharClass>	m_Records;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CCharClassArray();
  ~CCharClassArray() { Destroy(); }
  void Destroy (void);

	/* Get class members */
  CCharClass* GetCharClass  (const char* pName);
  dword       GetNumRecords (void) { return (m_Records.GetSize()); }

	/* Load character class definitions from a file */
  bool Load (CObFile& File);

};
/*===========================================================================
 *		End of Class CCharClassArray Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Charclassarray.H
 *=========================================================================*/

