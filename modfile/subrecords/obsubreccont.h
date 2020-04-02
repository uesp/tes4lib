/*===========================================================================
 *
 * File:	ObSubreccont.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObSubRecContainer used to hold a collection of records.
 *
 *=========================================================================*/
#ifndef __OBUSBRECCONT_H
#define __OBUSBRECCONT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
  #include "../../common/obptrarray.h"
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
 * Begin Class CObSubrecContainer Definition
 *
 * Should be designed and implemented as a generic container class. The exact
 * nature of the container (array, list, map, tree, etc...) should be 
 * irrelevant and not discernable from outside the class.
 *
 * Current implementation uses a simple dynamic array.
 *
 *=========================================================================*/
class CObSubrecContainer {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObSubrecordArray m_Subrecords;		/* Container of subrecords */


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSubrecContainer();
  ~CObSubrecContainer() { Destroy(); }
  void Destroy (void);

	/* Add records */
  void Add (CObSubrecord* pRecord) { m_Subrecords.Add(pRecord); }

	/* Delete records */
  void Delete (const dword       Index) { m_Subrecords.Delete(Index); }
  void Delete (const obrectype_t Type);

	/* Find the specified record in the container */
  int Find (CObSubrecord* pRecord) { return m_Subrecords.Find(pRecord); }

	/* Insert in a certain position */
  int InsertAfter (CObSubrecord* pSubrecord, CObSubrecord* pAfter, const int Offset) { return m_Subrecords.InsertAfter(pSubrecord, pAfter, Offset); }

  	/* Access records */
  CObSubrecord* GetRecord  (const dword Index) { return m_Subrecords[Index]; }
  CObSubrecord* operator[] (const dword Index) { return m_Subrecords[Index]; }

  dword GetSize (void) const { return (m_Subrecords.GetSize()); }

 };
/*===========================================================================
 *		End of Class CObSubrecContainer Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File ObSubreccont.H
 *=========================================================================*/
