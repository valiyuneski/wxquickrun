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
 *	\file AboutDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include "AboutDialog.h"
#include "wxQuickRun.h"

#define WXQUICKRUN_VERSION wxT("0.95")

BEGIN_EVENT_TABLE(CAboutDialog, wxDialog)
END_EVENT_TABLE()

CAboutDialog::CAboutDialog(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
, m_pStaticBitmapLogo(NULL)
{
	CreateGUIControls();
	CentreOnScreen();
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
}

CAboutDialog::~CAboutDialog(void)
{
}

void CAboutDialog::CreateGUIControls(void)
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	m_pStaticBox = new wxStaticBox(this, wxID_STATIC_BOX_ABOUT_DIALOG, wxT("About"), wxDefaultPosition, wxDefaultSize);
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer( m_pStaticBox, wxVERTICAL );

	wxBoxSizer* pLogoInfoSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* pInfoSizer = new wxBoxSizer(wxVERTICAL);
	wxString strProductInfo = wxString::Format(wxT("wxQuickRun Ver %s"), WXQUICKRUN_VERSION);
	m_pInfoText = new wxHyperlinkCtrl(this, wxID_HYPERLINK_ABOUT_DIALOG, strProductInfo, wxT("http://www.priyank.co.in/wxQuickRun/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE, wxT("HyperLinkText"));
	m_pInfoText->SetFont(wxFont(14, wxSWISS, wxNORMAL,wxBOLD, FALSE, wxT("Times New Roman")));
	pInfoSizer->Add(m_pInfoText, 0, wxALL | wxALIGN_CENTER | wxEXPAND, 0);

	m_pCopyRightText = new wxStaticText(this, wxID_STATIC_TEXT_COPYRIGHT_1, wxT("Copyright (c) 2006-2007 Priyank Bolia."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
	pInfoSizer->Add(m_pCopyRightText, 0, wxALL | wxALIGN_CENTER | wxEXPAND, 5);

	wxBoxSizer* pLogoSizer = new wxBoxSizer(wxVERTICAL);
	m_pStaticBitmapLogo = new wxStaticBitmap(this, wxID_STATIC_BITMAP_LOGO, wxICON(IDI_ICON_APPICON), wxDefaultPosition, wxDefaultSize, 0, wxT("Logo"));
	pLogoSizer->Add(m_pStaticBitmapLogo, 0, wxTOP | wxALIGN_CENTER | wxEXPAND, 5);
	pLogoSizer->AddStretchSpacer(1);
	pLogoInfoSizer->Add(pLogoSizer, 0, wxALL | wxALIGN_CENTER | wxEXPAND, 5);
	pLogoInfoSizer->Add(pInfoSizer, 1, wxALL | wxALIGN_CENTER | wxEXPAND, 5);
	pStaticBoxSizer->Add(pLogoInfoSizer, 1, wxALL | wxALIGN_CENTER | wxEXPAND, 0);

	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pOkButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pOkButton, 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);
	pStaticBoxSizer->Add(pButtonSizer, 0, wxALL | wxALIGN_CENTER, 5);

	pMainSizer->Add(pStaticBoxSizer, 1, wxALL | wxALIGN_CENTER | wxEXPAND, 10);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	Fit();
}
