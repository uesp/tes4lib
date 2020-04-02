/*===========================================================================
 *
 * File:	Obbookrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObBookRecord class for book records.
 *
 *=========================================================================*/
#ifndef __OBBOOKRECORD_H
#define __OBBOOKRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem2record.h"
  #include "../subrecords/obbookdatasubrecord.h"
  #include "../subrecords/obstringsubrecord.h"
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
 * Begin Class CObBookRecord Definition
 *
 * Holds book data.
 *
 *=========================================================================*/
class CObBookRecord : public CObItem2Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObBookRecord, CObItem2Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObBookDataSubrecord*	m_pBookData;
  CObStringSubrecord*   m_pText;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBookRecord();
  //virtual ~CObBookRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObBookRecord; }

	/* Get class members */
  obbookdata_t* GetBookData (void) { return (m_pBookData ? &m_pBookData->GetBookData()   : NULL); }
  float         GetWeight   (void) { return (m_pBookData ?  m_pBookData->GetWeight()     : 0.0f); }
  dword         GetValue    (void) { return (m_pBookData ?  m_pBookData->GetValue()      : 0); }
  int           GetTeaches  (void) { return (m_pBookData ?  m_pBookData->GetTeaches()    : -1); }    
  const SSCHAR* GetBookText (void) { return (m_pText     ?  m_pText->GetString().c_str() : ""); }
  bool          IsNoTake    (void) { return (m_pBookData ?  m_pBookData->IsNoTake()      : false); }
  bool          IsScroll    (void) { return (m_pBookData ?  m_pBookData->IsScroll()      : false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight     (const float Value) { if (m_pBookData != NULL) m_pBookData->SetWeight(Value); }
  void SetValue      (const dword Value) { if (m_pBookData != NULL) m_pBookData->SetValue(Value); }
  void SetTeaches    (const dword Value) { if (m_pBookData != NULL) m_pBookData->SetTeaches(Value); }
  void SetNoTake     (const bool Flag)   { if (m_pBookData != NULL) m_pBookData->SetNoTake(Flag); }
  void SetIsScroll   (const bool Flag)   { if (m_pBookData != NULL) m_pBookData->SetIsScroll(Flag); }
  void SetBookText   (const SSCHAR* pString);

	/* Field get methods */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldTeaches)
  DECLARE_OBFIELD(FieldNoTake)
  DECLARE_OBFIELD(FieldIsScroll)
  DECLARE_OBFIELD(FieldBookText)
 };
/*===========================================================================
 *		End of Class CObAmmoRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obbookrecord.H
 *=========================================================================*/
