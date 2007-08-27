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
 *	\file ReminderDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 04 Jul, 2006
 **/
#pragma once
#include "stdwx.h"
#include "checkedlistctrl.h"
#include <wx/combobox.h>
#include <vector>
using namespace std;

class CReminderDialog :	public wxDialog
{
public:
	CReminderDialog(wxWindow* parent, wxWindowID id = CReminderDialog::wxID_DIALOG_REMINDER_TASK, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 350), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Reminder Dialog Box"));
	virtual ~CReminderDialog(void);
	void SetTaskID(int nTaskReminderID);
	int GetTaskID(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnSnoozeButton(wxCommandEvent &event);
	void OnDismissButton(wxCommandEvent &event);
	void OnDismissAllButton(wxCommandEvent &event);
	void OnOpenItemButton(wxCommandEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);

	wxDateTime ParseSnoozeTime(wxString strTime);
	void GetTaskInformation();
	void FillTasksList();
	wxTimeSpan GetTimeSpan(int weeks, int days, int hours, int minutes);

public:
	enum
	{
		wxID_DIALOG_REMINDER_TASK = wxID_HIGHEST + 1350,
		wxID_STATIC_TEXT_SUBJECT,
		wxID_STATIC_TEXT_CATEGORY,
		wxID_STATIC_TEXT_START_TIME,
		wxID_STATIC_TEXT_SNOOZE,
		wxID_BUTTON_DISMISS,
		wxID_BUTTON_DISMISS_ALL,
		wxID_BUTTON_SNOOZE,
		wxID_BUTTON_OPEN_ITEM,
		wxID_LISTCTRL_TASKS,
		wxID_COMBOBOX_SNOOZE
	};

private:
	wxStaticText *m_pStaticSubject;
	wxStaticText *m_pStaticCategory;
	wxStaticText *m_pStaticStartTime;
	wxCheckedListCtrl *m_pTasksList;
	wxButton *m_pButtonDismiss;
	wxButton *m_pButtonSnooze;
	wxButton *m_pButtonDismissAll;
	wxButton *m_pButtonOpenItem;
	wxStaticText *m_pStaticSnooze;
	wxComboBox *m_pComboBoxSnooze;
	int m_nTaskReminderID;
	wxString m_strTaskSubject;
	wxString m_strTaskCategory;
	wxDateTime m_dtTaskStartTime;
	vector<int> m_vecTasksID;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
