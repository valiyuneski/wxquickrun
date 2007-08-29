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
 *	\file PrimaryDetailsPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Aug, 2006
 **/

#include "PrimaryDetailsPanel.h"
#include "FullNameDialog.h"
#include "RegExValidator.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CPrimaryDetailsPanel, wxPanel)
	EVT_CLOSE(CPrimaryDetailsPanel::OnClose)
	EVT_BUTTON(wxID_BUTTON_FULLNAME, CPrimaryDetailsPanel::OnFullNameButton)
END_EVENT_TABLE()

CPrimaryDetailsPanel::CPrimaryDetailsPanel(wxWindow* parent, wxWindowID id, int nEditContact, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
, m_nEditContact(nEditContact)
, m_pStaticTextTelephone(NULL)
, m_pStaticTextEmail(NULL)
, m_pStaticTextInstantMessaging(NULL)
, m_pStaticTextNickname(NULL)
, m_pButtonFullname(NULL)
, m_pTextCtrlFullname(NULL)
, m_pTextCtrlNickname(NULL)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
}

CPrimaryDetailsPanel::~CPrimaryDetailsPanel(void)
{
}

void CPrimaryDetailsPanel::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CPrimaryDetailsPanel::CreateGUIControls()
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* pStaticBoxSizer;
	if(m_nEditContact == -1)
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Add Contact:"));
	else
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Edit Contact:"));

	wxBoxSizer *pNameSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pStaticTextNameSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlNameSizer = new wxBoxSizer(wxVERTICAL);
	m_pButtonFullname = new wxButton(this, wxID_BUTTON_FULLNAME, wxT("&Full Name:"));
	m_pTextCtrlFullname = new wxTextCtrl(this, wxID_TEXTCTRL_FULLNAME, GetName(), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	m_pStaticTextNickname = new wxStaticText(this, wxID_STATIC_TEXT_NICKNAME, wxT(" &Nickname:"));
	m_pTextCtrlNickname = new wxTextCtrl(this, wxID_TEXTCTRL_NICKNAME, m_strNickName);
	pStaticTextNameSizer->Add(m_pButtonFullname, 1, wxALL | wxEXPAND, 5);
	pStaticTextNameSizer->Add(m_pStaticTextNickname, 1, wxALL | wxEXPAND, 5);
	pTextCtrlNameSizer->Add(m_pTextCtrlFullname, 1, wxALL | wxEXPAND, 5);
	pTextCtrlNameSizer->Add(m_pTextCtrlNickname, 1, wxALL | wxEXPAND, 5);
	pNameSizer->Add(pStaticTextNameSizer, 0, wxALL | wxEXPAND, 0);
	pNameSizer->Add(pTextCtrlNameSizer, 1, wxALL | wxEXPAND, 0);
	pStaticBoxSizer->Add(pNameSizer, 1, wxALL | wxEXPAND, 0);

	m_pStaticLine[0] = new wxStaticLine(this, wxID_ANY);
	pStaticBoxSizer->Add(m_pStaticLine[0], 0, wxALL | wxEXPAND, 5);

	wxBoxSizer *pEmailSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pStaticTextEmailSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlEmailSizer = new wxBoxSizer(wxVERTICAL);
	m_pStaticTextEmail = new wxStaticText(this, wxID_STATIC_TEXT_EMAIL, wxT("&Email:"));
	wxFont font = m_pStaticTextEmail->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	m_pStaticTextEmail->SetFont(font);
	pStaticBoxSizer->Add(m_pStaticTextEmail, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 5);
	wxArrayString arrayEmail;
	arrayEmail.Add(wxT("Work"));
	arrayEmail.Add(wxT("Home"));
	arrayEmail.Add(wxT("Other"));
	m_pComboEmail[0] = new wxComboBox(this, wxID_COMBOBOX_EMAIL_1, wxT("Work"), wxDefaultPosition, wxDefaultSize, arrayEmail, wxCB_READONLY);
	m_pTextCtrlEmail[0] = new wxTextCtrl(this, wxID_TEXTCTRL_EMAIL_1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT, wxRegExValidator(wxT("^[a-zA-Z][\\w\\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$"), &m_strEmail[0]));
	m_pComboEmail[1] = new wxComboBox(this, wxID_COMBOBOX_EMAIL_2, wxT("Home"), wxDefaultPosition, wxDefaultSize, arrayEmail, wxCB_READONLY);
	m_pTextCtrlEmail[1] = new wxTextCtrl(this, wxID_TEXTCTRL_EMAIL_2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_LEFT, wxRegExValidator(wxT("^[a-zA-Z][\\w\\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][\\w\\.-]*[a-zA-Z0-9]\\.[a-zA-Z][a-zA-Z\\.]*[a-zA-Z]$"), &m_strEmail[1]));
	pStaticTextEmailSizer->Add(m_pComboEmail[0], 1, wxALL | wxEXPAND, 5);
	pStaticTextEmailSizer->Add(m_pComboEmail[1], 1, wxALL | wxEXPAND, 5);
	pTextCtrlEmailSizer->Add(m_pTextCtrlEmail[0], 1, wxALL | wxEXPAND, 5);
	pTextCtrlEmailSizer->Add(m_pTextCtrlEmail[1], 1, wxALL | wxEXPAND, 5);
	pEmailSizer->Add(pStaticTextEmailSizer, 0, wxALL | wxEXPAND, 0);
	pEmailSizer->Add(pTextCtrlEmailSizer, 1, wxALL | wxEXPAND, 0);
	pStaticBoxSizer->Add(pEmailSizer, 1, wxALL | wxEXPAND, 0);

	m_pStaticLine[1] = new wxStaticLine(this, wxID_ANY);
	pStaticBoxSizer->Add(m_pStaticLine[1], 0, wxALL | wxEXPAND, 5);

	wxBoxSizer *pPhoneSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pStaticTextPhoneSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlPhoneSizer = new wxBoxSizer(wxVERTICAL);
	m_pStaticTextTelephone = new wxStaticText(this, wxID_STATIC_TEXT_TELEPHONE, wxT("&Telephone:"));
	font = m_pStaticTextTelephone->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	m_pStaticTextTelephone->SetFont(font);
	pStaticBoxSizer->Add(m_pStaticTextTelephone, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 5);
	wxArrayString arrayPhone;
	arrayPhone.Add(wxT("Business"));
	arrayPhone.Add(wxT("Home"));
	arrayPhone.Add(wxT("Mobile"));
	arrayPhone.Add(wxT("Fax"));
	arrayPhone.Add(wxT("VOIP"));
	arrayPhone.Add(wxT("Other"));
	m_pComboTelephone[0] = new wxComboBox(this, wxID_COMBOBOX_TELEPHONE_1, wxT("Business"), wxDefaultPosition, wxDefaultSize, arrayPhone, wxCB_READONLY);
	m_pTextCtrlTelephone[0] = new wxTextCtrl(this, wxID_TEXTCTRL_TELEPHONE_1, wxEmptyString);
	m_pComboTelephone[1] = new wxComboBox(this, wxID_COMBOBOX_TELEPHONE_2, wxT("Mobile"), wxDefaultPosition, wxDefaultSize, arrayPhone, wxCB_READONLY);
	m_pTextCtrlTelephone[1] = new wxTextCtrl(this, wxID_TEXTCTRL_TELEPHONE_2, wxEmptyString);
	pStaticTextPhoneSizer->Add(m_pComboTelephone[0], 1, wxALL | wxEXPAND, 5);
	pStaticTextPhoneSizer->Add(m_pComboTelephone[1], 1, wxALL | wxEXPAND, 5);
	pTextCtrlPhoneSizer->Add(m_pTextCtrlTelephone[0], 1, wxALL | wxEXPAND, 5);
	pTextCtrlPhoneSizer->Add(m_pTextCtrlTelephone[1], 1, wxALL | wxEXPAND, 5);
	pPhoneSizer->Add(pStaticTextPhoneSizer, 0, wxALL | wxEXPAND, 0);
	pPhoneSizer->Add(pTextCtrlPhoneSizer, 1, wxALL | wxEXPAND, 0);
	pStaticBoxSizer->Add(pPhoneSizer, 1, wxALL | wxEXPAND, 0);

	m_pStaticLine[2] = new wxStaticLine(this, wxID_ANY);
	pStaticBoxSizer->Add(m_pStaticLine[2], 0, wxALL | wxEXPAND, 5);

	wxBoxSizer *pIMSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *pStaticTextIMSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlIMSizer = new wxBoxSizer(wxVERTICAL);
	m_pStaticTextInstantMessaging = new wxStaticText(this, wxID_STATIC_TEXT_IM, wxT("Instant &Messaging:"));
	font = m_pStaticTextInstantMessaging->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	m_pStaticTextInstantMessaging->SetFont(font);
	pStaticBoxSizer->Add(m_pStaticTextInstantMessaging, 0, wxTOP | wxLEFT | wxRIGHT | wxEXPAND, 5);
	wxArrayString arrayIM;
	arrayIM.Add(wxT("AIM"));
	arrayIM.Add(wxT("Yahoo"));
	arrayIM.Add(wxT("GTalk"));
	arrayIM.Add(wxT("ICQ"));
	arrayIM.Add(wxT("Jabber"));
	arrayIM.Add(wxT("MSN"));
	arrayIM.Add(wxT("SIP"));
	arrayIM.Add(wxT("Corporate"));
	arrayIM.Add(wxT("Other"));
	m_pComboIM[0] = new wxComboBox(this, wxID_COMBOBOX_IM_1, wxT("AIM"), wxDefaultPosition, wxDefaultSize, arrayIM, wxCB_READONLY);
	m_pTextCtrlIM[0] = new wxTextCtrl(this, wxID_TEXTCTRL_IM_1, wxEmptyString);
	m_pComboIM[1] = new wxComboBox(this, wxID_COMBOBOX_IM_2, wxT("Jabber"), wxDefaultPosition, wxDefaultSize, arrayIM, wxCB_READONLY);
	m_pTextCtrlIM[1] = new wxTextCtrl(this, wxID_TEXTCTRL_IM_2, wxEmptyString);
	pStaticTextIMSizer->Add(m_pComboIM[0], 1, wxALL | wxEXPAND, 5);
	pStaticTextIMSizer->Add(m_pComboIM[1], 1, wxALL | wxEXPAND, 5);
	pTextCtrlIMSizer->Add(m_pTextCtrlIM[0], 1, wxALL | wxEXPAND, 5);
	pTextCtrlIMSizer->Add(m_pTextCtrlIM[1], 1, wxALL | wxEXPAND, 5);
	pIMSizer->Add(pStaticTextIMSizer, 0, wxALL | wxEXPAND, 0);
	pIMSizer->Add(pTextCtrlIMSizer, 1, wxALL | wxEXPAND, 0);
	pStaticBoxSizer->Add(pIMSizer, 1, wxALL | wxEXPAND, 0);

	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 10);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
}

