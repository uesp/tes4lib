/*===========================================================================
 *
 * File:	Obmoddefs.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 19, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obmoddefs.h"
#include "ctype.h"


/*===========================================================================
 *
 * Begin Global Constants
 *
 *=========================================================================*/
const obrgba_t OB_COLOR_NULL = { 0, 0, 0, 0 };
/*===========================================================================
 *		End of Global Constants
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Script Functions
 *
 *=========================================================================*/
  CObScriptFunctions	g_ScriptFunctions;
/*===========================================================================
 *		End of Script Functions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Biped Flags
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObMakeBipedFlags)
	ADD_STRINGVALUE( OB_BIPEDFLAG_NONE,		"None")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HEAD,		"Head")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HAIR,		"Hair")
	ADD_STRINGVALUE( OB_BIPEDFLAG_UPPERBODY,	"UpperBody")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LOWERBODY,	"LowerBody")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HAND,		"Hand")
	ADD_STRINGVALUE( OB_BIPEDFLAG_FOOT,		"Foot")
	ADD_STRINGVALUE( OB_BIPEDFLAG_RIGHTRING,	"RightRing")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LEFTRING,		"LeftRing")
	ADD_STRINGVALUE( OB_BIPEDFLAG_AMULET,		"Amulet")
	ADD_STRINGVALUE( OB_BIPEDFLAG_WEAPON,		"Weapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_BACKWEAPON,	"BackWeapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_SIDEWEAPON,	"SideWeapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_QUIVER,		"Quiver")
	ADD_STRINGVALUE( OB_BIPEDFLAG_SHIELD,		"Shield")
	ADD_STRINGVALUE( OB_BIPEDFLAG_TORCH,		"Torch")
	ADD_STRINGVALUE( OB_BIPEDFLAG_TAIL,		"Tail")
END_STRINGVALUE()

	/* Keep the following array for backwards compatibility */
BEGIN_STRINGVALUE(s_ObBipedFlags)
	ADD_STRINGVALUE( OB_BIPEDFLAG_NONE,		"None")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HEAD,		"Head")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HAIR,		"Hair")
	ADD_STRINGVALUE( OB_BIPEDFLAG_UPPERBODY,	"UpperBody")
	ADD_STRINGVALUE( OB_BIPEDFLAG_UPPERBODY,	"Upper Body")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LOWERBODY,	"LowerBody")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LOWERBODY,	"Lower Body")
	ADD_STRINGVALUE( OB_BIPEDFLAG_HAND,		"Hand")
	ADD_STRINGVALUE( OB_BIPEDFLAG_FOOT,		"Foot")
	ADD_STRINGVALUE( OB_BIPEDFLAG_RIGHTRING,	"RightRing")
	ADD_STRINGVALUE( OB_BIPEDFLAG_RIGHTRING,	"Right Ring")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LEFTRING,		"LeftRing")
	ADD_STRINGVALUE( OB_BIPEDFLAG_LEFTRING,		"Left Ring")
	ADD_STRINGVALUE( OB_BIPEDFLAG_AMULET,		"Amulet")
	ADD_STRINGVALUE( OB_BIPEDFLAG_WEAPON,		"Weapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_BACKWEAPON,	"BackWeapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_BACKWEAPON,	"Back Weapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_SIDEWEAPON,	"SideWeapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_SIDEWEAPON,	"Side Weapon")
	ADD_STRINGVALUE( OB_BIPEDFLAG_QUIVER,		"Quiver")
	ADD_STRINGVALUE( OB_BIPEDFLAG_SHIELD,		"Shield")
	ADD_STRINGVALUE( OB_BIPEDFLAG_TORCH,		"Torch")
	ADD_STRINGVALUE( OB_BIPEDFLAG_TAIL,		"Tail")
