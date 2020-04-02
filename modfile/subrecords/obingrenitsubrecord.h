/*===========================================================================
 *
 * File:	Obingrenitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBINGRENITSUBRECORD_H
#define __OBINGRENITSUBRECORD_H


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

	/* Standard INGR-ENIT subrecord size in bytes */
  #define OB_INGRENIT_SUBRECORD_SIZE	8

	/* Ammo data flags */
  #define OB_INGRENIT_FLAG_MANUALCALC	0x00000001
  #define OB_INGRENIT_FLAG_FOODITEM	0x00000002

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Ammo DATA structure */
  struct obingrenitdata_t {
	dword	Value;
	dword	Flags;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObIngrEnitSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObIngrEnitSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObIngrEnitSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obingrenitdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OB_INGRENIT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OB_INGRENIT_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObIngrEnitSubrecord() { }
  //virtual ~CObIngrEnitSubrecord() { Destroy(); }
  virtual void Destroy (void) { CObSubrecord::Destroy(); }

 	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObIngrEnitSubrecord* pSubrecord1 = ObCastClassNull(CObIngrEnitSubrecord, pSubrecord);
	m_RecordSize = OB_INGRENIT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetEnchantData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObIngrEnitSubrecord); }

	/* Get class members */
  obingrenitdata_t& GetEnchantData (void) { return (m_Data); }
  virtual byte*	    GetData        (void) { return (byte *)(&m_Data); }
  dword             GetValue       (void) { return (m_Data.Value); }
  bool		    IsAutoCalc	   (void) { return !CheckFlagBits(m_Data.Flags, OB_INGRENIT_FLAG_MANUALCALC); }
  bool		    IsFoodItem     (void) { return CheckFlagBits(m_Data.Flags, OB_INGRENIT_FLAG_FOODITEM); }
  
	/* Initialize a new record */
  void InitializeNew (void) { CObSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = OB_INGRENIT_SUBRECORD_SIZE; }

	/* Set class members */
  void SetValue    (const dword Value) { m_Data.Value  = Value; }
  void SetAutoCalc (const bool  Value) { FlipFlagBits(m_Data.Flags, OB_INGRENIT_FLAG_MANUALCALC, !Value); }
  void SetFoodItem (const bool  Value) { FlipFlagBits(m_Data.Flags, OB_INGRENIT_FLAG_FOODITEM,    Value); }

 };
/*===========================================================================
 *		End of Class CObIngrEnitSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obingrenitsubrecord.H
 *=========================================================================*/
