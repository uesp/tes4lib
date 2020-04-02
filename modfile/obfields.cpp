/*===========================================================================
 *
 * File:	Obfields.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	July 29, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obfields.h"
#include "math.h"
#include "ctype.h"
#include "limits.h"


/*===========================================================================
 *
 * Begin Field Text Strings
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObFields)
	ADD_STRINGVALUE( OB_FIELD_UNKNOWN,		"Unknown")
	ADD_STRINGVALUE( OB_FIELD_NONE,			"None")
	ADD_STRINGVALUE( OB_FIELD_RECORDTYPE,		"RecordType")
	ADD_STRINGVALUE( OB_FIELD_FORMID,		"FormID")
	ADD_STRINGVALUE( OB_FIELD_EDITORID,		"EditorID")
	ADD_STRINGVALUE( OB_FIELD_ITEMNAME,		"ItemName")
	ADD_STRINGVALUE( OB_FIELD_FULLNAME,		"FullName")
	ADD_STRINGVALUE( OB_FIELD_VALUE,		"Value")
	ADD_STRINGVALUE( OB_FIELD_WEIGHT,		"Weight")
	ADD_STRINGVALUE( OB_FIELD_TYPE,			"Type")
	ADD_STRINGVALUE( OB_FIELD_BIPED,		"Biped")
	ADD_STRINGVALUE( OB_FIELD_ICON,			"Icon")
	ADD_STRINGVALUE( OB_FIELD_ICON2,		"Icon2")
	ADD_STRINGVALUE( OB_FIELD_MODEL,		"Model")
	ADD_STRINGVALUE( OB_FIELD_MODEL2,		"Model2")
	ADD_STRINGVALUE( OB_FIELD_MODEL3,		"Model3")
	ADD_STRINGVALUE( OB_FIELD_MODEL4,		"Model4")
	ADD_STRINGVALUE( OB_FIELD_ARMOR,		"Armor")
	ADD_STRINGVALUE( OB_FIELD_DAMAGE,		"Damage")
	ADD_STRINGVALUE( OB_FIELD_SPEED,		"Speed")
	ADD_STRINGVALUE( OB_FIELD_REACH,		"Reach")
	ADD_STRINGVALUE( OB_FIELD_HEALTH,		"Health")
	ADD_STRINGVALUE( OB_FIELD_FLAGS,		"Flags")
	ADD_STRINGVALUE( OB_FIELD_AUTHOR,		"Author")
	ADD_STRINGVALUE( OB_FIELD_SUMMARY,		"Summary")
	ADD_STRINGVALUE( OB_FIELD_VERSION,		"Version")
	ADD_STRINGVALUE( OB_FIELD_FILETYPE,		"FileType")
	ADD_STRINGVALUE( OB_FIELD_ENCHANTMENT,		"Enchantment")
	ADD_STRINGVALUE( OB_FIELD_ENCHANTPOINTS,	"EnchantPoints")
	ADD_STRINGVALUE( OB_FIELD_QUALITY,		"Quality")
	ADD_STRINGVALUE( OB_FIELD_IGNORERESIST,		"IgnoreResist")
	ADD_STRINGVALUE( OB_FIELD_HIDEAMULET,		"HideAmulet")
	ADD_STRINGVALUE( OB_FIELD_HIDERINGS,		"HideRings")
	ADD_STRINGVALUE( OB_FIELD_TEACHES,		"Teaches")
	ADD_STRINGVALUE( OB_FIELD_SCROLL,		"Scroll")
	ADD_STRINGVALUE( OB_FIELD_NOTAKE,		"NoTake")
	ADD_STRINGVALUE( OB_FIELD_TEXT,			"Text")
	ADD_STRINGVALUE( OB_FIELD_CHARGE,		"Charge")
	ADD_STRINGVALUE( OB_FIELD_COST,			"Cost")
	ADD_STRINGVALUE( OB_FIELD_AUTOCALC,		"AutoCalc")
	ADD_STRINGVALUE( OB_FIELD_FOOD,			"Food")
	ADD_STRINGVALUE( OB_FIELD_SCRIPT,		"Script")
	ADD_STRINGVALUE( OB_FIELD_CHANCENONE,		"ChanceNone")
	ADD_STRINGVALUE( OB_FIELD_CALCULATEALL,		"CalculateAll")
	ADD_STRINGVALUE( OB_FIELD_CALCULATEEACH,	"CalculateEach")
	ADD_STRINGVALUE( OB_FIELD_ITEMLIST,		"ItemList")
	ADD_STRINGVALUE( OB_FIELD_SCRIPTTEXT,		"ScriptText")
	ADD_STRINGVALUE( OB_FIELD_USES,			"Uses")
	ADD_STRINGVALUE( OB_FIELD_LEVEL,		"Level")
	ADD_STRINGVALUE( OB_FIELD_PLAYERSTART,		"PlayerStart")
	ADD_STRINGVALUE( OB_FIELD_IGNORELOS,		"IgnoreLOS")
	ADD_STRINGVALUE( OB_FIELD_ALWAYSAPPLY,		"AlwaysApply")
	ADD_STRINGVALUE( OB_FIELD_ABSORBREFLECT,	"AbsorbReflect")
	ADD_STRINGVALUE( OB_FIELD_SILENCEIMMUNE,	"SilenceImmune")
	ADD_STRINGVALUE( OB_FIELD_RECORDCOUNT,		"RecordCount")
	ADD_STRINGVALUE( OB_FIELD_ITEMCOUNT,		"ItemCount")
	ADD_STRINGVALUE( OB_FIELD_EFFECTCOUNT,		"EffectCount")
	ADD_STRINGVALUE( OB_FIELD_USERDATA,		"UserData")
	ADD_STRINGVALUE( OB_FIELD_EFFECTID,		"EffectID")
	ADD_STRINGVALUE( OB_FIELD_EFFECTNAME,		"EffectName")
	ADD_STRINGVALUE( OB_FIELD_MAGNITUDE,		"Magnitude")
	ADD_STRINGVALUE( OB_FIELD_AREA,			"Area")
	ADD_STRINGVALUE( OB_FIELD_DURATION,		"Duration")
	ADD_STRINGVALUE( OB_FIELD_RANGE,		"Range")
	ADD_STRINGVALUE( OB_FIELD_SCHOOL,		"School")
	ADD_STRINGVALUE( OB_FIELD_ACTORVALUE,		"ActorValue")
	ADD_STRINGVALUE( OB_FIELD_EFFECTDESC,		"EffectDesc")
	ADD_STRINGVALUE( OB_FIELD_SCRIPTSCHOOL,		"ScriptSchool")
	ADD_STRINGVALUE( OB_FIELD_VISUALNAME,		"VisualName")
	ADD_STRINGVALUE( OB_FIELD_HOSTILE,		"Hostile")
	ADD_STRINGVALUE( OB_FIELD_DATANAME,		"DataName")
	ADD_STRINGVALUE( OB_FIELD_NAME2,		"Name2")
	ADD_STRINGVALUE( OB_FIELD_SCRIPTID,		"ScriptID")
	ADD_STRINGVALUE( OB_FIELD_PLAYABLE,		"Playable")
	ADD_STRINGVALUE( OB_FIELD_TIME,			"Time")
	ADD_STRINGVALUE( OB_FIELD_RADIUS,		"Radius")
	ADD_STRINGVALUE( OB_FIELD_FOV,			"FOV")
	ADD_STRINGVALUE( OB_FIELD_CARRIED,		"Carried")
	ADD_STRINGVALUE( OB_FIELD_COLOR,		"Color")
	ADD_STRINGVALUE( OB_FIELD_FADE,			"Fade")
	ADD_STRINGVALUE( OB_FIELD_FALLOFF,		"Falloff")
	ADD_STRINGVALUE( OB_FIELD_DYNAMIC,		"Dynamic")
	ADD_STRINGVALUE( OB_FIELD_NEGATIVE,		"Negative")
	ADD_STRINGVALUE( OB_FIELD_DEFAULTOFF,		"DefaultOff")
	ADD_STRINGVALUE( OB_FIELD_SPOTLIGHT,		"SpotLight")
	ADD_STRINGVALUE( OB_FIELD_SPOTSHADOW,		"SpotShadow")
	ADD_STRINGVALUE( OB_FIELD_SOUNDID,		"SoundID")
	ADD_STRINGVALUE( OB_FIELD_SOUND,		"Sound")
	ADD_STRINGVALUE( OB_FIELD_ENCHANTMENTID,	"EnchantmentID")
	ADD_STRINGVALUE( OB_FIELD_USEALLSPELLS,		"UseAllSpells")
	ADD_STRINGVALUE( OB_FIELD_TEMPLATE,		"Template")
	ADD_STRINGVALUE( OB_FIELD_TEMPLATEID,		"TemplateID")
	ADD_STRINGVALUE( OB_FIELD_CAPACITY,		"Capacity")
	ADD_STRINGVALUE( OB_FIELD_SOUL,			"Soul")

	ADD_STRINGVALUE( OB_FIELD_LOCATIONX,		"LocationX")
	ADD_STRINGVALUE( OB_FIELD_LOCATIONY,		"LocationY")
	ADD_STRINGVALUE( OB_FIELD_LOCATIONZ,		"LocationZ")
	ADD_STRINGVALUE( OB_FIELD_ANGLEX,		"AngleX")
	ADD_STRINGVALUE( OB_FIELD_ANGLEY,		"AngleY")
	ADD_STRINGVALUE( OB_FIELD_ANGLEZ,		"AngleZ")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTFORMID,	"TeleportFormID")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTNAME,		"TeleportName")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTLOCX,		"TeleportLocX")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTLOCY,		"TeleportLocY")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTLOCZ,		"TeleportLocZ")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTANGLEX,	"TeleportAngleX")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTANGLEY,	"TeleportAngleY")
	ADD_STRINGVALUE( OB_FIELD_TELEPORTANGLEZ,	"TeleportAngleZ")
	ADD_STRINGVALUE( OB_FIELD_WORLDSPACE,		"WorldSpace")
	ADD_STRINGVALUE( OB_FIELD_MARKERTYPE,		"MarkerType")
	ADD_STRINGVALUE( OB_FIELD_MARKERTYPEID,		"MarkerTypeID")
	ADD_STRINGVALUE( OB_FIELD_BASEFORMID,		"BaseFormID")
	ADD_STRINGVALUE( OB_FIELD_BASEEDITORID,		"BaseEditorID")
	ADD_STRINGVALUE( OB_FIELD_BASENAME,		"BaseName")
	ADD_STRINGVALUE( OB_FIELD_RESPAWNS,		"Respawns")
	ADD_STRINGVALUE( OB_FIELD_OPENSOUND,		"OpenSound")
	ADD_STRINGVALUE( OB_FIELD_OPENSOUNDID,		"OpenSoundID")
	ADD_STRINGVALUE( OB_FIELD_CLOSESOUND,		"CloseSound")
	ADD_STRINGVALUE( OB_FIELD_CLOSESOUNDID,		"CloseSoundID")

	ADD_STRINGVALUE( OB_FIELD_LINECOUNT,		"LineCount")
	ADD_STRINGVALUE( OB_FIELD_SIZE,			"Size")
	ADD_STRINGVALUE( OB_FIELD_REALARMOR,		"RealArmor")
	ADD_STRINGVALUE( OB_FIELD_QUESTITEM,		"QuestItem")
	ADD_STRINGVALUE( OB_FIELD_DANGEROUS,		"Dangerous")
	ADD_STRINGVALUE( OB_FIELD_IGNORED,		"Ignored")
	ADD_STRINGVALUE( OB_FIELD_DELETED,		"Deleted")

	ADD_STRINGVALUE( OB_FIELD_MINATTENUATION,       "MinAttenuation")
	ADD_STRINGVALUE( OB_FIELD_MAXATTENUATION,       "MaxAttenuation")
	ADD_STRINGVALUE( OB_FIELD_STATICATTENUATION,    "StaticAttentuation")
	ADD_STRINGVALUE( OB_FIELD_FREQADJUSTMENT,       "FreqAdjustment")
	ADD_STRINGVALUE( OB_FIELD_STARTTIME,            "StartTime")
	ADD_STRINGVALUE( OB_FIELD_STOPTIME,             "StopTime")
	ADD_STRINGVALUE( OB_FIELD_RANDOMFREQSHIFT,      "RandomFreqShift")
	ADD_STRINGVALUE( OB_FIELD_RANDOMPLAY,           "RandomPlay")
	ADD_STRINGVALUE( OB_FIELD_RANDOMLOCATION,       "RandomLocation")
	ADD_STRINGVALUE( OB_FIELD_LOOP,                 "Loop")
	ADD_STRINGVALUE( OB_FIELD_MENUSOUND,            "MenuSound")
	ADD_STRINGVALUE( OB_FIELD_IGNOREENVIRONMENT,    "IgnoreEnvironment")
	ADD_STRINGVALUE( OB_FIELD_2DSOUND,              "2DSound")
	ADD_STRINGVALUE( OB_FIELD_360LFE,               "360LFE")
	ADD_STRINGVALUE( OB_FIELD_INGREDIANT,           "Ingrediant")
	ADD_STRINGVALUE( OB_FIELD_INGREDIANTID,         "IngrediantID")
	ADD_STRINGVALUE( OB_FIELD_SPRING,               "Spring")
	ADD_STRINGVALUE( OB_FIELD_SUMMER,               "Summer")
	ADD_STRINGVALUE( OB_FIELD_FALL,                 "Fall")
	ADD_STRINGVALUE( OB_FIELD_WINTER,               "Winter")
	ADD_STRINGVALUE( OB_FIELD_SOUNDFILE,            "SoundFile")
	ADD_STRINGVALUE( OB_FIELD_REDCOLOR,             "RedColor")
	ADD_STRINGVALUE( OB_FIELD_GREENCOLOR,           "GreenColor")
	ADD_STRINGVALUE( OB_FIELD_BLUECOLOR,            "BlueColor")
	
	ADD_STRINGVALUE( OB_FIELD_RECORDTYPE,		"Name")
	ADD_STRINGVALUE( OB_FIELD_RECORDTYPE,		"Kind")
	
END_STRINGVALUE()
/*===========================================================================
 *		End of Field Text Strings
 *=========================================================================*/


