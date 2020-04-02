/*===========================================================================
 *
 * File:	Obcontdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBCONTDATASUBRECORD_H
#define __OBCONTDATASUBRECORD_H


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

  #define OB_CONTDATA_SUBRECORD_SIZE	5

  #define OB_CONTFLAG_RESPAWNS	0x02
   
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obcontdata_t {
	byte	Flags;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObContDataSubrecord Definition
 *
 *=========================================================================*/
class CObContDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObContDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obcontdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_CONTDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_CONTDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObContDataSubrecord() { }
  //virtual ~CObContDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObContDataSubrecord* pSubrecord1 = ObCastClassNull(CObContDataSubrecord, pSubrecord);
	m_RecordSize = OB_CONTDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetContianerData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObContDataSubrecord); }

	/* Get class members */
  obcontdata_t& GetContianerData (void) { return (m_Data); }
  virtual byte*	GetData          (void) { return (byte *)(&m_Data); }
  float         GetWeight        (void) { return (m_Data.Weight); }
  bool          IsRespawns       (void) { return CheckFlagBits(m_Data.Flags, OB_CONTFLAG_RESPAWNS); }
      
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_CONTDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetRespawns  (const bool   Flag) { FlipFlagBits(m_Data.Flags, OB_CONTFLAG_RESPAWNS, Flag);  }
  void SetWeight    (const float Value) { m_Data.Weight = Value; }

 };
/*===========================================================================
 *		End of Class CObContDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obcontdatasubrecord.H
 *=========================================================================*/
