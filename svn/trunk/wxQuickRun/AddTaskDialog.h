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
 *	\file AddTaskDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/combobox.h>
#include <wx/spinctrl.h>

// Task Status
#define TASK_STATUS_NOT_STARTED			0
#define TASK_STATUS_IN_PROGRESS			1
#define TASK_STATUS_COMPLETED			2
#define TASK_STATUS_WAITING_ON_SOMEONE	3
#define TASK_STATUS_DEFERRED			4

// Task Priority
#define TASK_PRIORITY_BLOCKER			0
#define TASK_PRIORITY_CRITICAL			1
#define TASK_PRIORITY_MAJOR				2
#define TASK_PRIORITY_MINOR				3
#define TASK_PRIORITY_TRIVIAL			4

class CAddTaskDialog : public wxDialog
{
public:
	CAddTaskDialog(wxWindow* parent, wxWindowID id = CAddTaskDialog::wxID_DIALOG_ADD_TASK, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 425), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Add Task DialogBox"));

public:
	virtual ~CAddTaskDialog(void);
	wxString GetTaskSubject(void);
	wxString GetTaskDetail(void);
	wxString GetCategory(void);
	int GetStatus(void);
	int GetPercentCompletion(void);
	int GetPriority(void);
	wxDateTime GetStartTime(void);
	wxDateTime GetEndTime(void);
	wxDateTime GetReminderTime(void);
	bool IsReminderSet(void);

	void SetTaskSubjet(wxString);
	void SetTaskDetail(wxString);
	void SetCategory(wxString);
	void SetStatus(int);
	void SetPercentCompletion(int);
	void SetPriority(int);
	void SetStartTime(wxDateTime);
	void SetEndTime(wxDateTime);
	void SetReminderTime(wxDateTime);
	void SetReminder(bool);
	void SetEditMode(wxString strEditSubject, wxString strEditCategory);

private:
	void OnClose(wxCloseEvent &event);
	void OnOK(wxCommandEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnButtonStartDate(wxCommandEvent &event);
	void OnButtonEndDate(wxCommandEvent &event);
	void OnButtonReminderDate(wxCommandEvent &event);
	void OnCheckBoxReminder(wxCommandEvent &event);
	void OnStatusChange(wxCommandEvent &event);

	void ParseDate(wxString strDate, int &nDay, int &nMonth, int &nYear);
	void ParseTime(wxString strTime, wxString AMPM, int &nHour, int &nMinute);
	void FillEditInfo(void);

public:
	enum
	{
		wxID_DIALOG_ADD_TASK = wxID_HIGHEST + 775,
		wxID_STATIC_TEXT_SUBJECT,
		wxID_STATIC_TEXT_CATEGORY,
		wxID_TEXTCTRL_SUBJECT,
		wxID_COMBOBOX_CATEGORY,
		wxID_STATIC_TEXT_STATUS,
		wxID_COMBOBOX_STATUS,
		wxID_STATIC_TEXT_PERCENT,
		wxID_SPINCTRL_PERCENT,
		wxID_STATIC_TEXT_PRIORITY,
		wxID_COMBOBOX_PRIORITY,
		wxID_TEXTCTRL_DESCRIPTION,
		wxID_STATIC_TEXT_START_DATE,
		wxID_STATIC_TEXT_END_DATE,
		wxID_STATIC_TEXT_REMINDER_DATE,
		wxID_TEXTCTRL_START_DATE,
		wxID_TEXTCTRL_END_DATE,
		wxID_TEXTCTRL_REMINDER_DATE,
		wxID_TEXTCTRL_START_TIME,
		wxID_TEXTCTRL_END_TIME,
		wxID_TEXTCTRL_REMINDER_TIME,
		wxID_COMBOBOX_START_AM_PM,
		wxID_COMBOBOX_END_AM_PM,
		wxID_COMBOBOX_REMINDER_AM_PM,
		wxID_BUTTON_START_DATE,
		wxID_BUTTON_END_DATE,
		wxID_BUTTON_REMINDER_DATE,
		wxID_CHECKBOX_REMINDER,
		wxID_DIALOG_CALENDAR
	};

private:
	wxStaticText *m_pStaticSubject;
	wxStaticText *m_pStaticCategory;
	wxTextCtrl *m_pTextCtrlSubject;
	wxComboBox *m_pComboCategory;
	wxStaticText *m_pStaticStatus;
	wxComboBox *m_pComboStatus;
	wxStaticText *m_pStaticPercent;
	wxSpinCtrl *m_pSpinCtrlPercent;
	wxStaticText *m_pStaticPriority;
	wxComboBox *m_pComboPriority;
	wxTextCtrl *m_pTextCtrlDescription;
	wxStaticText *m_pStaticStartDate;
	wxTextCtrl *m_pTextCtrlStartDate;
	wxButton *m_pButtonStartDate;
	wxTextCtrl *m_pTextCtrlStartTime;
	wxComboBox *m_pComboStartAMPM;
	wxStaticText *m_pStaticEndDate;
	wxTextCtrl *m_pTextCtrlEndDate;
	wxButton *m_pButtonEndDate;
	wxTextCtrl *m_pTextCtrlEndTime;
	wxComboBox *m_pComboEndAMPM;
	wxStaticText *m_pStaticReminderDate;
	wxTextCtrl *m_pTextCtrlReminderDate;
	wxButton *m_pButtonReminderDate;
	wxTextCtrl *m_pTextCtrlReminderTime;
	wxComboBox *m_pComboReminderAMPM;
	wxCheckBox *m_pCheckBoxReminder;
	wxString m_strEditSubject;
	wxString m_strEditCategory;
	wxString m_strSubject;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
