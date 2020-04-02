/*===========================================================================
 *
 * File:	Obbasesubrec.CPP
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	April 6, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obsubrecord.h"
#include "../records/obrecordfield.h"
#include "limits.h"


/*===========================================================================
 *
 * Class CObSubrecord Constructor
 *
 *=========================================================================*/
CObSubrecord::CObSubrecord () {

  m_RecordType  = OB_NAME_NULL;
  m_RecordSize  = 0;
     
}
/*===========================================================================
 *		End of Class CObSubrecord Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Destructor
 *
 *=========================================================================*/
CObSubrecord::~CObSubrecord () {

}
/*===========================================================================
 *		End of Class CObSubrecord Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - void Destroy (void);
 *
 * Delete class contents.
 *
 *=========================================================================*/
void CObSubrecord::Destroy (void) {

  m_RecordType  = OB_NAME_NULL;
  m_RecordSize  = 0;

}
/*===========================================================================
 *		End of Class Method CObSubrecord::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
bool CObSubrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {

  switch (FieldID) {
    case OB_FIELD_RECORDTYPE:
	Result = strnicmp(GetRecordType(), pSubrecord->GetRecordType(), OB_RECTYPE_SIZE);
	return (true);
   }

	/* No match */
  return (false);
 }
/*===========================================================================
 *		End of Class Method CObSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool Copy (pSubrecord);
 *
 *=========================================================================*/
bool CObSubrecord::Copy (CObSubrecord* pSubrecord) {

  Destroy();

  if (pSubrecord == NULL) return (false);

  m_RecordSize = pSubrecord->GetRecordSize();

  return (true);
}
/*===========================================================================
 *		End of Class Method CObSubrecord::Copy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - dword Find (obfinddata_t& FindData);
 *
 *=========================================================================*/
dword CObSubrecord::Find (obfinddata_t& FindData) {
  dword       Count;
  dword       FindCount = 0;

  ++FindData.SubrecordCount;

	/* Look in the subrecord header if required */
  if (FindData.Flags & OB_FIND_SUBRECORDHEADER) {
    Count      = ObFindData((const byte*) &m_RecordType, 6, FindData);
    FindCount += Count;
  }

	/* Look in the subrecord data */
  if (GetData() != NULL) FindCount += ObFindData(GetData(), GetRecordSize(), FindData);
  return (FindCount);
}
/*===========================================================================
 *		End of Class Method CObSubrecord::Find()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - dword FindText (obfinddata_t& FindData);
 *
 *=========================================================================*/
dword CObSubrecord::FindText (obfinddata_t& FindData) {
  dword       Count;
  dword       FindCount = 0;

  ++FindData.SubrecordCount;

	/* Look in the subrecord header if required */
  if ((FindData.Flags & OB_FIND_SUBRECORDHEADER) != 0) {
    Count      = ObFindTextData((const byte*) &m_RecordType, 6, FindData);
    FindCount += Count;
  }

	/* Look in the subrecord data */
  FindCount += ObFindTextData(GetData(), GetRecordSize(), FindData);
  return (FindCount);
}
/*===========================================================================
 *		End of Class Method CObSubrecord::FindText()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
bool CObSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_RECORDTYPE:
        Buffer.Format("%4.4s", GetRecordType().Name);
	break;
    default:
	return (false);
   }

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObSubrecord::GetField()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool Read (File);
 *
 * Reads the subrecord data starting from the current location in the 
 * given File. Returns false on any error.
 *
 *=========================================================================*/
bool CObSubrecord::Read (CObFile& File) {
  return ReadData(File);
 }
/*===========================================================================
 *		End of Class Method CObSubrecord::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool ReadData (File);
 *
 * Reads the subrecord data starting from the current location in the 
 * given File. Returns false on any error.
 *
 *=========================================================================*/
bool CObSubrecord::ReadData (CObFile& File) {
  return File.SeekCur(m_RecordSize);
}
/*===========================================================================
 *		End of Class Method CObSubrecord::ReadData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool Write (File);
 *
 * Write the subrecord starting from the current location in the given File.
 * Returns false on any error.
 *
 *=========================================================================*/
bool CObSubrecord::Write (CObFile& File) {
  bool Result;
  
  	/* Output the subrecord header */
  Result = File.Write(&m_RecordType, OB_RECTYPE_SIZE);
  if (!Result) return (false);

  if (m_RecordSize > USHRT_MAX) { 
    Result = File.WriteWord(0);
    if (!Result) return (false);
   }
  else {
    Result = File.WriteWord(GetRecordSize());
    if (!Result) return (false);
   }

  return WriteData(File);
 }
/*===========================================================================
 *		End of Class Method CObSubrecord::Write()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObSubrecord Method - bool WriteData (File);
 *
 * Write the raw subrecord data. Returns false on any error.
 *
 *=========================================================================*/
bool CObSubrecord::WriteData (CObFile& File) {
  
  if (m_RecordSize > 0) {
    return File.SeekCur(m_RecordSize);
   }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObSubrecord::WriteData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ReadObSubRecordHeader (File, Header);
 *
 * Reads in a subrecord header. Returns false on any error.
 *
 *=========================================================================*/
bool ReadObSubRecordHeader (CObFile& File, obsubrecheader_t& Header) {
  
	/* Input the record header */
  return File.Read(&Header, sizeof(Header));
 }
/*===========================================================================
 *		End of Function ReadObSubRecordHeader()
 *=========================================================================*/

