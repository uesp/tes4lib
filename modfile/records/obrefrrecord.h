/*===========================================================================
 *
 * File:	ObRefrRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObRefrRecord class for reference records.
 *
 *=========================================================================*/
#ifndef __OBREFRRECORD_H
#define __OBREFRRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbaserefrrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obwordsubrecord.h"
  #include "../subrecords/obrefrdatasubrecord.h"
  #include "../subrecords/obxtelsubrecord.h"
  #include "../subrecords/obformidsubrecord.h"
  #include "../subrecords/obxespsubrecord.h"
  #include "../subrecords/obxlocsubrecord.h"
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
 * Begin Class CObRefrRecord Definition
 *
 * Holds reference data.
 *
 *=========================================================================*/
class CObRefrRecord : public CObBaseRefrRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObRefrRecord, CObBaseRefrRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFullSubrecord*	m_pItemName;
  CObXtelSubrecord*	m_pTeleport;
  CObWordSubrecord*	m_pMarkerType;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRefrRecord();
  //virtual ~CObRefrRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObRefrRecord; }

	/* Get class members */
  const SSCHAR* GetItemName       (void) { return (m_pItemName ? m_pItemName->GetString().c_str()    : ""); }
  obxteldata_t* GetTeleportData   (void) { return (m_pTeleport ? &m_pTeleport->GetXtelData() : NULL); }
  obformid_t    GetTeleportFormID (void) { return (m_pTeleport ? m_pTeleport->GetFormID()    : OB_FORMID_NULL); }
  float         GetTeleportLocX   (void) { return (m_pTeleport ? m_pTeleport->GetX()	     : 0); }
  float         GetTeleportLocY   (void) { return (m_pTeleport ? m_pTeleport->GetY()	     : 0); }
  float         GetTeleportLocZ   (void) { return (m_pTeleport ? m_pTeleport->GetZ()	     : 0); }
  float         GetTeleportAngleX (void) { return (m_pTeleport ? m_pTeleport->GetAX()	     : 0); }
  float         GetTeleportAngleY (void) { return (m_pTeleport ? m_pTeleport->GetAY()	     : 0); }
  float         GetTeleportAngleZ (void) { return (m_pTeleport ? m_pTeleport->GetAZ()	     : 0); }
  word		GetMarkerType     (void) { return (m_pMarkerType ? m_pMarkerType->GetValue() : 0); }
  virtual bool	IsMapMarker	  (void) { return (m_pMarkerType != NULL); }

	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (true); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetItemName   (const SSCHAR* pString);

	/* Begin field method definitions */
  DECLARE_OBGETFIELD(GetFieldItemName)
  DECLARE_OBGETFIELD(GetFieldTeleportFormID)
  DECLARE_OBGETFIELD(GetFieldTeleportName)
  DECLARE_OBGETFIELD(GetFieldTeleportLocX)
  DECLARE_OBGETFIELD(GetFieldTeleportLocY)
  DECLARE_OBGETFIELD(GetFieldTeleportLocZ)
  DECLARE_OBGETFIELD(GetFieldTeleportAngleX)
  DECLARE_OBGETFIELD(GetFieldTeleportAngleY)
  DECLARE_OBGETFIELD(GetFieldTeleportAngleZ)
  DECLARE_OBGETFIELD(GetFieldMarkerType)
  DECLARE_OBGETFIELD(GetFieldMarkerTypeID)

  DECLARE_OBCOMPFIELD(CompareFieldItemName)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportFormID)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportLocX)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportLocY)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportLocZ)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportAngleX)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportAngleY)
  DECLARE_OBCOMPFIELD(CompareFieldTeleportAngleZ)
  DECLARE_OBCOMPFIELD(CompareFieldMarkerType)
  DECLARE_OBCOMPFIELD(CompareFieldMarkerTypeID)

  DECLARE_OBSETFIELD(SetFieldItemName)

};
/*===========================================================================
 *		End of Class CObRefrRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRefrRecord.H
 *=========================================================================*/
