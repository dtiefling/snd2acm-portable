// chitem.h : main header file for the CHITEM application
//

#if !defined(AFX_CHITEM_H__82C8D991_857B_4DDB_9704_0525A2869DD5__INCLUDED_)
#define AFX_CHITEM_H__82C8D991_857B_4DDB_9704_0525A2869DD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <afxadv.h>
#include <io.h>
#include "resource.h"		// main symbols
#include "structs.h"
#include "item.h"
#include "store.h"
#include "proj.h"
#include "spell.h"
#include "effect.h"
#include "creature.h"
#include "script.h"
#include "VVC.h"
#include "dialog.h"
#include "area.h"
#include "bam.h"
#include "game.h"
#include "map.h"
#include "mos.h"
#include "chui.h"
#include "src.h"
#include "ItemPicker.h"
#include "ColorPicker.h"

//
#define MAXBUFFSIZE 4096
#define MAXIDSIZE   512

extern char external[MAXBUFFSIZE]; //we need some hacks sometimes

//updatedata flags
#define UD_RETRIEVE  TRUE
#define UD_DISPLAY   FALSE

//macro for checking a menuitem
#define MF_SET(flg) ((flg)?(MF_BYCOMMAND|MF_CHECKED):(MF_BYCOMMAND|MF_UNCHECKED))
#define MFP_SET(flg) ((flg)?(MF_BYPOSITION|MF_ENABLED):(MF_BYPOSITION|MF_GRAYED))

extern UINT WM_FINDREPLACE;
#define SR_SEARCH 0
#define SR_REPLACE 1
#define SR_ALL 2

#define MAX_LINE  1000
//#define VIEW_MAXEXTENT 8   

//bif res_loc definitions
#define FILE_IDX_MASK  0x03fff
#define TIS_IDX_MASK   0xfc000

//class definitions
#define CLASS_MAGE          1
#define CLASS_CLERIC        3
#define CLASS_BARD          5
#define CLASS_PALADIN       6
#define FIGHTER_MAGE        7
#define FIGHTER_CLERIC      8
#define CLASS_DRUID         11
#define CLASS_RANGER        12
#define MAGE_THIEF          13
#define CLERIC_MAGE         14
#define CLERIC_THIEF        15
#define FIGHTER_DRUID       16
#define FIGHTER_MAGE_CLERIC 17
#define CLERIC_RANGER       18
#define CLASS_SORCEROR      19

#define EXTENDED_NIGHT      64
//constants
#define NUM_CD 5

//script parameter datatypes
#define SPT_OBJECT   'O'
#define SPT_OVERRIDE 'O1'
#define SPT_SECONDOB 'O2'
#define SPT_ACTION   'A'
#define SPT_POINT    'P'
#define SPT_INTEGER  'I'  //1. position
#define SPT_INTEGER2 'I2' //3. (trigger) or 4. (action) position
#define SPT_INTEGER3 'I3' //4. position (trigger) or 5. position for action
#define SPT_STRREF   'IS' //1. position (strref)
#define SPT_STRREF2  '2I'
#define SPT_STRREF3  '3I'
#define SPT_ZERO     '0'  //argument that isn't required (own feature)
#define SPT_STRING1  'S1'
#define SPT_STRING2  'S2'
#define SPT_AREA1    'SA'   //area (inserted)
#define SPT_VAR1     'SV'   //simple variable
#define SPT_TOKEN1   'ST'   //token
#define SPT_COLUMN1  'SX'   //xplist column
#define SPT_RESREF1  'SR'   //resource (8 chars long)
#define SPT_NUMLIST1 'SN'   //number list (3 digits numbers)
#define SPT_DEAD1    'DE'   //death variable
#define SPT_AREA2    '2A'   //area variable inserted into 2. place
#define SPT_VAR2     '2V'   //simple variable goes to 2. place
#define SPT_TOKEN2   '2T'   //token
#define SPT_COLUMN2  '2X'   //xplist column
#define SPT_RESREF2  '2R'   //resource (8 chars long)
#define SPT_NUMLIST2 '2N'   //number list (3 digits numbers)
#define SPT_DEAD2    '2D'   //death variable

