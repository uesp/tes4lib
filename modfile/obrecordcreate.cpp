/*===========================================================================
 *
 * File:	Obrecordcreate.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	August 25, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obespfile.h"


/*===========================================================================
 *
 * Begin Record Creation Array
 *
 * Holds information used to create each type of record (and group).
 *
 *=========================================================================*/
static obreccreate_t s_CreateRecords[] = {
	{ &OB_NAME_ACHR, CObAchrRecord::Create },
	{ &OB_NAME_ACRE, CObAcreRecord::Create },
	{ &OB_NAME_ACTI, CObActiRecord::Create },
	{ &OB_NAME_ALCH, CObAlchRecord::Create },
	{ &OB_NAME_AMMO, CObAmmoRecord::Create },
	{ &OB_NAME_ANIO, CObAnioRecord::Create },
	{ &OB_NAME_ARMO, CObArmoRecord::Create },
	{ &OB_NAME_APPA, CObAppaRecord::Create },
	{ &OB_NAME_BOOK, CObBookRecord::Create },
	{ &OB_NAME_BSGN, CObBsgnRecord::Create },
	{ &OB_NAME_CELL, CObCellRecord::Create },
	{ &OB_NAME_CLAS, CObIdRecord::Create },
	{ &OB_NAME_CLMT, CObClmtRecord::Create },
	{ &OB_NAME_CLOT, CObClotRecord::Create },
	{ &OB_NAME_CONT, CObContRecord::Create },
	{ &OB_NAME_CREA, CObCreaRecord::Create },
	{ &OB_NAME_CSTY, CObIdRecord::Create },
	{ &OB_NAME_DIAL, CObDialRecord::Create },
	{ &OB_NAME_DOOR, CObDoorRecord::Create },
	{ &OB_NAME_EFSH, CObIdRecord::Create },
	{ &OB_NAME_ENCH, CObEnchRecord::Create },
	{ &OB_NAME_EYES, CObIdRecord::Create },	
	{ &OB_NAME_FACT, CObFactRecord::Create },
	{ &OB_NAME_FLOR, CObFlorRecord::Create },
	{ &OB_NAME_FURN, CObFurnRecord::Create },
	{ &OB_NAME_GLOB, CObIdRecord::Create },
	{ &OB_NAME_GMST, CObIdRecord::Create },
	{ &OB_NAME_GRAS, CObIdRecord::Create },
	{ &OB_NAME_HAIR, CObIdRecord::Create },	
	{ &OB_NAME_IDLE, CObIdleRecord::Create },
	{ &OB_NAME_INFO, CObInfoRecord::Create },
	{ &OB_NAME_INGR, CObIngrRecord::Create },
	{ &OB_NAME_KEYM, CObKeymRecord::Create },
	{ &OB_NAME_LAND, CObLandRecord::Create },
	{ &OB_NAME_LIGH, CObLighRecord::Create },
	{ &OB_NAME_LSCR, CObLscrRecord::Create },
	{ &OB_NAME_LTEX, CObLtexRecord::Create },
	{ &OB_NAME_LVLC, CObLvlcRecord::Create },
	{ &OB_NAME_LVLI, CObLvliRecord::Create },
	{ &OB_NAME_LVSP, CObLvspRecord::Create },
	{ &OB_NAME_MGEF, CObMgefRecord::Create },
	{ &OB_NAME_MISC, CObMiscRecord::Create },
	{ &OB_NAME_NPC_, CObNpcRecord::Create },
	{ &OB_NAME_PACK, CObPackRecord::Create },
	{ &OB_NAME_PGRD, CObPgrdRecord::Create },
	{ &OB_NAME_QUST, CObQustRecord::Create },
	{ &OB_NAME_RACE, CObRaceRecord::Create },
	{ &OB_NAME_REFR, CObRefrRecord::Create },
	{ &OB_NAME_REGN, CObRegnRecord::Create },
	{ &OB_NAME_ROAD, CObRecord::Create },
	{ &OB_NAME_SBSP, CObIdRecord::Create },
	{ &OB_NAME_SCPT, CObScptRecord::Create },
	{ &OB_NAME_SGST, CObSgstRecord::Create },
	{ &OB_NAME_SLGM, CObSlgmRecord::Create },
	{ &OB_NAME_SKIL, CObIdRecord::Create },
	{ &OB_NAME_SPEL, CObSpelRecord::Create },
	{ &OB_NAME_SOUN, CObSounRecord::Create },
	{ &OB_NAME_STAT, CObStatRecord::Create },
	{ &OB_NAME_TES4, CObTes4Record::Create },
	{ &OB_NAME_TREE, CObIdRecord::Create },
	{ &OB_NAME_WATR, CObWatrRecord::Create },
	{ &OB_NAME_WEAP, CObWeapRecord::Create },
	{ &OB_NAME_WRLD, CObWrldRecord::Create },
	{ &OB_NAME_WTHR, CObWthrRecord::Create },
	{ NULL,		 NULL }	/* Must be last */
  };
