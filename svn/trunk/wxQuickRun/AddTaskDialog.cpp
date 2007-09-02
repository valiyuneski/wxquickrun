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
 *	\file AddTaskDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#include "AddTaskDialog.h"
#include "CalendarDialog.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CAddTaskDialog, wxDialog)
	EVT_CLOSE(CAddTaskDialog::OnClose)
	EVT_BUTTON(wxID_OK, CAddTaskDialog::OnOK)
	EVT_BUTTON(wxID_BUTTON_START_DATE, CAddTaskDialog::OnButtonStartDate)
	EVT_BUTTON(wxID_BUTTON_END_DATE, CAddTaskDialog::OnButtonEndDate)
	EVT_BUTTON(wxID_BUTTON_REMINDER_DATE, CAddTaskDialog::OnButtonReminderDate)
	EVT_CHECKBOX(wxID_CHECKBOX_REMINDER, CAddTaskDialog::OnCheckBoxReminder)
	EVT_COMBOBOX(wxID_COMBOBOX_STATUS, CAddTaskDialog::OnStatusChange)
	EVT_COMBOBOX(wxID_COMBOBOX_REMINDER_TASK, CAddTaskDialog::OnReminderTaskChange)
	EVT_INIT_DIALOG(CAddTaskDialog::OnInitDialog)
END_EVENT_TABLE()

CAddTaskDialog::CAddTaskDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticSubject(NULL)
, m_pStaticCategory(NULL)
, m_pTextCtrlSubject(NULL)
, m_pComboCategory(NULL)
, m_pStaticStatus(NULL)
, m_pComboStatus(NULL)
, m_pStaticPercent(NULL)
, m_pSpinCtrlPercent(NULL)
, m_pStaticPriority(NULL)
, m_pComboPriority(NULL)
, m_pTextCtrlDescription(NULL)
, m_pStaticStartDate(NULL)
, m_pTextCtrlStartDate(NULL)
, m_pButtonStartDate(NULL)
, m_pTextCtrlStartTime(NULL)
, m_pComboStartAMPM(NULL)
, m_pStaticEndDate(NULL)
, m_pTextCtrlEndDate(NULL)
, m_pButtonEndDate(NULL)
, m_pTextCtrlEndTime(NULL)
, m_pComboEndAMPM(NULL)
, m_pStaticReminderDate(NULL)
, m_pTextCtrlReminderDate(NULL)
, m_pButtonReminderDate(NULL)
, m_pTextCtrlReminderTime(NULL)
, m_pComboReminderAMPM(NULL)
, m_pStaticReminderTask(NULL)
, m_pComboReminderTask(NULL)
, m_pCheckBoxReminder(NULL)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CAddTaskDialog::~CAddTaskDialog(void)
{
}

void CAddTaskDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CAddTaskDialog::OnInitDialog(wxInitDialogEvent& WXUNUSED(event))
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer;
	if(m_strEditSubject != wxEmptyString && m_strEditCategory != wxEmptyString)
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Edit task:"));
	else
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Add task:"));

	wxBoxSizer *pStaticTextSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlSizer = new wxBoxSizer(wxVERTICAL);

	if(m_strSubject!=wxEmptyString)
	{
		if(m_strSubject.Find(wxT('\n') > 0))
			m_strSubject = m_strSubject.Left(m_strSubject.Find(wxT('\n'))-1);
		m_strSubject.Trim(true);
		m_strSubject.Trim(false);
	}
	m_pStaticSubject = new wxStaticText(this, wxID_STATIC_TEXT_SUBJECT, wxT("&Subject:"));
	m_pTextCtrlSubject = new wxTextCtrl(this, wxID_TEXTCTRL_SUBJECT, m_strSubject);

	m_pStaticCategory = new wxStaticText(this, wxID_STATIC_TEXT_CATEGORY, wxT("&Category:"));

	wxArrayString arrayCategory;
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("categories")))
	{
		dbConn->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT category FROM categories"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			arrayCategory.Add(result.GetString(0));
		}
		result.Finalize();
	}

	if(arrayCategory.Count())
		m_pComboCategory = new wxComboBox(this, wxID_COMBOBOX_CATEGORY, arrayCategory.Item(0), wxDefaultPosition, wxDefaultSize, arrayCategory, wxCB_READONLY | wxCB_SORT);
	else
		m_pComboCategory = new wxComboBox(this, wxID_COMBOBOX_CATEGORY, wxEmptyString, wxDefaultPosition, wxDefaultSize, arrayCategory, wxCB_READONLY | wxCB_SORT);

	wxArrayString arrayTasks;
	arrayTasks.Add(wxEmptyString);
	if(dbConn->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select keyword from Commands"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			arrayTasks.Add(result.GetString(0));
		}
		result.Finalize();
	}

	wxArrayString arrayStatus;
	arrayStatus.Add(wxT("Not Started"));
	arrayStatus.Add(wxT("In Progress"));
	arrayStatus.Add(wxT("Completed"));
	arrayStatus.Add(wxT("Waiting on someone else"));
	arrayStatus.Add(wxT("Deferred"));
	m_pStaticStatus = new wxStaticText(this, wxID_STATIC_TEXT_STATUS, wxT("Stat&us:"));
	m_pComboStatus = new wxComboBox(this, wxID_COMBOBOX_STATUS, wxT("Not Started"), wxDefaultPosition, wxDefaultSize, arrayStatus, wxCB_READONLY);

	m_pStaticPercent = new wxStaticText(this, wxID_STATIC_TEXT_PERCENT, wxT("Perce&nt:"));
	m_pSpinCtrlPercent = new wxSpinCtrl(this, wxID_SPINCTRL_PERCENT, wxT("0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxSP_WRAP);

	wxArrayString arrayPriority;
	arrayPriority.Add(wxT("Blocker"));
	arrayPriority.Add(wxT("Critical"));
	arrayPriority.Add(wxT("Major"));
	arrayPriority.Add(wxT("Minor"));
	arrayPriority.Add(wxT("Trivial"));
	m_pStaticPriority = new wxStaticText(this, wxID_STATIC_TEXT_PRIORITY, wxT("&Priority:"));
	m_pComboPriority = new wxComboBox(this, wxID_COMBOBOX_PRIORITY, wxT("Major"), wxDefaultPosition, wxDefaultSize, arrayPriority, wxCB_READONLY);

	m_pCheckBoxReminder = new wxCheckBox(this, wxID_CHECKBOX_REMINDER, wxT("Reminder &Message"));

	pStaticTextSizer->Add(m_pStaticSubject, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticCategory, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticStatus, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticPriority, 1, wxALL | wxEXPAND, 5);

	pTextCtrlSizer->Add(m_pTextCtrlSubject, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pComboCategory, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	wxBoxSizer *pPercentSizer = new wxBoxSizer(wxHORIZONTAL);
	pPercentSizer->Add(m_pComboStatus, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pPercentSizer->Add(m_pStaticPercent, 0, wxTOP | wxBOTTOM | wxRIGHT | wxLEFT | wxEXPAND, 5);
	pPercentSizer->Add(m_pSpinCtrlPercent, 0, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(pPercentSizer, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 0);
	wxBoxSizer *pReminderSizer = new wxBoxSizer(wxHORIZONTAL);
	pReminderSizer->Add(m_pComboPriority, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pReminderSizer->Add(m_pCheckBoxReminder, 0, wxTOP | wxBOTTOM | wxRIGHT | wxLEFT | wxEXPAND, 5);
	pTextCtrlSizer->Add(pReminderSizer, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 0);

	wxBoxSizer *pControlsSizer = new wxBoxSizer(wxHORIZONTAL);
	pControlsSizer->Add(pStaticTextSizer, 0, wxALL | wxEXPAND, 5);
	pControlsSizer->Add(pTextCtrlSizer, 1, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(pControlsSizer, 0, wxALL | wxEXPAND, 0);

	wxArrayString arrayAMPM;
	arrayAMPM.Add(wxT("AM"));
	arrayAMPM.Add(wxT("PM"));
	wxBoxSizer *pStartDateSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pStaticStartDate = new wxStaticText(this, wxID_STATIC_TEXT_START_DATE, wxT("Start &Time:  "));
	m_pTextCtrlStartDate = new wxTextCtrl(this, wxID_TEXTCTRL_START_DATE, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pButtonStartDate = new wxButton(this, wxID_BUTTON_START_DATE, wxT("..."));
	m_pTextCtrlStartTime = new wxTextCtrl(this, wxID_TEXTCTRL_START_TIME, wxT(""));
	m_pComboStartAMPM = new wxComboBox(this, wxID_COMBOBOX_START_AM_PM, wxT("AM"), wxDefaultPosition, wxDefaultSize, arrayAMPM, wxCB_READONLY);
	pStartDateSizer->Add(m_pStaticStartDate, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);
	pStartDateSizer->Add(m_pTextCtrlStartDate, 2, wxRIGHT | wxEXPAND, 5);
	pStartDateSizer->Add(m_pButtonStartDate, 0, wxRIGHT | wxEXPAND, 5);
	pStartDateSizer->Add(m_pTextCtrlStartTime, 1, wxRIGHT | wxEXPAND, 5);
	pStartDateSizer->Add(m_pComboStartAMPM, 0, wxRIGHT | wxEXPAND, 5);

	wxBoxSizer *pEndDateSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pStaticEndDate = new wxStaticText(this, wxID_STATIC_TEXT_END_DATE, wxT("&End Time:    "));
	m_pTextCtrlEndDate = new wxTextCtrl(this, wxID_TEXTCTRL_END_DATE, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pButtonEndDate = new wxButton(this, wxID_BUTTON_END_DATE, wxT("..."));
	m_pTextCtrlEndTime = new wxTextCtrl(this, wxID_TEXTCTRL_END_TIME, wxT(""));
	m_pComboEndAMPM = new wxComboBox(this, wxID_COMBOBOX_END_AM_PM, wxT("PM"), wxDefaultPosition, wxDefaultSize, arrayAMPM, wxCB_READONLY);
	pEndDateSizer->Add(m_pStaticEndDate, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);
	pEndDateSizer->Add(m_pTextCtrlEndDate, 2, wxRIGHT | wxEXPAND, 5);
	pEndDateSizer->Add(m_pButtonEndDate, 0, wxRIGHT | wxEXPAND, 5);
	pEndDateSizer->Add(m_pTextCtrlEndTime, 1, wxRIGHT | wxEXPAND, 5);
	pEndDateSizer->Add(m_pComboEndAMPM, 0, wxRIGHT | wxEXPAND, 5);

	wxBoxSizer *pReminderDateSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pStaticReminderDate = new wxStaticText(this, wxID_STATIC_TEXT_REMINDER_DATE, wxT("&Reminder:   "));
	m_pTextCtrlReminderDate = new wxTextCtrl(this, wxID_TEXTCTRL_REMINDER_DATE, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pButtonReminderDate = new wxButton(this, wxID_BUTTON_REMINDER_DATE, wxT("..."));
	m_pTextCtrlReminderTime = new wxTextCtrl(this, wxID_TEXTCTRL_REMINDER_TIME, wxT(""));
	m_pComboReminderAMPM = new wxComboBox(this, wxID_COMBOBOX_REMINDER_AM_PM, wxT("AM"), wxDefaultPosition, wxDefaultSize, arrayAMPM, wxCB_READONLY);
	pReminderDateSizer->Add(m_pStaticReminderDate, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);
	pReminderDateSizer->Add(m_pTextCtrlReminderDate, 2, wxRIGHT | wxEXPAND, 5);
	pReminderDateSizer->Add(m_pButtonReminderDate, 0, wxRIGHT | wxEXPAND, 5);
	pReminderDateSizer->Add(m_pTextCtrlReminderTime, 1, wxRIGHT | wxEXPAND, 5);
	pReminderDateSizer->Add(m_pComboReminderAMPM, 0, wxRIGHT | wxEXPAND, 5);

	m_pTextCtrlDescription = new wxTextCtrl(this, wxID_TEXTCTRL_DESCRIPTION, wxT(""));
	m_pTextCtrlDescription->SetMaxLength(512);
	pStaticBoxSizer->Add(pStartDateSizer, 0, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(pEndDateSizer, 0, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(pReminderDateSizer, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer *pReminderTaskSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pStaticReminderTask = new wxStaticText(this, wxID_STATIC_TEXT_REMINDER_TASK, wxT("Tas&k:          "));
	m_pComboReminderTask = new wxComboBox(this, wxID_COMBOBOX_REMINDER_TASK, wxEmptyString, wxDefaultPosition, wxDefaultSize, arrayTasks, wxCB_READONLY);
	pReminderTaskSizer->Add(m_pStaticReminderTask, 0, wxLEFT | wxRIGHT | wxEXPAND, 5);
	pReminderTaskSizer->Add(m_pComboReminderTask, 1, wxRIGHT | wxEXPAND, 5);

	pStaticBoxSizer->Add(pReminderTaskSizer, 0, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(m_pTextCtrlDescription, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 10);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();

	wxString strDate = wxDateTime::Now().Format(wxT("%A, %d %B, %Y"));
	m_pTextCtrlStartDate->SetValue(strDate);
	m_pTextCtrlEndDate->SetValue(strDate);
	m_pTextCtrlReminderDate->SetValue(strDate);
	m_pTextCtrlStartTime->SetValue(wxT("09:30"));
	m_pTextCtrlEndTime->SetValue(wxT("06:00"));
	m_pTextCtrlReminderTime->SetValue(wxT("10:00"));
	m_pCheckBoxReminder->SetValue(true);

	m_pTextCtrlSubject->SetFocus();
	m_pSpinCtrlPercent->Disable();

	if(m_strEditSubject != wxEmptyString && m_strEditCategory != wxEmptyString)
		FillEditInfo();
}

void CAddTaskDialog::OnOK(wxCommandEvent &event)
{
	if(IsReminderSet() && (GetEndTime() - GetReminderTime()).IsNegative())
	{
		wxMessageBox(wxT("Reminder time cannot be set after the task completion time."), wxT("wxQuickRun"), wxICON_ERROR|wxOK|wxCENTER, this);
		event.Skip(false);
		return;
	}
	if((GetEndTime() - GetStartTime()).IsNegative())
	{
		wxMessageBox(wxT("Task estimated completion time is less than the task starting time."), wxT("wxQuickRun"), wxICON_ERROR|wxOK|wxCENTER, this);
		event.Skip(false);
		return;
	}
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("tasks")))
	{
		dbConn->ExecuteUpdate(wxT("create table tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, subject VARCHAR(255), category VARCHAR(64), status NUMERIC(1,0), priority NUMERIC(1,0), completion NUMERIC(3,0), startTime TIMESTAMP, endTime TIMESTAMP, reminderTime TIMESTAMP, reminder BOOLEAN, description TEXT, reminderTaskID INTEGER);"));
	}

	if(m_strEditSubject != GetTaskSubject() || m_strEditCategory != GetCategory())
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT ID FROM tasks WHERE subject = '%s' AND category = '%s'"), GetTaskSubject(), GetCategory());
		{
			wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				wxMessageBox(wxT("The task with the particular subject has already been created.\nPlease choose a different subject or category."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
				m_pTextCtrlSubject->SetFocus();
				result.Finalize();
				return;
			}
			result.Finalize();
		}
	}
	if(m_strEditSubject != wxEmptyString && m_strEditCategory != wxEmptyString)
	{
		wxString sqlCmd = wxString::Format(wxT("DELETE FROM tasks WHERE subject = '%s' AND category = '%s'"), m_strEditSubject, m_strEditCategory);
		dbConn->ExecuteQuery(sqlCmd);
	}

	wxString sqlCmd = wxString::Format(wxT("Insert INTO tasks('subject', 'category', 'status', 'priority', 'completion', 'startTime', 'endTime', 'reminderTime', 'reminder', 'description' , 'reminderTaskID') VALUES('%s', '%s', %d, %d, %d, ?, ?, ?, ?, ?, %d)"), GetTaskSubject(), GetCategory(), GetStatus(), GetPriority(), GetPercentCompletion(), GetReminderTaskID());
	wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
	// Bind the variables to the SQL statement
	stmt.BindTimestamp(1, GetStartTime());
	stmt.BindTimestamp(2, GetEndTime());
	stmt.BindTimestamp(3, GetReminderTime());
	stmt.BindBool(4, IsReminderSet());
	stmt.Bind(5, GetTaskDetail());
	// Execute the SQL Query
	stmt.ExecuteUpdate();

	event.Skip(true);
}

void CAddTaskDialog::OnButtonStartDate(wxCommandEvent& WXUNUSED(event))
{
	wxPoint point = GetPosition() + m_pButtonStartDate->GetPosition();
	wxSize size = m_pButtonStartDate->GetSize();
	point.y += size.GetHeight();
	CCalendarDialog dlgCalendar(this, wxID_DIALOG_CALENDAR, wxT("Calendar"), point);
	if(dlgCalendar.ShowModal()==wxID_OK)
	{
		m_pTextCtrlStartDate->SetValue(dlgCalendar.GetSelectedDate().Format(wxT("%A, %d %B, %Y")));
	}
	GetStartTime();
}

void CAddTaskDialog::OnButtonEndDate(wxCommandEvent& WXUNUSED(event))
{
	wxPoint point = GetPosition() + m_pButtonEndDate->GetPosition();
	wxSize size = m_pButtonEndDate->GetSize();
	point.y += size.GetHeight();
	CCalendarDialog dlgCalendar(this, wxID_DIALOG_CALENDAR, wxT("Calendar"), point);
	if(dlgCalendar.ShowModal()==wxID_OK)
	{
		m_pTextCtrlEndDate->SetValue(dlgCalendar.GetSelectedDate().Format(wxT("%A, %d %B, %Y")));
	}
}

void CAddTaskDialog::OnButtonReminderDate(wxCommandEvent& WXUNUSED(event))
{
	wxPoint point = GetPosition() + m_pButtonReminderDate->GetPosition();
	wxSize size = m_pButtonReminderDate->GetSize();
	point.y += size.GetHeight();
	CCalendarDialog dlgCalendar(this, wxID_DIALOG_CALENDAR, wxT("Calendar"), point);
	if(dlgCalendar.ShowModal()==wxID_OK)
	{
		m_pTextCtrlReminderDate->SetValue(dlgCalendar.GetSelectedDate().Format(wxT("%A, %d %B, %Y")));
	}
}

void CAddTaskDialog::OnCheckBoxReminder(wxCommandEvent& WXUNUSED(event))
{
	SetReminder(m_pCheckBoxReminder->IsChecked());
}

void CAddTaskDialog::OnStatusChange(wxCommandEvent& WXUNUSED(event))
{
	switch(m_pComboStatus->GetCurrentSelection())
	{
	case TASK_STATUS_NOT_STARTED:
		m_pSpinCtrlPercent->Disable();
		break;
	case TASK_STATUS_IN_PROGRESS:
		m_pSpinCtrlPercent->Enable();
		break;
	case TASK_STATUS_COMPLETED:
		m_pSpinCtrlPercent->Disable();
		break;
	case TASK_STATUS_WAITING_ON_SOMEONE:
		m_pSpinCtrlPercent->Enable();
		break;
	case TASK_STATUS_DEFERRED:
		m_pSpinCtrlPercent->Enable();
		break;
	}
}

wxString CAddTaskDialog::GetTaskSubject(void)
{
	return m_pTextCtrlSubject->GetValue();
}

wxString CAddTaskDialog::GetTaskDetail(void)
{
	return m_pTextCtrlDescription->GetValue();
}

wxString CAddTaskDialog::GetCategory(void)
{
	return m_pComboCategory->GetValue();
}

int CAddTaskDialog::GetStatus(void)
{
	return m_pComboStatus->GetCurrentSelection();
}

int CAddTaskDialog::GetPercentCompletion(void)
{
	if(m_pComboStatus->GetCurrentSelection()==TASK_STATUS_NOT_STARTED)
		return 0;
	else if(m_pComboStatus->GetCurrentSelection()==TASK_STATUS_COMPLETED)
		return 100;
	return m_pSpinCtrlPercent->GetValue();
}

int CAddTaskDialog::GetPriority(void)
{
	return m_pComboPriority->GetCurrentSelection();
}

wxDateTime CAddTaskDialog::GetStartTime(void)
{
	int day, month, year, hour, minute;
	ParseDate(m_pTextCtrlStartDate->GetValue(), day, month, year);
	ParseTime(m_pTextCtrlStartTime->GetValue(), m_pComboStartAMPM->GetValue(), hour, minute);
	wxDateTime dateTime(day, (wxDateTime::Month)month, year, hour, minute);
	return dateTime;
}

wxDateTime CAddTaskDialog::GetEndTime(void)
{
	int day, month, year, hour, minute;
	ParseDate(m_pTextCtrlEndDate->GetValue(), day, month, year);
	ParseTime(m_pTextCtrlEndTime->GetValue(), m_pComboEndAMPM->GetValue(), hour, minute);
	wxDateTime dateTime(day, (wxDateTime::Month)month, year, hour, minute);
	return dateTime;
}

wxDateTime CAddTaskDialog::GetReminderTime(void)
{
	int day, month, year, hour, minute;
	ParseDate(m_pTextCtrlReminderDate->GetValue(), day, month, year);
	ParseTime(m_pTextCtrlReminderTime->GetValue(), m_pComboReminderAMPM->GetValue(), hour, minute);
	wxDateTime dateTime(day, (wxDateTime::Month)month, year, hour, minute);
	return dateTime;
}

bool CAddTaskDialog::IsReminderSet(void)
{
	return m_pCheckBoxReminder->IsChecked();
}

void CAddTaskDialog::ParseDate(wxString strDate, int &nDay, int &nMonth, int &nYear)
{
	wxString strDay, strMonth, strYear;
	strDate = strDate.Right(strDate.Length() - strDate.Find(wxT(",")) - 2);
	strDay = strDate.Left(strDate.Find(wxT(" ")));
	strDate = strDate.Right(strDate.Length() - strDate.Find(wxT(" ")) - 1);
	strMonth = strDate.Left(strDate.Find(wxT(",")));
	strMonth = strMonth.Left(strMonth.Find(wxT(",")));
	strYear = strDate.Right(strDate.Length() - strDate.Find(wxT(",")) - 1);
	strYear = strYear.Strip(wxString::both);
	nDay = wxAtoi(strDay);
	nYear = wxAtoi(strYear);
	if(strMonth == wxT("January"))
		nMonth = 0;
	else if(strMonth == wxT("February"))
		nMonth = 1;
	else if(strMonth == wxT("March"))
		nMonth = 2;
	else if(strMonth == wxT("April"))
		nMonth = 3;
	else if(strMonth == wxT("May"))
		nMonth = 4;
	else if(strMonth == wxT("June"))
		nMonth = 5;
	else if(strMonth == wxT("July"))
		nMonth = 6;
	else if(strMonth == wxT("August"))
		nMonth = 7;
	else if(strMonth == wxT("September"))
		nMonth = 8;
	else if(strMonth == wxT("October"))
		nMonth = 9;
	else if(strMonth == wxT("November"))
		nMonth = 10;
	else if(strMonth == wxT("December"))
		nMonth = 11;
}

void CAddTaskDialog::ParseTime(wxString strTime, wxString AMPM, int &nHour, int &nMinute)
{
	wxString strHour, strMinute;
	strHour = strTime.Left(strTime.Find(wxT(":")));
	strMinute = strTime.Right(strTime.Length() - strTime.Find(wxT(":")) - 1);
	nHour = wxAtoi(strHour);
	nMinute = wxAtoi(strMinute);
	if(AMPM == wxT("PM"))
		nHour += 12;
	if(nHour < 0 || nHour > 24)
		nHour = 0;
	if(nMinute < 0 || nMinute > 60)
		nMinute = 0;
}

void CAddTaskDialog::SetTaskSubjet(wxString strSubject)
{
	m_strSubject = strSubject;
	if(m_pTextCtrlSubject)
		m_pTextCtrlSubject->SetValue(strSubject);
}

void CAddTaskDialog::SetTaskDetail(wxString strDetails)
{
	m_pTextCtrlDescription->SetValue(strDetails);
}

void CAddTaskDialog::SetCategory(wxString strCategory)
{
	m_pComboCategory->SetValue(strCategory);
}

void CAddTaskDialog::SetStatus(int nStatus)
{
	switch(nStatus)
	{
	case TASK_STATUS_NOT_STARTED:
		m_pComboStatus->SetValue(wxT("Not Started"));
		m_pSpinCtrlPercent->Disable();
		break;
	case TASK_STATUS_IN_PROGRESS:
		m_pComboStatus->SetValue(wxT("In Progress"));
		m_pSpinCtrlPercent->Enable();
		break;
	case TASK_STATUS_COMPLETED:
		m_pComboStatus->SetValue(wxT("Completed"));
		m_pSpinCtrlPercent->Disable();
		break;
	case TASK_STATUS_WAITING_ON_SOMEONE:
		m_pComboStatus->SetValue(wxT("Waiting on someone else"));
		m_pSpinCtrlPercent->Enable();
		break;
	case TASK_STATUS_DEFERRED:
		m_pComboStatus->SetValue(wxT("Deferred"));
		m_pSpinCtrlPercent->Enable();
		break;
	};
}

void CAddTaskDialog::SetPercentCompletion(int nCompletion)
{
	m_pSpinCtrlPercent->SetValue(nCompletion);
}

void CAddTaskDialog::SetPriority(int nPriority)
{
	switch(nPriority)
	{
	case TASK_PRIORITY_BLOCKER:
		m_pComboPriority->SetValue(wxT("Blocker"));
		break;
	case TASK_PRIORITY_CRITICAL:
		m_pComboPriority->SetValue(wxT("Critical"));
		break;
	case TASK_PRIORITY_MAJOR:
		m_pComboPriority->SetValue(wxT("Major"));
		break;
	case TASK_PRIORITY_MINOR:
		m_pComboPriority->SetValue(wxT("Minor"));
		break;
	case TASK_PRIORITY_TRIVIAL:
		m_pComboPriority->SetValue(wxT("Trivial"));
		break;
	};
}

void CAddTaskDialog::SetStartTime(wxDateTime dateTime)
{
	wxString strDate = dateTime.Format(wxT("%A, %d %B, %Y"));
	m_pTextCtrlStartDate->SetValue(strDate);
	wxString strTime = dateTime.Format(wxT("%I:%M"));
	m_pTextCtrlStartTime->SetValue(strTime);
	if(dateTime.GetHour()>=12)
		m_pComboStartAMPM->SetValue(wxT("PM"));
}

void CAddTaskDialog::SetEndTime(wxDateTime dateTime)
{
	wxString strDate = dateTime.Format(wxT("%A, %d %B, %Y"));
	m_pTextCtrlEndDate->SetValue(strDate);
	wxString strTime = dateTime.Format(wxT("%I:%M"));
	m_pTextCtrlEndTime->SetValue(strTime);
	if(dateTime.GetHour()>=12)
		m_pComboEndAMPM->SetValue(wxT("PM"));
}

void CAddTaskDialog::SetReminderTime(wxDateTime dateTime)
{
	wxString strDate = dateTime.Format(wxT("%A, %d %B, %Y"));
	m_pTextCtrlReminderDate->SetValue(strDate);
	wxString strTime = dateTime.Format(wxT("%I:%M"));
	m_pTextCtrlReminderTime->SetValue(strTime);
	if(dateTime.GetHour()>=12)
		m_pComboReminderAMPM->SetValue(wxT("PM"));
}

void CAddTaskDialog::SetReminder(bool bReminder)
{
	m_pCheckBoxReminder->SetValue(bReminder);
	if (bReminder)
	{
		m_pStaticReminderDate->Enable();
		m_pTextCtrlReminderDate->Enable();
		m_pButtonReminderDate->Enable();
		m_pTextCtrlReminderTime->Enable();
		m_pComboReminderAMPM->Enable();
		m_pStaticReminderTask->Enable();
		m_pComboReminderTask->Enable();
	}
	else
	{
		m_pStaticReminderDate->Disable();
		m_pTextCtrlReminderDate->Disable();
		m_pButtonReminderDate->Disable();
		m_pTextCtrlReminderTime->Disable();
		m_pComboReminderAMPM->Disable();
		m_pStaticReminderTask->Disable();
		m_pComboReminderTask->Disable();
	}
}

void CAddTaskDialog::SetEditMode(wxString strEditSubject, wxString strEditCategory)
{
	m_strEditSubject = strEditSubject;
	m_strEditCategory = strEditCategory;
}

void CAddTaskDialog::FillEditInfo(void)
{
	m_pTextCtrlSubject->SetValue(m_strEditSubject);
	m_pComboCategory->SetValue(m_strEditCategory);
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("tasks")))
	{
		dbConn->ExecuteUpdate(wxT("create table tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, subject VARCHAR(255), category VARCHAR(64), status NUMERIC(1,0), priority NUMERIC(1,0), completion NUMERIC(3,0), startTime TIMESTAMP, endTime TIMESTAMP, reminderTime TIMESTAMP, reminder BOOLEAN, description TEXT, reminderTaskID INTEGER);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT * from tasks WHERE  subject = '%s' AND category = '%s';"), m_strEditSubject, m_strEditCategory);
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			SetStatus(result.GetInt(3));
			SetPriority(result.GetInt(4));
			SetPercentCompletion(result.GetInt(5));
			SetStartTime(result.GetDateTime(6));
			SetEndTime(result.GetDateTime(7));
			SetReminderTime(result.GetDateTime(8));
			SetReminder(result.GetBool(9));
			SetTaskDetail(result.GetString(10));
			SetReminderTask(result.GetInt(11));
		}
		result.Finalize();
	}
}

void CAddTaskDialog::OnReminderTaskChange(wxCommandEvent& WXUNUSED(event))
{
}

int CAddTaskDialog::GetReminderTaskID()
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(dbConn->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select ID from Commands WHERE keyword = '%s'"), m_pComboReminderTask->GetValue());
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		int nCommnadID = 0;
		if(result.NextRow())
		{
			nCommnadID = result.GetInt(0);
		}
		result.Finalize();
		return nCommnadID;
	}
	return 0;
}

void CAddTaskDialog::SetReminderTask(int nCommandID)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(dbConn->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select keyword from Commands WHERE ID = %d"), nCommandID);
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			m_pComboReminderTask->SetValue(result.GetString(0));
		}
		result.Finalize();
	}
}
