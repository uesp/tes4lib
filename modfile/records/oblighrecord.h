/*===========================================================================
 *
 * File:	ObLightrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 22, 2006
 *
 * Defines the CObLighRecord class for miscitem records.
 *
 *=========================================================================*/
#ifndef __OBLIGHRECORD_H
#define __OBLIGHRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/oblighdatasubrecord.h"
  #include "../subrecords/obfloatsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLighRecord Definition
 *
 * Holds light item data.
 *
 *=========================================================================*/
class CObLighRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObLighRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObLighDataSubrecord*	m_pLighData;
  CObFloatSubrecord*	m_pFadeData;
  CObFormidSubrecord*	m_pSound;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLighRecord();
  //virtual ~CObLighRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObLighRecord; }

	/* Get class members */
  oblighdata_t* GetLightData  (void) { return (m_pLighData ? &m_pLighData->GetLightData() : NULL); }
  long          GetTime       (void) { return (m_pLighData ?  m_pLighData->GetTime()      : -1); }
  dword         GetRadius     (void) { return (m_pLighData ?  m_pLighData->GetRadius()    : 0); }
  obrgba_t      GetColor      (void) { return (m_pLighData ?  m_pLighData->GetColor()     : OB_COLOR_NULL ); }
  byte          GetRedColor   (void) { return (m_pLighData ?  m_pLighData->GetColor().R   : 0 ); }
  byte          GetGreenColor (void) { return (m_pLighData ?  m_pLighData->GetColor().G   : 0 ); }
  byte          GetBlueColor  (void) { return (m_pLighData ?  m_pLighData->GetColor().B   : 0 ); }
  float         GetFalloff    (void) { return (m_pLighData ?  m_pLighData->GetFalloff()   : 0); }
  float         GetFOV        (void) { return (m_pLighData ?  m_pLighData->GetFOV()       : 0.0f); }
  float         GetWeight     (void) { return (m_pLighData ?  m_pLighData->GetWeight()    : 0.0f); }
  dword         GetValue      (void) { return (m_pLighData ?  m_pLighData->GetValue()     : 0); }
  float		GetFade	      (void) { return (m_pFadeData ?  m_pFadeData->GetValue()     : 1.0f); }
  obformid_t    GetSound      (void) { return (m_pSound    ?  m_pSound->GetValue()        : OB_FORMID_NULL); }

  dword         GetLightType  (void) { return (m_pLighData ?  m_pLighData->GetLightType()  : OB_LIGHTYPE_NONE); }
  bool		IsFlicker     (void) { return (m_pLighData ?  m_pLighData->IsFlicker()     : false); }
  bool		IsFlickerSlow (void) { return (m_pLighData ?  m_pLighData->IsFlickerSlow() : false); }
  bool		IsPulse       (void) { return (m_pLighData ?  m_pLighData->IsPulse()       : false); }
  bool		IsPulseSlow   (void) { return (m_pLighData ?  m_pLighData->IsPulseSlow()   : false); }
  bool		IsTypeNone    (void) { return (m_pLighData ?  m_pLighData->IsTypeNone()    : false); }

  bool		IsDynamic     (void) { return (m_pLighData ?  m_pLighData->IsDynamic()    : false); }
  bool		IsCarried     (void) { return (m_pLighData ?  m_pLighData->IsCarried()    : false); }
  bool		IsNegative    (void) { return (m_pLighData ?  m_pLighData->IsNegative()   : false); }
  bool		IsDefaultOff  (void) { return (m_pLighData ?  m_pLighData->IsDefaultOff() : false); }
  bool		IsSpotLight   (void) { return (m_pLighData ?  m_pLighData->IsSpotLight()  : false); }
  bool		IsSpotShadow  (void) { return (m_pLighData ?  m_pLighData->IsSpotShadow() : false); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetTime    (const long  Value) { if (m_pLighData != NULL) m_pLighData->SetTime(Value); }
  void SetRadius  (const dword Value) { if (m_pLighData != NULL) m_pLighData->SetRadius(Value); }
  void SetFalloff (const float Value) { if (m_pLighData != NULL) m_pLighData->SetFalloff(Value); }
  void SetFOV     (const float Value) { if (m_pLighData != NULL) m_pLighData->SetFOV(Value); }
  void SetWeight  (const float Value) { if (m_pLighData != NULL) m_pLighData->SetWeight(Value); }
  void SetValue   (const dword Value) { if (m_pLighData != NULL) m_pLighData->SetValue(Value); }
  void SetFade	  (const float Value) { if (m_pFadeData != NULL) m_pFadeData->SetValue(Value); }
  void SetSound   (const obformid_t Value);

  void SetColor      (const obrgba_t Value)		      { if (m_pLighData != NULL) m_pLighData->SetColor(Value); }
  void SetColor      (const byte R, const byte G, const byte B) { if (m_pLighData != NULL) m_pLighData->SetColor(R, G, B); }
  void SetRedColor   (const byte Value)                         { if (m_pLighData != NULL) m_pLighData->SetRedColor(Value); }
  void SetGreenColor (const byte Value)                         { if (m_pLighData != NULL) m_pLighData->SetGreenColor(Value); }
  void SetBlueColor  (const byte Value)                         { if (m_pLighData != NULL) m_pLighData->SetBlueColor(Value); }

  void SetLightType   (const dword Type) { if (m_pLighData != NULL) m_pLighData->SetLightType(Type); }
  void SetTypeNone    (void) { if (m_pLighData != NULL) m_pLighData->SetTypeNone(); }
  void SetFlicker     (void) { if (m_pLighData != NULL) m_pLighData->SetFlicker(); }
  void SetFlickerSlow (void) { if (m_pLighData != NULL) m_pLighData->SetFlickerSlow(); }
  void SetPulse       (void) { if (m_pLighData != NULL) m_pLighData->SetPulse(); }
  void SetPulseSlow   (void) { if (m_pLighData != NULL) m_pLighData->SetPulseSlow(); }

  void SetDynamic    (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetDynamic(Flag); }
  void SetCarried    (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetCarried(Flag); }
  void SetNegative   (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetNegative(Flag); }
  void SetDefaultOff (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetDefaultOff(Flag); }
  void SetSpotLight  (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetSpotLight(Flag); }
  void SetSpotShadow (const bool  Flag) { if (m_pLighData != NULL) m_pLighData->SetSpotShadow(Flag); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldSpotShadow)
  DECLARE_OBFIELD(FieldSpotLight)
  DECLARE_OBFIELD(FieldDefaultOff)
  DECLARE_OBFIELD(FieldNegative)
  DECLARE_OBFIELD(FieldDynamic)
  DECLARE_OBFIELD(FieldCarried)
  DECLARE_OBFIELD(FieldType)
  DECLARE_OBFIELD(FieldFOV)
  DECLARE_OBFIELD(FieldFalloff)
  DECLARE_OBFIELD(FieldColor)
  DECLARE_OBFIELD(FieldRedColor)
  DECLARE_OBFIELD(FieldGreenColor)
  DECLARE_OBFIELD(FieldBlueColor)
  DECLARE_OBFIELD(FieldRadius)
  DECLARE_OBFIELD(FieldFade)
  DECLARE_OBFIELD(FieldTime)
  DECLARE_OBFIELD(FieldSoundID)
  DECLARE_OBFIELD(FieldSound)

 };
/*===========================================================================
 *		End of Class CObLighRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File ObLighrecord.H
 *=========================================================================*/