/*===========================================================================
 *		End of Record Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Group Creation Array
 *
 *=========================================================================*/
static obgroupcreate_t s_CreateGroups[] = {
	{ OB_GROUP_TYPE,	CObTypeGroup::Create },
	{ OB_GROUP_WORLDCHILD,	CObFormIDGroup::Create },
	{ OB_GROUP_INTCELL,	CObBlockGroup::Create },
	{ OB_GROUP_INTSUBCELL,	CObBlockGroup::Create },
	{ OB_GROUP_EXTCELL,	CObGridGroup::Create },
	{ OB_GROUP_EXTSUBCELL,	CObGridGroup::Create },
	{ OB_GROUP_CELLCHILD,	CObFormIDGroup::Create },
	{ OB_GROUP_TOPICCHILD,	CObFormIDGroup::Create },
	{ OB_GROUP_CELLPERSIST,	CObFormIDGroup::Create },
	{ OB_GROUP_CELLTEMP,	CObFormIDGroup::Create },
	{ OB_GROUP_CELLDISTANT,	CObFormIDGroup::Create },
	{ OB_GROUP_NONE,	NULL }	/* Must be last */
    };


static obgroupcreate_t s_CreateRefGroups[] = {
	{ OB_GROUP_TYPE,	CObRefTypeGroup::Create },
	{ OB_GROUP_WORLDCHILD,	CObRefFormIDGroup::Create },
	{ OB_GROUP_INTCELL,	CObRefBlockGroup::Create },
	{ OB_GROUP_INTSUBCELL,	CObRefBlockGroup::Create },
	{ OB_GROUP_EXTCELL,	CObRefGridGroup::Create },
	{ OB_GROUP_EXTSUBCELL,	CObRefGridGroup::Create },
	{ OB_GROUP_CELLCHILD,	CObRefFormIDGroup::Create },
	{ OB_GROUP_TOPICCHILD,	CObRefFormIDGroup::Create },
	{ OB_GROUP_CELLPERSIST,	CObRefFormIDGroup::Create },
	{ OB_GROUP_CELLTEMP,	CObRefFormIDGroup::Create },
	{ OB_GROUP_CELLDISTANT,	CObRefFormIDGroup::Create },
	{ OB_GROUP_NONE,	NULL }	/* Must be last */
    };
/*===========================================================================
 *		End of Group Creation Array
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Top Level Item Types
 *
 * This array lists the valid group/item types found at the top level 
 * of a mod file.
 *
 *=========================================================================*/
const obrectype_t* s_TopLevelTypes[] = { 
	&OB_NAME_ACTI,
	&OB_NAME_ALCH,
	&OB_NAME_AMMO,
	&OB_NAME_ARMO,
	&OB_NAME_APPA,
	&OB_NAME_BOOK,
	&OB_NAME_CLOT,
	&OB_NAME_CONT,
	&OB_NAME_CREA,
	&OB_NAME_DOOR,
	&OB_NAME_ENCH,
	&OB_NAME_FLOR,
	&OB_NAME_FURN,
	&OB_NAME_GRAS,
	&OB_NAME_INGR,
	&OB_NAME_KEYM,
	&OB_NAME_LIGH,
	&OB_NAME_LVSP,
	&OB_NAME_LVLC,
	&OB_NAME_LVLI,
	&OB_NAME_MISC,
	&OB_NAME_NPC_,
	&OB_NAME_SCPT,
	&OB_NAME_SGST,
	&OB_NAME_SLGM,
	&OB_NAME_SPEL,
	&OB_NAME_SOUN,
	&OB_NAME_STAT,
	&OB_NAME_TREE,
	&OB_NAME_WEAP,
	&OB_NAME_WRLD,
	NULL	/* Must be last */
  };

