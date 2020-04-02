/*===========================================================================
 *
 * File:	ObScriptutils.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	December 4, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obscriptutils.h"


/*===========================================================================
 *
 * Function - bool ObCompareScriptTextPriv (CompareInfo);
 *
 *=========================================================================*/
bool ObCompareScriptTextPriv (obscriptcompare_t& CompareInfo) {
  int Result;

	/* Check the script text sizes */
  if (CompareInfo.pScript1->GetScriptSize() != CompareInfo.pScript2->GetScriptSize()) {
    SystemLog.Printf("\tScript texts are not the same size: %u != %u bytes", CompareInfo.pScript1->GetScriptSize(), CompareInfo.pScript2->GetScriptSize());
    return (false);
  }

	/* Do a straight comparison at first */
  Result = strcmp(CompareInfo.pScript1->GetScriptText(), CompareInfo.pScript2->GetScriptText());
  if (Result == 0) return (false);

	/* Do a case insenstive comparison */
  Result = stricmp(CompareInfo.pScript1->GetScriptText(), CompareInfo.pScript2->GetScriptText());

  if (Result == 0) {
    SystemLog.Printf("\tScript texts differ only by case!");
    return (true);
  }

  SystemLog.Printf("\tScript texts are not identical!");
  return (false);
}
/*===========================================================================
 *		End of Function ObCompareScriptTextPriv
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompareScriptInfoPriv (CompareInfo);
 *
 *=========================================================================*/
bool ObCompareScriptInfoPriv (obscriptcompare_t& CompareInfo) {
  bool Compare = true;

	/* Compare the local variable count */
  if (CompareInfo.pScript1->GetVariableCount() != CompareInfo.pScript2->GetVariableCount()) {
    SystemLog.Printf("\tScript local variable counts are not the same: %u != %u", CompareInfo.pScript1->GetVariableCount(), CompareInfo.pScript2->GetVariableCount());
    Compare = false;
  }

	/* Compare the reference variable count */
  if (CompareInfo.pScript1->GetRefCount() != CompareInfo.pScript2->GetRefCount()) {
    SystemLog.Printf("\tScript reference variable counts are not the same: %u != %u", CompareInfo.pScript1->GetRefCount(), CompareInfo.pScript2->GetRefCount());
    Compare = false;
  }

  return (Compare);
}
/*===========================================================================
 *		End of Function ObCompareScriptInfoPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompareScriptLocalPriv (CompareInfo);
 *
 *=========================================================================*/
