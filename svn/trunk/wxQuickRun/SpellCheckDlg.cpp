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
 *	\file SpellCheckDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 10 Feb, 2007
 **/

#include <wx/filename.h>
#include "SpellCheckDlg.h"
#include <wx/stdpaths.h>
#include "hunspell.hxx"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CSpellCheckDlg, wxDialog)
	EVT_CLOSE(CSpellCheckDlg::OnClose)
	EVT_INIT_DIALOG(CSpellCheckDlg::OnInitDialog)
	EVT_BUTTON(wxID_BUTTON_IGNORE, CSpellCheckDlg::OnButtonIgnore)
	EVT_BUTTON(wxID_BUTTON_IGNORE_ALL, CSpellCheckDlg::OnButtonIgnoreAll)
	EVT_BUTTON(wxID_BUTTON_ADD, CSpellCheckDlg::OnButtonAdd)
	EVT_BUTTON(wxID_BUTTON_REPLACE, CSpellCheckDlg::OnButtonReplace)
	EVT_BUTTON(wxID_BUTTON_REPLACE_ALL, CSpellCheckDlg::OnButtonReplaceAll)
	EVT_BUTTON(wxID_BUTTON_CHECK_WORD, CSpellCheckDlg::OnButtonCheckWord)
	EVT_BUTTON(wxID_CANCEL, CSpellCheckDlg::OnButtonCancel)
END_EVENT_TABLE()

CSpellCheckDlg::CSpellCheckDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pListBoxSuggest(NULL)
, m_pTextCtrlMisSpelledText(NULL)
, m_pTextCtrlReplaceWith(NULL)
, m_pButtonIgnore(NULL)
, m_pButtonIgnoreAll(NULL)
, m_pButtonAdd(NULL)
, m_pButtonReplace(NULL)
, m_pButtonReplaceAll(NULL)
, m_pButtonCheckWord(NULL)
, m_pButtonCancel(NULL)
, nWordIndex(0)
{
	wxString strAppPath = wxStandardPaths().GetExecutablePath();
	strAppPath = strAppPath.Left(strAppPath.Find(wxFileName::GetPathSeparator(), true)+1);
	strAppPath += wxT("en");
	strAppPath += wxFileName::GetPathSeparator();
	m_afPath = strAppPath + wxT("en-US.aff");
	m_dfPath = strAppPath + wxT("en-US.dic");
}

CSpellCheckDlg::~CSpellCheckDlg(void)
{
}

void CSpellCheckDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CSpellCheckDlg::OnInitDialog(wxInitDialogEvent& WXUNUSED(event))
{
	SetMinSize(wxSize(450, 300));
	SetIcon(wxICON(IDI_ICON_SPELL_CHECK));
	wxBoxSizer *pMainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *pTextSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText *pStaticTextMisSpell = new wxStaticText(this, wxID_ANY, wxT("&Text being checked:"));
	m_pTextCtrlMisSpelledText = new wxTextCtrl(this, wxID_TEXTCTRL_MIS_SPELLED, m_strText2Check, wxDefaultPosition, wxDefaultSize, wxTE_RICH2|wxTE_MULTILINE|wxTE_READONLY);
	wxStaticText *pStaticTextReplaceWith = new wxStaticText(this, wxID_ANY, wxT("Replace &with:"));
	m_pTextCtrlReplaceWith = new wxTextCtrl(this, wxID_TEXTCTRL_REPLACE_WITH, wxEmptyString);
	wxStaticText *pStaticTextSuggestions = new wxStaticText(this, wxID_ANY, wxT("S&uggestions:"));
	m_pListBoxSuggest = new wxListBox(this, wxID_LISTBOX_SUGGEST);

	pTextSizer->Add(pStaticTextMisSpell, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5);
	pTextSizer->Add(m_pTextCtrlMisSpelledText, 1, wxEXPAND|wxALL, 5);
	pTextSizer->Add(pStaticTextReplaceWith, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5);
	pTextSizer->Add(m_pTextCtrlReplaceWith, 0, wxEXPAND|wxALL, 5);
	pTextSizer->Add(pStaticTextSuggestions, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, 5);
	pTextSizer->Add(m_pListBoxSuggest, 1, wxEXPAND|wxALL, 5);

	m_pButtonIgnore = new wxButton(this, wxID_BUTTON_IGNORE, wxT("&Ignore"));
	m_pButtonIgnoreAll = new wxButton(this, wxID_BUTTON_IGNORE_ALL, wxT("I&gnore All"));
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_ADD, wxT("&Add"));
	m_pButtonReplace = new wxButton(this, wxID_BUTTON_REPLACE, wxT("&Replace"));
	m_pButtonReplaceAll = new wxButton(this, wxID_BUTTON_REPLACE_ALL, wxT("Replace A&ll"));
	m_pButtonCheckWord = new wxButton(this, wxID_BUTTON_CHECK_WORD, wxT("Check W&ord"));
	m_pButtonCancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));

	pButtonSizer->Add(m_pButtonIgnore, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonIgnoreAll, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonAdd, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonReplace, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonReplaceAll, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonCheckWord, 1, wxEXPAND|wxALL, 5);
	pButtonSizer->Add(m_pButtonCancel, 1, wxEXPAND|wxALL, 5);

	pMainSizer->Add(pTextSizer, 1, wxEXPAND|wxALL, 5);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND|wxRIGHT|wxTOP|wxBOTTOM, 5);

	SetSizer(pMainSizer);
	SetAutoLayout(true);
	Fit();
	Layout();
	CenterOnScreen(wxBOTH);
	if(FindNextMisSpelledWord()==false)
	{
		wxMessageBox(wxT("There are no spelling mistakes in the selected text."), wxT("Spell Check"), wxOK|wxCENTER|wxICON_INFORMATION, this->GetParent());
		wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED,wxID_CANCEL);
		AddPendingEvent(evt);
	}
}