const obrectype_t* s_TopLevelTypeOrder[] = { 
	&OB_NAME_GMST,
	&OB_NAME_GLOB,
	&OB_NAME_CLAS,
	&OB_NAME_FACT,
	&OB_NAME_HAIR,
	&OB_NAME_EYES,
	&OB_NAME_RACE,
	&OB_NAME_SOUN,
	&OB_NAME_SKIL,
	&OB_NAME_MGEF,
	&OB_NAME_SCPT,
	&OB_NAME_LTEX,
	&OB_NAME_ENCH,
	&OB_NAME_SPEL,
	&OB_NAME_BSGN,
	&OB_NAME_ACTI,
	&OB_NAME_APPA,
	&OB_NAME_ARMO,
	&OB_NAME_BOOK,
	&OB_NAME_CLOT,
	&OB_NAME_CONT,
	&OB_NAME_DOOR,
	&OB_NAME_INGR,
	&OB_NAME_LIGH,
	&OB_NAME_MISC, 
	&OB_NAME_STAT, 
	&OB_NAME_GRAS, 
	&OB_NAME_TREE, 
	&OB_NAME_FLOR, 
	&OB_NAME_FURN, 
	&OB_NAME_WEAP, 
	&OB_NAME_AMMO, 
	&OB_NAME_NPC_, 
	&OB_NAME_CREA, 
	&OB_NAME_LVLC, 
	&OB_NAME_SLGM, 
	&OB_NAME_KEYM, 
	&OB_NAME_ALCH, 
	&OB_NAME_SBSP, 
	&OB_NAME_SGST, 
	&OB_NAME_LVLI, 
	&OB_NAME_WTHR, 
	&OB_NAME_CLMT, 
	&OB_NAME_REGN, 
	&OB_NAME_CELL, 
	&OB_NAME_WRLD, 
	&OB_NAME_DIAL, 
	&OB_NAME_QUST, 
	&OB_NAME_IDLE, 
	&OB_NAME_PACK, 
	&OB_NAME_CSTY, 
	&OB_NAME_LSCR, 
	&OB_NAME_LVSP, 
	&OB_NAME_ANIO, 
	&OB_NAME_WATR,
	&OB_NAME_EFSH,
	NULL
};
/*==========================================================================
 *		End of Top Level Item Types
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObBaseRecord* CreateObRecordGroup (Header);
 *
 * Creates and returns a group or record based on the input header data. 
 *
 *=========================================================================*/
CObBaseRecord* CreateObRecordGroup (const obbaseheader_t Header) {

	/* Determine whether to create a group or record */
  if (Header.Type == OB_NAME_GRUP) 
    return CreateObGroup(Header);
  else
    return CreateObRecord(Header);

 }
/*===========================================================================
 *		End of Function CreateObRecordGroup()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObBaseRecord* CreateObRecord (Header);
 *
 * Creates and returns a new record based on the input header
 * data. Should only return NULL on an out of memory error.
 *
 *=========================================================================*/
CObRecord* CreateObRecord (const obbaseheader_t Header) {
  CObRecord* pNewRecord = NULL;
  int	     Index;

  for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index) {
    if (Header.Type == *s_CreateRecords[Index].pType) {
      pNewRecord = s_CreateRecords[Index].CreateMethod();
      break;
     }
   }

	/* Create a base class record by default */
  if (pNewRecord == NULL) {
    SystemLog.Printf("Unknown record type '%4.4s' created!", Header.Type.Name);
    pNewRecord = CObRecord::Create();
  }

	/* Initialize and return the new record */
  pNewRecord->Initialize(Header);
  return (pNewRecord);
 }