END_STRINGVALUE()
/*===========================================================================
 *		End of Biped Flags
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Attributes
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObAttributes)
	ADD_STRINGVALUE( OB_ATTRIBUTE_STRENGTH,		"Strength")
	ADD_STRINGVALUE( OB_ATTRIBUTE_INTELLIGENCE,	"Intelligence")
	ADD_STRINGVALUE( OB_ATTRIBUTE_WILLPOWER,	"Willpower")
	ADD_STRINGVALUE( OB_ATTRIBUTE_AGILITY,		"Agility")
	ADD_STRINGVALUE( OB_ATTRIBUTE_SPEED,		"Speed")
	ADD_STRINGVALUE( OB_ATTRIBUTE_ENDURANCE,	"Endurance")
	ADD_STRINGVALUE( OB_ATTRIBUTE_PERSONALITY,	"Personality")
	ADD_STRINGVALUE( OB_ATTRIBUTE_LUCK,		"Luck")
END_STRINGVALUE()
/*===========================================================================
 *		End of Attributes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Skills
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObSkills)
	ADD_STRINGVALUE( OB_SKILL_ARMORER,	"Armorer")
	ADD_STRINGVALUE( OB_SKILL_ATHLETICS,	"Athletics")
	ADD_STRINGVALUE( OB_SKILL_BLADE,	"Blade")
	ADD_STRINGVALUE( OB_SKILL_BLOCK,	"Block")
	ADD_STRINGVALUE( OB_SKILL_BLUNT,	"Blunt")
	ADD_STRINGVALUE( OB_SKILL_HANDTOHAND,	"Hand to Hand")
	ADD_STRINGVALUE( OB_SKILL_HEAVYARMOR,	"Heavy Armor")
	ADD_STRINGVALUE( OB_SKILL_ALCHEMY,	"Alchemy")
	ADD_STRINGVALUE( OB_SKILL_ALTERATION,	"Alteration")
	ADD_STRINGVALUE( OB_SKILL_CONJURATION,	"Conjuration")
	ADD_STRINGVALUE( OB_SKILL_DESTRUCTION,	"Destruction")
	ADD_STRINGVALUE( OB_SKILL_ILLUSION,	"Illusion")
	ADD_STRINGVALUE( OB_SKILL_MYSTICISM,	"Musticism")
	ADD_STRINGVALUE( OB_SKILL_RESTORATION,	"Restoration")
	ADD_STRINGVALUE( OB_SKILL_ACROBATICS,	"Acrobatics")
	ADD_STRINGVALUE( OB_SKILL_LIGHTARMOR,	"Light Armor")
	ADD_STRINGVALUE( OB_SKILL_MARKSMAN,	"Marksman")
	ADD_STRINGVALUE( OB_SKILL_MERCANTILE,	"Mecantile")
	ADD_STRINGVALUE( OB_SKILL_SECURITY,	"Security")
	ADD_STRINGVALUE( OB_SKILL_SNEAK,	"Sneak")
	ADD_STRINGVALUE( OB_SKILL_SPEECHCRAFT,	"Speechcraft")
	ADD_STRINGVALUE( OB_SKILL_NONE,		"None")
	ADD_STRINGVALUE( OB_SKILL_NONE,		"")

	ADD_STRINGVALUE( OB_SKILL_HANDTOHAND,	"Hand-to-Hand")
END_STRINGVALUE()
/*===========================================================================
 *		End of Skills
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Actor Values
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObActorValues)
	ADD_STRINGVALUE( OB_ACTORVALUE_STRENGTH,	"Strength")
	ADD_STRINGVALUE( OB_ACTORVALUE_INTELLIGENCE,	"Intelligence")
	ADD_STRINGVALUE( OB_ACTORVALUE_WILLPOWER,	"Willpower")
	ADD_STRINGVALUE( OB_ACTORVALUE_AGILITY,		"Agility")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEED,		"Speed")
	ADD_STRINGVALUE( OB_ACTORVALUE_ENDURANCE,	"Endurance")
	ADD_STRINGVALUE( OB_ACTORVALUE_PERSONALITY,	"Personality")
	ADD_STRINGVALUE( OB_ACTORVALUE_LUCK,		"Luck")
	ADD_STRINGVALUE( OB_ACTORVALUE_HEALTH,		"Health")
	ADD_STRINGVALUE( OB_ACTORVALUE_MAGICKA,		"Magicka")
	ADD_STRINGVALUE( OB_ACTORVALUE_FATIGUE,		"Fatigue")
	ADD_STRINGVALUE( OB_ACTORVALUE_ENCUMBRANCE,	"Encumbrance")
	ADD_STRINGVALUE( OB_ACTORVALUE_ARMORER,		"Armorer")
	ADD_STRINGVALUE( OB_ACTORVALUE_ATHLETICS,	"Athletics")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLADE,		"Blade")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLOCK,		"Block")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLUNT,		"Blunt")
	ADD_STRINGVALUE( OB_ACTORVALUE_HANDTOHAND,	"Hand to Hand")
	ADD_STRINGVALUE( OB_ACTORVALUE_HEAVYARMOR,	"Heavy Armor")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALCHEMY,		"Alchemy")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALTERATION,	"Alteration")
	ADD_STRINGVALUE( OB_ACTORVALUE_CONJURATION,	"Conjuration")
	ADD_STRINGVALUE( OB_ACTORVALUE_DESTRUCTION,	"Destruction")
	ADD_STRINGVALUE( OB_ACTORVALUE_ILLUSION,	"Illusion")
	ADD_STRINGVALUE( OB_ACTORVALUE_MYSTICISM,	"Mysticism")
	ADD_STRINGVALUE( OB_ACTORVALUE_RESTORATION,	"Restoration")
	ADD_STRINGVALUE( OB_ACTORVALUE_ACROBATICS,	"Acrobatics")
	ADD_STRINGVALUE( OB_ACTORVALUE_LIGHTARMOR,	"Light Armor")
	ADD_STRINGVALUE( OB_ACTORVALUE_MARKSMAN,	"Marksman")
	ADD_STRINGVALUE( OB_ACTORVALUE_MERCANTILE,	"Mercantile")
	ADD_STRINGVALUE( OB_ACTORVALUE_SECURITY,	"Security")
	ADD_STRINGVALUE( OB_ACTORVALUE_SNEAK,		"Sneak")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEECHCRAFT,	"Speechcraft")
END_STRINGVALUE()


BEGIN_STRINGVALUE(s_ObActorValueSkills)
	ADD_STRINGVALUE( OB_ACTORVALUE_ARMORER,		"Armorer")
	ADD_STRINGVALUE( OB_ACTORVALUE_ATHLETICS,	"Athletics")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLADE,		"Blade")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLOCK,		"Block")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLUNT,		"Blunt")
	ADD_STRINGVALUE( OB_ACTORVALUE_HANDTOHAND,	"Hand to Hand")
	ADD_STRINGVALUE( OB_ACTORVALUE_HEAVYARMOR,	"Heavy Armor")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALCHEMY,		"Alchemy")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALTERATION,	"Alteration")
	ADD_STRINGVALUE( OB_ACTORVALUE_CONJURATION,	"Conjuration")
	ADD_STRINGVALUE( OB_ACTORVALUE_DESTRUCTION,	"Destruction")
	ADD_STRINGVALUE( OB_ACTORVALUE_ILLUSION,	"Illusion")
	ADD_STRINGVALUE( OB_ACTORVALUE_MYSTICISM,	"Mysticism")
	ADD_STRINGVALUE( OB_ACTORVALUE_RESTORATION,	"Restoration")
	ADD_STRINGVALUE( OB_ACTORVALUE_ACROBATICS,	"Acrobatics")
	ADD_STRINGVALUE( OB_ACTORVALUE_LIGHTARMOR,	"Light Armor")
	ADD_STRINGVALUE( OB_ACTORVALUE_MARKSMAN,	"Marksman")
	ADD_STRINGVALUE( OB_ACTORVALUE_MERCANTILE,	"Mercantile")
	ADD_STRINGVALUE( OB_ACTORVALUE_SECURITY,	"Security")
	ADD_STRINGVALUE( OB_ACTORVALUE_SNEAK,		"Sneak")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEECHCRAFT,	"Speechcraft")
END_STRINGVALUE()


BEGIN_STRINGVALUE(s_ObActorValueAttributes)
	ADD_STRINGVALUE( OB_ACTORVALUE_STRENGTH,	"Strength")
	ADD_STRINGVALUE( OB_ACTORVALUE_INTELLIGENCE,	"Intelligence")
	ADD_STRINGVALUE( OB_ACTORVALUE_WILLPOWER,	"Willpower")
	ADD_STRINGVALUE( OB_ACTORVALUE_AGILITY,		"Agility")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEED,		"Speed")
	ADD_STRINGVALUE( OB_ACTORVALUE_ENDURANCE,	"Endurance")
	ADD_STRINGVALUE( OB_ACTORVALUE_PERSONALITY,	"Personality")
	ADD_STRINGVALUE( OB_ACTORVALUE_LUCK,		"Luck")
END_STRINGVALUE()


BEGIN_STRINGVALUE(s_ObScriptActorValues)
	ADD_STRINGVALUE( OB_ACTORVALUE_STRENGTH,	"Strength")
	ADD_STRINGVALUE( OB_ACTORVALUE_INTELLIGENCE,	"Intelligence")
	ADD_STRINGVALUE( OB_ACTORVALUE_WILLPOWER,	"Willpower")
	ADD_STRINGVALUE( OB_ACTORVALUE_AGILITY,		"Agility")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEED,		"Speed")
	ADD_STRINGVALUE( OB_ACTORVALUE_ENDURANCE,	"Endurance")
	ADD_STRINGVALUE( OB_ACTORVALUE_PERSONALITY,	"Personality")
	ADD_STRINGVALUE( OB_ACTORVALUE_LUCK,		"Luck")
	ADD_STRINGVALUE( OB_ACTORVALUE_HEALTH,		"Health")
	ADD_STRINGVALUE( OB_ACTORVALUE_MAGICKA,		"Magicka")
	ADD_STRINGVALUE( OB_ACTORVALUE_FATIGUE,		"Fatigue")
	ADD_STRINGVALUE( OB_ACTORVALUE_ENCUMBRANCE,	"Encumbrance")
	ADD_STRINGVALUE( OB_ACTORVALUE_ARMORER,		"Armorer")
	ADD_STRINGVALUE( OB_ACTORVALUE_ATHLETICS,	"Athletics")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLADE,		"Blade")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLOCK,		"Block")
	ADD_STRINGVALUE( OB_ACTORVALUE_BLUNT,		"Blunt")
	ADD_STRINGVALUE( OB_ACTORVALUE_HANDTOHAND,	"HandtoHand")
	ADD_STRINGVALUE( OB_ACTORVALUE_HEAVYARMOR,	"HeavyArmor")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALCHEMY,		"Alchemy")
	ADD_STRINGVALUE( OB_ACTORVALUE_ALTERATION,	"Alteration")
	ADD_STRINGVALUE( OB_ACTORVALUE_CONJURATION,	"Conjuration")
	ADD_STRINGVALUE( OB_ACTORVALUE_DESTRUCTION,	"Destruction")
	ADD_STRINGVALUE( OB_ACTORVALUE_ILLUSION,	"Illusion")
	ADD_STRINGVALUE( OB_ACTORVALUE_MYSTICISM,	"Mysticism")
	ADD_STRINGVALUE( OB_ACTORVALUE_RESTORATION,	"Restoration")
	ADD_STRINGVALUE( OB_ACTORVALUE_ACROBATICS,	"Acrobatics")
	ADD_STRINGVALUE( OB_ACTORVALUE_LIGHTARMOR,	"LightArmor")
	ADD_STRINGVALUE( OB_ACTORVALUE_MARKSMAN,	"Marksman")
	ADD_STRINGVALUE( OB_ACTORVALUE_MERCANTILE,	"Mercantile")
	ADD_STRINGVALUE( OB_ACTORVALUE_SECURITY,	"Security")
	ADD_STRINGVALUE( OB_ACTORVALUE_SNEAK,		"Sneak")
	ADD_STRINGVALUE( OB_ACTORVALUE_SPEECHCRAFT,	"Speechcraft")
	ADD_STRINGVALUE( OB_ACTORVALUE_AGRESSION,	"Aggression" )
	ADD_STRINGVALUE( OB_ACTORVALUE_CONFIDENCE,	"Confidence" )
	ADD_STRINGVALUE( OB_ACTORVALUE_ENERGY,		"Energy" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESPONSIBILITY,	"Responsibility" )
	ADD_STRINGVALUE( OB_ACTORVALUE_BOUNTY,		"Bounty" )
	ADD_STRINGVALUE( OB_ACTORVALUE_MAGICKAMULT,	"MagickaMultiplier" )
	ADD_STRINGVALUE( OB_ACTORVALUE_NIGHTEYE,	"NightEyeBonus" )
	ADD_STRINGVALUE( OB_ACTORVALUE_ATTACSKBONUS,	"AttackBonus" )
	ADD_STRINGVALUE( OB_ACTORVALUE_DEFENDBONUS,	"DefendBonus" )
	ADD_STRINGVALUE( OB_ACTORVALUE_CASTINGPENALTY,	"CastingPenalty" )
	ADD_STRINGVALUE( OB_ACTORVALUE_BLINDNESS,	"Blindness" )
	ADD_STRINGVALUE( OB_ACTORVALUE_CHAMELEON,	"Chameleon" )
	ADD_STRINGVALUE( OB_ACTORVALUE_INVISIBILITY,	"Invisibility" )
	ADD_STRINGVALUE( OB_ACTORVALUE_PARALYSIS,	"Paralysis" )
	ADD_STRINGVALUE( OB_ACTORVALUE_SILENCE,		"Silence" )
	ADD_STRINGVALUE( OB_ACTORVALUE_CONFUSION,	"Confusion" )
	ADD_STRINGVALUE( OB_ACTORVALUE_DETECTITEMRANGE,	"DetectItemRange" )
	ADD_STRINGVALUE( OB_ACTORVALUE_SPELLABSORBCHANCE,"SpellAbsorbChance" )
	ADD_STRINGVALUE( OB_ACTORVALUE_SPELLREFLECTCHANCE,"SpellReflectChance" )
	ADD_STRINGVALUE( OB_ACTORVALUE_SWIMSPEEDMULT,	"SwimSpeedMultiplier" )
	ADD_STRINGVALUE( OB_ACTORVALUE_WATERBREATHING,	"WaterBreathing" )
	ADD_STRINGVALUE( OB_ACTORVALUE_WATERWALKING,	"WaterWalking" )
	ADD_STRINGVALUE( OB_ACTORVALUE_STUNTEDMAGICKA,	"StuntedMagicka" )
	ADD_STRINGVALUE( OB_ACTORVALUE_DETECTLIFERANGE,	"DetectLifeRange" )
	ADD_STRINGVALUE( OB_ACTORVALUE_REFLECTDAMAGE,	"ReflectDamage" )
	ADD_STRINGVALUE( OB_ACTORVALUE_TELEKINESIS,	"Telekinesis" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTFIRE,	"ResistFire" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTFROST,	"ResistFrost" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTDISEASE,	"ResistDisease" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTMAGIC,	"ResistMagic" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTNORMALWEAP,"ResistNormalWeapons" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTPARALYSIS,	"ResistParalysis" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTPOISON,	"ResistPoison" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTSHOCK,	"ResistShock" )
	ADD_STRINGVALUE( OB_ACTORVALUE_VAMPIRISM,	"Vampirism" )
	ADD_STRINGVALUE( OB_ACTORVALUE_DARKNESS,	"Darkness" )
	ADD_STRINGVALUE( OB_ACTORVALUE_RESISTWATER,	"ResistWaterDamage" )
END_STRINGVALUE()
/*===========================================================================
 *		End of Actor Values
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Spell School Values
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObSpellSchoolValues)
	ADD_STRINGVALUE( OB_SCHOOL_ALTERATION,  "Alteration")
	ADD_STRINGVALUE( OB_SCHOOL_CONJURATION, "Conjuration")
	ADD_STRINGVALUE( OB_SCHOOL_DESTRUCTION, "Destruction")
	ADD_STRINGVALUE( OB_SCHOOL_ILLUSION,    "Illusion")
	ADD_STRINGVALUE( OB_SCHOOL_MYSTICISM,   "Mysticism")
	ADD_STRINGVALUE( OB_SCHOOL_RESTORATION, "Restoration")
END_STRINGVALUE()
/*===========================================================================
 *		End of Spell School Values
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Magic Effects
 *
 *=========================================================================*/
