/*===========================================================================
 *
 * File:	Obstring1subrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obstring1subrecord.h"


/*===========================================================================
 *
 * Class CObString1Subrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObString1Subrecord::ReadData (CObFile& File) { 
  bool Result;

	/* Preallocate the string to the desired size */
  m_String.Empty();
  m_String.SetSize(m_RecordSize);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  Result = File.Read((void *)(const SSCHAR *)m_String, m_RecordSize);

	/* Ensure the string/record is the correct size by checking that is nul terminated */
  if (m_String.GetAt(m_RecordSize - 1) == NULL_CHAR) m_String.Truncate(m_RecordSize - 1);

  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObString1Subrecord::ReadData()
 *=========================================================================*/
