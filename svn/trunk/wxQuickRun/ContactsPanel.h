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
 *	\file ContactsPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 31 Jul, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/listctrl.h>

class CContactsPanel : public wxPanel
{
public:
	CContactsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Contacts Panel"));
	virtual ~CContactsPanel(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnAddContact(wxCommandEvent &event);
	void OnEditContact(wxCommandEvent &event);
	void OnDeleteContact(wxCommandEvent &event);
	void OnImportContact(wxCommandEvent &event);
	void OnExportContact(wxCommandEvent &event);
	void OnTextSearchChange(wxCommandEvent &event);
	void OnSearchContact(wxCommandEvent &event);
	void CreateGUIControls(void);
	void FillContactsList(void);

private:
	wxListCtrl *m_pContactsListCtrl;
	wxTextCtrl *m_pTextCtrlSearchContacts;
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonEdit;
	wxButton *m_pButtonDelete;
	wxButton *m_pButtonImport;
	wxButton *m_pButtonExport;
	wxButton *m_pButtonSearch;

public:
	enum
	{
		wxID_LISTCTRL_CONTACTS = wxID_HIGHEST + 1475,
		wxID_BUTTON_KEYWORD_ADD,
		wxID_BUTTON_KEYWORD_EDIT,
		wxID_BUTTON_KEYWORD_DELETE,
		wxID_BUTTON_KEYWORD_IMPORT,
		wxID_BUTTON_KEYWORD_EXPORT,
		wxID_TEXTCTRL_SEARCH_CONTACTS,
		wxID_BUTTON_SEARCH_CONTACTS,
		wxID_DIALOG_ADD_CONTACT
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
