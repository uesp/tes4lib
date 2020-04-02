/*===========================================================================
 *
 * File:	Obscitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSLSDSUBRECORD_H
#define __OBSLSDSUBRECORD_H


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

  #define OBSLSD_SUBRECORD_SIZE	24

  #define OBSLSD_FLAG_SHORTLONG 1
  #define OBSLSD_FLAG_MASK      0x000000FF


/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obslsddata_t {
	dword		Index;
	dword		Unknown1;
	dword		Unknown2;
	dword		Unknown3;
	dword		Flags;
	dword		Unknown4;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSlsdSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSlsdSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSlsdSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obslsddata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  m_RecordSize); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSlsdSubrecord() { }
  //virtual ~CObSlsdSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }
  
 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSlsdSubrecord* pSubrecord1 = ObCastClassNull(CObSlsdSubrecord, pSubrecord);
	m_RecordSize = OBSLSD_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetSlsdData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSlsdSubrecord); }

	/* Get class members */
  obslsddata_t& GetSlsdData         (void) { return (m_Data); }
  virtual byte*	GetData             (void) { return (byte *)(&m_Data); }
  bool          IsShortLong         (void) { return (m_Data.Flags & OBSLSD_FLAG_SHORTLONG) != 0; }
  dword         GetIndex            (void) { return (m_Data.Index); }
  dword         GetFlags            (void) { return (m_Data.Flags); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBSLSD_SUBRECORD_SIZE;  }

	/* Set class members */
  void SetShortLong (const bool   Flag) { FlipFlagBits(m_Data.Flags, OBSLSD_FLAG_SHORTLONG, Flag); }
  void SetIndex     (const dword Value) { m_Data.Index = Value; }
  void SetFlags     (const dword Value) { m_Data.Flags = Value; }

};
/*===========================================================================
 *		End of Class CObSlsdSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObSlsdSubrecord.H
 *=========================================================================*/
