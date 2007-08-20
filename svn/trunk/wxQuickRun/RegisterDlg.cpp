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
 *	\file RegisterDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#include "RegisterDlg.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CRegisterDlg, wxDialog)
	EVT_CLOSE(CRegisterDlg::OnClose)
	EVT_BUTTON(wxID_OK, CRegisterDlg::OnOK)
	EVT_BUTTON(wxID_BUTTON_BUY, CRegisterDlg::OnBuyNow)
	EVT_INIT_DIALOG(CRegisterDlg::OnInitDialog)
END_EVENT_TABLE()

CRegisterDlg::CRegisterDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pTextCtrlUserName(NULL)
, m_pTextCtrlSerialKey(NULL)
, m_pButtonRegister(NULL)
, m_pButtonBuy(NULL)
, m_pButtonCancel(NULL)
{
}

CRegisterDlg::~CRegisterDlg(void)
{
}

void CRegisterDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CRegisterDlg::OnInitDialog(wxInitDialogEvent &event)
{
	///Sizer for adding the controls created by users
	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("Registration:"));
	wxBoxSizer *pRegisterInfoSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText *pStaticTextUserName = new wxStaticText(this, wxID_ANY, wxT("&User name:"));
	m_pTextCtrlUserName = new wxTextCtrl(this, wxID_TEXTCTRL_USER_NAME, wxEmptyString);
	wxStaticText *pStaticTextSerialKey = new wxStaticText(this, wxID_ANY, wxT("&Serial key:"));
	m_pTextCtrlSerialKey = new wxTextCtrl(this, wxID_TEXTCTRL_SERIAL_KEY, wxEmptyString);
	pRegisterInfoSizer->Add(pStaticTextUserName, 1, wxALL|wxEXPAND, 5);
	pRegisterInfoSizer->Add(m_pTextCtrlUserName, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);
	pRegisterInfoSizer->Add(pStaticTextSerialKey, 1, wxALL|wxEXPAND, 5);
	pRegisterInfoSizer->Add(m_pTextCtrlSerialKey, 1, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);

	m_pButtonRegister = new wxButton(this, wxID_OK, wxT("&Register"));
	m_pButtonBuy = new wxButton(this, wxID_BUTTON_BUY, wxT("&Buy Now"));
	m_pButtonCancel = new wxButton(this, wxID_CANCEL, wxT("&Cancel"));
	pButtonSizer->Add(m_pButtonRegister, 1, wxALL|wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonBuy, 1, wxALL|wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonCancel, 1, wxALL|wxEXPAND, 5);

	pStaticBoxSizer->Add(pRegisterInfoSizer, 1, wxALL|wxEXPAND, 5);
	pStaticBoxSizer->Add(pButtonSizer, 0, wxALL|wxEXPAND, 5);
	pMainSizer->Add(pStaticBoxSizer, 1, wxALL|wxEXPAND, 5);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	SetIcon(wxICON(IDI_ICON_APPICON));
}

void CRegisterDlg::OnOK(wxCommandEvent& event)
{
	wxString strUserName = m_pTextCtrlUserName->GetValue();
	wxString strSerialKey = m_pTextCtrlSerialKey->GetValue();
	event.Skip(true);
}

void CRegisterDlg::OnBuyNow(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser(wxT("http://priyank.co.in/wxQuickRun/buy.php"));
	event.Skip(true);
}
