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
#include <wx/regex.h>
#include <boost/lexical_cast.hpp>

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
	m_vecTasksID.clear();
}

void CReminderDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CReminderDialog::OnInitDialog(wxInitDialogEvent &event)
{
	GetTaskInformation();

	SetMinSize(wxSize(400, 350));

	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Task reminder:"));
	m_pStaticSubject = new wxStaticText(this, wxID_STATIC_TEXT_SUBJECT, m_strTaskSubject);
	wxString strDateTime = wxT("Start time: ") + m_dtTaskStartTime.Format(wxT("%A, %d %B, %Y")) + wxT(" ") + m_dtTaskStartTime.Format(wxT("%I:%M"));
	if(m_dtTaskStartTime.GetHour() >= 12)
		strDateTime += wxT(" PM");
	else
		strDateTime += wxT(" AM");
	m_pStaticStartTime = new wxStaticText(this, wxID_STATIC_TEXT_START_TIME, strDateTime);
	m_pStaticCategory = new wxStaticText(this, wxID_STATIC_TEXT_CATEGORY, m_strTaskCategory);
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
	FillTasksList();
}

void CReminderDialog::OnSnoozeButton(wxCommandEvent &event)
{
	wxString strSubject = m_pStaticSubject->GetLabel();
	wxString strCategory = m_pStaticCategory->GetLabel();
	strCategory = strCategory.Right(strCategory.Length() - strCategory.Find(wxT(": ")) - 2);
	if(strCategory != wxEmptyString && strSubject != wxEmptyString)
	{
		DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
		if(dbConn->TableExists(wxT("tasks")))
		{
			wxString sqlCmd = wxString::Format(wxT("UPDATE tasks SET reminderTime = ? WHERE subject = '%s' AND category = '%s';"), strSubject, strCategory);
			wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.BindTimestamp(1, ParseSnoozeTime(m_pComboBoxSnooze->GetValue()));
			// Execute the SQL Query
			stmt.ExecuteUpdate();
		}
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
			wxString sqlCmd = wxString::Format(wxT("UPDATE tasks SET reminder = 0 WHERE subject = '%s' AND category = '%s';"), strSubject, strCategory);
			wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
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
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("tasks")))
	{
		wxString sqlCmd = wxString::Format(wxT("UPDATE tasks SET reminder = 0 WHERE ID in ("));
		for(vector<int>::const_iterator iter = m_vecTasksID.begin(); iter != m_vecTasksID.end(); ++iter)
		{
			try 
			{
				sqlCmd << boost::lexical_cast<int>(*iter) << wxT(", ");
			}
			catch (boost::bad_lexical_cast &)
			{	
			}
		}
		sqlCmd += wxT(" 0)");
		wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
		stmt.ExecuteUpdate();
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
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
	// Parser function to parse something like: 1 Week 3 Days 5 Minutes.
	wxDateTime dateTime = wxDateTime::Now();
	strTime = strTime.Trim(true);
	int weeks = 0, days = 0, hours = 0, minutes = 0;
	wxRegEx reExp(wxT("\\s*(\\d+)\\s*([a-zA-Z]*)\\s*"), wxRE_ADVANCED);
	wxString strNumber;
	wxString strText;
	int nNumber = 0;
	while( reExp.Matches(strTime) )
	{
		strNumber = reExp.GetMatch(strTime, 1);
		strText = reExp.GetMatch(strTime, 2);
		strTime = strTime.Remove(0, reExp.GetMatch(strTime, 0).Length());
		strText = strText.Lower();
		try
		{
			nNumber =  boost::lexical_cast<int>(strText.c_str());
		}
		catch (boost::bad_lexical_cast &)
		{			
			nNumber = 0;
		}
		if(strText.Find(wxT("minute")) == 0)
			minutes = nNumber;
		else if(strText.Find(wxT("hour")) == 0)
			hours = nNumber;
		else if(strText.Find(wxT("day")) == 0)
			days = nNumber;
		else if(strText.Find(wxT("week")) == 0)
			weeks = nNumber;
	}
	return dateTime + GetTimeSpan(weeks, days, hours, minutes);
}

void CReminderDialog::SetTaskID(int nTaskReminderID)
{
	m_nTaskReminderID = nTaskReminderID;
}

int CReminderDialog::GetTaskID(void)
{
	return m_nTaskReminderID;
}

void CReminderDialog::GetTaskInformation()
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("tasks")))
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT subject, category, startTime FROM tasks WHERE ID = %d"), m_nTaskReminderID);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			m_strTaskSubject = result.GetString(0);
			m_strTaskCategory = wxT("Category: ") + result.GetString(1);
			m_dtTaskStartTime = result.GetDateTime(2);
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CReminderDialog::FillTasksList()
{
	m_pTasksList->DeleteAllItems();
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("tasks")))
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT ID, subject, category, reminderTime FROM tasks WHERE reminderTime > ? LIMIT 3"));
		wxSQLite3Statement stmt = wxSQLiteDB->PrepareStatement(sqlCmd);
		// Bind the variables to the SQL statement
		stmt.BindTimestamp(1, wxDateTime::Now());
		wxSQLite3ResultSet result = stmt.ExecuteQuery();
		int nIndex = 0;
		m_vecTasksID.clear();
		m_vecTasksID.reserve(3);
		while(result.NextRow())
		{
			m_vecTasksID.push_back(result.GetInt(1));
			wxString strDateTime = (result.GetDateTime(3) - wxDateTime::Now()).Format();
			m_pTasksList->InsertItem(nIndex, result.GetString(1));
			m_pTasksList->SetItem(nIndex, 1, strDateTime);
			m_pTasksList->SetItem(nIndex, 2, result.GetString(2));
			nIndex++;
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

wxTimeSpan CReminderDialog::GetTimeSpan(int weeks, int days, int hours, int minutes)
{
	if(weeks > 0 && days > 0)
		hours += (days*24) + (weeks*24*7);
	else if(weeks > 0)
		hours += (weeks*24*7);
	else if(days > 0)
		hours += (days*24);
	wxTimeSpan timeSpan(hours, minutes);
	return timeSpan;
}
