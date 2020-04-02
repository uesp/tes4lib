/*===========================================================================
 *
 * File:	ObFactRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObFactRecord class for creature reference records.
 *
 *=========================================================================*/
#ifndef __OBFACTRECORD_H
#define __OBFACTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obxnamsubrecord.h"
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
 * Begin Class CObFactRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObFactRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObFactRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFactRecord();
  //virtual ~CObFactRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObFactRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObFactRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObFactRecord.H
 *=========================================================================*/
