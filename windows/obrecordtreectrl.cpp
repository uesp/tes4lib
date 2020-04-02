/*===========================================================================
 *
 * File:	Obrecordtreectrl.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 27, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "ObRecordTreeCtrl.h"


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

  obrectreeoptions_t CObRecordTreeCtrl::m_Options;

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecordTreeCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObRecordTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CObRecordTreeCtrl)
	ON_WM_RBUTTONDOWN( )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObRecordTreeCtrl Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Constructor
 *
 *=========================================================================*/
CObRecordTreeCtrl::CObRecordTreeCtrl() {
  m_pRefFilters = NULL;
 }
/*===========================================================================
 *		End of Class CObRecordTreeCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Destructor
 *
 *=========================================================================*/
CObRecordTreeCtrl::~CObRecordTreeCtrl() {
 }
/*===========================================================================
 *		End of Class CObRecordTreeCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - bool CreateItemsFromFilters (void);
 *
 * Creates the tree items from the current filter data. Returns false
 * on any error.
 *
 *=========================================================================*/
bool CObRecordTreeCtrl::CreateItemsFromFilters (void) {
  CObRecFilterArray* pFilterArray = GetFilterArray();
  CObRecordFilter*   pFilter;
  CString	     Buffer;
  HTREEITEM	     hParent;
  HTREEITEM	     hItem;
  dword		     Index;

	/* Clear the current tree */
  DeleteAllItems();

  for (Index = 0; Index < pFilterArray->GetSize(); ++Index) {
    pFilter = pFilterArray->GetAt(Index);

    if (pFilter->GetParent() == NULL) {
      hParent = TVI_ROOT;
     }
    else {
      hParent = (HTREEITEM) pFilter->GetParent()->GetUserData();
     }
    
    if (pFilter->IsFlagEmpty() || !m_Options.EnableCounts)
      Buffer.Format("%s", pFilter->GetDisplayName());
    else
      Buffer.Format("%s (0)", pFilter->GetDisplayName());

    hItem = InsertItem(Buffer, hParent, TVI_LAST);

    if (hItem != NULL) {
      SetItemData(hItem, (DWORD) (void *)pFilter);
      pFilter->SetUserData((dword) hItem);

      if (hParent == TVI_ROOT) SetItemState(hItem, TVIS_BOLD, TVIS_BOLD);
     }
   }

	/* Assume no selection initially */
  SelectItem(NULL);
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::CreateItemsFromFilters()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - CObRecordFilter* GetSelectedFilter (void);
 *
 *=========================================================================*/
CObRecordFilter* CObRecordTreeCtrl::GetSelectedFilter (void) {
  HTREEITEM hSelItem;

	/* Get the currently selected tree item */
  hSelItem = GetSelectedItem();
  if (hSelItem == NULL) return (NULL);

  return (CObRecordFilter *) GetItemData(hSelItem);
 }
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::GetSelectedFilter()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - bool Initialize (pFilename);
 *
 *=========================================================================*/
bool CObRecordTreeCtrl::Initialize (const SSCHAR* pFilename) {
  bool Result;

  Result  = LoadFilters(pFilename);
  Result &= CreateItemsFromFilters();

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::Initialize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - bool Initialize (pFilterArray);
 *
 *=========================================================================*/
bool CObRecordTreeCtrl::Initialize (CObRecFilterArray* pFilterArray) {
  bool Result;

  SetRefFilterArray(pFilterArray);
  Result = CreateItemsFromFilters();

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::Initialize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - dword IncludeInCounts (pRecord);
 *
 * Includes the given record in any matching filters. Returns the number
 * of count changes.
 *
 *=========================================================================*/
dword CObRecordTreeCtrl::IncludeInCounts (CObRecord* pRecord) {
  CObRecFilterArray* pFilterArray = GetFilterArray();
  CObRecordFilter*   pFilter;
  CString	     Buffer;
  HTREEITEM	     hItem;
  dword		     Index;
  dword		     Count = 0;
  bool		     Result;

	/* Ignore if not updating counts */
  if (!m_Options.EnableCounts) return (0);

  for (Index = 0; Index < pFilterArray->GetSize(); ++Index) {
    pFilter = pFilterArray->GetAt(Index);
    hItem   = (HTREEITEM) pFilter->GetUserData();

    if (hItem == NULL)          continue;
    if (pFilter->IsFlagEmpty()) continue;

    Result = pFilter->CheckRecord(pRecord);

    if (Result) {
      pFilter->ModRecordCount(1);
      ++Count;
      UpdateItemText(hItem, pFilter);
    }
    
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::IncludeInCounts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - dword RemoveFromCounts (CObRecord* pRecord);
 *
 * Removes the given record in any matching filters. Returns the number
 * of count changes.
 *
 *=========================================================================*/
dword CObRecordTreeCtrl::RemoveFromCounts (CObRecord* pRecord) {
  CObRecFilterArray* pFilterArray = GetFilterArray();
  CObRecordFilter*   pFilter;
  CString	     Buffer;
  HTREEITEM	     hItem;
  dword		     Index;
  dword		     Count = 0;
  bool		     Result;

  	/* Ignore if not updating counts */
  if (!m_Options.EnableCounts) return (0);

  for (Index = 0; Index < pFilterArray->GetSize(); ++Index) {
    pFilter = pFilterArray->GetAt(Index);
    hItem   = (HTREEITEM) pFilter->GetUserData();

    if (hItem == NULL)          continue;
    if (pFilter->IsFlagEmpty()) continue;

    Result = pFilter->CheckRecord(pRecord);

    if (Result) {
      pFilter->ModRecordCount(-1);
      ++Count;
      UpdateItemText(hItem, pFilter);
    }
    
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::RemoveFromCounts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Event - void OnRButtonDown (nFlags, Point);
 *
 *=========================================================================*/
void CObRecordTreeCtrl::OnRButtonDown (UINT nFlags, CPoint Point) {
  HTREEITEM hItem;
  
	/* Select item on right-click */
  hItem = HitTest(Point, NULL);
  if (hItem != NULL) SelectItem(hItem);

  CTreeCtrl::OnRButtonDown(nFlags, Point);
}
/*===========================================================================
 *		End of Class Event CObRecordTreeCtrl::OnRButtonDown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - HTREEITEM SelectFromFilterID (pID);
 *
 * Finds, selects and returns the tree item with the given filter
 * ID. Returns NULL if the item is not found.
 *
 *=========================================================================*/
HTREEITEM CObRecordTreeCtrl::SelectFromFilterID (const SSCHAR* pID) {
  CObRecFilterArray* pFilterArray = GetFilterArray();
  CObRecordFilter*   pFilter;
  HTREEITEM	     hItem;
  dword		     Index;

  for (Index = 0; Index < pFilterArray->GetSize(); ++Index) {
    pFilter = pFilterArray->GetAt(Index);

    if (stricmp(pFilter->GetID(), pID) == 0) {
      hItem = (HTREEITEM) pFilter->GetUserData();
      Select(hItem, TVGN_CARET);
      return (hItem);
    }
  }

	/* Assume no selection initially */
  return (NULL);
}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::SelectFromFilterID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - void UpdateFilterCounts (File);
 *
 *=========================================================================*/
void CObRecordTreeCtrl::UpdateFilterCounts (CObEspFile& File) {
  UpdateFilterCounts(&File.GetRecords());
}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::UpdateFilterCounts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - void UpdateFilterCounts (pTopGroup);
 *
 *=========================================================================*/
void CObRecordTreeCtrl::UpdateFilterCounts (CObGroup* pTopGroup) {
  CObRecFilterArray* pFilterArray = GetFilterArray();
  CObRecordFilter*   pFilter;
  CString	     Buffer;
  HTREEITEM	     hItem;
  dword		     Index;
  dword		     Count;

  	/* Ignore if not updating counts */
  if (!m_Options.EnableCounts) return;

  for (Index = 0; Index < pFilterArray->GetSize(); ++Index) {
    pFilter = pFilterArray->GetAt(Index);
    hItem   = (HTREEITEM) pFilter->GetUserData();
    if (hItem == NULL) continue;

    if (pFilter->IsFlagEmpty()) continue;

    Count = pFilter->CountMatchingRecords(pTopGroup);
    pFilter->SetRecordCount(Count);

    UpdateItemText(hItem, pFilter);
  }

}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::UpdateFilterCounts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordTreeCtrl Method - void UpdateItemText (hItem, pFilter);
 *
 * Helper function to update tree item text.
 *
 *=========================================================================*/
void CObRecordTreeCtrl::UpdateItemText (HTREEITEM hItem, CObRecordFilter* pFilter) {
  static CString s_Buffer;
  
  if (!m_Options.EnableCounts || pFilter->IsFlagEmpty())
    s_Buffer.Format("%s", pFilter->GetDisplayName());
  else
    s_Buffer.Format("%s (%d)", pFilter->GetDisplayName(), pFilter->GetRecordCount());
    
  SetItemText(hItem, s_Buffer);
}
/*===========================================================================
 *		End of Class Method CObRecordTreeCtrl::UpdateItemText()
 *=========================================================================*/
