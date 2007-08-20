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
 *	\file PrimaryDetailsPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Aug, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/statline.h>

class CPrimaryDetailsPanel : public wxPanel
{
private:
	int m_nEditContact;
	wxStaticText *m_pStaticTextTelephone;
	wxStaticText *m_pStaticTextEmail;
	wxStaticText *m_pStaticTextInstantMessaging;
	wxStaticText *m_pStaticTextNickname;
	wxButton *m_pButtonFullname;
	wxTextCtrl *m_pTextCtrlFullname;
	wxTextCtrl *m_pTextCtrlNickname;
	wxComboBox *m_pComboEmail[2];
	wxTextCtrl *m_pTextCtrlEmail[2];
	wxComboBox *m_pComboTelephone[2];
	wxTextCtrl *m_pTextCtrlTelephone[2];
	wxComboBox *m_pComboIM[2];
	wxTextCtrl *m_pTextCtrlIM[2];
	wxStaticLine *m_pStaticLine[3];
	wxString m_strTitle;
	wxString m_strFirstName;
	wxString m_strMiddleName;
	wxString m_strLastName;
	wxString m_strSuffix;
	wxString m_strNickName;
	wxString m_strEmail[2];

public:
	CPrimaryDetailsPanel(wxWindow* parent, wxWindowID id, int nEditContact = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Primary Details Panel"));
	virtual ~CPrimaryDetailsPanel(void);
	wxString GetFullname(void);
	wxString GetNickName(void);
	void GetEmail(int nIndex, wxString &strCategory, wxString &strValue);
	bool SetEmail(int nIndex, wxString strCategory, wxString strValue);
	void GetTelephone(int nIndex, wxString &strCategory, wxString &strValue);
	bool SetTelephone(int nIndex, wxString strCategory, wxString strValue);
	void GetIM(int nIndex, wxString &strCategory, wxString &strValue);
	bool SetIM(int nIndex, wxString strCategory, wxString strValue);
	wxString GetTitle(void);
	wxString GetFirstName(void);
	wxString GetMiddleName(void);
	wxString GetLastName(void);
	wxString GetSuffix(void);
	void SetTitle(wxString strTitle);
	void SetFirstName(wxString strFirstName);
	void SetMiddleName(wxString strMiddleName);
	void SetLastName(wxString strLastName);
	void SetSuffix(wxString strSuffix);
	void SetNickName(wxString strNickName);
	void SetNickNameFocus(void);

private:
	void OnClose(wxCloseEvent &event);
	void CreateGUIControls(void);
	void OnFullNameButton(wxCommandEvent& event);
	wxString GetName(void);

public:
	enum
	{
		wxID_PANEL_PRIMARY_DETAILS = wxID_HIGHEST + 1500,
		wxID_STATIC_TEXT_TELEPHONE,
		wxID_STATIC_TEXT_EMAIL,
		wxID_STATIC_TEXT_IM,
		wxID_STATIC_TEXT_NICKNAME,
		wxID_BUTTON_FULLNAME,
		wxID_TEXTCTRL_FULLNAME,
		wxID_TEXTCTRL_NICKNAME,
		wxID_COMBOBOX_EMAIL_1,
		wxID_COMBOBOX_EMAIL_2,
		wxID_COMBOBOX_TELEPHONE_1,
		wxID_COMBOBOX_TELEPHONE_2,
		wxID_COMBOBOX_IM_1,
		wxID_COMBOBOX_IM_2,
		wxID_TEXTCTRL_EMAIL_1,
		wxID_TEXTCTRL_EMAIL_2,
		wxID_TEXTCTRL_TELEPHONE_1,
		wxID_TEXTCTRL_TELEPHONE_2,
		wxID_TEXTCTRL_IM_1,
		wxID_TEXTCTRL_IM_2
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
