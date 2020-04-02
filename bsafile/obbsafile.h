/*===========================================================================
 *
 * File:	Obbsafile.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	October 3, 2006
 *
 * Defines the CObBsaFile class for handling BSA files.
 *
 *=========================================================================*/
#ifndef __OBBSAFILE_H
#define __OBBSAFILE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbsafolder.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default header data */
  #define OB_BSAHEADER_FILEID	"BSA\0"
  #define OB_BSAHEADER_VERSION	0x67

	/* Archive flags */
  #define OB_BSAARCHIVE_PATHNAMES	1
  #define OB_BSAARCHIVE_FILENAMES	2
  #define OB_BSAARCHIVE_COMPRESSFILES	4

	/* File flags */
  #define OB_BSAFILE_NIF	0x0001
  #define OB_BSAFILE_DDS	0x0002
  #define OB_BSAFILE_XML	0x0004
  #define OB_BSAFILE_WAV	0x0008
  #define OB_BSAFILE_MP3	0x0010
  #define OB_BSAFILE_TXT	0x0020
  #define OB_BSAFILE_HTML	0x0020
  #define OB_BSAFILE_BAT	0x0020
  #define OB_BSAFILE_SCC	0x0020
  #define OB_BSAFILE_SPT	0x0040
  #define OB_BSAFILE_TEX	0x0080
  #define OB_BSAFILE_FNT	0x0080
  #define OB_BSAFILE_CTL	0x0100

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
  struct obbsaheader_t {
	char		FileID[4];		/* BSA\0 */
	dword		Version;
	dword		FolderRecordOffset;
	dword		ArchiveFlags;
	dword		FolderCount;
	dword		FileCount;
	dword		FolderNameLength;
	dword		FileNameLength;
	dword		FileFlags;
  };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBsaFile Definition
 *
 *=========================================================================*/
class CObBsaFile {

  /*---------- Begin Private Class Members ----------------------*/
private:
  obbsaheader_t		m_Header;

  CObBsaFolderRecord	m_Folders;

  int			m_FilenameOffset;
  int			m_FileDataOffset;

  dword64		m_Filetime;
  int64			m_Filesize;
 
  CSString		m_Filename;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper input/output methods */
  bool ReadHeader          (CObFile& File);
  bool WriteHeader         (CObFile& File);
  bool ReadFolders         (CObFile& File);
  bool WriteFolders        (CObFile& File);
  bool WriteFolderHeaders  (CObFile& File);
  bool ReadFilenames       (CObFile& File);
  bool WriteFilenames      (CObFile& File);
  bool WriteData           (CObFile& File);
  void UpdateFileOffsets   (void);
  void UpdateFolderOffsets (void);

  bool CopyFileData (CObBsaFileRecord* pFile, CObFile& InputFile, CObFile& OutputFile);
  

  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBsaFile();
  virtual ~CObBsaFile() { Destroy(); }
  virtual void Destroy (void);

	/* Iterate through files */
  CObBsaFileRecord* GetFirstFile (BSAPOSITION& Position) { Position.FolderIndex = 0; Position.FileIndex = -1; return GetNextFile(Position); }
  CObBsaFileRecord* GetNextFile  (BSAPOSITION& Position);

	/* Get class members */
  dword64     GetFiletime  (void) { return (m_Filetime); }
  const char* GetFilename  (void) { return (m_Filename); }
  bool        IsCompressed (void) { return ((m_Header.ArchiveFlags & OB_BSAARCHIVE_COMPRESSFILES) != 0); }

  bool Load  (const char* pFilename);
  bool Save  (const char* pFilename);
  bool Read  (CObFile& File);
  bool Write (CObFile& File);

};

	/* Arrays of BSA files */
  typedef CObPtrArray<CObBsaFile>    CObBsaFileArray;
  typedef CObRefPtrArray<CObBsaFile> CObRefBsaFileArray;

/*===========================================================================
 *		End of Class CObBsaFile Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  void ObBsaDefaultHeader (obbsaheader_t& Header);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbsafile.H
 *=========================================================================*/
