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
#include "testsgst.h"


/*===========================================================================
 *
 * Begin Local Definitions
 *
 	dword Type;
	dword ChargeAmount;
	dword EnchantCost;
	dword Flags;

  testeff_t
	obrectype_t*	pItemName;
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
testeffsgst_t g_Effects[] = {
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



testsgst_t g_TestData = {
	0x00230000, { 1, 2, 3.0f }, "sigil_test", "Sigil Test", "model.nif", "icon.dds", 0x123, NULL, NULL, NULL, NULL, NULL
 };

static testsgst_t g_TestValues[] = {
	{ 0x00230001, { 1, 2, 3 }, "sgst_test", "Sigil Test", "model.nif", "icon.dds", 0x123, NULL, NULL, NULL, NULL, NULL },
	{ 0x00233006, { 100, 2, 3 }, "sgst_noautocalc", "Sigil Test", NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL  },
	{ 0x00230007, { 0, 200, 0 }, "sgst_null", "Sigil Test", NULL, NULL, 0, NULL, NULL, NULL, NULL, NULL  },
	{ 0x00230008, { 1, 2, 90.1f }, "sgst_eff_self", "Sigil Test", NULL, NULL, 0, &g_Effects[0], NULL, NULL, NULL, NULL },
	{ 0x00230009, { 1, 2, 3 }, "sgst_eff_touch", "Sigil Test", NULL, NULL, 0, &g_Effects[1], NULL, NULL, NULL, NULL },
	{ 0x00230010, { 1, 2, 3 }, "sgst_eff_target", "Sigil Test", NULL, NULL, 0, &g_Effects[2], NULL, NULL, NULL, NULL },
	{ 0x00230011, { 1, 2, 3 }, "sgst_eff_luck", "Sigil Test", NULL, NULL, 0, &g_Effects[3], NULL, NULL, NULL, NULL },
	{ 0x00230012, { 1, 2, 3 }, "sgst_eff_script", "Sigil Test", NULL, NULL, 0, &g_Effects[4], NULL, NULL, NULL, NULL },
	{ 0x00230013, { 1, 2, 3 }, "sgst_eff_alter", "Sigil Test", NULL, NULL, 0, &g_Effects[5], NULL, NULL, NULL, NULL },
	{ 0x00230014, { 1, 2, 3 }, "sgst_eff_conj", "Sigil Test", NULL, NULL, 0, &g_Effects[6], NULL, NULL, NULL, NULL },
	{ 0x00230015, { 1, 2, 3 }, "sgst_eff_dest", "Sigil Test", NULL, NULL, 0, &g_Effects[7], NULL, NULL, NULL, NULL },
	{ 0x00233016, { 1, 2, 3 }, "sgst_eff_ill", "Sigil Test", NULL, NULL, 0, &g_Effects[8], NULL, NULL, NULL, NULL },
	{ 0x00230017, { 1, 2, 3 }, "sgst_eff_mys", "Sigil Test", NULL, NULL, 0, &g_Effects[9], NULL, NULL, NULL, NULL },
	{ 0x00230018, { 1, 2, 3 }, "sgst_eff_rest", "Sigil Test", NULL, NULL, 0, &g_Effects[10], NULL, NULL, NULL, NULL },
	{ 0x00230019, { 1, 2, 3 }, "sgst_eff_hostile", "Sigil Test", NULL, NULL, 0, &g_Effects[11], NULL, NULL, NULL, NULL },
	{ 0x00230020, { 1, 2, 3 }, "sgst_eff2", "Sigil Test", NULL, NULL, 0, &g_Effects[0], &g_Effects[1], NULL, NULL, NULL },
	{ 0x00230021, { 1, 2, 3 }, "sgst_eff3", "Sigil Test", NULL, NULL, 0, &g_Effects[0], &g_Effects[1], &g_Effects[2], NULL, NULL },
	{ 0x00230022, { 1, 2, 3 }, "sgst_eff4", "Sigil Test", NULL, NULL, 0, &g_Effects[0], &g_Effects[1], &g_Effects[2], &g_Effects[3], NULL },
	{ 0x00230023, { 1, 2, 3 }, "sgst_eff5", "Sigil Test", NULL, NULL, 0, &g_Effects[0], &g_Effects[1], &g_Effects[2], &g_Effects[3], &g_Effects[4] },
	{ 0, { 0, 0, 0 }, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, NULL  }
 };
/*===========================================================================
 *		End of Local Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSgst_SetGet (void);
 *
 * Tests basic set/get methods of an ENCH record.
 *
 *=========================================================================*/
