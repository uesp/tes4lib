/*===========================================================================
 *
 * File:	Obcallback.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 29, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obcallback.h"


/*===========================================================================
 *
 * Class CObCallback Constructor
 *
 *=========================================================================*/
CObCallback::CObCallback () {
  m_Function = NULL;

  m_ProcessRecords      = 0;
  m_TotalRecords        = 0;
  m_LastCallbackRecords = 0;
  m_CallbackInterval    = 1000;

  m_TotalRecords1        = 0;
  m_ProcessRecords1      = 0;
  m_LastCallbackRecords1 = 0;

  m_Enabled     = true;
  m_UpdateTitle = false;
  m_UpdateLabel = false;

}
/*===========================================================================
 *		End of Class CObCallback Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - void Destroy (void);
 *
 *=========================================================================*/
void CObCallback::Destroy (void) {
  m_Function = NULL;

  m_Label.Empty();
  m_Title.Empty();

  m_UpdateTitle = false;
  m_UpdateLabel = false;

  m_ProcessRecords      = 0;
  m_TotalRecords        = 0;
  m_LastCallbackRecords = 0;

  m_TotalRecords1        = 0;
  m_ProcessRecords1      = 0;
  m_LastCallbackRecords1 = 0;
}
/*===========================================================================
 *		End of Class Method CObCallback::Destroy()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - int ForceCallback (ProcessRecords);
 *
 *=========================================================================*/
int CObCallback::ForceCallback (const int64 ProcessRecords) {

  m_ProcessRecords = ProcessRecords;
  if (!IsValid()) return (OBCALLBACK_NOFUNCTION);

  m_LastCallbackRecords = m_ProcessRecords;
  return m_Function(this);
}
/*===========================================================================
 *		End of Class Method CObCallback::ForceCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - float GetPercentDone (void);
 *
 *=========================================================================*/
float CObCallback::GetPercentDone (void) {
  float Result;

  if (m_TotalRecords == 0) return (0.0f);

  Result = (float) ((double) m_ProcessRecords * 100.0 / (double) m_TotalRecords);

  if (m_TotalRecords1 != 0) Result += (float) ((double) m_ProcessRecords1 * 100.0 / (double) m_TotalRecords1);

  return (Result);
}
/*===========================================================================
 *		End of Class Method CObCallback::GetPercentDone()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - void Reset (void);
 *
 *=========================================================================*/
void CObCallback::Reset (void) {
  m_ProcessRecords      = 0;
  m_LastCallbackRecords = 0;

  m_ProcessRecords1      = 0;
  m_LastCallbackRecords1 = 0;
}
/*===========================================================================
 *		End of Class Method CObCallback::Reset()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - void SetLabel ( pString, ...);
 *
 *=========================================================================*/
void CObCallback::SetLabel (const SSCHAR* pString, ...) {
  va_list Args;

  if (pString == NULL) {
    m_Label.Empty();
  }
  else {
    va_start(Args, pString);
    m_Label.FormatV(pString, Args);
    va_end(Args);
  }

  m_UpdateLabel = true;
}
/*===========================================================================
 *		End of Class Method CObCallback::SetLabel()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - void SetTitle (pString, ...);
 *
 *=========================================================================*/
void CObCallback::SetTitle (const SSCHAR* pString, ...) {
  va_list Args;

  if (pString == NULL) {
    m_Label.Empty();
  }
  else {
    va_start(Args, pString);
    m_Title.FormatV(pString, Args);
    va_end(Args);
  }

  m_UpdateTitle = true;
}
/*===========================================================================
 *		End of Class Method CObCallback::SetTitle()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - int UpdateCallback (ProcessRecords);
 *
 *=========================================================================*/
int CObCallback::UpdateCallback (const int64 ProcessRecords) {

  m_ProcessRecords = ProcessRecords;
  if (!IsValid()) return (OBCALLBACK_NOFUNCTION);

  if (m_LastCallbackRecords + m_CallbackInterval <= m_ProcessRecords) {
    m_LastCallbackRecords = m_ProcessRecords;

    return m_Function(this);
  }

  return (OBCALLBACK_NOTPROCESSED);
}
/*=====================================================================1======
 *		End of Class Method CObCallback::UpdateCallback()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObCallback Method - int UpdateCallback1 (ProcessRecords);
 *
 *=========================================================================*/
int CObCallback::UpdateCallback1 (const int64 ProcessRecords) {

  m_ProcessRecords1 = ProcessRecords;
  if (!IsValid()) return (OBCALLBACK_NOFUNCTION);

  if (m_LastCallbackRecords1 + m_CallbackInterval <= m_ProcessRecords1) {
    m_LastCallbackRecords1 = m_ProcessRecords1;

    return m_Function(this);
  }

  return (OBCALLBACK_NOTPROCESSED);
}
/*=====================================================================1======
 *		End of Class Method CObCallback::UpdateCallback1()
 *=========================================================================*/


