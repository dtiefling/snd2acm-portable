// TormentCre.cpp : implementation file
//

#include "stdafx.h"
#include "chitem.h"
#include "TormentCre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTormentCre dialog

CTormentCre::CTormentCre(CWnd* pParent /*=NULL*/)
	: CDialog(CTormentCre::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTormentCre)
	//}}AFX_DATA_INIT
}

void CTormentCre::DoDataExchange(CDataExchange* pDX)
{
  CString tmpstr;
  int value;
  int i;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTormentCre)
	//}}AFX_DATA_MAP
  DDX_Text(pDX, IDC_DIALOG, the_creature.pstheader.dialogradius);
  DDX_Text(pDX, IDC_FEETCIRCLE, the_creature.pstheader.feetcircle);
  RetrieveVariable(m_beast, the_creature.pstheader.bestiary);  
	DDX_CBString(pDX, IDC_DEATH, m_beast);
	DDV_MaxChars(pDX, m_beast, 32);
  StoreVariable(m_beast, the_creature.pstheader.bestiary);

  DDX_Text(pDX, IDC_COLOR, the_creature.pstheader.colornum);
  DDV_MinMaxInt(pDX, the_creature.pstheader.colornum, 0,6);

  tmpstr.Format("0x%x %s",the_creature.pstheader.idsspecies,IDSToken("RACE",the_creature.pstheader.idsspecies) );
  DDX_Text(pDX, IDC_IDSSPECIES, tmpstr);
  value=IDSKey("RACE", tmpstr);
  if(value==-1)
  {
    the_creature.pstheader.idsspecies=(BYTE) strtonum(tmpstr);
  }
  else
  {
    the_creature.pstheader.idsspecies=(BYTE) value;
  }
  if(!the_creature.pstheader.idsspecies) the_creature.pstheader.idsspecies=the_creature.header.idsrace;

  for(i=0;i<7;i++)
  {
    tmpstr=colortitle(the_creature.pstheader.colours[i]);
    DDX_Text(pDX, IDC_CMETAL+i, tmpstr);
    the_creature.pstheader.colours[i]=(BYTE) strtonum(tmpstr);

    tmpstr.Format("0x%x",the_creature.pstheader.colorslots[i]);
    DDX_Text(pDX, IDC_ATTR1+i, tmpstr);
    the_creature.pstheader.colorslots[i]=(unsigned char) strtonum(tmpstr);
  }
}

BEGIN_MESSAGE_MAP(CTormentCre, CDialog)
	//{{AFX_MSG_MAP(CTormentCre)
	ON_EN_KILLFOCUS(IDC_DIALOG, OnDefaultKillfocus)
	ON_BN_CLICKED(IDC_BROWSE1, OnBrowse1)
	ON_BN_CLICKED(IDC_BROWSE2, OnBrowse2)
	ON_BN_CLICKED(IDC_BROWSE3, OnBrowse3)
	ON_BN_CLICKED(IDC_BROWSE4, OnBrowse4)
	ON_BN_CLICKED(IDC_BROWSE5, OnBrowse5)
	ON_BN_CLICKED(IDC_BROWSE6, OnBrowse6)
	ON_BN_CLICKED(IDC_BROWSE7, OnBrowse7)
	ON_EN_KILLFOCUS(IDC_FEETCIRCLE, OnDefaultKillfocus)
	ON_CBN_KILLFOCUS(IDC_IDSSPECIES, OnDefaultKillfocus)
	ON_CBN_KILLFOCUS(IDC_DEATH, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CHAIR, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CMINOR, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CMAJOR, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CLEATHER, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CMETAL, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CARMOR, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_CSKIN, OnDefaultKillfocus)
	ON_EN_KILLFOCUS(IDC_COLOR, OnDefaultKillfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTormentCre message handlers

BOOL CTormentCre::OnInitDialog() 
{
  POSITION pos;
  CComboBox *cb;

	CDialog::OnInitDialog();

	cb=(CComboBox *) GetDlgItem(IDC_DEATH);
  pos=beasts.GetHeadPosition();
  while(pos)
  {
    cb->AddString(beasts.GetNext(pos));
  }

	cb=(CComboBox *) GetDlgItem(IDC_IDSSPECIES);
  FillCombo("RACE",cb,2);

  UpdateData(UD_DISPLAY);
	return TRUE;
}

void CTormentCre::OnDefaultKillfocus() 
{
	UpdateData(UD_RETRIEVE);
	UpdateData(UD_DISPLAY);
}

void CTormentCre::ColorDlg(int idx)
{
  colordlg.m_picked=the_creature.pstheader.colours[idx];
  if(colordlg.DoModal()==IDOK)
  {
    the_creature.pstheader.colours[idx]=(unsigned char) colordlg.m_picked;
    UpdateData(UD_DISPLAY);
  }
}

void CTormentCre::OnBrowse1() 
{
	ColorDlg(0);
}

void CTormentCre::OnBrowse2() 
{
	ColorDlg(1);
}

void CTormentCre::OnBrowse3() 
{
	ColorDlg(2);
}

void CTormentCre::OnBrowse4() 
{
	ColorDlg(3);
}

void CTormentCre::OnBrowse5() 
{
	ColorDlg(4);
}

void CTormentCre::OnBrowse6() 
{
	ColorDlg(5);
}

void CTormentCre::OnBrowse7() 
{
	ColorDlg(6);
}