void CPrimaryDetailsPanel::OnFullNameButton(wxCommandEvent& WXUNUSED(event))
{
	CFullNameDialog dlgFullName(this, CFullNameDialog::wxID_DIALOG_FULLNAME);
	dlgFullName.SetTitle(m_strTitle);
	dlgFullName.SetFirstName(m_strFirstName);
	dlgFullName.SetMiddleName(m_strMiddleName);
	dlgFullName.SetLastName(m_strLastName);
	dlgFullName.SetSuffix(m_strSuffix);
	if(dlgFullName.ShowModal()==wxID_OK)
	{
		m_pTextCtrlFullname->SetValue(dlgFullName.GetName());
		m_strTitle = dlgFullName.GetTitle();
		m_strFirstName = dlgFullName.GetFirstName();
		m_strMiddleName = dlgFullName.GetMiddleName();
		m_strLastName = dlgFullName.GetLastName();
		m_strSuffix = dlgFullName.GetSuffix();
	}
}

wxString CPrimaryDetailsPanel::GetName(void)
{
	wxString strFullName = wxString::Format(wxT("%s %s %s %s %s"), m_strTitle, m_strFirstName, m_strMiddleName, m_strLastName, m_strSuffix);
	while(strFullName.Replace(wxT("  "), wxT(" "), true));
	strFullName.Trim(false);
	strFullName.Trim(true);
	return strFullName;
}

