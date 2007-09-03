/**
 *	wxQuickRun
 *	Copyright © 2006-2007, Priyank Bolia.
 *
 *	Contact: http://priyank.co.in
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public
 *	License as published by the Free Software Foundation; either
 *	version 2 of the License, or (at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public
 *	License along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	See gpl.txt for more information regarding the GNU General Public License.
 *
 * 
 *	\file OptionsPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 3 Jul, 2006
 **/

#include "OptionsPanel.h"
#include "ClipBoardManager.h"
#include "SearchEngineDlg.h"
#include "KeysAssignDlg.h"
#include "wxQuickRun.h"
#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <wx/stdpaths.h>

#ifdef  __WXMSW__
	#include <wx/msw/registry.h>
#endif

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

#define WXQUICKRUN_VERSION wxT("0.95")

BEGIN_EVENT_TABLE(COptionsPanel, wxPanel)
	//EVT_BUTTON(wxID_BUTTON_FONT, COptionsPanel::OnFontButton)
	//EVT_BUTTON(wxID_BUTTON_BACK_COLOR, COptionsPanel::OnBackColorButton)
	EVT_BUTTON(wxID_BUTTON_SEARCH_ENGINE, COptionsPanel::OnSearchEngineButton)
	EVT_BUTTON(wxID_BUTTON_KEYS_ASSIGN, COptionsPanel::OnKeysAssignmentButton)
	EVT_BUTTON(wxID_OK, COptionsPanel::OnApplyButton)
	EVT_BUTTON(wxID_BUTTON_CHECK_LATEST_VER, COptionsPanel::OnCheckForLatestVersion)
	EVT_BUTTON(wxID_BUTTON_DONATE, COptionsPanel::OnDonate)
	EVT_BUTTON(wxID_BUTTON_SELECT_LANG, COptionsPanel::OnSelectLanguage)
	EVT_DOWNLOAD(COptionsPanel::OnDownloadEvent)
END_EVENT_TABLE()

COptionsPanel::COptionsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
//, m_pStaticFont(NULL)
//, m_pStaticFontName(NULL)
, m_pStaticSelectLang(NULL)
, m_pStaticSelectedLang(NULL)
, m_pButtonSelectLang(NULL)
//, m_pButtonFont(NULL)
//, m_pTimeFormat(NULL)
//, m_pComboTimeFormat(NULL)
, m_pStaticBackColor(NULL)
, m_pColorBoxBackColor(NULL)
, m_pButtonBackColor(NULL)
, m_pStaticTransparency(NULL)
, m_pSpinCtrlTransparency(NULL)
, m_pButtonApply(NULL)
, m_pButtonCancel(NULL)
, m_pCheckBoxAutoStart(NULL)
, m_pCheckBoxVirtualClipboard(NULL)
, m_pButtonCheckLatestVer(NULL)
, m_pDownloadFile(NULL)
, m_pStaticClipboardIndex(NULL)
, m_pComboClipboardIndex(NULL)
, m_pButtonSearchEngine(NULL)
, m_pButtonKeysAssign(NULL)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
}

COptionsPanel::~COptionsPanel(void)
{
	if(m_pDownloadFile)
		m_pDownloadFile->CancelDownload();
}

