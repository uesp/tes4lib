/*===========================================================================
 *
 * File:	Obbookdatasubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBOOKDATASUBRECORD_H
#define __OBBOOKDATASUBRECORD_H


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

	/* Standard BOOK-DATA subrecord size in bytes */
  #define OB_BOOKDATA_SUBRECORD_SIZE	10

	/* Ammo data flags */
  #define OB_BOOKFLAG_SCROLL 0x01
  #define OB_BOOKFLAG_NOTAKE 0x02

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Book DATA structure */
  struct obbookdata_t {
	byte	Flags;
	char	Teaches;
	dword	Value;
	float	Weight;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBookDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObBookDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObBookDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obbookdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_BOOKDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_BOOKDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBookDataSubrecord() { }
  //virtual ~CObBookDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObBookDataSubrecord* pSubrecord1 = ObCastClassNull(CObBookDataSubrecord, pSubrecord);
	m_RecordSize = OB_BOOKDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetBookData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObBookDataSubrecord); }

	/* Get class members */
  obbookdata_t& GetBookData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float         GetWeight    (void) { return (m_Data.Weight); }
  dword         GetValue     (void) { return (m_Data.Value); }
  char		GetTeaches   (void) { return (m_Data.Teaches); }
  
  bool IsNoTake (void) { return CheckFlagBits(m_Data.Flags, OB_BOOKFLAG_NOTAKE); }
  bool IsScroll (void) { return CheckFlagBits(m_Data.Flags, OB_BOOKFLAG_SCROLL); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_BOOKDATA_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue   (const dword Value) { m_Data.Value   = Value; }
  void SetWeight  (const float Value) { m_Data.Weight  = Value; }
  void SetTeaches (const char  Value) { m_Data.Teaches = Value; }

  void SetNoTake   (const bool Value) { FlipFlagBits(m_Data.Flags, OB_BOOKFLAG_NOTAKE, Value); }
  void SetIsScroll (const bool Value) { FlipFlagBits(m_Data.Flags, OB_BOOKFLAG_SCROLL, Value); }


 };
/*===========================================================================
 *		End of Class CObBookDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbookdatasubrecord.H
 *=========================================================================*/