START_EFFECTVALUE(l_EffectData)	
	ADD_EFFECTVALUE( OB_MGEF_ABAT, "Absorb Attribute", 0x00103827 )
	ADD_EFFECTVALUE( OB_MGEF_ABFA, "Absorb Fatigue", 0x01003825 )
	ADD_EFFECTVALUE( OB_MGEF_ABHE, "Absorb Health", 0x01003825 )
	ADD_EFFECTVALUE( OB_MGEF_ABSK, "Absorb Skill", 0x00083827 )
	ADD_EFFECTVALUE( OB_MGEF_ABSP, "Absorb Magicka", 0x01003825 )
	ADD_EFFECTVALUE( OB_MGEF_BABO, "Bound Boots", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BACU, "Bound Cuirass", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BAGA, "Bound Gauntlets", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BAGR, "Bound Greaves", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BAHE, "Bound Helmet", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BASH, "Bound Shield", 0x00022912 )
	ADD_EFFECTVALUE( OB_MGEF_BRDN, "Burden", 0x01001C73 )
	ADD_EFFECTVALUE( OB_MGEF_BWAX, "Bound Axe", 0x00012912 )
	ADD_EFFECTVALUE( OB_MGEF_BWBO, "Bound Bow", 0x00012912 )
	ADD_EFFECTVALUE( OB_MGEF_BWDA, "Bound Dagger", 0x00012912 )
	ADD_EFFECTVALUE( OB_MGEF_BWMA, "Bound Mace", 0x00012912 )
	ADD_EFFECTVALUE( OB_MGEF_BWSW, "Bound Sword", 0x00012912 )
	ADD_EFFECTVALUE( OB_MGEF_CALM, "Calm", 0x01000C66 )
	ADD_EFFECTVALUE( OB_MGEF_CHML, "Chameleon", 0x0100187A )
	ADD_EFFECTVALUE( OB_MGEF_CHRM, "Charm", 0x01000C62 )
	ADD_EFFECTVALUE( OB_MGEF_COCR, "Command Creature", 0x40001C62 )
	ADD_EFFECTVALUE( OB_MGEF_COHU, "Command Humanoid", 0x40001C62 )
	ADD_EFFECTVALUE( OB_MGEF_CUDI, "Cure Disease", 0x000009F0 )
	ADD_EFFECTVALUE( OB_MGEF_CUPA, "Cure Paralysis", 0x000009F0 )
	ADD_EFFECTVALUE( OB_MGEF_CUPO, "Cure Poison", 0x000009F0 )
	ADD_EFFECTVALUE( OB_MGEF_DARK, "DO NOT USE - Darkness", 0x01000072 )
	ADD_EFFECTVALUE( OB_MGEF_DEMO, "Demoralize", 0x41001C66 )
	ADD_EFFECTVALUE( OB_MGEF_DGAT, "Damage Attribute", 0x00101C75 )
	ADD_EFFECTVALUE( OB_MGEF_DGFA, "Damage Fatigue", 0x01001C75 )
	ADD_EFFECTVALUE( OB_MGEF_DGHE, "Damage Health", 0x21001C75 )
	ADD_EFFECTVALUE( OB_MGEF_DGSP, "Damage Magicka", 0x01001475 )
	ADD_EFFECTVALUE( OB_MGEF_DIAR, "Disintegrate Armor", 0x00003C75 )
	ADD_EFFECTVALUE( OB_MGEF_DIWE, "Disintegrate Weapon", 0x00003C75 )
	ADD_EFFECTVALUE( OB_MGEF_DRAT, "Drain Attribute", 0x00101C77 )
	ADD_EFFECTVALUE( OB_MGEF_DRFA, "Drain Fatigue", 0x01001C77 )
	ADD_EFFECTVALUE( OB_MGEF_DRHE, "Drain Health", 0x01001C77 )
	ADD_EFFECTVALUE( OB_MGEF_DRSK, "Drain Skill", 0x00081C77 )
	ADD_EFFECTVALUE( OB_MGEF_DRSP, "Drain Magicka", 0x01001C77 )
	ADD_EFFECTVALUE( OB_MGEF_DSPL, "Dispel", 0x000018F0 )
	ADD_EFFECTVALUE( OB_MGEF_DTCT, "Detect Life", 0x81001812 )
	ADD_EFFECTVALUE( OB_MGEF_FIDG, "Fire Damage", 0x21001C75 )
	ADD_EFFECTVALUE( OB_MGEF_FISH, "Fire Shield", 0x01001C7A )
	ADD_EFFECTVALUE( OB_MGEF_FOAT, "Fortify Attribute", 0x00101C72 )
	ADD_EFFECTVALUE( OB_MGEF_FOFA, "Fortify Fatigue", 0x01001C72 )
	ADD_EFFECTVALUE( OB_MGEF_FOHE, "Fortify Health", 0x01001C72 )
	ADD_EFFECTVALUE( OB_MGEF_FOMM, "Fortify Magicka Multiplier", 0x01002412 )
	ADD_EFFECTVALUE( OB_MGEF_FOSK, "Fortify Skill", 0x00081C72 )
	ADD_EFFECTVALUE( OB_MGEF_FOSP, "Fortify Magicka", 0x01001C72 )
	ADD_EFFECTVALUE( OB_MGEF_FRDG, "Frost Damage", 0x07001C75 )
	ADD_EFFECTVALUE( OB_MGEF_FRNZ, "Frenzy", 0x01001C62 )
	ADD_EFFECTVALUE( OB_MGEF_FRSH, "Frost Shield", 0x01001C7A )
	ADD_EFFECTVALUE( OB_MGEF_FTHR, "Feather", 0x01001876 )
	ADD_EFFECTVALUE( OB_MGEF_INVI, "Invisibility", 0x01000972 )
	ADD_EFFECTVALUE( OB_MGEF_LGHT, "Light", 0x80001872 )
	ADD_EFFECTVALUE( OB_MGEF_LISH, "Shock Shield", 0x01001C7A )
	ADD_EFFECTVALUE( OB_MGEF_LOCK, "DO NOT USE - Lock", 0x000038E0 )
	ADD_EFFECTVALUE( OB_MGEF_MYHL, "Summon Mythic Dawn Helm", 0x00022112 )
	ADD_EFFECTVALUE( OB_MGEF_MYTH, "Summon Mythic Dawn Armor", 0x00022112 )
	ADD_EFFECTVALUE( OB_MGEF_NEYE, "Night-Eye", 0x01001912 )
	ADD_EFFECTVALUE( OB_MGEF_OPEN, "Open", 0x000038C0 )
	ADD_EFFECTVALUE( OB_MGEF_PARA, "Paralyze", 0x01000D73 )
	ADD_EFFECTVALUE( OB_MGEF_POSN, "Poison Info", 0x00800000 )
	ADD_EFFECTVALUE( OB_MGEF_RALY, "Rally", 0x01001C62 )
	ADD_EFFECTVALUE( OB_MGEF_REAN, "Reanimate", 0x10020760 )
	ADD_EFFECTVALUE( OB_MGEF_REAT, "Restore Attribute", 0x00100870 )
	ADD_EFFECTVALUE( OB_MGEF_REDG, "Reflect Damage", 0x01000C1A )
	ADD_EFFECTVALUE( OB_MGEF_REFA, "Restore Fatigue", 0x01000870 )
	ADD_EFFECTVALUE( OB_MGEF_REHE, "Restore Health", 0x01000870 )
	ADD_EFFECTVALUE( OB_MGEF_RESP, "Restore Magicka", 0x01000870 )
	ADD_EFFECTVALUE( OB_MGEF_RFLC, "Reflect Spell", 0x0100087A )
	ADD_EFFECTVALUE( OB_MGEF_RSDI, "Resist Disease", 0x0100187A )
	ADD_EFFECTVALUE( OB_MGEF_RSFI, "Resist Fire", 0x01001872 )
	ADD_EFFECTVALUE( OB_MGEF_RSFR, "Resist Frost", 0x01001872 )
	ADD_EFFECTVALUE( OB_MGEF_RSMA, "Resist Magic", 0x0100087A )
	ADD_EFFECTVALUE( OB_MGEF_RSNW, "Resist Normal Weapons", 0x0100047A )
	ADD_EFFECTVALUE( OB_MGEF_RSPA, "Resist Paralysis", 0x01001872 )
	ADD_EFFECTVALUE( OB_MGEF_RSPO, "Resist Poison", 0x0100187A )
	ADD_EFFECTVALUE( OB_MGEF_RSSH, "Resist Shock", 0x01001872 )
	ADD_EFFECTVALUE( OB_MGEF_SABS, "Spell Absorption", 0x01000872 )
	ADD_EFFECTVALUE( OB_MGEF_SEFF, "Script Effect", 0x00002170 | OB_EFFECTFLAG_SPELLMAKING | OB_EFFECTFLAG_ENCHANTING )
	ADD_EFFECTVALUE( OB_MGEF_SHDG, "Shock Damage", 0x25001C75 )
	ADD_EFFECTVALUE( OB_MGEF_SHLD, "Shield", 0x01001C7A )
	ADD_EFFECTVALUE( OB_MGEF_SLNC, "Silence", 0x01001D73 )
	ADD_EFFECTVALUE( OB_MGEF_STMA, "Stunted Magicka", 0x01002112 )
	ADD_EFFECTVALUE( OB_MGEF_STRP, "Soul Trap", 0x00003D63 )
	ADD_EFFECTVALUE( OB_MGEF_SUDG, "Sun Damage", 0x00002014 )
	ADD_EFFECTVALUE( OB_MGEF_TELE, "Telekinesis", 0x89000A42 )
	ADD_EFFECTVALUE( OB_MGEF_TURN, "Turn Undead", 0x00001C63 )
	ADD_EFFECTVALUE( OB_MGEF_VAMP, "Vampirism", 0x00002092 )
	ADD_EFFECTVALUE( OB_MGEF_WABR, "Water Breathing", 0x01001972 )
	ADD_EFFECTVALUE( OB_MGEF_WAWA, "Water Walking", 0x01001972 )
	ADD_EFFECTVALUE( OB_MGEF_WKDI, "Weakness to Disease", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKFI, "Weakness to Fire", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKFR, "Weakness to Frost", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKMA, "Weakness to Magic", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKNW, "Weakness to Normal Weapons", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKPO, "Weakness to Poison", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_WKSH, "Weakness to Shock", 0x01001C7F )
	ADD_EFFECTVALUE( OB_MGEF_Z001, "Summon Rufio's Ghost", 0x00042112 )
	ADD_EFFECTVALUE( OB_MGEF_Z002, "Summon Ancestor Guardian", 0x00042112 )
	ADD_EFFECTVALUE( OB_MGEF_Z003, "Summon Spiderling", 0x00042112 )
	ADD_EFFECTVALUE( OB_MGEF_Z004, "Summon 04 Extra", 0x00042112 )
	ADD_EFFECTVALUE( OB_MGEF_Z005, "Summon Bear", 0x00042112 )
	ADD_EFFECTVALUE( OB_MGEF_ZCLA, "Summon Clannfear", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZDAE, "Summon Daedroth", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZDRE, "Summon Dremora", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZDRL, "Summon Dremora Lord", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZFIA, "Summon Flame Atronach", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZFRA, "Summon Frost Atronach", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZGHO, "Summon Ghost", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZHDZ, "Summon Headless Zombie", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZLIC, "Summon Lich", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSCA, "Summon Scamp", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSKA, "Summon Skeleton Guardian", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSKC, "Summon Skeleton Champion", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSKE, "Summon Skeleton", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSKH, "Summon Skeleton Hero", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSPD, "Summon Spider Daedra", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZSTA, "Summon Storm Atronach", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZWRA, "Summon Faded Wraith", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZWRL, "Summon Gloom Wraith", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZXIV, "Summon Xivilai", 0x00042912 )
	ADD_EFFECTVALUE( OB_MGEF_ZZOM, "Summon Zombie", 0x00042912 )