wxString CSpellCheckDlg::GetNextWord()
{
	bool bInWord = false;
	wxString strWord;
	for(; nWordIndex < m_strText2Check.Length(); nWordIndex++)
	{
		if(isalnum(m_strText2Check[nWordIndex]))
		{
			if(bInWord == false)
				bInWord = true;
			strWord += m_strText2Check[nWordIndex];
		}
		else if(isspace(m_strText2Check[nWordIndex]) || ispunct(m_strText2Check[nWordIndex]))
		{
			if(bInWord == true)
			{
				bInWord = false;
				break;
			}
		}
	}
	return strWord;
}

bool CSpellCheckDlg::FindNextMisSpelledWord(void)
{
	bool bIsMisSpell = false;
	char *pStrAF = wxStringToChar(m_afPath);
	char *pStrDF = wxStringToChar(m_dfPath);
	Hunspell *pMS = new Hunspell(pStrAF, pStrDF);
	while(true)
	{
		wxString strWord = GetNextWord();
		char *pWord = wxStringToChar(strWord);
		if (strWord == wxEmptyString)
		{
			delete pWord;
			pWord = NULL;
			break;
		}
		else if(!pMS->spell(pWord))
		{
			bIsMisSpell = true;
			char **wlst;
			int ns = pMS->suggest(&wlst, pWord);
			m_pListBoxSuggest->Clear();
			for (int i=0; i < ns; i++)
			{
				wxString strWord = wxString::FromAscii(wlst[i]);
				m_pListBoxSuggest->Append(strWord);
				free(wlst[i]);
			}
			if(ns > 0)
			{
				m_pListBoxSuggest->Select(0);
				m_pTextCtrlReplaceWith->SetValue(m_pListBoxSuggest->GetString(0));
			}
			delete pWord;
			pWord = NULL;
			break;
		}
		delete pWord;
		pWord = NULL;
	}
	delete pStrAF;
	delete pStrDF;
	delete pMS;
	return bIsMisSpell;
}

void CSpellCheckDlg::SetTextToCheck(wxString strText)
{
	m_strText2Check =  strText;
}

wxString CSpellCheckDlg::GetCorrectedText(void)
{
	return wxEmptyString;
}

void CSpellCheckDlg::OnButtonIgnore(wxCommandEvent& WXUNUSED(event))
{
}

void CSpellCheckDlg::OnButtonIgnoreAll(wxCommandEvent& WXUNUSED(event))
{
}

void CSpellCheckDlg::OnButtonAdd(wxCommandEvent& WXUNUSED(event))
{
	char *pStrAF = wxStringToChar(m_afPath);
	char *pStrDF = wxStringToChar(m_dfPath);
	Hunspell *pMS = new Hunspell(pStrAF, pStrDF);
	wxString strWord = m_pTextCtrlReplaceWith->GetValue();
	char *pWord = wxStringToChar(strWord);
	delete pWord;
	delete pStrAF;
	delete pStrDF;
	delete pMS;
}

void CSpellCheckDlg::OnButtonReplace(wxCommandEvent& WXUNUSED(event))
{
}

void CSpellCheckDlg::OnButtonReplaceAll(wxCommandEvent& WXUNUSED(event))
{
}

void CSpellCheckDlg::OnButtonCheckWord(wxCommandEvent& WXUNUSED(event))
{
}

void CSpellCheckDlg::OnButtonCancel(wxCommandEvent& event)
{
	event.Skip(true);
}
