/*===========================================================================
 *
 * File:	Obpfpcsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBPFPCSUBRECORD_H
#define __OBPFPCSUBRECORD_H


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

  #define OB_PFPC_SUBRECORD_SIZE 4

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  struct obpfpcdata_t {
	byte Spring;
	byte Summer;
	byte Fall;
	byte Winter;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObPfpcSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObPfpcSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObPfpcSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obpfpcdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_PFPC_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_PFPC_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObPfpcSubrecord() { }
  //virtual ~CObPfpcSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObPfpcSubrecord* pSubrecord1 = ObCastClassNull(CObPfpcSubrecord, pSubrecord);
	m_RecordSize = OB_PFPC_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetFloraData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObPfpcSubrecord); }

	/* Get class members */
  obpfpcdata_t& GetFloraData (void) { return (m_Data); }
  virtual byte*	GetData      (void) { return (byte *)(&m_Data); }
  byte          GetSummer    (void) { return (m_Data.Summer); }
  byte          GetFall      (void) { return (m_Data.Fall); }
  byte          GetWinter    (void) { return (m_Data.Winter); }
  byte          GetSpring    (void) { return (m_Data.Spring); }
    
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_PFPC_SUBRECORD_SIZE; }

	/* Set class members */
  void SetSummer (const byte Value)   { m_Data.Summer = Value; }
  void SetFall   (const byte Value)   { m_Data.Fall   = Value; }
  void SetWinter (const byte Value)   { m_Data.Winter = Value; }
  void SetSpring (const byte Value)   { m_Data.Spring = Value; }

};
/*===========================================================================
 *		End of Class CObPfpcSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obpfpcsubrecord.H
 *=========================================================================*/