wxString CPrimaryDetailsPanel::GetFullname(void)
{
	return m_pTextCtrlFullname->GetValue();
}

wxString CPrimaryDetailsPanel::GetNickName(void)
{
	return m_pTextCtrlNickname->GetValue();
}

void CPrimaryDetailsPanel::GetEmail(int nIndex, wxString &strCategory, wxString &strValue)
{
	if(m_pTextCtrlEmail[nIndex]->Validate()==false)
	{
		m_pTextCtrlEmail[nIndex]->SetFocus();
		return;
	}
	strCategory = m_pComboEmail[nIndex]->GetValue();
	strValue = m_pTextCtrlEmail[nIndex]->GetValue();
}

void CPrimaryDetailsPanel::GetTelephone(int nIndex, wxString &strCategory, wxString &strValue)
{
	strCategory = m_pComboTelephone[nIndex]->GetValue();
	strValue = m_pTextCtrlTelephone[nIndex]->GetValue();
}

void CPrimaryDetailsPanel::GetIM(int nIndex, wxString &strCategory, wxString &strValue)
{
	strCategory = m_pComboIM[nIndex]->GetValue();
	strValue = m_pTextCtrlIM[nIndex]->GetValue();
}

wxString CPrimaryDetailsPanel::GetTitle(void)
{
	return m_strTitle;
}

