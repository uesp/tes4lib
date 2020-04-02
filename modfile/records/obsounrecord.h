/*===========================================================================
 *
 * File:	ObSounRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Defines the CObSounRecord class.
 *
 *=========================================================================*/
#ifndef __OBSOUNRECORD_H
#define __OBSOUNRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obformidsubrecord.h"
  #include "../subrecords/obsndxsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

  #define OB_SOUN_MINATTENUATION_FACTOR    5
  #define OB_SOUN_MAXATTENUATION_FACTOR    100
  #define OB_SOUN_STATICATTENUATION_FACTOR -100.0f
  #define OB_SOUN_TIME_FACTOR              (1440.0f/256.0f)

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSounRecord Definition
 *
 * Holds enchantment data.
 *
 *=========================================================================*/
class CObSounRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObSounRecord, CObIdRecord)
  
  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObStringSubrecord*	m_pSoundFile;
  CObSndxSubrecord*	m_pData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSounRecord();
  //virtual ~CObSounRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObSounRecord; }

	/* Get class members */
  const SSCHAR* GetSoundFile           (void) { return (m_pSoundFile ? m_pSoundFile->GetString().c_str() : ""); }
  byte          GetMinAttenuation      (void) { return (m_pData ? m_pData->GetMinAttenuation() : 0); }
  byte          GetMaxAttenuation      (void) { return (m_pData ? m_pData->GetMaxAttenuation() : 0); }
  char          GetFreqAdjustment      (void) { return (m_pData ? m_pData->GetFreqAdjustment() : 0); }
  word          GetStaticAttenuation   (void) { return (m_pData ? m_pData->GetStaticAttenuation() : 0); }
  byte		GetStartTime           (void) { return (m_pData ? m_pData->GetStartTime() : 0); }
  byte		GetStopTime            (void) { return (m_pData ? m_pData->GetStopTime() : 0); }
  bool          IsRandomFreqShift      (void) { return (m_pData ? m_pData->IsRandomFreqShift() : false); }
  bool          IsRandomPlay           (void) { return (m_pData ? m_pData->IsRandomPlay() : false); }
  bool          IsIgnoreEnvironment    (void) { return (m_pData ? m_pData->IsIgnoreEnvironment() : false); }
  bool          IsRandomLocation       (void) { return (m_pData ? m_pData->IsRandomLocation() : false); }
  bool          IsLoop                 (void) { return (m_pData ? m_pData->IsLoop() : false); }
  bool          IsMenuSound            (void) { return (m_pData ? m_pData->IsMenuSound() : false); }
  bool          Is2DSound              (void) { return (m_pData ? m_pData->Is2DSound() : false); }
  bool          Is360LFE               (void) { return (m_pData ? m_pData->Is360LFE() : false); }

	/* Extended get class members */
  dword GetMinAttenuationUnits (void) { return (dword)GetMinAttenuation() * OB_SOUN_MINATTENUATION_FACTOR; }
  dword GetMaxAttenuationUnits (void) { return (dword)GetMaxAttenuation() * OB_SOUN_MAXATTENUATION_FACTOR; }
  float GetStaticAttenuationDB (void) { return (float)GetStaticAttenuation() / OB_SOUN_STATICATTENUATION_FACTOR; }
  dword GetStartTimeMinutes    (void) { return (dword)((dword)GetStartTime() * OB_SOUN_TIME_FACTOR); }
  dword GetStopTimeMinutes     (void) { return (dword)((dword)GetStopTime() * OB_SOUN_TIME_FACTOR); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetSoundFile         (const SSCHAR* pString);
  void SetMinAttenuation    (const byte Value) { if (m_pData) m_pData->SetMinAttenuation(Value); }
  void SetMaxAttenuation    (const byte Value) { if (m_pData) m_pData->SetMaxAttenuation(Value); }
  void SetFreqAdjustment    (const char Value) { if (m_pData) m_pData->SetFreqAdjustment(Value); }
  void SetStaticAttenuation (const word Value) { if (m_pData) m_pData->SetStaticAttenuation(Value); }
  void SetStartTime         (const byte Value) { if (m_pData) m_pData->SetStartTime(Value); }
  void SetStopTime          (const byte Value) { if (m_pData) m_pData->SetStopTime(Value); }
  void SetRandomFreqShift   (const bool Value) { if (m_pData) m_pData->SetRandomFreqShift(Value); }
  void SetRandomPlay        (const bool Value) { if (m_pData) m_pData->SetRandomPlay(Value); }
  void SetIgnoreEnvironment (const bool Value) { if (m_pData) m_pData->SetIgnoreEnvironment(Value); }
  void SetRandomLocation    (const bool Value) { if (m_pData) m_pData->SetRandomLocation(Value); }
  void SetLoop              (const bool Value) { if (m_pData) m_pData->SetLoop(Value); }
  void SetMenuSound         (const bool Value) { if (m_pData) m_pData->SetMenuSound(Value); }
  void Set2DSound           (const bool Value) { if (m_pData) m_pData->Set2DSound(Value); }
  void Set360LFE            (const bool Value) { if (m_pData) m_pData->Set360LFE(Value); }

	/* Extended set class members */
  void SetMinAttenuationUnits    (const dword Value) { SetMinAttenuation((byte) (Value / OB_SOUN_MINATTENUATION_FACTOR)); }
  void SetMaxAttenuationUnits    (const dword Value) { SetMaxAttenuation((byte) (Value / OB_SOUN_MAXATTENUATION_FACTOR)); }
  void SetStaticAttenuationDB    (const float Value) { SetStaticAttenuation((word) (Value * OB_SOUN_STATICATTENUATION_FACTOR)); }
  void SetStartTimeMinutes       (const dword Value) { SetStartTime((byte) (Value / OB_SOUN_TIME_FACTOR)); }
  void SetStopTimeMinutes        (const dword Value) { SetStopTime((byte) (Value / OB_SOUN_TIME_FACTOR)); }


	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldSoundFile)
  DECLARE_OBFIELD(FieldMinAttenuation)
  DECLARE_OBFIELD(FieldMaxAttenuation)
  DECLARE_OBFIELD(FieldStaticAttenuation)
  DECLARE_OBFIELD(FieldFreqAdjustment)
  DECLARE_OBFIELD(FieldStartTime)
  DECLARE_OBFIELD(FieldStopTime)
  DECLARE_OBFIELD(FieldRandomFreqShift)
  DECLARE_OBFIELD(FieldRandomPlay)
  DECLARE_OBFIELD(FieldRandomLocation)
  DECLARE_OBFIELD(FieldLoop)
  DECLARE_OBFIELD(FieldMenuSound)
  DECLARE_OBFIELD(FieldIgnoreEnvironment)
  DECLARE_OBFIELD(Field2DSound)
  DECLARE_OBFIELD(Field360LFE)

};
/*===========================================================================
 *		End of Class CObSounRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObSounRecord.H
 *=========================================================================*/

