/*===========================================================================
 *
 * File:	Oblvlcrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 15, 2006
 *
 * Defines the CObLvlcRecord class for leveled creature records.
 *
 *=========================================================================*/
#ifndef __OBLVLCRECORD_H
#define __OBLVLCRECORD_H


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
  #define OB_LVLCFLAG_CALCULATEALLLEVELS	0x01
  #define OB_LVLCFLAG_CALCULATEEACHITEM		0x02

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLvlcRecord Definition
 *
 *=========================================================================*/
class CObLvlcRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObLvlcRecord, CObIdRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObByteSubrecord*	m_pChanceNone;
  CObByteSubrecord*	m_pFlags;
  CObFormidSubrecord*	m_pScript;
  CObFormidSubrecord*	m_pTemplate;

  dword			m_CreatureCount;



  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLvlcRecord();
  //virtual ~CObLvlcRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Add a new creatures to the leveled list */
  CObLvloSubrecord* AddCreature (const obformid_t FormID, const word Level, const word Count);

	/* Delete all creatures in the leveled list */
  void ClearCreatures (void);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObLvlcRecord; }

	/* Delete a specified creature record */
  bool DeleteCreature (CObLvloSubrecord* pItem);

	/* Find an creature in the list based on its index */
  CObLvloSubrecord* FindCreature (const dword ItemIndex);
  
	/* Iterate through the list creatures */
  CObLvloSubrecord* GetFirstCreature (int& Position);
  CObLvloSubrecord* GetNextCreature  (int& Position);

	/* Get class members */
  byte	     GetChanceNone        (void) { return (m_pChanceNone ? m_pChanceNone->GetValue()        : 0); }
  bool       IsCalculateAllLevels (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVLCFLAG_CALCULATEALLLEVELS) : false); }
  bool       IsCalculateEachItem  (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVLCFLAG_CALCULATEEACHITEM)  : false); }
  dword      GetCreatureCount     (void) { return (m_CreatureCount); }
  obformid_t GetMarkerScript      (void) { return (m_pScript   ? m_pScript->GetValue()   : OB_FORMID_NULL); }
  obformid_t GetCreatureTemplate  (void) { return (m_pTemplate ? m_pTemplate->GetValue() : OB_FORMID_NULL); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetChanceNone         (const byte Value) { if (m_pChanceNone != NULL) m_pChanceNone->SetValue(Value); }
  void SetCalculateAllLevels (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVLCFLAG_CALCULATEALLLEVELS, Value); }
  void SetCalculateEachItem  (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVLCFLAG_CALCULATEEACHITEM,  Value); }
  void SetMarkerScript       (const obformid_t Value);
  void SetCreatureTemplate   (const obformid_t Value);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldChanceNone)
  DECLARE_OBFIELD(FieldCalculateAllLevels)
  DECLARE_OBFIELD(FieldCalculateEachItem)
  DECLARE_OBFIELD(FieldScript)
  DECLARE_OBFIELD(FieldScriptID)
  DECLARE_OBFIELD(FieldTemplate)
  DECLARE_OBFIELD(FieldTemplateID)
  DECLARE_OBFIELD(FieldItemList)
  DECLARE_OBFIELD(FieldItemCount)

};
/*===========================================================================
 *		End of Class CObLvlcRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Oblvlcrecord.H
 *=========================================================================*/
