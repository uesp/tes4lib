/*===========================================================================
 *
 * File:	ObDialRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObDialRecord class.
 *
 *=========================================================================*/
#ifndef __OBDIALRECORD_H
#define __OBDIALRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
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
 * Begin Class CObDialRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObDialRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObDialRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObDialRecord();
  //virtual ~CObDialRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObDialRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObDialRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAnioRecord.H
 *=========================================================================*/
