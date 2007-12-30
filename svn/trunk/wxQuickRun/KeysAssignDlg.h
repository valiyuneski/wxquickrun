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
 *	\file KeysAssignDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 13 Feb, 2007
 **/
#pragma once
#include "stdwx.h"
#include <wx/combobox.h>
#include "KeyInputCtrl.h"

class CKeysAssignDlg : public wxDialog
{
public:
	CKeysAssignDlg(wxWindow* parent, wxWindowID id = CKeysAssignDlg::wxID_DIALOG_KEYS_ASSIGN, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, const wxString& name = wxT("dialogBox"));
	virtual ~CKeysAssignDlg(void);
	static void AssignDefaultHotKey(void);
	static void GetCommandHotKey(wxString strKey, int &nVirtualKey, int &nModifier);
	static int GetModifier(wxString strModifier);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent &event);
	void GetKeyBindingsFromDB(void);
	void SaveKeyBindingsToDB(void);
	static void SaveRowToDB(wxString strKey, int nModifier, int nVirtualCode);
	bool CheckForDuplicateKeyBindings(void);
	void InitControlFromDB(wxString strKey, int nModifier, int nVirtualCode);

public:
	enum
	{
		wxID_DIALOG_KEYS_ASSIGN = wxID_HIGHEST + 1950,
		wxID_STATIC_TEXT_FOCUS,
		wxID_STATIC_TEXT_ADDNOTE,
		wxID_STATIC_TEXT_PASTE_FWD,
		wxID_STATIC_TEXT_PASTE_BKWD,
		wxID_STATIC_TEXT_CLIP_COPY,
		wxID_STATIC_TEXT_CLIP_PASTE,
		wxID_STATIC_TEXT_PASTE_INC,
		wxID_STATIC_TEXT_PASTE_DEC,
		wxID_STATIC_TEXT_GB_MENU,
		wxID_STATIC_TEXT_COUNT_CHARS,
		wxID_STATIC_TEXT_UPPERCASE,
		wxID_STATIC_TEXT_LOWERCASE,
		wxID_STATIC_TEXT_TOGGLE_CASE,
		wxID_STATIC_TEXT_SENTENCE_CASE,
		wxID_STATIC_TEXT_SPELL_CHECK,
		wxID_STATIC_TEXT_CALCULATION,
		wxID_TEXTCTRL_FOCUS,
		wxID_TEXTCTRL_ADDNOTE,
		wxID_TEXTCTRL_PASTE_FWD,
		wxID_TEXTCTRL_PASTE_BKWD,
		wxID_TEXTCTRL_CLIP_COPY,
		wxID_TEXTCTRL_CLIP_PASTE,
		wxID_TEXTCTRL_PASTE_INC,
		wxID_TEXTCTRL_PASTE_DEC,
		wxID_TEXTCTRL_GB_MENU,
		wxID_TEXTCTRL_COUNT_CHARS,
		wxID_TEXTCTRL_UPPERCASE,
		wxID_TEXTCTRL_LOWERCASE,
		wxID_TEXTCTRL_TOGGLE_CASE,
		wxID_TEXTCTRL_SENTENCE_CASE,
		wxID_TEXTCTRL_SPELL_CHECK,
		wxID_TEXTCTRL_CALCULATION,
		wxID_COMBOBOX_FOCUS,
		wxID_COMBOBOX_ADDNOTE,
		wxID_COMBOBOX_PASTE_FWD,
		wxID_COMBOBOX_PASTE_BKWD,
		wxID_COMBOBOX_CLIP_COPY,
		wxID_COMBOBOX_CLIP_PASTE,
		wxID_COMBOBOX_PASTE_INC,
		wxID_COMBOBOX_PASTE_DEC,
		wxID_COMBOBOX_GB_MENU,
		wxID_COMBOBOX_COUNT_CHARS,
		wxID_COMBOBOX_UPPERCASE,
		wxID_COMBOBOX_LOWERCASE,
		wxID_COMBOBOX_TOGGLE_CASE,
		wxID_COMBOBOX_SENTENCE_CASE,
		wxID_COMBOBOX_SPELL_CHECK,
		wxID_COMBOBOX_CALCULATION
	};

private:
	wxStaticText *m_pStaticTextFocus;
	CKeyInputCtrl *m_pTextCtrlFocus;
	wxComboBox *m_pComboBoxFocus;
	wxStaticText *m_pStaticTextAddNote;
	CKeyInputCtrl *m_pTextCtrlAddNote;
	wxComboBox *m_pComboBoxAddNote;
	wxStaticText *m_pStaticTextPasteFwd;
	CKeyInputCtrl *m_pTextCtrlPasteFwd;
	wxComboBox *m_pComboBoxPasteFwd;
	wxStaticText *m_pStaticTextPasteBkwd;
	CKeyInputCtrl *m_pTextCtrlPasteBkwd;
	wxComboBox *m_pComboBoxPasteBkwd;
	wxStaticText *m_pStaticTextClipCopy;
	CKeyInputCtrl *m_pTextCtrlClipCopy;
	wxComboBox *m_pComboBoxClipCopy;
	wxStaticText *m_pStaticTextClipPaste;
	CKeyInputCtrl *m_pTextCtrlClipPaste;
	wxComboBox *m_pComboBoxClipPaste;
	wxStaticText *m_pStaticTextPasteInc;
	CKeyInputCtrl *m_pTextCtrlPasteInc;
	wxComboBox *m_pComboBoxPasteInc;
	wxStaticText *m_pStaticTextPasteDec;
	CKeyInputCtrl *m_pTextCtrlPasteDec;
	wxComboBox *m_pComboBoxPasteDec;
	wxStaticText *m_pStaticTextGbMenu;
	CKeyInputCtrl *m_pTextCtrlGbMenu;
	wxComboBox *m_pComboBoxGbMenu;
	wxStaticText *m_pStaticTextCountChars;
	CKeyInputCtrl *m_pTextCtrlCountChars;
	wxComboBox *m_pComboBoxCountChars;
	wxStaticText *m_pStaticTextUpperCase;
	CKeyInputCtrl *m_pTextCtrlUpperCase;
	wxComboBox *m_pComboBoxUpperCase;
	wxStaticText *m_pStaticTextLowerCase;
	CKeyInputCtrl *m_pTextCtrlLowerCase;
	wxComboBox *m_pComboBoxLowerCase;
	wxStaticText *m_pStaticTextToogleCase;
	CKeyInputCtrl *m_pTextCtrlToogleCase;
	wxComboBox *m_pComboBoxToogleCase;
	wxStaticText *m_pStaticTextSentenceCase;
	CKeyInputCtrl *m_pTextCtrlSentenceCase;
	wxComboBox *m_pComboBoxSentenceCase;
	wxStaticText *m_pStaticTextCheckSpell;
	CKeyInputCtrl *m_pTextCtrlCheckSpell;
	wxComboBox *m_pComboBoxCheckSpell;
	wxStaticText *m_pStaticTextCalculation;
	CKeyInputCtrl *m_pTextCtrlCalculation;
	wxComboBox *m_pComboBoxCalculation;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};