END_EFFECTVALUE()
/*===========================================================================
 *		End of Magic Effects
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Light Types
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObLightTypes)
	ADD_STRINGVALUE( OB_LIGHTYPE_FLICKER,		"Flicker")
	ADD_STRINGVALUE( OB_LIGHTYPE_FLICKERSLOW,	"Flicker Slow")
	ADD_STRINGVALUE( OB_LIGHTYPE_FLICKERSLOW,	"FlickerSlow")
	ADD_STRINGVALUE( OB_LIGHTYPE_PULSE,		"Pulse")
	ADD_STRINGVALUE( OB_LIGHTYPE_PULSESLOW,		"Pulse Slow")
	ADD_STRINGVALUE( OB_LIGHTYPE_PULSESLOW,		"PulseSlow")
	ADD_STRINGVALUE( OB_LIGHTYPE_NONE,		"None")
	ADD_STRINGVALUE( OB_LIGHTYPE_NONE,		"")
END_STRINGVALUE()
/*===========================================================================
 *		End of Light Types
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchant Types String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObEnchantTypes)
	ADD_STRINGVALUE( OB_ENCHTYPE_SCROLL,	"Scroll")
	ADD_STRINGVALUE( OB_ENCHTYPE_STAFF,	"Staff")
	ADD_STRINGVALUE( OB_ENCHTYPE_WEAPON,	"Weapon")
	ADD_STRINGVALUE( OB_ENCHTYPE_APPAREL,	"Apparel")
END_STRINGVALUE()
/*===========================================================================
 *		End of Enchant Types String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Enchant Range Types String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObEnchantRangeTypes)
	ADD_STRINGVALUE( OB_EFFECTTYPE_SELF,	"Self")
	ADD_STRINGVALUE( OB_EFFECTTYPE_TOUCH,	"Touch")
	ADD_STRINGVALUE( OB_EFFECTTYPE_TARGET,	"Target")
END_STRINGVALUE()
/*===========================================================================
 *		End of Enchant Range Types String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Apparatus Type String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObApparatusTypes)
	ADD_STRINGVALUE( OB_APPATYPE_MORTAR,	 "Mortar")
	ADD_STRINGVALUE( OB_APPATYPE_ALEMBIC,	 "Alembic")
	ADD_STRINGVALUE( OB_APPATYPE_CALCINATOR, "Calcinator")
	ADD_STRINGVALUE( OB_APPATYPE_RETORT,	 "Retort")
END_STRINGVALUE()
/*===========================================================================
 *		End of Apparatus Type String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Map Marker String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObMapMarkerTypes)
	ADD_STRINGVALUE( OB_MAPMARKER_NONE,		"None")
	ADD_STRINGVALUE( OB_MAPMARKER_CAMP,		"Camp")
	ADD_STRINGVALUE( OB_MAPMARKER_CAVE,		"Cave")
	ADD_STRINGVALUE( OB_MAPMARKER_CITY,		"City")
	ADD_STRINGVALUE( OB_MAPMARKER_ELVENRUIN,	"Elven Ruin")
	ADD_STRINGVALUE( OB_MAPMARKER_FORTRUIN,		"Fort Ruin")
	ADD_STRINGVALUE( OB_MAPMARKER_MINE,		"Mine")
	ADD_STRINGVALUE( OB_MAPMARKER_LANDMARK,		"Landmark")
	ADD_STRINGVALUE( OB_MAPMARKER_TAVERN,		"Tavern")
	ADD_STRINGVALUE( OB_MAPMARKER_STABLE,		"Stable")
	ADD_STRINGVALUE( OB_MAPMARKER_SETTLEMENT,	"Settlement")
	ADD_STRINGVALUE( OB_MAPMARKER_DAEDRICSHRINE,	"Daedric Shrine")
	ADD_STRINGVALUE( OB_MAPMARKER_OBLIVIONGATE,	"Oblivion Gate")
	ADD_STRINGVALUE( OB_MAPMARKER_UNKNOWN,		"Unknown")
END_STRINGVALUE()
/*===========================================================================
 *		End of Map Marker String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Spell Type String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObSpellTypes)
	ADD_STRINGVALUE( OB_SPELLTYPE_SPELL,	  "Spell")
	ADD_STRINGVALUE( OB_SPELLTYPE_DISEASE,	  "Disease")
	ADD_STRINGVALUE( OB_SPELLTYPE_POWER,	  "Power")
	ADD_STRINGVALUE( OB_SPELLTYPE_LESSERPOWER, "Lesser Power")
	ADD_STRINGVALUE( OB_SPELLTYPE_ABILITY,    "Ability")
	ADD_STRINGVALUE( OB_SPELLTYPE_POISON,	  "Poison")
END_STRINGVALUE()
/*===========================================================================
 *		End of Spell Type String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Spell Level String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObSpellLevels)
	ADD_STRINGVALUE( OB_SPELLEVEL_NOVICE,	  "Novice")
	ADD_STRINGVALUE( OB_SPELLEVEL_APPRENTICE, "Apprentice")
	ADD_STRINGVALUE( OB_SPELLEVEL_JOURNEYMAN, "Journeyman")
	ADD_STRINGVALUE( OB_SPELLEVEL_EXPERT,	  "Expert")
	ADD_STRINGVALUE( OB_SPELLEVEL_MASTER,	  "Master")
END_STRINGVALUE()
/*===========================================================================
 *		End of Spell Level Stirng Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Soul Gem String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObSoulGems)
	ADD_STRINGVALUE( OB_SOULGEM_PETTY,    "Petty")
	ADD_STRINGVALUE( OB_SOULGEM_LESSER,   "Lesser")
	ADD_STRINGVALUE( OB_SOULGEM_COMMON,   "Common")
	ADD_STRINGVALUE( OB_SOULGEM_GREATER,  "Greater")
	ADD_STRINGVALUE( OB_SOULGEM_GRAND,    "Grand")
END_STRINGVALUE()


BEGIN_STRINGVALUE(s_ObSoulGemsNone)
	ADD_STRINGVALUE( OB_SOULGEM_NONE,     "None")
	ADD_STRINGVALUE( OB_SOULGEM_PETTY,    "Petty")
	ADD_STRINGVALUE( OB_SOULGEM_LESSER,   "Lesser")
	ADD_STRINGVALUE( OB_SOULGEM_COMMON,   "Common")
	ADD_STRINGVALUE( OB_SOULGEM_GREATER,  "Greater")
	ADD_STRINGVALUE( OB_SOULGEM_GRAND,    "Grand")
END_STRINGVALUE()
/*===========================================================================
 *		End of Soul Gem String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Weapon Type String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObWeaponTypes)
	ADD_STRINGVALUE( OB_WEAPTYPE_BLADEONEHAND,	"Blade One Hand")
	ADD_STRINGVALUE( OB_WEAPTYPE_BLADETWOHAND,	"Blade Two Hand")
	ADD_STRINGVALUE( OB_WEAPTYPE_BLUNTONEHAND,	"Blunt One Hand")
	ADD_STRINGVALUE( OB_WEAPTYPE_BLUNTTWOHAND,	"Blunt Two Hand")
	ADD_STRINGVALUE( OB_WEAPTYPE_STAFF,		"Staff")
	ADD_STRINGVALUE( OB_WEAPTYPE_BOW,		"Bow")
END_STRINGVALUE()
/*===========================================================================
 *		End of Weapon Type String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Animation Group String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObAnimationGroups)
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKBACKPOWER,    "AttackBackPower" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKBOW,          "AttackBow" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKFORWARDPOWER, "AttackForwardPower" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKLEFT,         "AttackLeft" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKLEFTPOWER,    "AttackLeftPower" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKPOWER,        "AttackPower" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKRIGHT,        "AttackRight" )
	ADD_STRINGVALUE( OB_ANIMGROUP_ATTACKRIGHTPOWER,   "AttackRightPower" )
	ADD_STRINGVALUE( OB_ANIMGROUP_BACKWARD,           "Backward" )
	ADD_STRINGVALUE( OB_ANIMGROUP_BLOCKATTACK,        "BlockAttack" )
	ADD_STRINGVALUE( OB_ANIMGROUP_BLOCKHIT,           "BlockHit" )
	ADD_STRINGVALUE( OB_ANIMGROUP_BLOCKIDLE,          "BlockIdle" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTSELF,           "CastSelf" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTSELFALT,        "CastSelfAlt" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTTARGET,         "CastTarget" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTTARGETALT,      "CastTargetAlt" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTTOUCH,          "CastTouch" )
	ADD_STRINGVALUE( OB_ANIMGROUP_CASTTOUCHALT,       "CastTouchAlt" )
	ADD_STRINGVALUE( OB_ANIMGROUP_DODGEBACK,          "DodgeBack" )
	ADD_STRINGVALUE( OB_ANIMGROUP_DODGEFORWARD,       "DodgeForward" )
	ADD_STRINGVALUE( OB_ANIMGROUP_DODGELEFT,          "DodgeLeft" )
	ADD_STRINGVALUE( OB_ANIMGROUP_DODGERIGHT,         "DodgeRight" )
	ADD_STRINGVALUE( OB_ANIMGROUP_DYNAMICIDLE,        "DynamicIdle" )
	ADD_STRINGVALUE( OB_ANIMGROUP_EQUIP,              "Equip" )
	ADD_STRINGVALUE( OB_ANIMGROUP_FASTBACKWARD,       "FastBackward" )
	ADD_STRINGVALUE( OB_ANIMGROUP_FASTFORWARD,        "FastForward" )
	ADD_STRINGVALUE( OB_ANIMGROUP_FASTLEFT,           "FastLeft" )
	ADD_STRINGVALUE( OB_ANIMGROUP_FASTRIGHT,          "FastRight" )
	ADD_STRINGVALUE( OB_ANIMGROUP_FORWARD,            "Forward" )
	ADD_STRINGVALUE( OB_ANIMGROUP_IDLE,               "Idle" )
	ADD_STRINGVALUE( OB_ANIMGROUP_JUMPLAND,           "JumpLand" )
	ADD_STRINGVALUE( OB_ANIMGROUP_JUMPLOOP,           "JumpLoop" )
	ADD_STRINGVALUE( OB_ANIMGROUP_JUMPSTART,          "JumpStart" )
	ADD_STRINGVALUE( OB_ANIMGROUP_LEFT,               "Left" )
	ADD_STRINGVALUE( OB_ANIMGROUP_RECOIL,             "Recoil" )
	ADD_STRINGVALUE( OB_ANIMGROUP_RIGHT,              "Right" )
	ADD_STRINGVALUE( OB_ANIMGROUP_SPECIALIDLE,        "SpecialIdle" )
	ADD_STRINGVALUE( OB_ANIMGROUP_STAGGER,            "Stagger" )
	ADD_STRINGVALUE( OB_ANIMGROUP_TORCHIDLE,          "TorchIdle" )
	ADD_STRINGVALUE( OB_ANIMGROUP_TURNLEFT,           "TurnLeft" )
	ADD_STRINGVALUE( OB_ANIMGROUP_TURNRIGHT,          "TurnRight" )
	ADD_STRINGVALUE( OB_ANIMGROUP_UNEQUIP,            "Unequip" )
END_STRINGVALUE()
/*===========================================================================
 *		End of Animation Group String Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Form Types String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObFormTypes)
	ADD_STRINGVALUE( OB_FORMTYPE_ACTIVATOR,       "Activator" )
	ADD_STRINGVALUE( OB_FORMTYPE_AMMO,            "Ammo" )
	ADD_STRINGVALUE( OB_FORMTYPE_ANIMOBJECT,      "AnimObject" )
	ADD_STRINGVALUE( OB_FORMTYPE_APPARATUS,       "Apparatus" )
	ADD_STRINGVALUE( OB_FORMTYPE_ARMOR,           "Armor" )
	ADD_STRINGVALUE( OB_FORMTYPE_BOOK,            "Book" )
	ADD_STRINGVALUE( OB_FORMTYPE_CLOTHING,        "Clothing" )
	ADD_STRINGVALUE( OB_FORMTYPE_COMBATSTYLE,     "CombatStyle" )
	ADD_STRINGVALUE( OB_FORMTYPE_CONTAINER,       "Container" )
	ADD_STRINGVALUE( OB_FORMTYPE_CREATURE,        "Creature" )
	ADD_STRINGVALUE( OB_FORMTYPE_DOOR,            "Door" )
	ADD_STRINGVALUE( OB_FORMTYPE_EFFECTSHADER,    "EffectShader" )
	ADD_STRINGVALUE( OB_FORMTYPE_ENCHANTMENT,     "Enchantment" )
	ADD_STRINGVALUE( OB_FORMTYPE_FLORA,           "Flora" )
	ADD_STRINGVALUE( OB_FORMTYPE_FURNITURE,       "Furniture" )
	ADD_STRINGVALUE( OB_FORMTYPE_GRASS,           "Grass" )
	ADD_STRINGVALUE( OB_FORMTYPE_INGREDIENT,      "Ingredient" )
	ADD_STRINGVALUE( OB_FORMTYPE_KEY,             "Key" )
	ADD_STRINGVALUE( OB_FORMTYPE_LANDTEXTURE,     "LandTexture" )
	ADD_STRINGVALUE( OB_FORMTYPE_LEVELEDCREATURE, "LeveledCreature" )
	ADD_STRINGVALUE( OB_FORMTYPE_LEVELEDITEM,     "LeveledItem" )
	ADD_STRINGVALUE( OB_FORMTYPE_LEVELEDSPELL,    "LeveledSpell" )
	ADD_STRINGVALUE( OB_FORMTYPE_LIGHT,           "Light" )
	ADD_STRINGVALUE( OB_FORMTYPE_LOADSCREEN,      "LoadScreen" )
	ADD_STRINGVALUE( OB_FORMTYPE_MISCITEM,        "MiscItem" )
	ADD_STRINGVALUE( OB_FORMTYPE_NPC,             "NPC" )
	ADD_STRINGVALUE( OB_FORMTYPE_POTION,          "Potion" )
	ADD_STRINGVALUE( OB_FORMTYPE_SIGILSTONE,      "SigilStone" )
	ADD_STRINGVALUE( OB_FORMTYPE_SOULGEM,         "SoulGem" )
	ADD_STRINGVALUE( OB_FORMTYPE_SOUND,           "Sound" )
	ADD_STRINGVALUE( OB_FORMTYPE_SPELL,           "Spell" )
	ADD_STRINGVALUE( OB_FORMTYPE_STATIC,          "Static" )
	ADD_STRINGVALUE( OB_FORMTYPE_SUBSPACE,        "SubSpace" )
	ADD_STRINGVALUE( OB_FORMTYPE_TREE,            "Tree" )
	ADD_STRINGVALUE( OB_FORMTYPE_WATERTYPE,       "WaterType" )
	ADD_STRINGVALUE( OB_FORMTYPE_WEAPON,          "Weapon" )
END_STRINGVALUE()
/*===========================================================================
 *		End of Form Types Table
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Crime Types String Table
 *
 *=========================================================================*/
