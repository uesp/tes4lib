/*===========================================================================
 *
 * File:	TestEnch.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 16, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "testEnch.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 	dword Type;
	dword ChargeAmount;
	dword EnchantCost;
	dword Flags;

  testeff_t
	obrectype*	pName;
	dword		Type;
	dword		Magnitude;
	dword		Area;
	dword		Duration;
	dword		ActorValue;

	obformid_t	ScriptID;
	dword		School;
	obrectype_t*	pVisualEffect;
	dword		Flags;
	const SSCHAR*	pScript;
 *
 *=========================================================================*/
testeff_t g_Effect1 = {	&OB_MGEF_FIDG, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0, 0, NULL, 0, NULL };
testeff_t g_Effect2 = {	&OB_MGEF_FIDG, OBEFIT_TYPE_TOUCH, 1, 2, 3, 0, 0, 0, NULL, 0, NULL };
testeff_t g_Effect3 = {	&OB_MGEF_FIDG, OBEFIT_TYPE_TARGET, 1, 2, 3, 0, 0, 0, NULL, 0, NULL };
testeff_t g_Effect4 = {	&OB_MGEF_FIDG, OBEFIT_TYPE_TARGET, 1, 2, 3, OB_ACTORVALUE_LUCK, 0, 0, NULL, 0, NULL };
testeff_t g_Effect5 = {	&OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, 0, &OB_NAME_FULL, 0, "script name" };
testeff_t g_Effect6 = {	&OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_ALTERATION, &OB_NAME_FULL, 0, "alteration" };
testeff_t g_Effect7 = {	&OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_CONJURATION, &OB_NAME_FULL, 0, "conjuration" };
testeff_t g_Effect8 = {	&OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_DESTRUCTION, &OB_NAME_FULL, 0, "destruction" };
testeff_t g_Effect9 = {	&OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_ILLUSION, &OB_NAME_FULL, 0, "illusion" };
testeff_t g_Effect10= { &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_MYSTICISM, &OB_NAME_FULL, 0, "mysticism" };
testeff_t g_Effect11= { &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, OBSCIT_SCHOOL_RESTORATION, &OB_NAME_FULL, 0, "restoration" };
testeff_t g_Effect12= { &OB_MGEF_SEFF, OBEFIT_TYPE_SELF, 1, 2, 3, 0, 0x1234, 0, &OB_NAME_FULL, OBSCIT_FLAG_HOSTILE, "hostile" };



testench_t g_TestData = {
	0x00180000,
	{ 1, 2, 3, 0 }, 
	"enchant_test", NULL, NULL, NULL, NULL, NULL
 };

