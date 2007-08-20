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
 *	\file SearchEntryDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Nov, 2006
 **/

#include "SearchEntryDlg.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CSearchEntryDlg, wxDialog)
	EVT_CLOSE(CSearchEntryDlg::OnClose)
	EVT_BUTTON(wxID_OK, CSearchEntryDlg::OnOK)
	EVT_INIT_DIALOG(CSearchEntryDlg::OnInitDialog)
END_EVENT_TABLE()

CSearchEntryDlg::CSearchEntryDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pTextCtrlEngineName(NULL)
, m_pTextCtrlEngineURL(NULL)
, m_bEditMode(false)
{
}

CSearchEntryDlg::~CSearchEntryDlg(void)
{
}

void CSearchEntryDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CSearchEntryDlg::OnInitDialog(wxInitDialogEvent &event)
{
	/// Sizer for adding the controls created by users
	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer *pSearchStaticSizer;
	if(m_bEditMode)
		pSearchStaticSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Edit Search Engine"));
	else
		pSearchStaticSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Add Search Engine"));

	wxStaticText *pStaticTextEngineName = new wxStaticText(this, wxID_ANY, wxT("&Name:"));
	m_pTextCtrlEngineName = new wxTextCtrl(this, wxID_TEXTCTRL_ENGINE_NAME, m_strEngineName);
	wxStaticText *pStaticTextEngineURL = new wxStaticText(this, wxID_ANY, wxT("&URL:"));
	m_pTextCtrlEngineURL = new wxTextCtrl(this, wxID_TEXTCTRL_ENGINE_URL, m_strEngineURL);
	pSearchStaticSizer->Add(pStaticTextEngineName, 1, wxALL|wxEXPAND, 5);
	pSearchStaticSizer->Add(m_pTextCtrlEngineName, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
	pSearchStaticSizer->Add(pStaticTextEngineURL, 1, wxALL|wxEXPAND, 5);
	pSearchStaticSizer->Add(m_pTextCtrlEngineURL, 1, wxLEFT|wxRIGHT|wxEXPAND, 5);
	pMainSizer->Add(pSearchStaticSizer, 1, wxALL|wxEXPAND, 5);
	pMainSizer->Add(CreateButtonSizer(wxOK|wxCANCEL), 0, wxALL|wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
}

void CSearchEntryDlg::OnOK(wxCommandEvent &event)
{
	m_strEngineName = m_pTextCtrlEngineName->GetValue();
	m_strEngineURL = m_pTextCtrlEngineURL->GetValue();
	m_strEngineName = m_strEngineName.Trim(true);
	m_strEngineURL = m_strEngineURL.Trim(true);
	if(m_strEngineName == wxEmptyString || m_strEngineURL == wxEmptyString)
		wxMessageBox(wxT("Please enter the search engine name and URL."), wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_ERROR, this);
	else
		event.Skip(true);
}

wxString CSearchEntryDlg::GetSearchEngineName(void)
{
	return m_strEngineName;
}

void CSearchEntryDlg::SetSearchEngineName(wxString strEngineName)
{
	m_strEngineName = strEngineName;
}

wxString CSearchEntryDlg::GetSearchEngineURL(void)
{
	return m_strEngineURL;
}

void CSearchEntryDlg::SetSearchEngineURL(wxString strEngineURL)
{
	m_strEngineURL = strEngineURL;
}

bool CSearchEntryDlg::IsEditMode(void)
{
	return m_bEditMode;
}

void CSearchEntryDlg::SetEditMode(bool bEditMode)
{
	m_bEditMode = bEditMode;
}
