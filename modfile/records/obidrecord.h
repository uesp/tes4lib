/*===========================================================================
 *
 * File:	Obidrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Defines the CObIdRecord which is used to derive any record class that
 * have an editor ID (EDID).
 *
 *=========================================================================*/
#ifndef __OBIDRECORD_H
#define __OBIDRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObIdRecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObIdRecord : public CObRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObIdRecord, CObRecord)


  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObStringSubrecord* m_pEditorID;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObIdRecord();
  //virtual ~CObIdRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return (new CObIdRecord); }

	/* Get the current editor ID */
  const SSCHAR* GetEditorID (void) const            { return (m_pEditorID ? (const SSCHAR *)m_pEditorID->GetString().c_str() : ""); }
  bool          IsEditorID  (const SSCHAR* pString) { return SafeStringCompare(GetEditorID(), pString, true) == 0; }
  bool          HasEditorID (void) const            { return (m_pEditorID != NULL && m_pEditorID->GetString()[0] != NULL_CHAR); }

	/* Initialize a new record */
  virtual void InitializeNew (void);

	/* Called when a subrecord is added to the record */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);
  
	/* Set the editor ID */
  void SetEditorID (const SSCHAR *pData);

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldEditorID)

};
/*===========================================================================
 *		End of Class CObIdRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Array of record pointers  */
  typedef CObPtrArray<CObIdRecord>    CObIdRecordArray;
  typedef CObRefPtrArray<CObIdRecord> CObRefIdRecordArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obidrecord.H
 *=========================================================================*/
