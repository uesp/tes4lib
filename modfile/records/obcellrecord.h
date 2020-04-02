/*===========================================================================
 *
 * File:	ObCellRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObCellRecord class for cell records.
 *
 *=========================================================================*/
#ifndef __OBCELLRECORD_H
#define __OBCELLRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obformidarraysubrecord.h"
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
 * Begin Class CObCellRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObCellRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObCellRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFullSubrecord*	m_pCellName;
  //CObRefrDataSubrecord* m_pData;
  //CObXtelSubrecord*	m_pTeleport;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObCellRecord();
  //virtual ~CObCellRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObCellRecord; }

	/* Get class members */
  const SSCHAR* GetCellName (void) { return (m_pCellName ? m_pCellName->GetString().c_str() : ""); }
  
	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (true); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetCellName (const SSCHAR* pString);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldCellName)

};
/*===========================================================================
 *		End of Class CObCellRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObCellRecord.H
 *=========================================================================*/
