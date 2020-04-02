/*===========================================================================
 *
 * File:	ObFlorRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Defines the CObFlorRecord class for activator records.
 *
 *=========================================================================*/
#ifndef __OBFLORRECORD_H
#define __OBFLORRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obpfpcsubrecord.h"
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
 * Begin Class CObFlorRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObFlorRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObFlorRecord, CObItem1Record)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObPfpcSubrecord*	m_pData;
  CObFormidSubrecord*	m_pIngrediant;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFlorRecord();
  //virtual ~CObFlorRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObFlorRecord; }

	/* Get class members */
  byte       GetSpring     (void) { return (m_pData ? m_pData->GetSpring() : 0); }
  byte       GetSummer     (void) { return (m_pData ? m_pData->GetSummer() : 0); }
  byte       GetFall       (void) { return (m_pData ? m_pData->GetFall()   : 0); }
  byte       GetWinter     (void) { return (m_pData ? m_pData->GetWinter() : 0); }
  obformid_t GetIngrediant (void) { return (m_pIngrediant ? m_pIngrediant->GetValue() : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetSpring     (const byte Value) { if (m_pData != NULL) m_pData->SetSpring(Value); }
  void SetSummer     (const byte Value) { if (m_pData != NULL) m_pData->SetSummer(Value); }
  void SetFall       (const byte Value) { if (m_pData != NULL) m_pData->SetFall(Value); }
  void SetWinter     (const byte Value) { if (m_pData != NULL) m_pData->SetWinter(Value); }
  void SetIngrediant (const obformid_t Value);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldIngrediant)
  DECLARE_OBFIELD(FieldIngrediantID)
  DECLARE_OBFIELD(FieldSummer)
  DECLARE_OBFIELD(FieldSpring)
  DECLARE_OBFIELD(FieldFall)
  DECLARE_OBFIELD(FieldWinter)

};
/*===========================================================================
 *		End of Class CObFlorRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObActiRecord.H
 *=========================================================================*/
