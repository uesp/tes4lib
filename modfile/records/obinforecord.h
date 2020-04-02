/*===========================================================================
 *
 * File:	ObInfoRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Defines the CObInfoRecord class for dialogue info records.
 *
 *=========================================================================*/
#ifndef __OBINFORECORD_H
#define __OBINFORECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obctdtsubrecord.h"
  #include "../subrecords/obctdasubrecord.h"
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
 * Begin Class CObInfoRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObInfoRecord : public CObRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObInfoRecord, CObRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObInfoRecord();
  //virtual ~CObInfoRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObInfoRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObInfoRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAcreRecord.H
 *=========================================================================*/