#define NUM_WEAPROF    54
extern int act_num_weaprof;

#define SLOT_WEAPON 9

#define NUM_ITEMTYPE   0x4a
//itemtype vs. two handed
//bit 1 - 1 handed
//bit 2 - 2 handed
//bit 4 - invalid item in bg2

extern int itvs2h[NUM_ITEMTYPE];

#define NUM_ANIMTYPES 10

#define NUM_ANIMIDX  37
#define NUM_STYPE  6
#define NUM_STYPE2  4

#define NUM_STORETYPE  6
//store types
#define STT_STORE     0
#define STT_TAVERN    1
#define STT_INN       2
#define STT_TEMPLE    3
#define STT_IWDCONT   4
#define STT_CONT      5

//stored itemflags
#define STI_IDENTIFIED  1
#define STI_NOSTEAL     2
#define STI_STOLEN      4

#define NUM_SPELLTYPE  4
//spell types
#define SP_SPECIAL 0
#define SP_WIZARD 1
#define SP_CLERIC 2
#define SP_INNATE 3

#define IT_BOOK    0
#define IT_ARROW   5
#define IT_BULLET  0xe
#define IT_BOW     0xf
#define IT_DAGGER  0x10
#define IT_MACE    0x11
#define IT_SLING   0x12
#define IT_SHORT   0x13
#define IT_BASTARD 0x14
#define IT_HAMMER  0x15
#define IT_MORNING 0x16
#define IT_FLAIL   0x17
#define IT_DART    0x18
#define IT_AXE     0x19
#define IT_XBOW    0x1b
#define IT_SPEAR   0x1d
#define IT_HALBERD 0x1e
#define IT_BOLT    0x1f
#define IT_GOLD    0x21
#define IT_GEM     0x22
#define IT_BAG     0x24
#define IT_CLUB    0x2c   //club in iwd
#define IT_SWORD   0x39   //special sword in iwd
#define IT_CONTAINER 0x3a //container in iwd

#define TBG_ALT 0x8000  //special handling of tbg
//alternate cre - soundset
//alternate gam - tbgn

#define REF_BMP   0x0001  //1
#define REF_MVE   0x0002  //2
#define REF_WAV   0x0004  //3
#define REF_WFX   0x0005  //4
#define REF_PLT   0x0006  //5
#define REF_MUS   0x0ffe  //6not in bif?
#define REF_ACM   0x0fff  //7not in bif?
#define REF_BAM   0x03e8  //8
#define REF_WED   0x03e9  //9
#define REF_CHU   0x03ea  //10
#define REF_TIS   0x03eb  //11
#define REF_MOS   0x03ec  //12
#define REF_ITM   0x03ed  //13
#define REF_SPL   0x03ee  //14
#define REF_BCS   0x03ef  //15
#define REF_IDS   0x03f0  //16
#define REF_CRE   0x03f1  //17
#define REF_ARE   0x03f2  //18
#define REF_DLG   0x03f3  //19
#define REF_2DA   0x03f4  //20
#define REF_GAM   0x03f5  //21
#define REF_STO   0x03f6  //22
#define REF_WMP   0x03f7  //23 
#define REF_EFF   0x03f8  //24
#define REF_VVC   0x03fb  //25
#define REF_VEF   0x03fc  //26
#define REF_PRO   0x03fd  //27
#define REF_INI   0x0802  //28
#define REF_SRC   0x0803  //29
#define NUM_OBJTYPE 29

#define NUM_FVALUE 3
extern CString proj_facing_desc[NUM_FVALUE];

#define NUM_SPKCOL 13

#define NUM_ARTYPE 4
//area types
#define AR_NORMAL
#define AR_NOSAVE
#define AR_TUTORIAL

#define NUM_ATYPE 5
//attack types
#define A_NONE   0
#define A_MELEE  1
#define A_PROJ   2
#define A_MAGIC  3
#define A_BOW    4

