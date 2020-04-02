/*===========================================================================
 *
 * File:	ObRdsdSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrdsdsubrecord.h"


/*===========================================================================
 *
 * Class CObRdsdSubrecord Constructor
 *
 *=========================================================================*/
CObRdsdSubrecord::CObRdsdSubrecord () {


}
/*===========================================================================
 *		End of Class CObRdsdSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRdsdSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRdsdSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObRdsdSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
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
 *		End of Class Method CObRdsdSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObRdsdSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObRdsdSubrecord* pSubrecord1 = ObCastClassNull(CObRdsdSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetRdsdArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetRdsdArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRdsdSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObRdsdSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index].FormID, m_Values[Index].FormID, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRdsdSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObRdsdSubrecord::ReadData (CObFile& File) { 
  obrdsddata_t Data;
  dword        NumRecords = m_RecordSize / sizeof(obrdsddata_t);
  dword        ExtraBytes = m_RecordSize % sizeof(obrdsddata_t);
  dword        Index;
  bool         Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(obrdsddata_t));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in RDSD subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdsdSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdsdSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObRdsdSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obrdsddata_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdsdSubrecord::WriteData()
 *=========================================================================*/
