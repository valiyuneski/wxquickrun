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
 *	\file StickyNoteFrame.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/
#include "StickyNoteFrame.h"
#include <wx/statline.h>
#include <wx/textfile.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CStickyNoteFrame, wxFrame)
	EVT_CLOSE(CStickyNoteFrame::OnClose)
	EVT_BUTTON(wxID_BITMAP_BUTTON_SYSMENU, CStickyNoteFrame::OnSysMenuButton)
	EVT_BUTTON(wxID_BITMAP_BUTTON_STAY_ON_TOP, CStickyNoteFrame::OnStayOnTopButton)
	EVT_BUTTON(wxID_CLOSE, CStickyNoteFrame::OnCloseButton)
	EVT_MENU(wxID_CLOSE, CStickyNoteFrame::OnCloseButton)
	EVT_MENU(wxID_MENU_IMPORT_FROM_FILE, CStickyNoteFrame::OnImportFromFile)
	EVT_MENU(wxID_MENU_SET_TITLE, CStickyNoteFrame::OnSetTitle)
	EVT_LEFT_DOWN(CStickyNoteFrame::OnLeftDown)
	EVT_LEFT_UP(CStickyNoteFrame::OnLeftUp)
	EVT_MOTION(CStickyNoteFrame::OnMouseMove)
	EVT_SIZE(CStickyNoteFrame::OnSize)
END_EVENT_TABLE()

CStickyNoteFrame::CStickyNoteFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxFrame(parent, id, title, pos, size, style, name)
, m_pTextCtrlNote(NULL)
, m_pButtonStayOnTop(NULL)
, m_pButtonSysMenu(NULL)
, m_pButtonClose(NULL)
, m_pStaticTextTime(NULL)
, m_bMoving(false)
, m_bStayOnTop(false)
{
	CreateGUIControls();
}

CStickyNoteFrame::~CStickyNoteFrame(void)
{
}

