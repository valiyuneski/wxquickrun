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

	//wxBoxSizer *pHotKeySizer = new wxBoxSizer(wxHORIZONTAL);
	//wxArrayString arrayHotKey;
	//arrayHotKey.Add(wxEmptyString);
	//arrayHotKey.Add(wxT("Alt"));
	//arrayHotKey.Add(wxT("Ctrl"));
	//arrayHotKey.Add(wxT("Shift"));
	//arrayHotKey.Add(wxT("Ctrl+Alt"));
	//arrayHotKey.Add(wxT("Alt+Shift"));
	//arrayHotKey.Add(wxT("Ctrl+Shift"));
	//arrayHotKey.Add(wxT("Ctrl+Alt+Shift"));
	//m_pStaticTextHotKey = new wxStaticText(this, wxID_STATIC_TEXT_HOT_KEY, wxT("Focus &Hot Key:"));
	//m_pTextCtrlHotKey = new wxTextCtrl(this, wxID_TEXTCTRL_HOT_KEY, wxEmptyString);
	//m_pTextCtrlHotKey->SetMaxLength(1);
	//m_pComboHotKey = new wxComboBox(this, wxID_COMBOBOX_HOT_KEY, wxT("Ctrl"), wxDefaultPosition, wxDefaultSize, arrayHotKey, wxCB_READONLY);
	//pStaticSizer->Add(m_pStaticTextHotKey, 1, wxALL | wxEXPAND, 5);
	//pHotKeySizer->Add(m_pTextCtrlHotKey, 1, wxALL | wxEXPAND, 5);
	//pHotKeySizer->Add(m_pComboHotKey, 1, wxALL | wxEXPAND, 5);

	//pTextSizer->Add(pFontSizer, 1, wxALL | wxEXPAND, 0);
	//pTextSizer->Add(pTimeSizer, 1, wxALL | wxEXPAND, 0);
	//pTextSizer->Add(pBackColorSizer, 1, wxALL | wxEXPAND, 0);
	//pTextSizer->Add(pTransparencySizer, 1, wxALL | wxEXPAND, 0);
	
	//pTextSizer->Add(pHotKeySizer, 1, wxALL | wxEXPAND, 0);

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


	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("settings")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(32), value VARCHAR(32));"));
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
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				if(result.GetString(0) == wxT("true"))
					m_pCheckBoxAutoStart->SetValue(true);
				else
					m_pCheckBoxAutoStart->SetValue(false);
			}
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'VirtualClipboard';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				if(result.GetString(0) == wxT("true"))
					m_pCheckBoxVirtualClipboard->SetValue(true);
				else
					m_pCheckBoxVirtualClipboard->SetValue(false);
			}
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'ClipboardIndex';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				m_pComboClipboardIndex->SetValue(result.GetString(0));
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
		//switch(nModifier)
		//{
		//case wxMOD_ALT:
		//	m_pComboHotKey->SetValue(wxT("Alt"));
		//	break;
		//case wxMOD_CONTROL:
		//	m_pComboHotKey->SetValue(wxT("Ctrl"));
		//	break;
		//case wxMOD_SHIFT:
		//	m_pComboHotKey->SetValue(wxT("Shift"));
		//	break;
		//case wxMOD_CONTROL|wxMOD_ALT:
		//	m_pComboHotKey->SetValue(wxT("Ctrl+Alt"));
		//	break;
		//case wxMOD_ALT|wxMOD_SHIFT:
		//	m_pComboHotKey->SetValue(wxT("Alt+Shift"));
		//	break;
		//case wxMOD_CONTROL|wxMOD_SHIFT:
		//	m_pComboHotKey->SetValue(wxT("Ctrl+Shift"));
		//	break;
		//case wxMOD_CONTROL|wxMOD_ALT|wxMOD_SHIFT:
		//	m_pComboHotKey->SetValue(wxT("Ctrl+Alt+Shift"));
		//	break;
		//default:
		//	m_pComboHotKey->SetValue(wxEmptyString);
		//	break;
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
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
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
	//int nHotKey = GetVirtualKeyCode(m_pTextCtrlHotKey->GetValue().GetChar(0));
	//int nModifier = 0;
	//if(m_pComboHotKey->GetValue() == wxT("Alt"))
	//	nModifier = wxMOD_ALT;
	//else if(m_pComboHotKey->GetValue() == wxT("Ctrl"))
	//	nModifier = wxMOD_CONTROL;
	//else if(m_pComboHotKey->GetValue() == wxT("Shift"))
	//	nModifier = wxMOD_SHIFT;
	//else if(m_pComboHotKey->GetValue() == wxT("Ctrl+Alt"))
	//	nModifier = wxMOD_CONTROL|wxMOD_ALT;
	//else if(m_pComboHotKey->GetValue() == wxT("Alt+Shift"))
	//	nModifier = wxMOD_ALT|wxMOD_SHIFT;
	//else if(m_pComboHotKey->GetValue() == wxT("Ctrl+Shift"))
	//	nModifier = wxMOD_CONTROL|wxMOD_SHIFT;
	//else if(m_pComboHotKey->GetValue() == wxT("Ctrl+Alt+Shift"))
	//	nModifier = wxMOD_CONTROL|wxMOD_ALT|wxMOD_SHIFT;
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("settings")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(32), value VARCHAR(32));"));
	}
	wxString sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'AutoStart';"));
	wxSQLiteDB->ExecuteUpdate(sqlCmd);
	if (m_pCheckBoxAutoStart->GetValue())
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('AutoStart', 'true');"));
	else
		sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('AutoStart', 'false');"));
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'VirtualClipboard';"));
	wxSQLiteDB->ExecuteUpdate(sqlCmd);
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
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'ClipboardIndex';"));
	wxSQLiteDB->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("INSERT INTO settings(key, value) VALUES('ClipboardIndex', '%s');"), m_pComboClipboardIndex->GetValue());
	wxSQLiteDB->ExecuteUpdate(sqlCmd);
	CClipBoardManager::GetInstance()->SetVirtualClipBoardIndex(wxAtoi(m_pComboClipboardIndex->GetValue())-1);
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
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	event.Skip(true);

	//wxWindow *pParent = GetParent();
	//while(pParent->GetParent())
	//	pParent = pParent->GetParent();
	//((CQuickRunFrame *)pParent)->RegisterFreshHotKey(CQuickRunFrame::wxID_HOTKEY_BRING_FOCUS, nHotKey, nModifier);
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

		m_pDownloadFile->Delete();
		m_pDownloadFile = NULL;
	}
	else if(event.GetDownLoadStatus() == wxDownloadEvent::DOWNLOAD_FAIL)
	{
		wxString strMessage = wxString::Format(wxT("Could not connect to the server for information.\nPlease visit http://priyank.co.in/wxQuickRun/ for latest updates."));
		wxMessageBox(strMessage, wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_ERROR, this);
		m_pDownloadFile->Delete();
		m_pDownloadFile = NULL;
	}
}

