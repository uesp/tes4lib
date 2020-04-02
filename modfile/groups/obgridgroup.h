/*===========================================================================
 *
 * File:	ObGridGroup.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 13, 2006
 *
 * Defines the CObGridGroup for handling type groups.
 *
 *=========================================================================*/
#ifndef __OBGRIDGROUP_H
#define __OBGRIDGROUP_H


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
 * Begin Class CObGridGroup Definition
 *
 * Description
 *
 *=========================================================================*/
class CObGridGroup : public CObGroup {
  DECLARE_OBCLASS(CObGridGroup, CObGroup)

  /*---------- Begin Private Class Members ----------------------*/
private:


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObGridGroup(const bool UseRef = false) : CObGroup(UseRef) { }
  //virtual ~CObGridGroup() { Destroy(); }
  //virtual void Destroy (void);

	/* Attempt to add a child record */
  bool AddChildRecord (CObBaseRecord* pNewRecord) { return (false); }
  //bool IsValidChild   (CObBaseRecord* pNewRecord);

	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObGridGroup); }

	/* Get class members */
  int GetGridX (void) const { return (m_Header.Data.XGrid); }
  int GetGridY (void) const { return (m_Header.Data.YGrid); }

	/* Get class members */
  void SetGridX (const int X) { m_Header.Data.XGrid = X; }
  void SetGridY (const int Y) { m_Header.Data.YGrid = Y; }
  void SetGrid  (const int X, const int Y) { m_Header.Data.XGrid = X; m_Header.Data.XGrid = Y; }

 };
/*===========================================================================
 *		End of Class CObGridGroup Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObRefGroup Definition
 *
 *=========================================================================*/
class CObRefGridGroup : public CObGridGroup {

public:

  CObRefGridGroup() : CObGridGroup(true) { }

  	/* Return a new class instance */
  static CObGroup* Create (void) { return (new CObRefGridGroup); }

};
/*===========================================================================
 *		End of Class CObRefGroup Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObGridGroup.H
 *=========================================================================*/
