/*===========================================================================
 *
 * File:	Obrecordlistctrl.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 24, 2006
 *
 * Implements the CObRecordListCtrl class
 *
 *=========================================================================*/

	/* Include Files */
#include "stdafx.h"
#include "ObRecordListCtrl.h"
#include "obedit.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 *=========================================================================*/
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  obreclistoptions_t CObRecordListCtrl::m_Options;

  IMPLEMENT_DYNCREATE(CObRecordListCtrl, CListCtrl);

/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Record List Default Column Data
 *
 *=========================================================================*/
static obreclistcolinit_t s_ActiListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	100,	LVCFMT_LEFT },
	{ OB_FIELD_SCRIPT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_SOUND,	100,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_DANGEROUS,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_AlchListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	100,	LVCFMT_LEFT },
	{ OB_FIELD_SCRIPT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_CENTER },
	{ OB_FIELD_AUTOCALC,	50,	LVCFMT_CENTER },
	{ OB_FIELD_FOODITEM,	50,	LVCFMT_CENTER },
	{ OB_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_AmmoListInit[] = {
	{ OB_FIELD_EDITORID,	  100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	  5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	  50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	  150,	LVCFMT_LEFT },
	{ OB_FIELD_VALUE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_DAMAGE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_SPEED,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTMENT,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTPOINTS, 60,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_IGNORERESIST,  60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_AppaListInit[] = {
	{ OB_FIELD_EDITORID,	  100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	  5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	  50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	  150,	LVCFMT_LEFT },
	{ OB_FIELD_TYPE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_QUALITY,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_ArmoListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_TYPE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_BIPED,	120,	LVCFMT_CENTER },
	{ OB_FIELD_REALARMOR,	60,	LVCFMT_CENTER },
	{ OB_FIELD_HEALTH,	60,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTMENT, 80,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_BookListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_SCROLL,	40,	LVCFMT_CENTER },
	{ OB_FIELD_TEACHES,	75,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTMENT, 80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_ClotListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_TYPE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_BIPED,	120,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTMENT, 80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_ContListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_ITEMCOUNT,   60,     LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_OPENSOUND,	100,	LVCFMT_CENTER },
	{ OB_FIELD_CLOSESOUND,	100,	LVCFMT_CENTER },
	{ OB_FIELD_RESPAWNS,    60,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_EnchListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_CHARGE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_COST,	60,	LVCFMT_CENTER },
	{ OB_FIELD_AUTOCALC,	50,	LVCFMT_CENTER },
	{ OB_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_FlorListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	100,	LVCFMT_CENTER },
	{ OB_FIELD_INGREDIANT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_SPRING,	60,	LVCFMT_CENTER },
	{ OB_FIELD_SUMMER,	60,	LVCFMT_CENTER },
	{ OB_FIELD_FALL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WINTER,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_FurnListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_IngrListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FULLNAME,	100,	LVCFMT_LEFT },
	{ OB_FIELD_SCRIPT,	100,	LVCFMT_CENTER },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_CENTER },
	{ OB_FIELD_AUTOCALC,	50,	LVCFMT_CENTER },
	{ OB_FIELD_FOODITEM,	50,	LVCFMT_CENTER },
	{ OB_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_KeymListInit[] = {
	{ OB_FIELD_EDITORID,	  100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	  5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	  50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	  150,	LVCFMT_LEFT },
	{ OB_FIELD_VALUE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_LighListInit[] = {
	{ OB_FIELD_EDITORID,	 100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,     80,	LVCFMT_CENTER },
	{ OB_FIELD_TIME,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_RADIUS,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_FOV,		 60,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_CARRIED,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_COLOR,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_LvlcListInit[] = {
	{ OB_FIELD_EDITORID,	 100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_TEMPLATE,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_CHANCENONE,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEALL, 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEEACH,60,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMCOUNT,    80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMLIST,	 200,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_LvspListInit[] = {
	{ OB_FIELD_EDITORID,	 100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_CHANCENONE,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEALL, 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEEACH,60,	LVCFMT_CENTER },
	{ OB_FIELD_USEALLSPELLS, 60,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMCOUNT,    80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMLIST,	 200,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_LvliListInit[] = {
	{ OB_FIELD_EDITORID,	 100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_CHANCENONE,	 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEALL, 60,	LVCFMT_CENTER },
	{ OB_FIELD_CALCULATEEACH,60,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMCOUNT,    80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMLIST,	 200,	LVCFMT_LEFT },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_MiscListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_NpcListInit[] = {
	{ OB_FIELD_EDITORID,	 100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	 5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	 50,	LVCFMT_CENTER },
	{ OB_FIELD_FULLNAME,	120,	LVCFMT_CENTER },
	{ OB_FIELD_SCRIPT,	 80,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_ScptListInit[] = {
	{ OB_FIELD_EDITORID,	140,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_LINECOUNT,	75,	LVCFMT_CENTER },
	{ OB_FIELD_SIZE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_SgstListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	140,	LVCFMT_CENTER },
	{ OB_FIELD_USES,	60,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_EFFECTCOUNT,	80,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_SlgmListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	150,	LVCFMT_LEFT },
	{ OB_FIELD_CAPACITY,	60,	LVCFMT_CENTER },
	{ OB_FIELD_SOUL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_SounListInit[] = {
	{ OB_FIELD_EDITORID,	     100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,   	       5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	      50,	LVCFMT_CENTER },
	{ OB_FIELD_SOUNDFILE,	     100,	LVCFMT_CENTER },
	{ OB_FIELD_MINATTENUATION,    60,	LVCFMT_CENTER },
	{ OB_FIELD_MAXATTENUATION,    60,	LVCFMT_CENTER },
	{ OB_FIELD_STATICATTENUATION, 60,	LVCFMT_CENTER },
	{ OB_FIELD_FREQADJUSTMENT,    60,	LVCFMT_CENTER },
	{ OB_FIELD_STARTTIME,         60,	LVCFMT_CENTER },
	{ OB_FIELD_STOPTIME,          60,	LVCFMT_CENTER },
	{ OB_FIELD_RANDOMPLAY,        60,	LVCFMT_CENTER },
	{ OB_FIELD_RANDOMLOCATION,    60,	LVCFMT_CENTER },
	{ OB_FIELD_RANDOMFREQSHIFT,   60,	LVCFMT_CENTER },
	{ OB_FIELD_LOOP,              60,	LVCFMT_CENTER },
	{ OB_FIELD_MENUSOUND,         60,	LVCFMT_CENTER },
	{ OB_FIELD_2DSOUND,           60,	LVCFMT_CENTER },
	{ OB_FIELD_360LFE,            60,	LVCFMT_CENTER },
	{ OB_FIELD_IGNOREENVIRONMENT, 60,	LVCFMT_CENTER },
	
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_SpelListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	140,	LVCFMT_CENTER },
	{ OB_FIELD_TYPE,	75,	LVCFMT_CENTER },
	{ OB_FIELD_COST,	60,	LVCFMT_CENTER },
	{ OB_FIELD_LEVEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	80,	LVCFMT_CENTER },
	{ OB_FIELD_AUTOCALC,	60,	LVCFMT_CENTER },
	{ OB_FIELD_PLAYERSTART,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_StatListInit[] = {
	{ OB_FIELD_EDITORID,	100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	50,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistcolinit_t s_WeapListInit[] = {
	{ OB_FIELD_EDITORID,	  100,	LVCFMT_LEFT },
	{ OB_FIELD_FORMID,	  5,	LVCFMT_LEFT },
	{ OB_FIELD_FLAGS,	  50,	LVCFMT_CENTER },
	{ OB_FIELD_ITEMNAME,	  150,	LVCFMT_LEFT },
	{ OB_FIELD_TYPE,	  100,	LVCFMT_CENTER },
	{ OB_FIELD_VALUE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_WEIGHT,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_DAMAGE,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_SPEED,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_REACH,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_HEALTH,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_USERDATA,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTMENT,	  80,	LVCFMT_CENTER },
	{ OB_FIELD_ENCHANTPOINTS, 60,	LVCFMT_CENTER },
	{ OB_FIELD_MODEL,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_ICON,	  60,	LVCFMT_CENTER },
	{ OB_FIELD_NONE, 0, 0 }
 };

static obreclistinfoinit_t s_ListInit[] = {
	{ &OB_NAME_ACTI, s_ActiListInit, &CObActiRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_ALCH, s_AlchListInit, &CObAlchRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_AMMO, s_AmmoListInit, &CObAmmoRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_APPA, s_AppaListInit, &CObAppaRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_ARMO, s_ArmoListInit, &CObArmoRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_BOOK, s_BookListInit, &CObBookRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_CLOT, s_ClotListInit, &CObClotRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_CONT, s_ContListInit, &CObContRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_ENCH, s_EnchListInit, &CObEnchRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_FLOR, s_FlorListInit, &CObFlorRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_FURN, s_FurnListInit, &CObFurnRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_INGR, s_IngrListInit, &CObIngrRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_KEYM, s_KeymListInit, &CObKeymRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_LIGH, s_LighListInit, &CObLighRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_LVSP, s_LvspListInit, &CObLvspRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_LVLC, s_LvlcListInit, &CObLvlcRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_LVLI, s_LvliListInit, &CObLvliRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_MISC, s_MiscListInit, &CObMiscRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_NPC_, s_NpcListInit,  &CObNpcRecord::s_FieldMap,  OB_FIELD_EDITORID },
	{ &OB_NAME_SCPT, s_ScptListInit, &CObScptRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_SGST, s_SgstListInit, &CObSgstRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_SLGM, s_SlgmListInit, &CObSlgmRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_SOUN, s_SounListInit, &CObSounRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_SPEL, s_SpelListInit, &CObSpelRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_STAT, s_StatListInit, &CObStatRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ &OB_NAME_WEAP, s_WeapListInit, &CObWeapRecord::s_FieldMap, OB_FIELD_EDITORID },
	{ NULL, NULL, NULL }
 };

/*===========================================================================
 *		End of Record List Default Column Data
 *=========================================================================*/


/*===========================================================================
 *
 * Begin CObRecordListCtrl Message Map
 *
 *=========================================================================*/
BEGIN_MESSAGE_MAP(CObRecordListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CObRecordListCtrl)
	ON_NOTIFY_REFLECT(HDN_ITEMCLICK, OnItemclick)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*===========================================================================
 *		End of CObRecordListCtrl Message Map
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int CALLBACK s_DefaultRecListSort (lParam1, lParam2, lParamSort);
 *
 * Default callback function for record list sorting.
 *
 *=========================================================================*/
int CALLBACK s_DefaultRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);

  if (pRecord1 == NULL  || pRecord2 == NULL) return (0);
  
  if (pSortData->Reverse) return -pRecord1->CompareFields(pSortData->FieldID, pRecord2);
  return pRecord1->CompareFields(pSortData->FieldID, pRecord2);
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int CALLBACK s_DefaultCustomRecListSort (lParam1, lParam2, lParamSort);
 *
 * Default callback function for record list sorting with custom data.
 *
 *=========================================================================*/
int CALLBACK s_DefaultCustomRecListSort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
  OBRL_SORTFUNC_GETPARAMS(lParam1, lParam2, lParamSort);
  dword Index;
  bool  Result = false;
  int   Value;

	/* Ensure valid data */
  if (pCustomData1 == NULL || pCustomData2 == NULL) return (0);

	/* Check all subrecord fields first */
  for (Index = 0; Index < OB_RLMAX_SUBRECORDS; ++Index) {
    if (pCustomData1->pSubrecords[Index] == NULL) continue;
    if (pCustomData2->pSubrecords[Index] == NULL) continue;

    Result = pCustomData1->pSubrecords[Index]->CompareFields(Value, pSortData->FieldID, pCustomData2->pSubrecords[Index]);
    if (Result) break;
   }  
  
	/* Use the record comparison only if all the subrecord comparison failed */
  if (pRecord1 == NULL || pRecord2 == NULL) return (0);
  if (!Result) Value = pRecord1->CompareFields(pSortData->FieldID, pRecord2);

  if (pSortData->Reverse) return (-Value);
  return (Value);
}
/*===========================================================================
 *		End of Function CALLBACK s_DefaultCustomRecListSort()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Constructor
 *
 *=========================================================================*/
CObRecordListCtrl::CObRecordListCtrl() {
  m_pCurrentList    = NULL;
  m_pCurrentFilter  = NULL;
  m_AutoResize      = false;
  m_EnableDrag      = true;
  m_ActNormalList   = false;
  m_IsDragging      = false;
  m_ActivateType    = OB_RLACTIVATE_DEFAULT;
  m_pDragImage      = NULL;
  m_AcceptDrop      = true;
  m_LastDropValid   = false;
  m_EnableColors    = true;
  m_pLastDropWnd    = NULL;
  m_DragType        = OB_RECORDLIST_RECORD;

  m_ListName = "DefaultList";

  //m_WantKeys	    = true;

  m_hGoodDropCursor = NULL;
  m_hBadDropCursor  = LoadCursor(NULL, MAKEINTRESOURCE(IDC_NO));
}
/*===========================================================================
 *		End of Class CObRecordListCtrl Constructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Destructor
 *
 *=========================================================================*/
CObRecordListCtrl::~CObRecordListCtrl() {
  m_ListInfos.Destroy();

  if (m_pDragImage != NULL) {
    delete m_pDragImage;
    m_pDragImage = NULL;
  }

}
/*===========================================================================
 *		End of Class CObRecordListCtrl Destructor
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int AddRecord (pRecord);
 *
 * Adds a record to the list using the current setup. Does not check to see
 * if the record is a valid type or not based on the current settings.
 *
 *=========================================================================*/
int CObRecordListCtrl::AddRecord (CObRecord* pRecord) {
  if (pRecord == NULL) return (-1);
  return AddCustomRecord(pRecord, NULL, 0);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AddRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int AddCustomRecord (pRecord, pSubrecord, UserData);
 *
 * Adds a new record in a custom list type.
 *
 *=========================================================================*/
int CObRecordListCtrl::AddCustomRecord (CObRecord* pRecord, CObSubrecord* pSubrecord, const int UserData) {
  obrlcustomdata_t CustomData;

  memset(&CustomData, 0, sizeof(CustomData));
  CustomData.pRecord        = pRecord;
  CustomData.pSubrecords[0] = pSubrecord;
  CustomData.UserData       = UserData;

  return AddCustomRecord(CustomData);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AddCustomRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int AddCustomRecord (CustomData);
 *
 * Adds a new record in a custom list type.
 *
 *=========================================================================*/
int CObRecordListCtrl::AddCustomRecord (obrlcustomdata_t& CustomData) {
  int ListIndex;
  
	/* Ignore if we don't know what we're displaying */
  if (m_pCurrentList == NULL) return (-1);

	/* Insert a new row */
  ListIndex = InsertItem(GetItemCount(), "");
  if (ListIndex < 0) return (ListIndex);
  SetItemData(ListIndex, CustomData);
  
	/* Update all column texts */
  SetColumnTexts(ListIndex, CustomData.pRecord, CustomData.pSubrecords);
  return (ListIndex);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AddCustomRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void AddAllRecords (File);
 *
 * Adds all records from the given file based on the current settings.
 *
 *=========================================================================*/
void CObRecordListCtrl::AddAllRecords (CObEspFile& File) {
  AddAllRecords(&File.GetRecords());
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AddAllRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void AddAllRecords (pTopGroup);
 *
 * Adds all records from the given file based on the current settings.
 *
 *=========================================================================*/
void CObRecordListCtrl::AddAllRecords (CObGroup* pTopGroup) {
  CObTypeGroup*  pGroup;
  CObBaseRecord* pBaseRecord;
  CObRecord*     pRecord;
  dword		 Index;

  if (m_pCurrentList == NULL) return;
  if (pTopGroup      == NULL) return;

  pGroup = pTopGroup->GetTypeGroup(*m_pCurrentList->pRecordType);
  if (pGroup == NULL) return;

  SetRedraw(FALSE);

  for (Index = 0; Index < pGroup->GetNumRecords(); ++Index) {
    pBaseRecord = pGroup->GetRecord(Index);
    pRecord = ObCastClass(CObRecord, pBaseRecord);
    if (pRecord == NULL) continue;

    if (m_pCurrentFilter != NULL) {
      if (m_pCurrentFilter->CheckRecord(pRecord)) AddRecord(pRecord);
     }
    else if (pRecord->GetRecordType() == *m_pCurrentList->pRecordType) 
      AddRecord(pRecord);
   }

	/* Sort the initial list */
  if (m_pCurrentList->SortField != OB_FIELD_NONE) SortListPriv(m_pCurrentList->SortField);
  SetRedraw(TRUE);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AddAllRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void AutoResize (void);
 *
 * Description
 *
 *=========================================================================*/
void CObRecordListCtrl::AutoResize (void) {
  CRect ParentRect;
  CRect NewSize;

  GetParent()->GetClientRect(&ParentRect);

  NewSize.top    = m_AutoResizeOffset.top;
  NewSize.bottom = m_AutoResizeOffset.bottom + ParentRect.bottom - 35;
  NewSize.right  = m_AutoResizeOffset.right  + ParentRect.right + 0;
  NewSize.left   = m_AutoResizeOffset.left;

  SetWindowPos(NULL, NewSize.left, NewSize.top, NewSize.Width(), NewSize.Height(), SWP_NOZORDER | SWP_NOMOVE );
  //SetWindowPos(NULL, 0, 0, NewSize.Width(), NewSize.Height(), SWP_NOZORDER | SWP_NOMOVE );
  //SetWindowPos(NULL, 0, 0, 100, 200, SWP_NOZORDER | SWP_NOMOVE );
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::AutoResize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - obreclistinfo_t* CreateListInfoObject (void);
 *
 * Create and return a new list information structure.
 *
 *=========================================================================*/
obreclistinfo_t* CObRecordListCtrl::CreateListInfoObject (void) {
  obreclistinfo_t* pListInfo;

  pListInfo = new obreclistinfo_t;
  m_ListInfos.Add(pListInfo);
  memset(pListInfo, 0, sizeof(obreclistinfo_t));

  return (pListInfo);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::CreateListInfoObject()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - obreclistinfo_t* CreateDefaultListInfo (Type);
 *
 * Attempts to create a default list information object for the given
 * record type. Returns NULL if it cannot.
 *
 *=========================================================================*/
obreclistinfo_t* CObRecordListCtrl::CreateDefaultListInfo (const obrectype_t Type) {
  obreclistinfo_t* pListInfo;
  dword            Index;

  for (Index = 0; s_ListInit[Index].pRecordType != NULL; ++Index) {
    if (Type == *s_ListInit[Index].pRecordType) {
      pListInfo = InitializeColumns(*s_ListInit[Index].pRecordType, s_ListInit[Index].pInit, s_ListInit[Index].pFieldMap, 0, s_ListInit[Index].SortField);
      if (pListInfo != NULL && m_Options.SaveState) ReadListInfoRegistry(pListInfo);
      return (pListInfo);
     }
   }

	/* Unknown type */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::CreateDefaultListInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void DefaultSettings (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::DefaultSettings (void) {

  SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
 }
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::DefaultSettings()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void DeleteAllColumns (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::DeleteAllColumns (void) {
  
  while (DeleteColumn(0)) {
   }
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::DeleteAllColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - BOOL DeleteAllItems (void);
 *
 *=========================================================================*/
BOOL CObRecordListCtrl::DeleteAllItems (void) {
  m_DragRecords.Destroy();
  m_DragCustomData.Destroy();
  m_CustomData.Destroy();
  
  return CListCtrl::DeleteAllItems();
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::DeleteAllItems()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int FindEditorID (pString);
 *
 *=========================================================================*/
int CObRecordListCtrl::FindEditorID (const SSCHAR* pString) {
  CSString   Buffer;
  CObRecord* pRecord;
  dword      Index;
  bool       Result;
  int        LastMatch = -1;
  int        LastMatchCount = 0;
  int	     Matching;

  for (Index = 0; Index < (dword) GetItemCount(); ++Index) {
    pRecord = GetRecord(Index);
    if (pRecord == NULL) continue;

    Result = pRecord->GetField(Buffer, OB_FIELD_EDITORID);
    if (!Result) continue;

    Matching = Buffer.CountMatchLengthNoCase(pString);

    if (Matching > LastMatchCount) {
      LastMatchCount = Matching;
      LastMatch      = Index;
    }
  } 

  return (LastMatch);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::FindEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - obreclistinfo_t* FindListInfo (Type);
 *
 * Finds the list information structure associated with the given
 * record type. Returns NULL if not found.
 *
 *=========================================================================*/
obreclistinfo_t* CObRecordListCtrl::FindListInfo (const obrectype_t Type) {
  obreclistinfo_t* pListInfo;
  dword		   Index;

  for (Index = 0; Index < m_ListInfos.GetSize(); ++Index) {
    pListInfo = m_ListInfos[Index];
    if (*pListInfo->pRecordType == Type) return (pListInfo);
   }

	/* Not found */
  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::FindListInfo()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool FindRecord (pRecord);
 *
 * Finds the given record in the current list. Returns the list index or
 * -1 if not found.
 *
 *=========================================================================*/
int CObRecordListCtrl::FindRecord (CObRecord* pRecord) {
  CObRecord* pListRecord;
  int	     Index;

  if (pRecord == NULL) return (-1);

  for (Index = 0; Index < this->GetItemCount(); ++Index) {
    pListRecord = GetRecord(Index);
    if (pListRecord == pRecord) return (Index);
  }

  return (-1);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::FindRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - CObRecord* GetRecord (ListIndex);
 *
 *=========================================================================*/
CObRecord* CObRecordListCtrl::GetRecord (const int ListIndex) {
  dword Value;
 
  if (ListIndex < 0 || ListIndex >= GetItemCount()) return (NULL);
  if (m_pCurrentList == NULL) return (NULL);

  Value = GetItemData(ListIndex);
  if (Value == 0) return (NULL);

  switch (m_pCurrentList->Type) {
    case OB_RECORDLIST_RECORD:
        return (CObRecord *) Value;
	break;
    case OB_RECORDLIST_CUSTOM:
        return ((obrlcustomdata_t *) Value)->pRecord;
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::GetRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - obrlcustomdata_t* GetCustomData (ListIndex);
 *
 *=========================================================================*/
obrlcustomdata_t* CObRecordListCtrl::GetCustomData (const int ListIndex) {
  dword Value;
 
  if (ListIndex < 0 || ListIndex >= GetItemCount()) return (NULL);
  if (m_pCurrentList == NULL) return (NULL);

  Value = GetItemData(ListIndex);
  if (Value == 0) return (NULL);

  switch (m_pCurrentList->Type) {
    case OB_RECORDLIST_RECORD:
	return (NULL);        
    case OB_RECORDLIST_CUSTOM:
        return ((obrlcustomdata_t *) Value);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::GetCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - CObRecord* GetSelectedRecord (void);
 *
 * Returns the first selected record in the list or NULL;
 *
 *=========================================================================*/
CObRecord* CObRecordListCtrl::GetSelectedRecord (void) {
  POSITION ListPos;
  int      ListIndex;

  ListPos = GetFirstSelectedItemPosition();
  if (ListPos == NULL) return (NULL);

  ListIndex = GetNextSelectedItem(ListPos);
  return GetRecord(ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::GetSelectedRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - CObRecord* GetSelectedCustomData (void);
 *
 * Returns the first selected custom data in the list or NULL;
 *
 *=========================================================================*/
obrlcustomdata_t* CObRecordListCtrl::GetSelectedCustomData (void) {
  POSITION ListPos;
  int      ListIndex;

  ListPos = GetFirstSelectedItemPosition();
  if (ListPos == NULL) return (NULL);

  ListIndex = GetNextSelectedItem(ListPos);
  return GetCustomData(ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::GetSelectedCustomData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int GetSelectedItem (void);
 *
 * Returns the first selected custom data in the list or NULL;
 *
 *=========================================================================*/
int CObRecordListCtrl::GetSelectedItem (void) {
  POSITION ListPos;
  int      ListIndex;

  ListPos = GetFirstSelectedItemPosition();
  if (ListPos == NULL) return (-1);
  
  ListIndex = GetNextSelectedItem(ListPos);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::GetSelectedItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - obreclistinfo_t* InitializeColumns (Type, ListInit, pFieldMap, Flags, SortField);
 *
 * Initialize the list info for the given record type. Returns the
 * new object on success or NULL on any error.
 *
 *=========================================================================*/
obreclistinfo_t* CObRecordListCtrl::InitializeColumns (const obrectype_t& Type, obreclistcolinit_t* ListInit, const obrecfieldmap_t* pFieldMap, const dword Flags, const obrecfieldid_t SortField) {
  const obrecfieldmap_t* pMap;
  obreclistinfo_t*	 pListInfo = NULL;
  obreclistcolumn_t*	 pColumn;
  dword			 Index;
  dword			 ColIndex;
  dword			 SubItem;

	/* Ignore invalid input */
  if (ListInit == NULL) return (NULL);

	/* Update an existing or create a new record */
  if ((Flags & OBRL_INITCOL_FORCENEW) == 0) pListInfo = FindListInfo(Type);
  if (pListInfo == NULL) pListInfo = CreateListInfoObject();

	/* Initialize the list info */
  pListInfo->Type        = OB_RECORDLIST_RECORD;
  pListInfo->pRecordType = &Type;
  pListInfo->NumColumns  = 0;
  pListInfo->SortSubItem = -1;
  pListInfo->SortField   = SortField;
  pListInfo->SortReverse = false;
  SubItem                = 0;

	/* Add all the predefined columns */
  for (Index = 0; ListInit[Index].FieldID != OB_FIELD_NONE; ++Index) {
    ColIndex = pListInfo->NumColumns;

    pListInfo->Columns[ColIndex].Display     = true;
    pListInfo->Columns[ColIndex].Format      = ListInit[Index].Format;
    pListInfo->Columns[ColIndex].Width       = ListInit[Index].Width;
    pListInfo->Columns[ColIndex].CompareFunc = ListInit[Index].CompareFunc;
    pListInfo->Columns[ColIndex].SubItem     = SubItem;
    pListInfo->Columns[ColIndex].FieldID     = ListInit[Index].FieldID;
    pListInfo->Columns[ColIndex].pField      = FindObFieldEntry(pFieldMap, ListInit[Index].FieldID);
    pListInfo->Columns[ColIndex].ColumnIndex = -1;

    if (pListInfo->Columns[ColIndex].pField == NULL) {
      pListInfo->Columns[ColIndex].SetTitle(GetObFieldString(pListInfo->Columns[ColIndex].FieldID));
    }
    else {
      pListInfo->Columns[ColIndex].SetTitle(pListInfo->Columns[ColIndex].pField->pName);
    }

    ++pListInfo->NumColumns;
    ++SubItem;
    if (pListInfo->NumColumns >= OB_RECLIST_MAXCOLS) break;
  }
  
	/* Add any remaining columns from the map heirarchy if required */
  if ((Flags & OBRL_INITCOL_NOEXTRAFIELDS) != 0) return (pListInfo);

  for (pMap = pFieldMap; pMap != NULL; pMap = pMap->pBaseFieldMap) {
    assert(pMap != pMap->pBaseFieldMap);

    for (Index = 0; pMap->pField[Index].GetMethod != NULL; ++Index) {
      pColumn = FindListColumn(pListInfo, pMap->pField[Index].FieldID);
      if (pColumn != NULL) continue;

      ColIndex = pListInfo->NumColumns;
       
      pListInfo->Columns[ColIndex].Display     = true;
      pListInfo->Columns[ColIndex].Format      = LVCFMT_CENTER;
      pListInfo->Columns[ColIndex].Width       = 20;
      pListInfo->Columns[ColIndex].SubItem     = SubItem;
      pListInfo->Columns[ColIndex].FieldID     = pMap->pField[Index].FieldID;
      pListInfo->Columns[ColIndex].pField      = &pMap->pField[Index];
      pListInfo->Columns[ColIndex].ColumnIndex = -1;
      pListInfo->Columns[ColIndex].SetTitle(pListInfo->Columns[ColIndex].pField->pName);
      
      ++pListInfo->NumColumns;
      ++SubItem;
      if (pListInfo->NumColumns >= OB_RECLIST_MAXCOLS) break;
    }
  }

  return (pListInfo);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::InitializeColumns()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnColumnclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnColumnclick (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*       pNMListView = (NM_LISTVIEW*)pNMHDR;
  obreclistcolumn_t* pColumn;
  int	             SubItem;
  *pResult = 0;

	/* Ignore if current list is invalid */
  if (m_pCurrentList == NULL) return;
  SubItem = pNMListView->iSubItem;

  if (SubItem == m_pCurrentList->SortSubItem) {
    m_pCurrentList->SortReverse = !m_pCurrentList->SortReverse;
  }
  else {
    m_pCurrentList->SortReverse = false;
    m_pCurrentList->SortSubItem = SubItem;
  }

  pColumn = FindListColumnBySubItem(m_pCurrentList, SubItem);
  if (pColumn == NULL) return;
  m_pCurrentList->SortField = pColumn->FieldID;

  SortListPriv(m_pCurrentList->SortField);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnColumnclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnCustomdraw (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnCustomdraw (NMHDR* pNMHDR, LRESULT* pResult) {
  NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	/* Take the default processing unless we set this to something else below. */
  *pResult = CDRF_DODEFAULT; 
  if (!m_Options.EnableColors || !m_EnableColors) return;

	/* First thing - check the draw stage. If it's the control's prepaint
	 * stage, then tell Windows we want messages for every item. */
  if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage ) {
    *pResult = CDRF_NOTIFYITEMDRAW;
  }
        /* This is the prepaint stage for an item. Here's where we set the
           item's text/back color. */
  else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage ) {
    CObRecord* pRecord;

    pRecord = GetRecord(pLVCD->nmcd.dwItemSpec);

    if (pRecord != NULL) {
      int Score = INT_MAX;

      if (pRecord->IsDeleted() && m_Options.DeletedColor.Enable && m_Options.DeletedColor.Order < Score) {
        Score = m_Options.DeletedColor.Order;
        pLVCD->clrTextBk = m_Options.DeletedColor.Color;
      }

      if (pRecord->IsActive() && m_Options.ActiveColor.Enable && m_Options.ActiveColor.Order < Score) {
        Score = m_Options.ActiveColor.Order;
        pLVCD->clrTextBk = m_Options.ActiveColor.Color;
      }

      if (pRecord->IsIgnored() && m_Options.IgnoredColor.Enable && m_Options.IgnoredColor.Order < Score) {
        Score = m_Options.IgnoredColor.Order;
        pLVCD->clrTextBk = m_Options.IgnoredColor.Color;
      }

      if (pRecord->IsQuestItem() && m_Options.QuestColor.Enable && m_Options.QuestColor.Order < Score) {
        Score = m_Options.QuestColor.Order;
        pLVCD->clrTextBk = m_Options.QuestColor.Color;
      }

      if (pRecord->IsDangerous() && m_Options.DangerousColor.Enable && m_Options.DangerousColor.Order < Score) {
        Score = m_Options.DangerousColor.Order;
        pLVCD->clrTextBk = m_Options.DangerousColor.Color;
      }
    }
		/* Tell Windows to paint the control itself */
    *pResult = CDRF_DODEFAULT;
  }

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnCustomdraw()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnDblclk (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnDblclk (NMHDR* pNMHDR, LRESULT* pResult) {
  POSITION	    SelPos;
  CObRecord*	    pRecord;
  CWnd*	            pWnd;
  bool		    AltState;
  int		    MsgID = ID_OBRECORDLIST_ACTIVATE;
  int               SelIndex;

	/* Ignore if we are not activating items */
  if (m_ActivateType == OB_RLACTIVATE_NONE) return;

  AltState = GetAsyncKeyState(VK_MENU) != 0;
  if (AltState) MsgID = ID_OBRECORDLIST_ALTACTIVATE;
  
  SelPos = GetFirstSelectedItemPosition();
  if (SelPos == NULL) return;

  SelIndex = GetNextSelectedItem(SelPos);
  if (SelIndex < 0) return;

  pRecord = GetRecord(SelIndex);

  pWnd = GetOwner();
  if (pWnd == NULL) pWnd = GetParent();

  if (pWnd != NULL) {
    pWnd->PostMessage(MsgID, (WPARAM) pRecord, 0);
  }

  *pResult = 0;
 }
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnDblclk()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnItemclick (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnItemclick (NMHDR* pNMHDR, LRESULT* pResult) {
  HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	
  *pResult = 0;
 }
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnItemclick()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnSize (nType, cx, cy);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnSize (UINT nType, int cx, int cy) {
  CListCtrl::OnSize(nType, cx, cy);
 }
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnSize()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void ResetContents (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::ResetContents (void) {
  DeleteAllItems();
  DeleteAllColumns();
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::ResetContents()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SelectRecord (pRecord);
 *
 *=========================================================================*/
bool CObRecordListCtrl::SelectRecord (CObRecord* pRecord) {
  CObRecord* pListRecord;
  int	     Index;

  for (Index = 0; Index < GetItemCount(); ++Index) {
    SetItemState(Index, 0, LVIS_SELECTED);

    pListRecord = GetRecord(Index);
    if (pListRecord == NULL) continue;

    if (pListRecord == pRecord) {
      SetItemState(Index, LVIS_SELECTED, LVIS_SELECTED);
      EnsureVisible(Index, FALSE);
    }
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SelectRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SelectRecord (ListIndex);
 *
 *=========================================================================*/
void CObRecordListCtrl::SelectRecord (const int ListIndex) {
  SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
  EnsureVisible(ListIndex, FALSE);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SelectRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SetItemData (ListIndex, pRecord);
 *
 *=========================================================================*/
void CObRecordListCtrl::SetItemData (const int ListIndex, CObRecord* pRecord) {
  obrlcustomdata_t* pCustomData;

  if (m_pCurrentList == NULL) return;

  switch (m_pCurrentList->Type) {  
    case OB_RECORDLIST_RECORD: 
        CListCtrl::SetItemData(ListIndex, (DWORD) (void *) pRecord);
	break;
    case OB_RECORDLIST_CUSTOM: 
        pCustomData = new obrlcustomdata_t;
	m_CustomData.Add(pCustomData);

	memset(pCustomData, 0, sizeof(obrlcustomdata_t));
	pCustomData->pRecord = pRecord;

	CListCtrl::SetItemData(ListIndex, (DWORD) (void *) pCustomData);
	break;
   }

 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SetItemData (ListIndex, pRecord, pSubrecord, UserData);
 *
 *=========================================================================*/
void CObRecordListCtrl::SetItemData (const int ListIndex, CObRecord* pRecord, CObSubrecord* pSubrecord, const int UserData) {
  obrlcustomdata_t* pCustomData;

  if (m_pCurrentList == NULL) return;

  switch (m_pCurrentList->Type) {  
    case OB_RECORDLIST_RECORD: 
        CListCtrl::SetItemData(ListIndex, (DWORD) (void *) pRecord);
	break;
    case OB_RECORDLIST_CUSTOM: 
        pCustomData = new obrlcustomdata_t;
	m_CustomData.Add(pCustomData);

        memset(pCustomData, 0, sizeof(obrlcustomdata_t));
	pCustomData->pRecord        = pRecord;
	pCustomData->pSubrecords[0] = pSubrecord;
	pCustomData->UserData       = UserData;

	CListCtrl::SetItemData(ListIndex, (DWORD) (void *) pCustomData);
	break;
   }

 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SetItemData (ListIndex, CustomData);
 *
 *=========================================================================*/
void CObRecordListCtrl::SetItemData (const int ListIndex, const obrlcustomdata_t CustomData) {
  obrlcustomdata_t* pCustomData;

  if (m_pCurrentList == NULL) return;

  switch (m_pCurrentList->Type) {  
    case OB_RECORDLIST_RECORD: 
        CListCtrl::SetItemData(ListIndex, (DWORD) (void *) CustomData.pRecord);
	break;
    case OB_RECORDLIST_CUSTOM: 
        pCustomData = new obrlcustomdata_t;
	m_CustomData.Add(pCustomData);

	*pCustomData = CustomData;

	CListCtrl::SetItemData(ListIndex, (DWORD) (void *) pCustomData);
	break;
   }

 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetItemData()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetCustomField (ListIndex, FieldID, pString);
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetCustomField (const int ListIndex, const obrecfieldid_t FieldID, const SSCHAR* pString) {
  obreclistcolumn_t* pColumn;

	/* Ignore if no current list to display */
  if (m_pCurrentList == NULL) return (false);

  pColumn = FindListColumn(m_pCurrentList, FieldID);
  if (pColumn == NULL) return (false);

  SetItemText(ListIndex, pColumn->SubItem, pString);  
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetCustomField()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetupList (pListInfo);
 *
 * Sets up a list based on the input list information.
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetupList (obreclistinfo_t* pListInfo) {
  obreclistcolumn_t* pColumn;
  dword		     Index;
  dword		     ColCount = 0;

  if (m_Options.SaveState) ReadListInfoRegistry(pListInfo);

  for (Index = 0; Index < pListInfo->NumColumns; ++Index) {
    pColumn = &pListInfo->Columns[Index];
    if (!pColumn->Display) continue;

    pColumn->ColumnIndex = InsertColumn(Index, pColumn->Title, pColumn->Format, pColumn->Width, pColumn->SubItem);
    ++ColCount;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetupList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetupList (Type);
 *
 * Sets up the list for the given record type. Returns false if the 
 * column definition for the type is not found.
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetupList (const obrectype_t Type) {
  obreclistinfo_t* pListInfo;
  dword		   ColCount = 0;

	/* Clear the current list contents and columns */
  ResetContents();
  
	/* Attempt to find the given list definition */
  pListInfo = FindListInfo(Type);

  if (pListInfo == NULL) {
    pListInfo = CreateDefaultListInfo(Type);
    if (pListInfo == NULL) return (false);
   }

  m_pCurrentList = pListInfo;
  SetupList(pListInfo);

  return (true);
 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetupList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetupList (pFilter);
 *
 * Sets up the list for the given filter.
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetupList (CObRecordFilter* pFilter) {
  bool Result;

  if (m_pCurrentFilter == pFilter) return (true);
  UpdateCurrentList();
  
  if (pFilter == NULL) {
    ResetContents();
    m_pCurrentList   = NULL;
    m_pCurrentFilter = NULL;
    return (true);
  }

	/* Setup the list again if needed */
  if (m_pCurrentFilter == NULL || m_pCurrentFilter->GetRecordType() != pFilter->GetRecordType()) {
    Result = SetupList(pFilter->GetRecordType());
    m_pCurrentFilter = pFilter;
    if (!Result) return (false);
  }
  else {
    DeleteAllItems();
    m_pCurrentFilter = pFilter;
  }

  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetupList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetupList (Type, pListInit, pFieldMap);
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetupList (const obrectype_t& Type, obreclistcolinit_t* pListInit, const obrecfieldmap_t* pFieldMap) {
  obreclistinfo_t* pListInfo;
  
  pListInfo = InitializeColumns(Type, pListInit, pFieldMap, OBRL_INITCOL_FORCENEW | OBRL_INITCOL_NOEXTRAFIELDS);
  if (pListInfo == NULL) return (false);

  m_pCurrentList = pListInfo;
  return SetupList(pListInfo);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetupList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool SetupCustomList (pColumns, pFieldMap);
 *
 *=========================================================================*/
bool CObRecordListCtrl::SetupCustomList (obreclistcolinit_t* pColumns, const obrecfieldmap_t* pFieldMap, const obrecfield_t* pCustomFields) {
  const obrecfield_t* pField;
  dword	   	      Index;
  
	/* Ignore invalid input */
  if (pColumns == NULL) return (false);

	/* Save the current content */
  UpdateCurrentList();
  
	/* Destroy the current setup  */
  ResetContents();

	/* Create a new list object */
  m_pCurrentList = CreateListInfoObject();
  m_pCurrentList->pRecordType = NULL;
  m_pCurrentList->Type        = OB_RECORDLIST_CUSTOM;
  
  for (Index = 0; pColumns[Index].FieldID != OB_FIELD_NONE; ++Index) {
    if (m_pCurrentList->NumColumns >= OB_RECLIST_MAXCOLS) break;
    
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].ColumnIndex = m_pCurrentList->NumColumns;
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].SubItem     = m_pCurrentList->NumColumns;
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].Display     = true;
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].Width       = pColumns[Index].Width;
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].Format      = pColumns[Index].Format;
    m_pCurrentList->Columns[m_pCurrentList->NumColumns].CompareFunc = pColumns[Index].CompareFunc;

    pField = FindObField(pCustomFields, pColumns[Index].FieldID);
    if (pField == NULL && pFieldMap != NULL) pField = FindObFieldEntry(pFieldMap, pColumns[Index].FieldID);

    if (pField != NULL) {
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].pField  = pField;
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].FieldID = pField->FieldID;
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].SetTitle(pField->pName);
      ++m_pCurrentList->NumColumns;
    }
    else {
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].pField  = NULL;
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].FieldID = pColumns[Index].FieldID;
      m_pCurrentList->Columns[m_pCurrentList->NumColumns].SetTitle(GetObFieldString(pColumns[Index].FieldID));
    }
   }

  SetupList(m_pCurrentList);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetupCustomList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SetAutoResizeOffset (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::SetAutoResizeOffset (void) {
  CRect ParentRect;
  CRect ThisRect;
  CRect FrameRect;

  GetWindowRect(&ThisRect);
  //GetClientRect(&ThisRect);
  GetParent()->GetClientRect(&ParentRect);
  GetParentFrame()->GetClientRect(&FrameRect);

  m_AutoResizeOffset.top    = ThisRect.top;
  m_AutoResizeOffset.bottom = ThisRect.bottom - ParentRect.bottom;
  m_AutoResizeOffset.right  = ThisRect.right  - ParentRect.right;
  m_AutoResizeOffset.left   = ThisRect.left;

 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetAutoResizeOffset()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SetColumnTexts (ListIndex, pRecord, pSubrecords);
 *
 * Updates the given record text in the list.
 *
 *=========================================================================*/
void CObRecordListCtrl::SetColumnTexts (const int ListIndex, CObRecord* pRecord, CObSubrecord* pSubrecords[]) {
  obreclistcolumn_t* pColumn;
  CSString	     Buffer;
  dword		     Index;
  dword		     SubIndex;
  bool		     Result;
  
  if (m_pCurrentList == NULL) return;
  if (pRecord        == NULL) return;
  
	/* Update all column texts */
  for (Index = 0; Index < m_pCurrentList->NumColumns; ++Index) {
    pColumn = &m_pCurrentList->Columns[Index];
    if (!pColumn->Display) continue;

		/* Use the supplied field method if available */
    if (pColumn->pField != NULL && pColumn->pField->GetMethod != NULL) {
      (pRecord ->*pColumn->pField->GetMethod)(Buffer, 0);
      SetItemText(ListIndex, pColumn->SubItem, Buffer);
      continue;
    }
    
		/* Try the record general field method */
    Result = pRecord->GetField(Buffer, pColumn->FieldID);

    if (Result) {
      SetItemText(ListIndex, pColumn->SubItem, Buffer);
      continue;
    }

		/* Try all valid subrecord general fields if present */
    if (pSubrecords == NULL) continue;

    for (SubIndex = 0; SubIndex < OB_RLMAX_SUBRECORDS; ++SubIndex) {
      if (pSubrecords[SubIndex] == NULL) continue;
      Result = pSubrecords[SubIndex]->GetField(Buffer, pColumn->FieldID);

      if (Result) {
        SetItemText(ListIndex, pColumn->SubItem, Buffer);
        break;
      }
    }
  }

}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SetColumnTexts()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SortList (FieldID);
 *
 *=========================================================================*/
void CObRecordListCtrl::SortList (const obrecfieldid_t FieldID, const bool Reverse) {
  obreclistcolumn_t* pColumn;

  if (m_pCurrentList == NULL) return;
  pColumn = FindListColumn(m_pCurrentList, FieldID);
  if (pColumn == NULL) return;

  m_pCurrentList->SortField   = FieldID;
  m_pCurrentList->SortSubItem = pColumn->SubItem;
  m_pCurrentList->SortReverse = Reverse;

  SortListPriv(FieldID);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SortList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void SortListPriv (FieldID);
 *
 *=========================================================================*/
void CObRecordListCtrl::SortListPriv (const obrecfieldid_t FieldID) {
  obreclistsort_t    SortData;
  obreclistcolumn_t* pColumn;

  if (m_pCurrentList == NULL) return;
  pColumn = FindListColumn(m_pCurrentList, FieldID);

  m_pCurrentList->SortField   = FieldID;
  m_pCurrentList->SortSubItem = pColumn->SubItem;

  SortData.FieldID  = m_pCurrentList->SortField;
  SortData.SubItem  = m_pCurrentList->SortSubItem;
  SortData.Reverse  = m_pCurrentList->SortReverse;
  SortData.ListType = m_pCurrentList->Type;

  if (pColumn == NULL || pColumn->CompareFunc == NULL) {

    if (m_pCurrentList->Type == OB_RECORDLIST_CUSTOM)
      SortItems(s_DefaultCustomRecListSort, (DWORD) (void *) &SortData);
    else
      SortItems(s_DefaultRecListSort, (DWORD) (void *) &SortData);
   }
  else
    SortItems(pColumn->CompareFunc, (DWORD) (void *) &SortData);

 }
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::SortListPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void UpdateCurrentList (void);
 *
 * Saves the current width/settings of the list to the list info object.
 *
 *=========================================================================*/
void CObRecordListCtrl::UpdateCurrentList (void) {
  obreclistcolumn_t* pColumn;
  dword		     Index;
  
	/* Ignore if nothing to update */
  if (m_pCurrentList == NULL) return;  
  
  for (Index = 0; Index < m_pCurrentList->NumColumns; ++Index) {
    pColumn = &m_pCurrentList->Columns[Index];
    if (!pColumn->Display || pColumn->ColumnIndex < 0) continue;

    pColumn->Width = GetColumnWidth(pColumn->ColumnIndex);
  }

  if (m_Options.SaveState) WriteListInfoRegistry(m_pCurrentList);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::UpdateCurrentList()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void UpdateRecord (ListIndex);
 *
 *=========================================================================*/
void CObRecordListCtrl::UpdateRecord (const int ListIndex) {
  CObRecord*        pRecord;
  obrlcustomdata_t* pCustomData;

  pCustomData = GetCustomData(ListIndex);

  if (pCustomData != NULL) {
    SetColumnTexts(ListIndex, pCustomData->pRecord, pCustomData->pSubrecords);
    return;
  }

  pRecord = GetRecord(ListIndex);
  if (pRecord == NULL) return;

  SetColumnTexts(ListIndex, pRecord, NULL);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::UpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - int UpdateRecord (pNewRecord, pOldRecord);
 *
 * Updates an existing record or adds a new one. Returns the updated list
 * index or -1 on any error.
 *
 *=========================================================================*/
int CObRecordListCtrl::UpdateRecord (CObRecord* pNewRecord, CObRecord* pOldRecord) {
  int ListIndex;

  ListIndex = FindRecord(pOldRecord);

  if (ListIndex < 0) {
    if (m_pCurrentFilter != NULL && !m_pCurrentFilter->CheckRecord(pNewRecord)) return (-1);
    return AddRecord(pNewRecord);
  }

  if (pNewRecord == NULL) {
    DeleteItem(ListIndex);
    return (-1);
  }

  SetItemData(ListIndex, pNewRecord);
  SetColumnTexts(ListIndex, pNewRecord, NULL);
  return (ListIndex);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::UpdateRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - bool RemoveItem (ListIndex);
 *
 *=========================================================================*/
bool CObRecordListCtrl::RemoveItem (const int ListIndex) { 
  obrlcustomdata_t* pCustomData;

  if (ListIndex < 0 || ListIndex >= GetItemCount()) return (false);

  pCustomData = GetCustomData(ListIndex);
  
  DeleteItem(ListIndex);

  if (pCustomData != NULL) m_CustomData.Delete(pCustomData);
  return (true);
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::RemoveItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnBeginDrag (pNMHDR, pResult);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnBeginDrag (NMHDR* pNMHDR, LRESULT* pResult) {
  NM_LISTVIEW*      pNMListView = (NM_LISTVIEW *)pNMHDR;
  obrlcustomdata_t* pCustomData;
  CObRecord*        pRecord;
  POINT		    DragPoint;
  POSITION	    SelPos;
  int		    Offset = 10;
  int		    ListIndex;
  *pResult = 0;

	/* Ignore if the dragging is disabled for the list */
  if (!m_EnableDrag || m_ActNormalList) return;

	/* Copy the records we wish to drag */
  m_DragRecords.Destroy();
  m_DragCustomData.Destroy();

	/* Get drag records */
  SelPos = GetFirstSelectedItemPosition();
  
  while (SelPos != NULL) {
    ListIndex   = GetNextSelectedItem(SelPos);
    pRecord     = GetRecord(ListIndex);
    pCustomData = GetCustomData(ListIndex);

    if (pRecord     != NULL && (m_DragType & OB_RECORDLIST_RECORD) != 0) m_DragRecords.Add(pRecord);
    if (pCustomData != NULL && (m_DragType & OB_RECORDLIST_CUSTOM) != 0) m_DragCustomData.Add(pCustomData);
  }

	/* Ignore if nothing to drag */
  if (m_DragRecords.GetSize() == 0 && m_DragCustomData.GetSize() == 0) return;


	/* Setup the dragging members */
  m_DragIndex  = pNMListView->iItem;
  DragPoint.x  = Offset;
  DragPoint.y  = Offset;
    
	/* Set the drag cursors */
  m_hGoodDropCursor = GetCursor();
  SetCursor(m_hBadDropCursor);

	/* Create the image for dragging */
  m_pDragImage = CreateDragImage(m_DragIndex, &DragPoint);
  if (m_pDragImage == NULL) return;   
  m_IsDragging    = true;
  m_LastDropValid = false;
  m_pLastDropWnd  = NULL;

	/* Change the cursor to the drag image
	  (still must perform DragMove() in OnMouseMove() to show it moving) */
  m_pDragImage->BeginDrag(0, CPoint(Offset, Offset));
  m_pDragImage->DragEnter(GetDesktopWindow(), pNMListView->ptAction);

	/* Cause this control to capture all the mouse messages */
  SetCapture();  
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnBeginDrag()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnLButtonUp (nFlags, Point);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnLButtonUp (UINT nFlags, CPoint Point) {

  	/* Ignore if not handling any dragging messages */
  if (!m_IsDragging) {
    CListCtrl::OnLButtonUp(nFlags, Point);
    return;
   }

	/* Release mouse capture, so that other controls can get control/messages */
  ReleaseCapture();

	/* Update the dragging state */
  m_IsDragging = false;

	/* End dragging image */
  m_pDragImage->DragLeave(GetDesktopWindow());
  m_pDragImage->EndDrag();

	/* Clean up the image list */
  delete m_pDragImage;
  m_pDragImage = NULL;

	/* Get the mouse point in screen coordinates */
  CPoint MousePt(Point); 
  ClientToScreen(&MousePt);
	
	/* Get the CWnd pointer of the window that is under the mouse cursor */
  CWnd* pDropWnd = WindowFromPoint(MousePt);
  if (pDropWnd == NULL) return;

	/* Drop records/custom data on the window */
  DropRecords(pDropWnd);
  m_DragRecords.Destroy();
  m_DragCustomData.Destroy();
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnLButtonUp()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnMouseMove (nFlags, Ppoint);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnMouseMove (UINT nFlags, CPoint Point) {
  obrldroprecords_t NotifyData;
  CWnd*		    pParentWnd = NULL;
  int		    Result = 0;

	/* Ignore if not handling any dragging messages */
  if (!m_IsDragging) {
    CListCtrl::OnMouseMove(nFlags, Point);
    return;
   }

	/* Get mouse coordinates in screen */
  CPoint MousePt(Point);
  ClientToScreen(&MousePt);

	/* Move the drag image to those coordinates */
  m_pDragImage->DragMove(MousePt); 
  m_pDragImage->DragShowNolock(false);	/* Smoother updates */

	/* Get the CWnd pointer of the window that is under the mouse cursor */
  CWnd* pDropWnd = WindowFromPoint(MousePt);

  if (pDropWnd == NULL) {
    m_pDragImage->DragShowNolock(true);
    return;
  }

  pDropWnd->ScreenToClient(&MousePt);
  if (pDropWnd == this) pDropWnd = NULL;

	/* Don't do anything if the window has not changed */
  if (m_pLastDropWnd == pDropWnd) {
    m_pDragImage->DragShowNolock(true);
    return;
  }

  m_pLastDropWnd = pDropWnd;

  if (pDropWnd != NULL) { 
    NotifyData.Notify.code     = ID_OBRECORDLIST_CHECKDROP;
    NotifyData.Notify.hwndFrom = pDropWnd->m_hWnd;
    NotifyData.Notify.idFrom   = pDropWnd->GetDlgCtrlID();
    NotifyData.pRecords        = &m_DragRecords;
    NotifyData.pCustomDatas    = &m_DragCustomData;

    pParentWnd = pDropWnd->GetParent();

    if (pParentWnd != NULL) {
      Result = pParentWnd->SendMessage(WM_NOTIFY, NotifyData.Notify.idFrom, (LPARAM) &NotifyData);
    }
  }
            
  if (Result == OBRL_DROPCHECK_OK) {
    m_LastDropValid = true;
    SetCursor(m_hGoodDropCursor); 
  }
  else {
    m_LastDropValid = false;
    SetCursor(m_hBadDropCursor);
  }

	/* Lock window updates */
  m_pDragImage->DragShowNolock(true);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnMouseMove()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Method - void DropRecords (pDropWnd);
 *
 * Used to drop dragged records between the current list and the given 
 * window.
 *
 *=========================================================================*/
void CObRecordListCtrl::DropRecords (CWnd* pDropWnd) {
  obrldroprecords_t NotifyData;
  CWnd*		    pParentWnd;
  int		    Result;
  
	/* Ignore if we are just dropping onto itself */
  if (pDropWnd == NULL || pDropWnd == this) return;
  if (m_ActNormalList) return;
  if (!m_LastDropValid) return;

  NotifyData.Notify.hwndFrom = pDropWnd->m_hWnd;
  NotifyData.Notify.idFrom   = pDropWnd->GetDlgCtrlID();
  NotifyData.pRecords        = &m_DragRecords;
  NotifyData.pCustomDatas    = &m_DragCustomData;
  NotifyData.Notify.code     = ID_OBRECORDLIST_DROP;
  
  pParentWnd = pDropWnd->GetParent();

  if (pParentWnd != NULL) {
    Result = pParentWnd->SendMessage(WM_NOTIFY, NotifyData.Notify.idFrom, (LPARAM) &NotifyData);
  }
  
}
/*===========================================================================
 *		End of Class Method CObRecordListCtrl::DropRecords()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnCaptureChanged ( pWnd);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnCaptureChanged (CWnd* pWnd) {

	/* TODO: Need an end drag method */
  if (m_IsDragging) {
    if (m_pDragImage != NULL) {
      delete m_pDragImage;
      m_pDragImage = NULL;
    }

    m_IsDragging = false;
  }

  CListCtrl::OnCaptureChanged(pWnd);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnCaptureChanged()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - UINT OnGetDlgCode ();
 *
 *=========================================================================*/
UINT CObRecordListCtrl::OnGetDlgCode() {

  return (CListCtrl::OnGetDlgCode() | DLGC_WANTCHARS );

  return CListCtrl::OnGetDlgCode();
 }
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnGetDlgCode()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnChar (nChar, nRepCnt, nFlags);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
  CWnd* pWnd = GetParent();

  if (pWnd != NULL) {
  /*
    NMCHAR Notify;

    Notify.ch           = nChar;
    Notify.dwItemNext   = 0;
    Notify.dwItemPrev   = 0;
    Notify.hdr.code     = ID_OBRECORDLIST_CHAR;
    Notify.hdr.hwndFrom = m_hWnd;
    Notify.hdr.idFrom   = GetDlgCtrlID();

    pWnd->SendMessage(WM_NOTIFY, Notify.hdr.idFrom, (LPARAM) &Notify);  //*/
  }

  CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnChar()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnKeyDown (nChar, nRepCnt, nFlags);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) {
  CWnd* pWnd = GetParent();

  if (pWnd != NULL) {
    obrlkeydown_t Notify;
    
    Notify.Alt   = (GetAsyncKeyState(VK_MENU)    & 0x8000) != 0;
    Notify.Ctrl  = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    Notify.Shift = (GetAsyncKeyState(VK_SHIFT)   & 0x8000) != 0;

    Notify.KeyDown.nVKey        = nChar;
    Notify.KeyDown.uFlags       = nFlags;
    Notify.KeyDown.hdr.code     = ID_OBRECORDLIST_KEYDOWN;
    Notify.KeyDown.hdr.hwndFrom = m_hWnd;
    Notify.KeyDown.hdr.idFrom   = GetDlgCtrlID();

    pWnd->SendMessage(WM_NOTIFY, Notify.KeyDown.hdr.idFrom, (LPARAM) &Notify); 
  }

  CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnKeyDown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void OnClose (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::OnClose (void) {
  UpdateCurrentList();
  CListCtrl::OnClose();
}


void CObRecordListCtrl::OnDestroy (void) {
  UpdateCurrentList();
  CListCtrl::OnDestroy();
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::OnKeyDown()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void CreateRegSectionName (pListInfo);
 *
 *=========================================================================*/
const char* CObRecordListCtrl::CreateRegSectionName (obreclistinfo_t* pListInfo) {
  static CSString s_Buffer;

	/* Create the registry section name to output to */
  if (pListInfo->pRecordType == NULL)
    s_Buffer.Format("%s\\%s\\List_\\", OBRL_REGKEY_ROOT, m_ListName);
  else
    s_Buffer.Format("%s\\%s\\List_%4.4s\\", OBRL_REGKEY_ROOT, m_ListName, pListInfo->pRecordType->Name);

  return (s_Buffer);
}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::CreateRegSectionName()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void ReadListInfoRegistry (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::ReadListInfoRegistry (void) {
  dword   Index;

  if (!m_Options.SaveState) return;

  for (Index = 0; Index < m_ListInfos.GetSize(); ++Index) {
    ReadListInfoRegistry(m_ListInfos.GetAt(Index));
  }

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::ReadListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void ReadListInfoRegistry (pListInfo);
 *
 *=========================================================================*/
void CObRecordListCtrl::ReadListInfoRegistry (obreclistinfo_t* pListInfo) {
  obreclistcolumn_t* pColumn;
  CString            Section;
  CString            Section1;
  dword              Index;
  HKEY               hKey;
  long               Result;
  int                FieldID;

  if (pListInfo == NULL || !m_Options.SaveState) return;
  Section = CreateRegSectionName(pListInfo);

  pListInfo->SortField   = AfxGetApp()->GetProfileInt(Section, "SortField", pListInfo->SortField);
  pListInfo->SortReverse = (AfxGetApp()->GetProfileInt(Section, "SortReverse", pListInfo->SortReverse) != 0);
  pListInfo->SortSubItem = AfxGetApp()->GetProfileInt(Section, "SortSubItem", pListInfo->SortSubItem);
  //pListInfo->Type        = AfxGetApp()->GetProfileInt(Section, "Type", pListInfo->Type);
  
  for (Index = 0; Index < OB_RECLIST_MAXCOLS; ++Index) {
    Section1.Format("%s%sColumn%d\\", OBEDIT_REGISTRY_BASE, Section, Index);

		/* See if the key exists */
    Result = RegOpenKeyEx(HKEY_CURRENT_USER, Section1, 0, KEY_READ, &hKey);
    if (Result != ERROR_SUCCESS) continue;
    RegCloseKey(hKey);

    Section1.Format("%s\\Column%d\\", Section, Index);

    FieldID = AfxGetApp()->GetProfileInt(Section1, "FieldID", -1);
    if (FieldID < 0) continue;

    pColumn = FindListColumn(pListInfo, FieldID);
    if (pColumn == NULL) continue;

    ReadListInfoRegistry(Section1, pColumn);
  }

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::ReadListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void ReadListInfoRegistry (pSection, pListInfo);
 *
 *=========================================================================*/
void CObRecordListCtrl::ReadListInfoRegistry (const char* pSection, obreclistcolumn_t* pColumn) {
  CString Buffer;

  pColumn->Display     = (AfxGetApp()->GetProfileInt   (pSection, "Display",     pColumn->Display) != 0);

  Buffer               = AfxGetApp()->GetProfileString (pSection, "Title",       pColumn->Title);
  strnncpy(pColumn->Title, Buffer, 60);

  pColumn->FieldID     = AfxGetApp()->GetProfileInt    (pSection, "FieldID",     pColumn->FieldID);
  pColumn->Width       = AfxGetApp()->GetProfileInt    (pSection, "Width",       pColumn->Width);
  pColumn->Format      = AfxGetApp()->GetProfileInt    (pSection, "Format",      pColumn->Format);
  pColumn->SubItem     = AfxGetApp()->GetProfileInt    (pSection, "SubItem",     pColumn->SubItem);
  pColumn->ColumnIndex = AfxGetApp()->GetProfileInt    (pSection, "ColumnIndex", pColumn->ColumnIndex);

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::ReadListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void WriteListInfoRegistry (void);
 *
 *=========================================================================*/
void CObRecordListCtrl::WriteListInfoRegistry (void) {
  dword   Index;

  if (!m_Options.SaveState) return;

  for (Index = 0; Index < m_ListInfos.GetSize(); ++Index) {
    WriteListInfoRegistry(m_ListInfos.GetAt(Index));
  }

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::WriteListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void WriteListInfoRegistry (pListInfo);
 *
 *=========================================================================*/
void CObRecordListCtrl::WriteListInfoRegistry (obreclistinfo_t* pListInfo) {
  CString Section;
  CString Section1;
  dword   Index;

  if (pListInfo == NULL || !m_Options.SaveState) return;
  Section = CreateRegSectionName(pListInfo);

  if (pListInfo->pRecordType == NULL)
    AfxGetApp()->WriteProfileString(Section, "RecordType", "");
  else {
    CSString Buffer;
    Buffer.Copy(pListInfo->pRecordType->Name, 4);
    AfxGetApp()->WriteProfileString(Section, "RecordType", Buffer.c_str());
  }

  AfxGetApp()->WriteProfileInt(Section, "SortField", pListInfo->SortField);
  AfxGetApp()->WriteProfileInt(Section, "SortReverse", pListInfo->SortReverse);
  AfxGetApp()->WriteProfileInt(Section, "SortSubItem", pListInfo->SortSubItem);
  AfxGetApp()->WriteProfileInt(Section, "Type", pListInfo->Type);
  
  for (Index = 0; Index < pListInfo->NumColumns; ++Index) {
    Section1.Format("%s\\Column%d\\", Section, Index);
    WriteListInfoRegistry(Section1, &pListInfo->Columns[Index]);
  }

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::WriteListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Class CObRecordListCtrl Event - void WriteListInfoRegistry (pSection, pListInfo);
 *
 *=========================================================================*/
void CObRecordListCtrl::WriteListInfoRegistry (const char* pSection, obreclistcolumn_t* pColumn) {

  AfxGetApp()->WriteProfileInt    (pSection, "Display",     pColumn->Display);
  AfxGetApp()->WriteProfileString (pSection, "Title",       pColumn->Title);
  AfxGetApp()->WriteProfileInt    (pSection, "FieldID",     pColumn->FieldID);
  AfxGetApp()->WriteProfileInt    (pSection, "Width",       pColumn->Width);
  AfxGetApp()->WriteProfileInt    (pSection, "Format",      pColumn->Format);
  AfxGetApp()->WriteProfileInt    (pSection, "SubItem",     pColumn->SubItem);
  AfxGetApp()->WriteProfileInt    (pSection, "ColumnIndex", pColumn->ColumnIndex);

}
/*===========================================================================
 *		End of Class Event CObRecordListCtrl::WriteListInfoRegistry()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obreclistcolumn_t* FindListColumnBySubItem (pListInfo, FieldID);
 *
 * Find the column with the given SubItem in the list data. Returns
 * NULL if not found.
 *
 *=========================================================================*/
obreclistcolumn_t* FindListColumnBySubItem (obreclistinfo_t* pListInfo, const int SubItem) {
  dword Index;

  for (Index = 0; Index < pListInfo->NumColumns; ++Index) {
    if (pListInfo->Columns[Index].SubItem == SubItem) return (&pListInfo->Columns[Index]);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Function FindListColumnBySubItem()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obreclistcolumn_t* FindListColumn (pListInfo, FieldID);
 *
 * Find the column with the given FieldID in the list data. Returns
 * NULL if not found.
 *
 *=========================================================================*/
obreclistcolumn_t* FindListColumn (obreclistinfo_t* pListInfo, const obrecfieldid_t FieldID) {
  dword Index;

  for (Index = 0; Index < pListInfo->NumColumns; ++Index) {
    if (pListInfo->Columns[Index].FieldID == FieldID) return (&pListInfo->Columns[Index]);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Function FindListColumn()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const obrecfield_t* FindObField (pFields, FieldID);
 *
 *=========================================================================*/
const obrecfield_t* FindObField (const obrecfield_t* pFields, const obrecfieldid_t FieldID) {
  dword Index;

  if (pFields == NULL) return (NULL);

  for (Index = 0; pFields[Index].FieldID != OB_FIELD_NONE; ++Index) { 
    if (pFields[Index].FieldID == FieldID) return &pFields[Index];
   }

	/* No match */
  return (NULL);
 }
/*===========================================================================
 *		End of Function obrecfield_t* FindObField()
 *=========================================================================*/


