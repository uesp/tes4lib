/*===========================================================================
 *
 * File:	Obrecordlistctrl.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 24, 2006
 *
 * Defines the CObRecordListCtrl class used for displaying a list of 
 * record data in a CListCtrl format.
 *
 *=========================================================================*/
#ifndef __OBRECORDLISTCTRL_H
#define __OBRECORDLISTCTRL_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
  #include "obrecordfilter.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Arbitrary number of columns allowed in a list */
  #define OB_RECLIST_MAXCOLS 100

	/* Custom messages */
  #define ID_OBRECORDLIST_ACTIVATE		(WM_APP + 101)
  #define ID_OBRECORDLIST_ALTACTIVATE		(WM_APP + 102)
  #define ID_OBRECORDLIST_DROP			(WM_APP + 103)
  #define ID_OBRECORDLIST_CHECKDROP		(WM_APP + 104)
  #define ID_OBRECORDLIST_CHAR			(WM_APP + 105)
  #define ID_OBRECORDLIST_KEYDOWN		(WM_APP + 106)
    
	/* List types */
  #define OB_RECORDLIST_RECORD	1
  #define OB_RECORDLIST_CUSTOM	2

  	/* Drag types */
  #define OB_RLDRAG_RECORD	0x0001
  #define OB_RLDRAG_CUSTOM	0x0002
  #define OB_RLDRAG_ALL		0xffff

	/* Types of list activation */
  #define OB_RLACTIVATE_NONE      0
  #define OB_RLACTIVATE_RECORD    1
  #define OB_RLACTIVATE_SUBRECORD 2
  #define OB_RLACTIVATE_DEFAULT OB_RLACTIVATE_RECORD

	/* Number of subrecords in the custom data structure */
  #define OB_RLMAX_SUBRECORDS 4

	/* Macro to get data from list compare function parameters */
  #define OBRL_SORTFUNC_GETPARAMS(Param1, Param2, Param3) obreclistsort_t* pSortData = (obreclistsort_t *) Param3; \
		obrlcustomdata_t* pCustomData1 = (pSortData->ListType == OB_RECORDLIST_CUSTOM) ? (obrlcustomdata_t *) Param1 : NULL; \
		obrlcustomdata_t* pCustomData2 = (pSortData->ListType == OB_RECORDLIST_CUSTOM) ? (obrlcustomdata_t *) Param2 : NULL; \
		CObRecord* pRecord1  = (pSortData->ListType == OB_RECORDLIST_RECORD) ? (CObRecord *) Param1 : pCustomData1->pRecord; \
		CObRecord* pRecord2  = (pSortData->ListType == OB_RECORDLIST_RECORD) ? (CObRecord *) Param2 : pCustomData2->pRecord; 

	/* Initialize columns flags */
  #define OBRL_INITCOL_NOEXTRAFIELDS	1
  #define OBRL_INITCOL_FORCENEW		2
  
	/* Types of color to apply to the list */
  #define OBRL_COLORMASK_ACTIVE		1
  #define OBRL_COLORMASK_IGNORE		2
  #define OBRL_COLORMASK_DELETE		4
  #define OBRL_COLORMASK_DANGEROUS	8
  #define OBRL_COLORMASK_QUEST		16

	/* Default list colors */
  #define OBRL_DEFAULT_COLOR_ACTIVE	RGB(172,255,172)
  #define OBRL_DEFAULT_COLOR_IGNORED	RGB(172,255,255)
  #define OBRL_DEFAULT_COLOR_DELETED	RGB(255,172,172)
  #define OBRL_DEFAULT_COLOR_DANGEROUS	RGB(255,255,172)
  #define OBRL_DEFAULT_COLOR_QUEST	RGB(172,172,255)

	/* Drop check results */
  #define OBRL_DROPCHECK_OK    1234
  #define OBRL_DROPCHECK_ERROR 4321
  
	/* Registry keys */
  #define OBRL_REGKEY_ROOT "Lists"
		
