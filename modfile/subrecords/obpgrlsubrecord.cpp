/*===========================================================================
 *
 * File:	ObPgrlSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obpgrlsubrecord.h"


/*===========================================================================
 *
 * Class CObPgrlSubrecord Constructor
 *
 *=========================================================================*/
CObPgrlSubrecord::CObPgrlSubrecord () {
  m_FormID = 0;

}
/*===========================================================================
 *		End of Class CObPgrlSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObPgrlSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObPgrlSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {

  if (m_FormID == OldID) {
    m_FormID = NewID;
    return (1);
  }

  return (0);
}
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObPgrlSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObPgrlSubrecord* pSubrecord1 = ObCastClassNull(CObPgrlSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  m_FormID = pSubrecord1->GetFormID();

  for (Index = 0; Index < pSubrecord1->GetPgrlArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetPgrlArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObPgrlSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  return ObFixupFormid(m_FormID, m_FormID, FixupArray);;
}
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObPgrlSubrecord::ReadData (CObFile& File) { 
  long         Data;
  dword        NumRecords = (m_RecordSize - 4) / sizeof(long);
  dword        ExtraBytes = (m_RecordSize - 4) % sizeof(long);
  dword        Index;
  bool         Result;

	/* Preallocate the array to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

  Result = File.Read(&m_FormID, 4);
  if (!Result) return (false);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(long));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in PGRL subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObPgrlSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObPgrlSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  Result = File.Write(&m_FormID, 4);
  if (!Result) return (false);

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(long));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObPgrlSubrecord::WriteData()
 *=========================================================================*/