void CStickyNoteFrame::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CStickyNoteFrame::CreateGUIControls()
{
	SetBackgroundColour(wxColor(255, 255, 216));
	///Sizer for adding the controls created by users
	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pTextCtrlNote = new wxTextCtrl(this, wxID_TEXTCTRL_NOTE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTE_MULTILINE|wxTE_RICH2);
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonSysMenu = new wxBitmapButton(this, wxID_BITMAP_BUTTON_SYSMENU, wxBITMAP(IDB_BITMAP_NOTE), wxDefaultPosition, wxDefaultSize, 0);
	m_pButtonStayOnTop = new wxBitmapButton(this, wxID_BITMAP_BUTTON_STAY_ON_TOP, wxBITMAP(IDB_BITMAP_PIN_OPEN), wxDefaultPosition, wxDefaultSize, 0);
	m_pButtonStayOnTop->SetBitmapFocus(wxBITMAP(IDB_BITMAP_PIN_HOVER));
	m_pButtonStayOnTop->SetBitmapSelected(wxBITMAP(IDB_BITMAP_PIN_CLOSE));
	m_pGradientPanel = new CGradientPanel(this);
	//m_pButtonClose = new wxBitmapButton(this, wxID_CLOSE, wxT("X"));
	m_pButtonSysMenu->SetBackgroundColour(wxColor(255, 255, 216));
	m_pButtonStayOnTop->SetBackgroundColour(wxColor(255, 255, 216));
	pButtonSizer->Add(m_pButtonSysMenu, 0, wxALL|wxEXPAND, 0);
	pButtonSizer->Add(m_pButtonStayOnTop, 0, wxALL|wxEXPAND, 0);
	pButtonSizer->Add(m_pGradientPanel, 1, wxTOP|wxBOTTOM|wxEXPAND, 5);
	//pButtonSizer->Add(m_pButtonClose, 0, wxALL|wxEXPAND, 0);
	m_pTextCtrlNote->SetBackgroundColour(wxColor(255, 255, 216));
	m_pStaticTextTime = new wxStaticText(this, wxID_STATIC_TEXT_TIME, wxDateTime::Now().Format(wxT("%d %b, %Y %I:%M %p")));
	m_pStaticTextTime->SetBackgroundColour(wxColor(255, 255, 216));
	wxStaticLine *pStaticLine = new wxStaticLine(this);
	pMainSizer->Add(pButtonSizer, 0, wxALL|wxEXPAND, 0);
	pMainSizer->Add(m_pTextCtrlNote, 1, wxALL|wxEXPAND, 0);
	pMainSizer->Add(pStaticLine, 0, wxLEFT| wxRIGHT | wxEXPAND, 5);
	pMainSizer->Add(m_pStaticTextTime, 0, wxLEFT| wxRIGHT | wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	CenterOnScreen(wxBOTH);
#ifdef __WXMSW__
	::SetParent((HWND)GetHWND(), HWND_DESKTOP);
	::SetWindowPos((HWND)GetHWND(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	::SetForegroundWindow((HWND)GetHWND());
#endif
}

void CStickyNoteFrame::OnSysMenuButton(wxCommandEvent& WXUNUSED(event))
{
	wxMenu *pContextMenu = new wxMenu(wxEmptyString);
	pContextMenu->Append(wxID_MENU_NEW_NOTE, wxT("&New Note"));
	pContextMenu->AppendSeparator();
	pContextMenu->Append(wxID_MENU_SAVE, wxT("&Save Note"));
	pContextMenu->Append(wxID_MENU_SAVE_TO_FILE, wxT("Save To &File"));
	pContextMenu->Append(wxID_MENU_IMPORT_FROM_FILE, wxT("&Import From File"));
	pContextMenu->Append(wxID_MENU_DELETE_NOTE, wxT("&Delete Note"));
	pContextMenu->AppendSeparator();
	pContextMenu->Append(wxID_MENU_SET_TITLE, wxT("S&et Title"));
	pContextMenu->AppendSeparator();
	pContextMenu->Append(wxID_CLOSE, wxT("&Close"));
	PopupMenu(pContextMenu, m_pButtonSysMenu->GetPosition().x, m_pButtonSysMenu->GetPosition().y+m_pButtonSysMenu->GetSize().GetHeight());
	delete pContextMenu;
}

void CStickyNoteFrame::OnStayOnTopButton(wxCommandEvent& WXUNUSED(event))
{
	if(m_bStayOnTop)
		SetWindowStyle(GetWindowStyle()|wxSTAY_ON_TOP);
	else
		SetWindowStyle(GetWindowStyle()^wxSTAY_ON_TOP);
	Refresh();
}

void CStickyNoteFrame::OnCloseButton(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void CStickyNoteFrame::OnLeftDown(wxMouseEvent &event)
{
	m_bMoving = true;
	wxPoint point = event.GetPosition();
	m_sizeMoveDiff = wxSize(point.x, point.y);
	CaptureMouse();
}

void CStickyNoteFrame::OnLeftUp(wxMouseEvent &event)
{
	m_bMoving = false;
	ReleaseMouse();
}

void CStickyNoteFrame::OnMouseMove(wxMouseEvent &event)
{
	if(m_bMoving && HasCapture())
	{
		wxPoint point = event.GetPosition();
		wxPoint position = GetPosition();
		SetSize(position.x+point.x-m_sizeMoveDiff.GetWidth(), position.y+point.y-m_sizeMoveDiff.GetHeight(), -1, -1, wxSIZE_USE_EXISTING);
	}
}

void CStickyNoteFrame::OnSize(wxSizeEvent &event)
{
	m_pGradientPanel->Refresh(true);
	event.Skip(true);
}

void CStickyNoteFrame::OnSaveToFile(wxCommandEvent &event)
{
	wxFileDialog fileDlg(this, wxT("Browse"), wxEmptyString, wxEmptyString, wxT("All Files (*.*)|*.*"), wxSAVE|wxOVERWRITE_PROMPT);
	if(fileDlg.ShowModal()==wxID_OK)
	{
		wxTextFile writeFile(fileDlg.GetPath());
		writeFile.Create();
		writeFile.Open();
		for(int i=0; i<m_pTextCtrlNote->GetNumberOfLines(); i++)
		{
			writeFile.AddLine(m_pTextCtrlNote->GetLineText(i));
		}
		writeFile.Write();
		writeFile.Close();
	}
}

void CStickyNoteFrame::OnImportFromFile(wxCommandEvent &event)
{
	wxFileDialog fileDlg(this, wxT("Browse"), wxEmptyString, wxEmptyString, wxT("All Files (*.*)|*.*"), wxOPEN|wxFILE_MUST_EXIST);
	if(fileDlg.ShowModal()==wxID_OK)
	{
		wxTextFile readFile(fileDlg.GetPath());
		if( readFile.Exists() && readFile.Open() )
		{
			wxString strContents;
			for ( size_t i = 0; i < readFile.GetLineCount(); i++ )
			{
				strContents += (readFile.GetLine( i ) + wxT("\n"));
			}
			m_pTextCtrlNote->SetValue(strContents);
		}		
	}
}

void CStickyNoteFrame::OnSetTitle(wxCommandEvent &event)
{
	wxTextEntryDialog titleDlg(this, wxT("Enter the title of the note:"), wxT("wxQuickRun"));
	if(titleDlg.ShowModal()==wxID_OK)
	{
		m_strTitle = titleDlg.GetValue();
	}
}