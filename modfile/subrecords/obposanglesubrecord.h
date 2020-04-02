/*===========================================================================
 *
 * File:	ObPosAnglesubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPOSANGLESUBRECORD_H
#define __OBPOSANGLESUBRECORD_H


/*===========================================================================
 *
 * Begin Reqiured Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Reqiured Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

  #define OBPOSANGLE_SUBRECORD_SIZE 24

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obposangledata_t {
	float X;
	float Y;
	float Z;
	float AX;
	float AY;
	float AZ;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPosAngleSubrecord Definition
 *
 *=========================================================================*/
class CObPosAngleSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObPosAngleSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  obposangledata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBPOSANGLE_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBPOSANGLE_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObHedrSubrecord();
  //virtual void Destroy (void);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObPosAngleSubrecord* pSubrecord1 = ObCastClassNull(CObPosAngleSubrecord, pSubrecord);
	m_RecordSize = OBPOSANGLE_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetPosition();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObPosAngleSubrecord); }

	/* Get class members */
  virtual byte*	    GetData     (void) { return (byte *)(&m_Data); }
  obposangledata_t& GetPosition (void) { return (m_Data); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBPOSANGLE_SUBRECORD_SIZE; }

	/* Set class members */

 };
/*===========================================================================
 *		End of Class CObPosAngleSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObPosAnglesubrecord.H
 *=========================================================================*/