#define NUM_SFTYPE 3
//spell forms
#define SF_NONE     0
#define SF_NORMAL   1
#define SF_PROJECT  2

#define NUM_LFTYPE  5
//location types
#define LF_NONE     0
#define LF_WEAPON   1  //weapon
#define LF_SPELL    2  //cast spell
#define LF_MAGIC    3  //magic equipment
#define LF_INNATE   4  //innate spell

#define NUM_TTYPE 8
//target types
#define T_INVALID  0
#define T_CREA  1
#define T_INV   2
#define T_DEAD  3
#define T_AREA  4
#define T_SELF  5
#define T_UNKNOWN 6
#define T_NONE  7

#define NUM_AMTYPE 6
extern CString ammo_types[NUM_AMTYPE];

#define NUM_DTYPE 6
//damage types
#define DT_NONE      0
#define DT_PIERCING  1  //magic too
#define DT_BLUNT     2
#define DT_SLASH     3
#define DT_RANGED    4
#define DT_FIST      5

#define NUM_CHTYPE 4
//charge types
#define CH_NONE      0
#define CH_DRAINED   1
#define CH_STABLE    2
#define CH_PERDAY    3

#define NUM_MTYPE  3
//missile types
#define M_ARROW    0
#define M_BOLT     1
#define M_BULLET   2

#define NUM_SLOTTYPE 8

#define NUM_FEATS 458 //hardcoded feature number (iwd2)

#define NUM_TMTYPE  11
//effect duration types
#define TIMING_DURATION 0
#define TIMING_PERMANENT 1
#define TIMING_EQUIPED  2
#define TIMING_DELDDUR  3
#define TIMING_DELAYED  4
#define TIMING_DEL2     5
#define TIMING_DUR2     6

#define NUM_ETTYPE  14
//effect target types
#define EFF_TARGET_SELF 1
#define EFF_TARGET_PRE  2

#define NUM_RTYPE 4

#define NUM_RTTYPE 3
//active region types
#define RT_TRAP 0
#define RT_INFO 1
#define RT_TRAVEL 2

#define NUM_FVALUES 16

#define NUM_SPTYPE 3

#define NUM_CITYPE 13

#define OBJECT  0x200
#define TRIGGER 0x100
#define ACTION  0x000

#define LINKTO      0x40000000
#define EXTERNAL    0xc0000000
#define TREESTATE   0x80000000
#define TRANSSTATE  0x00000000

#define TRANSTR     0x20000000
#define STATETR     0x40000000
#define ACTIONBL    0x60000000

#define FLAGMASK    0xe0000000
#define NODEMASK    0x1fffffff

// the special triggers/actions
#define TR_TRUE      0x23
#define TR_FALSE     0x30
#define TR_OR        0x89

#define AC_CONTINUE  0x36
#define AC_STARTCUT  120
#define AC_STCUTMD   121
#define AC_ENDCUTMD  122
#define AC_CLRALLACT 123
#define AC_CLRACT    133

#define AC_ADD_JOURNAL 173

//bg2
#define AC_QUESTDONE_BG 235
#define AC_REMOVE_JOURNAL_BG 263
//iwd2
#define AC_REMOVE_JOURNAL_IWD 244
#define AC_QUESTDONE_IWD 245

#define JT_QUEST  1
#define JT_DONE   2

#define CHECKING  0
#define MATCHING  1
#define SCANNING  2
#define JOURNAL   3

extern CString DECOMPILED;
extern CString WEIDU_LOG;
extern CString SELF_REFERENCE;
extern CString DELETED_REFERENCE;
// dialog transition trigger flags
#define HAS_TEXT    1
#define HAS_TRIGGER 2
#define HAS_ACTION  4
#define LEAF_NODE   8
#define HAS_JOURNAL 16  //journal entry
//#define ????? 32
#define HAS_QUEST   64  //missing quest
//#define ????? 128
#define HAS_SOLVED  0x100 //solved quest