void COptionsPanel::CreateGUIControls()
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pStaticSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* pTextSizer = new wxBoxSizer(wxVERTICAL);

	//wxBoxSizer *pFontSizer = new wxBoxSizer(wxHORIZONTAL);
	//m_pStaticFont = new wxStaticText(this, wxID_STATIC_TEXT_FONT, wxT("&Font:"));
	//m_pButtonFont = new wxButton(this, wxID_BUTTON_FONT, wxT("..."));
	//m_pStaticFontName = new wxStaticText(this, wxID_STATIC_TEXT_FONT_NAME, wxT("Times New Roman"));
	//pStaticSizer->Add(m_pStaticFont, 1, wxALL | wxEXPAND, 5);
	//pFontSizer->Add(m_pStaticFontName, 1, wxALL | wxEXPAND, 5);
	//pFontSizer->Add(m_pButtonFont, 0, wxALL | wxEXPAND, 5);

	//wxBoxSizer *pTimeSizer = new wxBoxSizer(wxHORIZONTAL);
	//m_pTimeFormat = new wxStaticText(this, wxID_STATIC_TEXT_TIME_FORMAT, wxT("&Time Format:"));
	//m_pComboTimeFormat = new wxComboBox(this, wxID_COMBOBOX_TIME_FORMAT, wxT(""), wxDefaultPosition, wxDefaultSize, wxArrayString(), wxCB_READONLY);
	//pStaticSizer->Add(m_pTimeFormat, 1, wxALL | wxEXPAND, 5);
	//pTimeSizer->Add(m_pComboTimeFormat, 1, wxALL | wxEXPAND, 5);

	//wxBoxSizer *pBackColorSizer = new wxBoxSizer(wxHORIZONTAL);
	//m_pStaticBackColor = new wxStaticText(this, wxID_STATIC_TEXT_BACK_COLOR, wxT("&Background Color:"));
	//m_pButtonBackColor = new wxButton(this, wxID_BUTTON_BACK_COLOR, wxT("..."));
	//m_pColorBoxBackColor = new wxColorBox(this, wxID_COLOR_BOX_BACK_COLOR);
	//pStaticSizer->Add(m_pStaticBackColor, 1, wxALL | wxEXPAND, 5);
	//pBackColorSizer->Add(m_pColorBoxBackColor, 1, wxALL | wxEXPAND, 5);
	//pBackColorSizer->Add(m_pButtonBackColor, 0, wxALL | wxEXPAND, 5);

	//wxBoxSizer *pTransparencySizer = new wxBoxSizer(wxHORIZONTAL);
	//m_pStaticTransparency = new wxStaticText(this, wxID_STATIC_TEXT_TRANSPARENCY, wxT("T&ransparency:"));
	//m_pSpinCtrlTransparency = new wxSpinCtrl(this, wxID_SPINCTRL_TRANSPARENCY, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP);
	//pStaticSizer->Add(m_pStaticTransparency, 1, wxALL | wxEXPAND, 5);
	//pTransparencySizer->Add(m_pSpinCtrlTransparency, 1, wxALL | wxEXPAND, 5);

	wxArrayString arrayIndex;
	for (int i=1; i<=10; i++)
	{
		arrayIndex.Add(wxString::Format(wxT("%d"), i));
	}
	m_pStaticClipboardIndex = new wxStaticText(this, wxID_STATIC_TEXT_CLIPBOARD_INDEX, wxT("Virtual Clipboard &Index:"));
	m_pComboClipboardIndex = new wxComboBox(this, wxID_COMBOBOX_CLIPBOARD_INDEX, arrayIndex.Item(0), wxDefaultPosition, wxDefaultSize, arrayIndex, wxCB_READONLY);
	pStaticSizer->Add(m_pStaticClipboardIndex, 1, wxALL | wxEXPAND, 5);
	pTextSizer->Add(m_pComboClipboardIndex, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer *pLangSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pStaticSelectLang = new wxStaticText(this, wxID_STATIC_TEXT_SELECT_LANG, wxT("&Language:"));
	m_pStaticSelectedLang = new wxStaticText(this, wxID_STATIC_TEXT_SELECTED_LANG, wxGetApp().GetSelectedLanguage());
	m_pButtonSelectLang = new wxButton(this, wxID_BUTTON_SELECT_LANG, wxT("Change &Language"));
	pStaticSizer->Add(m_pStaticSelectLang, 1, wxALL | wxEXPAND, 5);
	pLangSizer->Add(m_pStaticSelectedLang, 1, wxALL | wxEXPAND, 5);
	pLangSizer->Add(m_pButtonSelectLang, 1, wxALL | wxEXPAND, 5);
	pTextSizer->Add(pLangSizer, 1, wxALL | wxEXPAND, 0);

	wxBoxSizer* pControlSizer = new wxBoxSizer(wxHORIZONTAL);
	pControlSizer->Add(pStaticSizer, 0, wxALL | wxEXPAND, 0);
	pControlSizer->Add(pTextSizer, 1, wxALL | wxEXPAND, 0);
	
	wxBoxSizer* pManageOptionsSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSearchEngine = new wxButton(this, wxID_BUTTON_SEARCH_ENGINE, wxT("&Manage Search Engines"));
	m_pButtonKeysAssign = new wxButton(this, wxID_BUTTON_KEYS_ASSIGN, wxT("Hot&Keys Assignment"));
	pManageOptionsSizer->Add(m_pButtonSearchEngine, 1, wxRIGHT | wxEXPAND, 5);
	pManageOptionsSizer->Add(m_pButtonKeysAssign, 1, wxLEFT | wxEXPAND, 5);

	m_pCheckBoxVirtualClipboard = new wxCheckBox(this, wxID_CHECKBOX_VIRTUAL_CLIPBOARD, wxT("&Enable virtual clipboard."));
	m_pCheckBoxAutoStart = new wxCheckBox(this, wxID_CHECKBOX_AUTO_START, wxT("Auto &start with system logon."));

	wxBoxSizer* pWebButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonCheckLatestVer = new wxButton(this, wxID_BUTTON_CHECK_LATEST_VER, wxT("Check Latest &Version"));
	m_pButtonDonate = new wxButton(this, wxID_BUTTON_DONATE, wxT("&Donate Online"));
	pWebButtonsSizer->Add(m_pButtonCheckLatestVer, 1, wxRIGHT | wxEXPAND, 5);
	pWebButtonsSizer->Add(m_pButtonDonate, 1, wxLEFT | wxEXPAND, 5);

	wxStaticBoxSizer *pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Options:"));
	pStaticBoxSizer->Add(pControlSizer, 0, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(m_pCheckBoxVirtualClipboard, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 10);
	pStaticBoxSizer->Add(m_pCheckBoxAutoStart, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 10);
	pStaticBoxSizer->Add(pManageOptionsSizer, 0, wxALL | wxEXPAND, 10);
	pStaticBoxSizer->Add(pWebButtonsSizer, 0, wxALL | wxEXPAND, 10);
	pMainSizer->Add(pStaticBoxSizer, 1, wxALL | wxEXPAND, 10);


	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	m_pButtonApply = new wxButton(this, wxID_OK, wxT("&Apply"));
	m_pButtonCancel = new wxButton(this, wxID_CANCEL, wxT("&Close"));
	pButtonSizer->Add(m_pButtonApply, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonCancel, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 5);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(pButtonSizer, 0, wxALL | wxEXPAND, 0);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();


	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("settings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(32), value VARCHAR(32));"));
	}
	else
	{
		//wxString strFaceName = wxT("Times New Roman");
		//wxFontWeight fontWeight = wxFONTWEIGHT_NORMAL;
		//int fontStyle = wxFONTSTYLE_NORMAL;
		//int nPointSize = 12;
		//wxColour fontColor = *wxBLACK;
		//wxColour backColor = *wxWHITE;
		//int nModifier = wxMOD_CONTROL;
		//int nKeyCode = VK_OEM_1;
		wxString sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'AutoStart';"));
		{
			wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				if(result.GetString(0) == wxT("true"))
					m_pCheckBoxAutoStart->SetValue(true);
				else
					m_pCheckBoxAutoStart->SetValue(false);
			}
			result.Finalize();
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'VirtualClipboard';"));
			wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				if(result.GetString(0) == wxT("true"))
					m_pCheckBoxVirtualClipboard->SetValue(true);
				else
					m_pCheckBoxVirtualClipboard->SetValue(false);
			}
			result.Finalize();
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'ClipboardIndex';"));
			wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				m_pComboClipboardIndex->SetValue(result.GetString(0));
			result.Finalize();
		}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'FaceName';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		strFaceName = result.GetString(0);
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'FontWeight';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		fontWeight = (wxFontWeight)wxAtoi(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'fontStyle';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		fontStyle = wxAtoi(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'fontColor';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		fontColor = wxAtol(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'backColor';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		backColor = wxAtol(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'PointSize';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		nPointSize = wxAtoi(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'KeyCode';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		nKeyCode = wxAtoi(result.GetString(0));
		//}
		//{
		//	sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'Modifier';"));
		//	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		//	if(result.NextRow())
		//		nModifier = wxAtoi(result.GetString(0));
		//}
		//if(m_pStaticFontName)
		//{
		//	wxFont font = m_pStaticFontName->GetFont();
		//	font.SetFaceName(strFaceName);
		//	font.SetWeight(fontWeight);
		//	font.SetStyle(fontStyle);
		//	font.SetPointSize(nPointSize);
		//	m_FontData.SetChosenFont(font);
		//	m_FontData.SetColour(fontColor);
		//	m_pStaticFontName->SetLabel(strFaceName);
		//	m_pStaticFontName->SetFont(m_FontData.GetChosenFont());
		//	m_pStaticFontName->SetForegroundColour(m_FontData.GetColour());
		//	m_pColorBoxBackColor->SetBoxColor(backColor);
		//}
		//m_pTextCtrlHotKey->SetValue(wxString::Format(wxT("%c"), GetCharFromKeyCode(nKeyCode)));
	}
}

//void COptionsPanel::OnFontButton(wxCommandEvent &event)
//{
//	wxFontData data;
//	data.SetInitialFont(m_FontData.GetChosenFont());
//	data.SetColour(m_FontData.GetColour());
//	wxFontDialog fontDlg(this, data);
//	if(fontDlg.ShowModal()==wxID_OK)
//	{
//		m_FontData = fontDlg.GetFontData();
//		m_pStaticFontName->SetLabel(m_FontData.GetChosenFont().GetFaceName());
//		m_pStaticFontName->SetFont(m_FontData.GetChosenFont());
//		m_pStaticFontName->SetForegroundColour(m_FontData.GetColour());
//	}
//	event.Skip(false);
//}
//
//void COptionsPanel::OnBackColorButton(wxCommandEvent &event)
//{
//	wxColourDialog colorDlg(this, &m_ColorData); 
//	if (colorDlg.ShowModal()==wxID_OK)
//	{
//		m_ColorData = colorDlg.GetColourData();
//		m_pColorBoxBackColor->SetBoxColor(m_ColorData.GetColour());
//	}
//	event.Skip(false);
//}

void COptionsPanel::OnApplyButton(wxCommandEvent &event)
{
	if (m_pCheckBoxAutoStart->GetValue())
	{
#ifdef  __WXMSW__
		wxRegKey *pRegKey = new wxRegKey(wxT("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));
		//will create the Key if it does not exist
		if( !pRegKey->Exists() )
			pRegKey->Create();
		pRegKey->SetValue(wxT("wxQuickRun"), wxStandardPaths().GetExecutablePath());
		delete pRegKey;
#endif
	}
	else
	{
#ifdef  __WXMSW__
		wxRegKey *pRegKey = new wxRegKey(wxT("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"));
		//will create the Key if it does not exist
		if( pRegKey->Exists() && pRegKey->HasValue(wxT("wxQuickRun")) )
			pRegKey->DeleteValue(wxT("wxQuickRun"));
		delete pRegKey;
#endif
	}
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("settings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(32), value VARCHAR(32));"));
	}
	wxString sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'AutoStart';"));
	dbConn->ExecuteUpdate(sqlCmd);
	if (m_pCheckBoxAutoStart->GetValue())
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('AutoStart', 'true');"));
	else
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('AutoStart', 'false');"));
	dbConn->ExecuteUpdate(sqlCmd);

	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'VirtualClipboard';"));
	dbConn->ExecuteUpdate(sqlCmd);
	if (m_pCheckBoxVirtualClipboard->GetValue())
	{
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('VirtualClipboard', 'true');"));
		((CQuickRunFrame*)wxGetApp().GetMainFrameWindow())->EnableVirtualClipboard(true);
	}
	else
	{
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('VirtualClipboard', 'false');"));
		((CQuickRunFrame*)wxGetApp().GetMainFrameWindow())->EnableVirtualClipboard(false);
	}
	dbConn->ExecuteUpdate(sqlCmd);

	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'ClipboardIndex';"));
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('ClipboardIndex', '%s');"), m_pComboClipboardIndex->GetValue());
	dbConn->ExecuteUpdate(sqlCmd);
	CClipBoardManager::GetInstance()->SetVirtualClipBoardIndex(wxAtoi(m_pComboClipboardIndex->GetValue())-1);
	event.Skip(true);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'FaceName';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('FaceName', '%s');"), m_FontData.GetChosenFont().GetFaceName());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'FontWeight';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('FontWeight', '%d');"), m_FontData.GetChosenFont().GetWeight());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'fontStyle';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('fontStyle', '%d');"), m_FontData.GetChosenFont().GetStyle());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'fontColor';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('fontColor', '%ld');"), m_FontData.GetColour().GetPixel());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'backColor';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('backColor', '%ld');"), m_pColorBoxBackColor->GetBoxColor().GetPixel());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'PointSize';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('PointSize', '%d');"), m_FontData.GetChosenFont().GetPointSize());
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'Modifier';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('Modifier', '%d');"), nModifier);
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'KeyCode';"));
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);
	//sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('KeyCode', '%d');"), nHotKey);
	//wxSQLiteDB->ExecuteUpdate(sqlCmd);

	//wxWindow *pParent = GetParent();
	//while(pParent->GetParent())
	//	pParent = pParent->GetParent();
	//((CQuickRunFrame *)pParent)->RegisterHotKeyCommand(CQuickRunFrame::wxID_HOTKEY_BRING_FOCUS, nHotKey, nModifier);
}

