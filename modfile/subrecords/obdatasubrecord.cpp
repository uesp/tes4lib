/*===========================================================================
 *
 * File:	ObDataSubrecord.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obdatasubrecord.h"


/*===========================================================================
 *
 * Class CObDataSubrecord Constructor
 *
 *=========================================================================*/
CObDataSubrecord::CObDataSubrecord () {
  m_pData = NULL;
    
}
/*===========================================================================
 *		End of Class CObDataSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Destructor
 *
 *=========================================================================*/
CObDataSubrecord::~CObDataSubrecord () {

  if (m_pData != NULL) {
    delete[] m_pData;
  }

}
/*===========================================================================
 *		End of Class CObDataSubrecord Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - void Destroy (void);
 *
 * Delete class contents.
 *
 *=========================================================================*/
void CObDataSubrecord::Destroy (void) {
    
  if (m_pData != NULL) {
    delete[] m_pData;
    m_pData = NULL;
  }

}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - void AllocateNew (Size);
 *
 * Allocates a new data buffer the given size.
 *
 *=========================================================================*/
void CObDataSubrecord::AllocateNew (const dword Size) {

  if (m_pData != NULL) {
    delete[] m_pData;
    m_pData = NULL;
  }

  m_RecordSize = Size;

  m_pData = new byte[Size];
  //memset(m_pData, 0, Size);
}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::AllocateNew()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObDataSubrecord::Copy (CObSubrecord* pSubrecord) {
  CObDataSubrecord* pData;

  if (pSubrecord == NULL) return (false);

  pData = ObCastClass(CObDataSubrecord, pSubrecord);
  if (pData == NULL) return (false);

  m_RecordSize = pData->GetRecordSize();
  if (m_RecordSize == 0) return (true);

  m_pData = new byte[m_RecordSize];

  memcpy(m_pData, pData->GetData(), m_RecordSize);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - bool ReadData (File);
 *
 * Reads the subrecord data starting from the current location in the 
 * given File. Returns false on any error.
 *
 *=========================================================================*/
bool CObDataSubrecord::ReadData (CObFile& File) {
  bool Result;

	/* Delete any existing raw data */
  if (m_pData != NULL) {
    delete[] m_pData;
    m_pData    = NULL;
   }
  
	/* Ignore if no data to load */
  if (m_RecordSize == 0) return (true);

	/* Allocate the raw data buffer */
  m_pData = new byte[m_RecordSize];

	/* Read in the raw data */
  Result = File.Read(m_pData, m_RecordSize);
  return (Result);
}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - void SetData (pData, Size);
 *
 *=========================================================================*/
void CObDataSubrecord::SetData (const byte* pData, const word Size) {

  if (m_pData != NULL) {
    delete[] m_pData;
    m_pData = NULL;
    m_RecordSize = 0;
  }

  if (Size == 0) return;

  m_pData = new byte[Size + 2];
  m_RecordSize = Size;
  memcpy(m_pData, pData, Size);
}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::SetData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObDataSubrecord Method - bool WriteData (File);
 *
 * Write the raw subrecord data. Returns false on any error.
 *
 *=========================================================================*/
bool CObDataSubrecord::WriteData (CObFile& File) {
  
  if (m_RecordSize > 0 && m_pData != NULL) {
    return File.Write(m_pData, m_RecordSize);
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObDataSubrecord::WriteData()
 *=========================================================================*/
