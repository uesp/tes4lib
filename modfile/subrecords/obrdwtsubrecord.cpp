/*===========================================================================
 *
 * File:	ObRdwtSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	September 20, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrdwtsubrecord.h"


/*===========================================================================
 *
 * Class CObRdwtSubrecord Constructor
 *
 *=========================================================================*/
CObRdwtSubrecord::CObRdwtSubrecord () {


}
/*===========================================================================
 *		End of Class CObRdwtSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObRdwtSubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObRdwtSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObRdwtSubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
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
 *		End of Class Method CObRdwtSubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObRdwtSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObRdwtSubrecord* pSubrecord1 = ObCastClassNull(CObRdwtSubrecord, pSubrecord);
  dword		    Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetRdwtArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetRdwtArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRdwtSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObRdwtSubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index].FormID, m_Values[Index].FormID, FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObRdwtSubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObRdwtSubrecord::ReadData (CObFile& File) { 
  obrdwtdata_t Data;
  dword        NumRecords = m_RecordSize / sizeof(obrdwtdata_t);
  dword        ExtraBytes = m_RecordSize % sizeof(obrdwtdata_t);
  dword        Index;
  bool         Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&Data, sizeof(obrdwtdata_t));
    if (!Result) return (false);

    m_Values[Index] = Data;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in RDWT subrecord!", ExtraBytes);
    Result = File.Read((void *)&Data, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdwtSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRdwtSubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObRdwtSubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obrdwtdata_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRdwtSubrecord::WriteData()
 *=========================================================================*/