/////// script/dialog variable checking /////////
#define NO_CHECK     0
#define IS_VAR       1
#define ADD_LOCAL    2
#define ADD_GLOBAL   3
#define ADD_VAR      4
#define ADD_VAR2     5
#define VALID_TAG    6
#define ENTRY_POINT  7
#define ADD_DEAD     8
#define ADD_DEAD2    9

#define CHECK_SOUND  10 
#define CHECK_ITEM   11
#define CHECK_SPL    12
#define CHECK_CRE    13
#define CHECK_BCS    14
#define CHECK_DLG    15
#define CHECK_DEAD   16
#define CHECK_AREA   17
#define CHECK_STORE  18
#define CHECK_VVC    19
#define CHECK_2DA    20
#define CHECK_MOS    21
#define CHECK_DSOUND 22 //double sound resource
#define CHECK_MOVIE  23 //mve
#define CHECK_PAL    24 //palette (bmp)
#define CHECK_SRC    25 //pst src file
#define CHECK_GAME   26 //iwd2 party file

#define CHECK_SOUND2 30
#define CHECK_ITEM2  31
#define CHECK_SPL2   32
#define CHECK_BCS2   34
#define CHECK_DLG2   35
#define CHECK_DEAD2  36
#define CHECK_AREA2  37
#define CHECK_VVC2   39
#define CHECK_2DA2   40
#define CHECK_MOS2   41

#define CHECK_XPLIST 50  //a row in xplist 2da
#define CHECK_NUM    51  //a spell number list (4 digits/number)

#define CHECK_STRREF  0x10000
#define CHECK_ALIGN   0x20000
#define CHECK_POINT   0x40000
#define CHECK_BYTE    0x80000  //only one byte
#define CHECK_ONLYJ   0x100000
#define CHECK_JOURNAL 0x110000 //also set strref

#define MERGE_VARS 0xff

//store type flags
#define ST_BUY   1
#define ST_SELL  2
#define ST_ID    4
#define ST_STEAL 8
#define ST_CURE  16
#define ST_DONAT 32
#define ST_DRINK 64
#define ST_UNKN1  128
#define ST_UNKN2  256
#define ST_FENCE  512
#define ST_UNKN3  1024
#define ST_UNKN4  2048
#define ST_UNKN5  4096
#define ST_UNKN6  8192
#define ST_UNKN7  0x4000
#define ST_UNKN8  0x8000

#define ST_RENT   0x10000 //not in the original flags

#define PROJ_VISIBLE    1
#define PROJ_INANIMATE  2
#define PROJ_TRIGGER    4
#define PROJ_CONTROLLED 8
#define PROJ_NO_PARTY   16
#define PROJ_FRAGMENT   32
#define PROJ_NO_SELF    64
#define PROJ_NO_ENEMY   128

#define PROJ_HAS_VVC    1024
#define PROJ_CONE       2048

#define TRANSPARENT_GREEN  0x00ff00

#define COLORNUM 120

class colortype
{
public:
  COLORREF rgb[12];
  CString colorname;

  colortype(const int a, const char *b)
  {
    for(int i=0;i<12;i++) rgb[i]=a;
    colorname=b;
  }
  colortype(const COLORREF a, CString b)
  {
    for(int i=0;i<12;i++) rgb[i]=a;
    colorname=b;
  }
};

typedef struct
{
  CString title;
  CString initial;
} folderbrowse_t;

extern colortype colors[COLORNUM];

extern void init_colors();
extern CString colortitle(unsigned int value);
extern int feature_resource(int feature);
extern int *get_strref_opcodes();
CString convert_musiclist(CString tmpstr, bool onlyinternal);
int ModifyCFB(int mode, int featnum, feat_block *cfb);
void ConvertToV10Eff(const creature_effect *v20effect, feat_block *v10effect);
void ConvertToV20Eff(creature_effect *v20effect, const feat_block *v10effect);
int CheckDestination(CString area, CString entrance);
int BrowseForFolder(folderbrowse_t *pfb, HWND hwnd);
void HackForLargeList(CFileDialog &m_getfiledlg);
int WriteTempCreature(char *creature, long esize);

