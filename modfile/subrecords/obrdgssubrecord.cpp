/*===========================================================================
 *
 * File:	ObRdgsSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrdgssubrecord.h"


/*===========================================================================
 *
 * Class CObRdgsSubrecord Constructor
 *
 *=========================================================================*/
CObRdgsSubrecord::CObRdgsSubrecord () {


}
/*===========================================================================
 *		End of Class CObRdgsSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRdgsSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRdgsSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObRdgsSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
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
 *		End of Class Method CObRdgsSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObRdgsSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObRdgsSubrecord* pSubrecord1 = ObCastClassNull(CObRdgsSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetRdgsArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetRdgsArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRdgsSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObRdgsSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index].FormID, m_Values[Index].FormID, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRdgsSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObRdgsSubrecord::ReadData (CObFile& File) { 
  obrdgsdata_t Data;
  dword        NumRecords = m_RecordSize / sizeof(obrdgsdata_t);
  dword        ExtraBytes = m_RecordSize % sizeof(obrdgsdata_t);
  dword        Index;
  bool         Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(obrdgsdata_t));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in RDGS subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdgsSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdgsSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObRdgsSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obrdgsdata_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdgsSubrecord::WriteData()
 *=========================================================================*/
