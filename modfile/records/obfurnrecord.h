/*===========================================================================
 *
 * File:	ObFurnRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Defines the CObFurnRecord class
 *
 *=========================================================================*/
#ifndef __OBFURNRECORD_H
#define __OBFURNRECORD_H


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
 * Begin Class CObFurnRecord Definition
 *
 *=========================================================================*/
class CObFurnRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObFurnRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObDwordSubrecord*	m_pMarkers;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFurnRecord();
  //virtual ~CObFurnRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObFurnRecord; }

	/* Get class members */
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  
	/* Begin field method definitions */
  //DECLARE_OBFIELD(FieldWeight)

};
/*===========================================================================
 *		End of Class CObFurnRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File ObFurnRecord.H
 *=========================================================================*/