BEGIN_STRINGVALUE(s_ObCrimeTypes)
	ADD_STRINGVALUE( OB_CRIMETYPE_STEAL,      "Steal" )
	ADD_STRINGVALUE( OB_CRIMETYPE_PICKPOCKET, "PickPocket" )
	ADD_STRINGVALUE( OB_CRIMETYPE_TRESPASS,   "Trespass" )
	ADD_STRINGVALUE( OB_CRIMETYPE_ATTACK,     "Attack" )
	ADD_STRINGVALUE( OB_CRIMETYPE_MURDER,     "Murder" )
END_STRINGVALUE()
/*===========================================================================
 *		End of Crime Types Table
 *=========================================================================*/


/*===========================================================================
 *
 * Get String from a Value Functions
 *
 *=========================================================================*/
#if !OB_USESTRINGVALUEMAP
const SSCHAR* GetObBipedFlagString        (const int Value) { return FindStringValue(Value, s_ObBipedFlags); }
const SSCHAR* GetObSkillString            (const int Value) { return FindStringValue(Value, s_ObSkills); }
const SSCHAR* GetObAttributeString        (const int Value) { return FindStringValue(Value, s_ObAttributes); }
const SSCHAR* GetObActorValueString       (const int Value) { return FindStringValue(Value, s_ObActorValues); }
const SSCHAR* GetObScriptActorValueString (const int Value) { return FindStringValue(Value, s_ObScriptActorValues); }
const SSCHAR* GetObSpellSchoolString      (const int Value) { return FindStringValue(Value, s_ObSpellSchoolValues); }
const SSCHAR* GetObEnchantTypeString      (const int Value) { return FindStringValue(Value, s_ObEnchantTypes); }
const SSCHAR* GetObEnchantRangeString     (const int Value) { return FindStringValue(Value, s_ObEnchantRangeTypes); }
const SSCHAR* GetObLightTypeString        (const int Value) { return FindStringValue(Value, s_ObLightTypes); }
const SSCHAR* GetObApparatusTypeString    (const int Value) { return FindStringValue(Value, s_ObApparatusTypes); }
const SSCHAR* GetObMapMarkerTypeString    (const int Value) { return FindStringValue(Value, s_ObMapMarkerTypes); }
const SSCHAR* GetObSpellTypeString        (const int Value) { return FindStringValue(Value, s_ObSpellTypes);  }
const SSCHAR* GetObSpellLevelString       (const int Value) { return FindStringValue(Value, s_ObSpellLevels);  }
const SSCHAR* GetObSoulGemString          (const int Value) { return FindStringValue(Value, s_ObSoulGemsNone);  }
const SSCHAR* GetObWeaponTypeString       (const int Value) { return FindStringValue(Value, s_ObWeaponTypes);  }
const SSCHAR* GetObAnimationGroupString   (const int Value) { return FindStringValue(Value, s_ObAnimationGroups);  }
const SSCHAR* GetObFormTypeString         (const int Value) { return FindStringValue(Value, s_ObFormTypes);  }
const SSCHAR* GetObCrimeTypeString        (const int Value) { return FindStringValue(Value, s_ObCrimeTypes);  }

