/*===========================================================================
 *
 * File:	Obundoitem.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 27, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obundoitem.h"


/*===========================================================================
 *
 * Class CObUndoItem Constructor
 *
 *=========================================================================*/
CObUndoItem::CObUndoItem () {
  m_pRecordCopy = NULL;
  m_ActionType  = OB_UNDOTYPE_NONE;
  m_IsCopy      = false;
  m_IsRenamed   = false;
  m_NewFormID   = 0;
}
/*===========================================================================
 *		End of Class CObUndoItem Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoItem Method - void Destroy (void);
 *
 *=========================================================================*/
void CObUndoItem::Destroy (void) {

  if (m_pRecordCopy != NULL) {
    delete m_pRecordCopy;
    m_pRecordCopy = NULL;
  }

  m_ActionType  = OB_UNDOTYPE_NONE;
  m_IsCopy      = false;
  m_IsRenamed   = false;
  m_NewFormID   = 0;

  m_NewEditorID.Empty();
}
/*===========================================================================
 *		End of Class Method CObUndoItem::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoItem Method - CObRecord* CopyRecord (pRecord);
 *
 * Create a copy of the given record. Returns the new copy or NULL on any
 * error.
 *
 *=========================================================================*/
CObRecord* CObUndoItem::CopyRecord (CObRecord* pRecord) {

	/* Delete the current record if any */
  if (m_pRecordCopy != NULL) {
    delete m_pRecordCopy;
    m_pRecordCopy = NULL;
  }

	/* Ignore invalid niput */
  if (pRecord == NULL) return (NULL);

	/* Create the record copy */ 
  m_pRecordCopy = CreateObRecord(pRecord->GetRecordType());
  if (m_pRecordCopy == NULL) return (NULL);
  m_pRecordCopy->Copy(pRecord);

  return (m_pRecordCopy);
}
/*===========================================================================
 *		End of Class Method CObUndoItem::CopyRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObUndoItem Method - bool CreateUndoInfo (EditInfo);
 *
 *=========================================================================*/
bool CObUndoItem::CreateUndoInfo (obeditrecinfo_t& EditInfo) {

	/* Clear the current information */
  Destroy();

  EditInfo.pRecordCopy = CopyRecord(EditInfo.pOldRecord);

  m_NewEditorID = EditInfo.NewEditorID;
  m_IsCopy      = EditInfo.IsCopy;
  m_IsRenamed   = EditInfo.IsRenamed;
  m_ActionType = OB_UNDOTYPE_NONE;
  if (EditInfo.pNewRecord != NULL) m_NewFormID = EditInfo.pNewRecord->GetFormID();

  return (true);
}
/*===========================================================================
 *		End of Class Method CObUndoItem::CreateUndoInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class char* CObUndoItem Method - const MakeString (Buffer);
 *
 *=========================================================================*/
const char* CObUndoItem::MakeString (CSString& Buffer) {
  obformid_t OldFormID = 0;
  CSString   OldEditorID;

  if (m_pRecordCopy != NULL) {
    OldFormID = m_pRecordCopy->GetFormID();
    m_pRecordCopy->GetField(OldEditorID, OB_FIELD_EDITORID);
  }

  switch (m_ActionType) {
    case OB_UNDOTYPE_ADDRECORD:
	Buffer.Format("New %s (%X)", m_NewEditorID, OldFormID);
	break;
    case OB_UNDOTYPE_CLEANRECORD:
        Buffer.Format("Clean %s (%X)", OldEditorID, OldFormID);
	break;
    case OB_UNDOTYPE_UPDATERECORD:
        if (m_IsCopy)
	  Buffer.Format("Update %s (%X), copy of %s (%X)", m_NewEditorID, m_NewFormID, OldEditorID, OldFormID);
	else if (m_IsRenamed)
	  Buffer.Format("Update %s (%X), renamed %s", m_NewEditorID, OldFormID, OldEditorID);
	else
          Buffer.Format("Update %s (%X)", OldEditorID, OldFormID);

	break;
    default:
        Buffer.Format("Unknown");
	break;
  }

  return (Buffer);
}
/*===========================================================================
 *		End of Class Method char* CObUndoItem::MakeString()
 *=========================================================================*/

