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
 *	\file CParametersDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 29 March, 2007
 **/

#include "ParametersDlg.h"
#include "wxQuickRun.h"
#include <wx/sizer.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(CParametersDlg, wxDialog)

BEGIN_EVENT_TABLE(CParametersDlg, wxDialog)
	EVT_BUTTON(wxID_OK, OnButtonOK)
	EVT_INIT_DIALOG(OnInitDialog)
END_EVENT_TABLE()

CParametersDlg::CParametersDlg(void)
: m_pComboBoxParam(NULL)
, m_nCommandID(0)
{
}

CParametersDlg::CParametersDlg(wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
{
}

CParametersDlg::~CParametersDlg(void)
{
}

void CParametersDlg::OnButtonOK(wxCommandEvent &event)
{
	m_strParameters = m_pComboBoxParam->GetValue();
	SaveParamToDatabase(m_strParameters);
	event.Skip(true);
}

void CParametersDlg::OnInitDialog(wxInitDialogEvent &event)
{
	SetIcon(wxICON(IDI_ICON_APPICON));
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Command Parameter"));
	m_pComboBoxParam = new wxComboBox(this, wxID_COMBOBOX_PARAM, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxArrayString(), wxCB_DROPDOWN, wxDefaultValidator, wxT("comboBox"));
	m_pComboBoxParam->SetMinSize(wxSize(300, 12));
	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);
	pStaticBoxSizer->Add(m_pComboBoxParam, 1, wxEXPAND | wxALL, 10);
	pStaticBoxSizer->Add(pButtonSizer, 0, wxEXPAND | wxALL, 10);
	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Fit();
	Layout();
	AddSavedParamsToComboBox();
	m_pComboBoxParam->SetFocus();
}

wxString CParametersDlg::GetParameter(void)
{
	return m_strParameters;
}

void CParametersDlg::SetCommandID(int nCommandID)
{
	m_nCommandID = nCommandID;
}

void CParametersDlg::AddSavedParamsToComboBox(void)
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("parameters")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE parameters(ID INTEGER PRIMARY KEY AUTOINCREMENT, commandID INTEGER, param VARCHAR(255), lastused TIMESTAMP);"));
	}
	else
	{
		try
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT param FROM parameters WHERE commandID = %d ORDER BY lastused DESC"), m_nCommandID);
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			while(result.NextRow())
			{
				m_pComboBoxParam->Append(result.GetString(0));
			}
			if(m_pComboBoxParam->GetCount() > 0)
				m_pComboBoxParam->SetSelection(0);
		}
		catch (	wxSQLite3Exception *e)
		{
			wxMessageBox(e->GetMessage());
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CParametersDlg::SaveParamToDatabase(wxString strParam)
{
	if(strParam == wxEmptyString)
		return;
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("parameters")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE parameters(ID INTEGER PRIMARY KEY AUTOINCREMENT, commandID INTEGER, param VARCHAR(255), lastused TIMESTAMP);"));
	}
	wxString strEscapedParam(strParam);
	strEscapedParam.Replace(wxT("'"), wxT("''"));
	wxString sqlCmd = wxString::Format(wxT("select COUNT(ID) from parameters WHERE commandID = %d AND param = '%s'"), m_nCommandID, strEscapedParam);
	if(wxSQLiteDB->ExecuteScalar(sqlCmd) == 0)
	{
		sqlCmd = wxString::Format(wxT("Insert INTO parameters('commandID', 'param', 'lastused') VALUES (%d, ?, ?)"), m_nCommandID);
		wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
		stmt.Bind(1, strParam);
		stmt.BindTimestamp(2, wxDateTime::Now());
		stmt.ExecuteUpdate();
	}
	else
	{
		sqlCmd = wxString::Format(wxT("Update parameters SET lastused = ? WHERE commandID = %d AND param = ?"), m_nCommandID);
		wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
		stmt.BindTimestamp(1, wxDateTime::Now());
		stmt.Bind(2, strParam);
		stmt.ExecuteUpdate();
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	RemoveOldestParameter();
}

void CParametersDlg::RemoveOldestParameter(void)
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("parameters")))
	{
		wxString sqlCmd = wxString::Format(wxT("select COUNT(ID) from parameters WHERE commandID = %d"), m_nCommandID);
		if(wxSQLiteDB->ExecuteScalar(sqlCmd)>20)
		{
			sqlCmd = wxString::Format(wxT("select ID from parameters WHERE commandID = %d ORDER BY lastused LIMIT 1"), m_nCommandID);
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				sqlCmd = wxString::Format(wxT("DELETE FROM parameters WHERE ID = %d"), result.GetInt(0));
				result.Finalize();
				wxSQLiteDB->ExecuteQuery(sqlCmd);
			}
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}
