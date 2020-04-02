/*===========================================================================
 *
 * File:	Obrecordtreectrl.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 27, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRECORDTREECTRL_H
#define __OBRECORDTREECTRL_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obrecordfilter.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Options for the record tree */
  struct obrectreeoptions_t {
	bool	 EnableCounts;
	CSString FilterFile;
	CSString FullFilterFile;

	obrectreeoptions_t() {
		FilterFile     = "displayfilters.dat";
		FullFilterFile = FilterFile;
		EnableCounts   = true;
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecordTreeCtrl Definition
 *
 *=========================================================================*/
class CObRecordTreeCtrl : public CTreeCtrl {

  /*---------- Begin Protected Class Members ----------------------*/
protected:
  CObRecFilterArray		m_Filters;
  CObRecFilterArray*		m_pRefFilters;

  static obrectreeoptions_t	m_Options;


  /*---------- Begin Protected Class Methods ----------------------*/
protected:

	/* Create the tree structure from the current filter data */
  bool CreateItemsFromFilters (void);

	/* Helper update methods */
  void UpdateItemText (HTREEITEM hItem, CObRecordFilter* pFilter);


  /*---------- Begin Public Class Methods -------------------------*/
public:

	/* Construction/Destructor */
  CObRecordTreeCtrl();
  virtual ~CObRecordTreeCtrl();

	/* Get the currently selected filter object */
  CObRecordFilter* GetSelectedFilter (void);

	/* Access the current filter array */
  CObRecFilterArray* GetFilterArray (void) { return (m_pRefFilters == NULL ? &m_Filters : m_pRefFilters); }

	/* Access the static options member */
  static obrectreeoptions_t& GetOptions (void) { return (m_Options); }

	/* Load filters and create tree items from them */
  bool Initialize (const SSCHAR* pFilename);
  bool Initialize (CObRecFilterArray* pFilterArray);

	/* Load a record filter file */
  bool LoadFilters (const SSCHAR* pFilename) { return LoadObRecordFilters(pFilename, m_Filters); }

	/* Select a tree item with a matching filter ID */
  HTREEITEM SelectFromFilterID (const SSCHAR* pID);

	/* Sets an external filter array object */
  void SetRefFilterArray (CObRecFilterArray* pFilters = NULL) { m_pRefFilters = pFilters; }

	/* Update the currently displayed filter record counts */
  void  UpdateFilterCounts (CObEspFile& File);
  void  UpdateFilterCounts (CObGroup* pTopGroup);
  dword IncludeInCounts    (CObRecord* pRecord);
  dword RemoveFromCounts   (CObRecord* pRecord);

	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObRecordTreeCtrl)
  //}}AFX_VIRTUAL

protected:

	/* Generated message map functions */
  //{{AFX_MSG(CObRecordTreeCtrl)
  afx_msg void OnRButtonDown (UINT nFlags, CPoint Point);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

};
/*===========================================================================
 *		End of Class CObRecordTreeCtrl Definition
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obrecordtreectrl.H
 *=========================================================================*/
