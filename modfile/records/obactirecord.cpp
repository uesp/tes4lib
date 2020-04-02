/*===========================================================================
 *
 * File:	ObActiRecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	14 September, 2006
 *
 * Implements the CObActiRecord class for activator records.
 *
 *=========================================================================*/

	/* Include Files */
#include "obactirecord.h"
#include "../obrecordhandler.h"


/*===========================================================================
 *
 * Begin Subrecord Creation Array
 *
 *=========================================================================*/
BEGIN_OBSUBRECCREATE(CObActiRecord, CObItem1Record)
	DEFINE_OBSUBRECCREATE(OB_NAME_SNAM, CObFormidSubrecord::Create)
END_OBSUBRECCREATE()
/*===========================================================================
 *		End of Subrecord Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiRecord Field Map
 *
 *=========================================================================*/
BEGIN_OBFIELDMAP(CObActiRecord, CObItem1Record)
	ADD_OBFIELDALL("Sound",   OB_FIELD_SOUND,   0, CObActiRecord, FieldSound)
	ADD_OBFIELDALL("SoundID", OB_FIELD_SOUNDID, 0, CObActiRecord, FieldSoundID)
END_OBFIELDMAP()
/*===========================================================================
 *		End of CObActiRecord Field Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Constructor
 *
 *=========================================================================*/
CObActiRecord::CObActiRecord () {
  m_pSound = NULL;
}
/*===========================================================================
 *		End of Class CObActiRecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObActiRecord::Destroy (void) {
  m_pSound = NULL;

  CObItem1Record::Destroy();
}
/*===========================================================================
 *		End of Class Method CObActiRecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Method - void InitializeNew (void);
 *
 *=========================================================================*/
void CObActiRecord::InitializeNew (void) {

	/* Call the base class method first */
  CObItem1Record::InitializeNew();

  /* TODO */

}
/*===========================================================================
 *		End of Class Method CObActiRecord::InitializeNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Event - void OnAddSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObActiRecord::OnAddSubrecord (CObSubrecord* pSubrecord) {

  if (pSubrecord->GetRecordType() == OB_NAME_SNAM) {
    m_pSound = ObCastClass(CObFormidSubrecord, pSubrecord);
  }
  else {
    CObItem1Record::OnAddSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObActiRecord::OnAddSubRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Event - void OnDeleteSubrecord (pSubrecord);
 *
 *=========================================================================*/
void CObActiRecord::OnDeleteSubrecord (CObSubrecord* pSubrecord) {

  if (m_pSound == pSubrecord) {
    m_pSound = NULL;
  }
  else {
    CObItem1Record::OnDeleteSubrecord(pSubrecord);
  }

}
/*===========================================================================
 *		End of Class Event CObActiRecord::OnDeleteSubrecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObActiRecord Method - void SetSound (FormID);
 *
 *=========================================================================*/
void CObActiRecord::SetSound (const obformid_t FormID) {

	/* Clear the script value */
  if (FormID == OB_FORMID_NULL) {
    DeleteSubrecords(OB_NAME_SNAM);
    return;
  }

  if (m_pSound == NULL) {
     AddNewSubrecord(OB_NAME_SNAM);
     if (m_pSound == NULL) return;
     m_pSound->InitializeNew();
   }

  m_pSound->SetValue(FormID);
}
/*===========================================================================
 *		End of Class Method CObActiRecord::SetSound()
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiRecord Get Field Methods
 *
 *=========================================================================*/
DEFINE_OBGETFIELD(CObActiRecord::GetFieldSoundID, GetSound() ? String.Format("0x%08X", GetSound()) : String.Empty())

BEGIN_OBGETFIELD(CObActiRecord::GetFieldSound)
	if (m_pParent != NULL) return m_pParent->GetEditorID(String, GetSound());
        String.Format("0x%08X", GetSound());
END_OBGETFIELD()
/*===========================================================================
 *		End of CObActiRecord Get Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiRecord Compare Field Methods
 *
 *=========================================================================*/
DEFINE_OBCOMPFIELDEDITORID(CObActiRecord, CompareFieldSound, GetSound)
DEFINE_OBCOMPFIELDDWORD(CObActiRecord, CompareFieldSoundID, GetSound)
/*===========================================================================
 *		End of CObActiRecord Compare Field Methods
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObActiRecord Set Field Methods
 *
 *=========================================================================*/
BEGIN_OBSETFIELD(CObActiRecord::SetFieldSoundID)
  obformid_t FormID;
  if (!ObFieldConvertDword(pString, FormID)) return (false);
  SetSound(FormID);
END_OBSETFIELD()


BEGIN_OBSETFIELD(CObActiRecord::SetFieldSound)
  CObIdRecord*   pIdRecord = NULL;

  if (m_pParent != NULL) {

    if (pString == NULL || *pString == NULL_CHAR) {
      SetScript(OB_FORMID_NULL);
      return (true);
    }

    pIdRecord = m_pParent->FindEditorID(pString);
    if (pIdRecord == NULL) return AddObGeneralError("The sound '%s' does not exist!", pString);
    if (pIdRecord->GetRecordType() != OB_NAME_SOUN) return AddObGeneralError("The record '%s' is not a sound (%4.4s)!", pString, pIdRecord->GetRecordType().Name);

    SetSound(pIdRecord->GetFormID());
  }
  else {
    return AddObGeneralError("Unable to find the formID for the sound '%s'!", pString);
  }

END_OBSETFIELD()
/*===========================================================================
 *		End of CObActiRecord Set Field Methods
 *=========================================================================*/

