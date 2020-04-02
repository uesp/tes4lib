/*===========================================================================
 *
 * File:	Obnamesubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObNameSubrecord used for storing a 4-byte name ID string.
 *
 *=========================================================================*/
#ifndef __OBNAMESUBRECORD_H
#define __OBNAMESUBRECORD_H


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
 * Begin Class CObNameSubrecord Definition
 *
 * Defines a 4-byte name ID string data subrecord.
 *
 *=========================================================================*/
class CObNameSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObNameSubrecord, CObSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  obrectype_t m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(m_Data.Name, OB_RECTYPE_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(m_Data.Name, OB_RECTYPE_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObNameSubrecord();
  //virtual ~CObNameSubrecord() { Destroy(); }
  virtual void Destroy (void);

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObNameSubrecord* pSubrecord1 = ObCastClassNull(CObNameSubrecord, pSubrecord);
	m_RecordSize = OB_RECTYPE_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetDataName();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObNameSubrecord); }

	/* Get class members */
  const obrectype_t& GetDataName (void) { return (m_Data); }
  virtual byte*      GetData     (void) { return (byte *)(m_Data.Name); }

  	/* Get a string representation of a subrecord field */
  bool GetField (CSString& Buffer, const int FieldID);

	/* Initialize a new record */
  void InitializeNew (void);

  	/* Set class methods */
  void SetDataName (const SSCHAR*  pString) { m_Data = pString; }
  void SetDataName (const obrectype_t Type) { m_Data = Type; }
  
 };

	/* Synonyms for the name type */
  typedef CObNameSubrecord CObEfidSubrecord;

/*===========================================================================
 *		End of Class CObNameSubrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObNameSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObNameSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_NAME2:
    case OB_FIELD_DATANAME:
        Buffer.Format("%4.4s", GetDataName().Name);
	return (true);
   }

  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObNameSubrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obnamesubrecord.H
 *=========================================================================*/