void COptionsPanel::OnSelectLanguage(wxCommandEvent & event)
{
	if(wxGetApp().SelectLanguage(this))
	{
		wxMessageBox(wxT("The selected language will be applied, upon next startup."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_INFORMATION);
	}
}

//#ifdef __WXMAC__
//	# ifdef __DARWIN__
//		#  include <carbon>
//	# else
//		#  include <process.h>
//	# endif
//	# include "wx/filename.h"
//#endif
//
//wxString COptionsPanel::GetExecutablePath()
//{
//	static bool found = false;
//	static wxString path;
//
//	if (found)
//		return path;
//	else
//	{
//#ifdef __WXMSW__
//
//		WCHAR buff[512];
//		*buff = wxT('\0');
//		GetModuleFileName(NULL, buff, 511);
//		path = wxString::Format(wxT("%s"), buff);
//
//#elif defined(__WXMAC__)
//
//		ProcessInfoRec processinfo;
//		ProcessSerialNumber procno ;
//		FSSpec fsSpec;
//
//		procno.highLongOfPSN = NULL ;
//		procno.lowLongOfPSN = kCurrentProcess ;
//		processinfo.processInfoLength = sizeof(ProcessInfoRec);
//		processinfo.processName = NULL;
//		processinfo.processAppSpec = &fsSpec;
//
//		GetProcessInformation( &procno , &processinfo ) ;
//		path = wxMacFSSpec2MacFilename(&fsSpec);
//#else
//		wxString argv0 = wxTheApp->argv[0];
//
//		if (wxIsAbsolutePath(argv0))
//			path = argv0;
//		else
//		{
//			wxPathList pathlist;
//			pathlist.AddEnvList(wxT("PATH"));
//			path = pathlist.FindAbsoluteValidPath(argv0);
//		}
//
//		wxFileName filename(path);
//		filename.Normalize();
//		path = filename.GetFullPath();
//#endif
//		found = true;
//		return path;
//	}
//}

//int COptionsPanel::GetVirtualKeyCode(wxChar ch)
//{
//	switch(ch)
//	{
//#ifdef  __WXMSW__
//	case wxT(' '):
//		return VK_SPACE;
//		break;
//	case wxT('0'):
//		return 0x30;
//		break;
//	case wxT('1'):
//		return 0x31;
//		break;
//	case wxT('2'):
//		return 0x32;
//		break;
//	case wxT('3'):
//		return 0x33;
//		break;
//	case wxT('4'):
//		return 0x34;
//		break;
//	case wxT('5'):
//		return 0x35;
//		break;
//	case wxT('6'):
//		return 0x36;
//		break;
//	case wxT('7'):
//		return 0x37;
//		break;
//	case wxT('8'):
//		return 0x38;
//		break;
//	case wxT('9'):
//		return 0x39;
//		break;
//	case wxT('a'):
//	case wxT('A'):
//		return 0x41;
//		break;
//	case wxT('b'):
//	case wxT('B'):
//		return 0x42;
//		break;
//	case wxT('c'):
//	case wxT('C'):
//		return 0x43;
//		break;
//	case wxT('d'):
//	case wxT('D'):
//		return 0x44;
//		break;
//	case wxT('e'):
//	case wxT('E'):
//		return 0x45;
//		break;
//	case wxT('f'):
//	case wxT('F'):
//		return 0x46;
//		break;
//	case wxT('g'):
//	case wxT('G'):
//		return 0x47;
//		break;
//	case wxT('h'):
//	case wxT('H'):
//		return 0x48;
//		break;
//	case wxT('i'):
//	case wxT('I'):
//		return 0x49;
//		break;
//	case wxT('j'):
//	case wxT('J'):
//		return 0x4A;
//		break;
//	case wxT('k'):
//	case wxT('K'):
//		return 0x4B;
//		break;
//	case wxT('l'):
//	case wxT('L'):
//		return 0x4C;
//		break;
//	case wxT('m'):
//	case wxT('M'):
//		return 0x4D;
//		break;
//	case wxT('n'):
//	case wxT('N'):
//		return 0x4E;
//		break;
//	case wxT('o'):
//	case wxT('O'):
//		return 0x4F;
//		break;
//	case wxT('p'):
//	case wxT('P'):
//		return 0x50;
//		break;
//	case wxT('q'):
//	case wxT('Q'):
//		return 0x51;
//		break;
//	case wxT('r'):
//	case wxT('R'):
//		return 0x52;
//		break;
//	case wxT('s'):
//	case wxT('S'):
//		return 0x53;
//		break;
//	case wxT('t'):
//	case wxT('T'):
//		return 0x54;
//		break;
//	case wxT('u'):
//	case wxT('U'):
//		return 0x55;
//		break;
//	case wxT('v'):
//	case wxT('V'):
//		return 0x56;
//		break;
//	case wxT('w'):
//	case wxT('W'):
//		return 0x57;
//		break;
//	case wxT('x'):
//	case wxT('X'):
//		return 0x58;
//		break;
//	case wxT('y'):
//	case wxT('Y'):
//		return 0x59;
//		break;
//	case wxT('z'):
//	case wxT('Z'):
//		return 0x5A;
//		break;
//	case wxT('*'):
//		return VK_MULTIPLY;
//		break;
//	case wxT('+'):
//		return VK_ADD;
//		break;
//	case wxT('-'):
//		return VK_SUBTRACT;
//		break;
//	case wxT('.'):
//		return VK_DECIMAL;
//		break;
//	case wxT(';'):
//	case wxT(':'):
//		return VK_OEM_1;
//		break;
//	case wxT('/'):
//	case wxT('?'):
//		return VK_OEM_2;
//		break;
//	case wxT('`'):
//	case wxT('~'):
//		return VK_OEM_3;
//		break;
//	case wxT('['):
//	case wxT('{'):
//		return VK_OEM_4;
//		break;
//	case wxT('\\'):
//	case wxT('|'):
//		return VK_OEM_5;
//		break;
//	case wxT(']'):
//	case wxT('}'):
//		return VK_OEM_6;
//		break;
//	case wxT('\''):
//	case wxT('"'):
//		return VK_OEM_7;
//		break;
//#endif
//	default:
//		return 0;
//	}
//}
//
//wxChar COptionsPanel::GetCharFromKeyCode(int nKeyCode)
//{
//	switch(nKeyCode)
//	{
//#ifdef  __WXMSW__
//	case VK_SPACE:
//		return wxT(' ');
//		break;
//	case 0x30:
//		return wxT('0');
//		break;
//	case 0x31:
//		return wxT('1');
//		break;
//	case 0x32:
//		return wxT('2');
//		break;
//	case 0x33:
//		return wxT('3');
//		break;
//	case 0x34:
//		return wxT('4');
//		break;
//	case 0x35:
//		return wxT('5');
//		break;
//	case 0x36:
//		return wxT('6');
//		break;
//	case 0x37:
//		return wxT('7');
//		break;
//	case 0x38:
//		return wxT('8');
//		break;
//	case 0x39:
//		return wxT('9');
//		break;
//	case 0x41:
//		return wxT('A');
//		break;
//	case 0x42:
//		return wxT('B');
//		break;
//	case 0x43:
//		return wxT('C');
//		break;
//	case 0x44:
//		return wxT('D');
//		break;
//	case 0x45:
//		return wxT('E');
//		break;
//	case 0x46:
//		return wxT('F');
//		break;
//	case 0x47:
//		return wxT('G');
//		break;
//	case 0x48:
//		return wxT('H');
//		break;
//	case 0x49:
//		return wxT('I');
//		break;
//	case 0x4A:
//		return wxT('J');
//		break;
//	case 0x4B:
//		return wxT('K');
//		break;
//	case 0x4C:
//		return wxT('L');
//		break;
//	case 0x4D:
//		return wxT('M');
//		break;
//	case 0x4E:
//		return wxT('N');
//		break;
//	case 0x4F:
//		return wxT('O');
//		break;
//	case 0x50:
//		return wxT('P');
//		break;
//	case 0x51:
//		return wxT('Q');
//		break;
//	case 0x52:
//		return wxT('R');
//		break;
//	case 0x53:
//		return wxT('S');
//		break;
//	case 0x54:
//		return wxT('T');
//		break;
//	case 0x55:
//		return wxT('U');
//		break;
//	case 0x56:
//		return wxT('V');
//		break;
//	case 0x57:
//		return wxT('W');
//		break;
//	case 0x58:
//		return wxT('X');
//		break;
//	case 0x59:
//		return wxT('Y');
//		break;
//	case 0x5A:
//		return wxT('Z');
//		break;
//	case VK_MULTIPLY:
//		return wxT('*');
//		break;
//	case VK_ADD:
//		return wxT('+');
//		break;
//	case VK_SUBTRACT:
//		return wxT('-');
//		break;
//	case VK_DECIMAL:
//		return wxT('.');
//		break;
//	case VK_OEM_1:
//		return wxT(';');
//		break;
//	case VK_OEM_2:
//		return wxT('/');
//		break;
//	case VK_OEM_3:
//		return wxT('`');
//		break;
//	case VK_OEM_4:
//		return wxT('[');
//		break;
//	case VK_OEM_5:
//		return wxT('\\');
//		break;
//	case VK_OEM_6:
//		return wxT(']');
//		break;
//	case VK_OEM_7:
//		return wxT('\'');
//		break;
//#endif
//	default:
//		return 0;
//	}
//}

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
	CKeysAssignDlg keysAssignDlg(this);
	if(keysAssignDlg.ShowModal()==wxID_OK)
	{
	}
	event.Skip(false);
}

int COptionsPanel::CountSearchEngine(void)
{
	int nCount = 0;
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("searchengines")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT COUNT(*) FROM searchengines"));
		nCount = wxSQLiteDB->ExecuteScalar(sqlCmd);
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	return nCount;
}