#else

const SSCHAR* GetObBipedFlagString        (const int Value) { return s_ObBipedFlagsMap.FindValue(Value); }
const SSCHAR* GetObSkillString            (const int Value) { return s_ObSkillsMap.FindValue(Value);  }
const SSCHAR* GetObAttributeString        (const int Value) { return s_ObAttributesMap.FindValue(Value);  }
const SSCHAR* GetObActorValueString       (const int Value) { return s_ObActorValuesMap.FindValue(Value);  }
const SSCHAR* GetObScriptActorValueString (const int Value) { return s_ObScriptActorValuesMap.FindValue(Value);  }
const SSCHAR* GetObSpellSchoolString      (const int Value) { return s_ObSpellSchoolValuesMap.FindValue(Value);  }
const SSCHAR* GetObEnchantTypeString      (const int Value) { return s_ObEnchantTypesMap.FindValue(Value); }
const SSCHAR* GetObEnchantRangeString     (const int Value) { return s_ObEnchantRangeTypesMap.FindValue(Value); }
const SSCHAR* GetObLightTypeString        (const int Value) { return s_ObLightTypesMap.FindValue(Value); }
const SSCHAR* GetObApparatusTypeString    (const int Value) { return s_ObApparatusTypesMap.FindValue(Value); }
const SSCHAR* GetObMapMarkerTypeString    (const int Value) { return s_ObMapMarkerTypesMap.FindValue(Value); }
const SSCHAR* GetObSpellTypeString        (const int Value) { return s_ObSpellTypesMap.FindValue(Value);  }
const SSCHAR* GetObSpellLevelString       (const int Value) { return s_ObSpellLevelsMap.FindValue(Value);  }
const SSCHAR* GetObSoulGemString          (const int Value) { return s_ObSoulGemsNoneMap.FindValue(Value);  }
const SSCHAR* GetObWeaponTypeString       (const int Value) { return s_ObWeaponTypesMap.FindValue(Value);  }
const SSCHAR* GetObAnimationGroupString   (const int Value) { return s_ObAnimationGroupsMap.FindValue(Value);  }
const SSCHAR* GetObFormTypeString         (const int Value) { return s_ObFormTypesMap.FindValue(Value);  }
const SSCHAR* GetObCrimeTypeString        (const int Value) { return s_ObCrimeTypesMap.FindValue(Value);  }

#endif
/*===========================================================================
 *		End of Get String Functions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Get a Value from a String
 *
 *=========================================================================*/
#if !OB_USESTRINGVALUEMAP
bool GetObBipedFlagValue        (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObBipedFlags); }
bool GetObSkillValue            (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObSkills); }
bool GetObAttributeValue        (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObAttributes); }
bool GetObActorValueValue       (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObActorValues); }
bool GetObScriptActorValueValue (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObScriptActorValues); }
bool GetObSpellSchoolValue      (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObSpellSchoolValues); }
bool GetObEnchantTypeValue      (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObEnchantTypes); }
bool GetObEnchantRangeValue     (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObEnchantRangeTypes); }
bool GetObLightTypeValue        (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObLightTypes); }
bool GetObApparatusTypeValue    (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObApparatusTypes); }
bool GetObMapMarkerTypeValue    (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObMapMarkerTypes); }
bool GetObSpellTypeValue        (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObSpellTypes);  }
bool GetObSpellLevelValue       (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObSpellLevels);  }
bool GetObSoulGemValue          (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObSoulGemsNone);  }
bool GetObWeaponTypeValue       (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObWeaponTypes);  }
bool GetObAnimationGroupValue   (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObAnimationGroups);  }
bool GetObFormTypeValue         (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObFormTypes);  }
bool GetObCrimeTypeValue        (int& Value, const SSCHAR* pString) { return FindStringValue(Value, pString, s_ObCrimeTypes);  }

#else

bool GetObBipedFlagValue        (int& Value, const SSCHAR* pString) { return s_ObBipedFlagsMap.FindString(Value, pString); }
bool GetObSkillValue            (int& Value, const SSCHAR* pString) { return s_ObSkillsMap.FindString(Value, pString); }
bool GetObAttributeValue        (int& Value, const SSCHAR* pString) { return s_ObAttributesMap.FindString(Value, pString); }
bool GetObActorValueValue       (int& Value, const SSCHAR* pString) { return s_ObActorValuesMap.FindString(Value, pString); }
bool GetObScriptActorValueValue (int& Value, const SSCHAR* pString) { return s_ObScriptActorValuesMap.FindString(Value, pString); }
bool GetObSpellSchoolValue      (int& Value, const SSCHAR* pString) { return s_ObSpellSchoolValuesMap.FindString(Value, pString); }
bool GetObEnchantTypeValue      (int& Value, const SSCHAR* pString) { return s_ObEnchantTypesMap.FindString(Value, pString); }
bool GetObEnchantRangeValue     (int& Value, const SSCHAR* pString) { return s_ObEnchantRangeTypesMap.FindString(Value, pString); }
bool GetObLightTypeValue        (int& Value, const SSCHAR* pString) { return s_ObLightTypesMap.FindString(Value, pString); }
bool GetObApparatusTypeValue    (int& Value, const SSCHAR* pString) { return s_ObApparatusTypesMap.FindString(Value, pString); }
bool GetObMapMarkerTypeValue    (int& Value, const SSCHAR* pString) { return s_ObMapMarkerTypesMap.FindString(Value, pString); }
bool GetObSpellTypeValue        (int& Value, const SSCHAR* pString) { return s_ObSpellTypesMap.FindString(Value, pString);  }
bool GetObSpellLevelValue       (int& Value, const SSCHAR* pString) { return s_ObSpellLevelsMap.FindString(Value, pString);  }
bool GetObSoulGemValue          (int& Value, const SSCHAR* pString) { return s_ObSoulGemsNoneMap.FindString(Value, pString);  }
bool GetObWeaponTypeValue       (int& Value, const SSCHAR* pString) { return s_ObWeaponTypesMap.FindString(Value, pString);  }
bool GetObAnimationGroupValue   (int& Value, const SSCHAR* pString) { return s_ObAnimationGroupsMap.FindString(Value, pString);  }
bool GetObFormTypeValue         (int& Value, const SSCHAR* pString) { return s_ObFormTypesMap.FindString(Value, pString);  }
bool GetObCrimeTypeValue        (int& Value, const SSCHAR* pString) { return s_ObCrimeTypesMap.FindString(Value, pString);  }