bool ObCompareScriptLocalPriv (obscriptcompare_t& CompareInfo) {
  CObSlsdSubrecord*   pLocal1;
  CObSlsdSubrecord*   pLocal2;
  CObStringSubrecord* pName1;
  CObStringSubrecord* pName2;
  bool                Result;
  int	              LocalPos;

	/* Iterate through all locals defined in script1 */
  Result = CompareInfo.pScript1->FindFirstVariable(pLocal1, pName1, LocalPos);

  while (Result) {

		/* Find the local variable in script2 */
    pLocal2 = CompareInfo.pScript2->FindVariable(pName1->GetString());

    if (pLocal2 == NULL) {
      SystemLog.Printf("\tScript1 local variable '%s' was not found in script2!", pName1->GetString());
    }
		/* Compare the local variable data */
    else {
      if (pLocal1->GetSlsdData().Index != pLocal2->GetSlsdData().Index) {
        SystemLog.Printf("\tScript local variable '%s' indexes do not match: %u != %u", pName1->GetString(), pLocal1->GetSlsdData().Index, pLocal2->GetSlsdData().Index);
      }

      if (pLocal1->IsShortLong() != pLocal2->IsShortLong()) {
        SystemLog.Printf("\tScript local variable '%s' types do not match!", pName1->GetString(), pLocal1->GetSlsdData().Index, pLocal2->GetSlsdData().Index);
      }
    }
    
    Result = CompareInfo.pScript1->FindNextVariable(pLocal1, pName1, LocalPos);
  }

  	/* Find any locals in script2 not in script1 */
  Result = CompareInfo.pScript2->FindFirstVariable(pLocal2, pName2, LocalPos);

  while (Result) {
    pLocal1 = CompareInfo.pScript1->FindVariable(pName2->GetString());
    if (pLocal2 == NULL) SystemLog.Printf("\tScript2 local variable '%s' was not found in script1!", pName1->GetString());

    Result = CompareInfo.pScript2->FindNextVariable(pLocal2, pName2, LocalPos);
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObCompareScriptLocalPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompareScriptRefPriv (CompareInfo);
 *
 *=========================================================================*/
bool ObCompareScriptRefPriv (obscriptcompare_t& CompareInfo) {

	/* TODO */

  return (true);
}
/*===========================================================================
 *		End of Function ObCompareScriptRefPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompScript_GetWord (Data);
 *
 *=========================================================================*/
bool ObCompScript_GetWord (word& WordResult, obscriptdatacomp_t& Data) {

  if (Data.Index1 + 2 > Data.Size1) {
    SystemLog.Printf("\tScript1 is too short to match word value!");
    return (false);
  }
  else if (Data.Index2 + 2 > Data.Size2) {
    SystemLog.Printf("\tScript2 is too short to match word value!");
    return (false);
  }

  if (*(long *)(Data.pData1 + Data.Index1) != *(long *)(Data.pData2 + Data.Index2)) {
    SystemLog.Printf("\tScripts do not match word values at offset 0x%04X (%04X != %04X)!", Data.Index1, *(long *)(Data.pData1 + Data.Index1), *(long *)(Data.pData2 + Data.Index2));
    return (false);
  }
  
  WordResult = *(word *)(Data.pData1 + Data.Index1);
  Data.Index1 += 2;
  Data.Index2 += 2;

  return (true);
}
/*===========================================================================
 *		End of Function ObCompScript_GetWord()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompScript_MatchLong (Data);
 *
 *=========================================================================*/
bool ObCompScript_MatchLong (obscriptdatacomp_t& Data, const long Value) {

  if (Data.Index1 + 4 > Data.Size1) {
    SystemLog.Printf("\tScript1 is too short to match long value 0x%08X!", Value);
    return (false);
  }
  else if (Data.Index2 + 4 > Data.Size2) {
    SystemLog.Printf("\tScript2 is too short to match long value 0x%08X!", Value);
    return (false);
  }

  if (*(long *)(Data.pData1 + Data.Index1) != Value) {
    SystemLog.Printf("\tScript1 does not match value 0x%08X (actual 0x%08X) at offset 0x%04X!", Value, *(long *)(Data.pData1 + Data.Index1), Data.Index1);
    return (false);
  }
  else if (*(long *)(Data.pData2 + Data.Index2) != Value) {
    SystemLog.Printf("\tScript2 does not match value 0x%08X (actual 0x%08X) at offset 0x%04X!", Value, *(long *)(Data.pData2 + Data.Index2), Data.Index2);
    return (false);
  }

  Data.Index1 += 4;
  Data.Index2 += 4;

  return (true);
}
/*===========================================================================
 *		End of Function ObCompScript_MatchLong()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompScript_Begin (Data);
 *
 *=========================================================================*/
bool ObCompScript_Begin (obscriptdatacomp_t& Data) {
  bool Result;
  word WordValue;

	/* Scripts should both start with a SCN section */
  Result = ObCompScript_GetWord(WordValue, Data);
  if (!Result) return (false);

  if (WordValue != 0x0010) {
    SystemLog.Printf("\tScript missing begin block in data (0x0010 != 0x%04X) at offset 0x%04X!", WordValue, Data.Index1);
    return (false);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Function ObCompScript_Begin()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompScript_Start (Data);
 *
 *=========================================================================*/
bool ObCompScript_Start (obscriptdatacomp_t& Data) {
  bool Result;

	/* Scripts should both start with a SCN section */
  Result = ObCompScript_MatchLong(Data, 0x1d);
  if (!Result) return (false);

	/* Match all begin blocks */
  while (Data.Index1 < Data.Size1) {
    Result = ObCompScript_Begin(Data);
    if (!Result) return (false);
  }
  
  return (true);
}
/*===========================================================================
 *		End of Function ObCompScript_Start()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompScript_RawData (Data);
 *
 *=========================================================================*/
bool ObCompScript_RawData (obscriptdatacomp_t& Data) {
  int ErrorCount = 0;

  while (Data.Index1 < Data.Size1 && Data.Index2 < Data.Size2) {

    if (Data.pData1[Data.Index1] == Data.pData2[Data.Index2]) {
      ++Data.Index1;
      ++Data.Index2;
      continue;
    }

    ++ErrorCount;

    if (Data.Index1 + 1 < Data.Size1 && Data.pData1[Data.Index1 + 1] == Data.pData2[Data.Index2]) {
      SystemLog.Printf("\tScript data inserted byte in script1 at offsets 0x%04X/0x%04X: %02X", Data.Index1, Data.Index2, Data.pData1[Data.Index1]);
    }
    else if (Data.Index2 + 1 < Data.Size2 && Data.pData1[Data.Index1] == Data.pData2[Data.Index2 + 1]) {
      SystemLog.Printf("\tScript data deleted byte from script1 at offsets 0x%04X/0x%04X: %02X", Data.Index1, Data.Index2, Data.pData2[Data.Index2]);
    }
    else {
      SystemLog.Printf("\tScript data mismatch at offsets 0x%04X/0x%04X: %02X != %02X", Data.Index1, Data.Index2, Data.pData1[Data.Index1], Data.pData2[Data.Index2]);
    }

    if (ErrorCount > 10) {
      SystemLog.Printf("\tAborting comparison of script compiled data (reached limit of %u errors)!", ErrorCount);
      return (false);
    }
  }

  if (Data.Index1 < Data.Size1) {
    SystemLog.Printf("\tExtra %u bytes in script1 data!", Data.Size1, Data.Index1);
    return (false);
  }
  else if (Data.Index2 < Data.Size2) {
    SystemLog.Printf("\tExtra %u bytes in script2 data!", Data.Size2, Data.Index2);
    return (false);
  }

  return (true);
}
/*===========================================================================
 *		End of Function ObCompScript_RawData()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ObCompareScriptDataPriv (CompareInfo);
 *
 *=========================================================================*/
bool ObCompareScriptDataPriv (obscriptcompare_t& CompareInfo) {
  obscriptdatacomp_t Data;

  Data.pData1  = CompareInfo.pScript1->GetScriptData();
  Data.pData2  = CompareInfo.pScript2->GetScriptData();
  Data.Size1   = CompareInfo.pScript1->GetCompiledSize();
  Data.Size2   = CompareInfo.pScript2->GetCompiledSize();
  Data.Index1  = 0;
  Data.Index2  = 0;

	/* Ensure valid compiled data */
  if (Data.pData1 == NULL && Data.pData2 == NULL) {
    return (true);
  }
  else if (Data.pData1 == NULL || Data.Size1 == 0) {
    SystemLog.Printf("\tScript1 has no compiled data!");    
    return (false);
  }
  else if (Data.pData2 == NULL || Data.Size2 == 0) {
    SystemLog.Printf("\tScript2 has no compiled data!");    
    return (false);
  }
  else if (Data.Size1 != Data.Size2) {
    SystemLog.Printf("\tScript compiled data sizes do not match: %d != %d", Data.Size1, Data.Size2);
  }

	/* Simple data compare */
  return ObCompScript_RawData(Data);

	/* Parse the scripts */
  //return ObCompScript_Start(Data);
}
/*===========================================================================
 *		End of Function ObCompareScriptDataPriv()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - int ObCompareScripts (CompareInfo);
 *
 * Compares the given two scripts for equality. Returns true if they are 
 * exactly equal. Outputs all errors/warnings to the system log.
 *
 *=========================================================================*/
bool ObCompareScripts (obscriptcompare_t& CompareInfo) {

	/* Ignore invalid input */
  if (CompareInfo.pScript1 == NULL || CompareInfo.pScript2 == NULL) {
    SystemLog.Printf("\tInvalid NULL script record(s) received!");
    return (false);
  }

  ObCompareScriptTextPriv(CompareInfo);
  ObCompareScriptInfoPriv(CompareInfo);
  ObCompareScriptLocalPriv(CompareInfo);
  ObCompareScriptRefPriv(CompareInfo);
  ObCompareScriptDataPriv(CompareInfo);

  return (true);
}
/*===========================================================================
 *		End of Function ObCompareScripts()
 *=========================================================================*/

