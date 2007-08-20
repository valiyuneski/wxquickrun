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
 *	\file AddContactDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 31 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/wxFlatNotebook/wxFlatNotebook.h>
#include "PrimaryDetailsPanel.h"

class CAddContactDialog : public wxDialog
{
private:
	int m_nEditContact;
	wxFlatNotebook *m_pFlatNotebook;
	CPrimaryDetailsPanel *m_pPrimaryDetailsPanel;

public:
	CAddContactDialog(wxWindow* parent, wxWindowID id, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 460), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Add Contact Dialog"));
	virtual ~CAddContactDialog(void);
	void SetEditMode(int nEditContact);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent& event);
	int AddUserInfo(void);
	void AddUserEmail(int nID);
	void AddUserTelephone(int nID);
	void AddUserIM(int nID);

public:
	enum 
	{
		wxID_DIALOG_ADD_CONTACT = wxID_HIGHEST + 1400,
		wxID_NOTEBOOK_FLAT_CONTACT
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};