/*===========================================================================
 *
 * File:	Obstringsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObStringSubrecord used for storing a variable length
 * string.
 *
 *=========================================================================*/
#ifndef __OBSTRINGSUBRECORD_H
#define __OBSTRINGSUBRECORD_H


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
 * Begin Class CObStringSubrecord Definition
 *
 * Defines a simple variable length string data subrecord.
 *
 *=========================================================================*/
class CObStringSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObStringSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString	m_String;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File) { return File.Write((const SSCHAR *)m_String, m_String.GetLength() + 1); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObStringSubrecord();
  //virtual ~CObStringSubrecord() { Destroy(); }
  virtual void Destroy (void);

  	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObStringSubrecord* pSubrecord1 = ObCastClassNull(CObStringSubrecord, pSubrecord);
	
	if (pSubrecord1 != NULL) {
	  m_String     = pSubrecord1->GetString();
	  m_RecordSize = GetRecordSize();
	}
	else {
	  m_RecordSize = 0;
	}
	return (true);
  }

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObStringSubrecord); }

	/* Get class members */
  CSString&     GetString     (void)       { return (m_String); }
  virtual byte*	GetData       (void)       { return (byte *)(const SSCHAR *)(m_String); }
  virtual dword	GetRecordSize (void) const { return (m_String.GetLength() + 1); }

	/* Get a string representation of a subrecord field */
  virtual bool GetField (CSString& Buffer, const int FieldID);

  	/* Set class methods */
  void SetString (const SSCHAR* pString) { m_String = pString; }

  
 };

	/* Known subrecord types that are always strings */
  typedef CObStringSubrecord CObFullSubrecord;	/* Full name */
  typedef CObStringSubrecord CObModlSubrecord;	/* Model filename */
  typedef CObStringSubrecord CObIconSubrecord;	/* Icon filename */

/*===========================================================================
 *		End of Class CObStringSubrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStringSubrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
inline bool CObStringSubrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {
  CObStringSubrecord* pString = ObCastClass(CObStringSubrecord, pSubrecord);

  switch (FieldID) {
    case OB_FIELD_EFFECTNAME:
    case OB_FIELD_ITEMNAME:
		Result = (pString != NULL) ? stricmp(GetString().c_str(), pString->GetString().c_str()) : 1;
		return (true);
   }

	/* No match */
  return CObSubrecord::CompareFields(Result, FieldID, pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObStringSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObStringSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObStringSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_EFFECTNAME:
    case OB_FIELD_ITEMNAME:
        Buffer = GetString();
		return (true);
   }

  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObStringSubrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obstringsubrec.H
 *=========================================================================*/
