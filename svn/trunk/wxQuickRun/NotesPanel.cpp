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
 *	\file NotesPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 3 Jul, 2006
 **/

#include "NotesPanel.h"
#include "wxQuickRun.h"
#include <wx/clipbrd.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CNotesPanel, wxPanel)
	EVT_TEXT(wxID_TEXTCTRL_NOTE, CNotesPanel::OnTextNoteChange)
	EVT_BUTTON(wxID_BUTTON_COPY, CNotesPanel::OnCopyText)
	EVT_BUTTON(wxID_BUTTON_SAVE, CNotesPanel::OnSaveText)
	EVT_BUTTON(wxID_BUTTON_ADD, CNotesPanel::OnAddNote)
	EVT_BUTTON(wxID_BUTTON_DELETE, CNotesPanel::OnDeleteNote)
	EVT_BUTTON(wxID_BUTTON_PREVIOUS, CNotesPanel::OnPreviousNote)
	EVT_BUTTON(wxID_BUTTON_NEXT, CNotesPanel::OnNextNote)
	EVT_COMBOBOX(wxID_COMBOBOX_NOTE_ID, CNotesPanel::OnNoteIDSelection)
END_EVENT_TABLE()

CNotesPanel::CNotesPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
, m_pButtonAdd(NULL)
, m_pButtonDelete(NULL)
, m_pButtonCopy(NULL)
, m_pButtonSave(NULL)
, m_pButtonPrevious(NULL)
, m_pButtonNext(NULL)
, m_pTextCtrlNote(NULL)
, m_pComboBoxNoteID(NULL)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
}

CNotesPanel::~CNotesPanel(void)
{
}

void CNotesPanel::CreateGUIControls()
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(pMainSizer);
	wxArrayString arrayNotesID;

	m_pTextCtrlNote = new wxTextCtrl(this, wxID_TEXTCTRL_NOTE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_BESTWRAP);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_ADD, wxT("&Add"));
	m_pButtonDelete = new wxButton(this, wxID_BUTTON_DELETE, wxT("&Delete"));
	m_pButtonCopy = new wxButton(this, wxID_BUTTON_COPY, wxT("&Copy"));
	m_pButtonSave = new wxButton(this, wxID_BUTTON_SAVE, wxT("&Save"));
	m_pButtonPrevious = new wxButton(this, wxID_BUTTON_PREVIOUS, wxT("<"));
	m_pComboBoxNoteID = new wxComboBox(this, wxID_COMBOBOX_NOTE_ID, wxEmptyString, wxDefaultPosition, wxDefaultSize, arrayNotesID, wxCB_READONLY);
	m_pButtonNext = new wxButton(this, wxID_BUTTON_NEXT, wxT(">"));

	wxBoxSizer *pControlsSizer = new wxBoxSizer(wxHORIZONTAL);
	pControlsSizer->Add(m_pButtonAdd, 2, wxLEFT | wxTOP | wxBOTTOM | wxEXPAND, 5);
	pControlsSizer->Add(m_pButtonDelete, 2, wxALL | wxEXPAND, 5);
	pControlsSizer->AddStretchSpacer(1);
	pControlsSizer->Add(m_pButtonCopy, 2, wxLEFT | wxTOP | wxBOTTOM | wxEXPAND, 5);
	pControlsSizer->Add(m_pButtonSave, 2, wxALL | wxEXPAND, 5);
	pControlsSizer->AddStretchSpacer(1);
	pControlsSizer->Add(m_pButtonPrevious, 1, wxLEFT | wxTOP | wxBOTTOM | wxEXPAND, 5);
	pControlsSizer->Add(m_pComboBoxNoteID, 2, wxALL | wxEXPAND, 5);
	pControlsSizer->Add(m_pButtonNext, 1, wxRIGHT | wxTOP | wxBOTTOM | wxEXPAND, 5);

	pMainSizer->Add(m_pTextCtrlNote, 1, wxALL | wxEXPAND, 10);
	pMainSizer->Add(pControlsSizer, 0, wxALL | wxEXPAND, 5);

	SetAutoLayout (true);
	Layout();

	m_pButtonCopy->Disable();
	m_pButtonSave->Disable();
	m_pButtonAdd->Disable();
	m_pButtonDelete->Disable();
	m_pButtonPrevious->Disable();
	m_pButtonNext->Disable();

	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	int nID = -1;
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT ID from notes LIMIT 1;"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			nID = result.GetInt(0);
		}
		result.Finalize();
	}
	if(nID != -1)
		RefreshNote(nID);
}

