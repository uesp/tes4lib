/*===========================================================================
 *
 * File:	ObQustRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Defines the CObQustRecord class.
 *
 *=========================================================================*/
#ifndef __OBQUSTRECORD_H
#define __OBQUSTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obctdasubrecord.h"
  #include "../subrecords/obctdtsubrecord.h"
  #include "../subrecords/obqstasubrecord.h"
  #include "../subrecords/obscrosubrecord.h"
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
 * Begin Class CObQustRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObQustRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObQustRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObQustRecord();
  //virtual ~CObQustRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObQustRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObQustRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObPackRecord.H
 *=========================================================================*/
