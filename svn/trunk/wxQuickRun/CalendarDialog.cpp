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
 *	\file CalendarDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#include "CalendarDialog.h"

BEGIN_EVENT_TABLE(CCalendarDialog, wxDialog)
	EVT_CALENDAR(wxID_CALENDAR_CTRL_DIALOG, CCalendarDialog::OnDateSelection)
END_EVENT_TABLE()

CCalendarDialog::CCalendarDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, wxDateTime dateTime, const wxString& name)
: wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP  | wxRESIZE_BORDER, name)
, m_pCalendarCtrl(NULL)
, m_nStyle(style)
, m_dateTime(dateTime)
{
	CreateGUIControls();
}

CCalendarDialog::~CCalendarDialog(void)
{
}

void CCalendarDialog::CreateGUIControls(void)
{
	SetIcon(wxICON(IDI_ICON_CALENDAR));
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pCalendarCtrl = new wxCalendarCtrl(this, wxID_CALENDAR_CTRL_DIALOG, m_dateTime, wxDefaultPosition, wxDefaultSize, m_nStyle, wxT("Calendar Dialog Control"));
	pMainSizer->Add(m_pCalendarCtrl, 1, wxEXPAND | wxALL, 3);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Fit();
	Layout();
}

void CCalendarDialog::OnDateSelection(wxCalendarEvent &event)
{
	event.Skip();
	EndModal(wxID_OK);
}

wxDateTime CCalendarDialog::GetSelectedDate(void)
{
	return m_pCalendarCtrl->GetDate();
}

wxCalendarCtrl* CCalendarDialog::GetCalendarControl(void)
{
	return m_pCalendarCtrl;
}
