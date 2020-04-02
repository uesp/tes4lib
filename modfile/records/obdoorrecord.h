/*===========================================================================
 *
 * File:	ObDoorRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObDoorRecord class for activator records.
 *
 *=========================================================================*/
#ifndef __OBDOORRECORD_H
#define __OBDOORRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
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
 * Begin Class CObDoorRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObDoorRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObDoorRecord, CObItem1Record)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObDoorRecord();
  //virtual ~CObDoorRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObDoorRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObDoorRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObActiRecord.H
 *=========================================================================*/
