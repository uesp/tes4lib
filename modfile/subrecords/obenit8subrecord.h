/*===========================================================================
 *
 * File:	Obenit8subrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBENIT8SUBRECORD_H
#define __OBENIT8SUBRECORD_H


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

	/* Standard ENIT subrecord size in bytes */
  #define OBENIT8_SUBRECORD_SIZE	8

	/* Data flags */
  #define OB_ALCHFLAG_MANUALCALC 0x00000001
  #define OB_ALCHFLAG_FOODITEM   0x00000002

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* ENIT8 data structure */
  struct obenit8data_t {
	dword Value;
	dword Flags;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEnit8Subrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObEnit8Subrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObEnit8Subrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obenit8data_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBENIT8_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBENIT8_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEnit8Subrecord() { }
  //virtual ~CObEnit8Subrecord() { Destroy(); }
  //virtual void Destroy (void);

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObEnit8Subrecord* pSubrecord1 = ObCastClassNull(CObEnit8Subrecord, pSubrecord);
	m_RecordSize = OBENIT8_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetEnitData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObEnit8Subrecord); }

	/* Get class members */
  obenit8data_t& GetEnitData    (void) { return (m_Data); }
  virtual byte*	 GetData        (void) { return (byte *)(&m_Data); }
  dword		 GetValue       (void) { return (m_Data.Value); }
  dword		 GetFlags       (void) { return (m_Data.Flags); }
  bool           IsAutoCalc     (void) { return !CheckFlagBits(m_Data.Flags, OB_ALCHFLAG_MANUALCALC); }
  bool           IsFoodItem     (void) { return CheckFlagBits(m_Data.Flags, OB_ALCHFLAG_FOODITEM); }

	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBENIT8_SUBRECORD_SIZE; }

	/* Set class members */
  void SetAutoCalc (const bool  Flag)  { FlipFlagBits(m_Data.Flags,  OB_ALCHFLAG_MANUALCALC, !Flag); }
  void SetFoodItem (const bool  Flag)  { FlipFlagBits(m_Data.Flags,  OB_ALCHFLAG_FOODITEM,    Flag); }
  void SetFlags    (const dword Value) { m_Data.Flags = Value; }
  void SetValue    (const dword Value) { m_Data.Value = Value; }

 };
/*===========================================================================
 *		End of Class CObEnit8Subrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obenit8subrecord.H
 *=========================================================================*/
