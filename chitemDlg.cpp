// chitemDlg.cpp : implementation file
//

#include "stdafx.h"

#define PRG_VERSION "6.1"

#include <fcntl.h>
#include <direct.h>
#include "chitem.h"
#include "chitemDlg.h"
#include "options.h"
#include "compat.h"
#include "FindItem.h"
#include "FileExtract.h"
#include "CFBDialog.h"
#include "IapDialog.h"
#include "StrRefDlg.h"
#include "2da.h"
#include "variables.h"
#include "acmsound.h"
#include "tlkhandler.h"
#include "Bif.h"

//editors
#include "ItemEdit.h"
#include "SpellEdit.h"
#include "StoreEdit.h"
#include "ProjEdit.h"
#include "EffEdit.h"
#include "CreatureEdit.h"
#include "ChuiEdit.h"
#include "VVCEdit.h"
#include "AreaEdit.h"
#include "ScriptEdit.h"
#include "DialogEdit.h"
#include "BamEdit.h"
#include "GameEdit.h"
#include "MapEdit.h"
#include "MosEdit.h"
#include "2DAEdit.h"
#include "SRCEdit.h"
#include "KeyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

CString VersionString()
{
  return "DLTC Editor Pro V" PRG_VERSION;
}

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();
  
  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  CString m_version;
  //}}AFX_DATA
  
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
  // Implementation
protected:
  //{{AFX_MSG(CAboutDlg)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
  m_version = VersionString();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  DDX_Text(pDX, IDC_VERSION, m_version);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChitemDlg dialog


CChitemDlg::CChitemDlg(CWnd* pParent /*=NULL*/)
: CDialog(CChitemDlg::IDD, pParent)
{
  //{{AFX_DATA_INIT(CChitemDlg)
  m_etitle = _T("");
  m_event = _T("");
  //}}AFX_DATA_INIT
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  bifs=NULL;
}

void CChitemDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CChitemDlg)
  DDX_Control(pDX, IDC_EVENT, m_event_control);
  DDX_Text(pDX, IDC_EVENT_TYPE, m_etitle);
  DDX_Text(pDX, IDC_EVENT, m_event);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChitemDlg, CDialog)
//{{AFX_MSG_MAP(CChitemDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_RESCAN, OnRescan)
ON_BN_CLICKED(IDC_RESCAN2, OnRescan2)
ON_BN_CLICKED(IDC_COMPAT, OnCompat)
ON_COMMAND(ID_CONTEXT, OnContext)
ON_COMMAND(ID_TOOLTIPS, OnTooltips)
ON_COMMAND(ID_PROGRESS, OnProgress)
ON_COMMAND(ID_SAVESETTINGS, OnSavesettings)
ON_COMMAND(ID_LOGGING_NONE, OnLoggingNone)
ON_COMMAND(ID_LOGGING_SCREEN, OnLoggingScreen)
ON_COMMAND(ID_LOGGING_FILE, OnLoggingFile)
ON_BN_CLICKED(IDC_FINDITEM, OnFinditem)
ON_BN_CLICKED(IDC_FINDSPELL, OnFindspell)
ON_BN_CLICKED(IDC_FINDEFF, OnFindeff)
ON_BN_CLICKED(IDC_FINDCRE, OnFindcre)
ON_BN_CLICKED(IDC_FINDSTORE, OnFindstore)
ON_COMMAND(ID_SEARCH_PROJECTILE, OnFindProjectile)
ON_COMMAND(ID_SEARCH_VVC, OnFindVvc)
ON_BN_CLICKED(IDC_FINDSCRIPT, OnFindScript)
ON_COMMAND(ID_SEARCH_AREA, OnFindArea)
ON_BN_CLICKED(IDC_CHECKITEM, OnCheckItem)
ON_BN_CLICKED(IDC_CHECKSPELL, OnCheckSpell)
ON_BN_CLICKED(IDC_CHECKSTORE, OnCheckStore)
ON_BN_CLICKED(IDC_CHECKCRE, OnCheckCreature)
ON_COMMAND(ID_CHECK_VVC, OnCheckVvc)
ON_BN_CLICKED(IDC_CHECKSCRIPT, OnCheckScript)
ON_COMMAND(ID_CHECK_AREA, OnCheckArea)
ON_COMMAND(ID_FILE_EXTRACT, OnFileExtract)
ON_COMMAND(ID_READONLY, OnReadonly)
ON_COMMAND(ID_EDIT_ITEM, OnEditItem)
ON_COMMAND(ID_EDIT_VVC, OnEditVvc)
ON_COMMAND(ID_EDIT_CREATURE, OnEditCreature)
ON_COMMAND(ID_EDIT_EFFECT, OnEditEffect)
ON_COMMAND(ID_EDIT_PROJECTILE, OnEditProjectile)
ON_COMMAND(ID_EDIT_SPELL, OnEditSpell)
ON_COMMAND(ID_EDIT_STORE, OnEditStore)
ON_COMMAND(ID_EDIT_AREA, OnEditArea)
ON_COMMAND(ID_ADDCFBTOSPELLS, OnAddcfbtospells)
ON_COMMAND(ID_CLEARCFBFROMSPELLS, OnClearcfbfromspells)
ON_COMMAND(ID_SCANVARIABLES, OnScanvariables)
ON_BN_CLICKED(IDC_RESCAN3, OnRescan3)
ON_BN_CLICKED(IDC_CHECKDIALOG, OnCheckDialog)
ON_BN_CLICKED(IDC_FINDDIALOG, OnFindDialog)
ON_COMMAND(ID_EDIT_DIALOG, OnEditDialog)
ON_COMMAND(ID_EDIT_VARIABLES, OnEditVariables)
ON_BN_CLICKED(IDC_CHECKEFF, OnCheckEffect)
ON_COMMAND(IDM_ABOUTBOX, OnAboutbox)
ON_COMMAND(ID_EDIT_ANIMATION, OnEditAnimation)
ON_COMMAND(ID_CHECK_ANIMATION, OnCheckAnimation)
ON_COMMAND(ID_UNCOMPRESSBIF, OnUncompressbif)
ON_COMMAND(ID_FILE_SEARCH, OnFileSearch)
ON_COMMAND(ID_WAVCTOWAV, OnWavctowav)
ON_BN_CLICKED(IDC_RESCAN4, OnRescan4)
ON_COMMAND(ID_EDIT_GAMES, OnEditGames)
ON_COMMAND(ID_CHECK_GAME, OnCheckGame)
ON_COMMAND(ID_EDIT_WORLDMAP, OnEditWorldmap)
ON_COMMAND(ID_EDIT_GRAPHICS, OnEditGraphics)
ON_COMMAND(ID_CHECK_WORLDMAP, OnCheckWorldmap)
ON_COMMAND(ID_EDIT_2DA, OnEdit2da)
ON_BN_CLICKED(IDC_RESCAN5, OnRescan5)
ON_COMMAND(ID_EDIT_IDS, OnEditIds)
ON_COMMAND(ID_FILE_IMPORTTBG, OnImporttbg)
ON_COMMAND(ID_FILE_EXPORTTBG, OnCreateIAP)
ON_COMMAND(ID_EDIT_SCRIPT, OnEditScript)
ON_COMMAND(ID_CHECK_2DA, OnCheck2da)
ON_COMMAND(ID_TOOLS_LOOKUPSTRREF, OnLookupstrref)
ON_COMMAND(ID_UNCOMPRESSSAV, OnUncompresssav)
ON_COMMAND(ID_UNCOMPRESSCBF, OnUncompresscbf)
	ON_COMMAND(ID_ACMTOWAV, OnAcmtowav)
	ON_COMMAND(ID_EDIT_MUSICLIST, OnEditMusiclist)
	ON_COMMAND(ID_WAVTOACM, OnWavtoacm)
	ON_COMMAND(ID_WAVTOWAVC, OnWavtowavc)
	ON_COMMAND(ID_EDIT_TILESET, OnEditTileset)
	ON_COMMAND(ID_WAVCTOWAV2, OnWavctowav2)
	ON_COMMAND(ID_ACMTOWAV2, OnAcmtowav2)
	ON_COMMAND(ID_FILE_IMPORTD, OnFileImportd)
	ON_COMMAND(ID_EDIT_KEY, OnEditKey)
	ON_COMMAND(ID_REORDERBIF, OnReorderbif)
ON_COMMAND(ID_CHECK_PROJECTILE, OnCheckProjectile)
	ON_COMMAND(ID_SEARCH_2DA, OnFind2da)
	ON_COMMAND(ID_SEARCH_BAM, OnSearchBam)
	ON_COMMAND(ID_EDIT_CHUI, OnEditChui)
	ON_COMMAND(ID_SEARCH_UI, OnSearchUi)
	ON_COMMAND(ID_CHECK_UI, OnCheckUi)
	ON_COMMAND(ID_EDIT_STRINGSSRC, OnEditSRC)
