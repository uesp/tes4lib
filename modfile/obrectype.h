/*===========================================================================
 *
 * File:	ObRecType.H
 * Author:	Dave Humphrey (uesp@sympatico.ca)
 * Created On:	April 9, 2006
 *
 * Contains definitions related to the record, group, and subrecord type
 * fields. The type field is a 4 byte value that uses 4 characters to
 * describe it: "TES4", "HEDR", "GRUP", etc... While it is convienient
 * to consider them as a string (not nul terminated) from the user's
 * perspective, it is better to treat them as a 32-bit dword from a 
 * programming perspective. 
 *
 *=========================================================================*/
#ifndef __OBRECTYPE_H
#define __OBRECTYPE_H


/*===========================================================================
 *
 * Begin Required Includes
 *
 *=========================================================================*/
  #include "../common/obfile.h"
/*===========================================================================
 *		End of Required Includes
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Definitions
 *
 *=========================================================================*/

	/* Name field size */
  #define OB_RECTYPE_SIZE (4)

/*===========================================================================
 *		End of Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin Type Definitions
 *
 *=========================================================================*/
#pragma pack(push, 1)

	/* Standard record/sub-record name field */
  union obrectype_t {
  //struct obrectype_t {

        //union {
		char  Name[OB_RECTYPE_SIZE];
		dword Value;
	//};

		/* Constructors */
	obrectype_t (const dword Val = 0) { Value = Val; }
	obrectype_t (const char* pString) { Value = *(dword *) pString; }

		/* Conversion Operators */
	operator const char* (void) const { return (Name); }
	operator const dword (void) const { return (Value); }

	const obrectype_t& operator= (const char* pString) { Value = *(const dword *) pString; return (*this); }
	const obrectype_t& operator= (const dword InValue) { Value = InValue; return (*this); }
   };

#pragma pack(pop)
/*===========================================================================
 *		End of Type Definitions
 *=========================================================================*/


