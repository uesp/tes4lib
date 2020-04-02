/*===========================================================================
 *
 * File:	Obscptrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscptrecord.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObScptRecord, CObIdRecord)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCHR, CObSchrSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCDA, CObDataSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCTX, CObString1Subrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SLSD, CObSlsdSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCVR, CObStringSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRO, CObScroSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCRV, CObDwordSubrecord::Create)
	DEFINE_OBSUBRECCREATE(OB_NAME_SCVR, CObStringSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObScptRecord, CObIdRecord)
	ADD_OBFIELDALL("ScriptText", OB_FIELD_SCRIPTTEXT, 0, CObScptRecord, FieldScriptText)
	ADD_OBFIELDALL("Type",       OB_FIELD_TYPE,       0, CObScptRecord, FieldType)

	ADD_OBFIELDMAP("ScriptSize", OB_FIELD_SIZE,       0, &CObScptRecord::GetFieldScriptSize, NULL, &CObScptRecord::CompareFieldScriptSize)
	ADD_OBFIELDMAP("LineCount",  OB_FIELD_LINECOUNT,  0, &CObScptRecord::GetFieldNumLines,   NULL, &CObScptRecord::CompareFieldNumLines)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Script Types Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObScriptTypes)
	ADD_STRINGVALUE( OB_SCRIPTTYPE_OBJECT,		"Object")
	ADD_STRINGVALUE( OB_SCRIPTTYPE_QUEST,		"Quest")
	ADD_STRINGVALUE( OB_SCRIPTTYPE_MAGICEFFECT,	"Magic Effect")
END_STRINGVALUE()
/*===========================================================================
 *		End of Script Types Table
 *=========================================================================*/
 

/*===========================================================================
 *
 * Class CObScptRecord Constructor
 *
 *=========================================================================*/
CObScptRecord::CObScptRecord () {
  m_pScriptText   = NULL;
  m_pScriptData   = NULL;
  m_pCompiledData = NULL;
  m_NumLines      = 0;
 }
/*===========================================================================
 *		End of Class CObScptRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObScptRecord::Destroy (void) {
  m_pScriptText   = NULL;
  m_pScriptData   = NULL;
  m_pCompiledData = NULL;
  m_NumLines      = 0;

  CObIdRecord::Destroy();
 }
/*===========================================================================
 *		End of Class Method CObScptRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - CObScroSubrecord* AddReference (FormID);
 *
 *=========================================================================*/