wxString CPrimaryDetailsPanel::GetFirstName(void)
{
	return m_strFirstName;
}

wxString CPrimaryDetailsPanel::GetMiddleName(void)
{
	return m_strMiddleName;
}

wxString CPrimaryDetailsPanel::GetLastName(void)
{
	return m_strLastName;
}

wxString CPrimaryDetailsPanel::GetSuffix(void)
{
	return m_strSuffix;
}

void CPrimaryDetailsPanel::SetTitle(wxString strTitle)
{
	m_strTitle = strTitle;
	if(m_pTextCtrlFullname)
		m_pTextCtrlFullname->SetValue(GetName());
}

void CPrimaryDetailsPanel::SetFirstName(wxString strFirstName)
{
	m_strFirstName = strFirstName;
	if(m_pTextCtrlFullname)
		m_pTextCtrlFullname->SetValue(GetName());
}

void CPrimaryDetailsPanel::SetMiddleName(wxString strMiddleName)
{
	m_strMiddleName = strMiddleName;
	if(m_pTextCtrlFullname)
		m_pTextCtrlFullname->SetValue(GetName());
}

void CPrimaryDetailsPanel::SetLastName(wxString strLastName)
{
	m_strLastName = strLastName;
	if(m_pTextCtrlFullname)
		m_pTextCtrlFullname->SetValue(GetName());
}

void CPrimaryDetailsPanel::SetSuffix(wxString strSuffix)
{
	m_strSuffix = strSuffix;
	if(m_pTextCtrlFullname)
		m_pTextCtrlFullname->SetValue(GetName());
}

void CPrimaryDetailsPanel::SetNickName(wxString strNickName)
{
	m_strNickName = strNickName;
	if(m_pTextCtrlNickname)
		m_pTextCtrlNickname->SetValue(m_strNickName);
}

void CPrimaryDetailsPanel::SetNickNameFocus(void)
{
	m_pTextCtrlNickname->SetFocus();
}

bool CPrimaryDetailsPanel::SetEmail(int nIndex, wxString strCategory, wxString strValue)
{
	m_pComboEmail[nIndex]->SetValue(strCategory);
	m_pTextCtrlEmail[nIndex]->SetValue(strValue);
	return true;
}

bool CPrimaryDetailsPanel::SetTelephone(int nIndex, wxString strCategory, wxString strValue)
{
	m_pComboTelephone[nIndex]->SetValue(strCategory);
	m_pTextCtrlTelephone[nIndex]->SetValue(strValue);
	return true;
}

bool CPrimaryDetailsPanel::SetIM(int nIndex, wxString strCategory, wxString strValue)
{
	m_pComboIM[nIndex]->SetValue(strCategory);
	m_pTextCtrlIM[nIndex]->SetValue(strValue);
	return true;
}
