/*===========================================================================
 *
 * File:	ObDataSubrecord.H
 * Author:	Dave Humphrey (uesp@m0use.net)
 * Created On:	October 12, 2006
 *
 * Description
 *
 *=========================================================================*/
#ifndef __OBDATASUBRECORD_H
#define __OBDATASUBRECORD_H


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

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
   
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class CObDataSubrecord Definition
 *
 *=========================================================================*/
class CObDataSubrecord : public CObSubrecord {
  DECLARE_OBBASE(CObDataSubrecord)

  /*---------- Begin Protected Class Members --------------------*/
protected:
  byte*		m_pData;


  /*---------- Begin Protected Class Methods --------------------*/
protected:

	/* Output the raw subrecord data */
  virtual bool ReadData  (CObFile& File);
  virtual bool WriteData (CObFile& File);


  /*---------- Begin Public Class Methods -----------------------*/
public:

	/* Class Constructors/Destructors */
  CObDataSubrecord();
  virtual ~CObDataSubrecord();
  virtual void Destroy (void);

	/* Allocate a raw buffer */
  void AllocateNew (const dword Size);

	/* Copy the content from an existing subrecord */
  virtual bool Copy (CObSubrecord* pSubrecord);

	/* Create a class instance */
  static CObSubrecord* Create (void) { return (new CObDataSubrecord); }

	/* Get class members */
  virtual byte*	GetData (void) { return (m_pData); }

	/* Set data */
  virtual void SetData (const byte* pData, const word Size);

};
/*===========================================================================
 *		End of Class CObDataSubrecord Definition
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File ObDataSubrecord.H
 *=========================================================================*/
