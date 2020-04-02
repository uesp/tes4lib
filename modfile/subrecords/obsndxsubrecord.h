/*===========================================================================
 *
 * File:	Obsndxsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSNDXSUBRECORD_H
#define __OBSNDXSUBRECORD_H


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

  #define OB_SNDX_SUBRECORD_SIZE	12

	/* Flags */
  #define OB_SNDXFLAG_RANDOMFREQSHIFT	0x0001
  #define OB_SNDXFLAG_RANDOMPLAY	0x0002
  #define OB_SNDXFLAG_IGNOREENVIRONMENT	0x0004
  #define OB_SNDXFLAG_RANDOMLOCATION	0x0008
  #define OB_SNDXFLAG_LOOP		0x0010
  #define OB_SNDXFLAG_MENUSOUND		0x0020
  #define OB_SNDXFLAG_2D		0x0040
  #define OB_SNDXFLAG_360LFE		0x0080

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obsndxdata_t {
	byte	MinAttenuation;
	byte	MaxAttenuation;
	char	FreqAdjustment;
	byte	Unknown1;
	word	Flags;
	word	Unknown2;
	word	StaticAttenuation;
	byte	StopTime;
	byte	StartTime;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSndxSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSndxSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSndxSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obsndxdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { memset(&m_Data, 0, sizeof(m_Data)); return File.Read(&m_Data, m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSndxSubrecord() { }
  //virtual ~CObSndxSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSndxSubrecord* pSubrecord1 = ObCastClassNull(CObSndxSubrecord, pSubrecord);
	m_RecordSize = OB_SNDX_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSoundData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSndxSubrecord); }

	/* Get class members */
  obsndxdata_t& GetSoundData           (void) { return (m_Data); }
  virtual byte*	GetData                (void) { return (byte *)(&m_Data); }
  byte          GetMinAttenuation      (void) { return (m_Data.MinAttenuation); }
  byte          GetMaxAttenuation      (void) { return (m_Data.MaxAttenuation); }
  char          GetFreqAdjustment      (void) { return (m_Data.FreqAdjustment); }
  word          GetStaticAttenuation   (void) { return (m_Data.StaticAttenuation); }
  byte		GetStartTime           (void) { return (m_Data.StartTime); }
  byte		GetStopTime            (void) { return (m_Data.StopTime); }
  bool          IsRandomFreqShift      (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMFREQSHIFT); }
  bool          IsRandomPlay           (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMPLAY); }
  bool          IsIgnoreEnvironment    (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_IGNOREENVIRONMENT); }
  bool          IsRandomLocation       (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMLOCATION); }
  bool          IsLoop                 (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_LOOP); }
  bool          IsMenuSound            (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_MENUSOUND); }
  bool          Is2DSound              (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_2D); }
  bool          Is360LFE               (void) { return CheckFlagBits(m_Data.Flags, OB_SNDXFLAG_360LFE); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_SNDX_SUBRECORD_SIZE; }

	/* Set class members */
  void SetMinAttenuation    (const byte Value) { m_Data.MinAttenuation     = Value; }
  void SetMaxAttenuation    (const byte Value) { m_Data.MaxAttenuation     = Value; }
  void SetFreqAdjustment    (const char Value) { m_Data.FreqAdjustment     = Value; }
  void SetStaticAttenuation (const word Value) { m_Data.StaticAttenuation  = Value; }
  void SetStartTime         (const byte Value) { m_Data.StartTime          = Value; }
  void SetStopTime          (const byte Value) { m_Data.StopTime           = Value; }
  void SetRandomFreqShift   (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMFREQSHIFT, Value); }
  void SetRandomPlay        (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMPLAY, Value); }
  void SetIgnoreEnvironment (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_IGNOREENVIRONMENT, Value); }
  void SetRandomLocation    (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_RANDOMLOCATION, Value); }
  void SetLoop              (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_LOOP, Value); }
  void SetMenuSound         (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_MENUSOUND, Value); }
  void Set2DSound           (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_2D, Value); }
  void Set360LFE            (const bool Value) { FlipFlagBits(m_Data.Flags, OB_SNDXFLAG_360LFE, Value); }

};
/*===========================================================================
 *		End of Class CObSndxSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obsndxsubrecord.H
 *=========================================================================*/
