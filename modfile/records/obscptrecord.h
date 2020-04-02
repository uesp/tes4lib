/*===========================================================================
 *
 * File:	Obscptrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Defines the CObScptRecord containing script data.
 *
 *=========================================================================*/
#ifndef __OBSCPTRECORD_H
#define __OBSCPTRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obidrecord.h"
  #include "../subrecords/obstring1subrecord.h"
  #include "../subrecords/obdwordsubrecord.h"
  #include "../subrecords/obschrsubrecord.h"
  #include "../subrecords/obscrosubrecord.h"
  #include "../subrecords/obslsdsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScptRecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObScptRecord : public CObIdRecord {
  DECLARE_OBSUBRECCREATE()
  DECLARE_OBFIELDMAP()
  DECLARE_OBCLASS(CObScptRecord, CObIdRecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObSchrSubrecord*	m_pScriptData;
  CObString1Subrecord*	m_pScriptText;
  CObDataSubrecord*	m_pCompiledData;

  dword			m_NumLines;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScptRecord();
  //virtual ~CObScptRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Adds a new local variable to the script */
  CObSlsdSubrecord*   AddVariable       (const char* pName, const word Index, const dword Flags);
  CObDwordSubrecord*  AddRefVariable    (const word Index);
  CObScroSubrecord*   AddReference      (const obformid_t FormID);

	/* Return a new instance of the class */
  static CObRecord* Create (void) { return new CObScptRecord; }

	/* Find a local variable */
  CObSlsdSubrecord* FindVariable      (const char* pName);
  int               FindVariableIndex (const char* pName);

  bool FindFirstVariable (CObSlsdSubrecord*& pLocal, CObStringSubrecord*& pName, int& Position) { Position = -1; return FindNextVariable(pLocal, pName, Position); }
  bool FindNextVariable  (CObSlsdSubrecord*& pLocal, CObStringSubrecord*& pName, int& Position);

  bool FindFirstReference (CObFormidSubrecord*& pReference, int& Position) { Position = -1; return FindNextReference(pReference, Position); }
  bool FindNextReference  (CObFormidSubrecord*& pReference, int& Position);
  
	/* Get class data */
  const SSCHAR* GetScriptText    (void) { return (m_pScriptText ? m_pScriptText->GetString().c_str() : ""); }
  byte*         GetScriptData    (void) { return (m_pCompiledData ? m_pCompiledData->GetData() : NULL); }
  dword	        GetScriptSize    (void) { return (m_pScriptText ? m_pScriptText->GetString().GetLength() : 0); }
  dword         GetType          (void) { return (m_pScriptData ? m_pScriptData->GetType() : OB_SCRIPTTYPE_OBJECT); }
  dword		    GetNumLines      (void) { return (m_NumLines); }
  dword         GetCompiledSize  (void) { return (m_pScriptData ? m_pScriptData->GetCompiledSize() : 0); }
  dword         GetVariableCount (void) { return (m_pScriptData ? m_pScriptData->GetVariableCount() : 0); }
  dword         GetRefCount      (void) { return (m_pScriptData ? m_pScriptData->GetRefCount() : 0); }

	/* Get the next available variable index */
  dword GetNextLocalVarIndex (void);
  dword GetNextLocalRefIndex (void);

	/* Checks if the given local variable definition is a reference */
  bool IsVariableReference (CObSlsdSubrecord* pLocal);

	/* Initialize a new record */
  void InitializeNew (void);

	/* Called to alert record of a new subrecord being added */
  virtual void OnAddSubrecord    (CObSubrecord* pSubrecord);
  virtual void OnDeleteSubrecord (CObSubrecord* pSubrecord);

	/* Read record data */
  bool ReadData (CObFile& File);

	/* Set class members */
  void SetScriptText    (const SSCHAR* pString);
  void SetScriptData    (const byte* pData, const word Size);
  void SetType          (const dword   Type)  { if (m_pScriptData) m_pScriptData->SetType(Type); }
  void SetCompiledSize  (const dword   Value) { if (m_pScriptData) m_pScriptData->SetCompiledSize(Value); }
  void SetVariableCount (const dword   Value) { if (m_pScriptData) m_pScriptData->SetVariableCount(Value); }
  void SetRefCount      (const dword   Value) { if (m_pScriptData) m_pScriptData->SetRefCount(Value); }
  //void ResetCounts      (void) { SetVariableCount(0); SetRefCount(0); }

	/* Update the script line count */
  void UpdateNumLines (void) { m_NumLines = m_pScriptText ? m_pScriptText->GetString().CountChar('\n') + 1 : 0; }

	/* Begin field method definitions */
  DECLARE_OBFIELD(FieldScriptText)
  DECLARE_OBFIELD(FieldType)

  DECLARE_OBGETFIELD(GetFieldNumLines)
  DECLARE_OBGETFIELD(GetFieldScriptSize)

  DECLARE_OBCOMPFIELD(CompareFieldNumLines)
  DECLARE_OBCOMPFIELD(CompareFieldScriptSize)

};
/*===========================================================================
 *		End of Class CObScptRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
  const SSCHAR* GetObScriptTypeString (const int Value);
  bool          GetObScriptTypeValue  (int& Value, const SSCHAR* pString);
/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObScptrecord.H
 *=========================================================================*/
