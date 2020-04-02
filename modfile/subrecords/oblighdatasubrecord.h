/*===========================================================================
 *
 * File:	ObLighdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBLIGHDATASUBRECORD_H
#define __OBLIGHDATASUBRECORD_H


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

	/* Standard LIGH-DATA subrecord size in bytes */
  #define OB_LIGHDATA_SUBRECORD_SIZE	32

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Light DATA structure */
  struct oblighdata_t {
	long		Time;
	dword		Radius;
	obrgba_t	Color;
	dword		Flags;
	float		Falloff;
	float		FOV;
	dword		Value;
	float		Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObLighDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObLighDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObLighDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  oblighdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { memset(&m_Data, 0, sizeof(oblighdata_t)); return File.Read(&m_Data, m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObLighDataSubrecord() { }
  //virtual ~CObLighDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObLighDataSubrecord* pSubrecord1 = ObCastClassNull(CObLighDataSubrecord, pSubrecord);
	m_RecordSize = OB_LIGHDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetLightData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObLighDataSubrecord); }

	/* Get class members */
  oblighdata_t& GetLightData  (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  long          GetTime       (void) { return (m_Data.Time); }
  dword         GetRadius     (void) { return (m_Data.Radius); }
  obrgba_t      GetColor      (void) { return (m_Data.Color); }
  dword         GetFlags      (void) { return (m_Data.Flags); }
  float         GetFalloff    (void) { return (m_Data.Falloff); }
  float         GetFOV        (void) { return (m_Data.FOV); }
  float         GetWeight     (void) { return (m_Data.Weight); }
  dword         GetValue      (void) { return (m_Data.Value); }

  dword         GetLightType  (void) { return (m_Data.Flags & OB_LIGHTYPE_MASK); }
  bool		IsDynamic     (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_DYNAMIC); }
  bool		IsCarried     (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_CARRIED); }
  bool		IsNegative    (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_NEGATIVE); }
  bool		IsDefaultOff  (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_DEFAULTOFF); }
  bool		IsFlicker     (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_FLICKER); }
  bool		IsFlickerSlow (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_FLICKERSLOW); }
  bool		IsPulse       (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_PULSE); }
  bool		IsPulseSlow   (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_PULSESLOW); }
  bool		IsTypeNone    (void) { return !CheckFlagBits(m_Data.Flags, OB_LIGHTYPE_MASK); }
  bool		IsSpotLight   (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_SPOTLIGHT); }
  bool		IsSpotShadow  (void) { return CheckFlagBits(m_Data.Flags, OB_LIGHFLAG_SPOTSHADOW); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_Data.Time = -1; m_Data.FOV = 90; m_RecordSize = OB_LIGHDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetTime       (const long     Value)   { m_Data.Time    = Value; }
  void SetRadius     (const dword    Value)   { m_Data.Radius  = Value; }
  void SetColor      (const obrgba_t Value)   { m_Data.Color   = Value; }
  void SetRedColor   (const byte     Value)   { m_Data.Color.R = Value; }
  void SetGreenColor (const byte     Value)   { m_Data.Color.G = Value; }
  void SetBlueColor  (const byte     Value)   { m_Data.Color.B = Value; }
  void SetFlags      (const dword    Value)   { m_Data.Flags   = Value; }
  void SetFalloff    (const float    Value)   { m_Data.Falloff = Value; }
  void SetFOV        (const float    Value)   { m_Data.FOV     = Value; }
  void SetValue      (const dword    Value)   { m_Data.Value   = Value; }
  void SetWeight     (const float    Value)   { m_Data.Weight  = Value; }

  void SetColor (const byte R, const byte G, const byte B) { m_Data.Color.R = R; m_Data.Color.G = G;  m_Data.Color.B = B; }

  void SetDynamic     (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_DYNAMIC,    Flag); }
  void SetCarried     (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_CARRIED,    Flag); }
  void SetNegative    (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_NEGATIVE,   Flag); }
  void SetDefaultOff  (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_DEFAULTOFF, Flag); }
  void SetSpotLight   (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_SPOTLIGHT,  Flag); }
  void SetSpotShadow  (const bool Flag) { FlipFlagBits(m_Data.Flags, OB_LIGHFLAG_SPOTSHADOW, Flag); }

  void SetLightType   (const dword Type) { m_Data.Flags &= ~OB_LIGHTYPE_MASK; m_Data.Flags |= Type & OB_LIGHTYPE_MASK; }
  void SetFlicker     (void) { SetLightType(OB_LIGHTYPE_FLICKER); }
  void SetFlickerSlow (void) { SetLightType(OB_LIGHTYPE_FLICKERSLOW); }
  void SetPulse       (void) { SetLightType(OB_LIGHTYPE_PULSE); }
  void SetPulseSlow   (void) { SetLightType(OB_LIGHTYPE_PULSESLOW); }
  void SetTypeNone    (void) { SetLightType(OB_LIGHTYPE_NONE); }
   
 };
/*===========================================================================
 *		End of Class CObLighDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObLighDatasubrecord.H
 *=========================================================================*/
