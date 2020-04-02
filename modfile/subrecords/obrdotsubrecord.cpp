/*===========================================================================
 *
 * File:	ObRdotSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrdotsubrecord.h"


/*===========================================================================
 *
 * Class CObRdotSubrecord Constructor
 *
 *=========================================================================*/
CObRdotSubrecord::CObRdotSubrecord () {


}
/*===========================================================================
 *		End of Class CObRdotSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRdotSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRdotSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObRdotSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
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
 *		End of Class Method CObRdotSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObRdotSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObRdotSubrecord* pSubrecord1 = ObCastClassNull(CObRdotSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetRdotArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetRdotArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRdotSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObRdotSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index].FormID, m_Values[Index].FormID, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRdotSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObRdotSubrecord::ReadData (CObFile& File) { 
  obrdotdata_t Data;
  dword        NumRecords = m_RecordSize / sizeof(obrdotdata_t);
  dword        ExtraBytes = m_RecordSize % sizeof(obrdotdata_t);
  dword        Index;
  bool         Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(obrdotdata_t));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in RDOT subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdotSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdotSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObRdotSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obrdotdata_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdotSubrecord::WriteData()
 *=========================================================================*/
