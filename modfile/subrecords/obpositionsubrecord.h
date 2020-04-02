/*===========================================================================
 *
 * File:	ObPositionsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPOSITIONSUBRECORD_H
#define __OBPOSITIONSUBRECORD_H


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

	/* HEDR data size */
  #define OBPOSITION_SUBRECORD_SIZE 12

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obpositiondata_t {
	float X;
	float Y;
	float Z;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPositionSubrecord Definition
 *
 *=========================================================================*/
class CObPositionSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObPositionSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  obpositiondata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBPOSITION_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBPOSITION_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObHedrSubrecord();
  //virtual void Destroy (void);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObPositionSubrecord* pSubrecord1 = ObCastClassNull(CObPositionSubrecord, pSubrecord);
	m_RecordSize = OBPOSITION_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetPosition();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObPositionSubrecord); }

	/* Get class members */
  virtual byte*	    GetData     (void) { return (byte *)(&m_Data); }
  obpositiondata_t& GetPosition (void) { return (m_Data); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OBPOSITION_SUBRECORD_SIZE; }

	/* Set class members */

 };
/*===========================================================================
 *		End of Class CObPositionSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObPositionsubrecord.H
 *=========================================================================*/
