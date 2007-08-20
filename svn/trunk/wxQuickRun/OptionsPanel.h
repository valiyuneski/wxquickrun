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
 *	\file OptionsPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 3 Jul, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/fontdlg.h>
#include <wx/colordlg.h>
#include "ColorBox.h"
#include "DownloadFile.h"

class COptionsPanel : public wxPanel
{
public:
	COptionsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Panel"));
	virtual ~COptionsPanel(void);

	//static wxString GetExecutablePath();

private:
	void CreateGUIControls();

	//void OnFontButton(wxCommandEvent &event);
	//void OnBackColorButton(wxCommandEvent &event);
	void OnApplyButton(wxCommandEvent &event);
	void OnCheckForLatestVersion(wxCommandEvent &event);
	void OnDonate(wxCommandEvent &event);
	void OnSelectLanguage(wxCommandEvent &event);
	void OnDownloadEvent(wxDownloadEvent &event);
	void OnSearchEngineButton(wxCommandEvent &event);
	void OnKeysAssignmentButton(wxCommandEvent &event);

	//int GetVirtualKeyCode(wxChar ch);
	//wxChar GetCharFromKeyCode(int nKeyCode);
	int CountSearchEngine(void);

private:
	//wxStaticText *m_pStaticFont;
	//wxStaticText *m_pStaticFontName;
	wxStaticText *m_pStaticSelectLang;
	wxStaticText *m_pStaticSelectedLang;
	wxStaticText *m_pStaticClipboardIndex;
	wxComboBox *m_pComboClipboardIndex;
	wxButton *m_pButtonSelectLang;
	wxButton *m_pButtonSearchEngine;
	wxButton *m_pButtonKeysAssign;
	wxButton *m_pButtonFont;
	//wxStaticText *m_pTimeFormat;
	//wxComboBox *m_pComboTimeFormat;
	wxStaticText *m_pStaticBackColor;
	wxColorBox *m_pColorBoxBackColor;
	wxButton *m_pButtonBackColor;
	wxStaticText *m_pStaticTransparency;
	wxSpinCtrl *m_pSpinCtrlTransparency;
	wxButton *m_pButtonApply;
	wxButton *m_pButtonCancel;
	wxCheckBox *m_pCheckBoxAutoStart;
	wxCheckBox *m_pCheckBoxVirtualClipboard;
	//wxFontData m_FontData;
	//wxColourData m_ColorData;
	//wxStaticText *m_pStaticTextHotKey;
	//wxTextCtrl* m_pTextCtrlHotKey;
	//wxComboBox *m_pComboHotKey;
	wxButton *m_pButtonCheckLatestVer;
	wxButton *m_pButtonDonate;
	wxDownloadFile *m_pDownloadFile;

	enum
	{
		//wxID_STATIC_TEXT_FONT
		//wxID_STATIC_TEXT_FONT_NAME,
		//wxID_BUTTON_FONT,
		//wxID_STATIC_TEXT_TIME_FORMAT,
		//wxID_COMBOBOX_TIME_FORMAT,
		wxID_STATIC_TEXT_BACK_COLOR = wxID_HIGHEST + 1200,
		wxID_COLOR_BOX_BACK_COLOR,
		wxID_BUTTON_BACK_COLOR,
		wxID_STATIC_TEXT_TRANSPARENCY,
		wxID_SPINCTRL_TRANSPARENCY,
		wxID_CHECKBOX_AUTO_START,
		wxID_CHECKBOX_VIRTUAL_CLIPBOARD,
		wxID_BUTTON_CHECK_LATEST_VER,
		wxID_BUTTON_DONATE,
		//wxID_STATIC_TEXT_HOT_KEY,
		//wxID_TEXTCTRL_HOT_KEY,
		//wxID_COMBOBOX_HOT_KEY,
		wxID_STATIC_TEXT_SELECT_LANG,
		wxID_STATIC_TEXT_SELECTED_LANG,
		wxID_BUTTON_SELECT_LANG,
		wxID_STATIC_TEXT_CLIPBOARD_INDEX,
		wxID_COMBOBOX_CLIPBOARD_INDEX,
		wxID_BUTTON_SEARCH_ENGINE,
		wxID_BUTTON_KEYS_ASSIGN
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
