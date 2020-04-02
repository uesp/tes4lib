/*===========================================================================
 *
 * File:	Oblvlirecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObLvliRecord class for levelled item lists records.
 *
 *=========================================================================*/
#ifndef __OBLVLIRECORD_H
#define __OBLVLIRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obbytesubrecord.h"
  #include "../subrecords/oblvlosubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Item flags */
  #define OB_LVLIFLAG_CALCULATEALLLEVELS	0x01
  #define OB_LVLIFLAG_CALCULATEEACHITEM		0x02

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLvliRecord Definition
 *
 * Holds levelled item list data.
 *
 *=========================================================================*/
class CObLvliRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObLvliRecord, CObIdRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObByteSubrecord*	m_pChanceNone;
  CObByteSubrecord*	m_pFlags;

  dword			m_ItemCount;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLvliRecord();
  //virtual ~CObLvliRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Add a new item to the levelled list */
  CObLvloSubrecord* AddItem (const obformid_t FormID, const word Level, const word Count);

	/* Delete all items in the levelled list */
  void ClearItems (void);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObLvliRecord; }

	/* Delete a specified item record */
  bool DeleteItem (CObLvloSubrecord* pItem);

	/* Find an item in the list based on its index */
  CObLvloSubrecord* FindItem (const dword ItemIndex);
  
	/* Iterate through the list items */
  CObLvloSubrecord* GetFirstItem (int& Position);
  CObLvloSubrecord* GetNextItem  (int& Position);

	/* Get class members */
  byte	GetChanceNone        (void) { return (m_pChanceNone ? m_pChanceNone->GetValue()        : 0); }
  bool  IsCalculateAllLevels (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVLIFLAG_CALCULATEALLLEVELS) : false); }
  bool  IsCalculateEachItem  (void) { return (m_pFlags      ? m_pFlags->CheckFlag(OB_LVLIFLAG_CALCULATEEACHITEM)  : false); }
  dword GetItemCount	     (void) { return (m_ItemCount); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Set class members */
  void SetChanceNone         (const byte Value) { if (m_pChanceNone != NULL) m_pChanceNone->SetValue(Value); }
  void SetCalculateAllLevels (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVLIFLAG_CALCULATEALLLEVELS, Value); }
  void SetCalculateEachItem  (const bool Value) { if (m_pFlags      != NULL) m_pFlags->FlipFlag(OB_LVLIFLAG_CALCULATEEACHITEM,  Value); }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldChanceNone)
  DECLARE_OBFIELD(FieldCalculateAllLevels)
  DECLARE_OBFIELD(FieldCalculateEachItem)
  DECLARE_OBFIELD(FieldItemList)
  DECLARE_OBFIELD(FieldItemCount)

};
/*===========================================================================
 *		End of Class CObLvliRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Oblvlirecord.H
 *=========================================================================*/