ON_COMMAND(ID_COMPAT, OnCompat)
ON_COMMAND(ID_SEARCH_ITEM, OnFinditem)
ON_COMMAND(ID_SEARCH_SPELL, OnFindspell)
ON_COMMAND(ID_SEARCH_CREATURE, OnFindcre)
ON_COMMAND(ID_SEARCH_STORE, OnFindstore)
ON_COMMAND(ID_SEARCH_EFFECT, OnFindeff)
ON_COMMAND(ID_SEARCH_SCRIPT, OnFindScript)
ON_COMMAND(ID_SEARCH_DIALOG, OnFindDialog)
ON_COMMAND(ID_SEARCH_SCRIPT, OnFindScript)
ON_COMMAND(ID_CHECK_ITEM, OnCheckItem)
ON_COMMAND(ID_CHECK_SPELL, OnCheckSpell)
ON_COMMAND(ID_CHECK_CREATURE, OnCheckCreature)
ON_COMMAND(ID_CHECK_STORE, OnCheckStore)
ON_COMMAND(ID_CHECK_SCRIPT, OnCheckScript)
ON_COMMAND(ID_CHECK_DIALOG, OnCheckDialog)
ON_COMMAND(ID_CHECK_DIALOG, OnCheckDialog)
ON_COMMAND(ID_CHECK_EFFECT, OnCheckEffect)
ON_COMMAND(ID_RESCAN, OnRescan)
ON_COMMAND(ID_RESCAN2, OnRescan2)
ON_COMMAND(ID_RESCAN3, OnRescan3)
ON_COMMAND(ID_RESCAN4, OnRescan4)
ON_COMMAND(ID_RESCAN5, OnRescan5)
	ON_BN_CLICKED(IDC_FINDPROJ, OnFindArea)
	ON_BN_CLICKED(IDC_CHECKPROJ, OnCheckArea)
	ON_COMMAND(ID_TOOLS_SCANJOURNALENTRIES, OnScanjournal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChitemDlg message handlers
BOOL CChitemDlg::PreTranslateMessage(MSG* pMsg)
{
  m_tooltip.RelayEvent(pMsg);
  return CDialog::PreTranslateMessage(pMsg);
}

static const int logmenu[]={ID_LOGGING_NONE, ID_LOGGING_SCREEN, ID_LOGGING_FILE,0};

void CChitemDlg::start_progress(int max, CString title)
{
  if(!m_progressdlg && do_progress)
  {
    m_progressdlg=new progressbar;
    if(m_progressdlg)
    {
      m_progressdlg->Create(IDD_PROGRESS);
    }
  }
  if(m_progressdlg) m_progressdlg->SetRange(max,title);
}

void CChitemDlg::set_progress(int actual)
{
  if(m_progressdlg)
  {
    m_progressdlg->SetProgress(actual);
  }    
}

void CChitemDlg::end_progress()
{
  if(m_progressdlg)
  {
    m_progressdlg->DestroyWindow();
    delete m_progressdlg;
    m_progressdlg=NULL;
  }
}

void CChitemDlg::start_panic()
{
  if(m_panicbutton) return;
  m_panicbutton=new panicbutton;
  if(m_panicbutton)
  {
    m_panicbutton->Create(IDD_PANICBUTTON,0);
  }  
}

void CChitemDlg::end_panic()
{
  if(m_panicbutton)
  {
    m_panicbutton->DestroyWindow();
    delete m_panicbutton;
    m_panicbutton=NULL;
  }
}

void CChitemDlg::rescan_dialog(bool flg)
{
  scan_dialog(flg);
  end_progress();
}

BOOL CChitemDlg::OnInitDialog()
{
  int tmp;
  int SMALL_PRIME, MEDIUM_PRIME, LARGE_PRIME;

  CDialog::OnInitDialog();
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  
  SMALL_PRIME=get_hash_size(100);
  MEDIUM_PRIME=get_hash_size(1000);
  LARGE_PRIME=get_hash_size(5000);

  items.InitHashTable(LARGE_PRIME);//.itm1
  creatures.InitHashTable(LARGE_PRIME); //.cre2
  icons.InitHashTable(LARGE_PRIME); //.bam3
  bitmaps.InitHashTable(LARGE_PRIME); //.bmp4
  stores.InitHashTable(SMALL_PRIME); //.sto5
  dialogs.InitHashTable(LARGE_PRIME); //.dlg6
  darefs.InitHashTable(MEDIUM_PRIME); //.2da7
  scripts.InitHashTable(LARGE_PRIME); //.bcs8
  idrefs.InitHashTable(SMALL_PRIME); //.ids9
  projects.InitHashTable(SMALL_PRIME); //.pro10
  spells.InitHashTable(MEDIUM_PRIME); //.spl11
  effects.InitHashTable(MEDIUM_PRIME); //.eff12
  vvcs.InitHashTable(SMALL_PRIME); //.vvc13
  areas.InitHashTable(MEDIUM_PRIME);//.are14
  chuis.InitHashTable(SMALL_PRIME); //.chu15
  mos.InitHashTable(MEDIUM_PRIME); //.mos16
  weds.InitHashTable(MEDIUM_PRIME); //.wed17
  tis.InitHashTable(MEDIUM_PRIME); //.tis18
  sounds.InitHashTable(LARGE_PRIME); //.wav19
  games.InitHashTable(SMALL_PRIME); //.gam20
  wmaps.InitHashTable(SMALL_PRIME); //.wmp21
  musics.InitHashTable(SMALL_PRIME); //.acm22
  musiclists.InitHashTable(SMALL_PRIME); //.mus23
  movies.InitHashTable(SMALL_PRIME); //.mve24
  wfxs.InitHashTable(SMALL_PRIME); //.wfx25
  strings.InitHashTable(SMALL_PRIME); //.src26
  paperdolls.InitHashTable(SMALL_PRIME); //.plt27
  vefs.InitHashTable(SMALL_PRIME); //.vef28
  inis.InitHashTable(SMALL_PRIME); //.ini29

  storeitems.InitHashTable(SMALL_PRIME); //container .itm
  rnditems.InitHashTable(SMALL_PRIME);   //random .itm
  dial_references.InitHashTable(SMALL_PRIME);
  store_spell_desc.InitHashTable(SMALL_PRIME); //store spell descriptions
  variables.InitHashTable(MEDIUM_PRIME);
  searchflags=0;
  memset(&searchdata,0,sizeof(searchdata) );
  
  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);
  
  CMenu* pSysMenu = GetSystemMenu(FALSE);
  if (pSysMenu != NULL)
  {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);
    if (!strAboutMenu.IsEmpty())
    {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }
  
  //tooltips
  {
    m_tooltip.Create(this,TTS_NOPREFIX);
    m_tooltip.SetMaxTipWidth(200);
    m_tooltip.SetTipBkColor(RGB(240,224,160));

    m_tooltip.AddTool(GetDlgItem(IDC_RESCAN), IDS_RESCAN);
    m_tooltip.AddTool(GetDlgItem(IDC_RESCAN2), IDS_RESCAN2);
    m_tooltip.AddTool(GetDlgItem(IDC_RESCAN3), IDS_RESCAN3);
    m_tooltip.AddTool(GetDlgItem(IDC_RESCAN4), IDS_RESCAN4);
    m_tooltip.AddTool(GetDlgItem(IDC_RESCAN5), IDS_RESCAN5);
    m_tooltip.AddTool(GetDlgItem(IDC_COMPAT), IDS_GAMEOPT);
    m_tooltip.AddTool(GetDlgItem(IDC_EVENT), IDS_EVENT);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKITEM), IDS_RUN);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKSTORE), IDS_RUN2);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKPROJ), IDS_RUN4);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKSPELL), IDS_RUN3);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKSCRIPT),IDS_CHECKSCRIPT);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKDIALOG),IDS_CHECKDLG);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKEFF),IDS_CHECKEFF);
    m_tooltip.AddTool(GetDlgItem(IDC_CHECKCRE),IDS_CHECKCRE);
    m_tooltip.AddTool(GetDlgItem(IDOK), IDS_EXIT);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDCRE), IDS_FIND1);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDITEM), IDS_FIND2);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDSPELL),IDS_FIND3);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDEFF),IDS_FIND4);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDSTORE),IDS_FINDSTOR);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDSCRIPT),IDS_FINDSCRIPT);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDDIALOG),IDS_FINDDLG);
    m_tooltip.AddTool(GetDlgItem(IDC_FINDPROJ),IDS_FINDPROJ);
  }
  
  _fmode=O_BINARY;
  newitem=FALSE;
  m_progressdlg=0;
  m_panicbutton=0;

  if(bgfolder.IsEmpty())
  {
    MessageBox("Please run setup!");
  }
  else
  {
    if(read_effect_descs())
    {
      MessageBox("There was an error while processing the effect descriptions.","Warning",MB_ICONWARNING|MB_OK);
    }
    scan_chitin();
    scan_override();
    scan_2da();
    scan_dialog();
    load_variables(m_hWnd, 0, 1, variables); //not verbose
    end_progress();
  }
  RefreshMenu();
  UpdateData(UD_DISPLAY);
  if(theApp.m_lpCmdLine)
  { 
    tmp=menuids[determinemenu(theApp.MyParseCommandLine('f'))];
    if(tmp) PostMessage(WM_COMMAND,tmp,0);
  }
  return TRUE;
}

void CChitemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  if(nID==0xf012)
  {
    PostMessage(WM_SYSCOMMAND,SC_CONTEXTHELP,0);    
  }
  if ((nID & 0xFFF0) == IDM_ABOUTBOX)
  {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  }
  else
  {
    CDialog::OnSysCommand(nID, lParam);
  }
}

void CChitemDlg::OnAboutbox() 
{
  CAboutDlg dlgAbout;
  dlgAbout.DoModal();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChitemDlg::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting
    
    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
    
    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    
    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }
}

HCURSOR CChitemDlg::OnQueryDragIcon()
{
  return (HCURSOR) m_hIcon;
}

void CChitemDlg::log(CString format, ...)
{
  FILE *fpoi;
  int x;
  va_list arglist;
  
  if(logtype==LOG_NO)
  {
    return;
  }
  if(newitem)
  {
    newitem=FALSE;
    log(itemname);
  }
  if(logtype==LOG_SCREEN)
  {
    m_etitle="Event log:";
    m_event_control.SetReadOnly(true);
  }
  if(format.IsEmpty())
  {
    m_event="";
    return;
  }
  va_start(arglist, format);
  lasterrormsg.FormatV(format,arglist);
  va_end(arglist);
  if(logtype==LOG_FILE)
  {
    fpoi=fopen("chitem.log","at");
    if(fpoi)
    {
      fprintf(fpoi,"%s\n",lasterrormsg);
      fclose(fpoi);
    }
    return;
  }
  if(m_event.IsEmpty())
  {
    m_event=lasterrormsg;
    x=0;
  }
  else
  {
    m_event+=CString("\r\n")+lasterrormsg;
    if(m_event.GetLength()>30000)
    {
      x=m_event.Find("\n",10000);
      if(x>0)
      {
        m_event=m_event.Mid(x+1);
      }
    }
  }
  UpdateData(UD_DISPLAY);
  m_event_control.LineScroll(MAX_LINE);
}