/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Holds information on a single column in the displayed list */
  struct obreclistcolumn_t {
	const obrecfield_t*	pField;		/* Which field this column represents */
	obfieldid_t		FieldID;
	TCHAR			Title[64];
	int			Width;		/* Output width */
	int			Format;		/* Output format flags */
	int			SubItem;	/* Subitem index */
	int			ColumnIndex;
	bool			Display;	/* Display the column or not */
	PFNLVCOMPARE		CompareFunc;

	obreclistcolumn_t() {
		Title[0]	= NULL_CHAR;
		pField		= NULL;
		FieldID		= 0;
		Width		= 10;
		Format		= 0;
		SubItem		= -1;
		ColumnIndex	= -1;
		Display		= false;
		CompareFunc	= NULL;
	}

	void SetTitle (const TCHAR* pString) { strnncpy(Title, pString, 62); }
   };

	/* Holds information on a single list configuration */
  struct obreclistinfo_t {
	int			Type;
	const obrectype_t*	pRecordType;
	int			SortSubItem;
	obrecfieldid_t		SortField;
	bool			SortReverse;
	PFNLVCOMPARE		CompareFunc;

	obreclistcolumn_t	Columns[OB_RECLIST_MAXCOLS];
	dword			NumColumns;
   };

	/* Used to initialize column data for a list */
  struct obreclistcolinit_t { 
	obrecfieldid_t	FieldID;
	int		Width;
	int		Format;
	PFNLVCOMPARE	CompareFunc;
   };

	/* Used to initialize a list configuration */
  struct obreclistinfoinit_t {
	const obrectype_t*	pRecordType;
	obreclistcolinit_t*	pInit;
	const obrecfieldmap_t*  pFieldMap;
	obrecfieldid_t		SortField;
   };

	/* Holds item information in a custom list */
  struct obrlcustomdata_t {
	CObRecord*	pRecord;
	CObSubrecord*	pSubrecords[OB_RLMAX_SUBRECORDS];
	int		UserData;
   };

	/* Used when sorting the list */
  struct obreclistsort_t {
	int		SubItem;
	int		ListType;
	obrecfieldid_t	FieldID;
	bool		Reverse;
   };

	/* An array of list information pointers */
  typedef CObPtrArray<obreclistinfo_t>     CObRecListInfoArray;
  typedef CObPtrArray<obrlcustomdata_t>    CObRLCustomDataArray;
  typedef CObRefPtrArray<obrlcustomdata_t> CObRLRefCustomDataArray;

	/* Color options for a specific type of record in the list */
  struct obreclistcolor_t {
	bool		Enable;
	COLORREF	Color;
	int		Order;

	obreclistcolor_t() {
		Enable = true;
		Color  = RGB(255,255,255);
		Order  = 1;
	}
  };

	/* List control options */
  struct obreclistoptions_t {
	bool			EnableColors;
	bool			SaveState;

	obreclistcolor_t	ActiveColor;
	obreclistcolor_t	DeletedColor;
	obreclistcolor_t	IgnoredColor;
	obreclistcolor_t	DangerousColor;
	obreclistcolor_t	QuestColor;

	obreclistoptions_t() {
		EnableColors = true;
		SaveState    = true;

		ActiveColor.Color    = OBRL_DEFAULT_COLOR_ACTIVE;
		DeletedColor.Color   = OBRL_DEFAULT_COLOR_DELETED;
		IgnoredColor.Color   = OBRL_DEFAULT_COLOR_IGNORED;
		DangerousColor.Color = OBRL_DEFAULT_COLOR_DANGEROUS;
		QuestColor.Color     = OBRL_DEFAULT_COLOR_QUEST;

		DeletedColor.Order   = 1;
		ActiveColor.Order    = 2;
		IgnoredColor.Order   = 3;
		QuestColor.Order     = 4;
		DangerousColor.Order = 5;

		IgnoredColor.Enable   = false;
		QuestColor.Enable     = false;
		DangerousColor.Enable = false;

	}
  };

	/* Used to test drop targets */
  struct obrldroprecords_t {
	NMHDR			 Notify;
	CObRefRecordArray*	 pRecords;
	CObRLRefCustomDataArray* pCustomDatas;
  };

	/* Used for key notify events */
  struct obrlkeydown_t {
	NMKEY		KeyDown;
	bool		Ctrl;
	bool		Alt;
	bool		Shift;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin class CObRecordListCtrl
 *
 *=========================================================================*/
class CObRecordListCtrl : public CListCtrl {
  DECLARE_DYNCREATE(CObRecordListCtrl);

  /*---------- Begin Protected Class Members -------------------------*/
protected:
  CObRecListInfoArray	m_ListInfos;
  obreclistinfo_t*	m_pCurrentList;
  CObRecordFilter*	m_pCurrentFilter;

  bool			m_ActNormalList;
  bool			m_EnableColors;

  CObRefRecordArray	  m_DragRecords;
  CObRLRefCustomDataArray m_DragCustomData;

  bool			m_EnableDrag;
  int			m_DragType;
  bool			m_AcceptDrop;
  bool			m_IsDragging;
  int			m_DragIndex;
  HCURSOR		m_hBadDropCursor;
  HCURSOR		m_hGoodDropCursor;
  CImageList*		m_pDragImage;
  int			m_DropIndex;
  bool			m_LastDropValid;
  CWnd*			m_pLastDropWnd;

  CObRLCustomDataArray	m_CustomData;	

  bool			m_AutoResize;
  CRect			m_AutoResizeOffset;

  int			m_ActivateType;

  CSString		m_ListName;

  static obreclistoptions_t m_Options;


  /*---------- Begin Protected Class Methods -------------------------*/
protected:

	/* Create a new list info structure */
  obreclistinfo_t* CreateListInfoObject (void);

	/* Initialize list information with default values if available */
  obreclistinfo_t* CreateDefaultListInfo (const obrectype_t Type);

	/* Helper drag/drop methods */
  void DropRecords (CWnd* pDropWnd);
 
	/* Find list information related to a record type */
  obreclistinfo_t* FindListInfo (const obrectype_t Type);

  	/* Initialize column data with the given information */
  obreclistinfo_t* InitializeColumns (const obrectype_t& Type, obreclistcolinit_t* ListInit, const obrecfieldmap_t* pFieldMap, const dword Flags = 0, const obrecfieldid_t SortField = 0);

	/* */ 

	/* Update the texts in a column */
  void SetColumnTexts (const int ListIndex, CObRecord* pRecord, CObSubrecord* pSubrecords[]);

	/* Helper sort methods */
  virtual void SortListPriv (const obrecfieldid_t FieldID);

	/* Output list information to the registry */
  void WriteListInfoRegistry (void);
  void WriteListInfoRegistry (obreclistinfo_t* pListInfo);
  void WriteListInfoRegistry (const char* pSection, obreclistcolumn_t* pColumn);

  void ReadListInfoRegistry (void);
  void ReadListInfoRegistry (obreclistinfo_t* pListInfo);
  void ReadListInfoRegistry (const char* pSection, obreclistcolumn_t* pColumn);

  const char* CreateRegSectionName (obreclistinfo_t* pListInfo);


  /*---------- Begin Public Class Methods ----------------------------*/
public:

	/* Constructor/Destructor */
  CObRecordListCtrl();
  virtual ~CObRecordListCtrl();

	/* Called when the parent window is resized */
  void AutoResize (void);

	/* Adds a record to the list */
  virtual int  AddRecord       (CObRecord*  pRecord);
  virtual int  AddCustomRecord (CObRecord*  pRecord, CObSubrecord* pSubrecord, const int UserData = 0);
  virtual int  AddCustomRecord (obrlcustomdata_t& CustomData);
  virtual void AddAllRecords   (CObEspFile& File);
  virtual void AddAllRecords   (CObGroup* pTopGroup);

	/* Set default list settings */
  virtual void DefaultSettings (void);

	/* Removes all currently defined columns */
  virtual void DeleteAllColumns (void);
  virtual BOOL DeleteAllItems   (void);

	/* Finds the closest match to the given editorid string in the list */
  virtual int FindEditorID (const SSCHAR* pString);

	/* Find a record in the list */
  virtual int FindRecord (CObRecord* pRecord);

	/* Access data from a list item */
  virtual CObRecord*         GetRecord             (const int ListIndex);
  virtual obrlcustomdata_t*  GetCustomData         (const int ListIndex);
  virtual const obrectype_t* GetCurrentRecordType  (void) { return (m_pCurrentList ? m_pCurrentList->pRecordType : NULL); }
  virtual CObRecord*         GetSelectedRecord     (void);
  virtual obrlcustomdata_t*  GetSelectedCustomData (void);
  virtual int                GetSelectedItem       (void);

	/* Access the static options member */
  static obreclistoptions_t& GetOptions (void) { return (m_Options); }

	/* Remove an item from the list */
  virtual bool RemoveItem (const int ListIndex);

	/* Deletes all items and columns from the list */
  void ResetContents (void);

	/* Select a record in the list */
  bool SelectRecord (CObRecord* pRecord);
  void SelectRecord (const int ListIndex);
  
	/* Setup columns for the given type */
  bool SetupList (const obrectype_t Type);
  bool SetupList (CObRecordFilter*  pFilter);
  bool SetupList (obreclistinfo_t*  pListInfo);
  bool SetupList (const obrectype_t& Type, obreclistcolinit_t* pListInit, const obrecfieldmap_t* pFieldMap);

	/* Setup a custom list definition */
  bool SetupCustomList (obreclistcolinit_t* pColumns, const obrecfieldmap_t* pFieldMap, const obrecfield_t* pCustomFields);
  
	/* Set custom list data */
  virtual void SetItemData (const int ListIndex, CObRecord* pRecord);
  virtual void SetItemData (const int ListIndex, CObRecord* pRecord, CObSubrecord* pSubrecord, const int UserData);
  virtual void SetItemData (const int ListIndex, const obrlcustomdata_t CustomData);

	/* Set class members */
  void SetAutoResize       (const bool Flag) { m_AutoResize = Flag; }
  void SetAutoResizeOffset (void);
  void SetDragEnable       (const bool Flag) { m_EnableDrag = Flag; }
  void SetColorEnable      (const bool Flag) { m_EnableColors = Flag; }
  void SetDragType         (const int  Type) { m_DragType     = Type; }
  void SetListName         (const char* pName) { m_ListName   = pName; }

	/* Set the activation type */
  void SetActivateType (const int Type) { m_ActivateType = Type; }

	/* Set a custom field value for the current list */
  bool SetCustomField (const int ListIndex, const obrecfieldid_t FieldID, const SSCHAR* pString);

	/* Sorts the current list by the given field */
  virtual void SortList (const obrecfieldid_t FieldID, const bool Reverse = false);

	/* Saves any changes in the current list */
  void UpdateCurrentList (void);

	/* Update a record in the list */
  virtual int  UpdateRecord (CObRecord* pNewRecord, CObRecord* pOldRecord);
  virtual void UpdateRecord (const int ListIndex);


	/* ClassWizard generated virtual function overrides */
  //{{AFX_VIRTUAL(CObRecordListCtrl)
protected:
  //}}AFX_VIRTUAL

	/* Generated message map functions */
protected:
  //{{AFX_MSG(CObRecordListCtrl)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnItemclick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnMouseMove (UINT nFlags, CPoint Point);
  afx_msg void OnLButtonUp (UINT nFlags, CPoint Point);
  afx_msg void OnBeginDrag (NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnCaptureChanged (CWnd* pWnd);
  afx_msg UINT OnGetDlgCode();
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnClose();
  afx_msg void OnDestroy();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP();

};
/*===========================================================================
 *		End of class CObRecordListCtrl
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  obreclistcolumn_t* FindListColumnBySubItem (obreclistinfo_t* pListInfo, const int SubItem);
  obreclistcolumn_t* FindListColumn          (obreclistinfo_t* pListInfo, const obrecfieldid_t FieldID);

  const obrecfield_t* FindObField (const obrecfield_t* pFields, const obrecfieldid_t FieldID);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


//{{AFX_INSERT_LOCATION}}
//}}AFX_INSERT_LOCATION


#endif
/*===========================================================================
 *		End of File Obrecordlistctrl.H
 *=========================================================================*/
