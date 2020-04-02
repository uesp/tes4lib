/*===========================================================================
 *
 * File:	ObBaseRecCont.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 6, 2006
 *
 * Defines the CObBaseRecordContainer used to handle a collection of 
 * groups and records.
 *
 *=========================================================================*/
#ifndef __OBBASERECCONT_H
#define __OBBASERECCONT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbaserecord.h"
  #include "../../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBaseRecordContBase Definition
 *
 * Base abstract class.
 *
 *=========================================================================*/
class CObBaseRecordContBase {

  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObBaseRecordContBase();
  //virtual ~CObBaseRecordContBase() { Destroy(); }
  virtual void Destroy (void) = 0;

	/* Add records */
  virtual void Add         (CObBaseRecord* pObject) = 0;
  virtual void InsertAfter (CObBaseRecord* pObject, CObBaseRecord* pInsert) = 0;

	/* Delete records */
  virtual bool Delete (CObBaseRecord* pObject) = 0;

  	/* Access records */
  virtual CObBaseRecord* GetRecord  (const int Index) = 0;
  virtual CObBaseRecord* GetAt      (const int Index) = 0;
  virtual CObBaseRecord* operator[] (const int Index) = 0;

  virtual dword GetSize (void) const = 0;

	/* Set a specific record */
  virtual void SetAt (const int Index, CObBaseRecord* pObject) = 0;

	/* Set the minimum array allocated size */
  virtual void SetAllocatedSize (const int Index) = 0;

 };
/*===========================================================================
 *		End of Class CObBaseRecordContBase Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBaseRecordCont Definition
 *
 * Description
 *
 *=========================================================================*/
class CObBaseRecordCont : public CObBaseRecordContBase {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObBaseRecordArray	m_Records;		/* Container of records and groups */


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObBaseRecordCont();
  virtual ~CObBaseRecordCont() { Destroy(); }
  virtual void Destroy (void) { m_Records.Destroy(); }

	/* Add records */
  virtual void Add (CObBaseRecord* pObject) { m_Records.Add(pObject); }
  virtual void InsertAfter (CObBaseRecord* pObject, CObBaseRecord* pInsert) { m_Records.InsertAfter(pObject, pInsert); }

	/* Delete records */
  virtual bool Delete (CObBaseRecord* pObject);

  	/* Access records */
  virtual CObBaseRecord* GetRecord  (const int Index) { return m_Records.GetAt(Index); }
  virtual CObBaseRecord* GetAt      (const int Index) { return m_Records.GetAt(Index); }
  virtual CObBaseRecord* operator[] (const int Index) { return m_Records.GetAt(Index); }

  virtual dword GetSize (void) const { return (m_Records.GetSize()); }
  
	/* Set a specific record */
  virtual void SetAt (const int Index, CObBaseRecord* pObject) { m_Records.SetAt(Index, pObject); }

	/* Set the minimum array allocated size */
  virtual void SetAllocatedSize (const int Size) { m_Records.SetAllocatedSize((dword) Size); }

 };
/*===========================================================================
 *		End of Class CObBaseRecordCont Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefBaseRecordCont
 *
 *=========================================================================*/
class CObRefBaseRecordCont : public CObBaseRecordContBase {

 /*---------- Begin Private Class Members ----------------------*/
private:
  CObRefBaseRecordArray	m_Records;		/* Container of records and groups */


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructor */
  //CObRefBaseRecordCont();
  virtual ~CObRefBaseRecordCont() { Destroy(); }
  virtual void Destroy (void) { m_Records.Destroy(); }
  
	/* Add records */
  virtual void Add (CObBaseRecord* pObject) { m_Records.Add(pObject); }
  virtual void InsertAfter (CObBaseRecord* pObject, CObBaseRecord* pInsert) { m_Records.InsertAfter(pObject, pInsert); }

	/* Delete records */
  virtual bool Delete (CObBaseRecord* pObject);

  	/* Access records */
  virtual CObBaseRecord* GetRecord  (const int Index) { return m_Records.GetAt(Index); }
  virtual CObBaseRecord* GetAt      (const int Index) { return m_Records.GetAt(Index); }
  virtual CObBaseRecord* operator[] (const int Index) { return m_Records.GetAt(Index); }

  virtual dword GetSize (void) const { return (m_Records.GetSize()); }

  	/* Set a specific record */
  virtual void SetAt (const int Index, CObBaseRecord* pObject) { m_Records.SetAt(Index, pObject); }

	/* Set the minimum array allocated size */
  virtual void SetAllocatedSize (const int Size) { m_Records.SetAllocatedSize((dword) Size); }

};
/*===========================================================================
 *		End of Class CObRefBaseRecordCont
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obgrupcont.H
 *=========================================================================*/
