/*===========================================================================
 *
 * File:	Obfields.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	May 9, 2006
 *
 * Basic definitions for field IDs.
 *
 *=========================================================================*/
#ifndef __OBFIELDS_H
#define __OBFIELDS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../common/textutils.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* The basic field ID type */
  typedef long obfieldid_t;
  typedef obfieldid_t obrecfieldid_t;

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Default format strings */
  #define OB_FORMATSTR_WEIGHT "%g"

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Field Types
 *
 *=========================================================================*/

  #define OB_FIELD_UNKNOWN		-1
  #define OB_FIELD_NONE			0
  #define OB_FIELD_RECORDTYPE		1
  #define OB_FIELD_FORMID		2
  #define OB_FIELD_EDITORID		3
  #define OB_FIELD_ITEMNAME		4
  #define OB_FIELD_FULLNAME		4
  #define OB_FIELD_VALUE		5
  #define OB_FIELD_WEIGHT		6
  #define OB_FIELD_TYPE			7
  #define OB_FIELD_BIPED		8
  #define OB_FIELD_ICON			9
  #define OB_FIELD_ICON2		10
  #define OB_FIELD_MODEL		11
  #define OB_FIELD_MODEL2		12
  #define OB_FIELD_MODEL3		13
  #define OB_FIELD_MODEL4		14
  #define OB_FIELD_ARMOR		15
  #define OB_FIELD_DAMAGE		16
  #define OB_FIELD_SPEED		17
  #define OB_FIELD_REACH		18
  #define OB_FIELD_HEALTH		19
  #define OB_FIELD_FLAGS		20
  #define OB_FIELD_AUTHOR		21
  #define OB_FIELD_SUMMARY		22
  #define OB_FIELD_VERSION		23
  #define OB_FIELD_FILETYPE		24
  #define OB_FIELD_ENCHANTMENT		25
  #define OB_FIELD_ENCHANTPOINTS	26
  #define OB_FIELD_QUALITY		27
  #define OB_FIELD_IGNORERESIST		28
  #define OB_FIELD_HIDEAMULET		29
  #define OB_FIELD_HIDERINGS		30
  #define OB_FIELD_TEACHES		31
  #define OB_FIELD_SCROLL		32
  #define OB_FIELD_NOTAKE		33
  #define OB_FIELD_TEXT			34
  #define OB_FIELD_CHARGE		35
  #define OB_FIELD_COST			36
  #define OB_FIELD_AUTOCALC		37
  #define OB_FIELD_FOOD			38
  #define OB_FIELD_FOODITEM		38
  #define OB_FIELD_SCRIPT		39
  #define OB_FIELD_CHANCENONE		40
  #define OB_FIELD_CALCULATEALL		41
  #define OB_FIELD_CALCULATEEACH	42
  #define OB_FIELD_ITEMLIST		43
  #define OB_FIELD_SCRIPTTEXT		44
  #define OB_FIELD_USES			45
  #define OB_FIELD_LEVEL		46
  #define OB_FIELD_PLAYERSTART		47
  #define OB_FIELD_IGNORELOS		48
  #define OB_FIELD_ALWAYSAPPLY		49
  #define OB_FIELD_ABSORBREFLECT	50
  #define OB_FIELD_SILENCEIMMUNE	51
  #define OB_FIELD_RECORDCOUNT		52
  #define OB_FIELD_ITEMCOUNT		53
  #define OB_FIELD_EFFECTCOUNT		54
  #define OB_FIELD_USERDATA		55
  #define OB_FIELD_EFFECTID		56
  #define OB_FIELD_EFFECTNAME		57
  #define OB_FIELD_MAGNITUDE		58
  #define OB_FIELD_AREA			59
  #define OB_FIELD_DURATION		60
  #define OB_FIELD_RANGE		61
  #define OB_FIELD_SCHOOL		62
  #define OB_FIELD_ACTORVALUE		63
  #define OB_FIELD_EFFECTDESC		64
  #define OB_FIELD_SCRIPTSCHOOL		65
  #define OB_FIELD_VISUALNAME		66
  #define OB_FIELD_HOSTILE		67
  #define OB_FIELD_DATANAME		68
  #define OB_FIELD_NAME2		69
  #define OB_FIELD_SCRIPTID		70
  #define OB_FIELD_PLAYABLE		71
  #define OB_FIELD_TIME			72
  #define OB_FIELD_RADIUS		73
  #define OB_FIELD_FOV			74
  #define OB_FIELD_CARRIED		75
  #define OB_FIELD_COLOR		76
  #define OB_FIELD_FADE			77
  #define OB_FIELD_FALLOFF		78
  #define OB_FIELD_DYNAMIC		79
  #define OB_FIELD_NEGATIVE		80
  #define OB_FIELD_DEFAULTOFF		81
  #define OB_FIELD_SPOTLIGHT		82
  #define OB_FIELD_SPOTSHADOW		83
  #define OB_FIELD_SOUNDID		84
  #define OB_FIELD_SOUND		85
  #define OB_FIELD_ENCHANTMENTID	86
  #define OB_FIELD_LOCATIONX		87
  #define OB_FIELD_LOCATIONY		88
  #define OB_FIELD_LOCATIONZ		89
  #define OB_FIELD_ANGLEX		90
  #define OB_FIELD_ANGLEY		91
  #define OB_FIELD_ANGLEZ		92
  #define OB_FIELD_TELEPORTFORMID	93
  #define OB_FIELD_TELEPORTNAME		94
  #define OB_FIELD_TELEPORTLOCX		95
  #define OB_FIELD_TELEPORTLOCY		96
  #define OB_FIELD_TELEPORTLOCZ		97
  #define OB_FIELD_TELEPORTANGLEX	98
  #define OB_FIELD_TELEPORTANGLEY	99
  #define OB_FIELD_TELEPORTANGLEZ	100
  #define OB_FIELD_WORLDSPACE		101
  #define OB_FIELD_MARKERTYPE		102
  #define OB_FIELD_MARKERTYPEID		103
  #define OB_FIELD_BASEFORMID		104
  #define OB_FIELD_BASEEDITORID		105
  #define OB_FIELD_BASENAME		106
  #define OB_FIELD_LINECOUNT		107
  #define OB_FIELD_SIZE			108
  #define OB_FIELD_REALARMOR		109
  #define OB_FIELD_QUESTITEM		110
  #define OB_FIELD_DANGEROUS		111
  #define OB_FIELD_IGNORED		112
  #define OB_FIELD_DELETED		113
  #define OB_FIELD_USEALLSPELLS		114
  #define OB_FIELD_TEMPLATE		115
  #define OB_FIELD_TEMPLATEID		116
  #define OB_FIELD_CAPACITY		117
  #define OB_FIELD_SOUL			118
  #define OB_FIELD_RESPAWNS		119
  #define OB_FIELD_OPENSOUND		120
  #define OB_FIELD_OPENSOUNDID		121
  #define OB_FIELD_CLOSESOUND		122
  #define OB_FIELD_CLOSESOUNDID		123
  #define OB_FIELD_MINATTENUATION       125
  #define OB_FIELD_MAXATTENUATION       126
  #define OB_FIELD_STATICATTENUATION    127
  #define OB_FIELD_FREQADJUSTMENT       128
  #define OB_FIELD_STARTTIME            129
  #define OB_FIELD_STOPTIME             130
  #define OB_FIELD_RANDOMFREQSHIFT      131
  #define OB_FIELD_RANDOMPLAY           132
  #define OB_FIELD_RANDOMLOCATION       133
  #define OB_FIELD_LOOP                 134
  #define OB_FIELD_MENUSOUND            135
  #define OB_FIELD_IGNOREENVIRONMENT    136
  #define OB_FIELD_2DSOUND              137
  #define OB_FIELD_360LFE               138
  #define OB_FIELD_INGREDIANT		139
  #define OB_FIELD_INGREDIANTID		140
  #define OB_FIELD_SPRING		141
  #define OB_FIELD_SUMMER		142
  #define OB_FIELD_FALL			143
  #define OB_FIELD_WINTER		144
  #define OB_FIELD_SOUNDFILE		145
  #define OB_FIELD_REDCOLOR		146
  #define OB_FIELD_GREENCOLOR		147
  #define OB_FIELD_BLUECOLOR		148
/*===========================================================================
 *		End of Field Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Prototypes
 *
 *=========================================================================*/

  bool          GetObFieldValue  (int& Value, const SSCHAR* pString);
  const SSCHAR* GetObFieldString (const int Value);

  bool ObFieldConvertLong    (const SSCHAR* pString, long&  Value);
  bool ObFieldConvertInt     (const SSCHAR* pString, int&   Value);
  bool ObFieldConvertDword   (const SSCHAR* pString, dword& Value);
  bool ObFieldConvertShort   (const SSCHAR* pString, short& Value);
  bool ObFieldConvertWord    (const SSCHAR* pString, word&  Value);
  bool ObFieldConvertByte    (const SSCHAR* pString, byte&  Value);
  bool ObFieldConvertFloat   (const SSCHAR* pString, float& Value);
  bool ObFieldConvertBoolean (const SSCHAR* pString, bool&  Value);
  bool ObFieldConvertColor   (const SSCHAR* pString, obrgba_t& Value);

/*===========================================================================
 *		End of Function Prototypes
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obfields.H
 *=========================================================================*/
