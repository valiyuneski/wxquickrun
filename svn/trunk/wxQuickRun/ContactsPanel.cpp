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
 *	\file ContactsPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 31 Jun, 2006
 **/

#include "ContactsPanel.h"
#include "AddContactDialog.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CContactsPanel, wxPanel)
	EVT_CLOSE(CContactsPanel::OnClose)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_ADD, CContactsPanel::OnAddContact)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_EDIT, CContactsPanel::OnEditContact)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_DELETE, CContactsPanel::OnDeleteContact)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_IMPORT, CContactsPanel::OnImportContact)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_EXPORT, CContactsPanel::OnExportContact)
	EVT_TEXT(wxID_TEXTCTRL_SEARCH_CONTACTS, CContactsPanel::OnTextSearchChange)
	EVT_BUTTON(wxID_BUTTON_SEARCH_CONTACTS, CContactsPanel::OnSearchContact)
END_EVENT_TABLE()

CContactsPanel::CContactsPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
, m_pContactsListCtrl(NULL)
, m_pButtonAdd(NULL)
, m_pButtonEdit(NULL)
, m_pButtonDelete(NULL)
, m_pButtonImport(NULL)
, m_pButtonExport(NULL)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
}

CContactsPanel::~CContactsPanel(void)
{
}

void CContactsPanel::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CContactsPanel::CreateGUIControls()
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pContactsListCtrl = new wxListCtrl(this, wxID_LISTCTRL_CONTACTS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES | wxLC_SINGLE_SEL);
	m_pContactsListCtrl->InsertColumn(0, wxT("Name"), wxLIST_FORMAT_LEFT, 115);
	m_pContactsListCtrl->InsertColumn(1, wxT("Phone"), wxLIST_FORMAT_LEFT, 75);
	m_pContactsListCtrl->InsertColumn(2, wxT("IM"), wxLIST_FORMAT_LEFT, 90);
	m_pContactsListCtrl->InsertColumn(3, wxT("Mobile"), wxLIST_FORMAT_LEFT, 85);
	m_pContactsListCtrl->InsertColumn(4, wxT("Email"), wxLIST_FORMAT_LEFT, 123);

	wxBoxSizer *pSearchSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pTextCtrlSearchContacts = new wxTextCtrl(this, wxID_TEXTCTRL_SEARCH_CONTACTS, wxEmptyString);
	m_pButtonSearch = new wxButton(this, wxID_BUTTON_SEARCH_CONTACTS, wxT("&Search"));
	pSearchSizer->Add(m_pTextCtrlSearchContacts, 1, wxALL | wxEXPAND, 5);
	pSearchSizer->Add(m_pButtonSearch, 0, wxALL | wxEXPAND, 5);
	
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_KEYWORD_ADD, wxT("&Add"));
	m_pButtonEdit = new wxButton(this, wxID_BUTTON_KEYWORD_EDIT, wxT("&Edit"));
	m_pButtonDelete = new wxButton(this, wxID_BUTTON_KEYWORD_DELETE, wxT("&Delete"));
	m_pButtonImport = new wxButton(this, wxID_BUTTON_KEYWORD_IMPORT, wxT("&Import"));
	m_pButtonExport = new wxButton(this, wxID_BUTTON_KEYWORD_EXPORT, wxT("&Export"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonAdd, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonEdit, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonDelete, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonImport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonExport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(pSearchSizer, 0, wxALL | wxEXPAND, 0);
	pMainSizer->Add(m_pContactsListCtrl, 1, wxALL | wxEXPAND, 0);
	pMainSizer->Add(pButtonSizer, 0, wxALL | wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	m_pButtonImport->Disable();
	m_pButtonExport->Disable();
	FillContactsList();
}

void CContactsPanel::FillContactsList(void)
{
	m_pContactsListCtrl->DeleteAllItems();
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("users")))
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT ID, nickName from users"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		int nIndex = 0;
		while(result.NextRow())
		{
			wxString strName;
			wxString strEmail;
			wxString strPhone;
			wxString strMobile;
			wxString strIM;
			strName = wxString::Format(wxT("%s"), result.GetString(1));
			sqlCmd = wxString::Format(wxT("SELECT emailAddress from email WHERE userID = %d LIMIT 1"), result.GetInt(0));
			wxSQLite3ResultSet emailResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(emailResult.NextRow())
				strEmail = emailResult.GetString(0);
			sqlCmd = wxString::Format(wxT("SELECT phoneNumber from telephone WHERE type = 'Mobile' AND userID = %d LIMIT 1"), result.GetInt(0));
			wxSQLite3ResultSet mobileResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(mobileResult.NextRow())
				strMobile = mobileResult.GetString(0);
			sqlCmd = wxString::Format(wxT("SELECT phoneNumber from telephone WHERE phoneNumber <> '%s' AND userID = %d LIMIT 1"), strMobile, result.GetInt(0));
			wxSQLite3ResultSet phoneResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(phoneResult.NextRow())
				strPhone = phoneResult.GetString(0);
			sqlCmd = wxString::Format(wxT("SELECT IMAddress from IM WHERE userID = %d LIMIT 1"), result.GetInt(0));
			wxSQLite3ResultSet IMResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(IMResult.NextRow())
				strIM = IMResult.GetString(0);
			m_pContactsListCtrl->InsertItem(nIndex, strName);
			m_pContactsListCtrl->SetItem(nIndex, 1, strPhone);
			m_pContactsListCtrl->SetItem(nIndex, 2, strIM);
			m_pContactsListCtrl->SetItem(nIndex, 3, strMobile);
			m_pContactsListCtrl->SetItem(nIndex, 4, strEmail);
			nIndex++;
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CContactsPanel::OnAddContact(wxCommandEvent &event)
{
	CAddContactDialog dlgAddContact(this, wxID_DIALOG_ADD_CONTACT);
	if(dlgAddContact.ShowModal()==wxID_OK)
	{
		FillContactsList();
	}
	event.Skip(false);
}

void CContactsPanel::OnEditContact(wxCommandEvent &event)
{
	long item = -1;
	item = m_pContactsListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		CAddContactDialog dlgAddContact(this, wxID_DIALOG_ADD_CONTACT);
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		int nID = -1;
		if(wxSQLiteDB->TableExists(wxT("users")))
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT ID FROM users WHERE nickName = '%s'"), m_pContactsListCtrl->GetItemText(item));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				nID = result.GetInt(0);
			}
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		dlgAddContact.SetEditMode( nID );
		if(dlgAddContact.ShowModal()==wxID_OK)
		{
			FillContactsList();
		}
	}
	event.Skip(false);
}

