/*===========================================================================
 *
 * File:	Obhedrsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBHEDRSUBRECORD_H
#define __OBHEDRSUBRECORD_H


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

	/* Special filespec values */
  #define OBHEDR_FILETYPE_MASTER 4278230808u

	/* Standard version data */
  #define OBHEDR_VERSION_DEFAULT 0.8f

	/* HEDR data size */
  #define OBHEDR_SUBRECORD_SIZE 12

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* HEDR data structure */
  struct obhedrdata_t {
	float Version;
	int   RecordCount;
	dword FileType;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObHedrSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObHedrSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObHedrSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  obhedrdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBHEDR_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBHEDR_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObHedrSubrecord();
  virtual void Destroy (void);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObHedrSubrecord* pSubrecord1 = ObCastClassNull(CObHedrSubrecord, pSubrecord);
	m_RecordSize = OBHEDR_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetHeaderData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObHedrSubrecord); }

	/* Get class members */
  obhedrdata_t& GetHeaderData  (void) { return (m_Data); }
  virtual byte*	GetData        (void) { return (byte *)(&m_Data); }
  int	        GetRecordCount (void) { return (m_Data.RecordCount); }
  float		GetVersion     (void) { return (m_Data.Version); }
  dword		GetFileType    (void) { return (m_Data.FileType); }
    
	/* Initialize a new record */
  void InitializeNew (void);

	/* Set class members */
  void SetRecordCount (const int   Value) { m_Data.RecordCount  = Value; }
  void ModRecordCount (const int   Value) { m_Data.RecordCount += Value; if ( m_Data.RecordCount < 0)  m_Data.RecordCount = 0; }
  void SetVersion     (const float Value) { m_Data.Version      = Value; }
  void SetFileType    (const dword Value) { m_Data.FileType     = Value; }

 };
/*===========================================================================
 *		End of Class CObHedrSubrecord Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obhedrsubrecord.H
 *=========================================================================*/
