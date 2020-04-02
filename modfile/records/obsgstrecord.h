/*===========================================================================
 *
 * File:	ObSgstRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Defines the CObSgstRecord class for ingrediant records.
 *
 *=========================================================================*/
#ifndef __OBSGSTRECORD_H
#define __OBSGSTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obeffitemrecord.h"
  #include "../subrecords/obsgstdatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSgstRecord Definition
 *
 * Holds sigil stone record data.
 *
 *=========================================================================*/
class CObSgstRecord : public CObEffectItemRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObSgstRecord, CObEffectItemRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObSgstDataSubrecord*	m_pSigilData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSgstRecord();
  //virtual ~CObSgstRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObSgstRecord; }

	/* Get class members */
  obsgstdata_t* GetSigilData (void) { return (m_pSigilData ? &m_pSigilData->GetSigilData() : NULL); }
  float		GetWeight    (void) { return (m_pSigilData ?  m_pSigilData->GetWeight()    : 0); }
  dword		GetValue     (void) { return (m_pSigilData ?  m_pSigilData->GetValue()     : 0); }
  byte		GetUses      (void) { return (m_pSigilData ?  m_pSigilData->GetUses()      : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetWeight   (const float Value) { if (m_pSigilData != NULL) m_pSigilData->SetWeight(Value); }
  void SetValue    (const dword Value) { if (m_pSigilData != NULL) m_pSigilData->SetValue(Value); }
  void SetUses     (const byte  Value) { if (m_pSigilData != NULL) m_pSigilData->SetUses(Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldUses)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldWeight)

 };
/*===========================================================================
 *		End of Class CObSgstRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObSgstRecord.H
 *=========================================================================*/