void CContactsPanel::OnDeleteContact(wxCommandEvent &event)
{
	long item = -1;
	item = m_pContactsListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		wxString strNickName = m_pContactsListCtrl->GetItemText(item);
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("users")))
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT ID FROM users WHERE nickName = '%s'"), strNickName);
			int nID = 0;
			
			{
				wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
				if(result.NextRow())
				{
					nID = result.GetInt(0);
				}
			}
			
			sqlCmd = wxString::Format(wxT("DELETE FROM users WHERE nickName = '%s'"), strNickName);
			wxSQLiteDB->ExecuteUpdate(sqlCmd);

			sqlCmd = wxString::Format(wxT("DELETE FROM email WHERE userID = %d"), nID);
			wxSQLiteDB->ExecuteUpdate(sqlCmd);

			sqlCmd = wxString::Format(wxT("DELETE FROM telephone WHERE userID = %d"), nID);
			wxSQLiteDB->ExecuteUpdate(sqlCmd);

			sqlCmd = wxString::Format(wxT("DELETE FROM IM WHERE userID = %d"), nID);
			wxSQLiteDB->ExecuteUpdate(sqlCmd);
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		m_pContactsListCtrl->DeleteItem(item);
	}
	event.Skip(false);
}

void CContactsPanel::OnImportContact(wxCommandEvent &event)
{
	event.Skip(false);
}

void CContactsPanel::OnExportContact(wxCommandEvent &event)
{
	event.Skip(false);
}

void CContactsPanel::OnTextSearchChange(wxCommandEvent &event)
{
	event.Skip(false);
}

void CContactsPanel::OnSearchContact(wxCommandEvent &event)
{
	if(m_pTextCtrlSearchContacts->GetValue().Length()==0)
	{
		FillContactsList();
	}
	else
	{
		m_pContactsListCtrl->DeleteAllItems();
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("users")))
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT ID, nickName from users WHERE nickName LIKE '%s%%'"), m_pTextCtrlSearchContacts->GetValue());
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			int nIndex = 0;
			while(result.NextRow())
			{
				wxString strName;
				wxString strEmail;
				wxString strPhone;
				wxString strMobile;
				wxString strIM;
				strName = wxString::Format(wxT("%s"), result.GetString(1));
				sqlCmd = wxString::Format(wxT("SELECT emailAddress from email WHERE userID = %d LIMIT 1"), result.GetInt(0));
				wxSQLite3ResultSet emailResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				if(emailResult.NextRow())
					strEmail = emailResult.GetString(0);
				sqlCmd = wxString::Format(wxT("SELECT phoneNumber from telephone WHERE type = 'Mobile' AND userID = %d LIMIT 1"), result.GetInt(0));
				wxSQLite3ResultSet mobileResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				if(mobileResult.NextRow())
					strMobile = mobileResult.GetString(0);
				sqlCmd = wxString::Format(wxT("SELECT phoneNumber from telephone WHERE phoneNumber <> '%s' AND userID = %d LIMIT 1"), strMobile, result.GetInt(0));
				wxSQLite3ResultSet phoneResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				if(phoneResult.NextRow())
					strPhone = phoneResult.GetString(0);
				sqlCmd = wxString::Format(wxT("SELECT IMAddress from IM WHERE userID = %d LIMIT 1"), result.GetInt(0));
				wxSQLite3ResultSet IMResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				if(IMResult.NextRow())
					strIM = IMResult.GetString(0);
				m_pContactsListCtrl->InsertItem(nIndex, strName);
				m_pContactsListCtrl->SetItem(nIndex, 1, strPhone);
				m_pContactsListCtrl->SetItem(nIndex, 2, strIM);
				m_pContactsListCtrl->SetItem(nIndex, 3, strMobile);
				m_pContactsListCtrl->SetItem(nIndex, 4, strEmail);
				nIndex++;
			}
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
	}
	event.Skip(false);
}