void CNotesPanel::OnTextNoteChange(wxCommandEvent &event)
{
	if(m_pTextCtrlNote->GetValue().Length()==0)
	{
		m_pButtonCopy->Disable();
		m_pButtonSave->Disable();
		m_pButtonAdd->Disable();
	}
	else
	{
		m_pButtonCopy->Enable();
		m_pButtonAdd->Enable();
		if(m_pComboBoxNoteID->GetValue() == wxEmptyString)
			m_pButtonSave->Disable();
		else
			m_pButtonSave->Enable();
	}
}

void CNotesPanel::OnCopyText(wxCommandEvent &event)
{
	wxString strText = m_pTextCtrlNote->GetStringSelection();
	if (strText == wxEmptyString)
	{
		strText = m_pTextCtrlNote->GetValue();
	}
	// Write text to the clipboard
	if (wxTheClipboard->Open())
	{
		// This data objects are held by the clipboard, 
		// so do not delete them in the app.
		wxTheClipboard->SetData( new wxTextDataObject(strText) );
		wxTheClipboard->Close();
	}
}

void CNotesPanel::OnSaveText(wxCommandEvent &event)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxT("UPDATE notes SET note = ? WHERE ID = ?;");
		wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
		stmt.Bind(1, m_pTextCtrlNote->GetValue());
		stmt.Bind(2, wxAtoi(m_pComboBoxNoteID->GetValue()));
		stmt.ExecuteUpdate();
	}
}

void CNotesPanel::OnAddNote(wxCommandEvent &event)
{
	RefreshNavigationControls(AddNote(m_pTextCtrlNote->GetValue()));
}

wxLongLong CNotesPanel::AddNote(wxString strNote)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	wxString sqlCmd = wxString::Format(wxT("Insert INTO notes('note') VALUES(?)"));
	wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
	// Bind the variables to the SQL statement
	stmt.Bind(1, strNote);
	// Execute the SQL Query
	stmt.ExecuteUpdate();
	wxLongLong nID = dbConn->GetLastRowId();
	return nID;
}

void CNotesPanel::OnDeleteNote(wxCommandEvent &event)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("DELETE FROM notes WHERE ID = %d;"), wxAtoi(m_pComboBoxNoteID->GetValue()));
		dbConn->ExecuteUpdate(sqlCmd);
	}
	m_pTextCtrlNote->SetValue(wxEmptyString);
	m_pComboBoxNoteID->Delete(m_pComboBoxNoteID->GetSelection());
	m_pComboBoxNoteID->SetSelection(0);
	int nID = wxAtoi(m_pComboBoxNoteID->GetValue());
	RefreshNote(nID);
}

void CNotesPanel::OnPreviousNote(wxCommandEvent &event)
{
	int nSel = m_pComboBoxNoteID->GetSelection();
	nSel--;
	m_pComboBoxNoteID->SetSelection(nSel);
	int nID = wxAtoi(m_pComboBoxNoteID->GetValue());
	RefreshNote(nID);
}

void CNotesPanel::OnNextNote(wxCommandEvent &event)
{
	int nSel = m_pComboBoxNoteID->GetSelection();
	nSel++;
	m_pComboBoxNoteID->SetSelection(nSel);
	int nID = wxAtoi(m_pComboBoxNoteID->GetValue());
	RefreshNote(nID);
}

void CNotesPanel::OnNoteIDSelection(wxCommandEvent &event)
{
	int nID = wxAtoi(m_pComboBoxNoteID->GetValue());
	RefreshNote(nID);
}

void CNotesPanel::RefreshNote(int nID)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT note from notes WHERE ID = %d;"), nID);
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			m_pTextCtrlNote->SetValue(result.GetString(0));
		}
		result.Finalize();
	}
	RefreshNavigationControls(nID);
}

void CNotesPanel::RefreshNavigationControls(wxLongLong nID)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("notes")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE notes(ID INTEGER PRIMARY KEY AUTOINCREMENT, note TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT ID from notes;"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		m_pComboBoxNoteID->Clear();
		while(result.NextRow())
		{
			m_pComboBoxNoteID->Append(wxString::Format(wxT("%d"), result.GetInt(0)));
		}
		result.Finalize();
		m_pComboBoxNoteID->SetValue(wxString::Format(wxT("%d"), nID));
	}
	int nSel = m_pComboBoxNoteID->GetSelection();
	int nCount = m_pComboBoxNoteID->GetCount();
	m_pButtonPrevious->Enable();
	m_pButtonNext->Enable();
	if(nCount == 0 || nSel == 0)
		m_pButtonPrevious->Disable();
	if(nSel+1 == nCount)
		m_pButtonNext->Disable();
	if(nCount > 0)
		m_pButtonDelete->Enable();
	else
	{
		m_pButtonDelete->Disable();
		m_pButtonSave->Disable();
		m_pComboBoxNoteID->SetValue(wxEmptyString);
	}
}