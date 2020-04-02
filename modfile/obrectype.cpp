/*===========================================================================
 *
 * File:	ObRecType.CPP
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 9, 2006
 *
 * Description
 *
 *=========================================================================*/

	/* Include Files */
#include "obrectype.h"


/*===========================================================================
 *
 * Begin Standard Record Names
 *
 *=========================================================================*/

	/* Special names */
  const obrectype_t OB_NAME_NULL = "\0\0\0\0";

	/* Special group name */
  const obrectype_t OB_NAME_GRUP = "GRUP";
	
	/* Known record names */
  const obrectype_t OB_NAME_AMMO = "AMMO";
  const obrectype_t OB_NAME_ARMO = "ARMO";
  const obrectype_t OB_NAME_APPA = "APPA";
  const obrectype_t OB_NAME_BOOK = "BOOK";
  const obrectype_t OB_NAME_CELL = "CELL";
  const obrectype_t OB_NAME_CLOT = "CLOT";
  const obrectype_t OB_NAME_ENCH = "ENCH";
  const obrectype_t OB_NAME_FLOR = "FLOR";
  const obrectype_t OB_NAME_INGR = "INGR";
  const obrectype_t OB_NAME_LAND = "LAND";
  const obrectype_t OB_NAME_LIGH = "LIGH";
  const obrectype_t OB_NAME_LVLI = "LVLI";
  const obrectype_t OB_NAME_MISC = "MISC";
  const obrectype_t OB_NAME_NPC_ = "NPC_";
  const obrectype_t OB_NAME_PGRD = "PGRD";
  const obrectype_t OB_NAME_REFR = "REFR";
  const obrectype_t OB_NAME_SCPT = "SCPT";
  const obrectype_t OB_NAME_SGST = "SGST";
  const obrectype_t OB_NAME_SOUN = "SOUN";
  const obrectype_t OB_NAME_SPEL = "SPEL";
  const obrectype_t OB_NAME_TES4 = "TES4";
  const obrectype_t OB_NAME_WEAP = "WEAP";
  const obrectype_t OB_NAME_WRLD = "WRLD";

  const obrectype_t OB_NAME_ACHR = "ACHR";
  const obrectype_t OB_NAME_ACRE = "ACRE";
  const obrectype_t OB_NAME_ACTI = "ACTI";
  const obrectype_t OB_NAME_ALCH = "ALCH";
  const obrectype_t OB_NAME_ANIO = "ANIO";
  const obrectype_t OB_NAME_BSGN = "BSGN";
  const obrectype_t OB_NAME_CLAS = "CLAS";
  const obrectype_t OB_NAME_CLMT = "CLMT";
  const obrectype_t OB_NAME_CONT = "CONT";
  const obrectype_t OB_NAME_CSTY = "CSTY";
  const obrectype_t OB_NAME_CREA = "CREA";
  const obrectype_t OB_NAME_DIAL = "DIAL";
  const obrectype_t OB_NAME_DOOR = "DOOR";
  const obrectype_t OB_NAME_EFSH = "EFSH";
  const obrectype_t OB_NAME_EYES = "EYES";
  const obrectype_t OB_NAME_FURN = "FURN";
  const obrectype_t OB_NAME_GLOB = "GLOB";
  const obrectype_t OB_NAME_GMST = "GMST";
  const obrectype_t OB_NAME_GRAS = "GRAS";
  const obrectype_t OB_NAME_FACT = "FACT";
  const obrectype_t OB_NAME_HAIR = "HAIR";
  const obrectype_t OB_NAME_IDLE = "IDLE";
  const obrectype_t OB_NAME_INFO = "INFO";
  const obrectype_t OB_NAME_KEYM = "KEYM";
  const obrectype_t OB_NAME_LSCR = "LSCR";
  const obrectype_t OB_NAME_LTEX = "LTEX";
  const obrectype_t OB_NAME_LVLC = "LVLC";
  const obrectype_t OB_NAME_LVSP = "LVSP";
  const obrectype_t OB_NAME_MGEF = "MGEF";
  const obrectype_t OB_NAME_PACK = "PACK";
  const obrectype_t OB_NAME_QUST = "QUST";
  const obrectype_t OB_NAME_RACE = "RACE";
  const obrectype_t OB_NAME_REGN = "REGN";
  const obrectype_t OB_NAME_ROAD = "ROAD";
  const obrectype_t OB_NAME_SBSP = "SBSP";
  const obrectype_t OB_NAME_SKIL = "SKIL";
  const obrectype_t OB_NAME_SLGM = "SLGM";
  const obrectype_t OB_NAME_STAT = "STAT";
  const obrectype_t OB_NAME_TREE = "TREE";
  const obrectype_t OB_NAME_WATR = "WATR";
  const obrectype_t OB_NAME_WTHR = "WTHR";
