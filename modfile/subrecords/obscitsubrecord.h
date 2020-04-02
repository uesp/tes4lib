/*===========================================================================
 *
 * File:	Obscitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSCITSUBRECORD_H
#define __OBSCITSUBRECORD_H


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

	/* Standard SCIT subrecord size in bytes */
  #define OBSCIT_SUBRECORD_SIZE	16

	/* Flag values */
  #define OBSCIT_FLAG_HOSTILE 0x01

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* scIT data structure */
  struct obscitdata_t {
	obformid_t  ScriptFormID;
	dword	    School;
	obrectype_t VisualEffect;
	dword	    Flags;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObScitSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObScitSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObScitSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obscitdata_t	m_Data;
  obformid_t	m_OrigScriptFormID;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { 
	memset(&m_Data, 0, sizeof(obscitdata_t)); 
	bool Result = File.Read(&m_Data, m_RecordSize); 
	m_OrigScriptFormID = m_Data.ScriptFormID;
	return (Result); }

  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, m_RecordSize); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObScitSubrecord();
  //virtual ~CObScitSubrecord() { Destroy(); }
  virtual void Destroy (void);
  
  	/* Change any matching formid in the subrecord */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) { 
	if (m_Data.ScriptFormID == OldID) {
	  m_Data.ScriptFormID = NewID;
	  m_OrigScriptFormID  = NewID;
	  return (1);
	}
	return (0); 
  }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObScitSubrecord* pSubrecord1 = ObCastClassNull(CObScitSubrecord, pSubrecord);
	m_RecordSize = OBSCIT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetScitData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObScitSubrecord); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormID (CObFormidFixupArray& FixupArray) {
	return ObFixupFormid(m_Data.ScriptFormID, m_OrigScriptFormID, FixupArray);
  }

	/* Get class members */
  obscitdata_t& GetScitData         (void) { return (m_Data); }
  virtual byte*	GetData             (void) { return (byte *)(&m_Data); }
  bool          IsHostile           (void) { return ((m_Data.Flags & OBSCIT_FLAG_HOSTILE) != 0); }
  dword         GetSchool           (void) { return (m_Data.School); }
  obformid_t    GetScriptFormID     (void) { return (m_Data.ScriptFormID); }
  obformid_t    GetOrigScriptFormID (void) { return (m_OrigScriptFormID); }
  obrectype_t   GetVisualEffect     (void) { return (m_Data.VisualEffect); }
  
  	/* Get a string representation of a subrecord field */
  bool GetField (CSString& Buffer, const int FieldID);

	/* Initialize a new record */
  void InitializeNew (void);

	/* Set class members */
  void SetHostile          (const bool       Flag)  { if (Flag) m_Data.Flags |= OBSCIT_FLAG_HOSTILE; else m_Data.Flags &= ~OBSCIT_FLAG_HOSTILE; }
  void SetScriptFormID     (const obformid_t Value) { m_Data.ScriptFormID = Value; }
  void SetOrigScriptFormID (const obformid_t Value) { m_OrigScriptFormID  = Value; }
  void SetSchool           (const dword      Value) { m_Data.School       = Value; }
  void SetVisualEffect     (const SSCHAR*    pName) { m_Data.VisualEffect = pName; }

 };
/*===========================================================================
 *		End of Class CObScitSubrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScitSubrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
inline bool CObScitSubrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {
  CObScitSubrecord* pScit = ObCastClass(CObScitSubrecord, pSubrecord);

  switch (FieldID) {
    case OB_FIELD_SCRIPTSCHOOL:
    case OB_FIELD_SCHOOL:
        Result = (int) GetSchool();
	if (pScit != NULL) Result -= (int) pScit->GetSchool();
	return (true);
    case OB_FIELD_VISUALNAME:
        if (pScit == NULL)
	  Result = 1;
        else
          Result = strnicmp(GetVisualEffect().Name, pScit->GetVisualEffect().Name, OB_RECTYPE_SIZE);

	return (true);
    case OB_FIELD_HOSTILE:
        Result = (int) IsHostile();
	if (pScit != NULL) Result -= (int) pScit->IsHostile();
	return (true);
    case OB_FIELD_SCRIPTID:
	Result = (int)GetScriptFormID();
	if (pScit != NULL) Result -=  (int) pScit->GetScriptFormID();
	return (true);
   }

	/* Check subrecord */
  return CObSubrecord::CompareFields(Result, FieldID, pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObScitSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObScitSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObScitSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_HOSTILE:
        Buffer.Format("%s", BooleanToString(IsHostile()));
	return (true);
    case OB_FIELD_SCRIPTID:
        Buffer.Format("%08Xh", GetScriptFormID());
	return (true);
    case OB_FIELD_VISUALNAME:
        Buffer.Format("%4.4s", GetVisualEffect().Name);
	return (true);
    case OB_FIELD_SCRIPTSCHOOL:
    case OB_FIELD_SCHOOL:
        Buffer.Format("%s", GetObSpellSchoolString(GetSchool()));
	return (true);
   }

  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObScitSubrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obscitsubrecord.H
 *=========================================================================*/
