/*===========================================================================
 *
 * File:	Obschrsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBSCHRSUBRECORD_H
#define __OBSCHRSUBRECORD_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "obsubrecord.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Standard SCHR subrecord size in bytes */
  #define OB_SCHR_SUBRECORD_SIZE	0x14

	/* SCHR data types */
  #define OB_SCRIPTTYPE_OBJECT		0
  #define OB_SCRIPTTYPE_QUEST		1
  #define OB_SCRIPTTYPE_MAGICEFFECT	0x100

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* SCHR data structure */
  struct obschrdata_t {
	dword	Unknown;
	dword	RefCount;
	dword	CompiledSize;
	dword	VariableCount;
	dword	Type;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObSchrSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObSchrSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObSchrSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obschrdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_SCHR_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_SCHR_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObSchrSubrecord() { }
  //virtual ~CObSchrSubrecord() { Destroy(); }
  //virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObSchrSubrecord* pSubrecord1 = ObCastClassNull(CObSchrSubrecord, pSubrecord);
	m_RecordSize = OB_SCHR_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetScriptData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObSchrSubrecord); }

	/* Get class members */
  obschrdata_t& GetScriptData    (void) { return (m_Data); }
  virtual byte*	GetData          (void) { return (byte *)(&m_Data); }
  dword		GetRefCount      (void) { return (m_Data.RefCount); }
  dword		GetCompiledSize  (void) { return (m_Data.CompiledSize); }
  dword		GetVariableCount (void) { return (m_Data.VariableCount); }
  dword		GetType          (void) { return (m_Data.Type); }
 
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_SCHR_SUBRECORD_SIZE; }

	/* Set class members */
  void SetType          (const dword Value) { m_Data.Type          = Value; }
  void SetCompiledSize  (const dword Value) { m_Data.CompiledSize  = Value; }
  void SetVariableCount (const dword Value) { m_Data.VariableCount = Value; }
  void SetRefCount      (const dword Value) { m_Data.RefCount      = Value; }
};
/*===========================================================================
 *		End of Class CObSchrSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obschrsubrecord.H
 *=========================================================================*/
