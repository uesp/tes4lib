/*===========================================================================
 *
 * File:	ObActiRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObActiRecord class for activator records.
 *
 *=========================================================================*/
#ifndef __OBACTIRECORD_H
#define __OBACTIRECORD_H


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
 * Begin Class CObActiRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObActiRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObActiRecord, CObItem1Record)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFormidSubrecord*	m_pSound;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObActiRecord();
  //virtual ~CObActiRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObActiRecord; }

	/* Get class members */
  obformid_t GetSound (void) { return (m_pSound ? m_pSound->GetValue() : OB_FORMID_NULL); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set the activator sound */
  void SetSound (const obformid_t FormID);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldSound);
  DECLARE_OBFIELD(FieldSoundID);
  
};
/*===========================================================================
 *		End of Class CObActiRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObActiRecord.H
 *=========================================================================*/
