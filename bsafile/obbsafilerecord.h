/*===========================================================================
 *
 * File:	Obbsafilerecord.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBSAFILERECORD_H
#define __OBBSAFILERECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../common/obfile.h"
  #include "../common/obptrarray.h"
  #include "../common/sstring.h"
  #include "../common/oblogfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/

/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Bitmasks for the size field in the header */
  #define OB_BSAFILEREC_SIZEMASK 0x7fffffff
  #define OB_BSAFILEREC_FLAGMASK 0xC0000000

	/* Record flags */
  #define OB_BSAFILEREC_FLAG_COMPRESS	0x80000000

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

  	/* BSA file header */
  struct obbsafileheader_t {
	int64		NameHash;
	dword		Filesize;
	dword		Offset;
  };

#pragma pack(pop)

	/* Forward class definition */
  class CObBsaFolder;
  class CObBsaFile;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBsaFileRecord Definition
 *
 *=========================================================================*/
class CObBsaFileRecord {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  CSString		m_Filename;
  obbsafileheader_t	m_Header;
  CObBsaFolder*		m_pFolder;

  CSString		m_TmpFilename;

  dword			m_InputOffset;
  dword			m_Filesize;
  dword			m_Flags;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper input/output methods */
  bool ReadHeader  (CObFile& File);
  bool WriteHeader (CObFile& File);

  bool SaveFileData           (CObFile& OutputFile, CObFile& InputFile);
  bool SaveCompressedFileData (CObFile& OutputFile, CObFile& InputFile);
  bool MakeTempFilename       (CSString& OutputFilename, const char* pTempPath);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBsaFileRecord();
  virtual ~CObBsaFileRecord() { Destroy(); }
  virtual void Destroy (void);

	/* Get class members */
  dword64	GetFiletime	 (void);
  dword         GetFilesize      (void) { return (m_Filesize); }
  const char*   GetFilename      (void) { return (m_Filename); }
  const char*   GetTmpFilename   (void) { return (m_TmpFilename); }
  dword		GetFilenameSize  (void) { return (m_Filename.GetLength()); }
  bool          IsCompressToggle (void) { return (m_Flags & OB_BSAFILEREC_FLAG_COMPRESS) != 0; }
  CObBsaFolder* GetFolder        (void) { return (m_pFolder); }
  CObBsaFile*   GetParentFile    (void);
  const char*   GetFullFilename  (void);
  const char*   GetFullPath      (void);
  dword		GetOffset        (void) { return (m_Header.Offset); }
  dword		GetInputOffset   (void) { return (m_InputOffset); }

	/* Is the file data compressed or not */
  bool IsCompressed (void);

	/* Set class members */
  void SetCompressToggle (const bool     Flag) { if (Flag) {m_Flags |= OB_BSAFILEREC_FLAG_COMPRESS; } else { m_Flags &= ~OB_BSAFILEREC_FLAG_COMPRESS; } }
  void SetFilename       (const char* pString) { m_Filename = pString; }
  void SetTmpFilename    (const char* pString) { m_TmpFilename = pString; }
  void SetFolder         (CObBsaFolder* pFold) { m_pFolder  = pFold; }
  void SetOffset         (const dword  Offset) { m_Header.Offset = Offset; }
  void SetInputOffset    (const dword  Offset) { m_InputOffset   = Offset; }

	/* Input/output record */
  bool Read  (CObFile& File);
  bool Write (CObFile& File);

	/* Output a BSA record to a seperate file */
  bool SaveFile            (const char* pOutput);
  bool SaveTempFile        (CSString& OutputFilename, const char* pTempPath);
  bool GetExistingTempFile (CSString& Filename, const char* pTempPath);

};

	/* Array of file pointers */
  typedef CObPtrArray<CObBsaFileRecord> CObBsaFileRecArray;

/*===========================================================================
 *		End of Class CObBsaFileRecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/
  int64 ObHashString64 (const char* pString);

  bool ObReadBString  (CSString& String, CObFile& File);
  bool ObWriteBString (CSString& String, CObFile& File);

  bool GetFileInfo (const char* pFilename, int64& Filesize, dword64& Filetime);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbsafilerecord.H
 *=========================================================================*/
