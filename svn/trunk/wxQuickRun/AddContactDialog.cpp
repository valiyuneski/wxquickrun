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
 *	\file AddContactDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 31 Jun, 2006
 **/

#include "AddContactDialog.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CAddContactDialog, wxDialog)
	EVT_CLOSE(CAddContactDialog::OnClose)
	EVT_BUTTON(wxID_OK, CAddContactDialog::OnOK)
	EVT_INIT_DIALOG(CAddContactDialog::OnInitDialog)
END_EVENT_TABLE()

CAddContactDialog::CAddContactDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pPrimaryDetailsPanel(NULL)
, m_nEditContact(-1)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CAddContactDialog::~CAddContactDialog(void)
{
}

void CAddContactDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CAddContactDialog::OnInitDialog(wxInitDialogEvent& WXUNUSED(event))
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pFlatNotebook = new wxFlatNotebook(this, wxID_NOTEBOOK_FLAT_CONTACT, wxDefaultPosition, wxDefaultSize, wxFNB_TABS_BORDER_SIMPLE | wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG);
	m_pPrimaryDetailsPanel = new CPrimaryDetailsPanel(m_pFlatNotebook, CPrimaryDetailsPanel::wxID_PANEL_PRIMARY_DETAILS, m_nEditContact);
	m_pFlatNotebook->AddPage(m_pPrimaryDetailsPanel, wxT("Contact"), true);
	pMainSizer->Add(m_pFlatNotebook, 1, wxALL | wxEXPAND, 0);

	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	
	if(m_nEditContact != -1)
	{
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("users")))
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT ID, title, firstName, middleName, lastName, suffix, nickName from users WHERE ID = %d"), m_nEditContact);
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				m_pPrimaryDetailsPanel->SetTitle(result.GetString(1));
				m_pPrimaryDetailsPanel->SetFirstName(result.GetString(2));
				m_pPrimaryDetailsPanel->SetMiddleName(result.GetString(3));
				m_pPrimaryDetailsPanel->SetLastName(result.GetString(4));
				m_pPrimaryDetailsPanel->SetSuffix(result.GetString(5));
				m_pPrimaryDetailsPanel->SetNickName(result.GetString(6));

				int nIndex = 0;
				sqlCmd = wxString::Format(wxT("SELECT type, emailAddress from email WHERE userID = %d"), result.GetInt(0));
				wxSQLite3ResultSet emailResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				while(emailResult.NextRow() && nIndex < 2)
				{
					m_pPrimaryDetailsPanel->SetEmail(nIndex++, emailResult.GetString(0), emailResult.GetString(1));
				}

				nIndex = 0;
				sqlCmd = wxString::Format(wxT("SELECT type, phoneNumber from telephone WHERE userID = %d"), result.GetInt(0));
				wxSQLite3ResultSet mobileResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				while(mobileResult.NextRow() && nIndex < 2)
				{
					m_pPrimaryDetailsPanel->SetTelephone(nIndex++, mobileResult.GetString(0), mobileResult.GetString(1));
				}

				nIndex = 0;
				sqlCmd = wxString::Format(wxT("SELECT IMProvider, IMAddress from IM WHERE userID = %d"), result.GetInt(0));
				wxSQLite3ResultSet IMResult = wxSQLiteDB->ExecuteQuery(sqlCmd);
				while(IMResult.NextRow() && nIndex < 2)
				{
					m_pPrimaryDetailsPanel->SetIM(nIndex++, IMResult.GetString(0), IMResult.GetString(1));
				}
			}
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
	}
}

void CAddContactDialog::OnOK(wxCommandEvent& event)
{
	if(m_pPrimaryDetailsPanel->GetFullname() == wxEmptyString)
	{
		wxMessageBox(wxT("Please provide a full name."), wxT("wxQuickRun"), wxOK|wxCENTER|wxICON_STOP, this);
		return;
	}
	if(m_pPrimaryDetailsPanel->GetNickName() == wxEmptyString)
	{
		wxMessageBox(wxT("Please provide a nick name."), wxT("wxQuickRun"), wxOK|wxCENTER|wxICON_STOP, this);
		return;
	}
	wxString strEmailCategory[2];
	wxString strEmailAddress[2];
	m_pPrimaryDetailsPanel->GetEmail(0, strEmailCategory[0], strEmailAddress[0]);
	m_pPrimaryDetailsPanel->GetEmail(1, strEmailCategory[1], strEmailAddress[1]);
	if(strEmailCategory[0] == wxEmptyString || strEmailCategory[1] == wxEmptyString)
		return;
	int nIDInserted = AddUserInfo();
	if(nIDInserted < 0)
		return;
	AddUserEmail(nIDInserted);
	AddUserTelephone(nIDInserted);
	AddUserIM(nIDInserted);
	event.Skip(true);
}

void CAddContactDialog::SetEditMode(int nEditContact)
{
	m_nEditContact = nEditContact;
}

