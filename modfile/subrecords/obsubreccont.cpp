/*===========================================================================
 *
 * File:	ObSubreccont.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obsubreccont.h"


/*===========================================================================
 *
 * Class CObSubrecContainer Constructor
 *
 *=========================================================================*/
CObSubrecContainer::CObSubrecContainer () {

 }
/*===========================================================================
 *		End of Class CObSubrecContainer Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecContainer Method - void Destroy (void);
 *
 * Destroy object contents.
 *
 *=========================================================================*/
void CObSubrecContainer::Destroy (void) {
  m_Subrecords.Destroy();
 }
/*===========================================================================
 *		End of Class Method CObSubrecContainer::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecContainer Method - void Delete (Type);
 *
 * Delete all subrecords matching the given type.
 *
 *=========================================================================*/
void CObSubrecContainer::Delete (const obrectype_t Type) {
  int Index;

	/* Iterate through the array in reverse looking for name matches */
  for (Index = m_Subrecords.GetSize() - 1; Index >= 0; --Index) {
    if (m_Subrecords[Index]->GetRecordType() == Type) m_Subrecords.Delete(Index);
   }

 }
/*===========================================================================
 *		End of Class Method CObSubrecContainer::Delete()
 *=========================================================================*/
