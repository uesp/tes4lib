/*===========================================================================
 *
 * File:	Obitem2record.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObItem2Record class for records with:
 *
 *	ANAM - Enchantment pts
 *	ENAM - Enchantment formid
 *
 * In addition to all standard CObItem1Record subrecords.
 *
 *=========================================================================*/
#ifndef __OBITEM2RECORD_H
#define __OBITEM2RECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obwordsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObItem2Record Definition
 *
 *=========================================================================*/
class CObItem2Record : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObItem2Record, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFormidSubrecord* m_pEnchantment;
  CObWordSubrecord*   m_pEnchantPoints;

  CSString	      m_CachedEnchantID;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObItem2Record();
  //virtual ~CObItem2Record() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObItem2Record; }

	/* Get class members */
  obformid_t    GetEnchantment     (void) { return (m_pEnchantment   ? m_pEnchantment->GetValue()   : OB_FORMID_NULL); }
  word          GetEnchantPoints   (void) { return (m_pEnchantPoints ? m_pEnchantPoints->GetValue() : 0); }
  const SSCHAR* GetEnchantEditorID (void);
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetEnchantment   (const obformid_t FormID);
  void SetEnchantPoints (const word       Points);
  
  	/* Field get methods */
  DECLARE_OBFIELD(FieldEnchantment)
  DECLARE_OBFIELD(FieldEnchantPoints)
  DECLARE_OBFIELD(FieldEnchantmentID)
 };
/*===========================================================================
 *		End of Class CObItem2Record Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obitem2record.H
 *=========================================================================*/
