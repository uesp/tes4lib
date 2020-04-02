/*===========================================================================
 *
 * File:	Obitem1record.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObItem1Record class for records with:
 *
 *	FULL - Item Name
 *	MODL - Model filename
 *	ICON - ICON filename
 *	SCRI - Script
 *
 *=========================================================================*/
#ifndef __OBITEM1RECORD_H
#define __OBITEM1RECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obformidsubrecord.h"
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
 * Begin Class CObItem1Record Definition
 *
 * Holds enchantment data.
 *
 *=========================================================================*/
class CObItem1Record : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObItem1Record, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFullSubrecord*	m_pItemName;
  CObModlSubrecord*	m_pModel;
  CObIconSubrecord*	m_pIcon;
  CObFormidSubrecord*	m_pScript;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObItem1Record();
  //virtual ~CObItem1Record() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObItem1Record; }

	/* Get class members */
  const SSCHAR* GetItemName (void) { return (m_pItemName ? m_pItemName->GetString().c_str() : ""); }
  const SSCHAR* GetModel    (void) { return (m_pModel    ? m_pModel->GetString().c_str()    : ""); }
  const SSCHAR* GetIcon     (void) { return (m_pIcon     ? m_pIcon->GetString().c_str()     : ""); }
  obformid_t    GetScript   (void) { return (m_pScript   ? m_pScript->GetValue()            : OB_FORMID_NULL); }

	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (true); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetItemName (const SSCHAR* pString);
  void SetModel    (const SSCHAR* pString);
  void SetIcon     (const SSCHAR* pString);
  void SetScript   (const obformid_t FormID);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldItemName)
  DECLARE_OBFIELD(FieldModel)
  DECLARE_OBFIELD(FieldIcon)
  DECLARE_OBFIELD(FieldScript)
  DECLARE_OBFIELD(FieldScriptID)

};
/*===========================================================================
 *		End of Class CObItem1Record Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obitem1record.H
 *=========================================================================*/
