/*===========================================================================
 *
 * File:	Obrecordvirtuallistctrl.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 5, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRECORDVIRTUALLISTCTRL_H
#define __OBRECORDVIRTUALLISTCTRL_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecordlistctrl.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecordVirtualListCtrl Definition
 *
 * Description
 *
 *=========================================================================*/
class CObRecordVirtualListCtrl : public CObRecordListCtrl {
  DECLARE_DYNCREATE(CObRecordVirtualListCtrl);

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CObRefRecordArray	m_Records;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

  	/* Sorts the current list by the given field */
  virtual void SortListPriv (const obrecfieldid_t FieldID);



  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRecordVirtualListCtrl();
  virtual ~CObRecordVirtualListCtrl();

	/* Add a new item */
  virtual int AddCustomRecord (obrlcustomdata_t& CustomData); 

	/* Set default list settings */
  virtual void DefaultSettings (void);

	/* Clear all items */
  virtual BOOL DeleteAllItems (void);

  	/* Find a record in the list */
  virtual int FindRecord (CObRecord* pRecord);

  	/* Finds the closest match to the given editorid string in the list */
  virtual int FindEditorID (const SSCHAR* pString);

	/* Get a record object */
  virtual CObRecord* GetRecord  (const int ListIndex);
  CObRefRecordArray* GetRecords (void) { return (&m_Records); }

  	/* Remove an item from the list */
  virtual bool RemoveItem (const int ListIndex);

  	/* Update a record in the list */
  virtual int UpdateRecord (CObRecord* pNewRecord, CObRecord* pOldRecord);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObRecordVirtualListCtrl)
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObRecordVirtualListCtrl)
  afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

 };
/*===========================================================================
 *		End of Class CObRecordVirtualListCtrl Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obrecordvirtuallistctrl.H
 *=========================================================================*/
