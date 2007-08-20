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
 *	\file AboutDialog.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/hyperlink.h>

class CAboutDialog : public wxDialog
{
private:
	enum
	{
		wxID_STATIC_BOX_ABOUT_DIALOG = wxID_HIGHEST + 200,
		wxID_HYPERLINK_ABOUT_DIALOG,
		wxID_STATIC_TEXT_COPYRIGHT_1,
		wxID_STATIC_TEXT_COPYRIGHT_2,
		wxID_STATIC_BITMAP_LOGO
	};
	wxHyperlinkCtrl *m_pInfoText;
	wxStaticText *m_pCopyRightText;
	wxButton *m_pOkButton;
	wxStaticBox *m_pStaticBox;
	wxStaticBitmap *m_pStaticBitmapLogo;

public:
	CAboutDialog(wxWindow *parent, wxWindowID id = CAboutDialog::wxID_DIALOG_ABOUT, const wxString &title = wxT("wxQuickRun"), const wxPoint &position = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
	virtual ~CAboutDialog(void);

private:
	void CreateGUIControls(void);
	
public:
	enum
	{
		wxID_DIALOG_ABOUT = wxID_HIGHEST + 500
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
