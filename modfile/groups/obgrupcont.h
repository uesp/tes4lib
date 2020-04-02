/*===========================================================================
 *
 * File:	Obgrupcont.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Defines the CObGrupContainer used to handle a collection of group 
 * records.
 *
 *=========================================================================*/
#ifndef __OBGRUPCONT_H
#define __OBGRUPCONT_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obgroup.h"
  #include "../../common/obptrarray.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObGrupContainer Definition
 *
 * Description
 *
 *=========================================================================*/
class CObGrupContainer {

  /*---------- Begin Private Class Members ----------------------*/
private:
  CObPtrArray<CObGroup> m_Groups;		/* Container of groups */


  /*---------- Begin Protected Class Methods --------------------*/
protected:


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObGrupContainer();
  ~CObGrupContainer() { Destroy(); }
  void Destroy (void);

	/* Add records */
  void Add (CObGroup* pGroup) { m_Groups.Add(pGroup); }

	/* Access records */
  CObGroup* GetRecord (const int Index) { return m_Groups[Index]; }

 };
/*===========================================================================
 *		End of Class CObGrupContainer Definition
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File Obgrupcont.H
 *=========================================================================*/
