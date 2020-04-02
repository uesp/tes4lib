/*===========================================================================
 *
 * File:	ObRefrDataSubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBREFRDATASUBRECORD_H
#define __OBREFRDATASUBRECORD_H


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

	/* Standard REFR-DATA subrecord size in bytes */
  #define OB_REFRDATA_SUBRECORD_SIZE	24

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Misc DATA structure */
  struct obrefrdata_t {
	float	X, Y, Z;	/* Position */
	float	AX, AY, AZ;	/* Angle in radians */
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefrDataSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObRefrDataSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObRefrDataSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obrefrdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_REFRDATA_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_REFRDATA_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRefrDataSubrecord() { }
  //virtual ~CObRefrDataSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObRefrDataSubrecord* pSubrecord1 = ObCastClassNull(CObRefrDataSubrecord, pSubrecord);
	m_RecordSize = OB_REFRDATA_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetRefrData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObRefrDataSubrecord); }

	/* Get class members */
  obrefrdata_t& GetRefrData  (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  float	        GetX         (void) { return (m_Data.X); }
  float	        GetY         (void) { return (m_Data.Y); }
  float	        GetZ         (void) { return (m_Data.Z); }
  float	        GetAX        (void) { return (m_Data.AX); }
  float	        GetAY        (void) { return (m_Data.AY); }
  float	        GetAZ        (void) { return (m_Data.AZ); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_REFRDATA_SUBRECORD_SIZE; }

	/* Set class members */

 };
/*===========================================================================
 *		End of Class CObRefrDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObRefrDataSubrecord.H
 *=========================================================================*/
