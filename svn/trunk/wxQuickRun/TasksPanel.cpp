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
 *	\file TasksPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#include "TasksPanel.h"
#include "AddTaskDialog.h"
#include "CategoriesDlg.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CTasksPanel, wxPanel)
	EVT_CLOSE(CTasksPanel::OnClose)
	EVT_BUTTON(wxID_BUTTON_TASK_ADD, CTasksPanel::OnAddTask)
	EVT_BUTTON(wxID_BUTTON_TASK_EDIT, CTasksPanel::OnEditTask)
	EVT_BUTTON(wxID_BUTTON_TASK_DELETE, CTasksPanel::OnDeleteTask)
	EVT_BUTTON(wxID_BUTTON_TASK_IMPORT, CTasksPanel::OnImportTask)
	EVT_BUTTON(wxID_BUTTON_TASK_EXPORT, CTasksPanel::OnExportTask)
	EVT_COMBOBOX(wxID_COMBOBOX_CATEGORY, CTasksPanel::OnCategoryChange)
	EVT_BUTTON(wxID_BUTTON_CATEGORY, CTasksPanel::OnManageCategories)
	EVT_LIST_ITEM_CHECKED(wxID_LISTCTRL_TASKS, CTasksPanel::OnItemChecked)
	EVT_LIST_ITEM_UNCHECKED(wxID_LISTCTRL_TASKS, CTasksPanel::OnItemUnChecked)
	EVT_SIZE(CTasksPanel::OnSize)
END_EVENT_TABLE()

CTasksPanel::CTasksPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
, m_pTasksListCtrl(NULL)
, m_pButtonAdd(NULL)
, m_pButtonEdit(NULL)
, m_pButtonDelete(NULL)
, m_pButtonImport(NULL)
, m_pButtonExport(NULL)
, m_pStaticTextCategory(NULL)
, m_pComboCategory(NULL)
, m_pButtonCategory(NULL)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
}

CTasksPanel::~CTasksPanel(void)
{
}

void CTasksPanel::OnClose(wxCloseEvent &event)
{
	MarkCheckedAsComplete();
	event.Skip(true);
}

