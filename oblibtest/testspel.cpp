/*===========================================================================
 *
 * File:	TestSpel.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 18, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testSpel.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 	dword Type;
	dword SpellCost;
	dword SpellLevel;
	dword Flags;
 *
 *=========================================================================*/
static testeffspel_t g_Effects[] = {
	{ &OB_MGEF_FIDG, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0, 0, NULL, 0, NULL },
	{ &OB_MGEF_FIDG, OBEFIT_TYPE_TOUCH, 1, 2, 3, 0, 0, 0, NULL, 0, NULL },
	{ &OB_MGEF_FIDG, OBEFIT_TYPE_TARGET, 1, 2, 3, 0, 0, 0, NULL, 0, NULL },
	{ &OB_MGEF_FIDG, OBEFIT_TYPE_TARGET, 1, 2, 3, OB_ACTORVALUE_LUCK, 0, 0, NULL, 0, NULL },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, 0, &OB_NAME_FULL, 0, "script name" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_ALTERATION, &OB_NAME_FULL, 0, "alteration" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_CONJURATION, &OB_NAME_FULL, 0, "conjuration" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_DESTRUCTION, &OB_NAME_FULL, 0, "destruction" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_ILLUSION, &OB_NAME_FULL, 0, "illusion" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_MYSTICISM, &OB_NAME_FULL, 0, "mysticism" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_RESTORATION, &OB_NAME_FULL, 0, "restoration" },
	{ &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, 0, &OB_NAME_FULL, OBSCIT_FLAG_HOSTILE, "hostile" }
 };




static testspel_t g_TestData = {
	0x00240000, { 0, 1, 2, 0 }, "spell_test", "Spell Name", NULL, NULL, NULL, NULL
 };

