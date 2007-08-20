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
 *	\file ReminderDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 04 Jul, 2006
 **/
#include "ReminderDialog.h"
#include "AddTaskDialog.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CReminderDialog, wxDialog)
	EVT_CLOSE(CReminderDialog::OnClose)
	EVT_BUTTON(wxID_BUTTON_SNOOZE, CReminderDialog::OnSnoozeButton)
	EVT_BUTTON(wxID_BUTTON_DISMISS, CReminderDialog::OnDismissButton)
	EVT_BUTTON(wxID_BUTTON_DISMISS_ALL, CReminderDialog::OnDismissAllButton)
	EVT_BUTTON(wxID_BUTTON_OPEN_ITEM, CReminderDialog::OnOpenItemButton)
	EVT_SIZE(CReminderDialog::OnSize)
	EVT_INIT_DIALOG(CReminderDialog::OnInitDialog)
END_EVENT_TABLE()

CReminderDialog::CReminderDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticSubject(NULL)
, m_pStaticStartTime(NULL)
, m_pTasksList(NULL)
, m_pButtonDismiss(NULL)
, m_pButtonSnooze(NULL)
, m_pButtonDismissAll(NULL)
, m_pButtonOpenItem(NULL)
, m_pStaticSnooze(NULL)
, m_pComboBoxSnooze(NULL)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CReminderDialog::~CReminderDialog(void)
{
}

void CReminderDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CReminderDialog::OnInitDialog(wxInitDialogEvent &event)
{
	SetMinSize(wxSize(400, 350));

	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Task reminder:"));
	m_pStaticSubject = new wxStaticText(this, wxID_STATIC_TEXT_SUBJECT, wxT("Dummy Message"));
	m_pStaticStartTime = new wxStaticText(this, wxID_STATIC_TEXT_START_TIME, wxT("Start time:"));
	m_pStaticCategory = new wxStaticText(this, wxID_STATIC_TEXT_CATEGORY, wxT("Category: "));
	m_pTasksList = new wxCheckedListCtrl(this, wxID_LISTCTRL_TASKS, wxDefaultPosition, wxDefaultSize, wxLC_HRULES | wxLC_VRULES | wxLC_REPORT | wxLC_SINGLE_SEL);
	m_pButtonDismissAll = new wxButton(this, wxID_BUTTON_DISMISS_ALL, wxT("Dismiss &All"));
	m_pButtonOpenItem = new wxButton(this, wxID_BUTTON_OPEN_ITEM, wxT("&Open Item"));
	m_pButtonDismiss = new wxButton(this, wxID_BUTTON_DISMISS, wxT("&Dismiss"));
	m_pStaticSnooze = new wxStaticText(this, wxID_STATIC_TEXT_SNOOZE, wxT("&Click Snooze to be reminded again in:"));
	wxArrayString arraySnooze;
	arraySnooze.Add(wxT("5 Minutes"));
	arraySnooze.Add(wxT("10 Minutes"));
	arraySnooze.Add(wxT("15 Minutes"));
	arraySnooze.Add(wxT("30 Minutes"));
	arraySnooze.Add(wxT("1 Hour"));
	arraySnooze.Add(wxT("2 Hours"));
	arraySnooze.Add(wxT("3 Hours"));
	arraySnooze.Add(wxT("5 Hours"));
	arraySnooze.Add(wxT("8 Hours"));
	arraySnooze.Add(wxT("12 Hours"));
	arraySnooze.Add(wxT("1 Day"));
	arraySnooze.Add(wxT("2 Days"));
	arraySnooze.Add(wxT("3 Days"));
	arraySnooze.Add(wxT("4 Days"));
	arraySnooze.Add(wxT("5 Days"));
	arraySnooze.Add(wxT("1 Week"));
	m_pComboBoxSnooze = new wxComboBox(this, wxID_COMBOBOX_SNOOZE, arraySnooze.Item(0), wxDefaultPosition, wxDefaultSize, arraySnooze);
	m_pButtonSnooze = new wxButton(this, wxID_BUTTON_SNOOZE, wxT("&Snooze"));

	pStaticBoxSizer->Add(m_pStaticSubject, 0, wxEXPAND | wxALL, 5);
	pStaticBoxSizer->Add(m_pStaticStartTime, 0, wxEXPAND | wxALL, 5);
	pStaticBoxSizer->Add(m_pStaticCategory, 0, wxEXPAND | wxALL, 5);
	pStaticBoxSizer->Add(m_pTasksList, 1, wxEXPAND | wxALL, 5);
	wxBoxSizer *pButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonsSizer->Add(m_pButtonDismissAll, 0, wxEXPAND | wxALL, 5);
	pButtonsSizer->AddStretchSpacer(1);
	pButtonsSizer->Add(m_pButtonOpenItem, 0, wxEXPAND | wxALL, 5);
	pButtonsSizer->Add(m_pButtonDismiss, 0, wxEXPAND | wxALL, 5);
	pStaticBoxSizer->Add(pButtonsSizer, 0, wxEXPAND | wxALL, 0);
	pStaticBoxSizer->Add(m_pStaticSnooze, 0, wxEXPAND | wxALL, 6);
	wxBoxSizer *pSnoozeSizer = new wxBoxSizer(wxHORIZONTAL);
	pSnoozeSizer->Add(m_pComboBoxSnooze, 1, wxEXPAND | wxALL, 5);
	pSnoozeSizer->Add(m_pButtonSnooze, 0, wxEXPAND | wxALL, 5);
	pStaticBoxSizer->Add(pSnoozeSizer, 0, wxEXPAND | wxALL, 0);
	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Fit();
	Layout();

	wxSize size = m_pTasksList->GetSize();
	m_pTasksList->InsertColumn(0, wxT("Subject"), wxLIST_FORMAT_LEFT, size.GetWidth()*0.55);
	m_pTasksList->InsertColumn(1, wxT("Due in"), wxLIST_FORMAT_LEFT, size.GetWidth()*0.20);
	m_pTasksList->InsertColumn(2, wxT("Category"), wxLIST_FORMAT_LEFT, size.GetWidth()*0.20);
}

