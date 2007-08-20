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
 *	\file SetupDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 23 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/wxFlatNotebook/wxFlatNotebook.h>

class CSetupDialog : public wxDialog
{
public:
	CSetupDialog(wxWindow* parent, wxWindowID id, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 400), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Setup Dialog"));
	virtual ~CSetupDialog(void);

private:
	void OnClose(wxCloseEvent &event);
	void CreateGUIControls();

public:
	enum
	{
		wxID_DIALOG_SETUP = wxID_HIGHEST + 650,
		wxID_NOTEBOOK_FLAT,
		wxID_PANEL_KEYWORDS,
		wxID_PANEL_TASKS,
		wxID_PANEL_CONTACTS,
		wxID_PANEL_NOTES,
		wxID_PANEL_DISPLAY
	};

private:
	wxFlatNotebook *m_pFlatNotebook;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