/*===========================================================================
 *
 * Get String from a Value Functions
 *
 *=========================================================================*/
const SSCHAR* GetObFieldString (const int Value) { return FindStringValue(Value, s_ObFields); }
/*===========================================================================
 *		End of Get String Functions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Get a Value from a String
 *
 *=========================================================================*/
bool GetObFieldValue (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObFields); }
/*===========================================================================
 *		End of Get a Value from a String
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObFieldConvertInt (pString, Value);
 *
 * Attempts to convert the given value to an integer value. Returns false
 * on any error.
 *
 *=========================================================================*/
bool ObFieldConvertInt (const SSCHAR* pString, int& Value) {
  SSCHAR* pError;

  Value = strtol(pString, &pError, 0);

  if (!isspace(*pError) && *pError != NULL_CHAR) {
    AddObGeneralError("The string '%s' is not a valid integer value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertLong (const SSCHAR* pString, long& Value) {
  SSCHAR* pError;

  Value = strtol(pString, &pError, 0);

  if (!isspace(*pError) && *pError != NULL_CHAR) {
    AddObGeneralError("The string '%s' is not a valid integer value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertDword (const SSCHAR* pString, dword& Value) {
  SSCHAR* pError;

  Value = strtoul(pString, &pError, 0);

  if (!isspace(*pError) && *pError != NULL_CHAR) {
    AddObGeneralError("The string '%s' is not a valid unsigned integer value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertShort (const SSCHAR* pString, short& Value) {
  SSCHAR* pError;
  long    lValue;

  lValue = strtol(pString, &pError, 0);
  Value  = (short) lValue;

  if (!isspace(*pError) && *pError != NULL_CHAR || lValue != (long) Value) {
    AddObGeneralError("The string '%s' is not a valid short value!", pString);
    return (false);
  }

  
  return (true);
}


bool ObFieldConvertWord (const SSCHAR* pString, word& Value) {
  SSCHAR* pError;
  dword   lValue;

  lValue = strtoul(pString, &pError, 0);
  Value  = (word) lValue;

  if (!isspace(*pError) && *pError != NULL_CHAR || lValue != (dword) Value) {
    AddObGeneralError("The string '%s' is not a valid unsigned short value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertByte (const SSCHAR* pString, byte& Value) {
  SSCHAR* pError;
  dword   lValue;

  lValue = strtoul(pString, &pError, 0);
  Value  = (byte) lValue;

  if (!isspace(*pError) && *pError != NULL_CHAR || lValue != (dword) Value) {
    AddObGeneralError("The string '%s' is not a valid byte value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertFloat (const SSCHAR* pString, float& Value) {
  SSCHAR* pError;
  double  dValue;

  dValue = strtod(pString, &pError);
  Value  = (float) dValue;

  if (!isspace(*pError) && *pError != NULL_CHAR) {
    AddObGeneralError("The string '%s' is not a valid float value!", pString);
    return (false);
  }
  else if (dValue == HUGE_VAL || dValue == -HUGE_VAL) {
    AddObGeneralError("The string '%s' would result in a float overflow!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertBoolean (const SSCHAR* pString, bool& Value) {

  if (stricmp(pString, "true") == 0) {
    Value = true;
  }
  else if (stricmp(pString, "false") == 0) {
    Value = false;
  }
  else {
    AddObGeneralError("The string '%s' is not a valid boolean value!", pString);
    return (false);
  }

  return (true);
}


bool ObFieldConvertColor (const SSCHAR* pString, obrgba_t& Value) {
  SSCHAR* pError;
  dword   lValue;

  lValue = strtoul(pString, &pError, 16);
  Value.A = lValue >> 24;
  Value.B = (lValue >> 16) & 0xff;
  Value.G = (lValue >>  8) & 0xff;
  Value.R = lValue & 0xff;

  if (!isspace(*pError) && *pError != NULL_CHAR) {
    AddObGeneralError("The string '%s' is not a valid color value!", pString);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObFieldConvertInt()
 *=========================================================================*/
