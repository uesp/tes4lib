/*===========================================================================
 *
 * File:	ObFileGroup.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObFileGroup for handling top level records/groups in 
 * a ESP/ESM file.
 *
 *=========================================================================*/
#ifndef __OBFILEGROUP_H
#define __OBFILEGROUP_H


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
 * Begin Class CObFileGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObFileGroup : public CObGroup {
  //DECLARE_OBCLASS(CObFileGroup, CObGroup)

  /*---------- Begin Private Class Members ----------------------*/
private:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFileGroup(const bool UseRef = false) : CObGroup(UseRef) { }
  //virtual ~CObFileGroup() { Destroy(); }
  //virtual void Destroy (void);

	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObFileGroup); }

	/* Override to just output records with no group header */
  virtual bool Write (CObFile& File, CObCallback* pCallback);

 };
/*===========================================================================
 *		End of Class CObFileGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefFileGroup : public CObFileGroup {

public:

  CObRefFileGroup() : CObFileGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefFileGroup); }

};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFileGroup.H
 *=========================================================================*/
