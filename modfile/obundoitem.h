/*===========================================================================
 *
 * File:	Obundoitem.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 27, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBUNDOITEM_H
#define __OBUNDOITEM_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecordhandler.h"
  #include "records/obrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Undo types */
  #define OB_UNDOTYPE_NONE		0
  #define OB_UNDOTYPE_ADDRECORD		1
  #define OB_UNDOTYPE_UPDATERECORD	2
  #define OB_UNDOTYPE_CLEANRECORD	3

	/* Undo options */
  struct obundooptions_t {
	bool	EnableUndo;	/* Enable undo operations to be saved */
	dword	UndoLimit;	/* Number of undo operations to save */

	obundooptions_t() {
		EnableUndo = true;
		UndoLimit  = 50;
	}
  };

/*===========================================================================
 *		End of Definitions
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
 * Begin Class CObUndoItem Definition
 *
 * Holds a single undo item definition.
 *
 *=========================================================================*/
class CObUndoItem {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRecord*	m_pRecordCopy;		/* Copy of the record updated */
  int		m_ActionType;		/* Type of action that was performed */

  CSString	m_NewEditorID;		/* The new editorid if changed */
  bool		m_IsCopy;		/* Copied from a previous version */
  bool		m_IsRenamed;		/* Renamed from a previous version */
  obformid_t	m_NewFormID;		/* Used for copied records */


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObUndoItem();
  virtual ~CObUndoItem() { Destroy(); }
  virtual void Destroy (void);

	/* Create a copy of the given record */
  CObRecord* CopyRecord (CObRecord* pRecord);

  	/* Set undo information based on the given edit information */
  bool CreateUndoInfo (obeditrecinfo_t& EditInfo);

	/* Get class members */
  CObRecord*    GetRecord	(void) { return (m_pRecordCopy); }
  int           GetActionType	(void) { return (m_ActionType); }
  const SSCHAR* GetNewEditorID	(void) { return (m_NewEditorID); }
  bool		HasNewEditorID	(void) { return (!m_NewEditorID.IsEmpty()); }
  bool		IsCopy		(void) { return (m_IsCopy); }
  bool		IsRenamed	(void) { return (m_IsRenamed); }
  obformid_t    GetNewFormID    (void) { return (m_NewFormID); }

	/* Gets a string representation of the undo item */
  const char* MakeString (CSString& Buffer);

	/* Set class members */
  void SetRecord      (CObRecord*      pRecord) { m_pRecordCopy = pRecord; }
  void SetActionType  (const int          Type) { m_ActionType  = Type; }
  void SetNewEditorID (const SSCHAR*   pString) { m_NewEditorID = pString; }
  void SetIsCopy      (const bool         Flag) { m_IsCopy      = Flag; }
  void SetIsRenamed   (const bool         Flag) { m_IsRenamed   = Flag; }
  void SetNewFormID   (const obformid_t FormID) { m_NewFormID   = FormID; }

};

	/* Arrays of items */
  typedef CObPtrArray<CObUndoItem>    CObUndoItemArray;
  typedef CObRefPtrArray<CObUndoItem> CObRefUndoItemArray;

/*===========================================================================
 *		End of Class CObUndoItem Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obundoitem.H
 *=========================================================================*/
