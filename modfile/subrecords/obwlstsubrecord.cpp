/*===========================================================================
 *
 * File:	ObWlstSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obwlstsubrecord.h"


/*===========================================================================
 *
 * Class CObWlstSubrecord Constructor
 *
 *=========================================================================*/
CObWlstSubrecord::CObWlstSubrecord () {


}
/*===========================================================================
 *		End of Class CObWlstSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObWlstSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObWlstSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
  dword Index;
  dword Count = 0;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {

    if (m_Values[Index].FormID == OldID) {
      m_Values[Index].FormID = NewID;
      ++Count;
    }
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObWlstSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObWlstSubrecord* pSubrecord1 = ObCastClassNull(CObWlstSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetWlstArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetWlstArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObWlstSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index].FormID, m_Values[Index].FormID, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObWlstSubrecord::ReadData (CObFile& File) { 
  obwlstdata_t Data;
  dword        NumRecords = m_RecordSize / sizeof(obwlstdata_t);
  dword        ExtraBytes = m_RecordSize % sizeof(obwlstdata_t);
  dword        Index;
  bool         Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(obwlstdata_t));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in WLST subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObWlstSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObWlstSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obwlstdata_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObWlstSubrecord::WriteData()
 *=========================================================================*/
