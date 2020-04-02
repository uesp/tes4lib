/*===========================================================================
 *
 * File:	Obmiscrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObMiscRecord class for miscitem records.
 *
 *=========================================================================*/
#ifndef __OBMISCRECORD_H
#define __OBMISCRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obmiscdatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObMiscRecord Definition
 *
 * Holds misc item data.
 *
 *=========================================================================*/
class CObMiscRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObMiscRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObMiscDataSubrecord*	m_pMiscData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObMiscRecord();
  //virtual ~CObMiscRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObMiscRecord; }

	/* Get class members */
  obmiscdata_t* GetMiscData (void) { return (m_pMiscData ? &m_pMiscData->GetMiscData() : NULL); }
  float         GetWeight   (void) { return (m_pMiscData ?  m_pMiscData->GetWeight()   : 0.0f); }
  dword         GetValue    (void) { return (m_pMiscData ?  m_pMiscData->GetValue()    : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight (const float Value) { if (m_pMiscData != NULL) m_pMiscData->SetWeight(Value); }
  void SetValue  (const dword Value) { if (m_pMiscData != NULL) m_pMiscData->SetValue(Value); }
  
	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)

};
/*===========================================================================
 *		End of Class CObMiscRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obmiscrecord.H
 *=========================================================================*/
