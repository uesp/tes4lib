/*===========================================================================
 *
 * File:	Obptrarray.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPTRARRAY_H
#define __OBPTRARRAY_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "stdio.h"
  #include "string.h"
  #include "obtypes.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Minimum array size */
  #define OBPTRARRAY_MINSIZE	32

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  typedef  int (__stdcall *PTRARRAYSORTFUNC) (long lParam1, long lParam2, long lParamSort);

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPtrArray Definition
 *
 * Description
 *
 *=========================================================================*/
template <class TObj>
class CObPtrArray {

  /*---------- Begin Private Class Members ----------------------*/
protected:
  TObj**	m_ppRecords;
  dword		m_NumRecords;
  dword		m_NumAllocated;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Change the allocated size */
  void Resize (const dword NewSize);
  void Grow   (void);

  void Sort_Priv (int StartIndex, int EndIndex, PTRARRAYSORTFUNC CompareFunc, const long Data);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPtrArray();
  virtual   ~CObPtrArray() { Destroy(); }
  virtual void Destroy (void);
  void         Empty   (void) { Destroy(); }

	/* Add new elements */
  void  Add    (TObj* pRecord);
  TObj* AddNew (void);

	/* Delete elements */
  virtual bool  Delete   (const dword Index);
  virtual bool  Delete   (TObj* pRecord);
  virtual TObj* Remove   (const dword Index);
  virtual TObj* Remove   (TObj* pRecord);

	/* Find elements */
  int Find (TObj* pRecord);

	/* Get class members */
  dword GetSize          (void) const { return (m_NumRecords); }
  dword GetAllocatedSize (void) const { return (m_NumAllocated); }

	/* Access records */
  bool  IsValidIndex (const dword Index) const { return (Index < m_NumRecords); }
  TObj* GetAt        (const dword Index) { return (IsValidIndex(Index) ? m_ppRecords[Index] : NULL); }

	/* Insert at a paticular position */
  int  InsertAfter (TObj* pRecord, TObj* pAfter, const int Offset = 0);

	/* Update a record */
  void SetAt (const dword Index, TObj* pRecord) { if (IsValidIndex(Index)) m_ppRecords[Index] = pRecord; }

	/* Set the minimum allocated size */
  void SetAllocatedSize (const dword Size);

	/* Sort records using a comparison function */
  void Sort (PTRARRAYSORTFUNC CompareFunc, const long Data);

	/* Operators */
  TObj* operator[] (const dword Index) { return GetAt(Index); }

 };
/*===========================================================================
 *		End of Class CObPtrArray Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefPtrArray Definition
 *
 * Does not 'own' pointers (are not deleted when the array is deleted).
 *
 *=========================================================================*/
template <class TObj>
class CObRefPtrArray : virtual public CObPtrArray<TObj> {

  /*---------- Begin Public Class Methods -----------------------*/
public:
  virtual ~CObRefPtrArray() { Destroy(); }

	/* Class Constructors/Destructors */
  void Destroy (void);

	/* Delete elements */
  bool Delete (const dword Index);
  bool Delete (TObj* pRecord) { return this->Delete( this->Find(pRecord)); }

 };
/*===========================================================================
 *		End of Class CObRefPtrArray Definition
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObPtrArray Constructor
 *
 *=========================================================================*/
template <class TObj>
CObPtrArray< TObj >::CObPtrArray () {
  m_NumRecords   = 0;
  m_NumAllocated = 0;
  m_ppRecords    = NULL;
 }
/*===========================================================================
 *		End of Class CObPtrArray Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void Destroy (void);
 *
 * Delete the object contents.
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::Destroy (void) {
  dword Index;

  if (m_ppRecords != NULL) {
    for (Index = 0; Index < m_NumRecords; ++Index) {
      if (m_ppRecords[Index] != NULL) {
        delete m_ppRecords[Index];
        m_ppRecords[Index] = NULL;
      }
     }

    delete [] m_ppRecords;
    m_ppRecords = NULL;
   }
  
  m_NumRecords   = 0;
  m_NumAllocated = 0;
 }
/*===========================================================================
 *		End of Class Method CObPtrArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefPtrArray Method - void Destroy (void);
 *
 * Delete the object contents.
 *
 *=========================================================================*/