static testspel_t g_TestValues[] = {
	{ 0x00240001, { 0, 1, 2, 0 }, "spell_test", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240002, { OB_SPELTYPE_SPELL, 2, 3, 0 }, "spell_spell", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240003, { OB_SPELTYPE_DISEASE, 2, 3, 0 }, "spell_disease", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240004, { OB_SPELTYPE_POWER, 2, 3, 0 },	"spell_power", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240005, { OB_SPELTYPE_LESSERPOWER, 2, 3, 0 }, "spell_lesserpower", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240006, { OB_SPELTYPE_ABILITY, 2, 3, 0 }, "spell_ability", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240007, { OB_SPELTYPE_POISON, 2, 3, 0 }, "spell_poison", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240008, { 0, 1, OB_SPELLEVEL_NOVICE, 0 }, "spell_novice", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240009, { 0, 1, OB_SPELLEVEL_APPRENTICE, 0 }, "spell_appr", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240010, { 0, 1, OB_SPELLEVEL_JOURNEYMAN, 0 }, "spell_journeye", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240011, { 0, 1, OB_SPELLEVEL_EXPERT, 0 }, "spell_expert", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240012, { 0, 1, OB_SPELLEVEL_MASTER, 0 }, "spell_master", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240013, { 0, 1, 2, OB_SPELFLAG_MANUALCALC }, "spell_noautocalc", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240014, { 0, 1, 2, OB_SPELFLAG_PLAYERSTART }, "spell_playerstart", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240015, { 0, 1, 2, OB_SPELFLAG_SILENCEIMMUNE }, "spell_silenceimmune", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240016, { 0, 1, 2, OB_SPELFLAG_IGNORELOS }, "spell_ignorelos", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240017, { 0, 1, 2, OB_SPELFLAG_ALWAYSAPPLYSCRIPT }, "spell_alwaysapply", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240018, { 0, 1, 2, OB_SPELFLAG_NOABSORBREFLECT }, "spell_noabsorbreflect", "Spell Name", NULL, NULL, NULL, NULL },
	{ 0x00240019, { 0, 0, 0, 0 },	"ench_null",  "spell name", NULL, NULL, NULL, NULL },
	{ 0x00240020, { 1, 2, 3, 0 },	"ench_eff_self",  "spell name", &g_Effects[0], NULL, NULL, NULL, NULL },
	{ 0x00240021, { 1, 2, 3, 0 },	"ench_eff_touch",  "spell name", &g_Effects[1], NULL, NULL, NULL, NULL },
	{ 0x00240022, { 1, 2, 3, 0 },	"ench_eff_target",  "spell name", &g_Effects[2], NULL, NULL, NULL, NULL },
	{ 0x00240023, { 1, 2, 3, 0 },	"ench_eff_luck",  "spell name", &g_Effects[3], NULL, NULL, NULL, NULL },
	{ 0x00240024, { 1, 2, 3, 0 },	"ench_eff_script",  "spell name", &g_Effects[4], NULL, NULL, NULL, NULL },
	{ 0x00240025, { 1, 2, 3, 0 },	"ench_eff_alter",  "spell name", &g_Effects[5], NULL, NULL, NULL, NULL },
	{ 0x00240026, { 1, 2, 3, 0 },	"ench_eff_conj",  "spell name", &g_Effects[6], NULL, NULL, NULL, NULL },
	{ 0x00244027, { 1, 2, 3, 0 },	"ench_eff_dest",  "spell name", &g_Effects[7], NULL, NULL, NULL, NULL },
	{ 0x00240028, { 1, 2, 3, 0 },	"ench_eff_ill",  "spell name", &g_Effects[8], NULL, NULL, NULL, NULL },
	{ 0x00240029, { 1, 2, 3, 0 },	"ench_eff_mys",  "spell name", &g_Effects[9], NULL, NULL, NULL, NULL },
	{ 0x00240030, { 1, 2, 3, 0 },	"ench_eff_rest",  "spell name", &g_Effects[10], NULL, NULL, NULL, NULL },
	{ 0x00240031, { 1, 2, 3, 0 },	"ench_eff_hostile",  "spell name", &g_Effects[11], NULL, NULL, NULL, NULL },
	{ 0x00240032, { 1, 2, 3, 0 },	"ench_eff2",  "spell name", &g_Effects[0], &g_Effects[1], NULL, NULL, NULL },
	{ 0x00240033, { 1, 2, 3, 0 },	"ench_eff3",  "spell name", &g_Effects[0], &g_Effects[1], &g_Effects[2], NULL, NULL },
	{ 0x00240034, { 1, 2, 3, 0 },	"ench_eff4",  "spell name", &g_Effects[0], &g_Effects[1], &g_Effects[2], &g_Effects[3], NULL },
	{ 0x00240035, { 1, 2, 3, 0 },	"ench_eff5",  "spell name", &g_Effects[0], &g_Effects[1], &g_Effects[2], &g_Effects[3], &g_Effects[4] },
	{ 0, { 0, 0, 0, 0 }, NULL, NULL, NULL, NULL, NULL, NULL  }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSpel_SetGet (void);
 *
 * Tests basic set/get methods of an SPEL record.
 *
 *=========================================================================*/
bool TestSpel_SetGet (void) {
  CObSpelRecord	    Record;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfitEffect;
  CObScitSubrecord* pScitEffect;
  const SSCHAR*     pEffectName;
  bool		    Result;

  OBTEST_LEVEL("SPEL Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Spell level")
	Record.SetLevel(g_TestData.Data.SpellLevel);
	OBTEST_DOINTCOMPARE(Record.GetLevel(), ==, g_TestData.Data.SpellLevel)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Spell cost")
	Record.SetCost(g_TestData.Data.SpellCost);
	OBTEST_DOINTCOMPARE(Record.GetCost(), ==, g_TestData.Data.SpellCost)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Spell type")
	Record.SetType(g_TestData.Data.Type);
	OBTEST_DOINTCOMPARE(Record.GetType(), ==, g_TestData.Data.Type)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchant AutoCalc (true)")
	Record.SetAutoCalc(true);
	OBTEST_DOINTCOMPARE(Record.IsAutoCalc(), ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchant AutoCalc (false)")
	Record.SetAutoCalc(false);
	OBTEST_DOINTCOMPARE(Record.IsAutoCalc(), ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Add Effect")
	pEffect = Record.AddEffect(OB_MGEF_FIDG);
	OBTEST_DOCOMPARE(pEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEffect == NULL) return (false);

  OBTEST_START_TEST("Check effect type")
	OBTEST_DOINTCOMPARE(pEffect->GetClassType(), ==, OBCLASS_CObNameSubrecord)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check effect name")
	OBTEST_DOCOMPARE(pEffect->GetDataName(), ==, OB_MGEF_FIDG)
  OBTEST_END_TEST()
  
  OBTEST_START_TEST("Check GetEffectData()")
        pEfitEffect = Record.GetEffectData(pEffect);
	OBTEST_DOCOMPARE(pEfitEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEfitEffect == NULL) return (false);

  OBTEST_START_TEST("Check effect data name")
	OBTEST_DOCOMPARE(pEfitEffect->GetEffectName(), ==, OB_MGEF_FIDG)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check GetEffectData()  return type")
	OBTEST_DOINTCOMPARE(pEfitEffect->GetClassType(), ==, OBCLASS_CObEfitSubrecord)
  OBTEST_END_TEST()
  if (pEfitEffect == NULL) return (false);

  OBTEST_START_TEST("Check GetScriptEffectData() (for non script)")
	OBTEST_DOCOMPARE(Record.GetScriptEffectData(pEffect), ==, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check GetScriptEffectName() (for non script)")
	OBTEST_DOCOMPARE(Record.GetScriptEffectName(pEffect), ==, NULL)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check delete all effects (set invalid effect)")
	Record.DeleteAllEffects();
	Result = Record.SetEffectData(pEffect, 0, 1, 1, 1);
	OBTEST_DOCOMPARE(Result, ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Add script effect")
	pEffect = Record.AddEffect(OB_MGEF_SEFF);
	OBTEST_DOCOMPARE(pEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEffect == NULL) return (false);

  OBTEST_START_TEST("Check effect type")
	OBTEST_DOINTCOMPARE(pEffect->GetClassType(), ==, OBCLASS_CObNameSubrecord)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check effect name")
	OBTEST_DOCOMPARE(pEffect->GetDataName(), ==, OB_MGEF_SEFF)
  OBTEST_END_TEST()
  
  OBTEST_START_TEST("Check GetEffectData()")
        pEfitEffect = Record.GetEffectData(pEffect);
	OBTEST_DOCOMPARE(pEfitEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEfitEffect == NULL) return (false);

  OBTEST_START_TEST("Check effect data name")
	OBTEST_DOCOMPARE(pEfitEffect->GetEffectName(), ==, OB_MGEF_SEFF)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check GetScriptEffectData()")
	pScitEffect = Record.GetScriptEffectData(pEffect);
	OBTEST_DOCOMPARE(pScitEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pScitEffect == NULL) return (false);

  OBTEST_START_TEST("Check GetScriptEffectData() name")
	OBTEST_DOCOMPARE(pScitEffect->GetName(), ==, OB_NAME_SCIT)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check GetScriptEffectName()")
	pEffectName = Record.GetScriptEffectName(pEffect);
	OBTEST_DOCOMPARE(pEffectName, !=, NULL)
  OBTEST_END_TEST()

  pEffect = Record.AddEffect(OB_MGEF_FIDG);
  if (pEffect == NULL) return (false);

  OBTEST_START_TEST("Set effect data")
	Result = Record.SetEffectData(pEffect, 1, 2, 3, 4, 5);
	OBTEST_DOCOMPARE(Result, ==, true)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set script effect data (for non script)")
	Result = Record.SetScriptEffectData(pEffect, 1, 2, OB_NAME_HEDR, false);
	OBTEST_DOCOMPARE(Result, ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Set script effect name (for non script)")
	Result = Record.SetScriptEffectName(pEffect, "effect name");
	OBTEST_DOCOMPARE(Result, ==, false)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Check GetEffectData()")
        pEfitEffect = Record.GetEffectData(pEffect);
	OBTEST_DOCOMPARE(pEfitEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEfitEffect == NULL) return (false);

  OBTEST_START_TEST("Check effect type")
        pEfitEffect = Record.GetEffectData(pEffect);
	OBTEST_DOCOMPARE(pEfitEffect, !=, NULL)
  OBTEST_END_TEST()
  if (pEfitEffect == NULL) return (false);

  return (true);
 }
/*===========================================================================
 *		End of Function TestSpel_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSpel_Output (File);
 *
 * Outputs basic SPEL records to the given file.
 *
 *=========================================================================*/
bool TestSpel_Output (CObEspFile& File) {
  CObSpelRecord*    pRecord;
  CObBaseRecord*    pBase;
  CObNameSubrecord* pEffect;
  testeffspel_t*    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;
  bool		    Result;

  OBTEST_LEVEL("SPEL Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
  
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_SPEL);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObSpelRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    pRecord->SetCost(g_TestValues[Index].Data.SpellCost);
    pRecord->SetLevel(g_TestValues[Index].Data.SpellLevel);
    pRecord->SetType(g_TestValues[Index].Data.Type);

    if (g_TestValues[Index].pName     != NULL) pRecord->SetItemName(g_TestValues[Index].pName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);

    pRecord->SetAutoCalc(!((g_TestValues[Index].Data.Flags & OB_SPELFLAG_MANUALCALC) != 0));
    pRecord->SetAbsorbReflect( !((g_TestValues[Index].Data.Flags & OB_SPELFLAG_NOABSORBREFLECT) != 0));
    pRecord->SetAlwaysApplyScript( ((g_TestValues[Index].Data.Flags & OB_SPELFLAG_ALWAYSAPPLYSCRIPT) != 0));
    pRecord->SetIgnoreLOS( ((g_TestValues[Index].Data.Flags & OB_SPELFLAG_IGNORELOS) != 0));
    pRecord->SetPlayerStart( ((g_TestValues[Index].Data.Flags & OB_SPELFLAG_PLAYERSTART) != 0));
    pRecord->SetSilenceImmune( ((g_TestValues[Index].Data.Flags & OB_SPELFLAG_SILENCEIMMUNE) != 0));

    for (Index1 = 0; g_TestValues[Index].Effects[Index1] != NULL; ++Index1) {
      pTestEffect = g_TestValues[Index].Effects[Index1];

      OBTEST_START_TEST("Add new effect")
	  pEffect = pRecord->AddEffect(*pTestEffect->pName);
	  OBTEST_DOCOMPARE(pEffect, !=, NULL)
      OBTEST_END_TEST()
      if (pEffect == NULL) continue;

      OBTEST_START_TEST("Set effect data")
	   Result = pRecord->SetEffectData(pEffect, pTestEffect->Type, pTestEffect->Magnitude, pTestEffect->Area, pTestEffect->Duration, pTestEffect->ActorValue);
	   OBTEST_DOCOMPARE(Result, ==,  true)
      OBTEST_END_TEST()

      if (*pTestEffect->pName == OB_MGEF_SEFF) {
        Flag = (pTestEffect->Flags & OBSCIT_FLAG_HOSTILE) != 0;

	OBTEST_START_TEST("Set script effect data")
		pRecord->SetScriptEffectData(pEffect, pTestEffect->ScriptID, pTestEffect->School, *pTestEffect->pVisualEffect, Flag);
		OBTEST_DOCOMPARE(Result, ==,  true)
	OBTEST_END_TEST()

	OBTEST_START_TEST("Set script effect name")
		pRecord->SetScriptEffectName(pEffect, pTestEffect->pScript);
		OBTEST_DOCOMPARE(Result, ==,  true)
	OBTEST_END_TEST()
       }
     }
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestSpel_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSpel_Input (File);
 *
 * Checks the values of SPEL records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestSpel_Input (CObEspFile& File) {
  CObBaseRecord*    pBase;
  CObSpelRecord*    pRecord;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfit;
  CObScitSubrecord* pScit;
  const SSCHAR*     pScriptName;
  testeffspel_t*    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;

  OBTEST_LEVEL("SPEL Input")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
    OnTestOutputNote("Testing Record (%d, '%s')", g_TestValues[Index].FormID, g_TestValues[Index].pEditorID);

    OBTEST_START_TEST("Find record by formID")
        pBase = File.FindFormID(g_TestValues[Index].FormID);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()
    if (pBase == NULL) continue;
    
    OBTEST_START_TEST("Check record type")
	OBTEST_DOCOMPARE(pBase->IsRecord(), ==, true)
    OBTEST_END_TEST()
    if (!pBase->IsRecord()) continue;

    OBTEST_START_TEST("Check record name")
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_SPEL)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_SPEL) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObSpelRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check autocalc")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_MANUALCALC) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsAutoCalc(), ==, !Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check player start")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_PLAYERSTART) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsPlayerStart(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check ignore LOS")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_IGNORELOS) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsIgnoreLOS(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check silence immune")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_SILENCEIMMUNE) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsSilenceImmune(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check always apply script")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_ALWAYSAPPLYSCRIPT) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsAlwaysApplyScript(), ==, Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check absorb reflect")
	Flag = (g_TestValues[Index].Data.Flags & OB_SPELFLAG_NOABSORBREFLECT) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsAbsorbReflect(), ==, !Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check level")
	OBTEST_DOINTCOMPARE(pRecord->GetLevel(), ==, g_TestValues[Index].Data.SpellLevel);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check type")
	OBTEST_DOINTCOMPARE(pRecord->GetType(), ==, g_TestValues[Index].Data.Type);
    OBTEST_END_TEST()     

    OBTEST_START_TEST("Check cost")
	OBTEST_DOINTCOMPARE(pRecord->GetCost(), ==, g_TestValues[Index].Data.SpellCost);
    OBTEST_END_TEST()    
    
    for (Index1 = 0; g_TestValues[Index].Effects[Index1] != NULL; ++Index1) { 
      pTestEffect = g_TestValues[Index].Effects[Index1];

      OBTEST_START_TEST("Find effect")
	    pEffect = pRecord->FindEffect(Index1);
	    OBTEST_DOCOMPARE(pEffect, !=, NULL)
      OBTEST_END_TEST()    
      if (pEffect == NULL) continue;

      OBTEST_START_TEST("Check effect type")
	    OBTEST_DOCOMPARE(pEffect->GetName(), ==, OB_NAME_EFID)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect name")
	    OBTEST_DOCOMPARE(pEffect->GetDataName(), ==, *pTestEffect->pName)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Get effect data")
	    pEfit = pRecord->GetEffectData(pEffect);
	    OBTEST_DOINTCOMPARE(pEffect, !=, NULL)
      OBTEST_END_TEST()
      if (pEfit == NULL) continue;

      OBTEST_START_TEST("Check effect data type")
	    OBTEST_DOCOMPARE(pEfit->GetName(), ==, OB_NAME_EFIT)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect type")
	    OBTEST_DOINTCOMPARE(pEfit->GetEffectType(), ==, pTestEffect->Type)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect area")
	    OBTEST_DOINTCOMPARE(pEfit->GetArea(), ==, pTestEffect->Area)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect magnitude")
	    OBTEST_DOINTCOMPARE(pEfit->GetMagnitude(), ==, pTestEffect->Magnitude)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect duration")
	    OBTEST_DOINTCOMPARE(pEfit->GetDuration(), ==, pTestEffect->Duration)
      OBTEST_END_TEST()

      OBTEST_START_TEST("Check effect actor value")
	    OBTEST_DOINTCOMPARE(pEfit->GetActorValue(), ==, pTestEffect->ActorValue)
      OBTEST_END_TEST()

      if (*pTestEffect->pName == OB_MGEF_SEFF) {

	OBTEST_START_TEST("Get script effect data")
		pScit = pRecord->GetScriptEffectData(pEffect);
		OBTEST_DOCOMPARE(pScit, !=, NULL)
	OBTEST_END_TEST()

	OBTEST_START_TEST("Check script effect script ID")
	    OBTEST_DOINTCOMPARE(pScit->GetScriptFormID(), ==, pTestEffect->ScriptID)
        OBTEST_END_TEST()

	OBTEST_START_TEST("Check script effect school")
	    OBTEST_DOINTCOMPARE(pScit->GetSchool(), ==, pTestEffect->School)
        OBTEST_END_TEST()

	OBTEST_START_TEST("Check script effect visual effect")
	    OBTEST_DOCOMPARE(pScit->GetVisualEffect(), ==, *pTestEffect->pVisualEffect)
        OBTEST_END_TEST()

	OBTEST_START_TEST("Check script effect hostile")
	    Flag = (pTestEffect->Flags & OBSCIT_FLAG_HOSTILE) != 0; 
	    OBTEST_DOINTCOMPARE(pScit->IsHostile(), ==, Flag)
        OBTEST_END_TEST()

	OBTEST_START_TEST("Get script effect name")
		pScriptName = pRecord->GetScriptEffectName(pEffect);
		OBTEST_DOCOMPARE(pScriptName, !=, NULL)
	OBTEST_END_TEST()

	OBTEST_START_TEST("Check script effect name")
		OBTEST_DOSTRCOMPARE(pScriptName, ==, pTestEffect->pScript)
	OBTEST_END_TEST()
       }

     }
   }

  return (true);
 }
/*===========================================================================
 *		End of Function TestSpel_Input()
 *=========================================================================*/







