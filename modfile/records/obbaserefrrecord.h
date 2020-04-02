/*===========================================================================
 *
 * File:	ObBaseRefrRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	November 8, 2006
 *
 * Defines the CObBaseRefrRecord class for base reference records.
 *
 *=========================================================================*/
#ifndef __OBBASEREFRRECORD_H
#define __OBBASEREFRRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
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
 * Begin Class CObBaseRefrRecord Definition
 *
 *=========================================================================*/
class CObBaseRefrRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObBaseRefrRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObFormidSubrecord*	m_pName;
  CObRefrDataSubrecord* m_pData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBaseRefrRecord();
  //virtual ~CObBaseRefrRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObBaseRefrRecord; }

	/* Get class members */
  obrefrdata_t* GetRefrData       (void) { return (m_pData     ? &m_pData->GetRefrData()     : NULL); }
  float         GetLocationX      (void) { return (m_pData     ? m_pData->GetX()	     : 0); }
  float         GetLocationY      (void) { return (m_pData     ? m_pData->GetY()	     : 0); }
  float         GetLocationZ      (void) { return (m_pData     ? m_pData->GetZ()	     : 0); }
  float         GetAngleX         (void) { return (m_pData     ? m_pData->GetAX()	     : 0); }
  float         GetAngleY         (void) { return (m_pData     ? m_pData->GetAY()	     : 0); }
  float         GetAngleZ         (void) { return (m_pData     ? m_pData->GetAZ()	     : 0); }
  obformid_t	GetBaseFormID	  (void) { return (m_pName     ? m_pName->GetValue()	     : OB_FORMID_NULL); }
  virtual bool	IsMapMarker	  (void) { return (false); }
  virtual bool	IsActor           (void);
  virtual bool	IsContainer       (void);

	/* Check the form type for the reference */
  virtual bool IsFormType (const int Type);

	/* Used to determine if the record type has a FULL item name field */
  virtual bool HasFullItemName (void) { return (false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetBaseFormID (const obformid_t FormID);

	/* Begin field method definitions */
  DECLARE_OBGETFIELD(GetFieldLocationX)
  DECLARE_OBGETFIELD(GetFieldLocationY)
  DECLARE_OBGETFIELD(GetFieldLocationZ)
  DECLARE_OBGETFIELD(GetFieldAngleX)
  DECLARE_OBGETFIELD(GetFieldAngleY)
  DECLARE_OBGETFIELD(GetFieldAngleZ)
  DECLARE_OBGETFIELD(GetFieldWorldSpace)
  DECLARE_OBGETFIELD(GetFieldBaseFormID)
  DECLARE_OBGETFIELD(GetFieldBaseEditorID)
  DECLARE_OBGETFIELD(GetFieldBaseName)

  DECLARE_OBCOMPFIELD(CompareFieldLocationX)
  DECLARE_OBCOMPFIELD(CompareFieldLocationY)
  DECLARE_OBCOMPFIELD(CompareFieldLocationZ)
  DECLARE_OBCOMPFIELD(CompareFieldAngleX)
  DECLARE_OBCOMPFIELD(CompareFieldAngleY)
  DECLARE_OBCOMPFIELD(CompareFieldAngleZ)
  DECLARE_OBCOMPFIELD(CompareFieldBaseFormID)
  DECLARE_OBCOMPFIELD(CompareFieldBaseEditorID)

 };
/*===========================================================================
 *		End of Class CObBaseRefrRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObBaseRefrRecord.H
 *=========================================================================*/
