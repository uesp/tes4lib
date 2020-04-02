/*===========================================================================
 *
 * File:	Obmgefdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBMGEFDATASUBRECORD_H
#define __OBMGEFDATASUBRECORD_H


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

  #define OB_MGEFDATA_SUBRECORD_SIZE	64

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 * 
 *=========================================================================*/
#pragma pack(push, 1)

  struct obmgefdata_t {
	dword		Flags;
	float		BaseCost;
	dword		Unknown1;
	dword		MagicShool;
	dword		Resist;
	dword		Unknown2;
	obformid_t	LightFormID;
	float		ProjectileSpeed;
	obformid_t	EffectShaderFormID;
	obformid_t	EnchantEffectFormID;
	obformid_t	CastingSoundFormID;
	obformid_t	BoltSoundFormID;
	obformid_t	HitSoundFormID;
	obformid_t	AreaSoundFormID;
	float		CEEnchantmentFactor;
	float		CEBarterFactor;
  };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObMgefDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObMgefDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObMgefDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obmgefdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { memset(&m_Data, 0, sizeof(m_Data)); return File.Read(&m_Data,  m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObMgefDataSubrecord() { }
  //virtual ~CObMgefDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }
  
  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
        dword Count = 0;
	if (m_Data.LightFormID == OldID) {
	  m_Data.LightFormID = NewID;
	  ++Count;
	}
	if (m_Data.EffectShaderFormID == OldID) {
	  m_Data.EffectShaderFormID = NewID;
	  ++Count;
	}
	if (m_Data.EnchantEffectFormID == OldID) {
	  m_Data.EnchantEffectFormID = NewID;
	  ++Count;
	}
	if (m_Data.CastingSoundFormID == OldID) {
	  m_Data.CastingSoundFormID = NewID;
	  ++Count;
	}
	if (m_Data.BoltSoundFormID == OldID) {
	  m_Data.BoltSoundFormID = NewID;
	  ++Count;
	}
	if (m_Data.HitSoundFormID == OldID) {
	  m_Data.HitSoundFormID = NewID;
	  ++Count;
	}
	if (m_Data.AreaSoundFormID == OldID) {
	  m_Data.AreaSoundFormID = NewID;
	  ++Count;
	}
	return (Count);
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObMgefDataSubrecord* pSubrecord1 = ObCastClassNull(CObMgefDataSubrecord, pSubrecord);
	m_RecordSize = OB_MGEFDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetMgefData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObMgefDataSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return	ObFixupFormid(m_Data.LightFormID, m_Data.LightFormID, FixupArray) && 
		ObFixupFormid(m_Data.EffectShaderFormID, m_Data.EffectShaderFormID, FixupArray) &&
		ObFixupFormid(m_Data.EnchantEffectFormID, m_Data.EnchantEffectFormID, FixupArray) &&
		ObFixupFormid(m_Data.CastingSoundFormID, m_Data.CastingSoundFormID, FixupArray) &&
		ObFixupFormid(m_Data.BoltSoundFormID, m_Data.BoltSoundFormID, FixupArray) &&
		ObFixupFormid(m_Data.HitSoundFormID, m_Data.HitSoundFormID, FixupArray) &&
		ObFixupFormid(m_Data.AreaSoundFormID, m_Data.AreaSoundFormID, FixupArray);
  }

	/* Get class members */
  obmgefdata_t& GetMgefData   (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_MGEFDATA_SUBRECORD_SIZE; }

	/* Set class members */

 };
/*===========================================================================
 *		End of Class CObMgefDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obidledatasubrecord.H
 *=========================================================================*/
