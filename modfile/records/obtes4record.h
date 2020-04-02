/*===========================================================================
 *
 * File:	Obtes4record.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObTes4Record containing the header data for an ESM/ESP file.
 *
 *=========================================================================*/
#ifndef __OBTES4RECORD_H
#define __OBTES4RECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecord.h"
  #include "../subrecords/obhedrsubrecord.h"
  #include "../subrecords/obstringsubrecord.h"
  #include "../subrecords/obint64subrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObTes4Record Definition
 *
 * Description
 *
 *=========================================================================*/
class CObTes4Record : public CObRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObTes4Record, CObRecord)

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObHedrSubrecord*	m_pHeader;
  CObStringSubrecord*	m_pCreatedBy;
  CObStringSubrecord*	m_pSummary;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObTes4Record();
  //virtual ~CObTes4Record() { Destroy(); }
  virtual void Destroy (void);

	/* Add a master file */
  void AddMaster (const SSCHAR* pMaster, const int64 FileSize);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObTes4Record; }

	/* Delete all master definitions in the file */
  void DeleteMasters (void);

	/* Get class data */
  const SSCHAR* GetAuthor      (void) { return (m_pCreatedBy ? m_pCreatedBy->GetString().c_str()   : ""); }
  const SSCHAR* GetSummary     (void) { return (m_pSummary   ? m_pSummary->GetString().c_str()     : ""); }
  int		GetRecordCount (void) { return (m_pHeader    ? m_pHeader->GetRecordCount() : 0); }
  float		GetVersion     (void) { return (m_pHeader    ? m_pHeader->GetVersion()     : 0.0f); }
  dword		GetFileType    (void) { return (m_pHeader    ? m_pHeader->GetFileType()    : 0); }

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Modify the record count value */
  void ModRecordCount (const int Value) { if (m_pHeader != NULL) m_pHeader->ModRecordCount(Value); }

	/* Set class members */
  void SetVersion     (const float  Value) { if (m_pHeader) m_pHeader->SetVersion(Value); }
  void SetFileType    (const dword  Value) { if (m_pHeader) m_pHeader->SetFileType(Value); }
  void SetRecordCount (const int    Value) { if (m_pHeader) m_pHeader->SetRecordCount(Value); }

  void SetAuthor  (const SSCHAR* pString);
  void SetSummary (const SSCHAR* pString);

	/* Begin field method definitions */
  DECLARE_OBGETFIELD(GetFieldSummary)
  DECLARE_OBGETFIELD(GetFieldAuthor)
  DECLARE_OBGETFIELD(GetFieldVersion)
  DECLARE_OBGETFIELD(GetFieldRecordCount)
  DECLARE_OBGETFIELD(GetFieldFileType)

  DECLARE_OBCOMPFIELD(CompareFieldSummary)
  DECLARE_OBCOMPFIELD(CompareFieldAuthor)
  DECLARE_OBCOMPFIELD(CompareFieldVersion)
  DECLARE_OBCOMPFIELD(CompareFieldRecordCount)
  DECLARE_OBCOMPFIELD(CompareFieldFileType)

  DECLARE_OBSETFIELD(SetFieldSummary)
  DECLARE_OBSETFIELD(SetFieldAuthor)
 };
/*===========================================================================
 *		End of Class CObTes4Record Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obtes4record.H
 *=========================================================================*/
