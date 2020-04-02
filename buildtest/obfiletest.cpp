

#include "common/oberror.h"
#include "stdio.h"
#include "common/oblogfile.h"
#include "common/oberrorhandler.h"
#include "modfile/obespfile.h"
#include <iostream>
#include <vector>
#include "conio.h"
#include "windows.h"


int Test_sstring_RandomStress (const int NumTests);
//using namespace std;


std::vector<int*> TestArray;

CObEspFile EspFile(2000000);

void OutputText (void) {
  CObFile  File;
  CObFile  OutputFile;
  bool     Result;
  dword    TextOffset;
  int      Index;
  CSString Buffer;
  char     Text[32];

  Result = File.Open("h:\\oblivion\\TESConstructionSet.exe", "rb");
  if (!Result) return;
  Result = OutputFile.Open("index.txt", "wt");
  if (!Result) return;

  for (Index = 0; Index < 252; ++Index) {
    File.Seek(0x4e1390 + Index*32 + 1);

    Result = File.ReadDWord(TextOffset);  
    if (!Result) return;

    TextOffset -= 0x00400000;
    File.Seek(TextOffset);

    File.Read(Text, 31);

    Buffer.Format("%d = %s\n", Index, Text);
    OutputFile.Write(Buffer.c_str(), Buffer.GetLength());
   }

 }
  

int main (void) {
  CSString Test;
  DWORD    StartTick;
  DWORD	   EndTick;
  bool	   Result = true;

  #define TEST1(object) SystemLog.Printf("'%s'", #object);

  SystemLog.Open("test.log");
  SystemLog.Printf("Output test %d", 1234);
  Test.Format("Testing %d\n", 10);
  printf ("%s", Test.c_str());
  TEST1(Test);

  //AddObUserError(OBERR_USER_NULL, "Null received"); 
  //Test_sstring_RandomStress(10);

  //OutputText();

  StartTick = GetTickCount();

  //EspFile.Load("test1.esp");
  Result = EspFile.Load("h:\\oblivion\\data\\oblivion.esm");
  //Result = EspFile.Load("testa.esp");
  if (!Result) printf("Load failed!\n");

  EndTick = GetTickCount();
  printf("Load Time = %ld ms\n", EndTick - StartTick);

  StartTick = GetTickCount();
  //EspFile.Save("test1.esp.tmp");
  Result = EspFile.Save("ob1.esm");
  //Result = EspFile.Save("testa1.esp");
  if (!Result) printf("Save failed!\n");

  EndTick = GetTickCount();
  printf("Save Time = %ld ms\n", EndTick-StartTick);

/*
  EspFile.Destroy();
  EspFile.InitializeNew();
  CObEnchRecord* pEnchant = (CObEnchRecord *) EspFile.AddNewRecord(OB_NAME_ENCH);
  pEnchant->SetEditorID("test01");
  pEnchant->SetFormID(1001);

  CObEfidSubrecord* pEffect = pEnchant->AddEffect(OB_MGEF_FIDG);
  pEnchant->SetEffectData(pEffect, 1, 2, 3, 4, 1);

  pEffect = pEnchant->AddEffect(OB_MGEF_SEFF);
  pEnchant->SetEffectData(pEffect, 7, 8, 9, 10, 11);
  pEnchant->SetScriptEffectData(pEffect, 0, 1, OB_NAME_NULL, false);
  pEnchant->SetScriptEffectName(pEffect, "aaasd");

  Result = EspFile.Save("h:\\oblivion\\data\\empty.esp");
  Result = EspFile.Save("empty.esp");
  if (!Result) printf("Save failed!\n"); */


  printf ("sizeof(obrgba_t) = %d\n", sizeof(obrgba_t));
  printf ("sizeof(CObSubrecord) = %d\n", sizeof(CObSubrecord));
  printf ("sizeof(CObBaseRecord) = %d\n", sizeof(CObBaseRecord));
  printf ("sizeof(CObGroup) = %d\n", sizeof(CObGroup));
  printf ("sizeof(CObRecord) = %d\n", sizeof(CObRecord));
  printf ("sizeof(CObSubrecContainer) = %d\n", sizeof(CObSubrecContainer));
  printf ("sizeof(obgrupheader_t) = %d\n", sizeof(obgrupheader_t));
  printf ("sizeof(obrecheader_t) = %d\n", sizeof(obrecheader_t));
 

  _getch();
  return (0);
 } 
/*

	OFST subrec 0x1d698dc - No size?

	Oblivion.ESM Size = 242 MB
		1023758 Records, 73009 Groups, 3091597 Subrecords  (4188364 total)

	Overhead = 1023758 * 28 + 73009 * 16 + 3091597 * 18 + (4188364 * 4)
		 = 28.6 M + 1.2 M + 55.6 M + 16.5 M
		 = 101.4 M

	Allocated Debug = 880 MB
	Load Time Debug = 12.5 secs
	Save Time Debug = 9 secs
	Load Time with Decompression Debug = 36 secs
	Load Time with Decompression Debug = 104 secs
	Save Time with Decompression Debug = 27 secs
	Load Time with Decompression Debug (static compression buffers) = 14 secs
	Save Time with Decompression Debug (static compression buffers) = 27 secs
	Allocated with Decompression Debug =  MB
	

	Allocated Release = 585 MB
	Load Time Release = 6 secs
	Save Time Release = 9 secs
	Load Time with Decompression Release = 62 secs
	Save Time with Decompression Release = 20 secs
	Load Time with Decompression Release (static compression buffers) = 11 secs
	Save Time with Decompression Release (static compression buffers) = 26 secs
	Allocated with Decompression Release = 778 MB

	CS Load Time = 22 secs

	35506 Compressed Records:
		Total Bytes: 159905110 to 304336973 (52.5421%, 150 MB saved)

*/

/*

CS.EXE

0x4e1390 = Start of 32 byte records?, At least 155 records
	0x4e1390
		0x68
		Offset to "Strength"
		0x68
		Offset to "sSkillNameStrength"
		0xB9
		Offset to ?
		0xE8
		dword?
		0x68
		dword?, offset to raw data?
		0xe8
		dword?
		0x59c3

	0x4E15F0
		0x68 
		Offset to "Alchemy" text in EXE
		0x68
		Offset to "sSkillNameAlchemy" text
		0xB9
		Offset to 0x5edec8 (raw data?)
		0xE8



*/

