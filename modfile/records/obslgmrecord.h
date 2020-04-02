/*===========================================================================
 *
 * File:	ObSlgmrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 11, 2006
 *
 * Defines the CObSlgmRecord class for soul gem records.
 *
 *=========================================================================*/
#ifndef __OBSLGMRECORD_H
#define __OBSLGMRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obslgmdatasubrecord.h"
  #include "../subrecords/obbytesubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSlgmRecord Definition
 *
 *=========================================================================*/
class CObSlgmRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObSlgmRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObSlgmDataSubrecord*	m_pSoulGemData;
  CObByteSubrecord*	m_pCapacity;
  CObByteSubrecord*	m_pSoul;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSlgmRecord();
  //virtual ~CObSlgmRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObSlgmRecord; }

	/* Get class members */
  obslgmdata_t* GetSoulGemData (void) { return (m_pSoulGemData ? &m_pSoulGemData->GetSoulGemData() : NULL); }
  float         GetWeight      (void) { return (m_pSoulGemData ?  m_pSoulGemData->GetWeight()   : 0.0f); }
  dword         GetValue       (void) { return (m_pSoulGemData ?  m_pSoulGemData->GetValue()    : 0); }
  byte		GetCapacity    (void) { return (m_pCapacity    ?  m_pCapacity->GetValue()       : 0); }
  byte		GetSoul        (void) { return (m_pSoul        ?  m_pSoul->GetValue()           : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight   (const float Value) { if (m_pSoulGemData != NULL) m_pSoulGemData->SetWeight(Value); }
  void SetValue    (const dword Value) { if (m_pSoulGemData != NULL) m_pSoulGemData->SetValue(Value); }
  void SetCapacity (const byte  Value) { if (m_pCapacity    != NULL) m_pCapacity->SetValue(Value); }
  void SetSoul     (const byte  Value) { if (m_pSoul        != NULL) m_pSoul->SetValue(Value); }
  
	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldCapacity)
  DECLARE_OBFIELD(FieldSoul)

};
/*===========================================================================
 *		End of Class CObSlgmRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObSlgmRecord.H
 *=========================================================================*/
