/*===========================================================================
 *
 * File:	Obarmorecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObArmoRecord class for armor records.
 *
 *=========================================================================*/
#ifndef __OBARMORECORD_H
#define __OBARMORECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obitem2record.h"
  #include "../subrecords/obarmodatasubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Armo data flags */
  #define OB_ARMOFLAG_HIDEAMULET	0x00010000
  #define OB_ARMOFLAG_HIDERINGS		0x00020000
  #define OB_ARMOFLAG_NONPLAYABLE	0x00400000
  #define OB_ARMOFLAG_HEAVYARMOR	0x00800000

  #define OB_ARMOFLAG_DEFAULT		0xCD000000
  
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

  typedef CObDwordSubrecord CObBmdtSubrecord;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObArmoRecord Definition
 *
 * Holds armor data.
 *
 *=========================================================================*/
class CObArmoRecord : public CObItem2Record {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObArmoRecord, CObItem2Record)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObArmoDataSubrecord*	m_pArmorData;
  CObBmdtSubrecord*	m_pFlags;
  CObStringSubrecord*   m_pIcon2;
  CObStringSubrecord*   m_pModel2;
  CObStringSubrecord*   m_pModel3;
  CObStringSubrecord*   m_pModel4;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObArmoRecord();
  //virtual ~CObArmoRecord() { Destroy(); }
  virtual void Destroy (void);

    	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObArmoRecord; }

	/* Get class members */
  obarmodata_t* GetArmorData  (void) { return (m_pArmorData ? &m_pArmorData->GetArmorData() : NULL); }
  float         GetWeight     (void) { return (m_pArmorData ?  m_pArmorData->GetWeight()    : 0.0f); }
  dword         GetValue      (void) { return (m_pArmorData ?  m_pArmorData->GetValue()     : 0); }
  dword         GetHealth     (void) { return (m_pArmorData ?  m_pArmorData->GetHealth()    : 0); }
  word          GetArmor      (void) { return (m_pArmorData ?  m_pArmorData->GetArmor()     : 0); }
  dword		GetBipedFlags (void) { return (m_pFlags     ?  m_pFlags->GetValue() & OB_BIPEDFLAG_MASK : 0); } 

  const SSCHAR* GetModel2     (void) { return (m_pModel2 ? m_pModel2->GetString().c_str() : ""); }
  const SSCHAR* GetModel3     (void) { return (m_pModel3 ? m_pModel3->GetString().c_str() : ""); }
  const SSCHAR* GetModel4     (void) { return (m_pModel4 ? m_pModel4->GetString().c_str() : ""); }
  const SSCHAR* GetIcon2      (void) { return (m_pIcon2  ? m_pIcon2->GetString().c_str()  : ""); }
  bool          HasIcon2      (void) { return (m_pIcon2  != NULL); }
  bool          HasModel2     (void) { return (m_pModel2 != NULL); }
  bool          HasModel3     (void) { return (m_pModel3 != NULL); }  
  bool          HasModel4     (void) { return (m_pModel4 != NULL); }

  bool		IsPlayable    (void) { return (m_pFlags ? !m_pFlags->CheckFlag(OB_ARMOFLAG_NONPLAYABLE) : false); }
  bool		IsHeavyArmor  (void) { return (m_pFlags ? m_pFlags->CheckFlag(OB_ARMOFLAG_HEAVYARMOR)   : false); }
  bool		IsLightArmor  (void) { return !IsHeavyArmor(); }
  bool		IsHideRings   (void) { return (m_pFlags ? m_pFlags->CheckFlag(OB_ARMOFLAG_HIDERINGS)    : false); }
  bool		IsHideAmulet  (void) { return (m_pFlags ? m_pFlags->CheckFlag(OB_ARMOFLAG_HIDEAMULET)   : false); }
  
	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

  	/* Set class members */
  void SetWeight (const float Value) { if (m_pArmorData != NULL) m_pArmorData->SetWeight(Value); }
  void SetValue  (const dword Value) { if (m_pArmorData != NULL) m_pArmorData->SetValue(Value); }
  void SetHealth (const dword Value) { if (m_pArmorData != NULL) m_pArmorData->SetHealth(Value); }
  void SetArmor  (const word  Value) { if (m_pArmorData != NULL) m_pArmorData->SetArmor(Value); }

  void SetPlayable   (const bool Flag) { if (m_pFlags) m_pFlags->FlipFlag(OB_ARMOFLAG_NONPLAYABLE, !Flag); }
  void SetHeavyArmor (const bool Flag) { if (m_pFlags) m_pFlags->FlipFlag(OB_ARMOFLAG_HEAVYARMOR,  Flag); }
  void SetLightArmor (const bool Flag) { if (m_pFlags) m_pFlags->FlipFlag(OB_ARMOFLAG_HEAVYARMOR,  !Flag); }
  void SetHideRings  (const bool Flag) { if (m_pFlags) m_pFlags->FlipFlag(OB_ARMOFLAG_HIDERINGS,   Flag); }
  void SetHideAmulet (const bool Flag) { if (m_pFlags) m_pFlags->FlipFlag(OB_ARMOFLAG_HIDEAMULET,  Flag); }

  void ClearBipedFlags (void)              { if (m_pFlags) m_pFlags->ClearFlag(OB_BIPEDFLAG_MASK); }
  void SetBipedFlags   (const dword Flags) { if (m_pFlags) { m_pFlags->ClearFlag(OB_BIPEDFLAG_MASK); m_pFlags->SetFlag(Flags); } }

  void SetModel2 (const SSCHAR* pString);
  void SetModel3 (const SSCHAR* pString);
  void SetModel4 (const SSCHAR* pString);
  void SetIcon2  (const SSCHAR* pString);
  
	/* Begin field method definitions */
  DECLARE_OBGETFIELD(GetFieldWeight)
  DECLARE_OBGETFIELD(GetFieldValue)
  DECLARE_OBGETFIELD(GetFieldType)
  DECLARE_OBGETFIELD(GetFieldHealth)
  DECLARE_OBGETFIELD(GetFieldArmor)
  DECLARE_OBGETFIELD(GetFieldRealArmor)
  DECLARE_OBGETFIELD(GetFieldBipedParts)
  DECLARE_OBGETFIELD(GetFieldHideAmulet)
  DECLARE_OBGETFIELD(GetFieldHideRings)
  DECLARE_OBGETFIELD(GetFieldPlayable)
  DECLARE_OBGETFIELD(GetFieldModel2)
  DECLARE_OBGETFIELD(GetFieldModel3)
  DECLARE_OBGETFIELD(GetFieldModel4)
  DECLARE_OBGETFIELD(GetFieldIcon2)

  DECLARE_OBCOMPFIELD(CompareFieldWeight)
  DECLARE_OBCOMPFIELD(CompareFieldValue)
  DECLARE_OBCOMPFIELD(CompareFieldType)
  DECLARE_OBCOMPFIELD(CompareFieldHealth)
  DECLARE_OBCOMPFIELD(CompareFieldArmor)
  DECLARE_OBCOMPFIELD(CompareFieldRealArmor)
  DECLARE_OBCOMPFIELD(CompareFieldBipedParts)
  DECLARE_OBCOMPFIELD(CompareFieldHideAmulet)
  DECLARE_OBCOMPFIELD(CompareFieldHideRings)
  DECLARE_OBCOMPFIELD(CompareFieldPlayable)
  DECLARE_OBCOMPFIELD(CompareFieldModel2)
  DECLARE_OBCOMPFIELD(CompareFieldModel3)
  DECLARE_OBCOMPFIELD(CompareFieldModel4)
  DECLARE_OBCOMPFIELD(CompareFieldIcon2)

  DECLARE_OBSETFIELD(SetFieldWeight)
  DECLARE_OBSETFIELD(SetFieldValue)
  DECLARE_OBSETFIELD(SetFieldType)
  DECLARE_OBSETFIELD(SetFieldHealth)
  DECLARE_OBSETFIELD(SetFieldArmor)
  DECLARE_OBSETFIELD(SetFieldRealArmor)
  DECLARE_OBSETFIELD(SetFieldBipedParts)
  DECLARE_OBSETFIELD(SetFieldHideAmulet)
  DECLARE_OBSETFIELD(SetFieldHideRings)
  DECLARE_OBSETFIELD(SetFieldPlayable)
  DECLARE_OBSETFIELD(SetFieldModel2)
  DECLARE_OBSETFIELD(SetFieldModel3)
  DECLARE_OBSETFIELD(SetFieldModel4)
  DECLARE_OBSETFIELD(SetFieldIcon2)
 };
/*===========================================================================
 *		End of Class CObArmoRecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obarmorecord.H
 *=========================================================================*/
