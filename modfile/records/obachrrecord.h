/*===========================================================================
 *
 * File:	ObAchrRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObAchrRecord class for NPC reference records.
 *
 *=========================================================================*/
#ifndef __OBACHRRECORD_H
#define __OBACHRRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbaserefrrecord.h"
  #include "../subrecords/obposanglesubrecord.h"
  #include "../subrecords/obxespsubrecord.h"
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
 * Begin Class CObAchrRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObAchrRecord : public CObBaseRefrRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObAchrRecord, CObBaseRefrRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAchrRecord();
  //virtual ~CObAchrRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObAchrRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObAchrRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObBsgnRecord.H
 *=========================================================================*/