static testench_t g_TestValues[] = {
	{ 0x00180001, { 1, 2, 3, 0 },	"ench_test", NULL, NULL, NULL, NULL, NULL },
	{ 0x00180002, { OB_ENCHTYPE_SCROLL, 2, 3, 0 },	"ench_scroll",  NULL, NULL, NULL, NULL, NULL  },
	{ 0x00180003, { OB_ENCHTYPE_STAFF, 2, 3, 0 },	"ench_staff",  NULL, NULL, NULL, NULL, NULL  },
	{ 0x00180004, { OB_ENCHTYPE_WEAPON, 2, 3, 0 },	"ench_weapon",  NULL, NULL, NULL, NULL, NULL  },
	{ 0x00180005, { OB_ENCHTYPE_APPAREL, 2, 3, 0 },	"ench_apparel", NULL, NULL, NULL, NULL, NULL   },
	{ 0x00180006, { 0, 2, 3, OB_ENCHFLAG_MANUALCALC },	"ench_noautocalc",   NULL, NULL, NULL, NULL, NULL },
	{ 0x00180007, { 0, 0, 0, 0 },	"ench_null",   NULL, NULL, NULL, NULL, NULL },
	{ 0x00180008, { 1, 2, 3, 0 },	"ench_eff_self", &g_Effect1, NULL, NULL, NULL, NULL },
	{ 0x00180009, { 1, 2, 3, 0 },	"ench_eff_touch", &g_Effect2, NULL, NULL, NULL, NULL },
	{ 0x00180010, { 1, 2, 3, 0 },	"ench_eff_target", &g_Effect3, NULL, NULL, NULL, NULL },
	{ 0x00180011, { 1, 2, 3, 0 },	"ench_eff_luck", &g_Effect4, NULL, NULL, NULL, NULL },
	{ 0x00180012, { 1, 2, 3, 0 },	"ench_eff_script", &g_Effect5, NULL, NULL, NULL, NULL },
	{ 0x00180013, { 1, 2, 3, 0 },	"ench_eff_alter", &g_Effect6, NULL, NULL, NULL, NULL },
	{ 0x00180014, { 1, 2, 3, 0 },	"ench_eff_conj", &g_Effect7 , NULL, NULL, NULL, NULL},
	{ 0x00180015, { 1, 2, 3, 0 },	"ench_eff_dest", &g_Effect8, NULL, NULL, NULL, NULL },
	{ 0x00180016, { 1, 2, 3, 0 },	"ench_eff_ill", &g_Effect9, NULL, NULL, NULL, NULL },
	{ 0x00180017, { 1, 2, 3, 0 },	"ench_eff_mys", &g_Effect10, NULL, NULL, NULL, NULL },
	{ 0x00180018, { 1, 2, 3, 0 },	"ench_eff_rest", &g_Effect11, NULL, NULL, NULL, NULL },
	{ 0x00180019, { 1, 2, 3, 0 },	"ench_eff_hostile", &g_Effect12, NULL, NULL, NULL, NULL },
	{ 0x00180020, { 1, 2, 3, 0 },	"ench_eff2", &g_Effect1, &g_Effect2, NULL, NULL, NULL },
	{ 0x00180021, { 1, 2, 3, 0 },	"ench_eff3", &g_Effect1, &g_Effect2, &g_Effect3, NULL, NULL },
	{ 0x00180022, { 1, 2, 3, 0 },	"ench_eff4", &g_Effect1, &g_Effect2, &g_Effect3, &g_Effect4, NULL },
	{ 0x00180023, { 1, 2, 3, 0 },	"ench_eff5", &g_Effect1, &g_Effect2, &g_Effect3,&g_Effect4, &g_Effect5 },
	{ 0, { 0, 0, 0, 0 }, NULL, NULL, NULL, NULL, NULL, NULL  }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestEnch_SetGet (void);
 *
 * Tests basic set/get methods of an ENCH record.
 *
 *=========================================================================*/
bool TestEnch_SetGet (void) {
  CObEnchRecord	    Record;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfitEffect;
  CObScitSubrecord* pScitEffect;
  const SSCHAR*     pEffectName;
  bool		    Result;

  OBTEST_LEVEL("ENCH Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchant Type")
	Record.SetEnchantType(g_TestData.Data.Type);
	OBTEST_DOINTCOMPARE(Record.GetEnchantType(), ==, g_TestData.Data.Type)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchant Cost")
	Record.SetEnchantCost(g_TestData.Data.EnchantCost);
	OBTEST_DOINTCOMPARE(Record.GetEnchantCost(), ==, g_TestData.Data.EnchantCost)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Enchant Charge Amount")
	Record.SetChargeAmount(g_TestData.Data.ChargeAmount);
	OBTEST_DOINTCOMPARE(Record.GetChargeAmount(), ==, g_TestData.Data.ChargeAmount)
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

  //bool SetEffectData       (CObEfidSubrecord* pEffect, const dword Type, const dword Magnitude, const dword Area, const dword Duration, const dword ActorValue = 0);
  //bool SetScriptEffectData (CObEfidSubrecord* pEffect, const obformid_t ScriptFormID, const dword School, const obrectype_t VisualEffect = OB_NAME_NULL, const bool Hostile = true);
  //bool SetScriptEffectName (CObEfidSubrecord* pEffect, const SSCHAR* pString);


  return (true);
 }
/*===========================================================================
 *		End of Function TestEnch_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestEnch_Output (File);
 *
 * Outputs basic ENCH records to the given file.
 *
 *=========================================================================*/
bool TestEnch_Output (CObEspFile& File) {
  CObEnchRecord*    pRecord;
  CObBaseRecord*    pBase;
  CObNameSubrecord* pEffect;
  testeff_t*	    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;
  bool		    Result;

  OBTEST_LEVEL("ENCH Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
  
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_ENCH);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObEnchRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    pRecord->SetEnchantCost(g_TestValues[Index].Data.EnchantCost);
    pRecord->SetEnchantType(g_TestValues[Index].Data.Type);
    pRecord->SetChargeAmount(g_TestValues[Index].Data.ChargeAmount);

    if (g_TestValues[Index].Data.Flags & OB_ENCHFLAG_MANUALCALC) 
      pRecord->SetAutoCalc(false);
    else
      pRecord->SetAutoCalc(true);

    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);

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
 *		End of Function TestEnch_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestEnch_Input (File);
 *
 * Checks the values of ENCH records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestEnch_Input (CObEspFile& File) {
  CObBaseRecord*    pBase;
  CObEnchRecord*    pRecord;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfit;
  CObScitSubrecord* pScit;
  const SSCHAR*     pScriptName;
  testeff_t*	    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;

  OBTEST_LEVEL("ENCH Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_ENCH)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_ENCH) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObEnchRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check autocalc")
	Flag = (g_TestValues[Index].Data.Flags & OB_ENCHFLAG_MANUALCALC) != 0;
	OBTEST_DOINTCOMPARE(pRecord->IsAutoCalc(), ==, !Flag);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check charge amount")
	OBTEST_DOINTCOMPARE(pRecord->GetChargeAmount(), ==, g_TestValues[Index].Data.ChargeAmount);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check type")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantType(), ==, g_TestValues[Index].Data.Type);
    OBTEST_END_TEST()     

    OBTEST_START_TEST("Check enchant cost")
	OBTEST_DOINTCOMPARE(pRecord->GetEnchantCost(), ==, g_TestValues[Index].Data.EnchantCost);
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
 *		End of Function TestEnch_Input()
 *=========================================================================*/







