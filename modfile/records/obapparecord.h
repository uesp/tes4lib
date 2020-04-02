/*===========================================================================
 *
 * File:	Obapparecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObAppaRecord class for apparatus data.
 *
 *=========================================================================*/
#ifndef __OBAPPARECORD_H
#define __OBAPPARECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obstringsubrecord.h"
  #include "../subrecords/obappadatasubrecord.h"
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
 * Begin Class CObAppaRecord Definition
 *
 * Holds book data.
 *
 *=========================================================================*/
class CObAppaRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObAppaRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObAppaDataSubrecord* m_pAppaData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObAppaRecord();
  //virtual ~CObAppaRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObAppaRecord; }

	/* Get class members */
  obappadata_t* GetAppaData (void) { return (m_pAppaData ? &m_pAppaData->GetAppaData() : NULL); }
  float         GetWeight   (void) { return (m_pAppaData ?  m_pAppaData->GetWeight()   : 0.0f); }
  float         GetQuality  (void) { return (m_pAppaData ?  m_pAppaData->GetQuality()   : 0.0f); }
  dword         GetValue    (void) { return (m_pAppaData ?  m_pAppaData->GetValue()    : 0); }
  byte		GetType     (void) { return (m_pAppaData ?  m_pAppaData->GetType()     : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight  (const float Value) { if (m_pAppaData != NULL) m_pAppaData->SetWeight(Value); }
  void SetQuality (const float Value) { if (m_pAppaData != NULL) m_pAppaData->SetQuality(Value); }
  void SetValue   (const dword Value) { if (m_pAppaData != NULL) m_pAppaData->SetValue(Value); }
  void SetType    (const byte  Value) { if (m_pAppaData != NULL) m_pAppaData->SetType(Value); }    

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldQuality)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldType)
 };
/*===========================================================================
 *		End of Class CObAppaRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObAppaRecord.H
 *=========================================================================*/
