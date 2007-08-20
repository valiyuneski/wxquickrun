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
 *	\file GradientPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#pragma once
#include "stdwx.h"

#ifdef __WXMSW__
	typedef UINT (CALLBACK * LPFNDLLFUNC)(HDC, CONST PTRIVERTEX, DWORD, CONST PVOID, DWORD, DWORD);
#endif

class CGradientPanel : public wxPanel
{
private:
	wxSize m_sizeMoveDiff;
	bool m_bMoving;
	wxString m_strTitle;
	wxColor m_clrLeft;
	wxColor m_clrRight;
	BOOL m_bCanDoGradientFill;
#ifdef __WXMSW__
	HINSTANCE m_hinst_msimg32;
	LPFNDLLFUNC m_dllfunc_GradientFill;	
#endif

public:
	CGradientPanel(wxWindow* parent, wxWindowID id = CGradientPanel::wxID_PANEL_GRADIENT, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxNO_BORDER, const wxString& name = wxT("Gradient panel"));
	virtual ~CGradientPanel(void);

	wxString GetTitleString(void) { return m_strTitle; }
	void SetTitleString(wxString strTitle) { m_strTitle = strTitle; }

private:
	void OnEraseBackground(wxEraseEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnLeftUp(wxMouseEvent &event);
	void OnMouseMove(wxMouseEvent &event);
	void OnSize(wxSizeEvent &event);

public:
	enum 
	{
		wxID_PANEL_GRADIENT = wxID_HIGHEST + 1750
	};

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