extern char BASED_CODE cfbFilter[];

typedef char * charpoi;

class CStringMapCStringMapInt: public CStringMapToCStringMapInt
{
public:
  ~CStringMapCStringMapInt();
};

class CStringMapArray : public CStringMapTooltip
{
public:
 int query_count(CString key);
};
class CStringListLocEntry: public CList<stringloc_entry, stringloc_entry&>
{
public:
  void Fixup(int index, int value);
  bool RemoveKey(CString ref);
  bool Lookup(CString ref, loc_entry &fileloc);
  bool SetAt(CString ref, loc_entry &fileloc);
  void RemoveAll();
  POSITION AddList(CString ref, loc_entry entry);
};

class CStringMapLocEntry: public CMap<CString, LPCSTR, loc_entry, loc_entry&>
{
public:
  void Fixup(int index, int value);
  int Lookup(CString key, loc_entry &loc);
};

//global variable definitions

extern CStringMapLocEntry items;
extern CStringMapLocEntry icons;
extern CStringMapLocEntry bitmaps;
extern CStringMapLocEntry creatures;
extern CStringMapLocEntry spells;
extern CStringMapLocEntry stores;
extern CStringMapLocEntry darefs;
extern CStringMapLocEntry idrefs;
extern CStringMapLocEntry dialogs;
extern CStringMapLocEntry scripts;
extern CStringMapLocEntry projects;
extern CStringMapLocEntry effects;
extern CStringMapLocEntry vvcs;
extern CStringMapLocEntry areas;
extern CStringMapLocEntry chuis;
extern CStringMapLocEntry mos;
extern CStringMapLocEntry weds;
extern CStringMapLocEntry tis;
extern CStringMapLocEntry sounds;
extern CStringMapLocEntry games;
extern CStringMapLocEntry wmaps;
extern CStringMapLocEntry musics;
extern CStringMapLocEntry musiclists;
extern CStringMapLocEntry movies;
extern CStringMapLocEntry wfxs;
extern CStringMapLocEntry strings;
extern CStringMapLocEntry paperdolls;
extern CStringMapLocEntry vefs;
extern CStringMapLocEntry inis;

extern CStringMapLocEntry *resources[NUM_OBJTYPE+1];
extern CStringListLocEntry *duplicates[NUM_OBJTYPE+1];
//extern CMap<CString, LPCSTR, int, int&> variables;
extern CStringMapInt variables;
extern CIntMapString journals;

extern unsigned char xorblock[64];
extern CString setupname;
extern CString bgfolder;
extern CString tlkfilename;
extern CString descpath;
extern CString weidupath;
extern CString weiduextra;
extern CString weidudecompiled;
extern int logtype;
extern int tooltips;
extern int do_progress;
extern int readonly;
extern unsigned long chkflg;
extern unsigned long editflg;
extern unsigned long optflg;
extern unsigned long weiduflg;

extern CStringMapArray tooltipnumbers;
extern CStringMapArray store_spell_desc;
extern CStringMapInt dial_references;
extern CStringList exclude_item;
extern CStringList xplist;
extern CStringList pro_references;
extern CStringList pro_titles;
extern CStringList race_names;
extern CStringList spawngroup;
extern CStringMapInt rnditems;
extern CStringList sectype_names;
extern CStringList school_names;
extern CString2List songlist;
extern CString bg2_slot_names[SLOT_COUNT];
extern CString pst_slot_names[PST_SLOT_COUNT];
extern CString iwd2_slot_names[IWD2_SLOT_COUNT];
extern CString slot_names[IWD2_SLOT_COUNT];
extern CString snd_slots[SND_SLOT_COUNT];

#define MAX_ACTION 360
extern CString action_defs[MAX_ACTION];
#define MAX_TRIGGER 256
extern CString trigger_defs[MAX_TRIGGER];

