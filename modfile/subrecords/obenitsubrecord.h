/*===========================================================================
 *
 * File:	Obenitsubrecord.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 14, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBENITSUBRECORD_H
#define __OBENITSUBRECORD_H


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

	/* Standard ENIT subrecord size in bytes */
  #define OBENIT_SUBRECORD_SIZE	16

	/* Enchantment flags */
  #define OB_ENCHFLAG_MANUALCALC 0x00000001

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* ENIT data structure */
  struct obenitdata_t {
	dword Type;
	dword ChargeAmount;
	dword EnchantCost;
	dword Flags;
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObEnitSubrecord Definition
 *
 * Description
 *
 *=========================================================================*/
class CObEnitSubrecord : public CObSubrecord {
  DECLARE_OBCLASS(CObEnitSubrecord, CObSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  obenitdata_t	m_Data;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Input/output the subrecord data */
  virtual bool ReadData  (CObFile& File) { return File.Read(&m_Data,  OBENIT_SUBRECORD_SIZE); }
  virtual bool WriteData (CObFile& File) { return File.Write(&m_Data, OBENIT_SUBRECORD_SIZE); }


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObEnitSubrecord();
  //virtual ~CObEnitSubrecord() { Destroy(); }
  virtual void Destroy (void);

	/* Compare two subrecord fields */
  virtual bool CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord);

  	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord) {
	CObEnitSubrecord* pSubrecord1 = ObCastClassNull(CObEnitSubrecord, pSubrecord);
	m_RecordSize = OBENIT_SUBRECORD_SIZE;

	if (pSubrecord1 != NULL) {
	  m_Data = pSubrecord1->GetEnchantData();
	}
	else {
	  memset(&m_Data, 0, sizeof(m_Data));
	}
	return (true);
  }

  	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObEnitSubrecord); }

	/* Get class members */
  obenitdata_t& GetEnchantData (void) { return (m_Data); }
  virtual byte*	GetData        (void) { return (byte *)(&m_Data); }
  dword		GetType        (void) { return (m_Data.Type); }
  dword		GetCharge      (void) { return (m_Data.ChargeAmount); }
  dword		GetCost        (void) { return (m_Data.EnchantCost); }
  bool          IsAutoCalc     (void) { return !CheckFlagBits(m_Data.Flags, OB_ENCHFLAG_MANUALCALC); }

  	/* Get a string representation of a subrecord field */
  bool GetField (CSString& Buffer, const int FieldID);
  	
	/* Initialize a new record */
  void InitializeNew (void);

	/* Set class members */
  void SetAutoCalc (const bool  Flag)  { FlipFlagBits(m_Data.Flags,  OB_ENCHFLAG_MANUALCALC, !Flag); }
  void SetType     (const dword Value) { m_Data.Type         = Value; }
  void SetCharge   (const dword Value) { m_Data.ChargeAmount = Value; }
  void SetCost     (const dword Value) { m_Data.EnchantCost  = Value; }

 };
/*===========================================================================
 *		End of Class CObEnitSubrecord Definition
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnitSubrecord Method - int CompareFields (Result, FieldID, pSubrecord);
 *
 *=========================================================================*/
inline bool CObEnitSubrecord::CompareFields (int& Result, const int FieldID, CObSubrecord* pSubrecord) {
  CObEnitSubrecord* pEnit = ObCastClass(CObEnitSubrecord, pSubrecord);

  if (pEnit != NULL) {

    switch (FieldID) {
      case OB_FIELD_CHARGE:
        Result = (int)GetCharge() - (int)pEnit->GetCharge();
	return (true);
      case OB_FIELD_COST:
        Result = (int)GetCost() - (int)pEnit->GetCost();
	return (true);
      case OB_FIELD_AUTOCALC:
        Result = (int)IsAutoCalc() - (int)pEnit->IsAutoCalc();
	return (true);
      case OB_FIELD_RANGE:
	Result = (int)GetType() - (int)pEnit->GetType();
	return (true);
     }

   }

	/* Check subrecord */
  return CObSubrecord::CompareFields(Result, FieldID, pSubrecord);
 }
/*===========================================================================
 *		End of Class Method CObEnitSubrecord::CompareFields()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObEnitSubrecord Method - bool GetField (Buffer, FieldID);
 *
 *=========================================================================*/
inline bool CObEnitSubrecord::GetField (CSString& Buffer, const int FieldID) {
  
  switch (FieldID) {
    case OB_FIELD_CHARGE:
        Buffer.Format("%u", GetCharge());
	return (true);
    case OB_FIELD_COST:
        Buffer.Format("%u", GetCost());
	return (true);
    case OB_FIELD_AUTOCALC:
        Buffer.Format("%s", BooleanToString(IsAutoCalc()));
	return (true);
    case OB_FIELD_RANGE:
        Buffer.Format("%s", GetObEnchantTypeString(GetType()));
	return (true);
   }

  return CObSubrecord::GetField(Buffer, FieldID);
 }
/*===========================================================================
 *		End of Class Method CObEnitSubrecord::GetField()
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obenitsubrecord.H
 *=========================================================================*/
