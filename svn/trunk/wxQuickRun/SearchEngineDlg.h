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
 *	\file SearchEngineDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Nov, 2006
 **/
#pragma once
#include "stdwx.h"
#include <wx/listctrl.h>

class CSearchEngineDlg : public wxDialog
{
private:
	wxListCtrl *m_pListCtrlSearchEngine;
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonEdit;
	wxButton *m_pButtonDelete;

public:
	CSearchEngineDlg(wxWindow* parent, wxWindowID id = CSearchEngineDlg::wxID_DIALOG_SEARCH_ENGINE, const wxString& title = wxT("Manage Search Engines"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(470, 300), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Search Engine Dialog"));
	virtual ~CSearchEngineDlg(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnAddButton(wxCommandEvent &event);
	void OnEditButton(wxCommandEvent &event);
	void OnDeleteButton(wxCommandEvent &event);
	void OnSize(wxSizeEvent &event);

	wxString GetTextByColumn(long nIndex, int nCol);
	void FillSearchEnginesList(void);

public:
	enum 
	{
		wxID_DIALOG_SEARCH_ENGINE = wxID_HIGHEST + 1800,
		wxID_LISTCTRL_SEARCH_ENGINE,
		wxID_BUTTON_ADD,
		wxID_BUTTON_EDIT,
		wxID_BUTTON_DELETE
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
