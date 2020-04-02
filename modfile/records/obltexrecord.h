/*===========================================================================
 *
 * File:	ObLtexRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Defines the CObLtexRecord class for land texture records.
 *
 *=========================================================================*/
#ifndef __OBLTEXRECORD_H
#define __OBLTEXRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
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
 * Begin Class CObLtexRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObLtexRecord : public CObRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObLtexRecord, CObRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLtexRecord();
  //virtual ~CObLtexRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObLtexRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObLtexRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAcreRecord.H
 *=========================================================================*/
