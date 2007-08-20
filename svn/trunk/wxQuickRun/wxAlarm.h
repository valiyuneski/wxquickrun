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
 *	\file wxAlaram.h
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

#ifndef _ALARM_H
#define _ALARM_H

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "wxAlarm.h"
#endif

#include <wx/event.h>
#include <wx/datetime.h>
#include <wx/timer.h>
#include <map>

using namespace std;

// ----------------------------------------------------------------------------
// Declaration
// ----------------------------------------------------------------------------

class wxAlarm;
class wxAlarmEvent; 

struct cmpmap
{
	bool operator()(unsigned long l1, unsigned long l2) const
	{
		return l1 < l2;
	}
};

// ----------------------------------------------------------------------------
// Event Constants
// ----------------------------------------------------------------------------

typedef void (wxEvtHandler::*wxAlarmEventFunction)(wxAlarmEvent&);

#define wxAlarmEventHandler(func) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxAlarmEventFunction, &func)

#define EVT_ALARM(id, func) \
	wx__DECLARE_EVT1(wxEVT_ALARM, id, wxAlarmEventHandler(func))

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_ALARM, wxID_ANY)
END_DECLARE_EVENT_TYPES()

// ----------------------------------------------------------------------------
// wxAlarmEvent
// ----------------------------------------------------------------------------

/// Note: The event handler function should delete the data object, whose pointer is being provided.
class wxAlarmEvent : public wxEvent
{
	DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxAlarmEvent)

public:
	enum wxAlarmStatus {Canceled, Notify}; 

	wxAlarmEvent(wxEventType eventType=wxEVT_ALARM, int timerID=0)
	: wxEvent(timerID)
	{
		m_eventType = eventType;
	}

	// Returns an identical copy of itself. Required for sending with wxPostEvent() as references
	// which must be copied, it does not make sense to have a reference counting scheme to do this cloning,
	// because all wxAlarmEvent should have separate data.
	virtual wxEvent *Clone() const { return new wxAlarmEvent(*this); }

	/// Gets the status/cause of the alarm event, whether alarm canceled or notification for alarm.
	wxAlarmStatus GetStatus() const {return m_status;};
	/// Get the date/time associated with the alarm event.
	wxDateTime GetTime() const {return m_time;}
	/// Get the data associated with the alarm event.
	void* GetData() const {return m_data;}

	// These functions should not be called by the user, they have on effect on the implementation of wxAlarm
	// These are internal only functions called by the event generator to set the properties of the event.
public:
	// Set the status of the alarm event, whether canceled or notify.
	void SetStatus(wxAlarmStatus status) {m_status = status;};
	// Set the time specified for which the event is fired.
	void SetTime(const wxDateTime time) {m_time = time;};
	// Set the data object associated with that alarm, the event class is not responsible for deleting the data.
	void SetData(void* data) {m_data = data;};

private:
	wxAlarmStatus m_status;			// Alarm Status
	wxDateTime m_time;				// Time associated with the alarm for which the event is fired.
	void *m_data;					// Data associated with the alarm for which the event is fired.
}; 

// ----------------------------------------------------------------------------
// wxAlarm
// ----------------------------------------------------------------------------

/// Note: A wxAlarm can only be used from the main thread.
class wxAlarm : public wxEvtHandler
{
	DECLARE_DYNAMIC_CLASS(wxAlarm)
	DECLARE_EVENT_TABLE()

private:
	/// map to hold the date/time and data pointer for the alarms. Date/Time is hold as unsigned long in DOS date time format.
	/// Either the user should use smart pointer for data or delete the data object in the event handler for wxAlarm notifications.
	multimap<unsigned long, void*, cmpmap> m_mapAlarms;

	/// The real timer, which notifies the class, when the timer set to the minimum time difference
	/// between the list of alarms and the current system time elapsed.
	wxTimer m_timer;

	int m_id;                   // wxAlarm Id 
	wxEvtHandler *m_owner;      // Owner of alarm object
	bool m_bStart;				// Denotes whether the wxAlarm is started or stop.

public:
	/// Constructor
	wxAlarm()
	: m_owner(NULL)
	, m_id(wxID_ANY)
	, m_bStart(false)
	{
	}

	wxAlarm(wxEvtHandler *owner, int id = wxID_ANY)
	: m_owner(owner)
	, m_id(id)
	, m_bStart(false)
	{
		m_timer.SetOwner(this);
	}

	/// Virtual Destructor
	virtual ~wxAlarm(void);

	/// Sets a owner to which the alarm events should be posted.
	void SetOwner(wxEvtHandler *owner, int id = wxID_ANY)
	{
		m_owner = owner;
		m_id = id;
	}

	/// Returns the ID of the alarm object.
	int GetId() const
	{
		return m_id;
	}

	/// Adds a alarm given a time and data associated with the alarm, returns falls if the time had already elapsed.
	bool AddAlarm(wxDateTime time, void *data=NULL);

	/// Removes a alarm, given the data pointer associated with the alarm. The data pointer should be unique,
	/// else it will remove all the alarm associated with it.
	bool RemoveAlarm(void *data);

	/// Removes all the alarms, for a given the date/time.
	bool RemoveAlarm(wxDateTime time);

	/// Returns the total number of alarm added to wxAlarm.
	int GetAlarmsCount(void) const
	{
		return (int)m_mapAlarms.size();
	}

	/// Find alarm data from given date/time. Return alarm data of first found.
	void* FindAlarm(wxDateTime time);

	/// Find alarm date/time from given data. Return alarm date/time of first found.
	wxDateTime FindAlarm(void *data);

	/// Removes all alarms and send a cancel notification to the owner.
	bool RemoveAllAlarms(void);

	/// Refreshes the alarm, based on the data/time. Return false if the alarm is in stopped mode or isn't started yet.
	bool RefreshAlarms(void);

	/// Start wxAlarm
	bool Start()
	{
		m_bStart = true;
		RefreshAlarms();
	}
	
	/// Stop wxAlarm
	void Stop()
	{
		m_bStart = false;
		m_timer.Stop();
	}

protected:
	/// Handles the timer event, and notifies the client about the alarm. It also sets the timer to next alarm.
	void OnTimerEvent(wxTimerEvent &event);

	/// Generates a alarm event for given alarm, with given status
	virtual void NotifyAlarm(unsigned long time, void *data, wxAlarmEvent::wxAlarmStatus status);
};

#endif
