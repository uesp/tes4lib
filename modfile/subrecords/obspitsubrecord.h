/*===========================================================================
 *
 * File:	Obspitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 15, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSPITSUBRECORD_H
#define __OBSPITSUBRECORD_H


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

	/* Standard SPIT subrecord size in bytes */
  #define OBSPIT_SUBRECORD_SIZE	16

	/* Enchantment flags */
  #define OB_SPELFLAG_MANUALCALC        0x00000001
  #define OB_SPELFLAG_PLAYERSTART       0x00000004
  #define OB_SPELFLAG_SILENCEIMMUNE     0x0000000A
  #define OB_SPELFLAG_IGNORELOS         0x00000010
  #define OB_SPELFLAG_ALWAYSAPPLYSCRIPT 0x00000020
  #define OB_SPELFLAG_NOABSORBREFLECT   0x00000040

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* SPIT data structure */
  struct obspitdata_t {
	dword Type;
	dword SpellCost;
	dword SpellLevel;
	dword Flags;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSpitSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSpitSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSpitSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obspitdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBSPIT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBSPIT_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSpitSubrecord();
  //virtual ~CObSpitSubrecord() { Destroy(); }
  virtual void Destroy (void);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSpitSubrecord* pSubrecord1 = ObCastClassNull(CObSpitSubrecord, pSubrecord);
	m_RecordSize = OBSPIT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSpellData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSpitSubrecord); }

	/* Get class members */
  obspitdata_t& GetSpellData (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  dword		GetType      (void) { return (m_Data.Type); }
  dword		GetCost      (void) { return (m_Data.SpellCost); }
  dword		GetLevel     (void) { return (m_Data.SpellLevel); }

  bool IsAutoCalc          (void) { return !CheckFlagBits(m_Data.Flags, OB_SPELFLAG_MANUALCALC); }
  bool IsPlayerStart       (void) { return  CheckFlagBits(m_Data.Flags, OB_SPELFLAG_PLAYERSTART); }
  bool IsSilenceImmune     (void) { return  CheckFlagBits(m_Data.Flags, OB_SPELFLAG_SILENCEIMMUNE); }
  bool IsIgnoreLOS         (void) { return  CheckFlagBits(m_Data.Flags, OB_SPELFLAG_IGNORELOS); }  
  bool IsAlwaysApplyScript (void) { return  CheckFlagBits(m_Data.Flags, OB_SPELFLAG_ALWAYSAPPLYSCRIPT); }
  bool IsAbsorbReflect     (void) { return !CheckFlagBits(m_Data.Flags, OB_SPELFLAG_NOABSORBREFLECT); }
  	
	/* Initialize a new record */
  void InitializeNew (void);

	/* Set class members */
  void SetType  (const dword Value) { m_Data.Type       = Value; }
  void SetCost  (const dword Value) { m_Data.SpellCost  = Value; }
  void SetLevel (const dword Value) { m_Data.SpellLevel = Value; }

  void SetAutoCalc          (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_MANUALCALC,        !Flag); }
  void SetPlayerStart       (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_PLAYERSTART,        Flag); }
  void SetSilenceImmune     (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_SILENCEIMMUNE,      Flag); }
  void SetIgnoreLOS         (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_IGNORELOS,          Flag); }
  void SetAlwaysApplyScript (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_ALWAYSAPPLYSCRIPT,  Flag); }
  void SetAbsorbReflect     (const bool Flag) { FlipFlagBits(m_Data.Flags,  OB_SPELFLAG_NOABSORBREFLECT,   !Flag); }

 };
/*===========================================================================
 *		End of Class CObSpitSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obspitsubrecord.H
 *=========================================================================*/