template <class TObj>
void CObRefPtrArray< TObj >::Destroy (void) {
  
  if ( this->m_ppRecords != NULL) {
     delete [] this->m_ppRecords;
     this->m_ppRecords = NULL;
   }
  
   this->m_NumRecords   = 0;
   this->m_NumAllocated = 0;
 }
/*===========================================================================
 *		End of Class Method CObRefPtrArray::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void Add (TObj* pRecord);
 *
 * Adds a new record to the end of the array.
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::Add (TObj* pRecord) {

	/* Ignore NULLs */
  if (pRecord == NULL) return;

  if (m_NumRecords >= m_NumAllocated) Grow();

  m_ppRecords[m_NumRecords] = pRecord;
  ++m_NumRecords;
 }
/*===========================================================================
 *		End of Class Method CObPtrArray::Add()
 *=========================================================================*/



/*===========================================================================
 *
 * Class CObPtrArray Method - TObj* AddNew (void);
 *
 * Creates and adds a new record to the end of the array. The new record
 * is returned.
 *
 *=========================================================================*/
template <class TObj>
TObj* CObPtrArray< TObj >::AddNew (void) {
  TObj* pRecord;

  
  if (m_NumRecords >= m_NumAllocated) Grow();

  pRecord = new TObj;
  m_ppRecords[m_NumRecords] = pRecord;
  ++m_NumRecords;

  return (pRecord);
 }
/*===========================================================================
 *		End of Class Method CObPtrArray::AddNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - bool Delete (Index);
 *
 * Deletes the specified record from the array (also deletes the object).
 *
 *=========================================================================*/
template <class TObj>
bool CObPtrArray< TObj >::Delete (const dword Index) {

	/* Ignore invalid input */
  if (!IsValidIndex(Index)) return (false);

	/* Unallocate the specified record */
  delete m_ppRecords[Index];
  m_ppRecords[Index] = NULL;

	/* Shift array to the right of deletion point */
  memmove(m_ppRecords + Index, m_ppRecords + Index + 1, (m_NumRecords - Index) * sizeof(TObj *));
  
  --m_NumRecords;
  return (true);
 }


template <class TObj>
bool CObPtrArray< TObj >::Delete (TObj* pRecord) {
  return Delete(Find(pRecord));
}
/*===========================================================================
 *		End of Class Method CObPtrArray::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRefPtrArray Method - bool Delete (Index);
 *
 * Deletes the specified record from the array (does not delete the object).
 *
 *=========================================================================*/
