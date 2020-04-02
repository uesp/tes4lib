/*===========================================================================
 *
 * File:	Obrecordmap.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 6, 2006
 *
 * Defines various hash-map classes used to hold records.
 *
 *=========================================================================*/
#ifndef __OBRECORDMAP_H
#define __OBRECORDMAP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default size of the hash map tables */
  #define OB_RECORDMAP_DEFAULTSIZE 1009

	/* Used to iterate through records */
  typedef void* OBMAPPOS;

	/* Number of nodes to allocate at a time */
  #define OB_RECORDMAP_BLOCKSIZE 10000

	/* Use block allocators or not */
  #define OB_RECORDMAP_ALLOCATEBLOCK 1

#if OB_RECORDMAP_ALLOCATEBLOCK
  #define OBMAP_DELETENODE(pNode)	/* Don't delete a node when using blocked allocators */
#else
  #define OBMAP_DELETENODE(pNode) delete pNode
#endif

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBaseRecordMap Definition
 *
 * Template class from which specific hash-map implementations will be 
 * created from.
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
class CObBaseRecordMap {

	/* Private structure used as a linked list for each unique hash value */
  struct CObMapAssoc {
	CObMapAssoc* pNext;
	dword	     HashValue;
	TRecord*     Value;
  };

  struct CObMapBlock {
	CObMapAssoc*	pNodes;
	dword		NextFreeIndex;
	dword		BlockSize;
	CObMapBlock*	pNextBlock;
  };

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObMapAssoc**	m_ppHashTable;		/* Array of hash records */
  dword		m_RecordCount;
  dword		m_HashTableSize;

  CObMapBlock*	m_pHeadBlock;
  


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Create a new node */
  virtual CObMapAssoc* CreateAssocNode (void);

	/* Delete all allocated node blocks */
  void DestroyBlocks (void);

	/* Compare two keys */
  virtual bool CompareKeys (TKeyArg     Key1, TKeyArg     Key2);
  virtual bool CompareKeys (TRecord* Record1, TRecord* Record2);
  virtual bool CompareKeys (TRecord* Record,  TKeyArg      Key) = 0;

	/* Helper find method */
  virtual CObMapAssoc* GetAssocNode (TKeyArg  Key,    dword& Hash);
  virtual CObMapAssoc* GetAssocNode (TRecord* Record, dword& Hash);

	

	
  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBaseRecordMap();
  virtual ~CObBaseRecordMap() { Destroy(); }
  virtual void Destroy (void);

	/* Delete a specified key */
  void Delete (TKeyArg Key, TRecord* pRecord);

	/* Iterate through records in the map */
  TRecord* GetFirstRecord (OBMAPPOS& Position);
  TRecord* GetNextRecord  (OBMAPPOS& Position);

	/* Get class members */
  virtual dword GetRecordCount (void) { return (m_RecordCount); }

	/* Hash a key value */
  virtual dword HashKey (TKeyArg  Key);
  virtual dword HashKey (TRecord* pRecord);

	/* Initialize the hash table to a specific size */
  virtual void InitHashTable (const dword Size);

	/* Checks if the given record is valid or not */
  virtual bool IsValidRecord (TRecord* pRecord) { return (pRecord != NULL); }

	/* Find an existing value by its key */
  virtual bool Lookup (TKeyArg Key, TRecord*& pRecord);

	/* Delete all hash table entries */
  virtual void RemoveAll (void);

	/* Set a value */
  virtual void SetAt (TKeyArg Key, TRecord* pRecord);

 };
