/*===========================================================================
 *
 * File:	Obtypegroup.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObTypeGroup for handling type groups.
 *
 *=========================================================================*/
#ifndef __OBTYPEGROUP_H
#define __OBTYPEGROUP_H


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
 * Begin Class CObTypeGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObTypeGroup : public CObGroup {
  DECLARE_OBCLASS(CObTypeGroup, CObGroup)

  /*---------- Begin Private Class Members ----------------------*/
private:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObTypeGroup(const bool UseRef = false) : CObGroup(UseRef) { }
  //virtual ~CObTypeGroup() { Destroy(); }
  //virtual void Destroy (void);

	/* Attempt to add a child record */
  bool AddChildRecord (CObBaseRecord* pNewRecord);
  //bool IsValidChild   (CObBaseRecord* pNewRecord);

	/* Delete a child record */
  bool DeleteChildRecord (CObBaseRecord* pRecord);

	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObTypeGroup); }

	/* Get class members */
  const obrectype_t GetContainsType (void) const { return (m_Header.Data.ContainsType); }

	/* Get class members */
  void SetContainsType (const obrectype_t Type) { memcpy(m_Header.Data.ContainsType, Type.Name, OB_RECTYPE_SIZE); }

 };
/*===========================================================================
 *		End of Class CObTypeGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefTypeGroup : public CObTypeGroup {

public:

  CObRefTypeGroup() : CObTypeGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefTypeGroup); }

  
};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obtypegroup.H
 *=========================================================================*/
