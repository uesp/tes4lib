/*===========================================================================
 *
 * File:	Obmoddefs.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 17, 2006
 *
 * Common definitions used for mod files.
 *
 *=========================================================================*/
#ifndef __OBMODDEFS_H
#define __OBMODDEFS_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../common/obfile.h"
  #include "../common/oblogfile.h"
  #include "../common/textutils.h"
  #include "../common/obcallback.h"
  #include "../common/obarray.h"
  #include "../common/obptrarray.h"
  #include "../common/csvfile.h"
  #include "obfields.h"
  #include "obrectype.h"
  #include "../common/obtime.h"
  #include "compiler/obscriptfunctions.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin FormID Definitions
 *
 *=========================================================================*/

	/* Invalid/NULL form ID definition */
  #define OB_FORMID_NULL 0

  	/* Maximum allowed form id */
  #define MAX_OBFORMID	0x00ffffff
  #define OB_FORMID_MAX MAX_OBFORMID

	/* Get a modindex from a formid */
  #define OB_GETMODINDEX(FormID) ((((dword)FormID) >> 24) & 0xff) 

	/* Make a new formid from a formid and new modindex */
  #define OB_MAKEFORMID(FormID, ModIndex) (( ((dword)(FormID)) & 0x00ffffff) | (((dword)(ModIndex)) << 24) )

  #define OB_MODINDEX_MAX 255
  #define OB_MODINDEX_MIN 0

	/* Special formids */
  #define OB_PLAYERREF_FORMID 0x14
  #define OB_PLAYER_FORMID    0x7

