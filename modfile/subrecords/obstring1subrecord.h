/*===========================================================================
 *
 * File:	Obstring1subrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObString1Subrecord used for storing a variable length
 * string that is not nul termianted when output.
 *
 *=========================================================================*/
#ifndef __OBSTRING1SUBRECORD_H
#define __OBSTRING1SUBRECORD_H


/*===========================================================================
 *
 * Begin Reqiured Includes
 *
 *=========================================================================*/
  #include "obstringsubrecord.h"
/*===========================================================================
 *		End of Reqiured Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObString1Subrecord Definition
 *
 * Defines a simple variable length string data subrecord that is not nul
 * terminated when output.
 *
 *=========================================================================*/
class CObString1Subrecord : public CObStringSubrecord {
  DECLARE_OBCLASS(CObString1Subrecord, CObStringSubrecord)

  /*---------- Begin Private Class Members ----------------------*/
private:


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File) { return File.Write((const SSCHAR *)m_String, m_String.GetLength()); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  //CObString1Subrecord();
  //virtual ~CObString1Subrecord() { Destroy(); }
  //virtual void Destroy (void);

  	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);
 
	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObString1Subrecord); }

	/* Get class members */
  virtual dword	GetRecordSize (void) const { return (m_String.GetLength()); }

  	/* Get a string representation of a subrecord field */
  virtual bool GetField (CSString& Buffer, const int FieldID);
  
 };
/*===========================================================================
 *		End of Class CObString1Subrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObString1Subrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
inline bool CObString1Subrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {
  CObStringSubrecord* pString = ObCastClass(CObStringSubrecord, pSubrecord);

  if (pString != NULL) {

    switch (FieldID) {
      case OB_FIELD_SCRIPTTEXT:
		Result = (pString != NULL) ? stricmp(GetString().c_str(), pString->GetString().c_str()) : 1;
		return (true);
     }

   }

	/* Skip the CObStringSubrecord base class */
  return CObSubrecord::CompareFields(Result, FieldID, pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObStringSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObString1Subrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObString1Subrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_SCRIPTTEXT:
        Buffer = GetString();
		return (true);
   }

	/* Skip the CObStringSubrecord base class */
  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObString1Subrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obstring1subrecord.H
 *=========================================================================*/