int CAddContactDialog::AddUserInfo(void)
{
	wxString strTitle = m_pPrimaryDetailsPanel->GetTitle();
	wxString strFirstName = m_pPrimaryDetailsPanel->GetFirstName();
	wxString strMiddleName = m_pPrimaryDetailsPanel->GetMiddleName();
	wxString strLastName = m_pPrimaryDetailsPanel->GetLastName();
	wxString strSuffix = m_pPrimaryDetailsPanel->GetSuffix();
	wxString strNickName = m_pPrimaryDetailsPanel->GetNickName();

	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("users")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE users(ID INTEGER PRIMARY KEY AUTOINCREMENT, title VARCHAR(16), firstName VARCHAR(128), middleName VARCHAR(128), lastName VARCHAR(128), suffix VARCHAR(32), nickName VARCHAR(64));"));
	}

	if(m_nEditContact != -1)
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT nickName from users WHERE nickName = '%s' AND ID <> %d"), strNickName.Lower(), m_nEditContact);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			wxMessageBox(wxT("The nick name has been already assigned. Please choose a different nick name."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
			m_pPrimaryDetailsPanel->SetNickNameFocus();
			wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;
			return -1;
		}
		sqlCmd = wxString::Format(wxT("DELETE FROM users WHERE ID = %d"), m_nEditContact);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT nickName from users WHERE nickName = '%s'"), strNickName);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			wxMessageBox(wxT("The nick name has been already assigned. Please choose a different nick name."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
			m_pPrimaryDetailsPanel->SetNickNameFocus();
			wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;
			return -1;
		}
	}

	wxString sqlCmd = wxString::Format(wxT("Insert INTO users('title', 'firstName', 'middleName', 'lastName', 'suffix', 'nickName') VALUES('%s', '%s', '%s', '%s', '%s', '%s')"), strTitle, strFirstName, strMiddleName, strLastName, strSuffix, strNickName.Lower());
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	int nIDInserted = 0;
	sqlCmd = wxString::Format(wxT("SELECT ID FROM users WHERE nickName = '%s'"), strNickName);
	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
	if(result.NextRow())
	{
		nIDInserted = result.GetInt(0);
	}

	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	return nIDInserted;
}

void CAddContactDialog::AddUserEmail(int nID)
{
	wxString strEmailCategory[2];
	wxString strEmailAddress[2];
	m_pPrimaryDetailsPanel->GetEmail(0, strEmailCategory[0], strEmailAddress[0]);
	m_pPrimaryDetailsPanel->GetEmail(1, strEmailCategory[1], strEmailAddress[1]);

	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("email")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE email(ID INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, type VARCHAR(32), emailAddress VARCHAR(255));"));
	}

	wxString sqlCmd = wxString::Format(wxT("DELETE FROM email WHERE userID = %d"), nID);
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	if(strEmailAddress[0] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO email('userID', 'type', 'emailAddress') VALUES(%d, '%s', '%s')"), nID, strEmailCategory[0], strEmailAddress[0]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}
	if(strEmailAddress[1] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO email('userID', 'type', 'emailAddress') VALUES(%d, '%s', '%s')"), nID, strEmailCategory[1], strEmailAddress[1]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}

	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CAddContactDialog::AddUserTelephone(int nID)
{
	wxString strPhoneCategory[2];
	wxString strPhoneNumber[2];
	m_pPrimaryDetailsPanel->GetTelephone(0, strPhoneCategory[0], strPhoneNumber[0]);
	m_pPrimaryDetailsPanel->GetTelephone(1, strPhoneCategory[1], strPhoneNumber[1]);

	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("telephone")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE telephone(ID INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, type VARCHAR(32), phoneNumber VARCHAR(32));"));
	}

	wxString sqlCmd = wxString::Format(wxT("DELETE FROM telephone WHERE userID = %d"), nID);
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	if(strPhoneNumber[0] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO telephone('userID', 'type', 'phoneNumber') VALUES(%d, '%s', '%s')"), nID, strPhoneCategory[0], strPhoneNumber[0]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}
	if(strPhoneNumber[1] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO telephone('userID', 'type', 'phoneNumber') VALUES(%d, '%s', '%s')"), nID, strPhoneCategory[1], strPhoneNumber[1]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}

	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CAddContactDialog::AddUserIM(int nID)
{
	wxString strIMProvider[2];
	wxString strIMAddress[2];
	m_pPrimaryDetailsPanel->GetIM(0, strIMProvider[0], strIMAddress[0]);
	m_pPrimaryDetailsPanel->GetIM(1, strIMProvider[1], strIMAddress[1]);

	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("IM")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE IM(ID INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, IMProvider VARCHAR(32), IMAddress VARCHAR(255));"));
	}

	wxString sqlCmd = wxString::Format(wxT("DELETE FROM IM WHERE userID = %d"), nID);
	wxSQLiteDB->ExecuteUpdate(sqlCmd);

	if(strIMAddress[0] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO IM('userID', 'IMProvider', 'IMAddress') VALUES(%d, '%s', '%s')"), nID, strIMProvider[0], strIMAddress[0]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}
	if(strIMAddress[1] != wxEmptyString)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO IM('userID', 'IMProvider', 'IMAddress') VALUES(%d, '%s', '%s')"), nID, strIMProvider[1], strIMAddress[1]);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}

	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}
