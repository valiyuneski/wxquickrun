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
 *	\file CategoriesDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 14 Sep, 2006
 **/

#include "CategoriesDlg.h"
#include "wxQuickRun.h"
#include <wx/textdlg.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CCategoriesDlg, wxDialog)
	EVT_CLOSE(CCategoriesDlg::OnClose)
	EVT_INIT_DIALOG(CCategoriesDlg::OnInitDialog)
	EVT_BUTTON(wxID_BUTTON_ADD, CCategoriesDlg::OnAddButton)
	EVT_BUTTON(wxID_BUTTON_REMOVE, CCategoriesDlg::OnRemoveButton)
END_EVENT_TABLE()

CCategoriesDlg::CCategoriesDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pButtonAdd(NULL)
, m_pButtonRemove(NULL)
, m_pListBoxCategories(NULL)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CCategoriesDlg::~CCategoriesDlg(void)
{
}

void CCategoriesDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CCategoriesDlg::OnInitDialog(wxInitDialogEvent &event)
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("&Task Categories:"));
	m_pListBoxCategories = new wxListBox(this, wxID_LISTBOX_CATEGORIES, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE | wxLB_SORT);
	pStaticBoxSizer->Add(m_pListBoxCategories, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_ADD, wxT("&Add"));
	m_pButtonRemove = new wxButton(this, wxID_BUTTON_REMOVE, wxT("&Remove"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonAdd, 3, wxALL | wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonRemove, 3, wxALL | wxEXPAND, 5);
	pButtonSizer->AddStretchSpacer(1);

	pStaticBoxSizer->Add(pButtonSizer, 0, wxALL | wxEXPAND, 5);

	pMainSizer->Add(pStaticBoxSizer, 1, wxALL | wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();

	FillTaskCategories();
}

void CCategoriesDlg::OnAddButton(wxCommandEvent& event)
{
	wxTextEntryDialog categoryTextEntryDlg(this, wxT("Please enter a unique category name:"), wxT("wxQuickRun"), wxEmptyString, wxOK | wxCANCEL | wxCENTRE);
	if(categoryTextEntryDlg.ShowModal()==wxID_OK)
	{
		wxString strCategory = categoryTextEntryDlg.GetValue();
		if(strCategory != wxEmptyString)
		{
			wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
			wxSQLiteDB->Open(DATABASE_FILE);
			if(!wxSQLiteDB->TableExists(wxT("categories")))
			{
				wxSQLiteDB->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
			}

			wxString sqlCmd = wxString::Format(wxT("SELECT ID FROM categories WHERE category = '%s'"), strCategory);
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				wxSQLiteDB->Close();
				delete wxSQLiteDB;
				wxSQLiteDB = NULL;
				wxMessageBox(wxT("The category with the particular name already exists.\nPlease choose a different and unique name."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR );
				return;
			}

			sqlCmd = wxString::Format(wxT("Insert INTO categories('category') VALUES(?)"));
			wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.Bind(1, strCategory);
			// Execute the SQL Query
			stmt.ExecuteUpdate();

			wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;

			FillTaskCategories();
		}
	}
	event.Skip(false);
}

void CCategoriesDlg::OnRemoveButton(wxCommandEvent& event)
{
	wxString strRemoveCategory = m_pListBoxCategories->GetStringSelection();
	if(strRemoveCategory != wxEmptyString)
	{
		if(wxMessageBox(wxT("This will remove the category and all the tasks associated with it.\nDo you want to continue?."), wxT("wxQuickRun"), wxYES_NO | wxCENTRE | wxICON_QUESTION ) != wxYES)
			return;
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		
		if(!wxSQLiteDB->TableExists(wxT("categories")))
		{
			wxSQLiteDB->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
		}
		else
		{
			wxString sqlCmd = wxString::Format(wxT("DELETE FROM categories WHERE category = '%s'"), strRemoveCategory);
			wxSQLiteDB->ExecuteQuery(sqlCmd);
		}
		if(!wxSQLiteDB->TableExists(wxT("tasks")))
		{
			wxSQLiteDB->ExecuteUpdate(wxT("create table tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, subject VARCHAR(255), category VARCHAR(64), status NUMERIC(1,0), priority NUMERIC(1,0), completion NUMERIC(3,0), startTime TIMESTAMP, endTime TIMESTAMP, reminderTime TIMESTAMP, reminder BOOLEAN, description TEXT);"));
		}
		else
		{
			wxString sqlCmd = wxString::Format(wxT("DELETE FROM tasks WHERE category = '%s'"), strRemoveCategory);
			wxSQLiteDB->ExecuteQuery(sqlCmd);
		}

		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;

		FillTaskCategories();
	}
	event.Skip(false);
}

void CCategoriesDlg::FillTaskCategories(void)
{
	m_pListBoxCategories->Clear();
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("categories")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT category FROM categories"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			m_pListBoxCategories->Append(result.GetString(0));
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}