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
 *	\file NotesPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 3 Jul, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/combobox.h>

class CNotesPanel : public wxPanel
{
public:
	CNotesPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Notes Panel"));
	virtual ~CNotesPanel(void);

private:
	void OnTextNoteChange(wxCommandEvent &event);
	void OnCopyText(wxCommandEvent &event);
	void OnSaveText(wxCommandEvent &event);
	void OnAddNote(wxCommandEvent &event);
	void OnDeleteNote(wxCommandEvent &event);
	void OnPreviousNote(wxCommandEvent &event);
	void OnNextNote(wxCommandEvent &event);
	void OnNoteIDSelection(wxCommandEvent &event);
	void CreateGUIControls();
	void RefreshNote(int nNoteID);
	void RefreshNavigationControls(wxLongLong nID);

public:
	static wxLongLong AddNote(wxString);

private:
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonDelete;
	wxButton *m_pButtonCopy;
	wxButton *m_pButtonSave;
	wxButton *m_pButtonPrevious;
	wxButton *m_pButtonNext;
	wxTextCtrl *m_pTextCtrlNote;
	wxComboBox *m_pComboBoxNoteID;

	enum
	{
		wxID_BUTTON_ADD = wxID_HIGHEST + 1300,
		wxID_BUTTON_DELETE,
		wxID_BUTTON_COPY,
		wxID_BUTTON_SAVE,
		wxID_BUTTON_PREVIOUS,
		wxID_BUTTON_NEXT,
		wxID_TEXTCTRL_NOTE,
		wxID_COMBOBOX_NOTE_ID
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
