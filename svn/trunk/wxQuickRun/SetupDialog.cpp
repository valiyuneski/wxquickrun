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
 *	\file SetupDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 23 Jun, 2006
 **/

#include "SetupDialog.h"
#include "KeywordsListPanel.h"
#include "TasksPanel.h"
#include "OptionsPanel.h"
#include "NotesPanel.h"
#include "ContactsPanel.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CSetupDialog, wxDialog)
	EVT_CLOSE(CSetupDialog::OnClose)
END_EVENT_TABLE()

CSetupDialog::CSetupDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pFlatNotebook(NULL)
{
	CreateGUIControls();
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CSetupDialog::~CSetupDialog(void)
{
	wxFlatNotebook::CleanUp();
}

void CSetupDialog::OnClose(wxCloseEvent &event)
{
	for(int i=0; i < m_pFlatNotebook->GetPageCount(); i++)
	{
		m_pFlatNotebook->GetPage(i)->Close();
	}
	m_pFlatNotebook->Close();
	event.Skip(true);
}

void CSetupDialog::CreateGUIControls()
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pFlatNotebook = new wxFlatNotebook(this, wxID_NOTEBOOK_FLAT, wxDefaultPosition, wxDefaultSize, wxFNB_TABS_BORDER_SIMPLE | wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG);
	CKeywordsListPanel *pKeywordsPanel = new CKeywordsListPanel(m_pFlatNotebook, wxID_PANEL_KEYWORDS);
	CTasksPanel *pTasksPanel = new CTasksPanel(m_pFlatNotebook, wxID_PANEL_TASKS);
	CContactsPanel *pContactsPanel = new CContactsPanel(m_pFlatNotebook, wxID_PANEL_CONTACTS);
	CNotesPanel *pNotesPanel = new CNotesPanel(m_pFlatNotebook, wxID_PANEL_NOTES);
	COptionsPanel *pDisplayPanel = new COptionsPanel(m_pFlatNotebook, wxID_PANEL_DISPLAY);
	m_pFlatNotebook->AddPage(pKeywordsPanel, wxT("Keywords"), true);
	m_pFlatNotebook->AddPage(pTasksPanel, wxT("Tasks"), false);
	m_pFlatNotebook->AddPage(pContactsPanel, wxT("Contacts"), false);
	m_pFlatNotebook->AddPage(pNotesPanel, wxT("Notes"), false);
	m_pFlatNotebook->AddPage(pDisplayPanel, wxT("Options"), false);
	pMainSizer->Add(m_pFlatNotebook, 1, wxALL | wxEXPAND, 0);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
}
