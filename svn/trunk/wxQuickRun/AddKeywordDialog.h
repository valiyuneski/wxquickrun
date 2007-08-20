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
 *	\file AddKeywordDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "stdwx.h"

class CAddKeywordDialog : public wxDialog
{
private:
	wxStaticText *m_pStaticKeyword;
	wxStaticText *m_pStaticExecFile;
	wxStaticText *m_pStaticParameters;
	wxStaticText *m_pStaticStartUpPath;
	wxStaticText *m_pStaticNotes;
	wxTextCtrl *m_pTextCtrlKeyword;
	wxTextCtrl *m_pTextCtrlExecFile;
	wxTextCtrl *m_pTextCtrlParameters;
	wxTextCtrl *m_pTextCtrlStartUpPath;
	wxTextCtrl *m_pTextCtrlNotes;
	wxButton *m_pButtonFileDialog;
	wxString m_strEditKeyword;

public:
	CAddKeywordDialog(wxWindow* parent, wxWindowID id, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 275), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Add Keyword Dialog"));
	virtual ~CAddKeywordDialog(void);
	void SetEditMode(wxString strEditKeyword);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent& event);
	void OnButtonFileDialog(wxCommandEvent& WXUNUSED(event));
	void FillDialog();

public:
	enum 
	{
		wxID_DIALOG_ADD_KEYWORD = wxID_HIGHEST + 450,
		wxID_STATIC_TEXT_KEYWORD,
		wxID_STATIC_TEXT_EXEC_FILE,
		wxID_STATIC_TEXT_PARAMETERS,
		wxID_STATIC_TEXT_STARTUP_PATH,
		wxID_STATIC_TEXT_NOTES,
		wxID_TEXTCTRL_KEYWORD,
		wxID_TEXTCTRL_EXEC_FILE,
		wxID_TEXTCTRL_PARAMETERS,
		wxID_TEXTCTRL_STARTUP_PATH,
		wxID_TEXTCTRL_NOTES,
		wxID_BUTTON_FILE_DIALOG
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
