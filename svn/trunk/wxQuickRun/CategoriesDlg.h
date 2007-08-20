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
 *	\file CategoriesDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 14 Sep, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/listbox.h>

class CCategoriesDlg : public wxDialog
{
private:
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonRemove;
	wxListBox *m_pListBoxCategories;

public:
	CCategoriesDlg(wxWindow* parent, wxWindowID id = CCategoriesDlg::wxID_DIALOG_CATEGORIES, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(200, 350), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Categories Dialog"));
	virtual ~CCategoriesDlg(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnAddButton(wxCommandEvent& event);
	void OnRemoveButton(wxCommandEvent& event);

	void FillTaskCategories(void);

public:
	enum 
	{
		wxID_DIALOG_CATEGORIES = wxID_HIGHEST + 1600,
		wxID_BUTTON_ADD,
		wxID_BUTTON_REMOVE,
		wxID_LISTBOX_CATEGORIES
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};