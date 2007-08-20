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
 *	\file SearchEntryDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Nov, 2006
 **/

#pragma once
#include "stdwx.h"

class CSearchEntryDlg :	public wxDialog
{
private:
	wxString m_strEngineName;
	wxString m_strEngineURL;
	wxTextCtrl *m_pTextCtrlEngineName;
	wxTextCtrl *m_pTextCtrlEngineURL;
	bool m_bEditMode;

public:
	CSearchEntryDlg(wxWindow* parent, wxWindowID id = CSearchEntryDlg::wxID_DIALOG_SEARCH_ENGINE_ENTRY, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(450, 190), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Search Engine Entry Dialog"));
	virtual ~CSearchEntryDlg(void);

	wxString GetSearchEngineName(void);
	void SetSearchEngineName(wxString);
	wxString GetSearchEngineURL(void);
	void SetSearchEngineURL(wxString);
	bool IsEditMode(void);
	void SetEditMode(bool bEditMode);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent& event);

public:
	enum 
	{
		wxID_DIALOG_SEARCH_ENGINE_ENTRY = wxID_HIGHEST + 1850,
		wxID_TEXTCTRL_ENGINE_NAME,
		wxID_TEXTCTRL_ENGINE_URL
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