#endif
/*===========================================================================
 *		End of Get a Value from a String
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const obeffectdata_t* FindObEffectData (pString);
 *
 * Finds the record with the given effect ID or NULL.
 *
 *=========================================================================*/
const obeffectdata_t* FindObEffectData (const SSCHAR* pString) {
  dword Index;

  for (Index = 0; l_EffectData[Index].pName != NULL; ++Index) {
    if (*l_EffectData[Index].pName == pString) return (&l_EffectData[Index]);
   }

  return (NULL);
 }
/*===========================================================================
 *		End of Function FindObEffectData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObFixupFormid (OutputFormID, OrigFormID, FixupArray);
 *
 *=========================================================================*/
bool ObFixupFormid (obformid_t& OutputFormID, const obformid_t OrigFormID, CObFormidFixupArray& FixupArray) {
  dword OldModIndex;
  dword NewModIndex;

	/* Special case for the NULL formid */
  if (OrigFormID == OB_FORMID_NULL) {
    OutputFormID = OB_FORMID_NULL;
    return (true);
  }

  OldModIndex = OB_GETMODINDEX(OrigFormID);
  
  if (!FixupArray.IsValidIndex(OldModIndex)) {
    AddObGeneralError("Modindex of form 0x%08X is not valid (must be 0-%d)!", OrigFormID, FixupArray.GetSize()-1);
    return (false);
  }
  
  NewModIndex  = FixupArray[OldModIndex];
  OutputFormID = OB_MAKEFORMID(OrigFormID, NewModIndex);
  return (true);
}
/*===========================================================================
 *		End of Function ObFixupFormid()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void MakeObBipedFlagString (Buffer, Flag);
 *
 * Makes a complete Biped flag string of the form:
 *
 *	Upper Body | Lower Body
 *
 *=========================================================================*/
void MakeObBipedFlagString (CSString& Buffer, const dword Flag) { 
  MakeObBipedFlagString(Buffer, Flag, " | ");
}
/*===========================================================================
 *		End of Function MakeObBipedFlagString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - void MakeObBipedFlagString (Buffer, Flag, pDivString);
 *
 * Makes a complete Biped flag string of each part seperated by the
 * given string.
 *
 *=========================================================================*/
void MakeObBipedFlagString (CSString& Buffer, const dword Flag, const SSCHAR* pDivString) { 
  dword Index;

  Buffer.Empty();
  if (pDivString == NULL) pDivString = ", ";

  for (Index = 0; s_ObMakeBipedFlags[Index].pString != NULL; ++Index) {

    if ((Flag & s_ObMakeBipedFlags[Index].Value) != 0) {
      if (!Buffer.IsEmpty()) Buffer += pDivString;
      Buffer += s_ObMakeBipedFlags[Index].pString;
     }
   }
  
 }
/*===========================================================================
 *		End of Function MakeObBipedFlagString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ObFindData (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindData (const byte* pData, const dword Size, obfinddata_t& FindData) {
  if ((FindData.Flags & OB_FIND_CASESENSITIVE) != 0) return ObFindDataCase(pData, Size, FindData);
  return ObFindDataNoCase(pData, Size, FindData); 
}
/*===========================================================================
 *		End of Function ObFindData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ObFindTextData (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindTextData (const byte* pData, const dword Size, obfinddata_t& FindData) {
  if ((FindData.Flags & OB_FIND_CASESENSITIVE) != 0) return ObFindTextDataCase(pData, Size, FindData);
  return ObFindTextDataNoCase(pData, Size, FindData); 
}
/*===========================================================================
 *		End of Function ObFindTextData()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - dword ObFindDataNoCase (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindDataNoCase (const byte* pData, const dword Size, obfinddata_t& FindData) {
  dword FindCount = 0;
  dword Index     = 0;
  dword FindIndex = 0;
  const byte* pParse1;
  const byte* pParse2;

	/* Ignore if given data size is too small */
  if (Size < FindData.DataSize) return (0);
  if (pData == NULL) return (0);
  
  pParse1 = pData;
  pParse2 = FindData.pData;

  while (Index < Size) {
    if (pParse2[FindIndex] == pParse1[0]) {
      ++FindIndex;

      if (FindIndex == FindData.DataSize) {
        if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\t\tFound at index %u", Index);
	++FindCount;
	if ((FindData.Flags & OB_FIND_FINDALL) == 0) return (FindCount);
	FindIndex = 0;
      }
    }
    else {
      pParse1  -= FindIndex;
      Index    -= FindIndex;
      FindIndex = 0;
    }

    ++pParse1;
    ++Index;
  }

  return (FindCount);
}
/*===========================================================================
 *		End of Function ObFindDataNoCase()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ObFindDataCase (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindDataCase (const byte* pData, const dword Size, obfinddata_t& FindData) {
  dword FindCount = 0;
  dword Index     = 0;
  dword FindIndex = 0;
  const byte* pParse1;
  const byte* pParse2;

	/* Ignore if given data size is too small */
  if (Size < FindData.DataSize) return (0);
  if (pData == NULL) return (0);
 
  pParse1 = pData;
  pParse2 = FindData.pData;

  while (Index < Size) {

    if (pParse2[FindIndex] == pParse1[0]) {
      ++FindIndex;

      if (FindIndex == FindData.DataSize) {
        if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\t\tFound at index %u", Index);
	++FindCount;
	if ((FindData.Flags & OB_FIND_FINDALL) == 0) return (FindCount);
	FindIndex = 0;
      }
    }
    else {
      pParse1  -= FindIndex;
      Index    -= FindIndex;
      FindIndex = 0;
    }

    ++pParse1;
    ++Index;
  }

  return (FindCount);
}
/*===========================================================================
 *		End of Function ObFindDataCase()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ObFindTextDataNoCase (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindTextDataNoCase (const byte* pData, const dword Size, obfinddata_t& FindData) {
  dword FindCount = 0;
  dword Index     = 0;
  dword FindIndex = 0;
  const byte* pParse1;
  const byte* pParse2;

	/* Ignore if given data size is too small */
  if (Size < FindData.DataSize) return (0);
  if (pData == NULL) return (0);

  pParse1 = pData;
  pParse2 = FindData.pData;

  while (Index < Size) {

  		/* Stop searching on the first non-text character */
    if (*pParse1 < 0x05 || *pParse1 > 0x7f) break;

    if (tolower(pParse2[FindIndex]) == tolower(pParse1[0])) {
      ++FindIndex;

      if (FindIndex == FindData.DataSize) {
        if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\t\tFound at index %u", Index);
	++FindCount;
	if ((FindData.Flags & OB_FIND_FINDALL) == 0) return (FindCount);
	FindIndex = 0;
      }
    }
    else {
      pParse1  -= FindIndex;
      Index    -= FindIndex;
      FindIndex = 0;
    }

    ++pParse1;
    ++Index;
  }

  return (FindCount);
}
/*===========================================================================
 *		End of Function ObFindTextDataNoCase()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ObFindTextDataCase (pData, Size, FindData);
 *
 *=========================================================================*/
dword ObFindTextDataCase (const byte* pData, const dword Size, obfinddata_t& FindData) {
  dword FindCount = 0;
  dword Index     = 0;
  dword FindIndex = 0;
  const byte* pParse1;
  const byte* pParse2;

	/* Ignore if given data size is too small */
  if (Size < FindData.DataSize) return (0);
  if (pData == NULL) return (0);

  pParse1 = pData;
  pParse2 = FindData.pData;

  while (Index < Size) {

    		/* Stop searching on the first non-text character */
    if (*pParse1 < 0x05 || *pParse1 > 0x7f) break;

    if (tolower(pParse2[FindIndex]) == tolower(pParse1[0])) {
      ++FindIndex;

      if (FindIndex == FindData.DataSize) {
        if ((FindData.Flags & OB_FIND_OUTPUTLOG) != 0) SystemLog.Printf("\t\tFound at index %u", Index);
	++FindCount;
	if ((FindData.Flags & OB_FIND_FINDALL) == 0) return (FindCount);
	FindIndex = 0;
      }
    }
    else {
      pParse1  -= FindIndex;
      Index    -= FindIndex;
      FindIndex = 0;
    }

    ++pParse1;
    ++Index;
  }

  return (FindCount);
}
/*===========================================================================
 *		End of Function ObFindTextDataCase()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ParseObBipedFlagString (pValue);
 *
 * Parse a string composed of biped parts of the format:
 *
 *	Hair | Head | Upper Body
 *
 * and returns the associated biped flag.
 *
 *=========================================================================*/
