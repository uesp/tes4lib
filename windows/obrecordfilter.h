/*===========================================================================
 *
 * File:	Obrecordfilter.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 26, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBRECORDFILTER_H
#define __OBRECORDFILTER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "modfile/obespfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Record filter masks */
  #define OB_RECFILTER_MASK_RECORDTYPE	1
  #define OB_RECFILTER_MASK_BIPEDPARTS	2
  #define OB_RECFILTER_MASK_WEAPONTYPE	4
  #define OB_RECFILTER_MASK_ARMORTYPE	8
  #define OB_RECFILTER_MASK_MATERIAL	16
  #define OB_RECFILTER_MASK_ITEMNAME	32
  #define OB_RECFILTER_MASK_ENCHANTTYPE	64
  #define OB_RECFILTER_MASK_SCRIPTTYPE 128
  #define OB_RECFILTER_MASK_SPELLTYPE  256
  #define OB_RECFILTER_MASK_SPELLLEVEL 512
  #define OB_RECFILTER_MASK_FIELDS     1024

	/* Record filter flags */
  #define OB_RECFILTER_FLAG_EMPTY	1
  
  	/* Biped comparison types */
  #define OB_RECFILTER_BIPED_EQUAL	0	/* Flags must be identical */
  #define OB_RECFILTER_BIPED_AND	1	/* All filter flags must match */
  #define OB_RECFILTER_BIPED_OR		2	/* Any filter flags must match */

	/* Field filter flags */
  #define OB_RECFILTER_FIELDFLAG_EXACT		1	/* Exact match required */
  #define OB_RECFILTER_FIELDFLAG_CONTAINS	2	/* Look for a substring match */
  #define OB_RECFILTER_FIELDFLAG_STARTS		4	/* Look for a starting substring */
  #define OB_RECFILTER_FIELDFLAG_EXCLUDE	8	/* Exclude any matching records */
  #define OB_RECFILTER_FIELDFLAG_CASESENSITIVE	16


/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Used for field filters */
  struct obfilterfield_t {
	int		FieldID;	/* Which field to filter */
	CSString	Value;		/* Value to filter */
	dword		Flags;		/* Options */
  };

  typedef CObPtrArray<obfilterfield_t> CObFieldFilterArray;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRecordFilter Definition
 *
 * Description
 *
 *=========================================================================*/
class CObRecordFilter {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString		m_ID;
  CSString		m_DisplayName;
  dword			m_Flags;
  CSString		m_ParentName;
  CObRecordFilter*	m_pParent;

  dword			m_RecordCount;

  dword			m_FilterMask;
  obrectype_t		m_RecordType;
  CSString		m_Material;
  CSString		m_NameFilter;
  dword			m_BipedParts;
  dword			m_BipedCompare;
  int			m_WeaponType;
  int			m_ScriptType;
  int			m_EnchantType;
  int			m_SpellType;
  int			m_SpellLevel;
  dword			m_ArmorType;

  dword			m_UserData;

  CObFieldFilterArray	m_FieldFilters;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper check methods */
  bool CheckFieldRecord (CObRecord* pRecord);
  bool CheckFieldRecord (obfilterfield_t& Filter, CObRecord* pRecord);
	
	/* Sets a field parameter value */
  bool AddFieldFilter (const char* pValue, const dword Flags);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObRecordFilter();
  //~CObRecordFilter() { Destroy(); }
  void Destroy (void);

	/* Checks if a record matches the filter */
  bool CheckRecord (CObRecord* pRecord);

	/* Count records matching filter in the given file */
  dword CountMatchingRecords (CObEspFile& File);
  dword CountMatchingRecords (CObGroup* pTopGroup);

	/* Get class members */
  const SSCHAR*    GetID          (void) const { return (m_ID); }
  const SSCHAR*    GetDisplayName (void) const { return (m_DisplayName); }
  const SSCHAR*    GetMaterial    (void) const { return (m_Material); }
  const SSCHAR*    GetNameFilter  (void) const { return (m_NameFilter); }
  const SSCHAR*    GetParentName  (void) const { return (m_ParentName); }
  CObRecordFilter* GetParent      (void)       { return (m_pParent); }
  obrectype_t      GetRecordType  (void) const { return (m_RecordType); }
  dword            GetUserData    (void) const { return (m_UserData); }
  dword		   GetRecordCount (void) const { return (m_RecordCount); }
  bool		   HasParent      (void)       { return (m_pParent != NULL || !m_ParentName.IsEmpty()); }
  
  	/* Check flags and masks */
  bool IsFlagEmpty       (void) { return CheckFlagBits(m_Flags,      OB_RECFILTER_FLAG_EMPTY); }
  bool IsMaskRecordType  (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_RECORDTYPE); }
  bool IsMaskMaterial    (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_MATERIAL); }
  bool IsMaskItemName    (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_ITEMNAME); }
  bool IsMaskWeaponType  (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_WEAPONTYPE); }
  bool IsMaskArmorType   (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_ARMORTYPE); }
  bool IsMaskBipedParts  (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_BIPEDPARTS); }
  bool IsMaskScriptType  (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_SCRIPTTYPE); }
  bool IsMaskEnchantType (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_ENCHANTTYPE); }
  bool IsMaskSpellType   (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_SPELLTYPE); }
  bool IsMaskSpellLevel  (void) { return CheckFlagBits(m_FilterMask, OB_RECFILTER_MASK_SPELLLEVEL); }

	/* Sets a filter parameter from the given value-variable string pair */
  bool SetParameter (const SSCHAR* pVariable, const SSCHAR* pValue);

  	/* Set class members */
  void SetID          (const char*      pString) { m_ID           = pString; }
  void SetDisplayName (const char*      pString) { m_DisplayName  = pString; }
  void SetMaterial    (const char*      pString) { m_Material     = pString; }
  void SetNameFilter  (const char*      pString) { m_NameFilter   = pString; }
  void SetParentName  (const char*      pString) { m_ParentName   = pString; }
  void SetParent      (CObRecordFilter* pParent) { m_pParent      = pParent; }
  void SetEmpty       (const bool          Flag) { m_Flags        = Flag; }
  void SetUserData    (const dword        Value) { m_UserData     = Value; }
  void SetRecordCount (const dword        Value) { m_RecordCount  = Value; }
  void ModRecordCount (const int          Value) { m_RecordCount += Value; }

 };

	/* An array of record filters */
  typedef CObPtrArray<CObRecordFilter> CObRecFilterArray;
/*===========================================================================
 *		End of Class CObRecordFilter Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Find a filter by its display name */
  CObRecordFilter* FindObRecordFilter (const SSCHAR* pID, CObRecFilterArray& Filters);

	/* Load a filter file into an array */
  bool LoadObRecordFilters (const SSCHAR* pFilename, CObRecFilterArray& Records);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obrecordfilter.H
 *=========================================================================*/
