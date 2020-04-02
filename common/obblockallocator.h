/*===========================================================================
 *
 * File:	Obblockallocator.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 19, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBLOCKALLOCATOR_H
#define __OBBLOCKALLOCATOR_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "oberrorhandler.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default block size */
  #define OBBLOCK_DEFAULT_BLOCKSIZE 10000

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Template TObBlockAllocator Definition
 *
 *=========================================================================*/
template <class TClass>
class TObBlockAllocator {

	/* Internal structure that maintains a linked list of allocated blocks */
  struct TObBlock {
	TClass*		pNodes;
	dword		NextFreeIndex;
	TObBlock*	pNextBlock;
  };


  /*---------- Begin Protected Class Members ---------------------------*/
protected:
  TObBlock*	m_pHeadBlock;
  TObBlock*	m_pFreeBlocks;

  dword		m_BlockSize;		/* Number of elements allocated per block */


	/* Clears the content in the given block */
  void DestroyBlockContent (TObBlock* pBlock);


  /*---------- Begin Public Class Methods ------------------------------*/
public:

	/* Constructor/Destructor */
  TObBlockAllocator (const dword BlockSize = OBBLOCK_DEFAULT_BLOCKSIZE);
  ~TObBlockAllocator() { DestroyBlocks(); }
  void Destroy (void);
  void DestroyBlocks (void);

	/* Create a new object of the templated class */
  TClass* CreateObject (void);

};
/*===========================================================================
 *		End of Template TObBlockAllocator Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObBlockAllocator Constructor
 *
 *=========================================================================*/
template<class TClass>
TObBlockAllocator<TClass>::TObBlockAllocator (const dword BlockSize) {
  m_BlockSize   = BlockSize;
  m_pHeadBlock  = NULL;
  m_pFreeBlocks = NULL;
}
/*===========================================================================
 *		End of Class TObBlockAllocator Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObBlockAllocator Method - void Destroy (void);
 *
 *=========================================================================*/
template<class TClass>
void TObBlockAllocator<TClass>::Destroy (void) {
  TObBlock* pBlock = m_pHeadBlock;
  TObBlock* pNextBlock;
  
  while (pBlock != NULL) {
    DestroyBlockContent(pBlock);

    pNextBlock = pBlock->pNextBlock;

    pBlock->pNextBlock = m_pFreeBlocks;
    m_pFreeBlocks      = pBlock;

    pBlock = pNextBlock;
  }

  m_pHeadBlock = NULL;
}
/*===========================================================================
 *		End of Class Method TObBlockAllocator::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObBlockAllocator Method - void DestroyBlocks (void);
 *
 *=========================================================================*/
template<class TClass>
void TObBlockAllocator<TClass>::DestroyBlocks (void) {
  TObBlock* pBlock     = m_pHeadBlock;
  TObBlock* pNextBlock;

  while (pBlock != NULL) {
    delete[] pBlock->pNodes;

    pNextBlock = pBlock->pNextBlock;
    delete pBlock;
    pBlock = pNextBlock;
  }

  m_pHeadBlock = NULL;

  pBlock = m_pFreeBlocks;

  while (pBlock != NULL) {
    delete[] pBlock->pNodes;

    pNextBlock = pBlock->pNextBlock;
    delete pBlock;
    pBlock = pNextBlock;
  }

  m_pFreeBlocks = NULL;
}
/*===========================================================================
 *		End of Class Method TObBlockAllocator::DestroyBlocks()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObBlockAllocator Method - void Destroy (void);
 *
 *=========================================================================*/
template<class TClass>
void TObBlockAllocator<TClass>::DestroyBlockContent (TObBlock* pBlock) {
  dword Index;

  if (pBlock == NULL) return;

  for (Index = 0; Index < m_BlockSize; ++Index) {
    pBlock->pNodes[Index].Destroy();
  }

}
/*===========================================================================
 *		End of Class Method TObBlockAllocator::DestroyBlockContent()
 *=========================================================================*/


/*===========================================================================
 *
 * Class TObBlockAllocator Method - void CreateObject (void);
 *
 *=========================================================================*/
template<class TClass>
TClass* TObBlockAllocator<TClass>::CreateObject (void) {
  TClass*   pNewObject;
  
  if (m_pHeadBlock == NULL || m_pHeadBlock->NextFreeIndex >= m_BlockSize) {
    TObBlock* pNewBlock;

    if (m_pFreeBlocks == NULL) {
      pNewBlock = new TObBlock;
    }
    else {
      pNewBlock = m_pFreeBlocks;
      m_pFreeBlocks = m_pFreeBlocks->pNextBlock;
    }

    pNewBlock->NextFreeIndex = 0;
    pNewBlock->pNodes        = new TClass[m_BlockSize];
    pNewBlock->pNextBlock    = m_pHeadBlock;
    m_pHeadBlock = pNewBlock;
  }

  pNewObject = &(m_pHeadBlock->pNodes[m_pHeadBlock->NextFreeIndex]);
  ++m_pHeadBlock->NextFreeIndex;

  return (pNewObject);
}
/*===========================================================================
 *		End of Class Method TObBlockAllocator::CreateObject()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obblockallocator.H
 *=========================================================================*/
