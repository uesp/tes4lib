/*===========================================================================
 *
 * File:	ObKeymRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 10, 2006
 *
 * Defines the CObKeymRecord class for key data.
 *
 *=========================================================================*/
#ifndef __OBKEYMRECORD_H
#define __OBKEYMRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obstringsubrecord.h"
  #include "../subrecords/obkeymdatasubrecord.h"
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
 * Begin Class CObKeymRecord Definition
 *
 * Holds book data.
 *
 *=========================================================================*/
class CObKeymRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObKeymRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObKeymDataSubrecord* m_pKeyData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObKeymRecord();
  //virtual ~CObKeymRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObKeymRecord; }

	/* Get class members */
  obkeydata_t*  GetKeyData  (void) { return (m_pKeyData ? &m_pKeyData->GetKeyData()  : NULL); }
  float         GetWeight   (void) { return (m_pKeyData ?  m_pKeyData->GetWeight()   : 0.0f); }
  dword         GetValue    (void) { return (m_pKeyData ?  m_pKeyData->GetValue()    : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight  (const float Value) { if (m_pKeyData != NULL) m_pKeyData->SetWeight(Value); }
  void SetValue   (const dword Value) { if (m_pKeyData != NULL) m_pKeyData->SetValue(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)

};
/*===========================================================================
 *		End of Class CObKeymRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObKeymRecord.H
 *=========================================================================*/
