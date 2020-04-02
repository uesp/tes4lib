/*===========================================================================
 *
 * File:	ObXtelSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBXTELSUBRECORD_H
#define __OBXTELSUBRECORD_H


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

	/* Standard XTEL subrecord size in bytes */
  #define OB_XTEL_SUBRECORD_SIZE	28

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Teleport data structure */
  struct obxteldata_t {
	obformid_t	FormID;		/* Destination form ID */
	float		X, Y, Z;	/* Position */
	float		AX, AY, AZ;	/* Angle in radians */
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObXtelSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObXtelSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObXtelSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obxteldata_t	m_Data;
  

  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { bool Result = File.Read(&m_Data,  OB_XTEL_SUBRECORD_SIZE); return (Result); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_XTEL_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObXtelSubrecord() { }
  //virtual ~CObXtelSubrecord() { Destroy(); }
  //virtual void Destroy (void) { CObSubrecord::Destroy(); }

  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.FormID == OldID) {
	  m_Data.FormID = NewID;
	  return (1);
	}
	return (0); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObXtelSubrecord* pSubrecord1 = ObCastClassNull(CObXtelSubrecord, pSubrecord);
	m_RecordSize = OB_XTEL_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetXtelData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }
  
    	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObXtelSubrecord); }

	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.FormID, m_Data.FormID, FixupArray);
  }

	/* Get class members */
  obxteldata_t& GetXtelData   (void) { return (m_Data); }
  virtual byte*	GetData       (void) { return (byte *)(&m_Data); }
  obformid_t    GetFormID     (void) { return (m_Data.FormID); }
  float	        GetX          (void) { return (m_Data.X); }
  float	        GetY          (void) { return (m_Data.Y); }
  float	        GetZ          (void) { return (m_Data.Z); }
  float	        GetAX         (void) { return (m_Data.AX); }
  float	        GetAY         (void) { return (m_Data.AY); }
  float	        GetAZ         (void) { return (m_Data.AZ); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_XTEL_SUBRECORD_SIZE; }

	/* Set class members */

 };
/*===========================================================================
 *		End of Class CObXtelSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObXtelSubrecord.H
 *=========================================================================*/
