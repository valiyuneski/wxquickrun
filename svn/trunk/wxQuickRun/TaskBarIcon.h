/**
 *	wxQuickRun
 *	Copyright � 2006-2007, Priyank Bolia.
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
 *	\file TaskBarIcon.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "stdwx.h" 
#include <wx/taskbar.h>

class CTaskBarIcon : public wxTaskBarIcon
{
private:
	/**
	 * \var wxWindow *m_pParent;
	 * \breif Pointer to the main application frame/window.
	 */
	wxWindow *m_pParent;

public:
	CTaskBarIcon(wxWindow *pParent);
	virtual ~CTaskBarIcon(void);

private:
	virtual wxMenu *CreatePopupMenu();

private:
	void OnMenuExit(wxCommandEvent& WXUNUSED(event));
	void OnMenuAbout(wxCommandEvent& WXUNUSED(event));
	void OnMenuShowHide(wxCommandEvent& WXUNUSED(event));
	void OnMenuSetup(wxCommandEvent& WXUNUSED(event));
	void OnUpdateMenuShowHide(wxUpdateUIEvent &event);
	void OnLeftButtonDClick(wxTaskBarIconEvent& WXUNUSED(event));

private:
	enum
	{
		wxID_TASKBAR_ABOUT = wxID_HIGHEST + 400,
		wxID_TASKBAR_EXIT,
		wxID_TASKBAR_SHOW_HIDE,
		wxID_TASKBAR_SETUP
	};

private:
	DECLARE_EVENT_TABLE()
};