/*===========================================================================
 *		End of Standard Record Names
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Standard Subrecord Names
 *
 *=========================================================================*/
  const obrectype_t OB_NAME_ANAM = "ANAM";
  const obrectype_t OB_NAME_BMDT = "BMDT";
  const obrectype_t OB_NAME_CNAM = "CNAM";
  const obrectype_t OB_NAME_ENAM = "ENAM";
  const obrectype_t OB_NAME_DATA = "DATA";
  const obrectype_t OB_NAME_DESC = "DESC";
  const obrectype_t OB_NAME_EDID = "EDID";
  const obrectype_t OB_NAME_EFID = "EFID";
  const obrectype_t OB_NAME_EFIT = "EFIT";
  const obrectype_t OB_NAME_ENIT = "ENIT";
  const obrectype_t OB_NAME_FNAM = "FNAM";
  const obrectype_t OB_NAME_FULL = "FULL";
  const obrectype_t OB_NAME_HEDR = "HEDR";
  const obrectype_t OB_NAME_LVLD = "LVLD";
  const obrectype_t OB_NAME_LVLF = "LVLF";
  const obrectype_t OB_NAME_LVLO = "LVLO";
  const obrectype_t OB_NAME_ICON = "ICON";
  const obrectype_t OB_NAME_ICO2 = "ICO2";
  const obrectype_t OB_NAME_MAST = "MAST";
  const obrectype_t OB_NAME_MODB = "MODB";
  const obrectype_t OB_NAME_MO2B = "MO2B";
  const obrectype_t OB_NAME_MO3B = "MO3B";
  const obrectype_t OB_NAME_MO4B = "MO4B";
  const obrectype_t OB_NAME_MODL = "MODL";
  const obrectype_t OB_NAME_MOD2 = "MOD2";
  const obrectype_t OB_NAME_MOD3 = "MOD3";
  const obrectype_t OB_NAME_MOD4 = "MOD4";
  const obrectype_t OB_NAME_MODT = "MODT";
  const obrectype_t OB_NAME_MO2T = "MO2T";
  const obrectype_t OB_NAME_MO3T = "MO3T";
  const obrectype_t OB_NAME_MO4T = "MO4T";
  const obrectype_t OB_NAME_NAME = "NAME";
  const obrectype_t OB_NAME_OFST = "OFST";
  const obrectype_t OB_NAME_SCDA = "SCDA";
  const obrectype_t OB_NAME_SCHR = "SCHR";
  const obrectype_t OB_NAME_SCIT = "SCIT";
  const obrectype_t OB_NAME_SCRI = "SCRI";
  const obrectype_t OB_NAME_SCRO = "SCRO";
  const obrectype_t OB_NAME_SCRV = "SCRV";
  const obrectype_t OB_NAME_SCTX = "SCTX";
  const obrectype_t OB_NAME_SCVR = "SCVR";
  const obrectype_t OB_NAME_SLSD = "SLSD";
  const obrectype_t OB_NAME_SNAM = "SNAM";
  const obrectype_t OB_NAME_SPIT = "SPIT";
  const obrectype_t OB_NAME_XTEL = "XTEL";
  const obrectype_t OB_NAME_XXXX = "XXXX";
  const obrectype_t OB_NAME_TNAM = "TNAM";
  const obrectype_t OB_NAME_SPLO = "SPLO";
  const obrectype_t OB_NAME_QNAM = "QNAM";
  const obrectype_t OB_NAME_CNTO = "CNTO";
  const obrectype_t OB_NAME_XTRG = "XTRG";
  const obrectype_t OB_NAME_XRTM = "XRTM";
  const obrectype_t OB_NAME_XESP = "XESP";
  const obrectype_t OB_NAME_XHRS = "XHRS";
  const obrectype_t OB_NAME_XMRC = "XMRC";
  const obrectype_t OB_NAME_XSCL = "XSCL";
  const obrectype_t OB_NAME_XOWN = "XOWN";
  const obrectype_t OB_NAME_XGLB = "XGLB";
  const obrectype_t OB_NAME_XRNK = "XRNK";
  const obrectype_t OB_NAME_XCCM = "XCCM";
  const obrectype_t OB_NAME_XCWT = "XCWT";
  const obrectype_t OB_NAME_XCLW = "XCLW";
  const obrectype_t OB_NAME_XCLR = "XCLR";
  const obrectype_t OB_NAME_NAM2 = "NAM2";
  const obrectype_t OB_NAME_XPCI = "XPCI";
  const obrectype_t OB_NAME_WLST = "WLST";
  const obrectype_t OB_NAME_CSCR = "CSCR";
  const obrectype_t OB_NAME_CSDI = "CSDI";
  const obrectype_t OB_NAME_INAM = "INAM";
  const obrectype_t OB_NAME_ZNAM = "ZNAM";
  const obrectype_t OB_NAME_PKID = "PKID";
  const obrectype_t OB_NAME_QSTI = "QSTI";
  const obrectype_t OB_NAME_BNAM = "BNAM";
  const obrectype_t OB_NAME_XNAM = "XNAM";
  const obrectype_t OB_NAME_PFIG = "PFIG";
  const obrectype_t OB_NAME_CTDA = "CTDA";
  const obrectype_t OB_NAME_CTDT = "CTDT";
  const obrectype_t OB_NAME_TCLF = "TCLF";
  const obrectype_t OB_NAME_TCLT = "TCLT";
  const obrectype_t OB_NAME_ATXT = "ATXT";
  const obrectype_t OB_NAME_BTXT = "BTXT";
  const obrectype_t OB_NAME_VTEX = "VTEX";
  const obrectype_t OB_NAME_LNAM = "LNAM";
  const obrectype_t OB_NAME_GNAM = "GNAM";
  const obrectype_t OB_NAME_HNAM = "HNAM";
  const obrectype_t OB_NAME_RNAM = "RNAM";
  const obrectype_t OB_NAME_PLDT = "PLDT";
  const obrectype_t OB_NAME_PTDT = "PTDT";
  const obrectype_t OB_NAME_PGRL = "PGRL";
  const obrectype_t OB_NAME_QSTA = "QSTA";
  const obrectype_t OB_NAME_DNAM = "DNAM";
  const obrectype_t OB_NAME_VNAM = "VNAM";
  const obrectype_t OB_NAME_XLOC = "XLOC";
  const obrectype_t OB_NAME_WNAM = "WNAM";
  const obrectype_t OB_NAME_RDWT = "RDWT";
  const obrectype_t OB_NAME_RDGS = "RDGS";
  const obrectype_t OB_NAME_RDOT = "RDOT";
  const obrectype_t OB_NAME_RDSD = "RDSD";
  const obrectype_t OB_NAME_SOUL = "SOUL";
  const obrectype_t OB_NAME_SLCP = "SLCP";
  const obrectype_t OB_NAME_SNDX = "SNDX";
  const obrectype_t OB_NAME_SNDD = "SNDD";
  const obrectype_t OB_NAME_PFPC = "PFPC";
  const obrectype_t OB_NAME_MNAM = "MNAM";
  const obrectype_t OB_NAME_INDX = "INDX";
