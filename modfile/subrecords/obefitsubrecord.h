/*===========================================================================
 *
 * File:	Obefitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBEFITSUBRECORD_H
#define __OBEFITSUBRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Standard EFIT subrecord size in bytes */
  #define OBEFIT_SUBRECORD_SIZE	0x18

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* ENIT data structure */
  struct obefitdata_t {
	obrectype_t Name;
	dword	    Magnitude;
	dword	    Area;
	dword	    Duration;
	dword       Type;
	dword       ActorValue;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEfitSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObEfitSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObEfitSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obefitdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBEFIT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBEFIT_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEfitSubrecord();
  //virtual ~CObEfitSubrecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObEfitSubrecord* pSubrecord1 = ObCastClassNull(CObEfitSubrecord, pSubrecord);
	m_RecordSize = OBEFIT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetEffectData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}

	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObEfitSubrecord); }

	/* Get class members */
  obefitdata_t& GetEffectData (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  obrectype_t   GetEffectName (void) { return (m_Data.Name); }
  dword         GetMagnitude  (void) { return (m_Data.Magnitude); }
  dword         GetArea       (void) { return (m_Data.Area); }
  dword         GetDuration   (void) { return (m_Data.Duration); }
  dword         GetEffectType (void) { return (m_Data.Type); }
  dword         GetActorValue (void) { return (m_Data.ActorValue); }

  	/* Get a string representation of a subrecord field */
  bool GetField (CSString& Buffer, const int FieldID);
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Set class members */
  void SetEffectName (const SSCHAR* pString)  { m_Data.Name       = pString; }
  void SetEffectName (const obrectype_t Name) { m_Data.Name       = Name; }
  void SetMagnitude  (const dword   Value)    { m_Data.Magnitude  = Value; }
  void SetArea       (const dword   Value)    { m_Data.Area       = Value; }
  void SetDuration   (const dword   Value)    { m_Data.Duration   = Value; }
  void SetEffectType (const dword   Value)    { m_Data.Type       = Value; }
  void SetActorValue (const dword   Value)    { m_Data.ActorValue = Value; } 

 };
/*===========================================================================
 *		End of Class CObEfitSubrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEfitSubrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
inline bool CObEfitSubrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {
  CObEfitSubrecord* pEfit = ObCastClass(CObEfitSubrecord, pSubrecord);

  if (pEfit != NULL) {

    switch (FieldID) {
      case OB_FIELD_MAGNITUDE:
  	Result = (int)GetMagnitude() -  (int)pEfit->GetMagnitude();
	return (true);
      case OB_FIELD_DURATION:
        Result = (int)GetDuration() -  (int)pEfit->GetDuration();
	return (true);
      case OB_FIELD_AREA:
        Result = (int)GetArea() -  (int)pEfit->GetArea();
	return (true);
      case OB_FIELD_RANGE:
        Result = (int)GetEffectType() -  (int)pEfit->GetEffectType();
	return (true);
      case OB_FIELD_ACTORVALUE:
        Result = (int)GetActorValue() -  (int)pEfit->GetActorValue();
	return (true);
      case OB_FIELD_EFFECTID:
        Result = strnicmp(GetEffectName().Name, pEfit->GetEffectName().Name, OB_RECTYPE_SIZE);
	return (true);
      case OB_FIELD_EFFECTDESC:{
        const obeffectdata_t* pEffectData1 = FindObEffectData(GetEffectName().Name);
	const obeffectdata_t* pEffectData2 = FindObEffectData(pEfit->GetEffectName().Name);

	if (pEffectData1 == NULL) {
	  Result = (pEffectData2 == NULL) ? 0 : -1;
	 }
        else if (pEffectData2 == NULL) {
	  Result = 1;
	 }
	else {
          Result = SafeStringCompare(pEffectData1->pDescription, pEffectData2->pDescription);
	 }

	return (true);
       }
     }

   }

	/* No match */
  return CObSubrecord::CompareFields(Result, FieldID, pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObEfitSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEfitSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObEfitSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_MAGNITUDE:
        Buffer.Format("%u", GetMagnitude());
	return (true);
    case OB_FIELD_DURATION:
        Buffer.Format("%u", GetDuration());
	return (true);
    case OB_FIELD_AREA:
        Buffer.Format("%u", GetArea());
	return (true);
    case OB_FIELD_RANGE:
        Buffer.Format("%s", GetObEnchantRangeString(GetEffectType()));
	return (true);
    case OB_FIELD_ACTORVALUE: {
        const SSCHAR* pString = GetObActorValueString(GetActorValue());
        Buffer.Format("%s", pString == NULL ? "" : pString);
	return (true); }
    case OB_FIELD_EFFECTID:
        Buffer.Format("%4.4s", GetEffectName().Name);
	return (true);
    case OB_FIELD_EFFECTDESC: {
        const obeffectdata_t* pEffectData = FindObEffectData(GetEffectName().Name);
        Buffer.Format("%s", pEffectData == NULL ? "" : pEffectData->pDescription);
	return (true); }
   }

  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObEfitSubrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obefitsubrecord.H
 *=========================================================================*/
