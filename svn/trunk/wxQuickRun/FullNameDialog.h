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
 *	\file FullNameDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Aug, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/combobox.h>

class CFullNameDialog : public wxDialog
{
private:
	wxStaticText *m_pStaticTextTitle;
	wxStaticText *m_pStaticTextFirst;
	wxStaticText *m_pStaticTextMiddle;
	wxStaticText *m_pStaticTextLast;
	wxStaticText *m_pStaticTextSuffix;
	wxComboBox *m_pComboBoxTitle;
	wxTextCtrl *m_pTextCtrlFirst;
	wxTextCtrl *m_pTextCtrlMiddle;
	wxTextCtrl *m_pTextCtrlLast;
	wxComboBox *m_pComboBoxSuffix;
	wxString m_strTitle;
	wxString m_strFirstName;
	wxString m_strMiddleName;
	wxString m_strLastName;
	wxString m_strSuffix;

public:
	CFullNameDialog(wxWindow* parent, wxWindowID id, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(300, 260), long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("Full name Dialog"));
	virtual ~CFullNameDialog(void);
	wxString GetName(void);
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

private:
	void OnClose(wxCloseEvent &event);
	void OnInitDialog(wxInitDialogEvent &event);
	void OnOK(wxCommandEvent& event);

public:
	enum 
	{
		wxID_DIALOG_FULLNAME = wxID_HIGHEST + 1550,
		wxID_STATIC_TEXT_TITLE,
		wxID_STATIC_TEXT_FIRST,
		wxID_STATIC_TEXT_MIDDLE,
		wxID_STATIC_TEXT_LAST,
		wxID_STATIC_TEXT_SUFFIX,
		wxID_COMBOBOX_TITLE,
		wxID_TEXTCTRL_FIRST,
		wxID_TEXTCTRL_MIDDLE,
		wxID_TEXTCTRL_LAST,
		wxID_COMBOBOX_SUFFIX
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};