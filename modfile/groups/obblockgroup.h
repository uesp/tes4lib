/*===========================================================================
 *
 * File:	ObBlockGroup.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObBlockGroup for handling a group with a block value.
 *
 *=========================================================================*/
#ifndef __OBBLOCKGROUP_H
#define __OBBLOCKGROUP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obgroup.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBlockGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObBlockGroup : public CObGroup {
  DECLARE_OBCLASS(CObBlockGroup, CObGroup)

  /*---------- Begin Private Class Members ----------------------*/
private:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBlockGroup(const bool UseRef = false) : CObGroup(UseRef) { }
  //virtual ~CObBlockGroup() { Destroy(); }
  //virtual void Destroy (void);

	/* Attempt to add a child record */
  bool AddChildRecord (CObBaseRecord* pNewRecord) { return (false); }
  //bool IsValidChild   (CObBaseRecord* pNewRecord);

	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObBlockGroup); }

	/* Get class members */
  obformid_t GetBlock (void) const { return (m_Header.Data.Block); }

	/* Get class members */
  void SetBlock (const int Block) { m_Header.Data.Block = Block; }

 };
/*===========================================================================
 *		End of Class CObBlockGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefBlockGroup : public CObBlockGroup {

public:

  CObRefBlockGroup() : CObBlockGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefBlockGroup); }

};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File CObBlockGroup.H
 *=========================================================================*/
