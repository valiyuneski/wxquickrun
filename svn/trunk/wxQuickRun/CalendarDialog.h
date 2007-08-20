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
 *	\file CalendarDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/calctrl.h>

class CResource;

class CCalendarDialog : public wxDialog
{
private:
	wxWindow *m_pParent;
	wxCalendarCtrl* m_pCalendarCtrl;
	long m_nStyle;
	wxDateTime m_dateTime;

public:
	CCalendarDialog(wxWindow* parent = NULL, wxWindowID id = wxID_ANY, const wxString& title = wxT("Calendar"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE, wxDateTime dateTime = wxDefaultDateTime, const wxString& name = wxT("Calendar Dialog Box"));
	virtual ~CCalendarDialog(void);

public:
	wxDateTime GetSelectedDate(void);
	wxCalendarCtrl* GetCalendarControl(void);

private:
	void CreateGUIControls(void);

private:
	void OnDateSelection(wxCalendarEvent &event);

public:
	enum
	{
		wxID_CALENDAR_CTRL_DIALOG = wxID_HIGHEST + 1050
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
