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
 *	\file KeysAssignDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 13 Feb, 2007
 **/
#include "KeysAssignDlg.h"
#include "wxQuickRun.h"
#include <set>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CKeysAssignDlg, wxDialog)
	EVT_CLOSE(CKeysAssignDlg::OnClose)
	EVT_INIT_DIALOG(CKeysAssignDlg::OnInitDialog)
	EVT_BUTTON(wxID_OK, CKeysAssignDlg::OnOK)
END_EVENT_TABLE()

CKeysAssignDlg::CKeysAssignDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticTextFocus(NULL)
, m_pTextCtrlFocus(NULL)
, m_pComboBoxFocus(NULL)
, m_pStaticTextAddNote(NULL)
, m_pTextCtrlAddNote(NULL)
, m_pComboBoxAddNote(NULL)
, m_pStaticTextPasteFwd(NULL)
, m_pTextCtrlPasteFwd(NULL)
, m_pComboBoxPasteFwd(NULL)
, m_pStaticTextPasteBkwd(NULL)
, m_pTextCtrlPasteBkwd(NULL)
, m_pComboBoxPasteBkwd(NULL)
, m_pStaticTextClipCopy(NULL)
, m_pTextCtrlClipCopy(NULL)
, m_pComboBoxClipCopy(NULL)
, m_pStaticTextClipPaste(NULL)
, m_pTextCtrlClipPaste(NULL)
, m_pComboBoxClipPaste(NULL)
, m_pStaticTextPasteInc(NULL)
, m_pTextCtrlPasteInc(NULL)
, m_pComboBoxPasteInc(NULL)
, m_pStaticTextPasteDec(NULL)
, m_pTextCtrlPasteDec(NULL)
, m_pComboBoxPasteDec(NULL)
, m_pStaticTextGbMenu(NULL)
, m_pTextCtrlGbMenu(NULL)
, m_pComboBoxGbMenu(NULL)
, m_pStaticTextCountChars(NULL)
, m_pTextCtrlCountChars(NULL)
, m_pComboBoxCountChars(NULL)
, m_pStaticTextUpperCase(NULL)
, m_pTextCtrlUpperCase(NULL)
, m_pComboBoxUpperCase(NULL)
, m_pStaticTextLowerCase(NULL)
, m_pTextCtrlLowerCase(NULL)
, m_pComboBoxLowerCase(NULL)
, m_pStaticTextToogleCase(NULL)
, m_pTextCtrlToogleCase(NULL)
, m_pComboBoxToogleCase(NULL)
, m_pStaticTextSentenceCase(NULL)
, m_pTextCtrlSentenceCase(NULL)
, m_pComboBoxSentenceCase(NULL)
, m_pStaticTextCheckSpell(NULL)
, m_pTextCtrlCheckSpell(NULL)
, m_pComboBoxCheckSpell(NULL)
, m_pStaticTextCalculation(NULL)
, m_pTextCtrlCalculation(NULL)
, m_pComboBoxCalculation(NULL)
{
}

CKeysAssignDlg::~CKeysAssignDlg(void)
{
}

void CKeysAssignDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CKeysAssignDlg::OnInitDialog(wxInitDialogEvent &event)
{
	SetMinSize(wxSize(450, 300));
	SetIcon(wxICON(IDI_ICON_APPICON));

	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer *pStBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("HotKeys Binding"));
	wxFlexGridSizer *pFlexGridSizer = new wxFlexGridSizer(14, 3, 5, 5);
	wxArrayString modifier;
	modifier.Add(wxT(""));
	modifier.Add(wxT("SHIFT"));
	modifier.Add(wxT("CTRL"));
	modifier.Add(wxT("ALT"));
	modifier.Add(wxT("SHIFT|WIN"));
	modifier.Add(wxT("CTRL|WIN"));
	modifier.Add(wxT("ALT|WIN"));
	modifier.Add(wxT("ALT|SHIFT"));
	modifier.Add(wxT("ALT|CTRL"));
	modifier.Add(wxT("SHIFT|CTRL"));
	modifier.Add(wxT("CTRL|ALT|WIN"));
	modifier.Add(wxT("ALT|SHIFT|CTRL"));

	m_pStaticTextFocus = new wxStaticText(this, wxID_STATIC_TEXT_FOCUS, wxT("Command Input Focus:"));
	m_pTextCtrlFocus = new CKeyInputCtrl(this, wxID_TEXTCTRL_FOCUS, wxT(""));
	m_pComboBoxFocus = new wxComboBox(this, wxID_COMBOBOX_FOCUS, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextAddNote = new wxStaticText(this, wxID_STATIC_TEXT_ADDNOTE, wxT("Add Note:"));
	m_pTextCtrlAddNote = new CKeyInputCtrl(this, wxID_TEXTCTRL_ADDNOTE, wxT(""));
	m_pComboBoxAddNote = new wxComboBox(this, wxID_COMBOBOX_ADDNOTE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	//m_pStaticTextPasteFwd = new wxStaticText(this, wxID_STATIC_TEXT_PASTE_FWD, wxT("Paste Next:"));
	//m_pTextCtrlPasteFwd = new CKeyInputCtrl(this, wxID_TEXTCTRL_PASTE_FWD, wxT(""));
	//m_pComboBoxPasteFwd = new wxComboBox(this, wxID_COMBOBOX_PASTE_FWD, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	//m_pStaticTextPasteBkwd = new wxStaticText(this, wxID_STATIC_TEXT_PASTE_BKWD, wxT("Paste Previous:"));
	//m_pTextCtrlPasteBkwd = new CKeyInputCtrl(this, wxID_TEXTCTRL_PASTE_BKWD, wxT(""));
	//m_pComboBoxPasteBkwd = new wxComboBox(this, wxID_COMBOBOX_PASTE_BKWD, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextClipCopy = new wxStaticText(this, wxID_STATIC_TEXT_CLIP_COPY, wxT("Clipboard Copy:"));
	m_pTextCtrlClipCopy = new CKeyInputCtrl(this, wxID_TEXTCTRL_CLIP_COPY, wxT(""));
	m_pComboBoxClipCopy = new wxComboBox(this, wxID_COMBOBOX_CLIP_COPY, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextClipPaste = new wxStaticText(this, wxID_STATIC_TEXT_CLIP_PASTE, wxT("Clipboard Paste:"));
	m_pTextCtrlClipPaste = new CKeyInputCtrl(this, wxID_TEXTCTRL_CLIP_PASTE, wxT(""));
	m_pComboBoxClipPaste = new wxComboBox(this, wxID_COMBOBOX_CLIP_PASTE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextPasteInc = new wxStaticText(this, wxID_STATIC_TEXT_PASTE_INC, wxT("Increment Paste:"));
	m_pTextCtrlPasteInc = new CKeyInputCtrl(this, wxID_TEXTCTRL_PASTE_INC, wxT(""));
	m_pComboBoxPasteInc = new wxComboBox(this, wxID_COMBOBOX_PASTE_INC, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextPasteDec = new wxStaticText(this, wxID_STATIC_TEXT_PASTE_DEC, wxT("Decrement Paste:"));
	m_pTextCtrlPasteDec = new CKeyInputCtrl(this, wxID_TEXTCTRL_PASTE_DEC, wxT(""));
	m_pComboBoxPasteDec = new wxComboBox(this, wxID_COMBOBOX_PASTE_DEC, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextGbMenu = new wxStaticText(this, wxID_STATIC_TEXT_GB_MENU, wxT("Global Context Menu"));
	m_pTextCtrlGbMenu = new CKeyInputCtrl(this, wxID_TEXTCTRL_GB_MENU, wxT(""));
	m_pComboBoxGbMenu = new wxComboBox(this, wxID_COMBOBOX_GB_MENU, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextCountChars = new wxStaticText(this, wxID_STATIC_TEXT_COUNT_CHARS, wxT("Count Characters:"));
	m_pTextCtrlCountChars = new CKeyInputCtrl(this, wxID_TEXTCTRL_COUNT_CHARS, wxT(""));
	m_pComboBoxCountChars = new wxComboBox(this, wxID_COMBOBOX_COUNT_CHARS, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextUpperCase = new wxStaticText(this, wxID_STATIC_TEXT_UPPERCASE, wxT("Uppercase Conversion:"));
	m_pTextCtrlUpperCase = new CKeyInputCtrl(this, wxID_TEXTCTRL_UPPERCASE, wxT(""));
	m_pComboBoxUpperCase = new wxComboBox(this, wxID_COMBOBOX_UPPERCASE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextLowerCase = new wxStaticText(this, wxID_STATIC_TEXT_LOWERCASE, wxT("Lowercase Conversion:"));
	m_pTextCtrlLowerCase = new CKeyInputCtrl(this, wxID_TEXTCTRL_LOWERCASE, wxT(""));
	m_pComboBoxLowerCase = new wxComboBox(this, wxID_COMBOBOX_LOWERCASE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextToogleCase = new wxStaticText(this, wxID_STATIC_TEXT_TOGGLE_CASE, wxT("Toggle Case:"));
	m_pTextCtrlToogleCase = new CKeyInputCtrl(this, wxID_TEXTCTRL_TOGGLE_CASE, wxT(""));
	m_pComboBoxToogleCase = new wxComboBox(this, wxID_COMBOBOX_TOGGLE_CASE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextSentenceCase = new wxStaticText(this, wxID_STATIC_TEXT_SENTENCE_CASE, wxT("Sentence Case:"));
	m_pTextCtrlSentenceCase = new CKeyInputCtrl(this, wxID_TEXTCTRL_SENTENCE_CASE, wxT(""));
	m_pComboBoxSentenceCase = new wxComboBox(this, wxID_COMBOBOX_SENTENCE_CASE, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextCheckSpell = new wxStaticText(this, wxID_STATIC_TEXT_SPELL_CHECK, wxT("Spell Check:"));
	m_pTextCtrlCheckSpell = new CKeyInputCtrl(this, wxID_TEXTCTRL_SPELL_CHECK, wxT(""));
	m_pComboBoxCheckSpell = new wxComboBox(this, wxID_COMBOBOX_SPELL_CHECK, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);
	m_pStaticTextCalculation = new wxStaticText(this, wxID_STATIC_TEXT_CALCULATION, wxT("Maths Calculation:"));
	m_pTextCtrlCalculation = new CKeyInputCtrl(this, wxID_TEXTCTRL_CALCULATION, wxT(""));
	m_pComboBoxCalculation = new wxComboBox(this, wxID_COMBOBOX_CALCULATION, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);

	pFlexGridSizer->Add(m_pStaticTextFocus, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlFocus, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxFocus, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextAddNote, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlAddNote, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxAddNote, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pStaticTextPasteFwd, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pTextCtrlPasteFwd, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pComboBoxPasteFwd, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pStaticTextPasteBkwd, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pTextCtrlPasteBkwd, 1, wxEXPAND|wxALL, 0);
	//pFlexGridSizer->Add(m_pComboBoxPasteBkwd, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextClipCopy, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlClipCopy, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxClipCopy, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextClipPaste, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlClipPaste, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxClipPaste, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextPasteInc, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlPasteInc, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxPasteInc, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextPasteDec, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlPasteDec, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxPasteDec, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextGbMenu, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlGbMenu, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxGbMenu, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextCountChars, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlCountChars, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxCountChars, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextUpperCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlUpperCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxUpperCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextLowerCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlLowerCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxLowerCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextToogleCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlToogleCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxToogleCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextSentenceCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlSentenceCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxSentenceCase, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextCheckSpell, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlCheckSpell, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxCheckSpell, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pStaticTextCalculation, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pTextCtrlCalculation, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->Add(m_pComboBoxCalculation, 1, wxEXPAND|wxALL, 0);
	pFlexGridSizer->SetFlexibleDirection(wxBOTH);
	pFlexGridSizer->AddGrowableCol(2, 1);
	pFlexGridSizer->AddGrowableCol(1, 1);

	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton *pButtonApply = new wxButton(this, wxID_OK, wxT("&Apply"));
	wxButton *pButtonCancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(pButtonApply, 0, wxEXPAND | wxALL, 5);
	pButtonSizer->Add(pButtonCancel, 0, wxEXPAND | wxALL, 5);
	pButtonSizer->AddStretchSpacer(1);

	pStBoxSizer->Add(pFlexGridSizer, 1, wxEXPAND | wxALL, 5);
	pMainSizer->Add(pStBoxSizer, 1, wxEXPAND | wxALL, 5);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND | wxALL, 5);
	SetSizer(pMainSizer);

	m_pTextCtrlClipCopy->Disable();
	m_pTextCtrlClipCopy->SetValue(wxT("[0-9]"));
	m_pTextCtrlClipPaste->Disable();
	m_pTextCtrlClipPaste->SetValue(wxT("[0-9]"));

	SetAutoLayout(true);
	Fit();
	Layout();

	CenterOnScreen(wxBOTH);
	GetKeyBindingsFromDB();
}

void CKeysAssignDlg::OnOK(wxCommandEvent &event)
{
	if(CheckForDuplicateKeyBindings()==true)
	{
		SaveKeyBindingsToDB();
		event.Skip(true);
	}
	else
	{
		wxMessageBox(wxT("You have assigned two commands the same hotkey."), wxT("wxQuickRun"), wxOK|wxICON_ERROR|wxCENTRE, this);
		event.Skip(false);
	}
}

void CKeysAssignDlg::GetKeyBindingsFromDB(void)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("keybindings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE keybindings(key VARCHAR(32), modifier NUMERIC(3,0), virtualKey NUMERIC(2,0));"));
		AssignDefaultHotKey();
	}
	wxString sqlCmd = wxString::Format(wxT("select key, modifier, virtualKey from keybindings;"));
	wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
	while(result.NextRow())
	{
		InitControlFromDB(result.GetString(0), result.GetInt(1), result.GetInt(2));
	}
	result.Finalize();
}

void CKeysAssignDlg::SaveKeyBindingsToDB(void)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("keybindings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE keybindings(key VARCHAR(32), modifier NUMERIC(3,0), virtualKey NUMERIC(2,0));"));
	}
	dbConn->ExecuteUpdate(wxT("DELETE FROM keybindings WHERE 1=1;"));
	SaveRowToDB(wxT("Focus"), GetModifier(m_pComboBoxFocus->GetValue()), m_pTextCtrlFocus->GetKeyCode());
	SaveRowToDB(wxT("AddNote"), GetModifier(m_pComboBoxAddNote->GetValue()), m_pTextCtrlAddNote->GetKeyCode());
	//SaveRowToDB(wxT("PasteFwd"), GetModifier(m_pComboBoxPasteFwd->GetValue()), m_pTextCtrlPasteFwd->GetKeyCode());
	//SaveRowToDB(wxT("PasteBkwd"), GetModifier(m_pComboBoxPasteBkwd->GetValue()), m_pTextCtrlPasteBkwd->GetKeyCode());
	SaveRowToDB(wxT("ClipCopy"), GetModifier(m_pComboBoxClipCopy->GetValue()), 0);
	SaveRowToDB(wxT("ClipPaste"), GetModifier(m_pComboBoxClipPaste->GetValue()), 0);
	SaveRowToDB(wxT("PasteInc"), GetModifier(m_pComboBoxPasteInc->GetValue()), m_pTextCtrlPasteInc->GetKeyCode());
	SaveRowToDB(wxT("PasteDec"), GetModifier(m_pComboBoxPasteDec->GetValue()), m_pTextCtrlPasteDec->GetKeyCode());
	SaveRowToDB(wxT("GbMenu"), GetModifier(m_pComboBoxGbMenu->GetValue()), m_pTextCtrlGbMenu->GetKeyCode());
	SaveRowToDB(wxT("CountChars"), GetModifier(m_pComboBoxCountChars->GetValue()), m_pTextCtrlCountChars->GetKeyCode());
	SaveRowToDB(wxT("UpperCase"), GetModifier(m_pComboBoxUpperCase->GetValue()), m_pTextCtrlUpperCase->GetKeyCode());
	SaveRowToDB(wxT("LowerCase"), GetModifier(m_pComboBoxLowerCase->GetValue()), m_pTextCtrlLowerCase->GetKeyCode());
	SaveRowToDB(wxT("ToogleCase"), GetModifier(m_pComboBoxToogleCase->GetValue()), m_pTextCtrlToogleCase->GetKeyCode());
	SaveRowToDB(wxT("SentenceCase"), GetModifier(m_pComboBoxSentenceCase->GetValue()), m_pTextCtrlSentenceCase->GetKeyCode());
	SaveRowToDB(wxT("CheckSpell"), GetModifier(m_pComboBoxCheckSpell->GetValue()), m_pTextCtrlCheckSpell->GetKeyCode());
	SaveRowToDB(wxT("Calculation"), GetModifier(m_pComboBoxCalculation->GetValue()), m_pTextCtrlCalculation->GetKeyCode());
}

void CKeysAssignDlg::SaveRowToDB(wxString strKey, int nModifier, int nVirtualCode)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	wxString sqlCmd = wxString::Format(wxT("INSERT INTO keybindings('key', 'modifier', 'virtualKey') VALUES('%s', %d, %d);"), strKey, nModifier, nVirtualCode);
	dbConn->ExecuteUpdate(sqlCmd);
}

void CKeysAssignDlg::InitControlFromDB(wxString strKey, int nModifier, int nVirtualCode)
{
	if(strKey == wxT("Focus"))
	{
		m_pComboBoxFocus->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlFocus->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("AddNote"))
	{
		m_pComboBoxAddNote->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlAddNote->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("PasteFwd"))
	{
		//m_pComboBoxPasteFwd->SetValue(GetModifierAsString(nModifier));
		//m_pTextCtrlPasteFwd->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("PasteBkwd"))
	{
		//m_pComboBoxPasteBkwd->SetValue(GetModifierAsString(nModifier));
		//m_pTextCtrlPasteBkwd->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("ClipCopy"))
	{
		m_pTextCtrlClipCopy->SetValue(wxT("[0-9]"));
		m_pComboBoxClipCopy->SetValue(GetModifierAsString(nModifier));
	}
	else if(strKey == wxT("ClipPaste"))
	{
		m_pTextCtrlClipPaste->SetValue(wxT("[0-9]"));
		m_pComboBoxClipPaste->SetValue(GetModifierAsString(nModifier));
	}
	else if(strKey == wxT("PasteInc"))
	{
		m_pComboBoxPasteInc->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlPasteInc->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("PasteDec"))
	{
		m_pComboBoxPasteDec->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlPasteDec->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("GbMenu"))
	{
		m_pComboBoxGbMenu->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlGbMenu->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("CountChars"))
	{
		m_pComboBoxCountChars->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlCountChars->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("UpperCase"))
	{
		m_pComboBoxUpperCase->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlUpperCase->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("LowerCase"))
	{
		m_pComboBoxLowerCase->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlLowerCase->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("ToogleCase"))
	{
		m_pComboBoxToogleCase->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlToogleCase->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("SentenceCase"))
	{
		m_pComboBoxSentenceCase->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlSentenceCase->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("CheckSpell"))
	{
		m_pComboBoxCheckSpell->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlCheckSpell->SetKeyCode(nVirtualCode);
	}
	else if(strKey == wxT("Calculation"))
	{
		m_pComboBoxCalculation->SetValue(GetModifierAsString(nModifier));
		m_pTextCtrlCalculation->SetKeyCode(nVirtualCode);
	}
}

int CKeysAssignDlg::GetModifier(wxString strModifier)
{
	if(strModifier == wxT("SHIFT"))
		return wxMOD_SHIFT;
	else if(strModifier == wxT("CTRL"))
		return wxMOD_CONTROL;
	else if(strModifier == wxT("ALT"))
		return wxMOD_ALT;
	else if(strModifier == wxT("SHIFT|WIN"))
		return wxMOD_SHIFT|wxMOD_WIN;
	else if(strModifier == wxT("CTRL|WIN"))
		return wxMOD_CONTROL|wxMOD_WIN;
	else if(strModifier == wxT("ALT|WIN"))
		return wxMOD_ALT|wxMOD_WIN;
	else if(strModifier == wxT("ALT|SHIFT"))
		return wxMOD_ALT|wxMOD_SHIFT;
	else if(strModifier == wxT("ALT|CTRL"))
		return wxMOD_ALT|wxMOD_CONTROL;
	else if(strModifier == wxT("SHIFT|CTRL"))
		return wxMOD_SHIFT|wxMOD_CONTROL;
	else if(strModifier == wxT("ALT|SHIFT|CTRL"))
		return wxMOD_ALT|wxMOD_SHIFT|wxMOD_CONTROL;
	else if(strModifier == wxT("CTRL|ALT|WIN"))
		return wxMOD_CONTROL|wxMOD_ALT|wxMOD_WIN;
	return 0;
}

wxString CKeysAssignDlg::GetModifierAsString(int nModifier)
{
	if(nModifier == int(wxMOD_SHIFT))
		return wxT("SHIFT");
	else if(nModifier == int(wxMOD_CONTROL))
		return wxT("CTRL");
	else if(nModifier == int(wxMOD_ALT))
		return wxT("ALT");
	else if(nModifier == int(wxMOD_SHIFT|wxMOD_WIN))
		return wxT("SHIFT|WIN");
	else if(nModifier == int(wxMOD_CONTROL|wxMOD_WIN))
		return wxT("CTRL|WIN");
	else if(nModifier == int(wxMOD_ALT|wxMOD_WIN))
		return wxT("ALT|WIN");
	else if(nModifier == int(wxMOD_ALT|wxMOD_SHIFT))
		return wxT("ALT|SHIFT");
	else if(nModifier == int(wxMOD_ALT|wxMOD_CONTROL))
		return wxT("ALT|CTRL");
	else if(nModifier == int(wxMOD_SHIFT|wxMOD_CONTROL))
		return wxT("SHIFT|CTRL");
	else if(nModifier == int(wxMOD_ALT|wxMOD_SHIFT|wxMOD_CONTROL))
		return wxT("ALT|SHIFT|CTRL");
	else if(nModifier == int(wxMOD_CONTROL|wxMOD_ALT|wxMOD_WIN))
		return wxT("CTRL|ALT|WIN");
	return wxT("");
}

bool CKeysAssignDlg::CheckForDuplicateKeyBindings(void)
{
	int nKeyCode = 0; 
	std::set<int, less<int>> keysSet;

	nKeyCode = m_pTextCtrlFocus->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxFocus->GetValue());
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlAddNote->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxAddNote->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	//nKeyCode = m_pTextCtrlPasteFwd->GetKeyCode();
	//nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxPasteFwd->GetValue()); 
	//if(keysSet.insert(nKeyCode).second == false)
	//	return false;

	//nKeyCode = m_pTextCtrlPasteBkwd->GetKeyCode();
	//nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxPasteBkwd->GetValue()); 
	//if(keysSet.insert(nKeyCode).second == false)
	//	return false;

	for (int i=0; i<10; i++)
	{
		nKeyCode = i + int(char(wxT('0')));
		nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxClipCopy->GetValue()); 
		if(keysSet.insert(nKeyCode).second == false)
			return false;
	}

	for (int i=0; i<10; i++)
	{
		nKeyCode = i + int(char(wxT('0')));
		nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxClipPaste->GetValue()); 
		if(keysSet.insert(nKeyCode).second == false)
			return false;
	}

	nKeyCode = m_pTextCtrlPasteInc->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxPasteInc->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlPasteDec->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxPasteDec->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlGbMenu->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxGbMenu->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlCountChars->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxCountChars->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlUpperCase->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxUpperCase->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlLowerCase->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxLowerCase->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlToogleCase->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxToogleCase->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlSentenceCase->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxSentenceCase->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlCheckSpell->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxCheckSpell->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	nKeyCode = m_pTextCtrlCalculation->GetKeyCode();
	nKeyCode = (nKeyCode*100) + GetModifier(m_pComboBoxCalculation->GetValue()); 
	if(keysSet.insert(nKeyCode).second == false)
		return false;

	return true;
}

void CKeysAssignDlg::AssignDefaultHotKey(void)
{
	SaveRowToDB(wxT("Focus"), wxMOD_CONTROL, VK_OEM_3);
	SaveRowToDB(wxT("AddNote"), wxMOD_CONTROL|wxMOD_WIN, 0x4E);
	SaveRowToDB(wxT("PasteFwd"), 0, 0);
	SaveRowToDB(wxT("PasteBkwd"), 0, 0);
	SaveRowToDB(wxT("ClipCopy"), wxMOD_CONTROL|wxMOD_WIN, 0);
	SaveRowToDB(wxT("ClipPaste"), wxMOD_SHIFT|wxMOD_WIN, 0);
	SaveRowToDB(wxT("PasteInc"), wxMOD_CONTROL, VK_UP);
	SaveRowToDB(wxT("PasteDec"), wxMOD_CONTROL, VK_DOWN);
	SaveRowToDB(wxT("GbMenu"), wxMOD_CONTROL|wxMOD_WIN|wxMOD_ALT, 0);
	SaveRowToDB(wxT("CountChars"), wxMOD_CONTROL|wxMOD_ALT, 0x31);
	SaveRowToDB(wxT("UpperCase"), wxMOD_CONTROL|wxMOD_ALT, 0x32);
	SaveRowToDB(wxT("LowerCase"), wxMOD_CONTROL|wxMOD_ALT, 0x33);
	SaveRowToDB(wxT("ToogleCase"), wxMOD_CONTROL|wxMOD_ALT, 0x34);
	SaveRowToDB(wxT("SentenceCase"), wxMOD_CONTROL|wxMOD_ALT, 0x35);
	SaveRowToDB(wxT("CheckSpell"), wxMOD_CONTROL|wxMOD_ALT, 0x36);
	SaveRowToDB(wxT("Calculation"), wxMOD_CONTROL|wxMOD_ALT, 0x37);
}

void CKeysAssignDlg::GetCommandHotKey(wxString strKey, int &nVirtualKey, int &nModifier)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	wxString sqlCmd = wxString::Format(wxT("select virtualKey, modifier from keybindings WHERE key = '%s';"), strKey);
	wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
	if(result.NextRow())
	{
		nVirtualKey = result.GetInt(0);
		nModifier = result.GetInt(1);
	}
	result.Finalize();
}
