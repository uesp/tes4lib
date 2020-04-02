/*===========================================================================
 *
 * File:	ObStatRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Defines the CObStatRecord class for miscitem records.
 *
 *=========================================================================*/
#ifndef __OBSTATRECORD_H
#define __OBSTATRECORD_H


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
 * Begin Class CObStatRecord Definition
 *
 *=========================================================================*/
class CObStatRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObStatRecord, CObIdRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObStringSubrecord*	m_pModel;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObStatRecord();
  //virtual ~CObStatRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObStatRecord; }

	/* Get class members */
  const char* GetModel (void) { return (m_pModel ? m_pModel->GetString().c_str() : ""); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetModel (const char* pString);
  
	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldModel)

};
/*===========================================================================
 *		End of Class CObStatRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObStatRecord.H
 *=========================================================================*/
