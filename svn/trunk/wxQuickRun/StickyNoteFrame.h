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
 *	\file StickyNoteFrame.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/bmpbuttn.h>
#include "GradientPanel.h"

class CStickyNoteFrame : public wxFrame
{
private:
	wxTextCtrl *m_pTextCtrlNote;
	wxStaticText *m_pStaticTextTime;
	wxBitmapButton *m_pButtonStayOnTop;
	wxBitmapButton *m_pButtonSysMenu;
	wxBitmapButton *m_pButtonClose;
	CGradientPanel *m_pGradientPanel;
	wxString m_strTitle;
	wxSize m_sizeMoveDiff;
	bool m_bMoving;
	bool m_bStayOnTop;

public:
	CStickyNoteFrame(wxWindow* parent, wxWindowID id = CStickyNoteFrame::wxID_FRAME_NOTES, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(250, 225), long style = wxRESIZE_BORDER|wxFRAME_NO_TASKBAR|wxNO_BORDER, const wxString& name = wxT("Notes frame"));
	virtual ~CStickyNoteFrame(void);

private:
	void CreateGUIControls(void);
	void OnClose(wxCloseEvent &event);
	void OnSysMenuButton(wxCommandEvent& WXUNUSED(event));
	void OnStayOnTopButton(wxCommandEvent& WXUNUSED(event));
	void OnCloseButton(wxCommandEvent& WXUNUSED(event));
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnImportFromFile(wxCommandEvent &event);
	void OnSaveToFile(wxCommandEvent &event);
	void OnSetTitle(wxCommandEvent &event);

public:
	enum 
	{
		wxID_FRAME_NOTES = wxID_HIGHEST + 1700,
		wxID_TEXTCTRL_NOTE,
		wxID_STATIC_TEXT_TIME,
		wxID_STATUSBAR,
		wxID_BITMAP_BUTTON_SYSMENU,
		wxID_BITMAP_BUTTON_STAY_ON_TOP,
		wxID_MENU_SET_TITLE,
		wxID_MENU_SAVE,
		wxID_MENU_SAVE_TO_FILE,
		wxID_MENU_NEW_NOTE,
		wxID_MENU_IMPORT_FROM_FILE,
		wxID_MENU_DELETE_NOTE,
		wxID_MENU_COLOR_BLUE,
		wxID_MENU_COLOR_PINK,
		wxID_MENU_COLOR_GREEN
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
