/*===========================================================================
 *
 * File:	ObFormidArraysubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obformidarraysubrecord.h"


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Constructor
 *
 *=========================================================================*/
CObFormidArraySubrecord::CObFormidArraySubrecord () {


}
/*===========================================================================
 *		End of Class CObFormidArraySubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - void Destroy (void);
 *
 *=========================================================================*/
void CObFormidArraySubrecord::Destroy (void) {

  m_Values.Destroy();

  CObSubrecord::Destroy();
}
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - dword ChangeFormID (NewID, OldID);
 *
 *=========================================================================*/
dword CObFormidArraySubrecord::ChangeFormID (const obformid_t NewID, const obformid_t OldID) {
  dword Index;
  dword Count = 0;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {

    if (m_Values[Index] == OldID) {
      m_Values[Index] = NewID;
      ++Count;
    }
  }

  return (Count);
}
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::ChangeFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObFormidArraySubrecord::Copy (CObSubrecord* pSubrecord) {
  CObFormidArraySubrecord* pSubrecord1 = ObCastClassNull(CObFormidArraySubrecord, pSubrecord);
  dword			   Index;
  
  Destroy();
  if (pSubrecord1 == NULL) return (true);

  for (Index = 0; Index < pSubrecord1->GetFormIDArray().GetSize(); ++Index) {
    m_Values.Add(pSubrecord1->GetFormIDArray()[Index]);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - bool FixupFormID (FixupArray);
 *
 *=========================================================================*/
bool CObFormidArraySubrecord::FixupFormID (CObFormidFixupArray& FixupArray) {
  dword Index;
  bool  Result = true;

  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result &= ObFixupFormid(m_Values[Index], m_Values[Index], FixupArray);
  }

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::FixupFormID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - bool ReadData (File);
 *
 *=========================================================================*/
bool CObFormidArraySubrecord::ReadData (CObFile& File) { 
  obformid_t FormID;
  dword      NumRecords = m_RecordSize / sizeof(obformid_t);
  dword      ExtraBytes = m_RecordSize % sizeof(obformid_t);
  dword      Index;
  bool       Result;

	/* Preallocate the string to the desired size */
  m_Values.Destroy();
  m_Values.SetSize(NumRecords);
  if (m_RecordSize == 0) return (true);

	/* Read in the string data */ 
  for (Index = 0; Index < NumRecords; ++Index) {
    Result = File.Read((void *)&FormID, sizeof(obformid_t));
    if (!Result) return (false);

    m_Values[Index] = FormID;
  }

	/* Check for extra bytes */
  if (ExtraBytes != 0) {
    SystemLog.Printf("Extra %u bytes found in Formid array subrecord!", ExtraBytes);
    Result = File.Read((void *)&FormID, ExtraBytes);
    if (!Result) return (false);
  } 

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObFormidArraySubrecord Method - bool WriteData (File);
 *
 *=========================================================================*/
bool CObFormidArraySubrecord::WriteData (CObFile& File) { 
  dword Index;
  bool  Result;

  	/* Read in the string data */ 
  for (Index = 0; Index < m_Values.GetSize(); ++Index) {
    Result = File.Write(&m_Values[Index], sizeof(obformid_t));
    if (!Result) return (false);
  }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObFormidArraySubrecord::WriteData()
 *=========================================================================*/