/*===========================================================================
 *		End of Class CObBaseRecordMap Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Constructor
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
CObBaseRecordMap<TKey, TRecord, TKeyArg>::CObBaseRecordMap () {
  m_ppHashTable   = NULL;
  m_RecordCount   = 0;
  m_HashTableSize = OB_RECORDMAP_DEFAULTSIZE;
  m_pHeadBlock    = NULL;
 }
/*===========================================================================
 *		End of Class CObBaseRecordMap Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void Destroy (void);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
inline void CObBaseRecordMap<TKey, TRecord, TKeyArg>::Destroy (void) {
  RemoveAll();
}
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void DestroyBlocks (void);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
inline void CObBaseRecordMap<TKey, TRecord, TKeyArg>::DestroyBlocks (void) {
  CObMapBlock* pBlock     = m_pHeadBlock;
  CObMapBlock* pNextBlock = m_pHeadBlock;

  while (pBlock != NULL) {
    delete[] pBlock->pNodes;

    pNextBlock = pBlock->pNextBlock;
    delete pBlock;
    pBlock = pNextBlock;
  }

  m_pHeadBlock = NULL;
}
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - CObMapAssoc* CreateAssocNode (void);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
typename CObBaseRecordMap<TKey, TRecord, TKeyArg>::CObMapAssoc* CObBaseRecordMap<TKey, TRecord, TKeyArg>::CreateAssocNode (void) {
  typename CObBaseRecordMap::CObMapAssoc* pAssoc;

#if OB_RECORDMAP_ALLOCATEBLOCK

  if (m_pHeadBlock == NULL || m_pHeadBlock->NextFreeIndex >= m_pHeadBlock->BlockSize) {
    CObMapBlock* pNewBlock   = new CObMapBlock;
    pNewBlock->BlockSize     = OB_RECORDMAP_BLOCKSIZE;
    pNewBlock->NextFreeIndex = 0;
    pNewBlock->pNodes        = new CObMapAssoc[OB_RECORDMAP_BLOCKSIZE];
    pNewBlock->pNextBlock    = m_pHeadBlock;
    m_pHeadBlock = pNewBlock;
  }

  pAssoc = &(m_pHeadBlock->pNodes[m_pHeadBlock->NextFreeIndex]);
  ++m_pHeadBlock->NextFreeIndex;

#else
  pAssoc = new CObMapAssoc;
#endif

  return (pAssoc);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::CreateAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - bool CompareKeys (Key1, Key2);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
inline bool CObBaseRecordMap<TKey, TRecord, TKeyArg>::CompareKeys (TKeyArg Key1, TKeyArg Key2) {
  return (Key1 == Key2);
 }


template<class TKey, class TRecord, class TKeyArg>
inline bool CObBaseRecordMap<TKey, TRecord, TKeyArg>::CompareKeys (TRecord* Record1, TRecord* Record2) {
  return (Record1 == Record2);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::CompareKeys()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void Delete (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
void CObBaseRecordMap<TKey, TRecord, TKeyArg>::Delete (TKeyArg Key, TRecord* pRecord) {
  CObMapAssoc* pAssoc;
  CObMapAssoc* pLastAssoc = NULL;
  dword        Hash;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return;
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {

    if (CompareKeys(pAssoc->Value, Key)) {

      if (pLastAssoc != NULL) 
        pLastAssoc->pNext = pAssoc->pNext;
      else
        m_ppHashTable[Hash] = pAssoc->pNext;

      OBMAP_DELETENODE(pAssoc);
      return;
     }

    pLastAssoc = pAssoc;
   }

 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - CObMapAssoc* GetAssocNode (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
typename CObBaseRecordMap<TKey, TRecord, TKeyArg>::CObMapAssoc* CObBaseRecordMap<TKey, TRecord, TKeyArg>::GetAssocNode (TKeyArg Key, dword& Hash) {
  CObMapAssoc* pAssoc;

	/* Ignore if no table defined */
  Hash = HashKey(Key) % m_HashTableSize;
  if (m_ppHashTable == NULL) return (NULL);
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
    if (CompareKeys(pAssoc->Value, Key)) return pAssoc;
   }

  return (NULL);
 }


