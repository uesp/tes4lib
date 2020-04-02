/*===========================================================================
 *
 * File:	Obreccont.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObRecContainer used to hold a collection of records.
 *
 *=========================================================================*/
#ifndef __OBRECCONT_H
#define __OBRECCONT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
  #include "../../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Array of record pointers (not owned) */
  typedef CObRefPtrArray<CObBaseRecord> CObRefBaseRecordArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecContainer Definition
 *
 * Should be designed and implemented as a generic container class. The exact
 * nature of the container (array, list, map, tree, etc...) should be 
 * irrelevant and not discernable from outside the class.
 *
 * Current implementation uses a simple dynamic array.
 *
 *=========================================================================*/
class CObRecContainer {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObPtrArray<CObRecord> m_Records;		/* Container of records */


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRecContainer();
  ~CObRecContainer() { Destroy(); }
  void Destroy (void);

	/* Add records */
  void Add (CObRecord* pRecord) { m_Records.Add(pRecord); }

	/* Access records */
  CObRecord* GetRecord (const int Index) { return m_Records[Index]; }



 };
/*===========================================================================
 *		End of Class CObRecContainer Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obreccont.H
 *=========================================================================*/
