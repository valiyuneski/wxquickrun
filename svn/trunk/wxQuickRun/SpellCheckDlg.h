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
 *	\file SpellCheckDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 10 Feb, 2007
 **/

#pragma once
#include "stdwx.h"
#include <wx/listbox.h>

class CSpellCheckDlg : public wxDialog
{
private:
	wxString m_strText2Check;
	wxListBox *m_pListBoxSuggest;
	wxTextCtrl *m_pTextCtrlMisSpelledText;
	wxTextCtrl *m_pTextCtrlReplaceWith;
	wxButton *m_pButtonIgnore;
	wxButton *m_pButtonIgnoreAll;
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonReplace;
	wxButton *m_pButtonReplaceAll;
	wxButton *m_pButtonCheckWord;
	wxButton *m_pButtonCancel;
	size_t nWordIndex;
	wxString m_afPath;
	wxString m_dfPath;

public:
	CSpellCheckDlg(wxWindow* parent, wxWindowID id=CSpellCheckDlg::wxID_DIALOG_SPELL_CHECK, const wxString& title = wxT("Spell Check"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("spell checking dialog box."));
	virtual ~CSpellCheckDlg(void);
	void SetTextToCheck(wxString strText);
	wxString GetCorrectedText(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnButtonIgnore(wxCommandEvent& WXUNUSED(event));
	void OnButtonIgnoreAll(wxCommandEvent& WXUNUSED(event));
	void OnButtonAdd(wxCommandEvent& WXUNUSED(event));
	void OnButtonReplace(wxCommandEvent& WXUNUSED(event));
	void OnButtonReplaceAll(wxCommandEvent& WXUNUSED(event));
	void OnButtonCheckWord(wxCommandEvent& WXUNUSED(event));
	void OnButtonCancel(wxCommandEvent& event);

private:
	wxString GetNextWord();
	bool FindNextMisSpelledWord(void);

public:
	enum
	{
		wxID_DIALOG_SPELL_CHECK = wxID_HIGHEST + 1900,
		wxID_LISTBOX_SUGGEST,
		wxID_TEXTCTRL_MIS_SPELLED,
		wxID_TEXTCTRL_REPLACE_WITH,
		wxID_BUTTON_IGNORE,
		wxID_BUTTON_IGNORE_ALL,
		wxID_BUTTON_ADD,
		wxID_BUTTON_REPLACE,
		wxID_BUTTON_REPLACE_ALL,
		wxID_BUTTON_CHECK_WORD
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
