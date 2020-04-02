/*===========================================================================
 *
 * File:	ObIdleRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObIdleRecord class for idle animation ecords.
 *
 *=========================================================================*/
#ifndef __OBIDLERECORD_H
#define __OBIDLERECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obidledatasubrecord.h"
  #include "../subrecords/obctdasubrecord.h"
  #include "../subrecords/obctdtsubrecord.h"
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
 * Begin Class CObIdleRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObIdleRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObIdleRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObIdleRecord();
  //virtual ~CObIdleRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObIdleRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObIdleRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAcreRecord.H
 *=========================================================================*/