CObRecord* CreateObRecord (const obrectype_t Type) {
  CObRecord* pNewRecord = NULL;
  int	     Index;

  for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index) {
    if (Type == *s_CreateRecords[Index].pType) {
      pNewRecord = s_CreateRecords[Index].CreateMethod();
      break;
     }
   }

	/* Create a base class record by default */
  if (pNewRecord == NULL) {
    SystemLog.Printf("Unknown record type '%4.4s' created!", Type.Name);
    pNewRecord = CObRecord::Create();
  }

	/* Initialize and return the new record */
  pNewRecord->Initialize(Type);
  return (pNewRecord);
 }
/*===========================================================================
 *		End of Function CreateObRecord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - CObGroup* CreateObGroup (Header);
 *
 * Creates and returns a new group based on the input header
 * data. Should only return NULL on an out of memory error.
 *
 *=========================================================================*/
CObGroup* CreateObGroup (const obbaseheader_t Header) {
  CObGroup* pNewGroup = NULL;
  int	    Index;

  for (Index = 0; s_CreateGroups[Index].CreateMethod != NULL; ++Index) {
    if (Header.GroupType == s_CreateGroups[Index].GroupType) {
      pNewGroup = s_CreateGroups[Index].CreateMethod();
      break;
     }
   }

	/* Create a base class group by default */
  if (pNewGroup == NULL) pNewGroup = CObGroup::Create();

	/* Initialize and return the new group */
  pNewGroup->Initialize(Header);
  return (pNewGroup);
 }


CObGroup* CreateObGroup (const int Type) {
  CObGroup* pNewGroup = NULL;
  int	    Index;

  for (Index = 0; s_CreateGroups[Index].CreateMethod != NULL; ++Index) {
    if (Type == s_CreateGroups[Index].GroupType) {
      pNewGroup = s_CreateGroups[Index].CreateMethod();
      break;
     }
   }

	/* Create a base class group by default */
  if (pNewGroup == NULL) pNewGroup = CObGroup::Create();

	/* Initialize and return the new group */
  pNewGroup->Initialize(Type);
  return (pNewGroup);
}


CObGroup* CreateObRefGroup (const int Type) {
  CObGroup* pNewGroup = NULL;
  int	    Index;

  for (Index = 0; s_CreateRefGroups[Index].CreateMethod != NULL; ++Index) {
    if (Type == s_CreateRefGroups[Index].GroupType) {
      pNewGroup = s_CreateRefGroups[Index].CreateMethod();
      break;
     }
   }

	/* Create a base class group by default */
  if (pNewGroup == NULL) pNewGroup = CObRefGroup::Create();

	/* Initialize and return the new group */
  pNewGroup->Initialize(Type);
  return (pNewGroup);
 } 
/*===========================================================================
 *		End of Function CreateObGroup()
 *=========================================================================*/
 

/*===========================================================================
 *
 * Function - obreccreate_t* FindObRecCreate (Type);
 *
 *=========================================================================*/
obreccreate_t* FindObRecCreate (const obrectype_t Type) {
  dword Index;

  for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index) {
    if (Type == *s_CreateRecords[Index].pType) return &s_CreateRecords[Index];
  }

  return (NULL);
}
/*===========================================================================
 *		End of Function FindObRecCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - obreccreate_t* FindObRecCreate (pName);
 *
 *=========================================================================*/
obreccreate_t* FindObRecCreate (const SSCHAR* pName) {
  dword Index;

  for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index) {
    if (*s_CreateRecords[Index].pType == pName) return &s_CreateRecords[Index];
  }

  return (NULL);
}
/*===========================================================================
 *		End of Function FindObRecCreate()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool IsObTopLevelGroup (Type);
 *
 *=========================================================================*/
bool IsObTopLevelGroup (const obrectype_t Type) {
  dword Index;

  for (Index = 0; s_TopLevelTypeOrder[Index] != NULL; ++Index) {
    if (Type == *s_TopLevelTypeOrder[Index]) return (true);
   }

	/* Unknown type */
  return (false);
}
/*===========================================================================
 *		End of Function IsObTopLevelGroup()
 *=========================================================================*/
