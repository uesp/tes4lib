/*===========================================================================
 *
 * File:	ObFormIDGroup.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObFormIDGroup for handling a group with a parent formID.
 *
 *=========================================================================*/
#ifndef __OBFORMIDGROUP_H
#define __OBFORMIDGROUP_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obgroup.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObFormIDGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObFormIDGroup : public CObGroup {
  DECLARE_OBCLASS(CObFormIDGroup, CObGroup)

  /*---------- Begin Private Class Members ----------------------*/
private:
  obformid_t m_OrigParentFormID;


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObFormIDGroup (const bool UseRef = false) : CObGroup(UseRef) { m_OrigParentFormID = 0; }
  //virtual ~CObFormIDGroup() { Destroy(); }
  //virtual void Destroy (void);

	/* Attempt to add a child record */
  bool AddChildRecord (CObBaseRecord* pNewRecord) { return (false); }
  //bool IsValidChild   (CObBaseRecord* pNewRecord);

  	/* Change one ID for another */
  virtual dword ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
    dword Count = 0;
    if (m_Header.Data.ParentFormID == OldID) { m_Header.Data.ParentFormID = NewID; m_OrigParentFormID = NewID; Count = 1; }
    return (Count + CObGroup::ChangeFormID(NewID, OldID));
  }

	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObFormIDGroup); }

  	/* Fixup the modindex of formids */
  virtual bool FixupFormids (CObFormidFixupArray& FixupArray) {
    bool Result;
    Result  = ObFixupFormid(m_Header.Data.ParentFormID, m_OrigParentFormID, FixupArray);
    Result &= CObGroup::FixupFormids(FixupArray);
    return (Result);
  }

	/* Get class members */
  obformid_t GetParentFormID     (void) const { return (m_Header.Data.ParentFormID); }
  obformid_t GetOrigParentFormID (void) const { return (m_OrigParentFormID); }

  	/* Initialize the record with the given header */
  virtual void Initialize (const obbaseheader_t Header) { CObGroup::Initialize(Header); m_OrigParentFormID = m_Header.Data.ParentFormID; }
  virtual void Initialize (const int            Type)   { CObGroup::Initialize(Type);   m_OrigParentFormID = m_Header.Data.ParentFormID; }

	/* Get class members */
  void SetParentFormID     (const obformid_t FormID) { m_Header.Data.ParentFormID = FormID; }
  void SetOrigParentFormID (const obformid_t FormID) { m_OrigParentFormID = FormID; }

 };
/*===========================================================================
 *		End of Class CObFormIDGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefFormIDGroup : public CObFormIDGroup {

public:

  CObRefFormIDGroup() : CObFormIDGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefFormIDGroup); }

};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File ObFormIDGroup.H
 *=========================================================================*/