template<class TKey, class TRecord, class TKeyArg>
typename CObBaseRecordMap<TKey, TRecord, TKeyArg>::CObMapAssoc* CObBaseRecordMap<TKey, TRecord, TKeyArg>::GetAssocNode (TRecord* pRecord, dword& Hash) {
  CObMapAssoc* pAssoc;

	/* Ignore if no table defined */
  Hash = HashKey(pRecord) % m_HashTableSize;
  if (m_ppHashTable == NULL) return (NULL);
  
  for (pAssoc = m_ppHashTable[Hash]; pAssoc != NULL; pAssoc = pAssoc->pNext) {
    if (CompareKeys(pAssoc->Value, pRecord)) return pAssoc;
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::GetAssocNode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - CObMapAssoc* GetFirstRecord (Position);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
TRecord* CObBaseRecordMap<TKey, TRecord, TKeyArg>::GetFirstRecord (OBMAPPOS& Position) {
  CObMapAssoc* pAssoc;
  dword	       Index;

  Position = (OBMAPPOS) NULL;
  if (m_ppHashTable == NULL) return (NULL);

  for (Index = 0; Index < m_HashTableSize; ++Index) {
    pAssoc = m_ppHashTable[Index];
    
    if (pAssoc != NULL) {
      Position = (OBMAPPOS) pAssoc;
      return (pAssoc->Value);
     }
   }

	/* Nothing to return */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::GetFirstRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - CObMapAssoc* GetNextRecord (Key, Hash);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
TRecord* CObBaseRecordMap<TKey, TRecord, TKeyArg>::GetNextRecord (OBMAPPOS& Position) {
  CObMapAssoc* pAssoc;
  dword	       Index;

  pAssoc = (CObMapAssoc *) Position;
  if (m_ppHashTable == NULL) return (NULL);
  if (pAssoc        == NULL) return (NULL);

  if ( pAssoc->pNext != NULL) {
    Position = (OBMAPPOS)  pAssoc->pNext;
    return ( pAssoc->pNext->Value);
   }

  for (Index = pAssoc->HashValue + 1; Index < m_HashTableSize; ++Index) {
    pAssoc = m_ppHashTable[Index]; 
    
    if (pAssoc != NULL) {
      Position = (OBMAPPOS) pAssoc;
      return (pAssoc->Value);
     }
   }

	/* Nothing to return */
  Position = (OBMAPPOS) NULL;
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::GetNextRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - dword HashKey (Key);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
inline dword CObBaseRecordMap<TKey, TRecord, TKeyArg>::HashKey (TKeyArg Key) {
  return (dword) (((obptr_t) Key) >> 4);
 }


template<class TKey, class TRecord, class TKeyArg>
inline dword CObBaseRecordMap<TKey, TRecord, TKeyArg>::HashKey (TRecord* pRecord) {
  return (dword) (((obptr_t) pRecord) >> 4);
 }
/*===========================================================================
 *		End of Class Method dword CObBaseRecordMap::HashKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void InitHashTable (Size);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
void CObBaseRecordMap<TKey, TRecord, TKeyArg>::InitHashTable (const dword Size) {
  
	/* Clear the current table if any */
  if (m_ppHashTable != NULL) {
    delete[] m_ppHashTable;
    m_ppHashTable = NULL;
   }

	/* Allocate the new hash table */ 
  m_HashTableSize = Size;
  m_ppHashTable   = new CObMapAssoc* [m_HashTableSize];
  m_RecordCount   = 0;
  memset(m_ppHashTable, 0, sizeof(CObMapAssoc*) * m_HashTableSize);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::InitHashTable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - bool Lookup (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
bool CObBaseRecordMap<TKey, TRecord, TKeyArg>::Lookup (TKeyArg Key, TRecord*& pRecord) {
  CObMapAssoc* pAssoc;
  dword        Hash;

  pAssoc = GetAssocNode(Key, Hash);

  if (pAssoc == NULL) {
    pRecord = NULL;
    return (false);
   }

  pRecord = pAssoc->Value;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::Lookup()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void RemoveAll (void);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
void CObBaseRecordMap<TKey, TRecord, TKeyArg>::RemoveAll (void) {
  CObMapAssoc*	pAssoc;
  CObMapAssoc*	pAssoc1;
  dword		Index;

	/* Delete all records in the table */
  if (m_ppHashTable != NULL) {
    for (Index = 0; Index < m_HashTableSize; ++Index) {
      for (pAssoc = m_ppHashTable[Index]; pAssoc != NULL; ) {
        pAssoc1 = pAssoc->pNext;
        OBMAP_DELETENODE(pAssoc);
        pAssoc = pAssoc1;
       }
     }

    delete[] m_ppHashTable;
    m_ppHashTable = NULL;
   }

  m_RecordCount = 0;

	/* Allocate all nodes in blocks */
  DestroyBlocks();
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::RemoveAll()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObBaseRecordMap Method - void SetAt (Key, pRecord);
 *
 *=========================================================================*/
template<class TKey, class TRecord, class TKeyArg>
void CObBaseRecordMap<TKey, TRecord, TKeyArg>::SetAt (TKeyArg Key, TRecord* pRecord) {
  CObMapAssoc* pAssoc;
  dword        Hash;

	/* Only add valid records */
  if (!IsValidRecord(pRecord)) return;

	/* Find an existing node */
  pAssoc = GetAssocNode(Key, Hash);

  if (pAssoc == NULL) {
    if (m_ppHashTable == NULL) InitHashTable(m_HashTableSize);

    pAssoc = CreateAssocNode();
    pAssoc->HashValue = Hash;

    pAssoc->pNext       = m_ppHashTable[Hash];
    m_ppHashTable[Hash] = pAssoc;
    ++m_RecordCount;
   }

  pAssoc->Value = pRecord;
 }
/*===========================================================================
 *		End of Class Method CObBaseRecordMap::SetAt()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Default Hash Map Implementations
 *
 *=========================================================================*/

	/* Uses the lowest 24 bits of the form ID */
class CObFormIdRecordMap : public CObBaseRecordMap<obformid_t, CObRecord, obformid_t> {

protected:

	/* Compare two keys */
  virtual bool CompareKeys (CObRecord* Record1, CObRecord* Record2);
  virtual bool CompareKeys (CObRecord* Record,  obformid_t Key);


public:

	/* Delete record from the map */
  void Delete (CObRecord* pRecord);

	/* Compute a hash from a record key */
  dword HashKey (CObRecord* pRecord);
  dword HashKey (obformid_t     Key);

	/* Check if a record is valid and can be added to map */
  bool IsValidRecord (CObRecord* pRecord);

	/* Set a value */
  void SetAt (CObRecord* pRecord);

 };


	/* Uses the full form id */
class CObFullFormIdRecordMap : public CObFormIdRecordMap {

protected:

	/* Compare two keys */
  virtual bool CompareKeys (CObRecord* Record1, CObRecord* Record2);
  virtual bool CompareKeys (CObRecord* Record,  obformid_t Key);


public:

  	/* Compute a hash from a record key */
  dword HashKey (CObRecord* pRecord);
  dword HashKey (obformid_t Key);

 };


class CObEditorIdRecordMap : public CObBaseRecordMap<CSString, CObIdRecord, const SSCHAR *> {

protected:

	/* Compare two string keys */
  virtual bool CompareKeys (const SSCHAR* Key1,    const SSCHAR* Key2);
  virtual bool CompareKeys (CObIdRecord*  Record1, CObIdRecord*  Record2);
  virtual bool CompareKeys (CObIdRecord*  Record,  const SSCHAR* Key);


public:

	/* Delete record from the map */
  void Delete (CObIdRecord* pRecord);

	/* Compute a hash from a string key */
  dword HashKey (const SSCHAR* Key);
  dword HashKey (CObIdRecord*  pRecord);

	/* Check if a record is valid and can be added to map */
  bool IsValidRecord (CObIdRecord* pRecord);

  	/* Set a value */
  void SetAt (CObIdRecord* pRecord);

 };
/*===========================================================================
 *		End of Default Hash Map Implementations
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditorIdRecordMap Method - bool CompareKeys (Key1, Key2);
 *
 *=========================================================================*/
inline bool CObFormIdRecordMap::CompareKeys (CObRecord* Record1, CObRecord*  Record2) {
  return ((Record1->GetFormID() & 0x00FFFFFF) == (Record2->GetFormID() & 0x00FFFFFF));
 }


inline bool CObFormIdRecordMap::CompareKeys (CObRecord* Record, obformid_t Key) {
  return ((Record->GetFormID() & 0x00FFFFFF) == (Key & 0x00FFFFFF));
 }


inline bool CObFullFormIdRecordMap::CompareKeys (CObRecord* Record1, CObRecord*  Record2) {
  return (Record1->GetFormID() == Record2->GetFormID());
 }


inline bool CObFullFormIdRecordMap::CompareKeys (CObRecord* Record, obformid_t Key) {
  return (Record->GetFormID() == Key);
 }



inline bool CObEditorIdRecordMap::CompareKeys (const SSCHAR* Key1, const SSCHAR* Key2) {
  return (stricmp(Key1, Key2) == 0);
 }


inline bool CObEditorIdRecordMap::CompareKeys (CObIdRecord* Record1, CObIdRecord* Record2) {
  return (stricmp(Record1->GetEditorID(), Record2->GetEditorID()) == 0);
 }


inline bool CObEditorIdRecordMap::CompareKeys (CObIdRecord* Record, const SSCHAR* Key) {
  return (stricmp(Record->GetEditorID(), Key) == 0);
 }
/*===========================================================================
 *		End of Class Method dword CObEditorIdRecordMap::CompareKeys()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditorIdRecordMap Method - void Delete (pRecord);
 *
 *=========================================================================*/
inline void CObEditorIdRecordMap::Delete (CObIdRecord* Record) {
  if (Record != NULL) CObBaseRecordMap<CSString, CObIdRecord, const SSCHAR *>::Delete(Record->GetEditorID(), Record);
 }

inline void CObFormIdRecordMap::Delete (CObRecord* Record) {
  if (Record != NULL) CObBaseRecordMap<obformid_t, CObRecord, obformid_t>::Delete(Record->GetFormID(), Record);
 }
/*===========================================================================
 *		End of Class Method dword CObEditorIdRecordMap::Delete()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditorIdRecordMap Method - dword HashKey (Key);
 *
 * Specific implementations for hashing keys.
 *
 *=========================================================================*/
inline dword CObEditorIdRecordMap::HashKey (const SSCHAR* Key) {
  dword nHash = 0;

  while (*Key) {
    nHash = (nHash << 5) + nHash + tolower(*Key);
    ++Key;
   }

  return nHash;
 }


inline dword CObEditorIdRecordMap::HashKey (CObIdRecord* pRecord) {
  return HashKey(pRecord->GetEditorID());
 }


inline dword CObFormIdRecordMap::HashKey (CObRecord* pRecord) {
  return ((dword) (pRecord->GetFormID() & 0x00FFFFFF)) >> 4;
 }


inline dword CObFormIdRecordMap::HashKey (obformid_t Key) {
   return ((dword) (Key & 0x00FFFFFF)) >> 4;
 }


inline dword CObFullFormIdRecordMap::HashKey (CObRecord* pRecord) {
  return ((dword) pRecord->GetFormID()) >> 4;
 }


inline dword CObFullFormIdRecordMap::HashKey (obformid_t Key) {
   return ((dword) Key) >> 4;
 }
/*===========================================================================
 *		End of Class Method dword CObEditorIdRecordMap::HashKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEditorIdRecordMap Method - bool IsValidRecord (pRecord);
 *
 *=========================================================================*/	
inline bool CObFormIdRecordMap::IsValidRecord (CObRecord* pRecord) { 
  return (pRecord != NULL && pRecord->GetFormID() != 0); 
 }


inline bool CObEditorIdRecordMap::IsValidRecord (CObIdRecord* pRecord) { 
  return (pRecord != NULL && pRecord->GetEditorID() != NULL && pRecord->GetEditorID()[0] != NULL_CHAR); 
 }
/*===========================================================================
 *		End of Class Method dword CObEditorIdRecordMap::HashKey()
 *=========================================================================*/


/*===========================================================================
 *
 * Class void CObEditorIdRecordMap Method - inline SetAt (pRecord);
 *
 *=========================================================================*/
inline void CObFormIdRecordMap::SetAt (CObRecord* pRecord) {
  CObBaseRecordMap<obformid_t, CObRecord, obformid_t>::SetAt(pRecord->GetFormID(), pRecord);
 }


inline void CObEditorIdRecordMap::SetAt (CObIdRecord* pRecord) {
  //CObIdRecord* pIdRecord;

  //if (pRecord == NULL) return;
  //pIdRecord = ObCastClass(CObIdRecord, pRecord);
  //if (pIdRecord != NULL) 
  CObBaseRecordMap<CSString, CObIdRecord, const SSCHAR *>::SetAt(pRecord->GetEditorID(), pRecord);
 }
/*===========================================================================
 *		End of Class Method void CObEditorIdRecordMap::SetAt()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbaserecordmap.H
 *=========================================================================*/