template <class TObj>
bool CObRefPtrArray< TObj >::Delete (const dword Index) {

	/* Ignore invalid input */
  if (! this->IsValidIndex(Index)) return (false);
   this->m_ppRecords[Index] = NULL;

	/* Shift array to the right of deletion point */
  memmove( this->m_ppRecords + Index,  this->m_ppRecords + Index + 1, ( this->m_NumRecords - Index) * sizeof(TObj *));
  
  -- this->m_NumRecords;

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRefPtrArray::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - int InsertAfter (pRecord, pAfter, Offset);
 *
 *=========================================================================*/
template <class TObj>
int  CObPtrArray< TObj >::InsertAfter (TObj* pRecord, TObj* pAfter, const int Offset) {
  int InsertIndex;

  if (m_NumRecords >= m_NumAllocated) Grow();

  InsertIndex = Find(pAfter);
  if (InsertIndex < 0) InsertIndex = (int) m_NumRecords - 1;

  InsertIndex += Offset + 1;
  if (InsertIndex < 0) InsertIndex = 0;
  if (InsertIndex > (int)m_NumRecords) InsertIndex = m_NumRecords;

	/* Shift records if required */
  if (InsertIndex < (int)m_NumRecords) {
    memmove( this->m_ppRecords + InsertIndex + 1,  this->m_ppRecords + InsertIndex, ( (int)this->m_NumRecords - InsertIndex) * sizeof(TObj *));
  }
  
  m_ppRecords[InsertIndex] = pRecord;
  ++m_NumRecords;

  return (InsertIndex);
}
/*===========================================================================
 *		End of Class Method CObRefPtrArray::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - TObj* Remove (Index);
 *
 * Removes and returns the given record from the array. Returns NULL if
 * the input index is invalid.
 *
 *=========================================================================*/
template <class TObj>
TObj* CObPtrArray< TObj >::Remove (const dword Index) {
  TObj* pRecord;

	/* Ignore invalid input */
  if (!IsValidIndex(Index)) return (NULL);

	/* Save the record to return */
  pRecord = m_ppRecords[Index];

	/* Shift array to the right of deletion point */
  memmove(m_ppRecords + Index, m_ppRecords + Index + 1, (m_NumRecords - Index) * sizeof(TObj *));
  --m_NumRecords;

  return (pRecord);
 }


template <class TObj>
TObj* CObPtrArray< TObj >::Remove (TObj* pRecord) {
  return Remove(Find(pRecord));
}
/*===========================================================================
 *		End of Class Method CObPtrArray::Remove()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - int Find (TObj* pRecord);
 *
 * Finds the location of the given record in the array. Returns -1 if
 * the record was not found.
 *
 *=========================================================================*/
template <class TObj>
int CObPtrArray< TObj >::Find (TObj* pRecord) {
  dword Index;

	/* Ignore NULLs */
  if (pRecord == NULL) return (-1);

  for (Index = 0; Index < m_NumRecords; ++Index) {
    if (m_ppRecords[Index] == pRecord) return (Index);
   }

	/* Not found */
  return (-1);
 }
/*===========================================================================
 *		End of Class Method CObPtrArray::Add()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void Grow (void);
 *
 * Grows the size of the array by a set amount.
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::Grow (void) { 

  if (m_NumAllocated*2 < OBPTRARRAY_MINSIZE) {
    Resize(OBPTRARRAY_MINSIZE);
   }
  else {
    Resize(m_NumAllocated * 3 / 2);
   }

 }
/*===========================================================================
 *		End of Class Method CObPtrArray< TObj >::Grow()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void Resize (NewSize);
 *
 * Protected class method to resize the number of allocated elements.
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::Resize (const dword NewSize) {
  TObj** ppNewRecords;
  dword  Size = NewSize;

  if (Size < OBPTRARRAY_MINSIZE) Size = OBPTRARRAY_MINSIZE;
  if (m_NumAllocated >= Size) return;

  ppNewRecords   = new TObj*[Size];

  if (m_ppRecords != NULL) {
    memmove(ppNewRecords, m_ppRecords, sizeof(TObj*)*m_NumAllocated);
    delete [] m_ppRecords;
   }

  m_NumAllocated = Size;
  m_ppRecords = ppNewRecords;
 }
/*===========================================================================
 *		End of Class Method CObPtrArray::Resize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void Sort (CompareFunc, Data);
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::Sort (PTRARRAYSORTFUNC CompareFunc, const long Data) {

  if (CompareFunc == NULL) return;

  Sort_Priv(0, m_NumRecords - 1, CompareFunc, Data);

}
/*===========================================================================
 *		End of Class Method CObPtrArray::Sort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPtrArray Method - void SetAllocatedSize (Size);
 *
 *=========================================================================*/
template <class TObj>
void CObPtrArray< TObj >::SetAllocatedSize (const dword Size) {

  if (m_NumAllocated < Size) {
    Resize(Size);
  }

}
/*===========================================================================
 *		End of Class Method CObPtrArray::Sort()
 *=========================================================================*/


//* ComCtl32 QuickSort
template <class TObj>
void CObPtrArray< TObj >::Sort_Priv (int StartIndex, int EndIndex, PTRARRAYSORTFUNC CompareFunc, const long Data) {
//static VOID DPA_QuickSort (LPVOID *lpPtrs, INT l, INT r, PFNDPACOMPARE pfnCompare, LPARAM lParam)
  int   MidIndex;
  int   Result;
  TObj* pTemp;
 
  if (StartIndex < 0 || EndIndex < 0) return;	/* Empty list sort calls with a negative value */
  if (StartIndex == EndIndex) return;

  if (EndIndex < StartIndex) {
    Sort_Priv(EndIndex, StartIndex, CompareFunc, Data);
    return;
  }

  MidIndex = (StartIndex + EndIndex) / 2;
  Sort_Priv(StartIndex,   MidIndex, CompareFunc, Data);
  Sort_Priv(MidIndex + 1, EndIndex, CompareFunc, Data);
 
	/* Join the two sides */
  while( (StartIndex <= MidIndex) && (MidIndex < EndIndex) ) {
    Result = CompareFunc((long)m_ppRecords[StartIndex], (long)m_ppRecords[MidIndex + 1], Data);

    if (Result > 0) {
      pTemp = m_ppRecords[MidIndex + 1];
      memmove(&m_ppRecords[StartIndex + 1], &m_ppRecords[StartIndex], (MidIndex - StartIndex + 1)*sizeof(m_ppRecords[StartIndex]));
      m_ppRecords[StartIndex] = pTemp;

      ++MidIndex;
    }
    ++StartIndex;
  }

} //*/


/* Heap Sort

template <class TObj>
void CObPtrArray< TObj >::Sort_Priv (const int , const int , PTRARRAYSORTFUNC CompareFunc, const long Data) {
  TObj* pTemp;
  int   StartIndex = 0;
  int   EndIndex   = m_NumRecords - 1;
  int   RootIndex, ChildIndex;
  int   Result;
  int   Remainder;

  while (StartIndex <= (int)m_NumRecords - 2) {
    ++StartIndex;
    //SiftUp(StartIndex);
    ChildIndex = StartIndex;
    
    while (ChildIndex > 0) {
      Remainder = (ChildIndex - 1) % 2;
      RootIndex = ((ChildIndex - 1) - Remainder) / 2;

      Result = CompareFunc((long)m_ppRecords[RootIndex], (long)m_ppRecords[ChildIndex], Data);
      
      if (Result < 0) {
        pTemp = m_ppRecords[RootIndex];
        m_ppRecords[RootIndex] = m_ppRecords[ChildIndex];
        m_ppRecords[ChildIndex] = pTemp;
        ChildIndex = RootIndex;
      }
      else {
        break;
      }
    }
    //SiftUp(StartIndex);
  }

  while (EndIndex > 0) {
    pTemp = m_ppRecords[EndIndex];
    m_ppRecords[EndIndex] = m_ppRecords[0];
    m_ppRecords[0] = pTemp;

    //SiftDown(0, EndIndex);
    RootIndex = 0;

    while (RootIndex * 2 + 1 < EndIndex) {
      ChildIndex = RootIndex * 2 + 1;

      if (ChildIndex < EndIndex - 1) {
        Result = CompareFunc((long)m_ppRecords[ChildIndex], (long)m_ppRecords[ChildIndex + 1], Data);
        if (Result < 0) ++ChildIndex;
      }

      Result = CompareFunc((long)m_ppRecords[RootIndex], (long)m_ppRecords[ChildIndex], Data);

      if (Result < 0) {
        pTemp = m_ppRecords[RootIndex];
        m_ppRecords[RootIndex] = m_ppRecords[ChildIndex];
        m_ppRecords[ChildIndex] = pTemp;
	RootIndex = ChildIndex;
      }
      else {
        break;
      }
    }
    //SiftDown(0, EndIndex);

    --EndIndex;
  }

}
//*/

 
/* Partitioned Quick Sort
template <class TObj>
void CObPtrArray< TObj >::Sort_Priv (const int StartIndex, const int EndIndex, PTRARRAYSORTFUNC CompareFunc, const long Data) {

  if (EndIndex <= StartIndex) return;

  int   PivotIndex  = (EndIndex + StartIndex)/2;
  TObj* pPivot = m_ppRecords[PivotIndex];
  TObj* pTemp;

  pTemp = m_ppRecords[EndIndex];
  m_ppRecords[EndIndex]   = pPivot;
  m_ppRecords[PivotIndex] = pTemp;

  int StoreIndex = StartIndex;
  int Index;
  int Result;
  
  for (Index = StartIndex; Index < EndIndex; ++Index) {
    Result = CompareFunc((long)m_ppRecords[Index], (long)pPivot, Data);

    if (Result <= 0) {
      pTemp = m_ppRecords[StoreIndex];
      m_ppRecords[StoreIndex] = m_ppRecords[Index];
      m_ppRecords[Index]      = pTemp;
      ++StoreIndex;
    }
  }    

  pTemp = m_ppRecords[EndIndex];
  m_ppRecords[EndIndex]   = m_ppRecords[StoreIndex];
  m_ppRecords[StoreIndex] = pTemp;

  PivotIndex = StoreIndex;

  Sort_Priv(StartIndex, PivotIndex - 1, CompareFunc, Data);
  Sort_Priv(PivotIndex + 1, EndIndex, CompareFunc, Data);
}
//*/


#endif
/*===========================================================================
 *		End of File Obptrarray.H
 *=========================================================================*/
