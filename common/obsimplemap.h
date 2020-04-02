/*===========================================================================
 *
 * File:	Obsimplemap.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 26, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSIMPLEMAP_H
#define __OBSIMPLEMAP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "common/obtypes.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/



/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default size of the hash map tables */
  #define OB_SIMPLEMAP_DEFAULTSIZE 1009


/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSimpleMap Definition
 *
 * Template class from which simple hash-map implementations can be 
 * created from. 
 *
 *=========================================================================*/
template<class TKey>
class CObSimpleMap {

	/* Private structure used as a linked list for each unique hash value */
  struct CObSimpleMapAssoc {
	CObSimpleMapAssoc* pNext;
	dword		   HashValue;
	TKey               Value;
   };

  /*---------- Begin Protected Class Members --------------------*/
protected:

  CObSimpleMapAssoc**	m_ppHashTable;		/* Array of hash records */
  dword			m_RecordCount;
  dword			m_HashTableSize;
  


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Compare two keys */
  virtual bool CompareKeys (const TKey Key1, const TKey Key2);

	/* Helper find method */
  virtual CObSimpleMapAssoc* GetAssocNode (const TKey Key, dword& Hash);

	/* Create a new node */
  virtual CObSimpleMapAssoc* NewAssocNode (void);

	
  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSimpleMap();
  virtual ~CObSimpleMap() { Destroy(); }
  virtual void Destroy (void) { RemoveAll(); }

	/* Delete a specified key */
  void Delete (const TKey Key);

	/* Get class members */
  virtual dword GetRecordCount (void) { return (m_RecordCount); }

	/* Hash a key value */
  virtual dword HashKey (const TKey Key);

	/* Initialize the hash table to a specific size */
  virtual void InitHashTable (const dword Size);
	
	/* Find an existing value by its key */
  virtual bool Lookup (const TKey TempKey, TKey*& pKey);

	/* Delete all hash table entries */
  virtual void RemoveAll (void);

	/* Set a value */
  virtual void SetAt (const TKey Key);

 };
/*===========================================================================
 *		End of Class CObSimpleMap Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Constructor
 *
 *=========================================================================*/
template<class TKey>
CObSimpleMap<TKey>::CObSimpleMap () {
  m_ppHashTable   = NULL;
  m_RecordCount   = 0;
  m_HashTableSize = OB_SIMPLEMAP_DEFAULTSIZE;
 }
/*===========================================================================
 *		End of Class CObSimpleMap Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - bool CompareKeys (Key1, Key2);
 *
 *=========================================================================*/
template<class TKey>
inline bool CObSimpleMap<TKey>::CompareKeys (const TKey Key1, const TKey Key2) {
  return (Key1 == Key2);
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::CompareKeys()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - void Delete (Key);
 *
 *=========================================================================*/
template<class TKey>
void CObSimpleMap<TKey>::Delete (const TKey Key) {
  CObSimpleMapAssoc*	pAssoc;
  CObSimpleMapAssoc*	pLastAssoc = NULL;
  dword			Hash;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return;
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {

    if (CompareKeys(pAssoc->Value, Key)) {

      if (pLastAssoc == NULL)
        m_ppHashTable[Hash] = pAssoc->pNext;
      else
        pLastAssoc->pNext = pAssoc->pNext;

      delete pAssoc;
      return;
     }

    pLastAssoc = pAssoc;
   }

 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - CObSimpleMapAssoc* GetAssocNode (Key, Hash);
 *
 *=========================================================================*/
template<class TKey>
CObSimpleMap<TKey>::CObSimpleMapAssoc* CObSimpleMap<TKey>::GetAssocNode (const TKey Key, dword& Hash) {
  CObSimpleMapAssoc* pAssoc;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return (NULL);
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
    if (CompareKeys(pAssoc->Value, Key)) return pAssoc;
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::GetAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - dword HashKey (Key);
 *
 *=========================================================================*/
template<class TKey>
inline dword CObSimpleMap<TKey>::HashKey (const TKey Key) {
  return ((dword) Key) >> 4;
 }
/*===========================================================================
 *		End of Class Method dword CObSimpleMap::HashKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - void InitHashTable (Size);
 *
 *=========================================================================*/
template<class TKey>
void CObSimpleMap<TKey>::InitHashTable (const dword Size) {
  
	/* Clear the current table if any */
  if (m_ppHashTable != NULL) {
    delete[] m_ppHashTable;
    m_ppHashTable = NULL;
   }

   int Temp = sizeof(CObSimpleMapAssoc);

	/* Allocate the new hash table */ 
  m_HashTableSize = Size;
  m_ppHashTable   = new CObSimpleMapAssoc* [m_HashTableSize];
  m_RecordCount   = 0;
  memset(m_ppHashTable, 0, sizeof(CObSimpleMapAssoc*) * m_HashTableSize);
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::InitHashTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - bool Lookup (TempKey, pKey);
 *
 *=========================================================================*/
template<class TKey>
bool CObSimpleMap<TKey>::Lookup (const TKey TempKey, TKey*& pKey) {
  CObSimpleMapAssoc* pAssoc;
  dword        Hash;

  pAssoc = GetAssocNode(TempKey, Hash);

  if (pAssoc == NULL) {
    pKey = NULL;
    return (false);
   }

  pKey = &pAssoc->Value;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::Lookup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - CObSimpleMapAssoc* NewAssocNode (void);
 *
 *=========================================================================*/
template<class TKey>
CObSimpleMap<TKey>::CObSimpleMapAssoc* CObSimpleMap<TKey>::NewAssocNode (void) {
  CObSimpleMap::CObSimpleMapAssoc* pAssoc;

  pAssoc = new CObSimpleMapAssoc;
  return (pAssoc);
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::NewAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - void RemoveAll (void);
 *
 *=========================================================================*/
template<class TKey>
void CObSimpleMap<TKey>::RemoveAll (void) {
  CObSimpleMapAssoc*	pAssoc;
  CObSimpleMapAssoc*	pAssoc1;
  dword			Index;

	/* Delete all records in the table */
  if (m_ppHashTable != NULL) {
    for (Index = 0; Index < m_HashTableSize; ++Index) {
      for (pAssoc = m_ppHashTable[Index]; pAssoc != NULL; ) {
        pAssoc1 = pAssoc->pNext;
        delete pAssoc;
        pAssoc = pAssoc1;
       }
     }

    delete[] m_ppHashTable;
    m_ppHashTable = NULL;
   }

  m_RecordCount = 0;
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::RemoveAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSimpleMap Method - void SetAt (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey>
void CObSimpleMap<TKey>::SetAt (const TKey Key) {
  CObSimpleMapAssoc* pAssoc;
  dword        Hash;

	/* Find an existing node */
  pAssoc = GetAssocNode(Key, Hash);

  if (pAssoc == NULL) {
    if (m_ppHashTable == NULL) InitHashTable(m_HashTableSize);

    pAssoc = NewAssocNode();
    pAssoc->HashValue = Hash;

    pAssoc->pNext       = m_ppHashTable[Hash];
    m_ppHashTable[Hash] = pAssoc;
    ++m_RecordCount;
   }

  pAssoc->Value = Key;
 }
/*===========================================================================
 *		End of Class Method CObSimpleMap::SetAt()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obsimplemap.H
 *=========================================================================*/