extern CString itemname;
extern CString lasterrormsg;
extern Citem the_item;
extern Cstore the_store;
extern Cproj the_projectile;
extern Cspell the_spell;
extern Ceffect the_effect;
extern Ccreature the_creature;
extern CVVC the_videocell;
extern Cscript the_script;
extern Cdialog the_dialog;
extern Carea the_area;
extern Cbam the_bam;
extern Cgame the_game;
extern Cmap the_map;
extern Cmos the_mos;
extern Cchui the_chui;
extern Csrc the_src;

extern tlk_header tlk_headerinfo;
extern tlk_entry *tlk_entries;
extern bool global_changed;
extern int global_date;
extern key_header key_headerinfo;
extern membif_entry *bifs;
/*
extern CString *bifs;
extern int *biflocs;
*/
extern CString cds[NUM_CD];

extern opcode_struct opcodes[NUM_FEATS];
extern CString weaprofs[NUM_WEAPROF+1];
extern int ammos[NUM_AMTYPE];
extern CString objexts[NUM_OBJTYPE+1];
extern int menuids[NUM_OBJTYPE+1];
extern unsigned short objrefs[NUM_OBJTYPE+1];
extern int idstrings[NUM_OBJTYPE+1];
extern char tbgext[NUM_OBJTYPE+1];
extern char BASED_CODE szFilterKey[];
extern char BASED_CODE szFilterTbg[];
extern char BASED_CODE szFilterWeidu[];
extern char BASED_CODE szFilterBifc[];
extern char BASED_CODE szFilterBif[];
extern CString storetypes[NUM_STORETYPE+1];
extern CString spelltypes[NUM_SPELLTYPE+1];
extern CString itemtypes[NUM_ITEMTYPE+1];
extern long weaprofidx[NUM_WEAPROF+1];
extern unsigned short animtypes[NUM_ANIMTYPES][3];
extern CString animnames[NUM_ANIMTYPES];
extern CString itemanimations[NUM_ANIMIDX];
extern unsigned short animidx[NUM_ANIMIDX];
extern CString slottypes[NUM_SLOTTYPE];
extern CString save_types[NUM_STYPE];
extern CString save_types2[NUM_STYPE2];
extern CString resist_types[NUM_RTYPE];
extern int has_duration[];
extern CStringMapGameProps allgameprops;
extern CStringMapCStringMapInt idsmaps;

//area animation flags
#define AA_MIRROR 2048

 //0 button, 1 unknown,2 slider, 3 editbox,4 unknown, 5 scrolltext,
#define CC_BUTTON    0
#define CC_U1        1
#define CC_SLIDER    2
#define CC_EDITBOX   3
#define CC_U2        4
#define CC_TEXT      5
#define CC_LABEL     6
#define CC_SCROLLBAR 7

#define CCNUM 8

#define EA 0
#define GENERAL 1
#define RACE 2
#define CLASS 3
#define SPECIFIC 4
#define GENDER 5
#define ALIGN 6

#define NUM_IDS  7
extern char *idstype[NUM_IDS];
extern CString kitfile;

extern CColorPicker colordlg;
extern CItemPicker pickerdlg;
extern CString lastopenedscript;
extern CString lastopenedsave;
extern CString lastopeneddata;
/////////////////////////////////////////////////////////////////////////////
// CChitemApp:
// See chitem.cpp for the implementation of this class
//

class CChitemApp : public CWinApp
{
public:
  CChitemApp();
  
  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CChitemApp)
public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL
  CString m_defpath;
  CBitmap m_bbmp;
  HICON m_hIcon;

  // Implementation
  CString MyParseCommandLine(char param);
  int select_setup(CString setupname);
  void save_settings();
  void read_game_preferences();
  
private:
  //{{AFX_MSG(CChitemApp)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

extern CChitemApp theApp;