void COptionsPanel::OnCheckForLatestVersion(wxCommandEvent &event)
{
	m_pDownloadFile = new wxDownloadFile(this, wxT("http://www.priyank.co.in/wxQuickRun/getLatestVer.php"), wxT("latest.ver"));
	event.Skip(false);
}

void COptionsPanel::OnDonate(wxCommandEvent &event)
{
	wxLaunchDefaultBrowser(wxT("http://sourceforge.net/donate/index.php?group_id=169906"));
	event.Skip(false);
}

void COptionsPanel::OnDownloadEvent(wxDownloadEvent &event)
{
	if(event.GetDownLoadStatus() == wxDownloadEvent::DOWNLOAD_COMPLETE)
	{
		m_pDownloadFile->Delete();
		m_pDownloadFile = NULL;
		wxString strVer;
		{
			wxFileInputStream input(wxT("latest.ver"));
			wxTextInputStream text( input );
			text >> strVer;
		}
		::wxRemoveFile(wxT("latest.ver"));
		if(strVer != WXQUICKRUN_VERSION)
		{
			wxString strMessage = wxString::Format(wxT("A new version %s is avialable for download.\nDo you want to upgrade it now?"), strVer);
			if(wxMessageBox(strMessage, wxT("wxQuickRun"), wxYES_NO|wxCENTRE|wxICON_INFORMATION, this)==wxYES)
				wxLaunchDefaultBrowser(wxT("priyank.co.in/wxQuickRun/download.php"));
		}
		else
		{
			wxString strMessage = wxString::Format(wxT("You are currently using the latest version.\nPlease check again, after few days."));
			wxMessageBox(strMessage, wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_INFORMATION, this);
		}

	}
	else if(event.GetDownLoadStatus() == wxDownloadEvent::DOWNLOAD_FAIL)
	{
		m_pDownloadFile->Delete();
		m_pDownloadFile = NULL;
		wxString strMessage = wxString::Format(wxT("Could not connect to the server for information.\nPlease visit http://priyank.co.in/wxQuickRun/ for latest updates."));
		wxMessageBox(strMessage, wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_ERROR, this);
	}
}

void COptionsPanel::OnSelectLanguage(wxCommandEvent& WXUNUSED(event))
{
	if(wxGetApp().SelectLanguage(this))
	{
		wxMessageBox(wxT("The selected language will be applied, upon next startup."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_INFORMATION);
	}
}

void COptionsPanel::OnSearchEngineButton(wxCommandEvent &event)
{
	CSearchEngineDlg searchEngDlg(this);
	if(searchEngDlg.ShowModal()==wxID_OK)
	{
	}
	event.Skip(false);
}

void COptionsPanel::OnKeysAssignmentButton(wxCommandEvent &event)
{
	((CQuickRunFrame*)wxGetApp().GetMainFrameWindow())->DeInstallHotKeys();
	CKeysAssignDlg keysAssignDlg(this);
	if(keysAssignDlg.ShowModal()==wxID_OK)
	{
	}
	((CQuickRunFrame*)wxGetApp().GetMainFrameWindow())->InstallHotKeys();
	event.Skip(false);
}

int COptionsPanel::CountSearchEngine(void)
{
	int nCount = 0;
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("searchengines")))
	{
		dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT COUNT(*) FROM searchengines"));
		nCount = dbConn->ExecuteScalar(sqlCmd);
	}
	return nCount;
}
