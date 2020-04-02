/*===========================================================================
 *
 * File:	ObBsgnRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObBsgnRecord class for reference records.
 *
 *=========================================================================*/
#ifndef __OBBSGNRECORD_H
#define __OBBSGNRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obwordsubrecord.h"
  #include "../subrecords/obformidsubrecord.h"
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
 * Begin Class CObBsgnRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObBsgnRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObBsgnRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFullSubrecord*	m_pFullName;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBsgnRecord();
  //virtual ~CObBsgnRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObBsgnRecord; }

	/* Get class members */
  const SSCHAR* GetFullName (void) { return (m_pFullName ? m_pFullName->GetString().c_str() : ""); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetFullName (const SSCHAR* pString);

	/* Begin field method definitions */
  
};
/*===========================================================================
 *		End of Class CObBsgnRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObBsgnRecord.H
 *=========================================================================*/