CObScroSubrecord* CObScptRecord::AddReference (const obformid_t FormID) {
  CObScroSubrecord* pScroSubrecord;
  CObSubrecord*     pSubrecord;
  
  pSubrecord = AddNewSubrecord(OB_NAME_SCRO);
  if (pSubrecord == NULL) return (NULL);
  pSubrecord->InitializeNew();

  pScroSubrecord = ObCastClass(CObScroSubrecord, pSubrecord);
  if (pScroSubrecord == NULL) return (NULL);

  pScroSubrecord->SetValue(FormID);
  return (pScroSubrecord);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::AddReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - CObDwordSubrecord* AddRefVariable (Index);
 *
 *=========================================================================*/
CObDwordSubrecord* CObScptRecord::AddRefVariable (const word Index) {
  CObDwordSubrecord* pScrvSubrecord;
  CObSubrecord*      pSubrecord;
  
  pSubrecord = AddNewSubrecord(OB_NAME_SCRV);
  if (pSubrecord == NULL) return (NULL);
  pSubrecord->InitializeNew();

  pScrvSubrecord = ObCastClass(CObDwordSubrecord, pSubrecord);
  if (pScrvSubrecord == NULL) return (NULL);

  pScrvSubrecord->SetValue(Index);
  return (pScrvSubrecord);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::AddRefVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - CObSlsdSubrecord* AddVariable (pName, Index, Flags);
 *
 *=========================================================================*/
CObSlsdSubrecord* CObScptRecord::AddVariable (const char* pName, const word Index, const dword Flags) {
  CObSlsdSubrecord*   pSlsdSubrecord;
  CObStringSubrecord* pScvrSubrecord;
  CObSubrecord*       pSubrecord;

  pSubrecord = AddNewSubrecord(OB_NAME_SLSD);
  if (pSubrecord == NULL) return (NULL);
  pSubrecord->InitializeNew();

  pSlsdSubrecord = ObCastClass(CObSlsdSubrecord, pSubrecord);
  if (pSlsdSubrecord == NULL) return (NULL);

  pSlsdSubrecord->SetIndex(Index);
  pSlsdSubrecord->SetFlags(Flags);

  pSubrecord = AddNewSubrecord(OB_NAME_SCVR);
  if (pSubrecord == NULL) return (NULL);
  pSubrecord->InitializeNew();

  pScvrSubrecord = ObCastClass(CObStringSubrecord, pSubrecord);
  if (pScvrSubrecord == NULL) return (NULL);

  pScvrSubrecord->SetString(pName);
  return (pSlsdSubrecord);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::AddVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - CObSlsdSubrecord* FindVariable (pName);
 *
 *=========================================================================*/
CObSlsdSubrecord* CObScptRecord::FindVariable (const char* pName) {
  CObSubrecord*       pSubrecord;
  CObSubrecord*       pSubrecord1;
  CObSlsdSubrecord*   pSlsdSubrecord;
  int                 Position;
  
  pSubrecord = FindFirstSubrecord(OB_NAME_SLSD, Position);

  while (pSubrecord != NULL) {
    pSubrecord1 = GetSubrecord(pSubrecord, 1, OB_NAME_SCVR);
    
    if (pSubrecord1 != NULL) {
      pSlsdSubrecord = ObCastClass(CObSlsdSubrecord, pSubrecord);
      if (pSlsdSubrecord != NULL && stricmp((const char *)pSubrecord1->GetData(), pName) == 0) return (pSlsdSubrecord);
    }
    
    pSubrecord = FindNextSubrecord(OB_NAME_SLSD, Position);
  }

  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::FindVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - int FindVariableIndex (pName);
 *
 *=========================================================================*/
int CObScptRecord::FindVariableIndex (const char* pName) {
  CObSlsdSubrecord* pSubrecord;

  pSubrecord = FindVariable(pName);
  if (pSubrecord == NULL) return (-1);

  return (pSubrecord->GetSlsdData().Index);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::FindVariableIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - bool FindNextVariable (pLocal, pName, Position);
 *
 *=========================================================================*/
bool CObScptRecord::FindNextVariable (CObSlsdSubrecord*& pLocal, CObStringSubrecord*& pName, int& Position) {
  CObSubrecord* pSubrecord;

  ++Position;

  if (Position < 0 || Position >= m_Subrecords.GetSize()) {
    pLocal = NULL;
    pName  = NULL;
    return (false);
  }

  for (; Position < m_Subrecords.GetSize(); ++Position) {
    pSubrecord = m_Subrecords.GetAt(Position);
    if (pSubrecord->GetRecordType() != OB_NAME_SLSD) continue;

    pLocal = ObCastClass(CObSlsdSubrecord, pSubrecord);
    if (pLocal == NULL) continue;

    pSubrecord = m_Subrecords.GetAt(Position + 1);
    if (pSubrecord == NULL) continue;

    pName = ObCastClass(CObStringSubrecord, pSubrecord);
    if (pName == NULL) continue;
    
    return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::FindNextVariable()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - bool FindNextReference (pReference, Position);
 *
 *=========================================================================*/
bool CObScptRecord::FindNextReference (CObFormidSubrecord*& pReference, int& Position) {
  CObSubrecord* pSubrecord;

  ++Position;

  if (Position < 0 || Position >= m_Subrecords.GetSize()) {
    pReference = NULL;
    return (false);
  }

  for (; Position < m_Subrecords.GetSize(); ++Position) {
    pSubrecord = m_Subrecords.GetAt(Position);
    if (pSubrecord->GetRecordType() != OB_NAME_SCRO) continue;

    pReference = ObCastClass(CObFormidSubrecord, pSubrecord);
    if (pReference == NULL) continue;
    
    return (true);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::FindNextReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - dword GetNextLocalVarIndex (void);
 *
 *=========================================================================*/
dword CObScptRecord::GetNextLocalVarIndex (void) {
  if (m_pScriptData == NULL) return (0);

  return ++m_pScriptData->GetScriptData().VariableCount;
}
/*===========================================================================
 *		End of Class Method CObScptRecord::GetNextLocalVarIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - dword GetNextLocalRefIndex (void);
 *
 *=========================================================================*/
dword CObScptRecord::GetNextLocalRefIndex (void) {
  if (m_pScriptData == NULL) return (0);

  return ++m_pScriptData->GetScriptData().RefCount;
}
/*===========================================================================
 *		End of Class Method CObScptRecord::GetNextLocalRefIndex()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObScptRecord::InitializeNew (void) {

  CObIdRecord::InitializeNew();
  
  AddNewSubrecord(OB_NAME_SCHR);
  if (m_pScriptData != NULL) m_pScriptData->InitializeNew();

  AddNewSubrecord(OB_NAME_SCDA);

  if (m_pCompiledData != NULL) {
    m_pCompiledData->InitializeNew();
    m_pCompiledData->AllocateNew(4);
    *(dword *)m_pCompiledData->GetData() = 0x1D;

    if (m_pScriptData != NULL) m_pScriptData->GetScriptData().CompiledSize = 4;
  }

  AddNewSubrecord(OB_NAME_SCTX);
  if (m_pScriptText != NULL) m_pScriptText->InitializeNew();

}
/*===========================================================================
 *		End of Class Method CObScptRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - bool IsVariableReference (pLocal);
 *
 *=========================================================================*/
bool CObScptRecord::IsVariableReference (CObSlsdSubrecord* pLocal) {
  CObSubrecord*       pSubrecord;
  CObDwordSubrecord*  pScrvSubrecord = NULL;
  int                 Position;

	/* Ignore invalid input */
  if (pLocal = NULL) return (false);

	/* Find a SCRV subrecord with the same index as the input local */
  pSubrecord = FindFirstSubrecord(OB_NAME_SCRV, Position);

  while (pSubrecord != NULL) {
    pScrvSubrecord = ObCastClass(CObDwordSubrecord, pSubrecord);

    if (pScrvSubrecord != NULL && pScrvSubrecord->GetValue() == pLocal->GetIndex()) {
      return (true);
    }

    pSubrecord = FindNextSubrecord(OB_NAME_SCRV, Position);
  }

  return (false);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::IsVariableReference()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObScptRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_SCTX) {
    m_pScriptText = ObCastClass(CObString1Subrecord, pSubrecord);
    UpdateNumLines();
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCHR) {
    m_pScriptData = ObCastClass(CObSchrSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCDA) {
    m_pCompiledData = ObCastClass(CObDataSubrecord, pSubrecord);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SLSD) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 24, OB_NAME_SLSD);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCVR) {
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCRO) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_SCRO);
   }
  else if (pSubrecord->GetRecordType() == OB_NAME_SCRV) {
    //TEST_INTVALUE1(pSubrecord->GetRecordSize(), 4, OB_NAME_SCRV);
   }
  else
    CObIdRecord::OnAddSubrecord(pSubrecord);

 }
/*===========================================================================
 *		End of Class Event CObScptRecord::OnAddSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObScptRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pScriptText == pSubrecord) {
    m_pScriptText = NULL;
  }
  else if (m_pScriptData == pSubrecord) {
    m_pScriptData = NULL;
  }
  else if (m_pCompiledData == pSubrecord) {
    m_pCompiledData = NULL;
  }
  else
    CObIdRecord::OnDeleteSubrecord(pSubrecord);

}
/*===========================================================================
 *		End of Class Event CObScptRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObScptRecord::ReadData (CObFile& File) {
  bool Result = CObIdRecord::ReadData(File);

  UpdateNumLines();
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - void SetScriptText (pString);
 *
 *=========================================================================*/
void CObScptRecord::SetScriptText (const SSCHAR* pString) { 

  if (m_pScriptText == NULL) {
    AddNewSubrecord(OB_NAME_SCTX);
    if (m_pScriptText == NULL) return;
    m_pScriptText->InitializeNew();
  } 

  m_pScriptText->SetString(pString); 
  UpdateNumLines();
}
/*===========================================================================
 *		End of Class Method CObScptRecord::SetScriptText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScptRecord Method - void SetScriptData (pString);
 *
 *=========================================================================*/
void CObScptRecord::SetScriptData (const byte* pData, const word Size) { 

  if (m_pCompiledData == NULL) {
    AddNewSubrecord(OB_NAME_SCDA);
    if (m_pCompiledData == NULL) return;
    m_pCompiledData->InitializeNew();
  } 

  m_pCompiledData->SetData(pData, Size); 
  SetCompiledSize(Size);
}
/*===========================================================================
 *		End of Class Method CObScptRecord::SetScriptData()
 *=========================================================================*/


/*===========================================================================
 *
 * Get String from a Value Functions
 *
 *=========================================================================*/
const SSCHAR* GetObScriptTypeString (const int Value) { return FindStringValue(Value, s_ObScriptTypes); }

bool GetObScriptTypeValue (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObScriptTypes); }
/*===========================================================================
 *		End of Get a Value from a String
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObScptRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObScptRecord::GetFieldScriptText, String = GetScriptText() )
DEFINE_OBGETFIELD(CObScptRecord::GetFieldType,       String = GetObScriptTypeString(GetType()) )
DEFINE_OBGETFIELD(CObScptRecord::GetFieldNumLines,   String.Format("%u", GetNumLines()) )
DEFINE_OBGETFIELD(CObScptRecord::GetFieldScriptSize, String.Format("%u", GetScriptSize()) )
/*===========================================================================
 *		End of CObScptRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObScptRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDSTRING(CObScptRecord, CompareFieldScriptText, GetScriptText)
DEFINE_OBCOMPFIELDDWORD(CObScptRecord, CompareFieldType, GetType)
DEFINE_OBCOMPFIELDDWORD(CObScptRecord, CompareFieldNumLines, GetNumLines)
DEFINE_OBCOMPFIELDDWORD(CObScptRecord, CompareFieldScriptSize, GetScriptSize)
/*===========================================================================
 *		End of CObScptRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObScptRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObScptRecord::SetFieldScriptText)
  SetScriptText(pString);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObScptRecord::SetFieldType)
  int Value;

  if (!GetObScriptTypeValue(Value, pString)) {
    AddObGeneralError("The string '%s' is not a valid script type!", pString);
    return (false);
  }

  SetType(Value);
END_OBSETFIELD()
/*===========================================================================
 *		End of CObRecord Set Field Methods
 *=========================================================================*/