int CChitemDlg::scan_2da()
{
  POSITION pos;
  CString key;
  loc_entry tmploc;
  CStringMapInt *value;
  int val;
  int i;

  init_colors();
  pos=idsmaps.GetStartPosition();
  while(pos)
  {
    idsmaps.GetNextAssoc(pos,key,value);
    delete value;
  }
  idsmaps.RemoveAll();

  if(has_xpvar()) //iwd and iwd2
  {
    darefs.Lookup("EXPTABLE",tmploc);
    val=Read2da(tmploc, xplist);
  }
  else
  {
    if(tob_specific())
    {
      darefs.Lookup("XPLIST",tmploc);
      val=Read2da(tmploc, xplist);
    }
    else val=0;
  }
  if(val<0)
  {
    xplist.RemoveAll();
    if(has_xpvar())
    {
      MessageBox("exptable.2da not found, addxpvar actions will be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
    else
    {
      MessageBox("xplist.2da not found, addxp2da actions will be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
  }

  if(bg2_weaprofs())
  {
    darefs.Lookup("WEAPPROF",tmploc);
    val=ReadWeapProfs(tmploc);
  }

  if(!pst_compatible_var())
  {
    darefs.Lookup("ITEMEXCL",tmploc);
    val=Read2da(tmploc, exclude_item);
    if(val<0)
    {
      exclude_item.RemoveAll();
      MessageBox("itemexcl.2da not found, cannot edit 'exclude from wear' bit.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
  }

  val=get_idsfile("ANIMATE",true);
  if(val<0)
  {
    MessageBox("animate.ids not found, creatures will be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }

  val=get_idsfile("OBJECT",true);
  if(val<0)
  {
    MessageBox("object.ids not found, action/trigger checks may fail.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }

  if(has_xpvar()) //iwd1/iwd2
  {
    darefs.Lookup("MUSIC",tmploc);
    val=Read2daString(tmploc, songlist,0); //iwd2 (0 and 1)
  }
  else
  {
    if(!bg1_compatible_area())
    {
      idrefs.Lookup("SONGS",tmploc);
      val=ReadSongIds(tmploc, songlist); //pst
      if(val<0)
      {
        darefs.Lookup("SONGLIST",tmploc);
        val=Read2daString(tmploc, songlist,1); //1 and 2
        if(val) MessageBox("songlist.2da is inconsistent.","Warning",MB_ICONEXCLAMATION|MB_OK);
      }
    }
  }
  
  if(val<0)
  {
    MessageBox("songlist.2da or music.2da not found, song names are unavailable.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }
    
  
  if(!pst_compatible_var() && !bg1_compatible_area())
  {
    darefs.Lookup("MSECTYPE",tmploc);
    val=Read2da(tmploc,sectype_names);
    if(val<0)
    {
      idrefs.Lookup("SECTYPE",tmploc);
      val=ReadIds(tmploc,sectype_names,0);
    }
    if(val<0)
    {
      MessageBox("sectype.2da not found, spells may be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
    darefs.Lookup("MSCHOOL",tmploc);
    val=Read2da(tmploc,school_names);
    if(val<0)
    {
      idrefs.Lookup("SCHOOL",tmploc);
      val=ReadIds(tmploc,school_names,0);
    }
    if(val<0)
    {
      MessageBox("mschool.2da not found, spells may be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
    
//
    val=get_idsfile("KIT",true);
    if(val<0)
    {
      kitfile="MAGESPEC";
      val=get_idsfile("MAGESPEC", true);
    }
    else
    {
      kitfile="KIT";
    }
    if(val<0)
    {
      MessageBox("kit.ids or magespec.ids not found, spell school exclusion is not available.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }      
  }
  idrefs.Lookup("SNDSLOT",tmploc);
  val=ReadIds2(tmploc, snd_slots, SND_SLOT_COUNT);
  if(val<0)
  {
    idrefs.Lookup("SOUNDOFF",tmploc);
    val=ReadIds2(tmploc, snd_slots, SND_SLOT_COUNT);
  }
  if(val<0)
  {
    MessageBox("No sndslot.ids or soundoff.ids found, sound slot names are unavailable "
      "(copy a sndslot.ids file into your override folder if you want them).",
      "Warning",MB_ICONEXCLAMATION|MB_OK);
  }

  if(iwd2_structures())
  {
//    idrefs.Lookup("SLOTS",tmploc);
//    val=ReadIds2(tmploc, slot_names,IWD2_SLOT_COUNT);
    darefs.Lookup("RT_FURY", tmploc);
    val=Read2daInt(tmploc, rnditems, 1); //removeall=1
    darefs.Lookup("RT_NORM", tmploc);
    val|=Read2daInt(tmploc, rnditems, 0); //adding more items

//this is the slot setup
    for(i=0;i<IWD2_SLOT_COUNT;i++) slot_names[i]=iwd2_slot_names[i];
  }
  else
  {
    if(has_xpvar()) //iwd 
    {
      darefs.Lookup("RNDTRES", tmploc);
      val=Read2daInt(tmploc, rnditems, 1); //adding more items
    }

    if(bg1_compatible_area())
    {
      idrefs.Lookup("SLOTS",tmploc);
      val=ReadIds2(tmploc, slot_names,SLOT_COUNT);
      if(val<0)
      {
        MessageBox("slots.ids not found, slot names are unavailable.","Warning",MB_ICONEXCLAMATION|MB_OK);
      }
    }
    else
    {
      if(pst_compatible_var())
      {
        for(i=0;i<PST_SLOT_COUNT;i++) slot_names[i]=pst_slot_names[i];
      }
      else
      {
        for(i=0;i<SLOT_COUNT;i++) slot_names[i]=bg2_slot_names[i];
      }
    }
  }
  
  idrefs.Lookup("ACTION",tmploc);
  val=ReadIds3(tmploc, action_defs, MAX_ACTION, action_data, 0);
  switch(val)
  {
  case -2:
    MessageBox("action.ids not found, actions won't be resolved.","Warning",MB_ICONEXCLAMATION|MB_OK);
    break;
  case -1:
    MessageBox("action.ids is wrong, actions won't be resolved.","Warning",MB_ICONEXCLAMATION|MB_OK);
    break;
  }

  idrefs.Lookup("TRIGGER",tmploc);
  val=ReadIds3(tmploc, trigger_defs, MAX_TRIGGER, trigger_data, 1);
  switch(val)
  {
  case -2:
    MessageBox("trigger.ids not found, triggers won't be resolved.","Warning",MB_ICONEXCLAMATION|MB_OK);
    break;
  case -1:
    MessageBox("trigger.ids is wrong, triggers won't be resolved.","Warning",MB_ICONEXCLAMATION|MB_OK);
    break;
  }

  idrefs.Lookup("RACE",tmploc);
  val=ReadIds(tmploc, race_names,1);
  if(val<0)
  {
    MessageBox("race.ids not found, race names are unavailable.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }

  darefs.Lookup("SPAWNGRP",tmploc);
  Read2daRow(tmploc, spawngroup, 0); //no error reporting

  //these are not present in the blackisle branch
  if(tob_specific())
  {
    val=get_idsfile("FIREBALL",true);
    if(val<0)
    {
      MessageBox("fireball.ids not found, projectiles may be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
    
    idrefs.Lookup("MISSILE",tmploc);
    val=ReadIds(tmploc, pro_titles,1);
    if(val<0)
    {
      MessageBox("missile.ids not found, projectiles won't be described.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }    
  }
  else pro_titles.RemoveAll();

  if(!has_xpvar() && !pst_compatible_var())
  {
    if(!bg1_compatible_area())
    {
      idrefs.Lookup("PROJECTL",tmploc);
      val=ReadIds(tmploc, pro_references,2);
      if(val<0)
      {
        pro_references.RemoveAll();
        MessageBox("projectl.ids not found, projectiles may be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
      }
      darefs.Lookup("ITEMDIAL",tmploc);
      val=Read2daInt(tmploc, dial_references,1);
      if(val<0)
      {
        dial_references.RemoveAll(true);
        MessageBox("itemdial.2da not found, talking items will be buggy.","Warning",MB_ICONEXCLAMATION|MB_OK);
      }  
    }
  }
  else  //these are present in all blackisle but not in bioware
  {
    pro_references.RemoveAll();
    dial_references.RemoveAll(true);
    val=get_idsfile("CLOWNCLR", true);
    if(val<0)
    {
      MessageBox("Colour definitions not found, using default.","Warning",MB_ICONEXCLAMATION|MB_OK);
    }
  }

  darefs.Lookup("SPELDESC", tmploc);
  val=Read2daArray(tmploc, store_spell_desc,1);
  if(val<0)
  {
    store_spell_desc.RemoveAll(true);
    MessageBox("speldesc.2da not found, store spell names won't be used.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }  
  
  darefs.Lookup("TOOLTIP",tmploc);
  val=Read2daArray(tmploc, tooltipnumbers,3);
  if(val<0)
  {
    tooltipnumbers.RemoveAll(true);
    MessageBox("tooltip.2da not found, tooltips won't be used.","Warning",MB_ICONEXCLAMATION|MB_OK);    
  }
  return 0;
}

int CChitemDlg::scan_dialog(bool refresh)
{
  CString text;
  char *poi;
  tlk_reference reference;
  int fhandle1, fhandle2;
  long actpos;
  int maxref;
  int i;

  tlkfilename.Format("%sdialog%s.tlk",bgfolder,(optflg&DIALOGF)?"F":"");
  //don't reload the .tlk if it didn't change
  actpos=file_date(tlkfilename);
  if(refresh && (actpos==global_date)) return 0;
  global_changed=false;
  tlk_headerinfo.entrynum=-1;
  global_date=actpos;
  fhandle1=open(tlkfilename,O_RDONLY|O_BINARY);
  if(fhandle1<1)
  {
    MessageBox("No "+tlkfilename+" found, ignoring string references.","Warning",MB_ICONEXCLAMATION|MB_OK);
    return -1;
  }
  fhandle2=open(tlkfilename, O_RDONLY | O_BINARY);
  if(fhandle2<1)
  {
    MessageBox("Cannot open "+tlkfilename+" for the second time (out of resources?)","Error",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle1);
    return -1;
  }
  
  if(read(fhandle1,&tlk_headerinfo,sizeof(tlk_headerinfo) )!=sizeof(tlk_headerinfo) )
  {
    tlk_headerinfo.entrynum=-1;
    MessageBox(tlkfilename+" is corrupt, ignoring string references.","Warning",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle1);
    close(fhandle2);
    return -1;
  }
  maxref=tlk_headerinfo.entrynum;
  if(tlk_entries)
  {
    delete [] tlk_entries;
  }
  tlk_entries=new tlk_entry[maxref];
  if(!tlk_entries)
  {
    MessageBox("Not enough memory to load "+tlkfilename,"Error",MB_ICONSTOP|MB_OK);
    close(fhandle1);
    close(fhandle2);
    return -3;
  }

  start_progress(maxref,"Reading dialog.tlk");
  if((unsigned long) tlk_headerinfo.start!=tlk_headerinfo.entrynum*sizeof(tlk_reference)+sizeof(tlk_headerinfo))
  {
    if(MessageBox("The .tlk file appears to be corrupted, shall I try to fix it?","Warning",MB_ICONQUESTION|MB_YESNO)==IDYES )
    {
      tlk_headerinfo.start=tlk_headerinfo.entrynum*sizeof(tlk_reference)+sizeof(tlk_headerinfo);
      global_changed=true;
    }
  }
  lseek(fhandle2,tlk_headerinfo.start,SEEK_SET);
  i=0;
  while(maxref--)
  {
    if(read(fhandle1,&reference,sizeof(tlk_reference) )!=sizeof(tlk_reference) )
    {
      log("Cannot read reference #%d (.tlk is corrupted)",i);
      maxref=0; //bail out gracefully
      global_changed=false;
    }
    actpos=tell(fhandle2);
    if(actpos!=tlk_headerinfo.start+reference.offset)
    {
      if(reference.length)
      {
        log("Incorrect reference #%d (.tlk file is corrupted)",i);
        reference.offset=actpos-tlk_headerinfo.start;
        global_changed=false;
        maxref=0;
      }
    }
    if(reference.length<0)
    {
      log("Incorrect reference length of %d for #%d (.tlk file is corrupted)",reference.length,i);
      global_changed=false;
      maxref=0;
    }
    poi=text.GetBuffer(reference.length+1);
    read(fhandle2,poi,reference.length);
    poi[reference.length]=0;
    text.ReleaseBuffer(-1);
    reference.length=text.GetLength(); //recalculate length
    memcpy(&tlk_entries[i].reference, &reference,sizeof(tlk_reference) );
    tlk_entries[i].text=text;
    set_progress(++i);
  }
  close(fhandle1);
  close(fhandle2);
  return 0;
}

#define NUM_INI 4
CString inifiles[NUM_INI]={"torment.ini","baldur.ini","icewind2.ini","icewind.ini"};

void CChitemDlg::read_cd_locations()
{
  CString inifile;
  CString key;
  char *poi;
  int i,j;

  for(i=0;i<NUM_INI;i++)
  {
    inifile=bgfolder+inifiles[i];
    if(file_exists(inifile) ) break;
  }
  if(i==NUM_INI) return;
  for(i=0;i<NUM_CD;i++)
  {
    key.Format("CD%d:",i+1);
    poi=cds[i].GetBuffer(MAX_PATH);
    GetPrivateProfileString("alias",key,"",poi,MAX_PATH,inifile);
    for(j=0;j<MAX_PATH && poi[j];j++)
    {
      if(poi[j]==';')
      {
        poi[j]=0;
        break;
      }
    }
    cds[i].ReleaseBuffer();
  }
}

int CChitemDlg::scan_chitin()
{
  key_entry resentry;
  keybif_entry bifentry;
  loc_entry fileloc;
  CString chfilename;
  CString ref, ext;
  int fhandle;
  int ret;
  long bifidx, locidx;
  long tmpofs;
  char *poi;
  int i, type;
  int numref, duplo;

  log("");
  for(i=1;i<=NUM_OBJTYPE;i++)
  {
    resources[i]->RemoveAll(true);  //keep hash value
    duplicates[i]->RemoveAll();
  }

  storeitems.RemoveAll();
  memset(&key_headerinfo,0,sizeof(key_headerinfo));
  if(bifs)
  {
    delete [] bifs;
    bifs=NULL;
  }

  if(chkflg&IGNORECHITIN) return 0;
  if(bgfolder.IsEmpty()) return 0;
  read_cd_locations();
  
  duplo=!(chkflg&NODUPLO);
  chfilename.Format("%schitin.key",bgfolder);
  fhandle=open(chfilename,O_RDONLY|O_BINARY);
  if(fhandle<1)
  {
    MessageBox("No "+chfilename+" found, checking only the override folder","Warning",MB_ICONEXCLAMATION|MB_OK);
    return -1;
  }
  if(read(fhandle,&key_headerinfo,sizeof(key_headerinfo) )!=sizeof(key_headerinfo) )
  {
    MessageBox(chfilename+" is corrupt, checking only the override folder","Warning",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle);
    return -1;
  }
  if(memcmp(key_headerinfo.signature,"KEY ",4) )
  {
    MessageBox(chfilename+" is corrupt, checking only the override folder","Warning",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle);
    return -1;
  }
  //reading bifnames
  if(lseek(fhandle,key_headerinfo.offbif,SEEK_SET)!=key_headerinfo.offbif)
  {
    MessageBox(chfilename+" is corrupt, checking only the override folder","Warning",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle);
    return -1;
  }
  bifs=new membif_entry[key_headerinfo.numbif];
  if(!bifs)
  {
    return -3;
  }
  
  for(bifidx=0;bifidx<key_headerinfo.numbif;bifidx++)
  {
    read(fhandle,&bifentry,sizeof(bifentry) );
    tmpofs=tell(fhandle); //jumping to bif string
    lseek(fhandle,bifentry.offbif,SEEK_SET);
    bifs[bifidx].bifname.Empty();
    poi=bifs[bifidx].bifname.GetBufferSetLength(bifentry.namelen);
    read(fhandle,poi,bifentry.namelen);
    bifs[bifidx].bifname.ReleaseBuffer();
    bifs[bifidx].biflen=bifentry.biflen;
    bifs[bifidx].location=bifentry.location;
    lseek(fhandle,tmpofs,SEEK_SET);
  }
  
  //reading itm's
  if(lseek(fhandle,key_headerinfo.offref,SEEK_SET)!=key_headerinfo.offref)
  {
    MessageBox(chfilename+" is corrupt, checking only the override folder.","Warning",MB_ICONEXCLAMATION|MB_OK);
    close(fhandle);
    return -1;
  }
  ret=0;
  i=0;
  //
  start_progress(key_headerinfo.numref,"Reading chitin.key");

  numref=key_headerinfo.numref;
  while(numref--)
  {
    set_progress(++i);
    read(fhandle,&resentry,sizeof(resentry) );
    RetrieveResref(ref,resentry.filename);
    
    bifidx=(long) (resentry.residx>>20);    //highest 12 bits
    locidx=(long) (resentry.residx&0xfffff); //lowest 20 bits
    type=determinetype(resentry.restype);
    if(!type)
    {
      log("Unknown resource: %s/%0x",ref,resentry.restype);
      continue;
    }
    ext=objexts[type];
    chfilename.LoadString(idstrings[type]);
    if(duplo && resources[type]->Lookup(ref,fileloc) )
    {
      duplicates[type]->AddList(ref,fileloc); //old duplicated entries
      log("Duplicate %s in chitin.key: %s%s (%s  %s)",chfilename,ref,ext,fileloc.bifname,bifs[bifidx].bifname);
    }
    if(bifidx>=key_headerinfo.numbif)
    {
      log("Invalid resource locator: 0x%x",resentry.residx);
      continue;
    }
    fileloc.bifname=bifs[bifidx].bifname;
    fileloc.index=locidx;
    fileloc.size=-1;
    fileloc.bifindex=(unsigned short) bifidx;
    fileloc.cdloc=0;
    fileloc.resref=ref+ext;
    //another cheesy, fishy hack for the different path of sounds
    if(!fileloc.bifname.CompareNoCase("data\\desound.bif") )
    {
      if(file_exists(bgfolder+"\\sounds\\"+ref+".wav") )
      {
        fileloc.index=-1;
        fileloc.bifname="\\sounds\\"+ref+".wav";
      }
    }
    resources[type]->SetAt(ref,fileloc);
  }
  close(fhandle);
  for(i=1;i<NUM_OBJTYPE;i++)
  {
    chfilename.LoadString(idstrings[i]);
    log("Found %d %s(s) in chitin.key.",resources[i]->GetCount(), chfilename);
  }
  return ret;
}

void CChitemDlg::scan_override()
{
  if(gather_override("override\\")) OnCancel();
  if(gather_override("music\\",true)) OnCancel();
}

//
int CChitemDlg::gather_override(CString folder, int where)
{
  CString filename;
  CString ref;
  loc_entry fileloc;
  int ovrnum[NUM_OBJTYPE+1]; //this should be +1 because we start counting at 1
  int fhandle;
  _finddata_t fdata;
  int flg;
  int type;
  CStringMapLocEntry *resourcepoi;
  
  memset(ovrnum,0,sizeof(ovrnum));
  flg=0;
  filename=bgfolder+folder+"*.*";
  //scanning override dir for loose items
  fhandle=_findfirst(filename,&fdata);
  if(fhandle>0)
  {
    do
    {
      if(strlen(fdata.name)>12)
      {
        if(chkflg&NOMISS)
        {
          MessageBox("Invalid filename: "+folder+fdata.name);
        }
        continue;
      }
      RetrieveResref(ref,fdata.name,1);
      resourcepoi=resources[type=determinemenu(fdata.name)];
      if(!resourcepoi)
      {
        continue;
      }
      flg=resourcepoi->Lookup(ref,fileloc);
      filename=folder+ref+objexts[type];      
      fileloc.bifname=filename;
      fileloc.size=fdata.size;
      fileloc.resref=ref+objexts[type];
      if(!flg)
      {
        fileloc.bifindex=0xffff;
        fileloc.index=-2;
        fileloc.cdloc=0;  //not found in chitin, we should initialize it
        ovrnum[type]++;
        if(chkflg&NOMISS)
        {
          filename.LoadString(idstrings[type]);
          log("%s is an extra %s not found in chitin.key.",ref, filename);
        }
      }
      resourcepoi->SetAt(ref,fileloc);
    }
    while(!_findnext(fhandle, &fdata));
    _findclose(fhandle);
  }

  if(where)
  {
    ovrnum[0]=generate_acm_list();
    log("Found %d musics listed in musiclists.",ovrnum[0]);
  }
  else
  {
    for(type=1;type<NUM_OBJTYPE;type++)
    {
      if(ovrnum[type])
      {
        filename.LoadString(idstrings[type]);
        log("Found %d %s(s) not listed in chitin.key",ovrnum[type],filename);
      }
    }
  }
  return 0;
}

int CChitemDlg::AddAcm(CString key, loc_entry &fileloc, int dont)
{
  loc_entry tmploc;
  int fhandle;

  key.MakeUpper();
  if(key.IsEmpty()) return 0;
  if(key=="END") return 0;
  if(!dont) varname2=key;
  fileloc.resref=convert_musiclist(key,true);
  fileloc.bifname="music\\"+convert_musiclist(key,false)+".acm";
  fhandle=open(bgfolder+fileloc.bifname,O_BINARY|O_RDONLY);
  if(fhandle>0)
  {
    fileloc.size=filelength(fhandle);
    close(fhandle);
    if(!musics.Lookup(key,tmploc))
    {
      musics[fileloc.resref]=fileloc;
    }
    return 0;
  }
  return -1;
}

int CChitemDlg::CollectAcms()
{
  CString *tags;
  POSITION pos;
  loc_entry fileloc;
  int ret;

  ret=0;
  fileloc.bifindex=0xffff;
  fileloc.size=-1;
  fileloc.cdloc=0;
  fileloc.index=-2;
  if(!the_mus.data) return -2;
  pos=the_mus.data->GetHeadPosition();
  while(pos)
  {
    tags=(CString *) the_mus.data->GetNext(pos);
    ret|=AddAcm(tags[0],fileloc,ret);
    ret|=AddAcm(tags[1],fileloc,ret);
    ret|=AddAcm(tags[2],fileloc,ret);
  }
  return ret;
}

int CChitemDlg::generate_acm_list()
{
  int ret, flg;
  POSITION pos;
  CString key, tmpstr;
  loc_entry fileloc;

  tmpstr=itemname;
  ret=musics.GetCount();
  log("Generating music list...");
  pos=musiclists.GetStartPosition();
  while(pos)
  {
    musiclists.GetNextAssoc(pos,key,fileloc);
    changeitemname(key);
    if(!read_mus(key) )
    {
      flg=CollectAcms();
      switch(flg)
      {
      case -2:
        log("Invalid musiclist.");
        break;
      case -1:
        log("Missing music (%s) in musiclist.",varname2);
        break;
      }
    }
    else log("Error loading musiclist.");
  }
  itemname=tmpstr;
  newitem=FALSE;
  return musics.GetCount()-ret;
}

int CChitemDlg::rescan_only_storeitems()
{
  int ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  tooltip_data refs;
  
  ret=0;
  if(items.IsEmpty())
  {
    scan_chitin();
    scan_override();
  }
  end_progress();
  
  log("Searching store items...");
  pos=items.GetStartPosition();
  while(pos)
  {
    items.GetNextAssoc(pos,key,fileloc);
    
    changeitemname(key);
    ret=read_next_item(fileloc);
    if(ret>=0)
    {
      if(the_item.header.itemtype==IT_BAG)
      {
        storeitems[key]=""; //validating store item
      }
    }
  }
  newitem=FALSE;
  log("Found %d containers.",storeitems.GetCount());
  log("Searching cure names...");
  pos=spells.GetStartPosition();
  while(pos)
  {
    spells.GetNextAssoc(pos,key,fileloc);

    if(store_spell_desc.Lookup(key, refs) )
    {
      changeitemname(key);
      ret=read_next_spell(fileloc);
      if(ret>=0)
      {
        refs.data[1]=the_spell.header.spellname;
      }
      else 
      {
        refs.data[1]=-1;
      }
      store_spell_desc.SetAt(key,refs);
    }
  }
  newitem=FALSE;
  log("Resolved cure names...");
  return ret;
}

int CChitemDlg::process_pros(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking projectiles...");
  pos=projects.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    projects.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_projectile(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_projectile();
      else ret=check_projectile();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_spells(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking spells...");
  pos=spells.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    spells.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_spell(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_spell();
      else ret=check_spell();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_chuis(int check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;

  log("Checking chuis...");
  pos=chuis.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    chuis.GetNextAssoc(pos,key,fileloc);
    if((check_or_search!=SCANNING) && !(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_chui(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_chui();
      else ret=check_chui();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int add_death_variable(char *varname); //in variables.cpp

int CChitemDlg::process_creatures(int check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  gret=0;
  if(check_or_search==SCANNING)
  {
    log("Gathering death variables...");
  }
  else
  {
    m_event.Empty();
    UpdateData(UD_DISPLAY);
    log("Checking creatures...");
  }
  pos=creatures.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    creatures.GetNextAssoc(pos,key,fileloc);
    if((check_or_search!=SCANNING) && !(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_creature(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      switch(check_or_search)
      {
      case CHECKING: ret=check_creature(); break;
      case MATCHING: ret=match_creature(); break;
      case SCANNING:
        add_death_variable(the_creature.header.dvar); break;
      }
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_effects(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking effects...");
  pos=effects.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    effects.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_effect(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_effect();
      else ret=check_effect();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_videocells(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking videocells...");
  pos=vvcs.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    vvcs.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_videocell(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_videocell();
      else ret=check_videocell();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_scripts(int check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  int count,max;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  switch(check_or_search)
  {
  case JOURNAL:
    journals.RemoveAll(false);
    log("Scanning journal entries...");
    break;
  case SCANNING:
    variables.RemoveAll(true);
    log("Scanning scripts...");
    break;
  case CHECKING:
    if(!(chkflg&NOVARCHK) && variables.IsEmpty())
    {
      MessageBox("Variable check disabled, rescan variables then enable it again.","Warning",MB_ICONEXCLAMATION|MB_OK);
      chkflg|=NOVARCHK;
    }
    log("Checking scripts...");
    break;
  case MATCHING:
    log("Matching scripts...");
    break;
  }
  pos=scripts.GetStartPosition();
  max=scripts.GetCount();
  start_progress(max,"Processing scripts..."); 

  count=0;
  while(pos)
  {
    ret=-1;
    set_progress(++count);
    
    scripts.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_script(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      switch(check_or_search)
      {
      case CHECKING:ret=check_script(CHECKING); break;
      case MATCHING:ret=match_script(); break;
      case SCANNING:ret=check_script(SCANNING); break;
      case JOURNAL:ret=check_script(JOURNAL); break;
      default:
        MessageBox("Internal Error","Error",MB_ICONSTOP|MB_OK);
        return -1;
      }
    }
    the_script.CloseScriptFile();
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_progress();
  log("Done.");
  return gret;
}

int CChitemDlg::process_stores(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  int max,count;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  storeitems.RemoveAll();
  rescan_only_storeitems(); // storeitems are gathered by itemcheck too
  
  log("Checking stores/containers...");
  
  //first scanning scripts, looking for cloned items
  if(chkflg&DOSCRIPTS)
  {
    pos=scripts.GetStartPosition();
    max=scripts.GetCount();
    start_progress(max,"Scanning scripts...");
//    if(m_progressdlg) m_progressdlg->SetRange(max,"Scanning scripts...");
    count=0;
    while(pos)
    {
      ret=-1;
      set_progress(++count);
      scripts.GetNextAssoc(pos,key,fileloc);
      if(!(chkflg&SKIPSOA)) //skipping SoA items
      {
        if(fileloc.bifname.Left(5)=="data\\")
        {
          continue;
        }
      }
      
      changeitemname(key);
      //checking items requires rereading scripts, but finding doesn't
      if(!check_or_search)
      {
        ret=read_next_script(fileloc);
        if(ret) gret=1;
        if(ret>=0) ret=check_scriptitems();
        the_script.CloseScriptFile();
      }
      newitem=FALSE;
      if(ret) gret=1;
    }
    end_progress();
  } 
  
  pos=stores.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    stores.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_store(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_store();
      else ret=check_store();
    }
    newitem=FALSE;
    if(ret) gret=1;
  } 
  end_panic();
  log("Done.");
  return gret;
}

//search : true
//check : false
int CChitemDlg::process_items(bool check_or_search)
{
  int dummy;
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking items...");
  //first looking into all chitin files
  pos=items.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    items.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    if(rnditems.Lookup(key,dummy) ) continue; //this is a random item

    changeitemname(key);
    ret=read_next_item(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_item();
      else ret=check_item();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_tables()
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking tables...");
  pos=darefs.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    darefs.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_table(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      ret=match_2da();      
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  the_2da.new_2da(); //freeing up area memory
  log("Done.");
  return gret;
}

int CChitemDlg::process_areas(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking areas...");
  pos=areas.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    areas.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_area(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_area();
      else ret=check_area();      
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  the_area.new_area(); //freeing up area memory
  log("Done.");
  return gret;
}

int CChitemDlg::process_dialogs(int check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  int max,count;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  switch(check_or_search)
  {
  case JOURNAL:
  case SCANNING:
    log("Scanning dialogs...");
    break;
  case CHECKING:
    if(!(chkflg&NOVARCHK) && variables.IsEmpty())
    {
      MessageBox("Variable check disabled, rescan variables then enable it again.","Warning",MB_ICONEXCLAMATION|MB_OK);
      chkflg|=NOVARCHK;
    }
    log("Checking dialogs...");
    break;
  case MATCHING:
    log("Matching dialogs...");
    break;
  }
  pos=dialogs.GetStartPosition();
  max=dialogs.GetCount();
  start_progress(max,"Processing dialogs..."); 
//  if(m_progressdlg) m_progressdlg->SetRange(max,"Processing dialogs...");
  count=0;
  while(pos)
  {
    ret=-1;
    set_progress(++count);
    dialogs.GetNextAssoc(pos,key,fileloc);
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_dialog(fileloc);
    if(ret) gret=1;
    if(ret>=0) //accept 1 too (hacked dialog)
    {
      switch(check_or_search)
      {
      case CHECKING: ret=check_dialog(CHECKING); break;
      case MATCHING: ret=match_dialog(); break;
      case SCANNING: ret=check_dialog(SCANNING); break;
      case JOURNAL: ret=check_dialog(JOURNAL); break;
      }
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_progress();
  the_dialog.new_dialog();
  log("Done.");
  return gret;
}

int CChitemDlg::process_bams(bool check_or_search)
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking bams...");
  pos=icons.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    icons.GetNextAssoc(pos,key,fileloc); //cannot skip original bams, there are too many
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_bam(fileloc,check_or_search);
    if(ret) gret=1;
    if(ret>=0)
    {
      if(check_or_search) ret=match_bam();
      else ret=check_bam();
      
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  the_bam.new_bam(); //freeing up bam memory
  log("Done.");
  return gret;
}

int CChitemDlg::process_games()
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking games...");
  pos=games.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    games.GetNextAssoc(pos,key,fileloc); //cannot skip original bams, there are too many
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_game(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      ret=check_game();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

int CChitemDlg::process_maps()
{
  int gret, ret;
  POSITION pos;
  CString key;
  loc_entry fileloc;
  
  m_event.Empty();
  UpdateData(UD_DISPLAY);
  gret=0;
  
  log("Checking worldmaps...");
  pos=wmaps.GetStartPosition();
  start_panic();
  while(pos && m_panicbutton)
  {
    ret=-1;
    wmaps.GetNextAssoc(pos,key,fileloc); //cannot skip original bams, there are too many
    if(!(chkflg&SKIPSOA)) //skipping SoA items
    {
      if(fileloc.bifname.Left(5)=="data\\")
      {
        continue;
      }
    }
    
    changeitemname(key);
    ret=read_next_map(fileloc);
    if(ret) gret=1;
    if(ret>=0)
    {
      ret=check_map();
    }
    newitem=FALSE;
    if(ret) gret=1;
  }
  end_panic();
  log("Done.");
  return gret;
}

void CChitemDlg::OnCheckItem() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_items(CHECKING)) //check
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Item check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Item check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Item check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckSpell() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_spells(CHECKING))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Spell check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Spell check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Spell check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckProjectile() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_pros(0))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Projectile check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Projectile check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Projectile check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckUi() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_chuis(false)) //check
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","User interface check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","User interface check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","User interface check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckStore() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_stores(false)) //check
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Store check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Store check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Store check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheck2da() 
{
  int ret;

  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  ret=check_statdesc();
  ret|=check_songlist();
  ret|=check_kits();
  //more checks

  newitem=FALSE;
  if(!ret)
  {
    MessageBox("No problem found!","2DA check",MB_OK|MB_ICONINFORMATION);
  }
}

void CChitemDlg::OnCheckCreature() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_creatures(0))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Creature check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Creature check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Creature check",MB_OK|MB_ICONINFORMATION);
}

//handling var.var
void CChitemDlg::OnCheckScript() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(!variables.GetCount())
  {
    switch(MessageBox("You have to scan variables first, do you want to do it now?","Warning",MB_ICONQUESTION|MB_YESNOCANCEL))
    {
    case IDCANCEL: return;
    case IDYES:
      OnScanvariables();
    }
  }

  if(process_scripts(0))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Script check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Script check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Script check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckVvc() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_videocells(false))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Video cell check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Video cell check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Video cell check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckArea() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_areas(false))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Area check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Area check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Area check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckDialog() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(!variables.GetCount())
  {
    switch(MessageBox("You have to scan variables first, do you want to do it now?","Warning",MB_ICONQUESTION|MB_YESNOCANCEL))
    {
    case IDCANCEL: return;
    case IDYES:
      OnScanvariables();
    }
  }

  if(process_dialogs(CHECKING))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Dialog check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Dialog check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Dialog check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckEffect() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_effects(CHECKING))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Effect check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Effect check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Effect check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckAnimation() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_bams(CHECKING))
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Bam check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Bam check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Bam check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckGame() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_games())
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Game check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Game check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Game check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnCheckWorldmap() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(process_maps())
  {
    switch(logtype)
    {
    case 0:
      MessageBox("There were inconsistencies, change the logging type to see them!","Worldmap check",MB_OK|MB_ICONINFORMATION);
      break;
    case 2:
      MessageBox("See the chitem.log for details on the inconsistencies!","Worldmap check",MB_OK|MB_ICONINFORMATION);
      break;
    }
    return;
  }
  MessageBox("No problem found!","Game check",MB_OK|MB_ICONINFORMATION);
}

void CChitemDlg::OnRescan() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  scan_chitin();
  scan_override();
  end_progress();
}

void CChitemDlg::OnRescan2() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  
  scan_2da();
  log("Reloaded game setup files...");
}

void CChitemDlg::OnRescan3() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  load_variables(m_hWnd, 1, 1, variables);
  log("Reloaded variables...");
}

void CChitemDlg::OnRescan4() 
{
  if(descpath.IsEmpty()) //reading opcodes if possible
  {
    MessageBox("Set the IEEP effect description file path first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(!read_effect_descs())
  {
    log("Reloaded effects...");
  }
}

void CChitemDlg::OnRescan5() 
{
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  
  scan_dialog();
  end_progress();
}

void CChitemDlg::OnCompat() 
{
  Ccompat comdialog;
  int oldopt;
  CString oldsetup;
  CString oldfolder;
  CString olddesc;
  
  oldopt=optflg;
  oldsetup=setupname;
  oldfolder=bgfolder;
  olddesc=descpath;
  if(comdialog.DoModal()==IDCANCEL)
  {
    optflg=oldopt;
    setupname=oldsetup;
    bgfolder=oldfolder;
    descpath=olddesc;
    theApp.read_game_preferences();
  }
  else
  {
    if(bgfolder.IsEmpty())
    {
      MessageBox("Setup isn't complete.");
      return;
    }
  	if(read_effect_descs())
    {
      MessageBox("There was an error while processing the effect descriptions.","Warning",MB_ICONWARNING|MB_OK);
    }
    scan_chitin();
    scan_override();
    scan_2da();
    scan_dialog();

    load_variables(m_hWnd, 0, 1, variables); //not verbose
    UpdateData(UD_DISPLAY);
    end_progress();
  }
  RefreshMenu();
}

void CChitemDlg::RefreshMenu()
{
  CString filename, tmpstr;
  CMenu *pMenu;
  int i;

  if(setupname.IsEmpty())
  {
    filename=VersionString();
  }
  else
  {
    filename.Format("%s - %s",VersionString(),setupname);
  }
  tmpstr.Format("%s   %d KBytes free",filename, getfreememory() );
  SetWindowText(tmpstr);
  
  pMenu=GetMenu();
  if(pMenu)
  {
    pMenu->ModifyMenu(ID_COMPAT, 0, ID_COMPAT, setupname);
    m_tooltip.Activate(!!tooltips); 
    pMenu->CheckMenuItem(ID_TOOLTIPS, MF_SET(tooltips) );
    
    pMenu->CheckMenuItem(ID_PROGRESS, MF_SET(do_progress));

    pMenu->CheckMenuItem(ID_READONLY, MF_SET(readonly));
        
    for(i=0;logmenu[i];i++)
    {
      pMenu->CheckMenuItem(logmenu[i], MF_SET(i==logtype));      
    }
  }
  //RefreshMenu is called after return from every editor, so it is a good function
  //to hijack for flushing tlk changes. We don't write tlk everytime,
  //because it is just too big
  if(global_changed)
  {
    write_file_progress(tlkfilename); //this one writes back the tlk file
  }
  if(global_changed)
  {
    MessageBox(tlkfilename+" wasn't saved, exit all other programs that might use it, and try again.","Warning",MB_ICONEXCLAMATION|MB_OK);
  }
}

BOOL CChitemDlg::DestroyWindow() 
{
  if(bifs) delete [] bifs;
  bifs=NULL;
  if(tlk_entries) delete [] tlk_entries;
  tlk_entries=NULL;
  return CDialog::DestroyWindow();
}

void CChitemDlg::OnContext() 
{
  PostMessage(WM_SYSCOMMAND,SC_CONTEXTHELP,0);    
}

void CChitemDlg::OnTooltips() 
{
  tooltips=!tooltips;
  RefreshMenu(); 
}

void CChitemDlg::OnProgress() 
{
  do_progress=!do_progress;
  RefreshMenu(); 
}

void CChitemDlg::OnReadonly() 
{
  readonly=!readonly;
  RefreshMenu(); 
}

void CChitemDlg::OnSavesettings() 
{
  theApp.save_settings();
}

void CChitemDlg::OnLoggingNone() 
{
  logtype=0;
  RefreshMenu();
}

void CChitemDlg::OnLoggingScreen() 
{
  logtype=1;
  RefreshMenu();
}

void CChitemDlg::OnLoggingFile() 
{
  logtype=2;
  RefreshMenu();
}

void CChitemDlg::OnFindstore() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0x8000cc;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find stores";
  dlg.mtype_title="Allowed item types";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_stores(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFinditem() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0xc080007f;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find items";
  dlg.mtype_title="Match item type";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_items(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindspell() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0xc080007f;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find spells";
  dlg.mtype_title="Match spelltype";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_spells(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindeff() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0xc00070;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find effects";
  dlg.mtype_title="";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_effects(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindcre() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0xc0fffffc;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find creatures";
  dlg.mtype_title="Match animation";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_creatures(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindProjectile() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0x40;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find projectiles";
  dlg.mtype_title="";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_pros(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindVvc() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0x40;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find video cells";
  dlg.mtype_title="";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_videocells(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindScript() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0x4000fc;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find scripts";
  dlg.mtype_title="Match trigger";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_scripts(MATCHING); //perform matches
  }
}


void CChitemDlg::OnSearchUi() 
{
  CFindItem dlg;
  int ret;

	dlg.mask=0x80004c;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find user interfaces";
  dlg.mtype_title="Match control";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_chuis(MATCHING); //perform matches
  }
}

void CChitemDlg::OnSearchBam() 
{
  CFindItem dlg;
  int ret;

	dlg.mask=0x3c;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find bams";
  dlg.mtype_title="Match cycle";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_bams(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindArea() 
{
  CFindItem dlg;
  int ret;
  
  dlg.mask=0xfc;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find areas";
  dlg.mtype_title="Match area type";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_areas(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFindDialog() 
{
  CFindItem dlg; //so far they are the same
  int ret;
  
  dlg.mask=0xc0007c;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find dialogs";
  dlg.mtype_title="Match trigger";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_dialogs(MATCHING); //perform matches
  }
}

void CChitemDlg::OnFind2da() 
{
  CFindItem dlg; //so far they are the same
  int ret;
  
  dlg.mask=0xc00000;
  dlg.flags=searchflags;
  dlg.searchdata=searchdata;
  dlg.title="Find tables";
  dlg.mtype_title="";
  ret=dlg.DoModal();
  if(ret==IDOK)
  {
    searchflags=dlg.flags;
    searchdata=dlg.searchdata;
    process_tables(); //perform matches
  }
}

// import .D (weidu format)

void CChitemDlg::OnFileImportd() 
{
  POSITION pos;
  Ctbg tbg; //no need of a global
  CString filepath, syscommand;
	int res;
  bool flawless;

  itemname="new d";
  flawless=true;
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  res=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER;  
  CFileDialog m_getfiledlg(TRUE, "d", makeitemname(".d",0), res, szFilterWeidu);
  HackForLargeList(m_getfiledlg);

restart:  
  if( m_getfiledlg.DoModal() == IDOK )
  {
    res=99;
    pos=m_getfiledlg.GetStartPosition();
    chdir(bgfolder);
    while(pos)
    {
      filepath=m_getfiledlg.GetNextPathName(pos);
      
      //this one writes back the tlk file so the import will be consistent
      syscommand=AssembleWeiduCommandLine(filepath,"override");
      res=my_system(syscommand);
      if(res) break;
    }
    if(res)
    {
      flawless=false;
      switch(res)
      {
      case 99:
        MessageBox("No files selected for import.","Warning",MB_ICONEXCLAMATION|MB_OK);
        goto restart;
        break;
      default:
        MessageBox("Some problem while importing file.","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      }
    }
  }
  rescan_dialog(true);
  scan_override();
  if(flawless)
  {
    log("Imports done without error.");
  }
  else
  {
    log("Imports done with error(s).");
  }
}

/// import TBG

static char BASED_CODE szFilter3[] = "Tbg files (*.tbg)|*.tbg|Iap files (*.iap)|*.iap|All files (*.*)|*.*||";

void CChitemDlg::OnImporttbg()
{
  Importtbg(0);
}

void CChitemDlg::Importtbg(int alt)
{
  POSITION pos;
  Ctbg tbg; //no need of a global
  CString filepath;
	int res;
  bool flawless;

  itemname="new tbg";
  flawless=true;
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }  
  res=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER;
  CFileDialog m_getfiledlg(TRUE, "tbg", makeitemname(".tbg",0), res, szFilter3);
  HackForLargeList(m_getfiledlg);

restart:  
  if( m_getfiledlg.DoModal() == IDOK )
  {
    res=99;
    pos=m_getfiledlg.GetStartPosition();
    while(pos)
    {
      filepath=m_getfiledlg.GetNextPathName(pos);
      
      if(alt)
      {
        if(!checkfile(filepath,"TBGC") )
        {
          res=-4;
          goto leave;
        }
      }
      
      res=tbg.Readtbg(filepath);
leave:
      if(res) break;
    }
    if(res)
    {
      flawless=false;
      switch(res)
      {
      case 99:
        MessageBox("No files selected for import.","Warning",MB_ICONEXCLAMATION|MB_OK);
        goto restart;
        break;
      case -6:
        MessageBox("The current IE engine doesn't support this feature.","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      case -5:
        MessageBox("DLTCEP doesn't support this feature.","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      case -4:
        MessageBox("Unknown filetype (not tbg3, tbg4, tbgn or iap)","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      case -3:
        MessageBox("Not enough memory.","Error",MB_ICONSTOP|MB_OK);
        break;
      case -2:
        MessageBox("Error while importing file.","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      case -1:
        MessageBox("Some problem while importing file.","Warning",MB_ICONEXCLAMATION|MB_OK);
        break;
      }
    }
  }
  scan_chitin();
  scan_override();
  RefreshMenu(); //updates .tlk
  end_progress();
  if(flawless)
  {
    log("Imports done without error.");
  }
  else
  {
    log("Imports done with error(s).");
  }
}

// create iap from tbg/custom files

void CChitemDlg::OnCreateIAP() 
{
  CIapDialog dlg;
  
  dlg.NewIAP();
  dlg.DoModal();
}

void CChitemDlg::OnReorderbif() 
{
  POSITION pos;
  CBif my_bif;
  CString filepath, cdpath, newpath;
  int idx;
  int res;
  
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  res=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER;
  CFileDialog m_getfiledlg(TRUE, "bif", bgfolder+"*.bif", res, szFilterBif);
  HackForLargeList(m_getfiledlg);
  
  if( m_getfiledlg.DoModal() != IDOK ) return;
  pos=m_getfiledlg.GetStartPosition();
  while(pos)
  {
    filepath=m_getfiledlg.GetNextPathName(pos);
    idx = filepath.ReverseFind('.');
    if (idx >= 0)
		  changeitemname(filepath.Left(idx));
	  else
      changeitemname(filepath);

    if(!checkfile(filepath, "BIFF"))
    {
      log("Not an uncompressed bif");
      continue;
    }
    
    res=my_bif.ReadBifHeader(filepath);
    switch(res)
    {
    case 0:
      log("This bif needs no fixup.");
      continue;
    case 1:
      break; //continue the flow of actions
    case -1:
      log("Compressed bifs are not supported");
      continue;
    case -2:
      log("Invalid or non-existent file");
      continue;
    case -3:
      log("Out of memory");
      continue;
    default:
      log("Unsupported or corrupt bif format");
      continue;
    }
    //continued flow of actions
    res=my_bif.WriteBifHeader(filepath+".tmp");
    if(!res)
    {
      res=my_bif.CopyData(filepath,filepath+".tmp");
    }
    if(res)
    {
      MessageBox("Reordering has failed","Bif reordering",MB_ICONSTOP|MB_OK);
      continue;
    }
    //finalizing the change
    newpath=filepath+".old";
    unlink(newpath);
    rename(filepath,newpath);
    rename(filepath+".tmp",filepath);
  }
}

void CChitemDlg::OnFileExtract() 
{
  CFileExtract dlg;
  
  dlg.extract_or_search=true;
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(!bifs)
  {
    MessageBox("No bifs, enable chitin.key scan!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  dlg.DoModal();
}

void CChitemDlg::OnFileSearch() 
{
  CFileExtract dlg;
  
  dlg.extract_or_search=false;
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  if(!bifs)
  {
    MessageBox("No bifs, enable chitin.key scan!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  dlg.DoModal();
}

void CChitemDlg::OnUncompressbif() 
{
  CString *paths;
  CString filepath, cdpath;
  int res;
  int i;
  
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  res=OFN_FILEMUSTEXIST|OFN_ENABLESIZING|OFN_EXPLORER;
  if(readonly) res|=OFN_READONLY;  
  CFileDialog m_getfiledlg(TRUE, "bif", bgfolder+"*.bif", res, szFilterBifc);

restart:  
  if( m_getfiledlg.DoModal() == IDOK )
  {
    filepath=m_getfiledlg.GetPathName();
    if(!checkfile(filepath, "BIFC"))
    {
      MessageBox("Not a compressed bif","Warning",MB_ICONWARNING|MB_OK);
      goto restart;
    }
    paths=explode(filepath,'\\',res);
    if(res<2)
    {
      MessageBox("The bif must be in its original folder","Warning",MB_ICONWARNING|MB_OK);
      if(paths) delete [] paths;
      return;
    }
    if(res>2)
    {
      cdpath.Empty();
      for(i=0;i<res-2;i++)
      {
        cdpath+=paths[i]+"\\";
      }
      filepath=paths[i]+"\\"+paths[i+1];
    }
    if(paths) delete [] paths;
    res=decompress_bif(filepath, cdpath);
    if(res) MessageBox("Decompression failed","Error",MB_ICONSTOP|MB_OK);
    else MessageBox("Decompression succeeed","Item checker",MB_ICONINFORMATION|MB_OK);
  }	
}

void CChitemDlg::OnUncompresssav() 
{
	CFileExtract3 dlg;
	
  dlg.cbf_or_sav=0;
  dlg.DoModal();
}

void CChitemDlg::OnUncompresscbf() 
{
	CFileExtract3 dlg;

  dlg.cbf_or_sav=1;
  dlg.DoModal();
  OnRescan(); //most likely there is a new .bif
}

void CChitemDlg::OnAddcfbtospells() 
{
  CCFBDialog dlg;

  dlg.SetMode(1);
  dlg.DoModal();
}

void CChitemDlg::OnClearcfbfromspells() 
{
  CCFBDialog dlg;

  dlg.SetMode(0);
  dlg.DoModal();
}

void CChitemDlg::OnScanjournal() 
{
  POSITION pos;
  int key, space;
  CString tmpstr, where;

  process_scripts(JOURNAL); //this will clear the variables too
  process_dialogs(JOURNAL);
  pos=journals.GetStartPosition();
  while(pos)
  {
    journals.GetNextAssoc(pos, key, where);
    if(!where.IsEmpty())
    {
      tmpstr=resolve_tlk_text(key);
      space=tmpstr.Find('\n');
      if(space>0) tmpstr=tmpstr.Left(space);
      if(tmpstr.GetLength()>30) tmpstr=tmpstr.Left(30)+"...";
      log("Journal entry %d (%s) is never removed, set in %s.", key,tmpstr, where);
    }
  }
  journals.RemoveAll();
}

void CChitemDlg::OnScanvariables() 
{
  POSITION pos;
  CString key;
  int count;

  process_scripts(SCANNING); //this will clear the variables too
  process_dialogs(SCANNING);
  process_creatures(SCANNING);
  pos=variables.GetStartPosition();
  while(pos)
  {
    variables.GetNextAssoc(pos, key, count);
    if(count<=1)
    {
      log("Variable %s is referenced only %d times.", key, count);
    }
  }
  if(MessageBox("Do you want to save the variables?","Variables",MB_ICONQUESTION|MB_YESNO)==IDYES)
  {
    save_variables(m_hWnd, variables);
  }
}

void CChitemDlg::OnEditItem() 
{
  CItemEdit dlg;

  dlg.NewItem();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditKey() 
{
	CKeyEdit dlg;
	
  dlg.DoModal();
  OnRescan();  //reload chitin & override
  OnRescan2();
}

void CChitemDlg::OnEditVvc() 
{
  CVVCEdit dlg;

  dlg.NewVVC();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditChui() 
{
  CChuiEdit dlg;

  dlg.NewChui();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditCreature() 
{
  CCreatureEdit dlg;

  dlg.NewCreature();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditEffect() 
{
  CEffEdit dlg;

  dlg.SetLimitedEffect(0);
  dlg.NewEff();
  dlg.SetDefaultDuration(0);
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditProjectile() 
{
  CProjEdit dlg;

  dlg.NewProjectile();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditSpell() 
{
  CSpellEdit dlg;

  dlg.NewSpell();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditStore() 
{
  CStoreEdit dlg;

  //this will refresh spell name strrefs and valid container items
  rescan_only_storeitems();
  dlg.NewStore();
  dlg.DoModal();
  RefreshMenu(); //readonly might have changed
}

void CChitemDlg::OnEditArea() 
{
  CAreaEdit dlg;

  dlg.NewArea();
  dlg.DoModal();
  the_area.new_area(); //freeing up area memory
  RefreshMenu();
}

void CChitemDlg::OnEditScript() 
{
  CScriptEdit dlg;

  dlg.NewScript();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditDialog() 
{
  CDialogEdit dlg;

  dlg.NewDialog();
  dlg.DoModal();
  the_dialog.new_dialog();
  RefreshMenu();
}

void CChitemDlg::OnEditAnimation() 
{
  CBamEdit dlg;

  dlg.NewBam();
  dlg.DoModal();
  the_bam.new_bam();
  RefreshMenu();
}

void CChitemDlg::OnEditGames() 
{
	CGameEdit dlg;
	
  dlg.NewGame();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditWorldmap() 
{
	CMapEdit dlg;
	
  dlg.NewMap();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditGraphics() 
{
	CMosEdit dlg;
	
  dlg.NewMos(false);
  dlg.DoModal();
  the_mos.new_mos();
  RefreshMenu();
}

void CChitemDlg::OnEditTileset() 
{
	CMosEdit dlg;
	
  dlg.NewMos(true);
  dlg.DoModal();
  the_mos.new_mos();
  RefreshMenu();
}

void CChitemDlg::OnEditSRC() 
{
	CSRCEdit dlg;
	
  dlg.NewSRC();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEdit2da() 
{
	C2DAEdit dlg;
	
  dlg.New2DA();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditIds() 
{
	CIDSEdit dlg;
	
  dlg.NewIDS();
  dlg.SetReadOnly(0);
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditMusiclist() 
{
	CMUSEdit dlg;
	
  dlg.NewMUS();
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnEditVariables() 
{
  Cvariable dlg;

  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_OK|MB_ICONSTOP);
    return;
  }
  dlg.DoModal();
}

void CChitemDlg::OnWavctowav() 
{
  DecompressAcm(true);
}

void CChitemDlg::OnWavctowav2() 
{
	DecompressAcm2(true);	
}

void CChitemDlg::OnAcmtowav() 
{
  DecompressAcm(false);
}

void CChitemDlg::OnAcmtowav2() 
{
  DecompressAcm2(false);
}

void CChitemDlg::DecompressAcm(bool wavc_or_acm)
{
  unsigned char *memory;
  loc_entry fileloc;
  int fhandle;
  int ret;
  long samples_written;

  if(wavc_or_acm) pickerdlg.m_restype=REF_WAV;
  else pickerdlg.m_restype=REF_ACM;
  if(pickerdlg.DoModal()==IDOK)
  {
    if(wavc_or_acm)  ret=sounds.Lookup(pickerdlg.m_picked,fileloc);
    else ret=musics.Lookup(pickerdlg.m_picked,fileloc);
    if(ret)
    {
      fhandle=locate_file(fileloc, 0);
      if(fhandle<1)
      {
        MessageBox("Can't open file.","Warning",MB_ICONEXCLAMATION|MB_OK);
        return;
      }
      ConvertAcmWav(fhandle,fileloc.size,memory,samples_written, wavc_or_acm?0:(editflg&FORCESTEREO));
      close(fhandle);
      if(memory)
      {
        write_wav(pickerdlg.m_picked, memory,samples_written,1);
        delete [] memory;
      }
      else
      {
        MessageBox("Decompression failed.","ACM decoder",MB_ICONSTOP|MB_OK);
        return;
      }
    }
    MessageBox(CString("Decompression done."),"ACM decoder",MB_ICONINFORMATION|MB_OK);
  }
}

int CountFiles(CFileDialog &filedlg)
{
  POSITION pos;
  int cnt;

  pos=filedlg.GetStartPosition();
  cnt=0;
  while(pos)
  {
    cnt++;
    filedlg.GetNextPathName(pos);
  }
  return cnt;
}

static char BASED_CODE szFilter1[] = "Wav files (*.wav)|*.wav|All files (*.*)|*.*||";
static char BASED_CODE szFilter2[] = "Acm files (*.acm)|*.acm|All files (*.*)|*.*||";

void CChitemDlg::DecompressAcm2(bool wavc_or_acm)
{
  unsigned char *memory;
  int fhandle;
  POSITION pos;
  CString filepath;
  CString folder;
  int res;
  long samples_written;
  
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }  
  res=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER;
  if(readonly) res|=OFN_READONLY;  
  CFileDialog m_getfiledlg(TRUE, wavc_or_acm?"wav":"acm", wavc_or_acm?makeitemname(".wav",-1):makeitemname(".acm",-1), res, wavc_or_acm?szFilter1:szFilter2); 
  HackForLargeList(m_getfiledlg);

  if( m_getfiledlg.DoModal() == IDOK )
  {
    pos=m_getfiledlg.GetStartPosition();
    while(pos)
    {
      filepath=m_getfiledlg.GetNextPathName(pos);
      fhandle=open(filepath,O_RDONLY|O_BINARY);
      if(fhandle<1)
      {
        MessageBox("Can't open file.","Warning",MB_ICONEXCLAMATION|MB_OK);
        continue;
      }
      itemname=getitemname(filepath);
      ConvertAcmWav(fhandle,-1,memory,samples_written, wavc_or_acm?0:editflg&FORCESTEREO);
      close(fhandle);
      if(memory)
      {
        write_wav(itemname, memory,samples_written,1);
        delete [] memory;
      }
      else MessageBox("Decompression failed.","ACM decoder",MB_ICONSTOP|MB_OK);
    }
    MessageBox(CString("Decompression done."),"ACM decoder",MB_ICONINFORMATION|MB_OK);
  }	
}

void CChitemDlg::OnWavtowavc() 
{
	CompressWav(true);
}

void CChitemDlg::OnWavtoacm() 
{
  CompressWav(false);
}

//compress plain wav to wavc or acm
void CChitemDlg::CompressWav(bool wavc_or_acm)
{
  int fhandle;
  FILE *foutp;
  POSITION pos;
  CString filepath;
  CString folder;
  int res, cnt;
  folderbrowse_t fb;
  
  if(bgfolder.IsEmpty())
  {
    MessageBox("Use the setup first!","Warning",MB_ICONEXCLAMATION|MB_OK);
    return;
  }
  res=OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_EXPLORER;
  if(readonly) res|=OFN_READONLY;  
  CFileDialog m_getfiledlg(TRUE, "wav", makeitemname(".wav",0), res, szFilter1);
  HackForLargeList(m_getfiledlg);
  
  if( m_getfiledlg.DoModal() == IDOK )
  {
    pos=m_getfiledlg.GetStartPosition();
    cnt=CountFiles(m_getfiledlg);
    if(!cnt) return;
    if(wavc_or_acm) fb.initial=bgfolder+"override";
    else fb.initial=bgfolder+"music";

    fb.title="Select output folder for the compressed sounds";
    if(BrowseForFolder(&fb,m_hWnd)!=IDOK) return;
    start_progress(cnt,"Compressing sounds...");
    cnt=0;
    while(pos)
    {
      filepath=m_getfiledlg.GetNextPathName(pos);
      
      if(!checkfile(filepath, "RIFF"))
      {
        MessageBox(CString("Not an uncompressed sound file:")+filepath,"Warning",MB_ICONEXCLAMATION|MB_OK);
        continue;
      }
      itemname=getitemname(filepath);
      if(wavc_or_acm)
      {
        folder=fb.initial+"\\"+itemname+".wavc";
      }
      else
      {
        folder=itemname.Left(4);
        if(folder.Left(3)=="SPC") folder.Empty();
        else folder+="\\";
        folder=fb.initial+"\\"+folder;
        mkdir(folder);
        folder=folder+itemname+".acm";
      }
      unlink(folder);
      foutp=fopen(folder,"wb");
      if(foutp)
      {
        fhandle=open(filepath,O_RDONLY|O_BINARY);
        if(fhandle<1)
        {
          MessageBox("Can't open file.","Warning",MB_ICONEXCLAMATION|MB_OK);
          continue;
        }
        res=ConvertWavAcm(fhandle,-1,foutp, wavc_or_acm);
        fclose(foutp);
      }
      else res=-1;
      close(fhandle);
      if(res) MessageBox(CString("Compression failed:")+filepath,"ACM encoder",MB_ICONSTOP|MB_OK);
      else
      {
        if(wavc_or_acm)
        {
          filepath=fb.initial+"\\"+itemname+".wav";
          rename(filepath,filepath+".bak");
          unlink(filepath);
          rename(folder,filepath);
        }
      }
      set_progress(++cnt);
    }
    end_progress();
    MessageBox(CString("Compression done."),"ACM encoder",MB_ICONINFORMATION|MB_OK);
  }	
}

///////////////// read next <resource> /////////////////////
int CChitemDlg::read_next_item(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_item.ReadItemFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    if(chkflg&NOSTRUCT) break;
    log("Out of memory while reading item.");
    break;
  case -2:
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up item.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Invalid item or length is zero.");
    break;
  case 1:
    if(chkflg&NOSTRUCT) break;
    log("Crippled item: (length doesn't match structure)");
    break;
  case 2:
    if(chkflg&NOSTRUCT) break;
    log("Crippled item: (feature and extended headers are not in order)");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_creature(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_creature.ReadCreatureFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -4:
    if(chkflg&NOSTRUCT) break;
    log("Incompatible creature file (effects)");
    break;
  case -3:
    if(chkflg&NOSTRUCT) break;
    log("Out of memory while reading creature.");
    break;
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up creature");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Invalid creature or length is zero.");
    break;
  case 1:
    if(chkflg&NOSTRUCT) break;
    log("Incorrect file size.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_chui(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_chui.ReadChuiFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    if(chkflg&NOSTRUCT) break;
    log("Out of memory while reading chui.");
    break;
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up chui.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Invalid chui or length is zero.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_projectile(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_projectile.ReadProjectileFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    if(chkflg&NOSTRUCT) break;
    log("Crippled projectile");
    break;
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up projectile");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Invalid projectile or length is zero.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_effect(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_effect.ReadEffectFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up effect");
    break;
  case 0:
    break;
  }
  return ret;
}

int CChitemDlg::read_next_videocell(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_videocell.ReadVVCFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -2:
    if(chkflg&NOSTRUCT) break;
    log("Invalid videocell or length is zero.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up videocell.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_table(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_2da.Read2DAFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -2:
    if(chkflg&NOSTRUCT) break;
    log("Invalid table or length is zero.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up table.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_spell(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_spell.ReadSpellFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    if(chkflg&NOSTRUCT) break;
    log("Out of memory while reading spell.");
    break;
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Invalid spell or length is zero.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up spell.");
    break;
  case 0:
    break;
  case 1:
    if(chkflg&(NOSTRUCT|WARNINGS)) break;
    log("Incorrect file size.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_store(loc_entry fileloc)
{
  loc_entry dummy;
  int ret;
  int fhandle;
  CString key, tmp;
  char tmpstr[9];
  int i;
  int count;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_store.ReadStoreFromFile(fhandle,fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    if(chkflg&(NOSTRUCT|WARNINGS)) break;
    log("Incorrect file size.");
    break;
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up store.");
    break;
  case 0:
    for(i=0;i<the_store.entrynum;i++)
    {
      memcpy(tmpstr,the_store.entries[i].itemname,8);
      tmpstr[8]=0;
      key=tmpstr;
      key.MakeUpper();
      if(the_store.entries[i].infinite)
      {
        count=99;
      }
      else count=the_store.entries[i].count;
      if(!count)
      {
        log("The stock is 0 for %s.",key);
        continue;
      }
      if(!items.Lookup(key, dummy) )
      {
        log("Store has invalid item %s.",key);
        continue;
      }
      if(storeitems.Lookup(key, tmp) )
      {
        if(count!=1)
        {
          log("The stock is not exactly 1 for a container (%s).",key);
        }
        if(!tmp.IsEmpty())
        {
          log("The item %s was already stocked at %s",key,tmp);
          ret|=1;
        }
        storeitems[key]=itemname+".sto";
      }
    }
  }
  return ret;
}

int CChitemDlg::read_next_script(loc_entry fileloc)
{
  int fhandle;
  int ret;
  int line;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_script.ReadScriptFile(fhandle, fileloc.size);
  line=the_script.ErrLine();
  switch(ret)
  {
  case -4:
    if(chkflg&NOSTRUCT) break;
    log("Incorrect filesize.");
    break;
  case -3:
    log("Out of memory at line: %d",line);
    break;
  case -2:
    log("Internal error at line: %d",line);
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("File structure error at line: %d (%s)",line, the_script.GetErrLine());
    break;
  }
  close(fhandle);
  return ret;
}

int CChitemDlg::read_next_dialog(loc_entry fileloc)
{
  int fhandle;
  int ret;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_dialog.ReadDialogFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -3:
    log("Out of memory");
    break;
  case -2:
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up dialog.");
    break;
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("File structure error.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_area(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  loc_entry wedfileloc;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;  
  ret=the_area.ReadAreaFromFile(fhandle, fileloc.size);
  close(fhandle);
  if(ret>=0)
  {
    RetrieveResref(tmp,the_area.header.wed);
    if(weds.Lookup(tmp,wedfileloc))
    {
      fhandle=locate_file(wedfileloc, 0);
      if(fhandle<1)
      {
        ret=3; //wedfile not available
      }
      else
      {
        switch(the_area.ReadWedFromFile(fhandle, wedfileloc.size) )
        {
        case 0: case 1: case 2: break;
        default:
          ret=3;
        }
        close(fhandle);
      }
    }
    else ret=3;
  }
  switch(ret)
  {
  case -2: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up area.");
    break;
  case 0:
    break;
  case 1:
    if(chkflg&(NOSTRUCT|WARNINGS) ) break;
    log("Object is reordered.");
    break;
  case 2:
    if(chkflg&NOSTRUCT) break;
    log("Object is crippled.");
    break;
  case 3:
    if(chkflg&NOSTRUCT) break;
    log("Wedfile is not available.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_bam(loc_entry fileloc, bool onlyheader)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_bam.ReadBamFromFile(fhandle, fileloc.size,onlyheader);
  close(fhandle);
  switch(ret)
  {
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Bam file is inconsistent.");
    break;
  case 0:
    break;
  default: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up bam.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_game(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_game.ReadGameFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Game file is inconsistent.");
    break;
  case 0:
    break;
  default: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up save game.");
    break;
  }
  return ret;
}

int CChitemDlg::read_next_map(loc_entry fileloc)
{
  int ret;
  int fhandle;
  CString key, tmp;
  
  fhandle=locate_file(fileloc, 0);
  if(fhandle<1) return -2;
  ret=the_map.ReadMapFromFile(fhandle, fileloc.size);
  close(fhandle);
  switch(ret)
  {
  case -1:
    if(chkflg&NOSTRUCT) break;
    log("Worldmap is inconsistent.");
    break;
  case 0:
    break;
  default: //serious error
    if(chkflg&NOSTRUCT) break;
    log("Serious error while looking up worldmap.");
    break;
  }
  return ret;
}

void CChitemDlg::OnLookupstrref() 
{
	CStrRefDlg dlg;
	
  dlg.DoModal();
  RefreshMenu();
}

void CChitemDlg::OnCancel() 
{
  if(MessageBox("Are you sure?","Exit from DLTC Editor Pro",MB_YESNO|MB_ICONQUESTION)==IDYES)
  {
    CDialog::OnCancel();
  }
}