/*===========================================================================
 *		End of Standard Subrecord Names
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Magic Effect IDs
 *
 *=========================================================================*/
  const obrectype_t OB_MGEF_ABAT = "ABAT";
  const obrectype_t OB_MGEF_ABFA = "ABFA";
  const obrectype_t OB_MGEF_ABHE = "ABHE";
  const obrectype_t OB_MGEF_ABSK = "ABSK";
  const obrectype_t OB_MGEF_ABSP = "ABSP";
  const obrectype_t OB_MGEF_BABO = "BABO";
  const obrectype_t OB_MGEF_BACU = "BACU";
  const obrectype_t OB_MGEF_BAGA = "BAGA";
  const obrectype_t OB_MGEF_BAGR = "BAGR";
  const obrectype_t OB_MGEF_BAHE = "BAHE";
  const obrectype_t OB_MGEF_BASH = "BASH";
  const obrectype_t OB_MGEF_BRDN = "BRDN";
  const obrectype_t OB_MGEF_BWAX = "BWAX";
  const obrectype_t OB_MGEF_BWBO = "BWBO";
  const obrectype_t OB_MGEF_BWDA = "BWDA";
  const obrectype_t OB_MGEF_BWMA = "BWMA";
  const obrectype_t OB_MGEF_BWSW = "BWSW";
  const obrectype_t OB_MGEF_CALM = "CALM";
  const obrectype_t OB_MGEF_CHML = "CHML";
  const obrectype_t OB_MGEF_CHRM = "CHRM";
  const obrectype_t OB_MGEF_COCR = "COCR";
  const obrectype_t OB_MGEF_COHU = "COHU";
  const obrectype_t OB_MGEF_CUDI = "CUDI";
  const obrectype_t OB_MGEF_CUPA = "CUPA";
  const obrectype_t OB_MGEF_CUPO = "CUPO";
  const obrectype_t OB_MGEF_DARK = "DARK";
  const obrectype_t OB_MGEF_DEMO = "DEMO";
  const obrectype_t OB_MGEF_DGAT = "DGAT";
  const obrectype_t OB_MGEF_DGFA = "DGFA";
  const obrectype_t OB_MGEF_DGHE = "DGHE";
  const obrectype_t OB_MGEF_DGSP = "DGSP";
  const obrectype_t OB_MGEF_DIAR = "DIAR";
  const obrectype_t OB_MGEF_DIWE = "DIWE";
  const obrectype_t OB_MGEF_DRAT = "DRAT";
  const obrectype_t OB_MGEF_DRFA = "DRFA";
  const obrectype_t OB_MGEF_DRHE = "DRHE";
  const obrectype_t OB_MGEF_DRSK = "DRSK";
  const obrectype_t OB_MGEF_DRSP = "DRSP";
  const obrectype_t OB_MGEF_DSPL = "DSPL";
  const obrectype_t OB_MGEF_DTCT = "DTCT";
  const obrectype_t OB_MGEF_FIDG = "FIDG";
  const obrectype_t OB_MGEF_FISH = "FISH";
  const obrectype_t OB_MGEF_FOAT = "FOAT";
  const obrectype_t OB_MGEF_FOFA = "FOFA";
  const obrectype_t OB_MGEF_FOHE = "FOHE";
  const obrectype_t OB_MGEF_FOMM = "FOMM";
  const obrectype_t OB_MGEF_FOSK = "FOSK";
  const obrectype_t OB_MGEF_FOSP = "FOSP";
  const obrectype_t OB_MGEF_FRDG = "FRDG";
  const obrectype_t OB_MGEF_FRNZ = "FRNZ";
  const obrectype_t OB_MGEF_FRSH = "FRSH";
  const obrectype_t OB_MGEF_FTHR = "FTHR";
  const obrectype_t OB_MGEF_INVI = "INVI";
  const obrectype_t OB_MGEF_LGHT = "LGHT";
  const obrectype_t OB_MGEF_LISH = "LISH";
  const obrectype_t OB_MGEF_NEYE = "NEYE";
  const obrectype_t OB_MGEF_OPEN = "OPEN";
  const obrectype_t OB_MGEF_PARA = "PARA";
  const obrectype_t OB_MGEF_RALY = "RALY";
  const obrectype_t OB_MGEF_REAN = "REAN";
  const obrectype_t OB_MGEF_REAT = "REAT";
  const obrectype_t OB_MGEF_REDG = "REDG";
  const obrectype_t OB_MGEF_REFA = "REFA";
  const obrectype_t OB_MGEF_REHE = "REHE";
  const obrectype_t OB_MGEF_RESP = "RESP";
  const obrectype_t OB_MGEF_RFLC = "RFLC";
  const obrectype_t OB_MGEF_RSDI = "RSDI";
  const obrectype_t OB_MGEF_RSFI = "RSFI";
  const obrectype_t OB_MGEF_RSFR = "RSFR";
  const obrectype_t OB_MGEF_RSMA = "RSMA";
  const obrectype_t OB_MGEF_RSNW = "RSNW";
  const obrectype_t OB_MGEF_RSPA = "RSPA";
  const obrectype_t OB_MGEF_RSPO = "RSPO";
  const obrectype_t OB_MGEF_RSSH = "RSSH";
  const obrectype_t OB_MGEF_RSWD = "RSWD";
  const obrectype_t OB_MGEF_SABS = "SABS";
  const obrectype_t OB_MGEF_SEFF = "SEFF";
  const obrectype_t OB_MGEF_SHDG = "SHDG";
  const obrectype_t OB_MGEF_SHLD = "SHLD";
  const obrectype_t OB_MGEF_SLNC = "SLNC";
  const obrectype_t OB_MGEF_STMA = "STMA";
  const obrectype_t OB_MGEF_STRP = "STRP";
  const obrectype_t OB_MGEF_SUDG = "SUDG";
  const obrectype_t OB_MGEF_TELE = "TELE";
  const obrectype_t OB_MGEF_TURN = "TURN";
  const obrectype_t OB_MGEF_VAMP = "VAMP";
  const obrectype_t OB_MGEF_WABR = "WABR";
  const obrectype_t OB_MGEF_WAWA = "WAWA";
  const obrectype_t OB_MGEF_WKDI = "WKDI";
  const obrectype_t OB_MGEF_WKFI = "WKFI";
  const obrectype_t OB_MGEF_WKFR = "WKFR";
  const obrectype_t OB_MGEF_WKMA = "WKMA";
  const obrectype_t OB_MGEF_WKNW = "WKNW";
  const obrectype_t OB_MGEF_WKPO = "WKPO";
  const obrectype_t OB_MGEF_WKSH = "WKSH";
  const obrectype_t OB_MGEF_Z002 = "Z002";
  const obrectype_t OB_MGEF_Z003 = "Z003";
  const obrectype_t OB_MGEF_Z005 = "Z005";
  const obrectype_t OB_MGEF_ZCLA = "ZCLA";
  const obrectype_t OB_MGEF_ZDAE = "ZDAE";
  const obrectype_t OB_MGEF_ZDRE = "ZDRE";
  const obrectype_t OB_MGEF_ZDRL = "ZDRL";
  const obrectype_t OB_MGEF_ZFIA = "ZFIA";
  const obrectype_t OB_MGEF_ZFRA = "ZFRA";
  const obrectype_t OB_MGEF_ZGHO = "ZGHO";
  const obrectype_t OB_MGEF_ZHDZ = "ZHDZ";
  const obrectype_t OB_MGEF_ZLIC = "ZLIC";
  const obrectype_t OB_MGEF_ZSCA = "ZSCA";
  const obrectype_t OB_MGEF_ZSKA = "ZSKA";
  const obrectype_t OB_MGEF_ZSKC = "ZSKC";
  const obrectype_t OB_MGEF_ZSKE = "ZSKE";
  const obrectype_t OB_MGEF_ZSKH = "ZSKH";
  const obrectype_t OB_MGEF_ZSPD = "ZSPD";
  const obrectype_t OB_MGEF_ZSTA = "ZSTA";
  const obrectype_t OB_MGEF_ZWRA = "ZWRA";
  const obrectype_t OB_MGEF_ZWRL = "ZWRL";
  const obrectype_t OB_MGEF_ZXIV = "ZXIV";
  const obrectype_t OB_MGEF_ZZOM = "ZZOM";
  const obrectype_t OB_MGEF_LOCK = "LOCK";
  const obrectype_t OB_MGEF_MYHL = "MYHL";
  const obrectype_t OB_MGEF_MYTH = "MYTH";
  const obrectype_t OB_MGEF_POSN = "POSN";
  const obrectype_t OB_MGEF_Z001 = "Z001";
  const obrectype_t OB_MGEF_Z004 = "Z004";
/*===========================================================================
 *		End of Magic Effect IDs
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool ReadObRecType (CObFile& File, Name);
 *
 * Reads a 4-byte record type field returning false on any error.
 *
 *=========================================================================*/
bool ReadObRecType (CObFile& File, obrectype_t& Name) {
  return File.Read((void *)&Name, OB_RECTYPE_SIZE);
 }
/*===========================================================================
 *		End of Function ReadObRecType()
 *=========================================================================*/


/*===========================================================================
 *
 * Function - bool WriteObRecType (CObFile& File, Name);
 *
 * Writes a 4-byte record type field returning false on any error.
 *
 *=========================================================================*/
bool WriteObRecType (CObFile& File, const obrectype_t Name) {
  return File.Write((void *)&Name, OB_RECTYPE_SIZE);
 }
/*===========================================================================
 *		End of Function WriteObRecType()
 *=========================================================================*/


