/*===========================================================================
 *
 * File:	Obmemfile.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 11, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obmemfile.h"



/*===========================================================================
 *
 * Class CObMemFile Constructor
 *
 *=========================================================================*/
CObMemFile::CObMemFile () {

  m_pBuffer    = NULL;
  m_BufferSize = 0;
  m_Position   = 0;
  m_ErrorCount = 0;

 }

CObMemFile::CObMemFile (const dword Size) {

  m_pBuffer    = NULL;
  m_BufferSize = 0;
  m_Position   = 0;
  m_ErrorCount = 0;

  Open(Size);
 }
/*===========================================================================
 *		End of Class CObMemFile Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Destructor
 *
 *=========================================================================*/
CObMemFile::~CObMemFile () {

  if (m_pBuffer != NULL) {
    delete[] m_pBuffer;
   }

 }
/*===========================================================================
 *		End of Class CObMemFile Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - void Destroy (void);
 *
 *=========================================================================*/
void CObMemFile::Destroy (void) {
  Close();
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - void Close (void);
 *
 *=========================================================================*/
void CObMemFile::Close (void) {

  if (m_pBuffer != NULL) {
    delete[] m_pBuffer;
    m_pBuffer = NULL;
   }

  m_BufferSize = 0;
  m_Position   = 0;
  m_ErrorCount = 0;
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Close()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Open (BufferSize);
 *
 * Main open method for the memory mapped buffer. Creates a buffer the
 * given size.
 *
 *=========================================================================*/
bool CObMemFile::Open (const dword BufferSize) {

	/* Close an open file */
  Close();

  m_pBuffer    = new byte[BufferSize + 4];
  m_BufferSize = BufferSize;
  m_Position   = 0;

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Open()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Open (pFilename, pFileMode);
 *
 *=========================================================================*/
bool CObMemFile::Open (const SSCHAR*, const SSCHAR*) {
  return AddObUserError(OBERR_USER_BADINPUT, "Open(pFilename, pFileMode) not valid for a memory buffer file!");
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Open()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Read (pBuffer, Size);
 *
 * Reads bytes from the memory buffer.
 *
 *=========================================================================*/
bool CObMemFile::Read (void* pBuffer, const int Size) {
  int ReadSize;

	/* Ignore if not open */
  if (!IsOpen()) {
    ++m_ErrorCount;
    return AddObUserError(OBERR_USER_NOTOPEN);
   }

  ReadSize = Size;
  if (ReadSize + m_Position > m_BufferSize) ReadSize = m_BufferSize - m_Position;

	/* Abort if not enough bytes to read */
  if (ReadSize != Size) {
    if (ReadSize > 0) memmove(pBuffer, m_pBuffer + m_Position, ReadSize);
    ++m_ErrorCount;
    m_Position += ReadSize;
    return AddObSystemError("Failed to read data from memory buffer! Only %d of %d bytes input.", ReadSize, Size);
   }

  memmove(pBuffer, m_pBuffer + m_Position, ReadSize);
  m_Position += ReadSize;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Read()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Save (pFilename);
 *
 * Dump the current memory buffer to the given file.
 *
 *=========================================================================*/
bool CObMemFile::Save (const char* pFilename) {
  CObFile NewFile;
  bool    Result;

	/* Ignore if not open */
  if (!IsOpen()) {
    ++m_ErrorCount;
    return AddObUserError(OBERR_USER_NOTOPEN);
   }

  Result = NewFile.Open(pFilename, "wb");
  if (!Result) return (false);

  Result = NewFile.Write(m_pBuffer, m_BufferSize);
  return (Result);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Save()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Seek (Offset);
 *
 * Description
 *
 *=========================================================================*/
bool CObMemFile::Seek (const int Offset) {

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (Offset > (int) m_BufferSize) return AddObSystemError("Failed to set the memory file absolute position to %lu!", Offset);

  m_Position = Offset;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Seek()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool SeekCur (Offset);
 *
 *=========================================================================*/
bool CObMemFile::SeekCur (const int Offset) {
  int NewPos = Offset + m_Position;

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (NewPos > (int) m_BufferSize || NewPos < 0) return AddObSystemError("Failed to set the memory file relative position to %lu!", Offset);

  m_Position = NewPos;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::SeekCur()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Seek64 (Offset);
 *
 * Description
 *
 *=========================================================================*/
bool CObMemFile::Seek64 (const int64 Offset) {

  if (!IsOpen()) return AddObUserError(OBERR_USER_NOTOPEN);
  if (Offset > m_BufferSize) return AddObSystemError("Failed to set the memory file position to %lu!", Offset);

  m_Position = (dword) (dword64) Offset;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Seek()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObMemFile Method - bool Write (pBuffer, Size);
 *
 * Write bytes to the memory buffer.
 *
 *=========================================================================*/
bool CObMemFile::Write (const void* pBuffer, const int Size) {
  int WriteSize;

	/* Ignore if not open */
  if (!IsOpen()) {
    ++m_ErrorCount;
    return AddObUserError(OBERR_USER_NOTOPEN);
   }

  WriteSize = Size;
  if (WriteSize + m_Position > m_BufferSize) WriteSize = m_BufferSize - m_Position;

	/* Abort if not enough bytes to read */
  if (WriteSize != Size) {
    if (WriteSize > 0) memmove(m_pBuffer + m_Position, pBuffer, WriteSize);
    ++m_ErrorCount;
    m_Position += WriteSize;
    return AddObSystemError("Failed to write data to memory buffer! Only %d of %d bytes output.", WriteSize, Size);
   }

  memmove(m_pBuffer + m_Position, pBuffer, WriteSize);
  m_Position += WriteSize;
  return (true);
 }
/*===========================================================================
 *		End of Class Method CObMemFile::Write()
 *=========================================================================*/

