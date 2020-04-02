/*===========================================================================
 *
 * File:	ObPackRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 16, 2006
 *
 * Defines the CObPackRecord class.
 *
 *=========================================================================*/
#ifndef __OBPACKRECORD_H
#define __OBPACKRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obctdasubrecord.h"
  #include "../subrecords/obctdtsubrecord.h"
  #include "../subrecords/obpldtsubrecord.h"
  #include "../subrecords/obptdtsubrecord.h"
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
 * Begin Class CObPackRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObPackRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObPackRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPackRecord();
  //virtual ~CObPackRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObPackRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObPackRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObPackRecord.H
 *=========================================================================*/