bool MakeBitmapExternal(const COLORREF *pDIBits, int nWidth, int nHeight, HBITMAP &hBitmap);
bool MakeBitmapExternal(const LPBYTE pPixels, const COLORREF *pPalette, int nWidth, int nHeight, HBITMAP &hBitmap);
void SwapPalette(DWORD *palette, int idx1, int idx2);
int fill_destination(CString key, CComboBox *cb);
int determinemenu(CString commandline);
int determinetype(int reftype);
int WriteString(FILE *fpoi, CString mystring);
int nop();
unsigned long get_hash_size(unsigned long num);
int strtonum(CString str);
bool invalidnumber(CString tmpstr);
CString consolidate(char *poi, int textlength);
int member_array(int member, int *array);
bool checkfile(CString fname, CString magic);
bool file_exists(CString filename);
long file_length(CString filename);
long file_date(CString filename);
bool dir_exists(CString filename);
int my_system(CString syscommand);
int copy_file(int finput, int fhandle, int size, int decrypt); //copying data from bifs
int extract_from_cbf(CString key, CString ext, int finput, int override, int &maxlen);
int decompress_bif(CString bifname, CString cdpath); //this must be a cd bifname
int write_tis_header(int fhandle, loc_entry fileloc);

#define LF_IGNOREOVERRIDE  1
#define LF_IGNORECBF       2

int locate_file(loc_entry &fileloc, int ignoreoverride); //file location, ignore override
int resolve_tbg_entry(long reference, tbg_tlk_reference &ref);
CString get_script_type(int i);
CString format_storetype(unsigned int storetype);
CString format_spellslot(unsigned int spellslot);
CString format_spelltype(unsigned int spelltype);
CString format_schooltype(unsigned int schooltype);
CString format_sectype(unsigned int sectype);
CString format_itemtype(unsigned int itemtype);
short find_itemtype(CString itemtype);
void Pad(CString &str, int len);
void StoreResref(CString &dlgcontrol, char *itempoi);
void RetrieveResref(CString &dlgcontrol, const char *itempoi, int dot=0);
void StoreAnim(CString &dlgcontrol, char *itempoi);
void RetrieveAnim(CString &dlgcontrol, const char *itempoi);
void StoreVariable(CString &dlgcontrol, char *itempoi);
void RetrieveVariable(CString &dlgcontrol, const char *itempoi);
void StoreName(CString &dlgcontrol, char *itempoi);
CString format_label(CString label);
CString format_weaprofs(int profnum);
int getproficiencyidx(int profnum);
CString format_animtype(int animtype);
int getanimationidx(int animtype);
int find_animtype(unsigned short *percents);
CString convert_degree(int value);
CString convert_radius(int value, int direction=0);
CString get_face_value(int fvalue);
CString get_compile_error(int ret);
CString get_spark_colour(int spktype);
CString get_areatype(unsigned long artype);
CString get_attack_type(int atype);
CString get_attacknum(int anum);
int find_attacknum(CString anum);
CString get_slottype(int slottype);
CString get_spell_form(int sftype);
CString get_location_type(int lftype);
CString get_target_type(int ttype);
CString get_projectile_type(int ptype);
CString get_ammo_type(int amtype);
CString get_damage_type(int dtype);
CString get_charge_type(int chtype);
CString get_missile_type(int mtype);
CString get_opcode_text(int opcode);
CString get_opcode_desc(int opcode, int param2);
CString get_par1_label(int opcode);
CString get_par2_label(int opcode);
CString DamageType(int hex);
int ChuiControlSize(int controltype);
CString find_justification(int code);
CString ChuiControlName(int controltype);
CString IDSType(int ids, bool addtwo);
CString IDSName(int ids, bool addtwo);
int IDSKey(CString filename, CString key);
CString IDSToken(CString filename, int value);
int get_idsfile(CString idsname, bool forced);
int FillCombo(CString idsname, CComboBox *cb, int len);
CString get_resist_type(int rtype);
CString get_save_type(int stype);
CString get_timing_type(int tmtype);
CString get_duration_label(int tmtype);
CString get_efftarget_type(int ettype);
CString get_resist_type(int rtype);
CString get_projectile_id(int pronum, int offset);
CString format_priesttype(int ptype);
CString get_region_type(int rttype);
CString format_direction(int dir);
CString get_songname(int songidx);
CString get_songfile(int songidx);
CString get_spawntype(int sptype);
CString get_container_icon(int citype);
CString resolve_scriptelement(int opcode, int trigger, int block);
CString implode(CString *array, int count);
CString *explode2(const CString &array, int &count); //clever explode of a parameter list
CString *explode(const CString &array, char separator, int &count); //dumb explode