/*===========================================================================
 *		End of FormID Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Type Definitions
 *
 *=========================================================================*/

	/* Used to create simple runtime type checking for class casts */
  #define DECLARE_OBBASE(Class) \
	public: \
	static int GetClassType (void) { return (OBCLASS_##Class); } \
	virtual bool IsClassType (const int ClassType) { return (GetClassType() == ClassType); } \
	virtual int GetMyClassType (void) {  return (OBCLASS_##Class);  } 

  #define DECLARE_OBCLASS(Class, BaseClass) \
	public: \
	static int GetClassType (void) { return (OBCLASS_##Class); } \
	virtual bool IsClassType (const int ClassType) { return (GetClassType() == ClassType ? true : BaseClass::IsClassType(ClassType)); } \
	virtual int GetMyClassType (void) { return (OBCLASS_##Class);  } 

	/* Cast a class pointer checking to ensure the cast is valid (checks the class
	   heirarchy). If invalid NULL is returned. Do not call with NULL pointer. */
  #define ObCastClass(Class, Ptr) \
  	(Class *) ((Ptr)->IsClassType(Class::GetClassType()) ? (Ptr) : NULL)

	/* Allows NULL input */
  #define ObCastClassNull(Class, Ptr) \
	(Class *) (Ptr ? ((Ptr)->IsClassType(Class::GetClassType()) ? (Ptr) : NULL) : NULL)

	/* Special case for casting a base record */
  #define ObCastRecord(BaseRecord) \
	(CObRecord *) (((BaseRecord)->IsRecord()) ? ((BaseRecord)->IsClassType(CObRecord::GetClassType()) ? (BaseRecord) : NULL) : NULL)
  #define ObCastGroup(BaseRecord) \
	(CObGroup *) (((BaseRecord)->IsGroup()) ? ((BaseRecord)->IsClassType(CObGroup::GetClassType()) ? (BaseRecord) : NULL) : NULL)
	

/*===========================================================================
 *		End of Class Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/
	
	/* Used to define the effect data array */
  #define START_EFFECTVALUE(Array) const obeffectdata_t Array[] = {
  #define ADD_EFFECTVALUE(Name, String, Flags) { &Name, String, Flags }, 
  #define END_EFFECTVALUE() { NULL, NULL } };

	/* Find data flags */
  #define OB_FIND_COMPARETEXT		0x0001	/* Case insensitive text search, default is binary */
  #define OB_FIND_OUTPUTLOG		0x0002	/* Output results to system log */
  #define OB_FIND_GROUPHEADER		0x0004	/* Search group headers as well */
  #define OB_FIND_RECORDHEADER		0x0008	/* Search record headers as well */
  #define OB_FIND_SUBRECORDHEADER	0x0010	/* Search subrecord headers as well */
  #define OB_FIND_ALLHEADERS		0x001C	
  #define OB_FIND_COUNTONLY		0x0020	/* Only count results */
  #define OB_FIND_CASESENSITIVE		0x0040	
  #define OB_FIND_FINDALL		0x0080	
  #define OB_FIND_ADDRECORDS		0x0100	
  #define OB_FIND_NOHEADER		0x0200

	/* Main game master file */
  #define OB_GAME_MASTER "oblivion.esm"

  	/* Check validation codes used in various places */
  #define OB_CHECKRESULT_OK		 0
  #define OB_CHECKRESULT_NOCHANGE	 1
  #define OB_CHECKRESULT_ERROR		-1

	/* Cache flags */
  #define OB_CACHE_DEFERLOAD	1

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/

	/* Forward class definitions */
  class CObRecord;

	/* Array of string objects */
  typedef CObPtrArray<CSString> CSStringArray;

	/* Holds effect data */
  struct obeffectdata_t {
	const obrectype_t* pName;
	const SSCHAR*	   pDescription;
	dword		   DefaultFlags;
   };

	/* Used to fixup the modindex of formIDs */
  typedef TObArray<byte> CObFormidFixupArray;

	/* FormID used everywhere in mod files to identify objects */
  typedef dword obformid_t;
  typedef TObArray<obformid_t> CObFormidArray;

	/* Used to find information in record and subrecord data */
  struct obfinddata_t {
	const byte*		pData;			/* Data to match */
	dword			DataSize;		/* Size of data in bytes */
	dword			Flags;			/* Find options */
	dword			FileCount;
	dword			GroupCount;
	dword			RecordCount;
	dword			SubrecordCount;

	dword			FoundSubrecords;
	dword			FoundRecords;

	obrectype_t*		pExcludeRecords;	/* Optional list of record types to exclude from the search */

	CObRefPtrArray<CObRecord>*	pFindRecords;

	obfinddata_t() {
		pData		 = NULL;
		DataSize	 = 0;
		Flags		 = 0;
		FileCount	 = 0;
		GroupCount	 = 0;
		RecordCount	 = 0;
		SubrecordCount	 = 0;
		FoundSubrecords  = 0;
		FoundRecords     = 0;
		pExcludeRecords	 = NULL;
		pFindRecords     = NULL;

	}
  };

	/* Used to find and collect use information */
  struct obrecorduse_t {
	dword	   Count;
	CObRecord* pRecord;
  };

	/* Array of use information for multiple records */
  typedef CObPtrArray<obrecorduse_t> CObRecordUseArray;

	/* Use information on a single record */
  struct obuseinfo_t {
	obformid_t		FormID;		/* Formid being looked for */
	CObRecord*		pRecord;	/* Record being looked for if available */
	CObRecordUseArray	Uses;

	obuseinfo_t() {
		FormID  = OB_FORMID_NULL;
		pRecord = NULL;
	}
  };

/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Import/Export Definitions
 *
 *=========================================================================*/

	/* Forward structure definitions */
  struct obrecfield_t;

	/* Holds information on a single column in a CVS file */
  struct obcsvcolinfo_t {
        CSString*		pValue;
	dword			ColIndex;	/* Column index in the CSV file */
	obfieldid_t		FieldID;	/* Field ID of the column */
	const obrecfield_t*	pField;
	bool			Process;	/* Process this field or not */
	int			UserData;
  };

	/* Array of CSV column objects */
  typedef CObPtrArray<obcsvcolinfo_t> CObCsvColInfos;

	/* Used when importing/exporting a CSV file */
  struct obcsvinfo_t {
	CCsvFile*       pCsvFile;
	CObCsvColInfos  ColInfos;

	obcsvcolinfo_t*	pEditorID;
	obcsvcolinfo_t* pRecordName;

	dword		CurrentLine;
  };

/*===========================================================================
 *		End of Import/Export Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Magic Effect Flags
 *
 *=========================================================================*/
  #define OB_EFFECTFLAG_HOSTILE             0x00000001
  #define OB_EFFECTFLAG_RECOVER             0x00000002
  #define OB_EFFECTFLAG_DETRIMENTAL         0x00000004
  #define OB_EFFECTFLAG_MAGNITUDEPERCENT    0x00000008
  #define OB_EFFECTFLAG_SELF                0x00000010
  #define OB_EFFECTFLAG_TOUCH               0x00000020
  #define OB_EFFECTFLAG_TARGET              0x00000040
  #define OB_EFFECTFLAG_NODURATION          0x00000080
  #define OB_EFFECTFLAG_NOMAGNITUDE         0x00000100
  #define OB_EFFECTFLAG_NOAREA              0x00000200
  #define OB_EFFECTFLAG_FXPERSIST           0x00000400
  #define OB_EFFECTFLAG_SPELLMAKING         0x00000800
  #define OB_EFFECTFLAG_ENCHANTING          0x00001000
  #define OB_EFFECTFLAG_NOINGREDIANT        0x00002000
  #define OB_EFFECTFLAG_USEWEAPON           0x00010000
  #define OB_EFFECTFLAG_USEARMOR            0x00020000
  #define OB_EFFECTFLAG_USECREATURE         0x00040000
  #define OB_EFFECTFLAG_USESKILL            0x00080000
  #define OB_EFFECTFLAG_USEATTRIBUTE        0x00100000
  #define OB_EFFECTFLAG_SPRAYPROJECTILE     0x02000000
  #define OB_EFFECTFLAG_BOLTPROJECTILE      0x04000000
  #define OB_EFFECTFLAG_FOGPROJECTILE       0x06000000
  #define OB_EFFECTFLAG_NOHITEFFECT         0x08000000
/*===========================================================================
 *		End of Magic Effect Flags
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Biped Flags
 *
 *=========================================================================*/
  #define OB_BIPEDFLAG_NONE		0x00000000

  #define OB_BIPEDFLAG_HEAD		0x00000001
  #define OB_BIPEDFLAG_HAIR		0x00000002
  #define OB_BIPEDFLAG_UPPERBODY	0x00000004
  #define OB_BIPEDFLAG_LOWERBODY	0x00000008
  #define OB_BIPEDFLAG_HAND		0x00000010
  #define OB_BIPEDFLAG_FOOT		0x00000020
  #define OB_BIPEDFLAG_RIGHTRING	0x00000040
  #define OB_BIPEDFLAG_LEFTRING		0x00000080
  #define OB_BIPEDFLAG_AMULET		0x00000100
  #define OB_BIPEDFLAG_WEAPON		0x00000200
  #define OB_BIPEDFLAG_BACKWEAPON	0x00000400
  #define OB_BIPEDFLAG_SIDEWEAPON	0x00000800
  #define OB_BIPEDFLAG_QUIVER		0x00001000
  #define OB_BIPEDFLAG_SHIELD		0x00002000
  #define OB_BIPEDFLAG_TORCH		0x00004000
  #define OB_BIPEDFLAG_TAIL		0x00008000

  #define OB_BIPEDFLAG_MASK		0x0000FFFF
/*===========================================================================
 *		End of Biped Flags
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Attributes
 *
 *=========================================================================*/
  #define OB_ATTRIBUTE_STRENGTH		0
  #define OB_ATTRIBUTE_INTELLIGENCE	1
  #define OB_ATTRIBUTE_WILLPOWER	2
  #define OB_ATTRIBUTE_AGILITY		3
  #define OB_ATTRIBUTE_SPEED		4
  #define OB_ATTRIBUTE_ENDURANCE	5
  #define OB_ATTRIBUTE_PERSONALITY	6
  #define OB_ATTRIBUTE_LUCK		7
/*===========================================================================
 *		End of Attributes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Spell Types and Levels
 *
 *=========================================================================*/

	/* Spell types */
  #define OB_SPELLTYPE_SPELL       0
  #define OB_SPELLTYPE_DISEASE     1
  #define OB_SPELLTYPE_POWER       2
  #define OB_SPELLTYPE_LESSERPOWER 3
  #define OB_SPELLTYPE_ABILITY	   4
  #define OB_SPELLTYPE_POISON      5

	/* Spell levels */
  #define OB_SPELLEVEL_NOVICE     0
  #define OB_SPELLEVEL_APPRENTICE 1
  #define OB_SPELLEVEL_JOURNEYMAN 2
  #define OB_SPELLEVEL_EXPERT     3
  #define OB_SPELLEVEL_MASTER     4

/*===========================================================================
 *		End of Spell Types and Levels
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Skill Indices
 *
 *=========================================================================*/
  #define OB_SKILL_NONE		-1
  #define OB_SKILL_ARMORER	0
  #define OB_SKILL_ATHLETICS	1
  #define OB_SKILL_BLADE	2
  #define OB_SKILL_BLOCK	3
  #define OB_SKILL_BLUNT	4
  #define OB_SKILL_HANDTOHAND	5
  #define OB_SKILL_HEAVYARMOR	6
  #define OB_SKILL_ALCHEMY	7
  #define OB_SKILL_ALTERATION	8
  #define OB_SKILL_CONJURATION	9
  #define OB_SKILL_DESTRUCTION	10
  #define OB_SKILL_ILLUSION	11
  #define OB_SKILL_MYSTICISM	12
  #define OB_SKILL_RESTORATION	13
  #define OB_SKILL_ACROBATICS	14
  #define OB_SKILL_LIGHTARMOR	15
  #define OB_SKILL_MARKSMAN	16
  #define OB_SKILL_MERCANTILE	17
  #define OB_SKILL_SECURITY	18
  #define OB_SKILL_SNEAK	19
  #define OB_SKILL_SPEECHCRAFT	20
/*===========================================================================
 *		End of Skill Indices
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Spell Schools
 *
 *=========================================================================*/
  #define OB_SCHOOL_ALTERATION  0
  #define OB_SCHOOL_CONJURATION 1
  #define OB_SCHOOL_DESTRUCTION 2
  #define OB_SCHOOL_ILLUSION    3
  #define OB_SCHOOL_MYSTICISM   4
  #define OB_SCHOOL_RESTORATION 5
/*===========================================================================
 *		End of Spell Schools
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Light Flags and Types
 *
 *=========================================================================*/

	/* Light flags */
  #define OB_LIGHFLAG_DYNAMIC		0x00000001
  #define OB_LIGHFLAG_CARRIED		0x00000002
  #define OB_LIGHFLAG_NEGATIVE		0x00000004
  #define OB_LIGHFLAG_FLICKER		0x00000008
  #define OB_LIGHFLAG_DEFAULTOFF	0x00000020
  #define OB_LIGHFLAG_FLICKERSLOW	0x00000040
  #define OB_LIGHFLAG_PULSE		0x00000080
  #define OB_LIGHFLAG_PULSESLOW		0x00000100
  #define OB_LIGHFLAG_SPOTLIGHT		0x00000200
  #define OB_LIGHFLAG_SPOTSHADOW	0x00000400

	/* Light types (mutually exclusive) */
  #define OB_LIGHTYPE_NONE		0x00000000
  #define OB_LIGHTYPE_FLICKER		OB_LIGHFLAG_FLICKER
  #define OB_LIGHTYPE_FLICKERSLOW	OB_LIGHFLAG_FLICKERSLOW
  #define OB_LIGHTYPE_PULSE		OB_LIGHFLAG_PULSE
  #define OB_LIGHTYPE_PULSESLOW		OB_LIGHFLAG_PULSESLOW
  #define OB_LIGHTYPE_MASK		0x000001C8

/*===========================================================================
 *		End of Light Flags and Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Actor Value Indices
 *
 *=========================================================================*/
  #define OB_ACTORVALUE_NONE		-1
  #define OB_ACTORVALUE_STRENGTH	0
  #define OB_ACTORVALUE_INTELLIGENCE	1
  #define OB_ACTORVALUE_WILLPOWER	2
  #define OB_ACTORVALUE_AGILITY		3
  #define OB_ACTORVALUE_SPEED		4
  #define OB_ACTORVALUE_ENDURANCE	5
  #define OB_ACTORVALUE_PERSONALITY	6
  #define OB_ACTORVALUE_LUCK		7
  #define OB_ACTORVALUE_HEALTH		8
  #define OB_ACTORVALUE_MAGICKA		9
  #define OB_ACTORVALUE_FATIGUE		10
  #define OB_ACTORVALUE_ENCUMBRANCE	11
  #define OB_ACTORVALUE_ARMORER		12
  #define OB_ACTORVALUE_ATHLETICS	13
  #define OB_ACTORVALUE_BLADE		14
  #define OB_ACTORVALUE_BLOCK		15
  #define OB_ACTORVALUE_BLUNT		16
  #define OB_ACTORVALUE_HANDTOHAND	17
  #define OB_ACTORVALUE_HEAVYARMOR	18
  #define OB_ACTORVALUE_ALCHEMY		19
  #define OB_ACTORVALUE_ALTERATION	20
  #define OB_ACTORVALUE_CONJURATION	21
  #define OB_ACTORVALUE_DESTRUCTION	22
  #define OB_ACTORVALUE_ILLUSION	23
  #define OB_ACTORVALUE_MYSTICISM	24
  #define OB_ACTORVALUE_RESTORATION	25
  #define OB_ACTORVALUE_ACROBATICS	26
  #define OB_ACTORVALUE_LIGHTARMOR	27
  #define OB_ACTORVALUE_MARKSMAN	28 
  #define OB_ACTORVALUE_MERCANTILE	29
  #define OB_ACTORVALUE_SECURITY	30
  #define OB_ACTORVALUE_SNEAK		31
  #define OB_ACTORVALUE_SPEECHCRAFT	32

  #define OB_ACTORVALUE_AGRESSION	33
  #define OB_ACTORVALUE_CONFIDENCE	34
  #define OB_ACTORVALUE_ENERGY		35
  #define OB_ACTORVALUE_RESPONSIBILITY	36
  #define OB_ACTORVALUE_BOUNTY		37
  
  #define OB_ACTORVALUE_MAGICKAMULT	40
  #define OB_ACTORVALUE_NIGHTEYE	41
  #define OB_ACTORVALUE_ATTACSKBONUS	42
  #define OB_ACTORVALUE_DEFENDBONUS	43
  #define OB_ACTORVALUE_CASTINGPENALTY	44
  #define OB_ACTORVALUE_BLINDNESS	45
  #define OB_ACTORVALUE_CHAMELEON	46
  #define OB_ACTORVALUE_INVISIBILITY	47
  #define OB_ACTORVALUE_PARALYSIS	48
  #define OB_ACTORVALUE_SILENCE		49
  #define OB_ACTORVALUE_CONFUSION	50
  #define OB_ACTORVALUE_DETECTITEMRANGE	51
  #define OB_ACTORVALUE_SPELLABSORBCHANCE 52
  #define OB_ACTORVALUE_SPELLREFLECTCHANCE 53
  #define OB_ACTORVALUE_SWIMSPEEDMULT	54
  #define OB_ACTORVALUE_WATERBREATHING	55
  #define OB_ACTORVALUE_WATERWALKING	56
  #define OB_ACTORVALUE_STUNTEDMAGICKA	57
  #define OB_ACTORVALUE_DETECTLIFERANGE	58
  #define OB_ACTORVALUE_REFLECTDAMAGE	59
  #define OB_ACTORVALUE_TELEKINESIS	60
  #define OB_ACTORVALUE_RESISTFIRE	61
  #define OB_ACTORVALUE_RESISTFROST	62
  #define OB_ACTORVALUE_RESISTDISEASE	63
  #define OB_ACTORVALUE_RESISTMAGIC	64
  #define OB_ACTORVALUE_RESISTNORMALWEAP 65
  #define OB_ACTORVALUE_RESISTPARALYSIS	66
  #define OB_ACTORVALUE_RESISTPOISON	67
  #define OB_ACTORVALUE_RESISTSHOCK	68
  #define OB_ACTORVALUE_VAMPIRISM	69
  #define OB_ACTORVALUE_DARKNESS	70
  #define OB_ACTORVALUE_RESISTWATER	71

/*===========================================================================
 *		End of Actor Value Indices
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Soul Gem Definitions
 *
 *=========================================================================*/
  #define OB_SOULGEM_NONE	0
  #define OB_SOULGEM_PETTY	1
  #define OB_SOULGEM_LESSER	2
  #define OB_SOULGEM_COMMON	3
  #define OB_SOULGEM_GREATER	4
  #define OB_SOULGEM_GRAND	5
/*===========================================================================
 *		End of Soul Gem Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Weapon Types
 *
 *=========================================================================*/
  #define OB_WEAPTYPE_BLADEONEHAND	0
  #define OB_WEAPTYPE_BLADETWOHAND	1
  #define OB_WEAPTYPE_BLUNTONEHAND	2
  #define OB_WEAPTYPE_BLUNTTWOHAND	3
  #define OB_WEAPTYPE_STAFF		4
  #define OB_WEAPTYPE_BOW		5
/*===========================================================================
 *		End of Weapon Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchantment Types
 *
 *=========================================================================*/
  #define OB_ENCHTYPE_SCROLL  0
  #define OB_ENCHTYPE_STAFF   1
  #define OB_ENCHTYPE_WEAPON  2
  #define OB_ENCHTYPE_APPAREL 3
/*===========================================================================
 *		End of Enchantment Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchantment Effect Types
 *
 *=========================================================================*/
  #define OB_EFFECTTYPE_SELF   0x00000000
  #define OB_EFFECTTYPE_TOUCH  0x00000001
  #define OB_EFFECTTYPE_TARGET 0x00000002
/*===========================================================================
 *		End of Enchantment Effect Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Apparatus Types
 *
 *=========================================================================*/

	/* Apparatus types */
  #define OB_APPATYPE_MORTAR		0
  #define OB_APPATYPE_ALEMBIC		1
  #define OB_APPATYPE_CALCINATOR	2
  #define OB_APPATYPE_RETORT		3

/*===========================================================================
 *		End of Apparatus Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Animation Groups
 *
 *=========================================================================*/
  #define OB_ANIMGROUP_ATTACKBACKPOWER 	      0x18
  #define OB_ANIMGROUP_ATTACKBOW              0x13
  #define OB_ANIMGROUP_ATTACKFORWARDPOWER     0x17 
  #define OB_ANIMGROUP_ATTACKLEFT             0x14
  #define OB_ANIMGROUP_ATTACKLEFTPOWER        0x19
  #define OB_ANIMGROUP_ATTACKPOWER            0x16
  #define OB_ANIMGROUP_ATTACKRIGHT            0x15
  #define OB_ANIMGROUP_ATTACKRIGHTPOWER       0x1A
  #define OB_ANIMGROUP_BACKWARD               0x04
  #define OB_ANIMGROUP_BLOCKATTACK            0x1D
  #define OB_ANIMGROUP_BLOCKHIT               0x1C
  #define OB_ANIMGROUP_BLOCKIDLE              0x1B
  #define OB_ANIMGROUP_CASTSELF               0x22 
  #define OB_ANIMGROUP_CASTSELFALT            0x25
  #define OB_ANIMGROUP_CASTTARGET             0x24
  #define OB_ANIMGROUP_CASTTARGETALT          0x27
  #define OB_ANIMGROUP_CASTTOUCH              0x23
  #define OB_ANIMGROUP_CASTTOUCHALT           0x26
  #define OB_ANIMGROUP_DODGEBACK              0x0C
  #define OB_ANIMGROUP_DODGEFORWARD           0x0B
  #define OB_ANIMGROUP_DODGELEFT              0x0D
  #define OB_ANIMGROUP_DODGERIGHT             0x0E
  #define OB_ANIMGROUP_DYNAMICIDLE            0x01
  #define OB_ANIMGROUP_EQUIP                  0x11
  #define OB_ANIMGROUP_FASTBACKWARD           0x08
  #define OB_ANIMGROUP_FASTFORWARD            0x07
  #define OB_ANIMGROUP_FASTLEFT               0x09
  #define OB_ANIMGROUP_FASTRIGHT              0x0A
  #define OB_ANIMGROUP_FORWARD                0x03
  #define OB_ANIMGROUP_IDLE                   0x00
  #define OB_ANIMGROUP_JUMPLAND               0x2A
  #define OB_ANIMGROUP_JUMPLOOP               0x29
  #define OB_ANIMGROUP_JUMPSTART              0x28
  #define OB_ANIMGROUP_LEFT                   0x05
  #define OB_ANIMGROUP_RECOIL                 0x1E
  #define OB_ANIMGROUP_RIGHT                  0x06
  #define OB_ANIMGROUP_SPECIALIDLE            0x02
  #define OB_ANIMGROUP_STAGGER                0x1F
  #define OB_ANIMGROUP_TORCHIDLE              0x21
  #define OB_ANIMGROUP_TURNLEFT               0x0F
  #define OB_ANIMGROUP_TURNRIGHT              0x10
  #define OB_ANIMGROUP_UNEQUIP                0x12
/*===========================================================================
 *		End of Animation Groups
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Map Marker Types
 *
 *=========================================================================*/

  #define OB_MAPMARKER_NONE		0
  #define OB_MAPMARKER_CAMP		1
  #define OB_MAPMARKER_CAVE		2
  #define OB_MAPMARKER_CITY		3
  #define OB_MAPMARKER_ELVENRUIN	4
  #define OB_MAPMARKER_FORTRUIN		5
  #define OB_MAPMARKER_MINE		6
  #define OB_MAPMARKER_LANDMARK		7
  #define OB_MAPMARKER_TAVERN		8
  #define OB_MAPMARKER_STABLE		8
  #define OB_MAPMARKER_SETTLEMENT	9
  #define OB_MAPMARKER_DAEDRICSHRINE	10
  #define OB_MAPMARKER_OBLIVIONGATE	11
  #define OB_MAPMARKER_UNKNOWN		12

/*===========================================================================
 *		End of Map Marker Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Parameter types
 *
 *=========================================================================*/
  #define OB_FUNCPARAM_STRING		0x00
  #define OB_FUNCPARAM_INTEGER 		0x01
  #define OB_FUNCPARAM_FLOAT		0x02
  #define OB_FUNCPARAM_INVENTORYOBJECT	0x03
  #define OB_FUNCPARAM_OBJECTREF	0x04	/* ref */
  #define OB_FUNCPARAM_ACTORVALUE	0x05
  #define OB_FUNCPARAM_ACTOR		0x06	/* ref */
  #define OB_FUNCPARAM_SPELLITEM	0x07
  #define OB_FUNCPARAM_AXIS		0x08
  #define OB_FUNCPARAM_CELL		0x09
  #define OB_FUNCPARAM_ANIMATIONGROUP	0x0A
  #define OB_FUNCPARAM_MAGICITEM	0x0B
  #define OB_FUNCPARAM_SOUND		0x0C
  #define OB_FUNCPARAM_TOPIC		0x0D
  #define OB_FUNCPARAM_QUEST		0x0E
  #define OB_FUNCPARAM_RACE		0x0F
  #define OB_FUNCPARAM_CLASS		0x10
  #define OB_FUNCPARAM_FACTION		0x11
  #define OB_FUNCPARAM_SEX		0x12
  #define OB_FUNCPARAM_GLOBAL		0x13
  #define OB_FUNCPARAM_FURNITURE	0x14
  #define OB_FUNCPARAM_TESOBJECT	0x15
  #define OB_FUNCPARAM_VARIABLENAME	0x16
  #define OB_FUNCPARAM_QUESTSTAGE	0x17
  #define OB_FUNCPARAM_MAPMARKER	0x18	/* ref */
  #define OB_FUNCPARAM_ACTORBASE	0x19
  #define OB_FUNCPARAM_CONTAINER 	0x1A	/* ref */
  #define OB_FUNCPARAM_WORLDSPACE	0x1B
  #define OB_FUNCPARAM_CRIMETYPE	0x1C
  #define OB_FUNCPARAM_AIPACKAGE	0x1D
  #define OB_FUNCPARAM_COMBATSTYLE	0x1E
  #define OB_FUNCPARAM_MAGICEFFECT	0x1F
  #define OB_FUNCPARAM_BIRTHSIGN	0x20
  #define OB_FUNCPARAM_FORMTYPE		0x21
  #define OB_FUNCPARAM_WEATHER		0x22
  #define OB_FUNCPARAM_NPC 		0x23
  #define OB_FUNCPARAM_OWNER		0x24
  #define OB_FUNCPARAM_EFFECTSHADER	0x25
/*===========================================================================
 *		End of Function Parameter types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Form/Object Types
 *
 *=========================================================================*/
  #define OB_FORMTYPE_ACTIVATOR        0x12
  #define OB_FORMTYPE_AMMO             0x22
  #define OB_FORMTYPE_ANIMOBJECT       0x41
  #define OB_FORMTYPE_APPARATUS        0x13
  #define OB_FORMTYPE_ARMOR            0x14
  #define OB_FORMTYPE_BOOK             0x15
  #define OB_FORMTYPE_CLOTHING         0x16
  #define OB_FORMTYPE_COMBATSTYLE      0x3E
  #define OB_FORMTYPE_CONTAINER        0x17
  #define OB_FORMTYPE_CREATURE         0x24
  #define OB_FORMTYPE_DOOR             0x18
  #define OB_FORMTYPE_EFFECTSHADER     0x43
  #define OB_FORMTYPE_ENCHANTMENT      0x0F
  #define OB_FORMTYPE_FLORA            0x1F
  #define OB_FORMTYPE_FURNITURE        0x20
  #define OB_FORMTYPE_GRASS            0x1D
  #define OB_FORMTYPE_INGREDIENT       0x19
  #define OB_FORMTYPE_KEY              0x27
  #define OB_FORMTYPE_LANDTEXTURE      0x0E
  #define OB_FORMTYPE_LEVELEDCREATURE  0x25
  #define OB_FORMTYPE_LEVELEDITEM      0x2B
  #define OB_FORMTYPE_LEVELEDSPELL     0x40
  #define OB_FORMTYPE_LIGHT            0x1A
  #define OB_FORMTYPE_LOADSCREEN       0x3F
  #define OB_FORMTYPE_MISCITEM         0x1B
  #define OB_FORMTYPE_NPC              0x23
  #define OB_FORMTYPE_POTION           0x28
  #define OB_FORMTYPE_SIGILSTONE       0x2A
  #define OB_FORMTYPE_SOULGEM          0x26
  #define OB_FORMTYPE_SOUND            0x0A
  #define OB_FORMTYPE_SPELL            0x10
  #define OB_FORMTYPE_STATIC           0x1C
  #define OB_FORMTYPE_SUBSPACE         0x29
  #define OB_FORMTYPE_TREE             0x1E
  #define OB_FORMTYPE_WATERTYPE        0x42
  #define OB_FORMTYPE_WEAPON           0x21
/*===========================================================================
 *		End of Form/Object Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Crime Types
 *
 *=========================================================================*/
  #define OB_CRIMETYPE_STEAL      0
  #define OB_CRIMETYPE_PICKPOCKET 1
  #define OB_CRIMETYPE_TRESPASS   2
  #define OB_CRIMETYPE_ATTACK     3
  #define OB_CRIMETYPE_MURDER     4
/*===========================================================================
 *		End of Crime Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Class Type Definitions
 *
 * Define unique integers to known classes. Integers are used merely for
 * simplicity and speed. These values could be defined in their respective
 * classes but it is easily to define them all in the same place to ensure
 * no duplicates.
 *
 *=========================================================================*/
  #define OBCLASS_CObBaseRecord		10
  #define OBCLASS_CObRecord		100
  #define OBCLASS_CObGroup		101
  #define OBCLASS_CObTypeGroup		102
  #define OBCLASS_CObFormIDGroup	103
  #define OBCLASS_CObBlockGroup		104
  #define OBCLASS_CObGridGroup		105
  #define OBCLASS_CObSubrecord		200

  #define OBCLASS_CObIdRecord		1000
  #define OBCLASS_CObItem1Record	1001
  #define OBCLASS_CObItem2Record	1002
  #define OBCLASS_CObAmmoRecord		1003
  #define OBCLASS_CObAppaRecord		1004
  #define OBCLASS_CObArmoRecord		1005
  #define OBCLASS_CObBookRecord		1006
  #define OBCLASS_CObClotRecord		1007
  #define OBCLASS_CObEffectItemRecord	1008
  #define OBCLASS_CObEnchRecord		1009
  #define OBCLASS_CObIngrRecord		1010
  #define OBCLASS_CObLvliRecord		1011
  #define OBCLASS_CObMiscRecord		1012
  #define OBCLASS_CObScptRecord		1013
  #define OBCLASS_CObSgstRecord		1014
  #define OBCLASS_CObSpelRecord		1015
  #define OBCLASS_CObTes4Record		1016
  #define OBCLASS_CObWeapRecord		1017
  #define OBCLASS_CObLighRecord		1018
  #define OBCLASS_CObRefrRecord		1019
  #define OBCLASS_CObCellRecord		1020
  #define OBCLASS_CObWrldRecord		1021
  #define OBCLASS_CObBsgnRecord		1022
  #define OBCLASS_CObContRecord		1023
  #define OBCLASS_CObAchrRecord		1024
  #define OBCLASS_CObAcreRecord		1025
  #define OBCLASS_CObActiRecord		1026
  #define OBCLASS_CObAlchRecord		1027
  #define OBCLASS_CObAnioRecord		1028
  #define OBCLASS_CObClmtRecord		1029
  #define OBCLASS_CObCreaRecord		1030
  #define OBCLASS_CObDialRecord		1031
  #define OBCLASS_CObDoorRecord		1032
  #define OBCLASS_CObFactRecord		1033
  #define OBCLASS_CObFlorRecord		1034
  #define OBCLASS_CObIdleRecord		1035
  #define OBCLASS_CObInfoRecord		1036
  #define OBCLASS_CObLandRecord		1037
  #define OBCLASS_CObLscrRecord		1038
  #define OBCLASS_CObLtexRecord		1039
  #define OBCLASS_CObLvlcRecord		1040
  #define OBCLASS_CObLvspRecord		1041
  #define OBCLASS_CObMgefRecord		1042
  #define OBCLASS_CObNpcRecord		1043
  #define OBCLASS_CObPackRecord		1044
  #define OBCLASS_CObPgrdRecord		1045
  #define OBCLASS_CObQustRecord		1046
  #define OBCLASS_CObRaceRecord		1047
  #define OBCLASS_CObRegnRecord		1048
  #define OBCLASS_CObWatrRecord		1049
  #define OBCLASS_CObKeymRecord		1050
  #define OBCLASS_CObSlgmRecord		1051
  #define OBCLASS_CObStatRecord		1052
  #define OBCLASS_CObSounRecord		1053
  #define OBCLASS_CObFurnRecord		1054
  #define OBCLASS_CObBaseRefrRecord	1055
  
  #define OBCLASS_CObAmmoDataSubrecord	2000
  #define OBCLASS_CObAppaDataSubrecord	2001
  #define OBCLASS_CObArmoDataSubrecord	2002
  #define OBCLASS_CObBookDataSubrecord	2003
  #define OBCLASS_CObByteSubrecord	2004
  #define OBCLASS_CObClotDataSubrecord	2005
  #define OBCLASS_CObDwordSubrecord	2006
  #define OBCLASS_CObEfitSubrecord	2007
  #define OBCLASS_CObEnitSubrecord	2008
  #define OBCLASS_CObFloatSubrecord	2009
  #define OBCLASS_CObHedrSubrecord	2010
  #define OBCLASS_CObIngrEnitSubrecord	2011
  #define OBCLASS_CObInt64Subrecord	2012
  #define OBCLASS_CObLvloSubrecord	2013
  #define OBCLASS_CObMiscDataSubrecord	2014
  #define OBCLASS_CObNameSubrecord	2015
  #define OBCLASS_CObSchrSubrecord	2016
  #define OBCLASS_CObScitSubrecord	2017
  #define OBCLASS_CObSgstDataSubrecord	2018
  #define OBCLASS_CObSpitSubrecord	2019
  #define OBCLASS_CObString1Subrecord	2020
  #define OBCLASS_CObStringSubrecord	2021
  #define OBCLASS_CObWeapDataSubrecord	2022
  #define OBCLASS_CObWordSubrecord	2023
  #define OBCLASS_CObLighDataSubrecord	2024
  #define OBCLASS_CObRefrDataSubrecord	2025
  #define OBCLASS_CObXtelSubrecord	2026
  #define OBCLASS_CObFormidSubrecord	2026
  #define OBCLASS_CObCntoSubrecord	2027
  #define OBCLASS_CObPositionSubrecord	2028
  #define OBCLASS_CObPosAngleSubrecord  2029
  #define OBCLASS_CObLongSubrecord	2030  
  #define OBCLASS_CObFormidArraySubrecord 2031
  #define OBCLASS_CObXespSubrecord	2032
  #define OBCLASS_CObWlstSubrecord	2033
  #define OBCLASS_CObEnit8Subrecord	2034
  #define OBCLASS_CObCreaSnamSubrecord	2035
  #define OBCLASS_CObXnamSubrecord	2036
  #define OBCLASS_CObIdleDataSubrecord	2037
  #define OBCLASS_CObCtdaSubrecord	2038
  #define OBCLASS_CObCtdtSubrecord	2039
  #define OBCLASS_CObAtxtSubrecord	2040
  #define OBCLASS_CObBtxtSubrecord	2041
  #define OBCLASS_CObVtexSubrecord	2042
  #define OBCLASS_CObLnamSubrecord	2043
  #define OBCLASS_CObMgefDataSubrecord	2044
  #define OBCLASS_CObSnamSubrecord	2045
  #define OBCLASS_CObPldtSubrecord	2046
  #define OBCLASS_CObPgrlSubrecord	2047
  #define OBCLASS_CObQstaSubrecord	2048
  #define OBCLASS_CObScroSubrecord	2049
  #define OBCLASS_CObDnamSubrecord	2050
  #define OBCLASS_CObEnamSubrecord	2051
  #define OBCLASS_CObVnamSubrecord	2052
  #define OBCLASS_CObXlocSubrecord	2053
  #define OBCLASS_CObRdwtSubrecord	2054
  #define OBCLASS_CObRdgsSubrecord	2055
  #define OBCLASS_CObRdsdSubrecord	2056
  #define OBCLASS_CObRdotSubrecord	2057
  #define OBCLASS_CObWthrRecord		2058
  #define OBCLASS_CObPtdtSubrecord	2059
  #define OBCLASS_CObKeymDataSubrecord	2060
  #define OBCLASS_CObSlgmDataSubrecord	2061
  #define OBCLASS_CObContDataSubrecord	2062
  #define OBCLASS_CObSndxSubrecord	2063
  #define OBCLASS_CObPfpcSubrecord	2064
  #define OBCLASS_CObDataSubrecord	2065
  #define OBCLASS_CObSlsdSubrecord	2066

/*===========================================================================
 *		End of Class Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/

	/* Fixup a formID modindex */
  bool ObFixupFormid (obformid_t& OutputFormID, const obformid_t OrigFormID, CObFormidFixupArray& FixupArray);

	/* Get string values */
  const SSCHAR* GetObBipedFlagString        (const int Value);
  const SSCHAR* GetObSkillString            (const int Value);
  const SSCHAR* GetObAttributeString        (const int Value);
  const SSCHAR* GetObActorValueString       (const int Value);
  const SSCHAR* GetObScriptActorValueString (const int Value);
  const SSCHAR* GetObSpellSchoolString      (const int Value);
  const SSCHAR* GetObEnchantRangeString     (const int Value);
  const SSCHAR* GetObEnchantTypeString      (const int Value);
  const SSCHAR* GetObLightTypeString        (const int Value);
  const SSCHAR* GetObApparatusTypeString    (const int Value);
  const SSCHAR* GetObMapMarkerTypeString    (const int Value);
  const SSCHAR* GetObSpellTypeString        (const int Value);
  const SSCHAR* GetObSpellLevelString       (const int Value);
  const SSCHAR* GetObSoulGemString          (const int Value);
  const SSCHAR* GetObWeaponTypeString       (const int Value);
  const SSCHAR* GetObAnimationGroupString   (const int Value);
  const SSCHAR* GetObFormTypeString         (const int Value);
  const SSCHAR* GetObCrimeTypeString        (const int Value);

	/* Get a value from a string */
  bool GetObBipedFlagValue        (int& Value, const SSCHAR* pString);
  bool GetObSkillValue            (int& Value, const SSCHAR* pString);
  bool GetObAttributeValue        (int& Value, const SSCHAR* pString);
  bool GetObActorValueValue       (int& Value, const SSCHAR* pString);
  bool GetObScriptActorValueValue (int& Value, const SSCHAR* pString);
  bool GetObSpellSchoolValue      (int& Value, const SSCHAR* pString);
  bool GetObEnchantTypeValue      (int& Value, const SSCHAR* pString);
  bool GetObEnchantRangeValue     (int& Value, const SSCHAR* pString);
  bool GetObLightTypeValue        (int& Value, const SSCHAR* pString);
  bool GetObApparatusTypeValue    (int& Value, const SSCHAR* pString);
  bool GetObMapMarkerTypeValue    (int& Value, const SSCHAR* pString);
  bool GetObSpellTypeValue        (int& Value, const SSCHAR* pString);
  bool GetObSpellLevelValue       (int& Value, const SSCHAR* pString);
  bool GetObSoulGemValue          (int& Value, const SSCHAR* pString);
  bool GetObWeaponTypeValue       (int& Value, const SSCHAR* pString);
  bool GetObAnimationGroupValue   (int& Value, const SSCHAR* pString);
  bool GetObFormTypeValue         (int& Value, const SSCHAR* pString);
  bool GetObCrimeTypeValue        (int& Value, const SSCHAR* pString);

	/* Get effect data from an effect name string */
  const obeffectdata_t* FindObEffectData (const SSCHAR* pString);

	/* Parse/Make a complete biped flags string */
  void  MakeObBipedFlagString  (CSString& Buffer, const dword Flag);
  void  MakeObBipedFlagString  (CSString& Buffer, const dword Flag, const SSCHAR* pDivString);
  dword ParseObBipedFlagString (const SSCHAR* pValue);
  dword ParseObBipedFlagString (const SSCHAR* pValue, const SSCHAR* pDivString);

	/* Basic find in binary or text data */
  dword ObFindData           (const byte* pData, const dword Size, obfinddata_t& FindData);
  dword ObFindTextData       (const byte* pData, const dword Size, obfinddata_t& FindData);
  dword ObFindDataNoCase     (const byte* pData, const dword Size, obfinddata_t& FindData);
  dword ObFindTextDataNoCase (const byte* pData, const dword Size, obfinddata_t& FindData);
  dword ObFindDataCase       (const byte* pData, const dword Size, obfinddata_t& FindData);
  dword ObFindTextDataCase   (const byte* pData, const dword Size, obfinddata_t& FindData);

	/* Check if a record name occurs in a list */
  bool ObContainsRecordType (const obrectype_t Name, const obrectype_t* pArray);

	/* Prepares an editor id by removing invalid characters */
  bool ObPrepareEditorID (CSString& EditorID);

	/* Check record types */
  bool ObIsValidLvliRecord (const obrectype_t RecordType);
  bool ObIsValidLvspRecord (const obrectype_t RecordType);
  bool ObIsValidLvlcRecord (const obrectype_t RecordType);
  bool ObIsInventoryRecord (const obrectype_t RecordType);
  bool ObIsObjectRecord    (const obrectype_t RecordType);

	/* Script functions */
  CObScriptFunction* ObGetScriptFunction        (const char* pName);
  CObScriptFunction* ObGetScriptConsoleFunction (const char* pName);
  bool               ObLoadScriptFunctions      (const char* pFilename, const dword CustomFlags = 0);
  const SSCHAR*      ObGetScriptFuncParamString (const int Type);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/
  extern const stringvalue_t s_ObBipedFlags[];
  extern const stringvalue_t s_ObAttributes[];
  extern const stringvalue_t s_ObSkills[];
  extern const stringvalue_t s_ObSpellSchoolValues[];
  extern const stringvalue_t s_ObActorValues[];
  extern const stringvalue_t s_ObActorValueAttributes[];
  extern const stringvalue_t s_ObActorValueSkills[];  
  extern const stringvalue_t s_ObScriptActorValues[];
  extern const stringvalue_t s_ObLightTypes[];
  extern const stringvalue_t s_ObEnchantTypes[];
  extern const stringvalue_t s_ObEnchantRangeTypes[];
  extern const stringvalue_t s_ObApparatusTypes[];
  extern const stringvalue_t s_ObMapMarkerTypes[];
  extern const stringvalue_t s_ObSpellLevels[];
  extern const stringvalue_t s_ObSpellTypes[];
  extern const stringvalue_t s_ObSoulGems[];
  extern const stringvalue_t s_ObSoulGemsNone[];
  extern const stringvalue_t s_ObWeaponTypes[];
  extern const stringvalue_t s_ObAnimationGroups[];
  extern const stringvalue_t s_ObFormTypes[];
  extern const stringvalue_t s_ObCrimeTypes[];

  extern const obeffectdata_t l_EffectData[];
/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/


#endif
/*===========================================================================
 *		End of File Obmoddefs.H
 *=========================================================================*/