void CReminderDialog::OnSnoozeButton(wxCommandEvent &event)
{
	wxString strSubject = m_pStaticSubject->GetLabel();
	wxString strCategory = m_pStaticCategory->GetLabel();
	strCategory = strCategory.Right(strCategory.Length() - strCategory.Find(wxT(": ")) - 2);
	if(strCategory != wxEmptyString && strSubject != wxEmptyString)
	{
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("tasks")))
		{
			wxString sqlCmd = wxString::Format(wxT("UPDATE tasks SET reminderTime = ? WHERE subject = '%s' AND category = '%s';"), strSubject, strCategory);
			wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.BindTimestamp(1, ParseSnoozeTime(m_pComboBoxSnooze->GetValue()));
			// Execute the SQL Query
			stmt.ExecuteUpdate();
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
	}
	Close();
}

void CReminderDialog::OnDismissButton(wxCommandEvent &event)
{
	wxString strSubject = m_pStaticSubject->GetLabel();
	wxString strCategory = m_pStaticCategory->GetLabel();
	strCategory = strCategory.Right(strCategory.Length() - strCategory.Find(wxT(": ")) - 2);
	if(strCategory != wxEmptyString && strSubject != wxEmptyString)
	{
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("tasks")))
		{
			wxString sqlCmd = wxString::Format(wxT("UPDATE tasks SET reminderTime = ? WHERE subject = '%s' AND category = '%s';"), strSubject, strCategory);
			wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.BindTimestamp(1, wxDateTime(1, wxDateTime::Jan, 1970, 0, 0, 0));
			// Execute the SQL Query
			stmt.ExecuteUpdate();
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
	}
	Close();
}

void CReminderDialog::OnDismissAllButton(wxCommandEvent &event)
{
	Close();
}

void CReminderDialog::OnOpenItemButton(wxCommandEvent &event)
{
	wxString strSubject = m_pStaticSubject->GetLabel();
	wxString strCategory = m_pStaticCategory->GetLabel();
	strCategory = strCategory.Right(strCategory.Length() - strCategory.Find(wxT(": ")) - 2);
	if(strCategory != wxEmptyString && strSubject != wxEmptyString)
	{
		CAddTaskDialog addTaskDlg(this, CAddTaskDialog::wxID_DIALOG_ADD_TASK);
		addTaskDlg.SetEditMode(strSubject, strCategory);
		addTaskDlg.ShowModal();
	}
}

void CReminderDialog::OnSize(wxSizeEvent &event)
{
	wxSize size = m_pTasksList->GetSize();
	m_pTasksList->SetColumnWidth(0, size.GetWidth()*0.55);
	m_pTasksList->SetColumnWidth(1, size.GetWidth()*0.20);
	m_pTasksList->SetColumnWidth(2, size.GetWidth()*0.20);
	event.Skip(true);
}

wxDateTime CReminderDialog::ParseSnoozeTime(wxString strTime)
{
	//TODO: Write  the parser function to parse something like 1 Week 3 Days 5 Minutes.
	wxDateTime dateTime = wxDateTime::Now();
	strTime = strTime.Trim(true);
	return dateTime;
}