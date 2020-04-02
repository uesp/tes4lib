/*===========================================================================
 *
 * File:	ObEffItemRecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Defines the CObEffectItemRecord class for items that have effects
 * associated with them (Ingrediants, Enchantments, Spells, Sigil Stones).
 *
 *=========================================================================*/
#ifndef __OBEFFITEMRECORD_H
#define __OBEFFITEMRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem1record.h"
  #include "../subrecords/obingrenitsubrecord.h"
  #include "../subrecords/obfloatsubrecord.h"
  #include "../subrecords/obefitsubrecord.h"
  #include "../subrecords/obscitsubrecord.h"
  #include "../subrecords/obnamesubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEffectItemRecord Definition
 *
 * Is used as a base class by any item with effects.
 *
 *=========================================================================*/
class CObEffectItemRecord : public CObItem1Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObEffectItemRecord, CObItem1Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  dword		m_EffectCount;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEffectItemRecord();
  //virtual ~CObEffectItemRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Add an effect to the record */
  CObEfidSubrecord* AddEffect (const obrectype_t EffectName);

	/* Copy all effects from the given effect record */
  dword CopyEffects (CObEffectItemRecord* pSource);

	/* Delete all effects in the record */
  void DeleteAllEffects (void);

	/* Delete the specified effect in the record */
  bool DeleteEffect (CObEfidSubrecord* pEffect);

	/* Find an effect based on its index */
  CObEfidSubrecord* FindEffect (const dword Index);

  	/* Iterate through the effects */
  CObEfidSubrecord* GetFirstEffect (int& Position);
  CObEfidSubrecord* GetNextEffect  (int& Position);

	/* Get effect data */
  CObEfitSubrecord* GetEffectData           (CObEfidSubrecord* pEffect);
  CObScitSubrecord* GetScriptEffectData     (CObEfidSubrecord* pEffect);
  const SSCHAR*     GetScriptEffectName     (CObEfidSubrecord* pEffect);
  CObFullSubrecord* GetScriptEffectNameData (CObEfidSubrecord* pEffect);
  dword		    GetEffectCount          (void) { return (m_EffectCount); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set specific effect data */
  bool SetEffectData       (CObEfidSubrecord* pEffect, const dword Type, const dword Magnitude, const dword Area, const dword Duration, const dword ActorValue = 0);
  bool SetScriptEffectData (CObEfidSubrecord* pEffect, const obformid_t ScriptFormID, const dword School, const obrectype_t VisualEffect = OB_NAME_NULL, const bool Hostile = true);
  bool SetScriptEffectName (CObEfidSubrecord* pEffect, const SSCHAR* pString);

	/* Begin field method definitions */
  DECLARE_OBGETFIELD(GetFieldEffectCount)

  DECLARE_OBCOMPFIELD(CompareFieldEffectCount)
 };
/*===========================================================================
 *		End of Class CObEffectItemRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObEffItemRecord.H
 *=========================================================================*/