dword ParseObBipedFlagString (const SSCHAR* pValue) {
  return ParseObBipedFlagString(pValue, "|");
 }
/*===========================================================================
 *		End of Function ParseObBipedFlagString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - dword ParseObBipedFlagString (pValue, pDivString);
 *
 * Parse a string composed of biped parts seperated by the given string.
 * Returns the computed biped flag.
 *
 *=========================================================================*/
dword ParseObBipedFlagString (const SSCHAR* pValue, const SSCHAR* pDivString) {
  SSCHAR  Buffer[255+1];
  SSCHAR* pParse;
  SSCHAR* pParse1;
  dword   Mask = 0;
  int     PartValue;
  bool    Result;

	/* Create a copy of the input value for parsing */
  strnncpy(Buffer, pValue, 255);
  strlwr(Buffer);
  if (pDivString == NULL) pDivString = ",";

	/* Parse the entire string */
  pParse = strtok(Buffer, pDivString);

  while (pParse != NULL) {
    pParse1 = trim(pParse);
    
		/* Find the effect mask */
    Result = GetObBipedFlagValue(PartValue, pParse1);

    if (!Result)
      AddObGeneralError("Unknown biped part '%s'!", pParse1);
    else
      Mask |= (dword) PartValue;

    pParse = strtok(NULL, pDivString);
   }

  return (Mask);
 }
/*===========================================================================
 *		End of Function ParseObBipedFlagString()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObContainsRecordType (Name, pArray);
 *
 *=========================================================================*/
bool ObContainsRecordType (const obrectype_t Name, const obrectype_t* pArray) {
  if (pArray == NULL) return (false);

  while (*pArray != OB_NAME_NULL) {
    if (*pArray == Name) return (true);
    ++pArray;
  }

  return (false);
}
/*===========================================================================
 *		End of Function ObContainsRecordType()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObPrepareEditorID (EditorID);
 *
 * Prepares the given editorID for use, removing whitespace and any invalid
 * characters. Returns false if the final result is not a valid editor ID.
 *
 *=========================================================================*/
bool ObPrepareEditorID (CSString& EditorID) {

	/* Remove all whitespace */
  EditorID.Trim();

	/* Ensure the ID is only alpha-numeric */
  EditorID.RemoveCharsToMatch(isalnum);

	/* Empty string is not a valid ID */
  if (EditorID.IsEmpty()) return (false);

  return (true);
}
/*===========================================================================
 *		End of Function ObPrepareEditorID()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObIsInventoryRecord (RecordType);
 *
 *=========================================================================*/
bool ObIsInventoryRecord (const obrectype_t RecordType) {
const obrectype_t s_InventoryTypes[] = {
	OB_NAME_ALCH,	OB_NAME_AMMO,	OB_NAME_APPA,	OB_NAME_ARMO,	OB_NAME_BOOK,
	OB_NAME_CLOT,	OB_NAME_INGR,	OB_NAME_KEYM,	OB_NAME_LVLI,	OB_NAME_MISC,
	OB_NAME_SGST,	OB_NAME_SLGM,	OB_NAME_WEAP,	OB_NAME_LIGH,	OB_NAME_NULL };

  return ObContainsRecordType(RecordType, s_InventoryTypes);
}
/*===========================================================================
 *		End of Function ObIsInventoryRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObIsObjectRecord (RecordType);
 *
 *=========================================================================*/
bool ObIsObjectRecord (const obrectype_t RecordType) {
const obrectype_t s_InventoryTypes[] = {
	OB_NAME_ACTI, OB_NAME_ALCH, OB_NAME_AMMO, OB_NAME_ARMO, OB_NAME_APPA, OB_NAME_BOOK,
	OB_NAME_CLOT, OB_NAME_CONT, OB_NAME_CREA, OB_NAME_DOOR, OB_NAME_FLOR, OB_NAME_FURN,
	OB_NAME_INGR, OB_NAME_KEYM, OB_NAME_LIGH, OB_NAME_LVLC, OB_NAME_LVLI, OB_NAME_MISC,
	OB_NAME_NPC_, OB_NAME_REFR, OB_NAME_SGST, OB_NAME_SLGM, OB_NAME_STAT, OB_NAME_TREE, 
	OB_NAME_WEAP, OB_NAME_NULL };

  return ObContainsRecordType(RecordType, s_InventoryTypes);
}
/*===========================================================================
 *		End of Function ObIsObjectRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObIsValidLvliRecord (RecordType);
 *
 * Is the given record type a valid for use in a LVLI record.
 *
 * TODO: Combine with other lvli checks (lvl edit dlg)
 *
 *=========================================================================*/
bool ObIsValidLvliRecord (const obrectype_t RecordType) {
  const obrectype_t s_LvliRecordTypes[] = {
	OB_NAME_ALCH,	OB_NAME_AMMO,	OB_NAME_APPA,	OB_NAME_ARMO,	OB_NAME_BOOK,
	OB_NAME_CLOT,	OB_NAME_INGR,	OB_NAME_KEYM,	OB_NAME_LVLI,	OB_NAME_MISC,
	OB_NAME_SGST,	OB_NAME_SLGM,	OB_NAME_WEAP,	OB_NAME_LIGH,	OB_NAME_NULL };

  return ObContainsRecordType(RecordType, s_LvliRecordTypes);
}
/*===========================================================================
 *		End of Function ObIsValidLvliRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObIsValidLvspRecord (RecordType);
 *
 * Is the given record type a valid for use in a LVSP record.
 *
 * TODO: Combine with other lvli checks (lvl edit dlg)
 *
 *=========================================================================*/
bool ObIsValidLvspRecord (const obrectype_t RecordType) {
  const obrectype_t s_LvspRecordTypes[] = { OB_NAME_LVSP, OB_NAME_SPEL, OB_NAME_NULL };

  return ObContainsRecordType(RecordType, s_LvspRecordTypes);
}
/*===========================================================================
 *		End of Function ObIsValidLvspRecord()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - bool ObIsValidLvlcRecord (RecordType);
 *
 * Is the given record type a valid for use in a LVLC record.
 *
 * TODO: Combine with other lvli checks (lvl edit dlg)
 *
 *=========================================================================*/
bool ObIsValidLvlcRecord (const obrectype_t RecordType) {
  const obrectype_t s_LvspRecordTypes[] = { OB_NAME_LVLC, OB_NAME_CREA, OB_NAME_NPC_, OB_NAME_NULL };

  return ObContainsRecordType(RecordType, s_LvspRecordTypes);
}
/*===========================================================================
 *		End of Function ObIsValidLvlcRecord()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - CObScriptFunction* ObGetScriptFunction (pName);
 *
 *=========================================================================*/
CObScriptFunction* ObGetScriptFunction (const char* pName) {
  return g_ScriptFunctions.GetFunction(pName);
}
/*===========================================================================
 *		End of Function ObGetScriptFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObScriptFunction* ObGetScriptConsoleFunction (pName);
 *
 *=========================================================================*/
CObScriptFunction* ObGetScriptConsoleFunction (const char* pName) {
  return g_ScriptFunctions.GetConsoleFunction(pName);
}
/*===========================================================================
 *		End of Function ObGetScriptConsoleFunction()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObLoadScriptFunctions (pFilename, CustomFlags);
 *
 *=========================================================================*/
bool ObLoadScriptFunctions (const char* pFilename, const dword CustomFlags) {
  dword InitCount = g_ScriptFunctions.GetNumFunctions();
  bool  Result;

  Result = g_ScriptFunctions.Load(pFilename, CustomFlags);
  SystemLog.Printf("Loaded %u functions...", g_ScriptFunctions.GetNumFunctions() - InitCount);
  return (Result);
}
/*===========================================================================
 *		End of Function ObLoadScriptFunctions()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - const SSCHAR* ObGetScriptFuncParamString (Type);
 *
 *=========================================================================*/
const SSCHAR* ObGetScriptFuncParamString (const int Type) {
  static const SSCHAR* s_ParamStrings[] = {
          "String", "Integer", "Float", "InventoryObject", "ObjectRef", "ActorValue", "Actor",
          "SpellItem", "Axis", "Cell", "AnimationGroup", "MagicItem", "Sound", "Topic",
          "Quest", "Race", "Class", "Faction", "Sex", "Global", "Furniture", "TesObject",
          "VariableName", "QuestStage", "MapMarker", "ActorBase", "Container", "WorldSpace",
          "CrimeType", "AIPackage", "CombatStyle", "MagicEffect", "BirthSign", "FormType",
          "Weather", "NPC", "Owner", "EffectShader", NULL };

  if (Type < 0 || Type > OB_FUNCPARAM_EFFECTSHADER) return ("Unknown");
  return s_ParamStrings[Type];
}
/*===========================================================================
 *		End of Function SSCHAR* ObGetScriptFuncParamString()
 *=========================================================================*/
