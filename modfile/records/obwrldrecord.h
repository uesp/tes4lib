/*===========================================================================
 *
 * File:	ObWrldRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObWrldRecord class for worldspace records.
 *
 *=========================================================================*/
#ifndef __OBWRLDRECORD_H
#define __OBWRLDRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
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
 * Begin Class CObWrldRecord Definition
 *
 * Holds worldspace data.
 *
 *=========================================================================*/
class CObWrldRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObWrldRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFullSubrecord*	m_pFullName;
  //CObRefrDataSubrecord* m_pData;
  //CObXtelSubrecord*	m_pTeleport;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObWrldRecord();
  //virtual ~CObWrldRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObWrldRecord; }

	/* Get class members */
  const SSCHAR* GetFullName (void) { return (m_pFullName ? m_pFullName->GetString().c_str() : ""); }
  
	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (true); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetFullName (const SSCHAR* pString);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldFullName)

 };
/*===========================================================================
 *		End of Class CObWrldRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObWrldRecord.H
 *=========================================================================*/