bool TestSgst_SetGet (void) {
  CObSgstRecord	    Record;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfitEffect;
  CObScitSubrecord* pScitEffect;
  const SSCHAR*     pEffectName;
  bool		    Result;

  OBTEST_LEVEL("SGST Set/Get")
  Record.InitializeNew();

  OBTEST_START_TEST("Editor ID")
	Record.SetEditorID(g_TestData.pEditorID);
	OBTEST_DOSTRCOMPARE(Record.GetEditorID(), ==, g_TestData.pEditorID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Item name")
	Record.SetItemName(g_TestData.pItemName);
	OBTEST_DOSTRCOMPARE(Record.GetItemName(), ==, g_TestData.pItemName)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Model")
	Record.SetModel(g_TestData.pModel);
	OBTEST_DOSTRCOMPARE(Record.GetModel(), ==, g_TestData.pModel)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Icon")
	Record.SetIcon(g_TestData.pIcon);
	OBTEST_DOSTRCOMPARE(Record.GetIcon(), ==, g_TestData.pIcon)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Script ID")
	Record.SetScript(g_TestData.ScriptID);
	OBTEST_DOINTCOMPARE(Record.GetScript(), ==, g_TestData.ScriptID)
  OBTEST_END_TEST()  

  OBTEST_START_TEST("Form ID")
	Record.SetFormID(g_TestData.FormID);
	OBTEST_DOINTCOMPARE(Record.GetFormID(), ==, g_TestData.FormID)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Weight")
	Record.SetWeight(g_TestData.Data.Weight);
	OBTEST_DOFLTCOMPARE(Record.GetWeight(), ==, g_TestData.Data.Weight)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Value")
	Record.SetValue(g_TestData.Data.Value);
	OBTEST_DOINTCOMPARE(Record.GetValue(), ==, g_TestData.Data.Value)
  OBTEST_END_TEST()

  OBTEST_START_TEST("Uses")
	Record.SetUses(g_TestData.Data.Uses);
	OBTEST_DOINTCOMPARE(Record.GetUses(), ==, g_TestData.Data.Uses)
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
 *		End of Function TestSgst_SetGet()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSgst_Output (File);
 *
 * Outputs basic SGST records to the given file.
 *
 *=========================================================================*/
bool TestSgst_Output (CObEspFile& File) {
  CObSgstRecord*    pRecord;
  CObBaseRecord*    pBase;
  CObNameSubrecord* pEffect;
  testeffsgst_t*    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;
  bool		    Result;

  OBTEST_LEVEL("SGST Output")

  for (Index = 0; g_TestValues[Index].FormID != OB_FORMID_NULL; ++Index) {
  
    OBTEST_START_TEST("Create new record")
	pBase = File.AddNewRecord(OB_NAME_SGST);
	OBTEST_DOCOMPARE(pBase, !=, NULL)
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check Class")
    	pRecord = ObCastClass(CObSgstRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;
  
    pRecord->SetFormID(g_TestValues[Index].FormID);
    pRecord->SetScript(g_TestValues[Index].ScriptID);
    if (g_TestValues[Index].pItemName != NULL) pRecord->SetItemName(g_TestValues[Index].pItemName);
    if (g_TestValues[Index].pEditorID != NULL) pRecord->SetEditorID(g_TestValues[Index].pEditorID);
    if (g_TestValues[Index].pModel    != NULL) pRecord->SetModel(g_TestValues[Index].pModel);
    if (g_TestValues[Index].pIcon     != NULL) pRecord->SetIcon(g_TestValues[Index].pIcon);
    pRecord->SetWeight(g_TestValues[Index].Data.Weight);
    pRecord->SetValue(g_TestValues[Index].Data.Value);
    pRecord->SetUses(g_TestValues[Index].Data.Uses);

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
 *		End of Function TestSgst_Output()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool TestSgst_Input (File);
 *
 * Checks the values of SGST records in the given file and ensures they 
 * match those previously output.
 *
 *=========================================================================*/
bool TestSgst_Input (CObEspFile& File) {
  CObBaseRecord*    pBase;
  CObSgstRecord*    pRecord;
  CObEfidSubrecord* pEffect;
  CObEfitSubrecord* pEfit;
  CObScitSubrecord* pScit;
  const SSCHAR*     pScriptName;
  testeffsgst_t*    pTestEffect;
  dword		    Index;
  dword		    Index1;
  bool		    Flag;

  OBTEST_LEVEL("SGST Input")

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
	OBTEST_DOCOMPARE(pBase->GetName(), ==, OB_NAME_SGST)
    OBTEST_END_TEST()
    if (pBase->GetName() != OB_NAME_SGST) continue;

    OBTEST_START_TEST("Check class")
    	pRecord = ObCastClass(CObSgstRecord, pBase);
	OBTEST_DOCOMPARE(pRecord, !=, NULL)
    OBTEST_END_TEST()
    if (pRecord == NULL) continue;

    OBTEST_START_TEST("Check editor ID name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetEditorID(), ==, g_TestValues[Index].pEditorID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check item name")
	OBTEST_DOSTRCOMPARE1(pRecord->GetItemName(), ==, g_TestValues[Index].pItemName);
    OBTEST_END_TEST()
    
    OBTEST_START_TEST("Check model")
	OBTEST_DOSTRCOMPARE1(pRecord->GetModel(), ==, g_TestValues[Index].pModel);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check icon")
	OBTEST_DOSTRCOMPARE1(pRecord->GetIcon(), ==, g_TestValues[Index].pIcon);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check script formID")
	OBTEST_DOINTCOMPARE(pRecord->GetScript(), ==, g_TestValues[Index].ScriptID);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check weight")
	OBTEST_DOFLTCOMPARE(pRecord->GetWeight(), ==, g_TestValues[Index].Data.Weight);
    OBTEST_END_TEST()

    OBTEST_START_TEST("Check value")
	OBTEST_DOINTCOMPARE(pRecord->GetValue(), ==, g_TestValues[Index].Data.Value);
    OBTEST_END_TEST()     

    OBTEST_START_TEST("Check uses")
	OBTEST_DOINTCOMPARE(pRecord->GetUses(), ==, g_TestValues[Index].Data.Uses);
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
 *		End of Function TestSgst_Input()
 *=========================================================================*/







