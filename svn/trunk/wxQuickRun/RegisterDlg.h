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
 *	\file RegisterDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#pragma once
#include "stdwx.h"

class CRegisterDlg : public wxDialog
{
private:
	wxTextCtrl *m_pTextCtrlUserName;
	wxTextCtrl *m_pTextCtrlSerialKey;
	wxButton *m_pButtonRegister;
	wxButton *m_pButtonBuy;
	wxButton *m_pButtonCancel;

public:
	CRegisterDlg(wxWindow* parent, wxWindowID id = CRegisterDlg::wxID_DIALOG_REGISTER, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 180), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Register Dialog"));
	virtual ~CRegisterDlg(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent& event);
	void OnBuyNow(wxCommandEvent& event);

public:
	enum 
	{
		wxID_DIALOG_REGISTER = wxID_HIGHEST + 1650,
		wxID_TEXTCTRL_USER_NAME,
		wxID_TEXTCTRL_SERIAL_KEY,
		wxID_BUTTON_BUY
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
