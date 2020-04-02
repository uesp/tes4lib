/*===========================================================================
 *
 * File:	ObPgrdRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Defines the CObPgrdRecord class for magic effect records.
 *
 *=========================================================================*/
#ifndef __OBPGRDRECORD_H
#define __OBPGRDRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
  #include "../subrecords/obpgrlsubrecord.h"
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
 * Begin Class CObPgrdRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObPgrdRecord : public CObRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObPgrdRecord, CObRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPgrdRecord();
  //virtual ~CObPgrdRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObPgrdRecord; }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObPgrdRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAcreRecord.H
 *=========================================================================*/
