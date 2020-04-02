/*===========================================================================
 *
 * File:	ObSpelrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Defines the CObSpelRecord class for spell records.
 *
 *=========================================================================*/
#ifndef __OBSPELRECORD_H
#define __OBSPELRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obeffitemrecord.h"
  #include "../subrecords/obspitsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSpelRecord Definition
 *
 * Holds spell data.
 *
 *=========================================================================*/
class CObSpelRecord : public CObEffectItemRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObSpelRecord, CObEffectItemRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObSpitSubrecord*	m_pSpellData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSpelRecord();
  //virtual ~CObSpelRecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObSpelRecord; }

	/* Get class members */
  obspitdata_t* GetSpellData   (void) { return (m_pSpellData ? &m_pSpellData->GetSpellData() : NULL); }
  dword	        GetCost        (void) { return (m_pSpellData ?  m_pSpellData->GetCost()      : 0); }
  dword	        GetType        (void) { return (m_pSpellData ?  m_pSpellData->GetType()      : 0); }
  dword	        GetLevel       (void) { return (m_pSpellData ?  m_pSpellData->GetLevel()     : 0); }

  bool IsAutoCalc          (void) { return (m_pSpellData ?  m_pSpellData->IsAutoCalc()          : false); }
  bool IsPlayerStart       (void) { return (m_pSpellData ?  m_pSpellData->IsPlayerStart()       : false); }
  bool IsSilenceImmune     (void) { return (m_pSpellData ?  m_pSpellData->IsSilenceImmune()     : false); }
  bool IsIgnoreLOS         (void) { return (m_pSpellData ?  m_pSpellData->IsIgnoreLOS()         : false); }
  bool IsAlwaysApplyScript (void) { return (m_pSpellData ?  m_pSpellData->IsAlwaysApplyScript() : false); }
  bool IsAbsorbReflect     (void) { return (m_pSpellData ?  m_pSpellData->IsAbsorbReflect()     : false); }
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetCost     (const dword Value) { if (m_pSpellData != NULL) m_pSpellData->SetCost(Value); }
  void SetType     (const dword Value) { if (m_pSpellData != NULL) m_pSpellData->SetType(Value); }
  void SetLevel    (const dword Value) { if (m_pSpellData != NULL) m_pSpellData->SetLevel(Value); }

  void SetAutoCalc          (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetAutoCalc(Flag); }
  void SetPlayerStart       (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetPlayerStart(Flag); }
  void SetSilenceImmune     (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetSilenceImmune(Flag); }
  void SetIgnoreLOS         (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetIgnoreLOS(Flag); }
  void SetAlwaysApplyScript (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetAlwaysApplyScript(Flag); }
  void SetAbsorbReflect     (const bool Flag) { if (m_pSpellData != NULL) m_pSpellData->SetAbsorbReflect(Flag); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldCost)
  DECLARE_OBFIELD(FieldType)
  DECLARE_OBFIELD(FieldLevel)
  DECLARE_OBFIELD(FieldAutoCalc)
  DECLARE_OBFIELD(FieldPlayerStart)
  DECLARE_OBFIELD(FieldSilenceImmune)
  DECLARE_OBFIELD(FieldIgnoreLOS)
  DECLARE_OBFIELD(FieldAlwaysApplyScript)
  DECLARE_OBFIELD(FieldAbsorbReflect)

 };
/*===========================================================================
 *		End of Class CObSpelRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  const SSCHAR* GetObSpellTypeString (const int Value);
  bool GetObSpellTypeValue (int& Value, const SSCHAR* pString);
  const SSCHAR* GetObSpellLevelString (const int Value);
  bool GetObSpellLevelValue (int& Value, const SSCHAR* pString);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obspelrecord.H
 *=========================================================================*/
