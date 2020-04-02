/*===========================================================================
 *
 * File:	Oblvsprecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Defines the CObLvspRecord class for leveled spell records.
 *
 *=========================================================================*/
#ifndef __OBLVSPRECORD_H
#define __OBLVSPRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/oblvlosubrecord.h"
  #include "../subrecords/obbytesubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Item flags */
  #define OB_LVSPFLAG_CALCULATEALLLEVELS	0x01
  #define OB_LVSPFLAG_CALCULATEEACHITEM		0x02
  #define OB_LVSPFLAG_USEALLSPELLS		0x04

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLvspRecord Definition
 *
 *=========================================================================*/
class CObLvspRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObLvspRecord, CObIdRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObByteSubrecord*	m_pChanceNone;
  CObByteSubrecord*	m_pFlags;

  dword			m_SpellCount;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLvspRecord();
  //virtual ~CObLvspRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Add a new spell to the leveled list */
  CObLvloSubrecord* AddSpell (const obformid_t FormID, const word Level, const word Count);

	/* Delete all spells in the levelled list */
  void ClearSpells (void);
	
	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObLvspRecord; }

	/* Delete a specified spell record */
  bool DeleteSpell (CObLvloSubrecord* pSpell);

	/* Find an spell in the list based on its index */
  CObLvloSubrecord* FindSpell (const dword SpellIndex);
  
	/* Iterate through the list spells */
  CObLvloSubrecord* GetFirstSpell (int& Position);
  CObLvloSubrecord* GetNextSpell  (int& Position);

  	/* Get class members */
  byte	GetChanceNone        (void) { return (m_pChanceNone ? m_pChanceNone->GetValue()        : 0); }
  bool  IsCalculateAllLevels (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVSPFLAG_CALCULATEALLLEVELS) : false); }
  bool  IsCalculateEachItem  (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVSPFLAG_CALCULATEEACHITEM)  : false); }
  bool  IsUseAllSpells       (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVSPFLAG_USEALLSPELLS)       : false); }
  dword GetSpellCount	     (void) { return (m_SpellCount); }
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetChanceNone         (const byte Value) { if (m_pChanceNone != NULL) m_pChanceNone->SetValue(Value); }
  void SetCalculateAllLevels (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVSPFLAG_CALCULATEALLLEVELS, Value); }
  void SetCalculateEachItem  (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVSPFLAG_CALCULATEEACHITEM,  Value); }
  void SetUseAllSpells       (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVSPFLAG_USEALLSPELLS,       Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldChanceNone)
  DECLARE_OBFIELD(FieldCalculateAllLevels)
  DECLARE_OBFIELD(FieldCalculateEachItem)
  DECLARE_OBFIELD(FieldUseAllSpells)
  DECLARE_OBFIELD(FieldItemList)
  DECLARE_OBFIELD(FieldItemCount)

};
/*===========================================================================
 *		End of Class CObLvspRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oblvlcrecord.H
 *=========================================================================*/
