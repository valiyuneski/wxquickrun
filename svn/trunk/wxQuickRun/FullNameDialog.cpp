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
 *	\file FullNameDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Aug, 2006
 **/

#include "FullNameDialog.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CFullNameDialog, wxDialog)
	EVT_CLOSE(CFullNameDialog::OnClose)
	EVT_BUTTON(wxID_OK, CFullNameDialog::OnOK)
	EVT_INIT_DIALOG(CFullNameDialog::OnInitDialog)
END_EVENT_TABLE()

CFullNameDialog::CFullNameDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticTextTitle(NULL)
, m_pStaticTextFirst(NULL)
, m_pStaticTextMiddle(NULL)
, m_pStaticTextLast(NULL)
, m_pStaticTextSuffix(NULL)
, m_pComboBoxTitle(NULL)
, m_pTextCtrlFirst(NULL)
, m_pTextCtrlMiddle(NULL)
, m_pTextCtrlLast(NULL)
, m_pComboBoxSuffix(NULL)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CFullNameDialog::~CFullNameDialog(void)
{
}

void CFullNameDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CFullNameDialog::OnInitDialog(wxInitDialogEvent &event)
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Full &name:"));
	wxBoxSizer *pControlsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pStaticTextSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlSizer = new wxBoxSizer(wxVERTICAL);

	m_pStaticTextTitle = new wxStaticText(this, wxID_STATIC_TEXT_TITLE, wxT("&Title:"));
	wxArrayString arrayTitle;
	arrayTitle.Add(wxT(""));
	arrayTitle.Add(wxT("Mr."));
	arrayTitle.Add(wxT("Mrs."));
	arrayTitle.Add(wxT("Ms."));
	arrayTitle.Add(wxT("Miss."));
	arrayTitle.Add(wxT("Dr."));
	arrayTitle.Add(wxT("Er."));
	m_pComboBoxTitle = new wxComboBox(this, wxID_COMBOBOX_TITLE, m_strTitle, wxDefaultPosition, wxDefaultSize, arrayTitle, wxCB_DROPDOWN);
	m_pStaticTextFirst = new wxStaticText(this, wxID_STATIC_TEXT_FIRST, wxT("&First:"));
	m_pTextCtrlFirst = new wxTextCtrl(this, wxID_TEXTCTRL_FIRST, m_strFirstName);
	m_pStaticTextMiddle = new wxStaticText(this, wxID_STATIC_TEXT_MIDDLE, wxT("&Middle:"));
	m_pTextCtrlMiddle = new wxTextCtrl(this, wxID_STATIC_TEXT_MIDDLE, m_strMiddleName);
	m_pStaticTextLast = new wxStaticText(this, wxID_STATIC_TEXT_LAST, wxT("&Last:"));
	m_pTextCtrlLast = new wxTextCtrl(this, wxID_TEXTCTRL_LAST, m_strLastName);
	m_pStaticTextSuffix = new wxStaticText(this, wxID_STATIC_TEXT_SUFFIX, wxT("&Suffix:"));
	wxArrayString arraySuffix;
	arraySuffix.Add(wxT(""));
	arraySuffix.Add(wxT("Sr."));
	arraySuffix.Add(wxT("Jr."));
	arraySuffix.Add(wxT("I"));
	arraySuffix.Add(wxT("II"));
	arraySuffix.Add(wxT("III"));
	arraySuffix.Add(wxT("Esq."));
	m_pComboBoxSuffix = new wxComboBox(this, wxID_COMBOBOX_SUFFIX, m_strSuffix, wxDefaultPosition, wxDefaultSize, arraySuffix, wxCB_DROPDOWN);

	pStaticTextSizer->Add(m_pStaticTextTitle, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextFirst, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextMiddle, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextLast, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextSuffix, 1, wxALL | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pComboBoxTitle, 1, wxALL | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlFirst, 1, wxALL | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlMiddle, 1, wxALL | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlLast, 1, wxALL | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pComboBoxSuffix, 1, wxALL | wxEXPAND, 5);

	pControlsSizer->Add(pStaticTextSizer, 0, wxALL | wxEXPAND, 0);
	pControlsSizer->Add(pTextCtrlSizer, 1, wxALL | wxEXPAND, 0);
	pStaticBoxSizer->Add(pControlsSizer, 1, wxALL | wxEXPAND, 0);
	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 10);

	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	SetSizer(pMainSizer);
	SetAutoLayout(true);
	Layout();
}

void CFullNameDialog::OnOK(wxCommandEvent& event)
{
	event.Skip(true);
}

wxString CFullNameDialog::GetName(void)
{
	wxString strFullName = wxString::Format(wxT("%s %s %s %s %s"), m_pComboBoxTitle->GetValue(), m_pTextCtrlFirst->GetValue(), m_pTextCtrlMiddle->GetValue(), m_pTextCtrlLast->GetValue(), m_pComboBoxSuffix->GetValue());
	while(strFullName.Replace(wxT("  "), wxT(" "), true));
	strFullName.Trim(false);
	strFullName.Trim(true);
	return strFullName;
}

wxString CFullNameDialog::GetTitle(void)
{
	return m_pComboBoxTitle->GetValue();
}

wxString CFullNameDialog::GetFirstName(void)
{
	return m_pTextCtrlFirst->GetValue();
}

wxString CFullNameDialog::GetMiddleName(void)
{
	return m_pTextCtrlMiddle->GetValue();
}

wxString CFullNameDialog::GetLastName(void)
{
	return m_pTextCtrlLast->GetValue();
}

wxString CFullNameDialog::GetSuffix(void)
{
	return m_pComboBoxSuffix->GetValue();
}

void CFullNameDialog::SetTitle(wxString strTitle)
{
	m_strTitle = strTitle;
}

void CFullNameDialog::SetFirstName(wxString strFirstName)
{
	m_strFirstName = strFirstName;
}

void CFullNameDialog::SetMiddleName(wxString strMiddleName)
{
	m_strMiddleName = strMiddleName;
}

void CFullNameDialog::SetLastName(wxString strLastName)
{
	m_strLastName = strLastName;
}

void CFullNameDialog::SetSuffix(wxString strSuffix)
{
	m_strSuffix = strSuffix;
}
