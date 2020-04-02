/*===========================================================================
 *
 * File:	Obrecordvirtuallistctrl.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 5, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "obrecordvirtuallistctrl.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  IMPLEMENT_DYNCREATE(CObRecordVirtualListCtrl, CObRecordListCtrl);
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecordVirtualListCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObRecordVirtualListCtrl, CObRecordListCtrl)
	//{{AFX_MSG_MAP(CObRecordVirtualListCtrl)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetDispInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObRecordVirtualListCtrl Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int CALLBACK s_DefaultVirtualRecListSort (lParam1, lParam2, lParamSort);
 *
 *=========================================================================*/
int CALLBACK s_DefaultVirtualRecListSort (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  
  if (pSortData->Reverse) return -pRecord1->CompareFields(pSortData->FieldID, pRecord2);
  return pRecord1->CompareFields(pSortData->FieldID, pRecord2);
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultVirtualRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Constructor
 *
 *=========================================================================*/
CObRecordVirtualListCtrl::CObRecordVirtualListCtrl () {

 }
/*===========================================================================
 *		End of Class CObRecordVirtualListCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Destructor
 *
 *=========================================================================*/
CObRecordVirtualListCtrl::~CObRecordVirtualListCtrl () {
}
/*===========================================================================
 *		End of Class CObRecordVirtualListCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - int AddCustomRecord (CustomData);
 *
 *=========================================================================*/
int CObRecordVirtualListCtrl::AddCustomRecord (obrlcustomdata_t& CustomData) {
  int ListIndex;

  if (CustomData.pRecord == NULL) return (-1);
  ListIndex = m_Records.GetSize();

  m_Records.Add(CustomData.pRecord);

  SetItemCount(ListIndex + 1);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::AddCustomRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - void DefaultSettings (void);
 *
 *=========================================================================*/
void CObRecordVirtualListCtrl::DefaultSettings (void) {
  CObRecordListCtrl::DefaultSettings();
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::DefaultSettings()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - BOOL DeleteAllItems (void);
 *
 *=========================================================================*/
BOOL CObRecordVirtualListCtrl::DeleteAllItems (void) {
  m_Records.Destroy();
    
  return CObRecordListCtrl::DeleteAllItems();
 }
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::DeleteAllItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - int FindEditorID (pString);
 *
 *=========================================================================*/
int CObRecordVirtualListCtrl::FindEditorID (const SSCHAR* pString) {
  CSString Buffer;
  dword    Index;
  bool     Result;
  int      LastMatch = -1;
  int      LastMatchCount = 0;
  int	   Matching;

  for (Index = 0; Index < m_Records.GetSize(); ++Index) {
    Result = m_Records[Index]->GetField(Buffer, OB_FIELD_EDITORID);
    if (!Result) continue;

    Matching = Buffer.CountMatchLengthNoCase(pString);

    if (Matching > LastMatchCount) {
      LastMatchCount = Matching;
      LastMatch      = Index;
    }
  } 

  return (LastMatch);
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::FindEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - bool FindRecord (pRecord);
 *
 * Finds the given record in the current list. Returns the list index or
 * -1 if not found.
 *
 *=========================================================================*/
int CObRecordVirtualListCtrl::FindRecord (CObRecord* pRecord) {
  if (pRecord == NULL) return (-1);
  return m_Records.Find(pRecord);
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::FindRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - CObRecord* GetRecord (ListIndex);
 *
 *=========================================================================*/
CObRecord* CObRecordVirtualListCtrl::GetRecord (const int ListIndex) {
  CObBaseRecord* pBaseRecord = m_Records.GetAt(ListIndex);
  if (pBaseRecord == NULL) return (NULL);
  return ObCastClass(CObRecord, pBaseRecord); 
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::GetRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Event - void OnGetDispInfo (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordVirtualListCtrl::OnGetDispInfo (NMHDR* pNMHDR, LRESULT* pResult) {
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  LV_DISPINFO*   pDispInfo = (LV_DISPINFO *)pNMHDR;
  LV_ITEM*       pItem     = &(pDispInfo)->item;
  int	         ItemIndex = pItem->iItem;

  if (m_pCurrentList == NULL) return;

  pBaseRecord = m_Records.GetAt(ItemIndex);
  if (pBaseRecord == NULL) return;
  pRecord = ObCastClass(CObRecord, pBaseRecord);
  if (pRecord == NULL) return;

  if (pItem->mask & LVIF_TEXT) {
    CSString    Buffer;
    obfieldid_t FieldID;
    bool        Result;

    if (pItem->iSubItem < 0 || pItem->iSubItem >= (int) m_pCurrentList->NumColumns) return;

    FieldID = m_pCurrentList->Columns[pItem->iSubItem].FieldID;
    Result = pRecord->GetField(Buffer, FieldID);
    if (Result) lstrcpyn(pItem->pszText, Buffer, pItem->cchTextMax);
  }

  *pResult = 0;
 }
/*===========================================================================
 *		End of Class Event CObRecordVirtualListCtrl::OnGetDispInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - void SortListPriv (FieldID);
 *
 *=========================================================================*/
void CObRecordVirtualListCtrl::SortListPriv (const obrecfieldid_t FieldID) {
  obreclistsort_t    SortData;
  obreclistcolumn_t* pColumn;

  if (m_pCurrentList == NULL) return;
  pColumn = FindListColumn(m_pCurrentList, FieldID);

  SortData.FieldID  = m_pCurrentList->SortField;
  SortData.SubItem  = m_pCurrentList->SortSubItem;
  SortData.Reverse  = m_pCurrentList->SortReverse;
  SortData.ListType = m_pCurrentList->Type;

  if (pColumn == NULL || pColumn->CompareFunc == NULL) {

    if (m_pCurrentList->Type == OB_RECORDLIST_CUSTOM) 
      return;
    else
      m_Records.Sort(s_DefaultVirtualRecListSort, (DWORD) (void *) &SortData);
   }
  else
    m_Records.Sort(pColumn->CompareFunc, (DWORD) (void *) &SortData);


  this->RedrawWindow();
  //m_Records.Sort(s_DefaultVirtualRecListSort, );
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::SortListPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - int UpdateRecord (pNewRecord, pOldRecord);
 *
 * Updates an existing record or adds a new one. Returns the updated list
 * index or -1 on any error.
 *
 *=========================================================================*/
int CObRecordVirtualListCtrl::UpdateRecord (CObRecord* pNewRecord, CObRecord* pOldRecord) {
  int ListIndex;

  ListIndex = FindRecord(pOldRecord);

  if (ListIndex < 0) {
    if (m_pCurrentFilter != NULL && !m_pCurrentFilter->CheckRecord(pNewRecord)) return (-1);
    return AddRecord(pNewRecord);
  }

  if (pNewRecord == NULL) {
    m_Records.Delete(ListIndex);
    SetItemCount(m_Records.GetSize());

    RedrawItems(ListIndex, ListIndex + GetCountPerPage());
    UpdateWindow();

    return (-1);
  }
  
  m_Records.SetAt(ListIndex, pNewRecord);

  RedrawItems(ListIndex, ListIndex);
  UpdateWindow();

  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::UpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordVirtualListCtrl Method - bool RemoveItem (ListIndex);
 *
 *=========================================================================*/
bool CObRecordVirtualListCtrl::RemoveItem (const int ListIndex) {
  bool Result;

  Result = m_Records.Delete(ListIndex);
  if (!Result) return (false);

  SetItemCount(m_Records.GetSize());

  RedrawItems(ListIndex, ListIndex + GetCountPerPage());
  UpdateWindow();

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordVirtualListCtrl::RemoveItem()
 *=========================================================================*/

