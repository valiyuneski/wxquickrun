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
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *	General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public
 *	License along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	See gpl.txt for more information regarding the GNU General Public License.
 *
 * 
 *	\file wxAlarm.cpp
 *	\author Priyank Bolia
 *  \created 13 Oct, 2006
 *	\brief Class to handle multiple alarms, it allows you to execute code at multiple non-symmetric time intervals.
 *  wxAlarm does not fire a timer event, every second to check whether a timer has to be fired,
 *  to the client program, but it sets the timer object to the minimum time difference
 *  between the list of the alarms and the current time. This way is saves lot of CPU cycle
 *  and allows user to fire alarm on a particular system time, rather than after a particular
 *  amount of time elapsed. This way it saves the user from doing time based calculations,
 *  managing multiple objects of wxTimer and provide high efficiency. It works the same way
 *  as wxTimer providing a wxAlarmEvent which you can handle using EVT_ALARM.
 **/

// ==========================================================================
// headers
// ==========================================================================

//------------------------------------------------------------------------
// The standard wxWindow pragma and includes

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "wxAlarm.h"
#endif

#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif 

//------------------------------------------------------------------------
// The wxAlarm header
#include "wxAlarm.h"

// ==========================================================================
// Events Table
// ==========================================================================

DEFINE_EVENT_TYPE( wxEVT_ALARM );
IMPLEMENT_DYNAMIC_CLASS(wxAlarmEvent, wxEvent)

//------------------------------------------------------------------------
// Constructor and Destructor
//------------------------------------------------------------------------

wxAlarm::~wxAlarm(void)
{
}

// ==========================================================================
// wxAlarm Implementation
// ==========================================================================

IMPLEMENT_DYNAMIC_CLASS( wxAlarm, wxEvtHandler )

BEGIN_EVENT_TABLE(wxAlarm, wxEvtHandler)
	EVT_TIMER(wxID_ANY, wxAlarm::OnTimerEvent)
END_EVENT_TABLE()

//------------------------------------------------------------------------
// Public Functions
//------------------------------------------------------------------------

bool wxAlarm::AddAlarm(wxDateTime time, void *data)
{
	m_mapAlarms.insert(pair<unsigned long, void *>(time.GetAsDOS(), data));
	return RefreshAlarms();
}

bool wxAlarm::RemoveAlarm(void *data)
{
	multimap<unsigned long, void *, cmpmap>::iterator it;
	for (it = m_mapAlarms.begin(); it != m_mapAlarms.end(); ++it)
	{
		if((*it).second == data)
		{
			break;
		}
	}
	RefreshAlarms();
	return true;
}

bool wxAlarm::RemoveAlarm(wxDateTime time)
{
	multimap<unsigned long, void *, cmpmap>::iterator it = m_mapAlarms.find(time.GetAsDOS());
	RefreshAlarms();
	return true;
}

void* wxAlarm::FindAlarm(wxDateTime time)
{
	multimap<unsigned long, void *, cmpmap>::iterator it = m_mapAlarms.find(time.GetAsDOS());
	return (*it).second;
}

wxDateTime wxAlarm::FindAlarm(void *data)
{
	wxDateTime time;
	time.SetFromDOS(0);
	for (multimap<unsigned long, void *, cmpmap>::iterator it = m_mapAlarms.begin(); it != m_mapAlarms.end(); ++it)
	{
		if((*it).second == data)
		{
			time.SetFromDOS((*it).first);
			return time;
		}
	}
	return time;
}

bool wxAlarm::RemoveAllAlarms(void)
{
	RefreshAlarms();
	return true;
}

bool wxAlarm::RefreshAlarms(void)
{
	if(m_bStart == false)
		return false;
	return true;
}

//------------------------------------------------------------------------
// Protected Functions
//------------------------------------------------------------------------

void wxAlarm::OnTimerEvent(wxTimerEvent &event)
{
	event.Skip(false);
}

void wxAlarm::NotifyAlarm(unsigned long time, void *data, wxAlarmEvent::wxAlarmStatus status)
{
	// Make sure owner has been set, otherwise log error in Debug
	wxCHECK_RET( m_owner, wxT("wxAlarm::NotifyAlarm(unsigned long time, void *data, wxAlarmEvent::wxAlarmStatus) should be overridden."));
	wxAlarmEvent event(wxEVT_ALARM, m_id);
	wxDateTime datetime;
	datetime.SetFromDOS(time);
	event.SetStatus(status);
	event.SetTime(datetime);
	event.SetData(data);
	event.SetEventObject(this);
	(void)m_owner->ProcessEvent(event);
}