void CTasksPanel::CreateGUIControls()
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pTasksListCtrl = new wxCheckedListCtrl(this, wxID_LISTCTRL_TASKS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES | wxLC_NO_HEADER | wxCLC_CHECK_WHEN_SELECTING);

	wxBoxSizer *pCategorySizer = new wxBoxSizer(wxHORIZONTAL);

	wxArrayString arrayCategory;

	m_pButtonCategory = new wxButton(this, wxID_BUTTON_CATEGORY, wxT("&Manage Categories"));
	m_pStaticTextCategory = new wxStaticText(this, wxID_STATIC_TEXT_CATEGORY, wxT("&Category:"));
	if(arrayCategory.Count())
		m_pComboCategory = new wxComboBox(this, wxID_COMBOBOX_CATEGORY, arrayCategory.Item(0), wxDefaultPosition, wxDefaultSize, arrayCategory, wxCB_READONLY);
	else
		m_pComboCategory = new wxComboBox(this, wxID_COMBOBOX_CATEGORY, wxEmptyString, wxDefaultPosition, wxDefaultSize, arrayCategory, wxCB_READONLY);
	pCategorySizer->Add(m_pButtonCategory, 1, wxALL | wxEXPAND, 5);
	pCategorySizer->AddStretchSpacer(1);
	pCategorySizer->Add(m_pStaticTextCategory, 0, wxALL | wxEXPAND, 5);
	pCategorySizer->Add(m_pComboCategory, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_TASK_ADD, wxT("&Add"));
	m_pButtonEdit = new wxButton(this, wxID_BUTTON_TASK_EDIT, wxT("&Edit"));
	m_pButtonDelete = new wxButton(this, wxID_BUTTON_TASK_DELETE, wxT("&Delete"));
	m_pButtonImport = new wxButton(this, wxID_BUTTON_TASK_IMPORT, wxT("&Import"));
	m_pButtonExport = new wxButton(this, wxID_BUTTON_TASK_EXPORT, wxT("&Export"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonAdd, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonEdit, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonDelete, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonImport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonExport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(pCategorySizer, 0, wxALL | wxEXPAND, 0);
	pMainSizer->Add(m_pTasksListCtrl, 1, wxALL | wxEXPAND, 0);
	pMainSizer->Add(pButtonSizer, 0, wxALL | wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();

	m_pTasksListCtrl->InsertColumn(0, wxT("Subject"), wxLIST_FORMAT_LEFT, (m_pTasksListCtrl->GetClientRect().GetWidth()-180));
	m_pTasksListCtrl->InsertColumn(1, wxT("Priority"), wxLIST_FORMAT_CENTER, 16);
	m_pTasksListCtrl->InsertColumn(2, wxT("Percent Completion"), wxLIST_FORMAT_LEFT, 40);
	m_pTasksListCtrl->InsertColumn(3, wxT("Reminder"), wxLIST_FORMAT_CENTER, 16);
	m_pTasksListCtrl->InsertColumn(4, wxT("Due Date"), wxLIST_FORMAT_CENTER, 90);

	m_pButtonImport->Disable();
	m_pButtonExport->Disable();
	FillTasksCategory();
	FillTasksList(m_pComboCategory->GetValue());
}

void CTasksPanel::OnAddTask(wxCommandEvent &event)
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("categories")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
		wxMessageBox(wxT("Please add a task category, before creating a task."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		return;
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT category FROM categories"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(!result.NextRow())
		{
			wxMessageBox(wxT("Please add a task category, before creating a task."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
			wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;
			return;
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	CAddTaskDialog addTaskDlg(this, CAddTaskDialog::wxID_DIALOG_ADD_TASK);
	if(addTaskDlg.ShowModal() == wxID_OK)
	{
		FillTasksList(addTaskDlg.GetCategory());
	}
	event.Skip(false);
}

void CTasksPanel::OnEditTask(wxCommandEvent &event)
{
	long item = -1;
	item = m_pTasksListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		CAddTaskDialog addTaskDlg(this, CAddTaskDialog::wxID_DIALOG_ADD_TASK);
		addTaskDlg.SetEditMode(m_pTasksListCtrl->GetItemText(item), m_pComboCategory->GetValue());
		if(addTaskDlg.ShowModal() == wxID_OK)
		{
			FillTasksList(addTaskDlg.GetCategory());
		}
	}
	event.Skip(false);
}

void CTasksPanel::OnDeleteTask(wxCommandEvent &event)
{
	long item = -1;
	item = m_pTasksListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		wxString strSubject = m_pTasksListCtrl->GetItemText(item);
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("tasks")))
		{
			wxString sqlCmd = wxString::Format(wxT("DELETE FROM tasks WHERE subject = ? AND category = ?;"));
			wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.Bind(1, strSubject);
			stmt.Bind(2, m_pComboCategory->GetValue());
			// Execute the SQL Query
			stmt.ExecuteUpdate();
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		m_pTasksListCtrl->DeleteItem(item);
	}
	event.Skip(false);
}

void CTasksPanel::OnImportTask(wxCommandEvent &event)
{
	event.Skip(false);
}

void CTasksPanel::OnExportTask(wxCommandEvent &event)
{
	event.Skip(false);
}

void CTasksPanel::OnCategoryChange(wxCommandEvent &event)
{
	FillTasksList(m_pComboCategory->GetValue());
	event.Skip(false);
}

void CTasksPanel::OnSize(wxSizeEvent &event)
{
	m_pTasksListCtrl->SetColumnWidth(0, (m_pTasksListCtrl->GetClientRect().GetWidth()-180));
	m_pTasksListCtrl->SetColumnWidth(1, 16);
	m_pTasksListCtrl->SetColumnWidth(2, 40);
	m_pTasksListCtrl->SetColumnWidth(3, 16);
	m_pTasksListCtrl->SetColumnWidth(4, 90);
	event.Skip(true);
}

void CTasksPanel::FillTasksList(wxString strCategory)
{
	m_pTasksListCtrl->DeleteAllItems();
	m_pComboCategory->SetValue(strCategory);
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("tasks")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, subject VARCHAR(255), category VARCHAR(64), status NUMERIC(1,0), priority NUMERIC(1,0), completion NUMERIC(3,0), startTime TIMESTAMP, endTime TIMESTAMP, reminderTime TIMESTAMP, reminder BOOLEAN, description TEXT);"));
	}
	else
	{
		//#define TASK_STATUS_COMPLETED	2
		wxString sqlCmd = wxString::Format(wxT("SELECT * from tasks WHERE  category = '%s' AND status <> 2;"), strCategory);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			wxString subject = result.GetString(1);
			int nPriority = result.GetInt(4);
			int nCompletion = result.GetInt(5);
			bool bReminder = result.GetBool(9);
			wxDateTime dueDate = result.GetDateTime(7);
			int nItem = m_pTasksListCtrl->InsertItem(m_pTasksListCtrl->GetItemCount(), subject);
			m_pTasksListCtrl->SetItemColumnImage(nItem, 1, nPriority+4);
			m_pTasksListCtrl->SetItem(nItem, 2, wxString::Format(wxT("%d"), nCompletion));
			if(bReminder)
				m_pTasksListCtrl->SetItemColumnImage(nItem, 3, 9);
			m_pTasksListCtrl->SetItem(nItem, 4, dueDate.Format(wxT("%d, %B")));
			if(dueDate.Subtract(wxDateTime::Now()).IsNegative())
				m_pTasksListCtrl->SetItemTextColour(nItem, *wxRED);
		}
		if(m_pTasksListCtrl->GetItemCount() >= 1)
		{
			m_pTasksListCtrl->SetColumnWidth(0, (m_pTasksListCtrl->GetClientRect().GetWidth()-180));
			m_pTasksListCtrl->SetColumnWidth(1, 16);
			m_pTasksListCtrl->SetColumnWidth(2, 40);
			m_pTasksListCtrl->SetColumnWidth(3, 16);
			m_pTasksListCtrl->SetColumnWidth(4, 90);
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CTasksPanel::OnManageCategories(wxCommandEvent &event)
{
	CCategoriesDlg categoryDlg(this);
	categoryDlg.ShowModal();
	FillTasksCategory();
	FillTasksList(m_pComboCategory->GetValue());
	event.Skip(false);
}

void CTasksPanel::OnItemChecked(wxListEvent &event)
{
	if(event.GetItem() >=0 && event.GetItem() < m_pTasksListCtrl->GetItemCount())
	{
		wxFont font = m_pTasksListCtrl->GetItemFont(event.GetIndex());
		//font.SetStrikethrough(true);
		m_pTasksListCtrl->SetItemFont(event.GetIndex(), font);
	}
	event.Skip(false);
}

void CTasksPanel::OnItemUnChecked(wxListEvent &event)
{
	if(event.GetItem() >=0 && event.GetItem() < m_pTasksListCtrl->GetItemCount())
	{
		wxFont font = m_pTasksListCtrl->GetItemFont(event.GetIndex());
		//font.SetStrikethrough(false);
		m_pTasksListCtrl->SetItemFont(event.GetIndex(), font);
	}
	event.Skip(false);
}

void CTasksPanel::FillTasksCategory(void)
{
	m_pComboCategory->Clear();
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
			m_pComboCategory->Append(result.GetString(0));
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	m_pComboCategory->Select(0);
}

void CTasksPanel::MarkCheckedAsComplete(void)
{
	if(m_pTasksListCtrl->GetItemCount())
	{
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("tasks")))
		{
			wxString strSubject;
			wxString strCategory = m_pComboCategory->GetValue();
			wxString sqlCmd;
			for(int item = 0; item < m_pTasksListCtrl->GetItemCount(); item++)
			{
				if(m_pTasksListCtrl->IsChecked(item))
				{
					strSubject = m_pTasksListCtrl->GetItemText(item);
					sqlCmd = wxString::Format(wxT("DELETE FROM tasks WHERE subject = ? AND category = ?;"));
					wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
					// Bind the variables to the SQL statement
					stmt.Bind(1, strSubject);
					stmt.Bind(2, strCategory);
					// Execute the SQL Query
					stmt.ExecuteUpdate();
				}
			}
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
	}
}

wxString CTasksPanel::SetFontStrikethrough(wxString strFontDesc, bool bStrike)
{
	wxString strFont;
	int nCount = 0;
	while (strFontDesc != wxEmptyString && strFontDesc.Find(wxT(';')) > 0)
	{
		wxString strParse = strFontDesc.Left(strFontDesc.Find(wxT(';')));
		strFontDesc = strFontDesc.Right(strFontDesc.Length()-strFontDesc.Find(wxT(';'))-1);
		if(nCount == 9)
		{
			if(bStrike)
				strFont = strFont + wxT("1;");
			else
				strFont = strFont + wxT("0;");
		}
		else
		{
			strFont = strFont + strParse + wxT(";");
		}
		nCount++;
	}
	return strFont+strFontDesc;
}
