/*===========================================================================
 *
 * File:	Obclotrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObClotRecord class for armor records.
 *
 *=========================================================================*/
#ifndef __OBCLOTRECORD_H
#define __OBCLOTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem2record.h"
  #include "../subrecords/obclotdatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Clothing data flags */
  #define OB_CLOTFLAG_HIDEAMULET	0x00010000
  #define OB_CLOTFLAG_HIDERINGS		0x00020000
  #define OB_CLOTFLAG_NONPLAYABLE	0x00400000

  #define OB_CLOTFLAG_DEFAULT		0x00000000
  
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObClotRecord Definition
 *
 * Holds clothing data.
 *
 *=========================================================================*/
class CObClotRecord : public CObItem2Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObClotRecord, CObItem2Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObClotDataSubrecord*	m_pClothingData;
  CObDwordSubrecord*	m_pFlags;
  CObStringSubrecord*   m_pIcon2;
  CObStringSubrecord*   m_pModel2;
  CObStringSubrecord*   m_pModel3;
  CObStringSubrecord*   m_pModel4;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObClotRecord();
  //virtual ~CObClotRecord() { Destroy(); }
  virtual void Destroy (void);

    	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObClotRecord; }

	/* Get class members */
  obclotdata_t* GetClothingData (void) { return (m_pClothingData ? &m_pClothingData->GetClothingData()    : NULL); }
  float         GetWeight       (void) { return (m_pClothingData ?  m_pClothingData->GetWeight()          : 0.0f); }
  dword         GetValue        (void) { return (m_pClothingData ?  m_pClothingData->GetValue()           : 0); }
  dword		GetBipedFlags   (void) { return (m_pFlags        ?  m_pFlags->GetValue() & OB_BIPEDFLAG_MASK: 0); }

  bool		IsPlayable      (void) { return (m_pFlags ? !m_pFlags->CheckFlag(OB_CLOTFLAG_NONPLAYABLE) : false); }
  bool		IsHideRings     (void) { return (m_pFlags ?  m_pFlags->CheckFlag(OB_CLOTFLAG_HIDERINGS)   : false); }
  bool		IsHideAmulet    (void) { return (m_pFlags ?  m_pFlags->CheckFlag(OB_CLOTFLAG_HIDEAMULET)  : false); }

  const SSCHAR* GetModel2       (void) { return (m_pModel2 ? m_pModel2->GetString().c_str() : ""); }
  const SSCHAR* GetModel3       (void) { return (m_pModel3 ? m_pModel3->GetString().c_str() : ""); }
  const SSCHAR* GetModel4       (void) { return (m_pModel4 ? m_pModel4->GetString().c_str() : ""); }
  const SSCHAR* GetIcon2        (void) { return (m_pIcon2  ? m_pIcon2->GetString().c_str()  : ""); }
  bool          HasIcon2        (void) { return (m_pIcon2  != NULL); }
  bool          HasModel2       (void) { return (m_pModel2 != NULL); }
  bool          HasModel3       (void) { return (m_pModel3 != NULL); }  
  bool          HasModel4       (void) { return (m_pModel4 != NULL); }
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight     (const float Value) { if (m_pClothingData != NULL) m_pClothingData->SetWeight(Value); }
  void SetValue      (const dword Value) { if (m_pClothingData != NULL) m_pClothingData->SetValue(Value); }
  void SetPlayable   (const bool Flag)   { if (m_pFlags) m_pFlags->FlipFlag(OB_CLOTFLAG_NONPLAYABLE, !Flag); }
  void SetHideRings  (const bool Flag)   { if (m_pFlags) m_pFlags->FlipFlag(OB_CLOTFLAG_HIDERINGS,    Flag); }
  void SetHideAmulet (const bool Flag)   { if (m_pFlags) m_pFlags->FlipFlag(OB_CLOTFLAG_HIDEAMULET,   Flag); }
  
  void ClearBipedFlags (void)              { if (m_pFlags)   m_pFlags->ClearFlag(OB_BIPEDFLAG_MASK); }
  void SetBipedFlags   (const dword Flags) { if (m_pFlags) { m_pFlags->ClearFlag(OB_BIPEDFLAG_MASK); m_pFlags->SetFlag(Flags); } }

  void SetModel2 (const SSCHAR* pString);
  void SetModel3 (const SSCHAR* pString);
  void SetModel4 (const SSCHAR* pString);
  void SetIcon2  (const SSCHAR* pString);
  
  	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldWeight)
  DECLARE_OBFIELD(FieldValue)
  DECLARE_OBFIELD(FieldPlayable)
  DECLARE_OBFIELD(FieldBipedParts)
  DECLARE_OBFIELD(FieldHideAmulet)
  DECLARE_OBFIELD(FieldHideRings)
  DECLARE_OBFIELD(FieldModel2)
  DECLARE_OBFIELD(FieldModel3)
  DECLARE_OBFIELD(FieldModel4)
  DECLARE_OBFIELD(FieldIcon2)
 };
/*===========================================================================
 *		End of Class CObClotRecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obclotrecord.H
 *=========================================================================*/
