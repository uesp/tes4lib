/*===========================================================================
 *
 * File:	Obbsafolder.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 3, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBBSAFOLDER_H
#define __OBBSAFOLDER_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obbsafilerecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* BSA file header */
  struct obbsafolderheader_t {
	int64		NameHash;
	dword		FileCount;
	dword		Offset;
  };

#pragma pack(pop)

	/* Used to iterate through files */
  struct BSAPOSITION {
	int	FolderIndex;
	int	FileIndex;
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObBsaFolder Definition
 *
 *=========================================================================*/
class CObBsaFolder {

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obbsafolderheader_t	m_Header;
  CSString		m_FolderName;

  CObBsaFileRecArray	m_Files;

  CObBsaFile*		m_pBsaFile;		/* Parent file */


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Helper input/output methods */
  bool ReadHeader  (CObFile& File);
  bool WriteHeader (CObFile& File);
  bool ReadFiles   (CObFile& File);
  bool WriteFiles  (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObBsaFolder();
  virtual ~CObBsaFolder() { Destroy(); }
  virtual void Destroy (void);

	/* Get class members */
  dword         GetOffset         (void) { return (m_Header.Offset); }
  const char*   GetFolderName     (void) { return (m_FolderName); }
  dword         GetFolderNameSize (void) { return (m_FolderName.GetLength()); }
  CObBsaFile*   GetBsaFile        (void) { return (m_pBsaFile); }
  dword64       GetFiletime       (void);

	/* Iterate through records */
  CObBsaFileRecord* GetNextFile (BSAPOSITION& Position);

	/* Set class members */
  void SetOffset  (const dword     Value) { m_Header.Offset = Value; }
  void SetBsaFile (CObBsaFile*     pFile) { m_pBsaFile      = pFile; }

	/* Input/output the folder data */
  bool Read          (CObFile& File);
  bool Write         (CObFile& File);
  bool ReadContents  (CObFile& File);
  bool WriteContents (CObFile& File);


};

	/* Array of folder pointers */
  typedef CObPtrArray<CObBsaFolder> CObBsaFolderRecord;

/*===========================================================================
 *		End of Class CObBsaFolder Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obbsafolder.H
 *=========================================================================*/