/*===========================================================================
 *
 * Begin External Definitions
 *
 *=========================================================================*/

	/* Special names */
  extern const obrectype_t OB_NAME_NULL;

	/* Special group name */
  extern const obrectype_t OB_NAME_GRUP;
	
	/* Known record names */
  extern const obrectype_t OB_NAME_AMMO;
  extern const obrectype_t OB_NAME_ARMO;
  extern const obrectype_t OB_NAME_APPA;
  extern const obrectype_t OB_NAME_BOOK;
  extern const obrectype_t OB_NAME_CELL;
  extern const obrectype_t OB_NAME_CLOT;
  extern const obrectype_t OB_NAME_ENCH;
  extern const obrectype_t OB_NAME_FLOR;
  extern const obrectype_t OB_NAME_INGR;
  extern const obrectype_t OB_NAME_LAND;
  extern const obrectype_t OB_NAME_LIGH;
  extern const obrectype_t OB_NAME_LVLI;
  extern const obrectype_t OB_NAME_MISC;
  extern const obrectype_t OB_NAME_NPC_;
  extern const obrectype_t OB_NAME_PGRD;
  extern const obrectype_t OB_NAME_REFR;
  extern const obrectype_t OB_NAME_SCPT;
  extern const obrectype_t OB_NAME_SGST;
  extern const obrectype_t OB_NAME_SPEL;
  extern const obrectype_t OB_NAME_SOUN;
  extern const obrectype_t OB_NAME_TES4;
  extern const obrectype_t OB_NAME_WEAP;
  extern const obrectype_t OB_NAME_WRLD;
  
  extern const obrectype_t OB_NAME_ACHR;
  extern const obrectype_t OB_NAME_ACRE;
  extern const obrectype_t OB_NAME_ACTI;
  extern const obrectype_t OB_NAME_ALCH;
  extern const obrectype_t OB_NAME_ANIO;
  extern const obrectype_t OB_NAME_BSGN;
  extern const obrectype_t OB_NAME_CLAS;
  extern const obrectype_t OB_NAME_CLMT;
  extern const obrectype_t OB_NAME_CONT;
  extern const obrectype_t OB_NAME_CSTY;
  extern const obrectype_t OB_NAME_CREA;
  extern const obrectype_t OB_NAME_DIAL;
  extern const obrectype_t OB_NAME_DOOR;
  extern const obrectype_t OB_NAME_EFSH;
  extern const obrectype_t OB_NAME_EYES;
  extern const obrectype_t OB_NAME_FURN;
  extern const obrectype_t OB_NAME_GLOB;
  extern const obrectype_t OB_NAME_GMST;
  extern const obrectype_t OB_NAME_GRAS;
  extern const obrectype_t OB_NAME_FACT;
  extern const obrectype_t OB_NAME_HAIR;
  extern const obrectype_t OB_NAME_IDLE;
  extern const obrectype_t OB_NAME_INFO;
  extern const obrectype_t OB_NAME_KEYM;
  extern const obrectype_t OB_NAME_LSCR;
  extern const obrectype_t OB_NAME_LTEX;
  extern const obrectype_t OB_NAME_LVLC;
  extern const obrectype_t OB_NAME_LVSP;
  extern const obrectype_t OB_NAME_MGEF;
  extern const obrectype_t OB_NAME_PACK;
  extern const obrectype_t OB_NAME_QUST;
  extern const obrectype_t OB_NAME_RACE;
  extern const obrectype_t OB_NAME_REGN;
  extern const obrectype_t OB_NAME_ROAD;
  extern const obrectype_t OB_NAME_SBSP;
  extern const obrectype_t OB_NAME_SKIL;
  extern const obrectype_t OB_NAME_SLGM;
  extern const obrectype_t OB_NAME_STAT;
  extern const obrectype_t OB_NAME_TREE;
  extern const obrectype_t OB_NAME_WATR;
  extern const obrectype_t OB_NAME_WTHR;

	/* Known sub-records */
  extern const obrectype_t OB_NAME_ANAM;
  extern const obrectype_t OB_NAME_BMDT;
  extern const obrectype_t OB_NAME_DESC;
  extern const obrectype_t OB_NAME_ENAM;
  extern const obrectype_t OB_NAME_FNAM;
  extern const obrectype_t OB_NAME_HEDR;
  extern const obrectype_t OB_NAME_ICON;
  extern const obrectype_t OB_NAME_ICO2;
  extern const obrectype_t OB_NAME_LVLD;
  extern const obrectype_t OB_NAME_LVLF;
  extern const obrectype_t OB_NAME_LVLO;
  extern const obrectype_t OB_NAME_MODB;
  extern const obrectype_t OB_NAME_MO2B;
  extern const obrectype_t OB_NAME_MO3B;
  extern const obrectype_t OB_NAME_MO4B;
  extern const obrectype_t OB_NAME_MODL;
  extern const obrectype_t OB_NAME_MOD2;
  extern const obrectype_t OB_NAME_MOD3;
  extern const obrectype_t OB_NAME_MOD4;
  extern const obrectype_t OB_NAME_MODT;
  extern const obrectype_t OB_NAME_MO2T;
  extern const obrectype_t OB_NAME_MO3T;
  extern const obrectype_t OB_NAME_MO4T;
  extern const obrectype_t OB_NAME_NAME;
  extern const obrectype_t OB_NAME_XXXX;
  extern const obrectype_t OB_NAME_OFST;
  extern const obrectype_t OB_NAME_CNAM;
  extern const obrectype_t OB_NAME_SNAM;
  extern const obrectype_t OB_NAME_SCHR;
  extern const obrectype_t OB_NAME_SCDA;
  extern const obrectype_t OB_NAME_SCTX;
  extern const obrectype_t OB_NAME_SLSD;
  extern const obrectype_t OB_NAME_SCVR;
  extern const obrectype_t OB_NAME_SCRV;
  extern const obrectype_t OB_NAME_SCIT;
  extern const obrectype_t OB_NAME_SCRI;
  extern const obrectype_t OB_NAME_SPIT;  
  extern const obrectype_t OB_NAME_EDID;
  extern const obrectype_t OB_NAME_ENIT;
  extern const obrectype_t OB_NAME_EFIT;
  extern const obrectype_t OB_NAME_EFID;
  extern const obrectype_t OB_NAME_FULL;
  extern const obrectype_t OB_NAME_DATA;
  extern const obrectype_t OB_NAME_MAST;
  extern const obrectype_t OB_NAME_XTEL;
  extern const obrectype_t OB_NAME_TNAM;
  extern const obrectype_t OB_NAME_SPLO;
  extern const obrectype_t OB_NAME_QNAM;
  extern const obrectype_t OB_NAME_CNTO;
  extern const obrectype_t OB_NAME_XTRG;
  extern const obrectype_t OB_NAME_XRTM;
  extern const obrectype_t OB_NAME_XESP;
  extern const obrectype_t OB_NAME_XHRS;
  extern const obrectype_t OB_NAME_XMRC;
  extern const obrectype_t OB_NAME_XSCL;
  extern const obrectype_t OB_NAME_XOWN;
  extern const obrectype_t OB_NAME_XGLB;
  extern const obrectype_t OB_NAME_XRNK;
  extern const obrectype_t OB_NAME_XCCM;
  extern const obrectype_t OB_NAME_XCWT;
  extern const obrectype_t OB_NAME_XCLW;
  extern const obrectype_t OB_NAME_XCLR;
  extern const obrectype_t OB_NAME_NAM2;
  extern const obrectype_t OB_NAME_SCRO;
  extern const obrectype_t OB_NAME_XPCI;
  extern const obrectype_t OB_NAME_WLST;
  extern const obrectype_t OB_NAME_CSCR;
  extern const obrectype_t OB_NAME_CSDI;
  extern const obrectype_t OB_NAME_INAM;
  extern const obrectype_t OB_NAME_ZNAM;
  extern const obrectype_t OB_NAME_PKID;
  extern const obrectype_t OB_NAME_QSTI;
  extern const obrectype_t OB_NAME_BNAM;
  extern const obrectype_t OB_NAME_XNAM;
  extern const obrectype_t OB_NAME_PFIG;
  extern const obrectype_t OB_NAME_CTDA;
  extern const obrectype_t OB_NAME_CTDT;
  extern const obrectype_t OB_NAME_TCLF;
  extern const obrectype_t OB_NAME_TCLT;
  extern const obrectype_t OB_NAME_ATXT;
  extern const obrectype_t OB_NAME_BTXT;
  extern const obrectype_t OB_NAME_VTEX;
  extern const obrectype_t OB_NAME_LNAM;
  extern const obrectype_t OB_NAME_GNAM;
  extern const obrectype_t OB_NAME_HNAM;
  extern const obrectype_t OB_NAME_RNAM;
  extern const obrectype_t OB_NAME_PLDT;
  extern const obrectype_t OB_NAME_PTDT;
  extern const obrectype_t OB_NAME_PGRL;
  extern const obrectype_t OB_NAME_QSTA;
  extern const obrectype_t OB_NAME_DNAM;
  extern const obrectype_t OB_NAME_VNAM;
  extern const obrectype_t OB_NAME_XLOC;
  extern const obrectype_t OB_NAME_WNAM;
  extern const obrectype_t OB_NAME_RDWT;
  extern const obrectype_t OB_NAME_RDGS;
  extern const obrectype_t OB_NAME_RDOT;
  extern const obrectype_t OB_NAME_RDSD;
  extern const obrectype_t OB_NAME_SOUL;
  extern const obrectype_t OB_NAME_SLCP;
  extern const obrectype_t OB_NAME_SNDX;
  extern const obrectype_t OB_NAME_SNDD;
  extern const obrectype_t OB_NAME_PFPC;
  extern const obrectype_t OB_NAME_MNAM;
  extern const obrectype_t OB_NAME_INDX;
  
	/* Magic effect IDs */
  extern const obrectype_t OB_MGEF_ABAT; 
  extern const obrectype_t OB_MGEF_ABFA;
  extern const obrectype_t OB_MGEF_ABHE;
  extern const obrectype_t OB_MGEF_ABSK;
  extern const obrectype_t OB_MGEF_ABSP;
  extern const obrectype_t OB_MGEF_BABO;
  extern const obrectype_t OB_MGEF_BACU;
  extern const obrectype_t OB_MGEF_BAGA;
  extern const obrectype_t OB_MGEF_BAGR;
  extern const obrectype_t OB_MGEF_BAHE;
  extern const obrectype_t OB_MGEF_BASH;
  extern const obrectype_t OB_MGEF_BRDN;
  extern const obrectype_t OB_MGEF_BWAX;
  extern const obrectype_t OB_MGEF_BWBO;
  extern const obrectype_t OB_MGEF_BWDA;
  extern const obrectype_t OB_MGEF_BWMA;
  extern const obrectype_t OB_MGEF_BWSW;
  extern const obrectype_t OB_MGEF_CALM;
  extern const obrectype_t OB_MGEF_CHML;
  extern const obrectype_t OB_MGEF_CHRM;
  extern const obrectype_t OB_MGEF_COCR;
  extern const obrectype_t OB_MGEF_COHU;
  extern const obrectype_t OB_MGEF_CUDI;
  extern const obrectype_t OB_MGEF_CUPA;
  extern const obrectype_t OB_MGEF_CUPO;
  extern const obrectype_t OB_MGEF_DARK;
  extern const obrectype_t OB_MGEF_DEMO;
  extern const obrectype_t OB_MGEF_DGAT;
  extern const obrectype_t OB_MGEF_DGFA;
  extern const obrectype_t OB_MGEF_DGHE;
  extern const obrectype_t OB_MGEF_DGSP;
  extern const obrectype_t OB_MGEF_DIAR;
  extern const obrectype_t OB_MGEF_DIWE;
  extern const obrectype_t OB_MGEF_DRAT;
  extern const obrectype_t OB_MGEF_DRFA;
  extern const obrectype_t OB_MGEF_DRHE;
  extern const obrectype_t OB_MGEF_DRSK;
  extern const obrectype_t OB_MGEF_DRSP;
  extern const obrectype_t OB_MGEF_DSPL;
  extern const obrectype_t OB_MGEF_DTCT;
  extern const obrectype_t OB_MGEF_FIDG;
  extern const obrectype_t OB_MGEF_FISH;
  extern const obrectype_t OB_MGEF_FOAT;
  extern const obrectype_t OB_MGEF_FOFA;
  extern const obrectype_t OB_MGEF_FOHE;
  extern const obrectype_t OB_MGEF_FOMM;
  extern const obrectype_t OB_MGEF_FOSK;
  extern const obrectype_t OB_MGEF_FOSP;
  extern const obrectype_t OB_MGEF_FRDG;
  extern const obrectype_t OB_MGEF_FRNZ;
  extern const obrectype_t OB_MGEF_FRSH;
  extern const obrectype_t OB_MGEF_FTHR;
  extern const obrectype_t OB_MGEF_INVI;
  extern const obrectype_t OB_MGEF_LGHT;
  extern const obrectype_t OB_MGEF_LISH;
  extern const obrectype_t OB_MGEF_NEYE;
  extern const obrectype_t OB_MGEF_OPEN;
  extern const obrectype_t OB_MGEF_PARA;
  extern const obrectype_t OB_MGEF_RALY;
  extern const obrectype_t OB_MGEF_REAN;
  extern const obrectype_t OB_MGEF_REAT;
  extern const obrectype_t OB_MGEF_REDG;
  extern const obrectype_t OB_MGEF_REFA;
  extern const obrectype_t OB_MGEF_REHE;
  extern const obrectype_t OB_MGEF_RESP;
  extern const obrectype_t OB_MGEF_RFLC;
  extern const obrectype_t OB_MGEF_RSDI;
  extern const obrectype_t OB_MGEF_RSFI;
  extern const obrectype_t OB_MGEF_RSFR;
  extern const obrectype_t OB_MGEF_RSMA;
  extern const obrectype_t OB_MGEF_RSNW;
  extern const obrectype_t OB_MGEF_RSPA;
  extern const obrectype_t OB_MGEF_RSPO;
  extern const obrectype_t OB_MGEF_RSSH;
  extern const obrectype_t OB_MGEF_RSWD;
  extern const obrectype_t OB_MGEF_SABS;
  extern const obrectype_t OB_MGEF_SEFF;
  extern const obrectype_t OB_MGEF_SHDG;
  extern const obrectype_t OB_MGEF_SHLD;
  extern const obrectype_t OB_MGEF_SLNC;
  extern const obrectype_t OB_MGEF_STMA;
  extern const obrectype_t OB_MGEF_STRP;
  extern const obrectype_t OB_MGEF_SUDG;
  extern const obrectype_t OB_MGEF_TELE;
  extern const obrectype_t OB_MGEF_TURN;
  extern const obrectype_t OB_MGEF_VAMP;
  extern const obrectype_t OB_MGEF_WABR;
  extern const obrectype_t OB_MGEF_WAWA;
  extern const obrectype_t OB_MGEF_WKDI;
  extern const obrectype_t OB_MGEF_WKFI;
  extern const obrectype_t OB_MGEF_WKFR;
  extern const obrectype_t OB_MGEF_WKMA;
  extern const obrectype_t OB_MGEF_WKNW;
  extern const obrectype_t OB_MGEF_WKPO;
  extern const obrectype_t OB_MGEF_WKSH;
  extern const obrectype_t OB_MGEF_Z002;
  extern const obrectype_t OB_MGEF_Z003;
  extern const obrectype_t OB_MGEF_Z005;
  extern const obrectype_t OB_MGEF_ZCLA;
  extern const obrectype_t OB_MGEF_ZDAE;
  extern const obrectype_t OB_MGEF_ZDRE;
  extern const obrectype_t OB_MGEF_ZDRL;
  extern const obrectype_t OB_MGEF_ZFIA;
  extern const obrectype_t OB_MGEF_ZFRA;
  extern const obrectype_t OB_MGEF_ZGHO;
  extern const obrectype_t OB_MGEF_ZHDZ;
  extern const obrectype_t OB_MGEF_ZLIC;
  extern const obrectype_t OB_MGEF_ZSCA;
  extern const obrectype_t OB_MGEF_ZSKA;
  extern const obrectype_t OB_MGEF_ZSKC;
  extern const obrectype_t OB_MGEF_ZSKE;
  extern const obrectype_t OB_MGEF_ZSKH;
  extern const obrectype_t OB_MGEF_ZSPD;
  extern const obrectype_t OB_MGEF_ZSTA;
  extern const obrectype_t OB_MGEF_ZWRA;
  extern const obrectype_t OB_MGEF_ZWRL;
  extern const obrectype_t OB_MGEF_ZXIV;
  extern const obrectype_t OB_MGEF_ZZOM;
  extern const obrectype_t OB_MGEF_LOCK;
  extern const obrectype_t OB_MGEF_MYHL;
  extern const obrectype_t OB_MGEF_MYTH;
  extern const obrectype_t OB_MGEF_POSN;
  extern const obrectype_t OB_MGEF_Z001;
  extern const obrectype_t OB_MGEF_Z004;

/*===========================================================================
 *		End of External Definitions
 *=========================================================================*/



/*===========================================================================
 *
 * Begin Function Definitions
 *
 *=========================================================================*/
	
	/* Comparison operators */
  inline bool operator== (const obrectype_t Name, const char* pString)      { return (Name.Value == * (dword *) pString); }
  inline bool operator== (const obrectype_t Name, const dword Value)        { return (Name.Value == Value); }
  inline bool operator== (const obrectype_t Name1, const obrectype_t Name2) { return (Name1.Value == Name2.Value);  }
  inline bool operator!= (const obrectype_t Name, const char* pString)      { return (Name.Value != * (dword *) pString); }
  inline bool operator!= (const obrectype_t Name, const dword Value)        { return (Name.Value != Value); }
  inline bool operator!= (const obrectype_t Name1, const obrectype_t Name2) { return (Name1.Value != Name2.Value); }

	/* Read/write functions */
  bool ReadObRecType  (CObFile& File, obrectype_t& Name);
  bool WriteObRecType (CObFile& File, const obrectype_t Name);

/*===========================================================================
 *		End of Function Definitions
 *=========================================================================*/



#endif
/*===========================================================================
 *		End of File ObRecType.H
 *=========================================================================*/