//qsort helpers for sorting longs
int longsort(const void *a,const void *b);  //descending
int longsortb(const void *a,const void *b); //ascending

#define GREY_TRESHOLD 2048
#define SMALL_DIFF    16
#define DITHER_MAX 20   //for dl1 dithering

//searchmap tile size
#define GR_WIDTH  16
#define GR_HEIGHT 12

extern unsigned short r_offset[256], g_offset[256], b_offset[256];
extern char *dith_max;
extern BYTE *range;
extern unsigned long *squares;

int ChiSquare(BYTE *a,BYTE *b);

int compile_trigger(CString line, trigger &trigger);
int compile_action(CString line, action &action, bool inoverride);
int handle_trigger(int opcode);
int handle_action(int opcode);
//void outputtable();

//validity checkers
int check_ids_targeting(int par1, int par2);
int check_probability(int p1, int p2);
int check_alignment(long alignment);

//options
bool old_version_dlg();
bool pst_compatible_var();
bool bg1_compatible_area();
bool iwd2_structures();
bool unlimited_itemtypes();
bool no_compress();
bool bg2_weaprofs();
bool has_xpvar();
bool dltc_weaprofs();
bool tob_specific();

CString getitemname(CString filepath);
CString makeitemname(CString ext, int remember);
CString ImageFilter(int mostisbmp);
void CreateMinimap(HWND hwnd);
int GetScanLineLength(int width, int bytes);
CString AssembleWeiduCommandLine(CString filename, CString outpath);
unsigned long getfreememory();
afx_msg void DefaultKillFocus();

//readers & writers (they handle the lookup tables)
void UpdateIEResource(CString key, int restype, CString filepath, int size);
int read_item(CString key);
int write_item(CString key);
int read_spell(CString key);
int write_spell(CString key);
int read_store(CString key);
int read_area(CString key);
int read_projectile(CString key);
int read_chui(CString key);
int read_src(CString key);
int read_creature(CString key);
int write_creature(CString key);
void MakeGradientBitmap(HBITMAP &hb, int GradientIndex);
CString GetMapTypeValue(int maptype, int value);
int read_bmp(CString key,HBITMAP &hb);
int read_bmp(CString key, Cbam *cb, int lazy=0); //cb can't be NULL due to polymorphism
int read_bam(CString key, Cbam *cb=NULL, int lazy=0);
int write_bam(CString key);
int read_mos(CString key, Cmos *cb=NULL, int lazy=0);
int read_tis(CString key, Cmos *cb=NULL, int lazy=0);
int read_dialog(CString key);
int read_videocell(CString key);
int read_mus(CString key);
int read_worldmap(CString key);
int read_effect(CString key);
int read_game(CString key);
int write_game(CString key);
int read_2da(CString key);
int read_ids(CString key);
int play_acm(CString key, bool acm_or_wavc, int justload);
int write_wav(CString key, void *memory, long samples_written, int wav_or_acm);
int check_reference(long reference, int loretoid=0);

/// tlk handler
int truncate_references(long maxnumber);
CString resolve_tlk_text(long reference);
int store_tlk_data(long reference, CString text, CString sound);
BOOL match_tlk_text(long reference, CString text, int ignorecase);
int store_tlk_text(long reference, CString text);
bool resolve_tlk_tag(long reference);
bool toggle_tlk_tag(long reference);
int store_tlk_soundref(long reference, CString sound);
CString resolve_tlk_soundref(long reference);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHITEM_H__82C8D991_857B_4DDB_9704_0525A2869DD5__INCLUDED_)
