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
 *	\file ToggleBitmapButton.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#pragma once
#include "stdwx.h" 
#include <wx/image.h>
#include <wx/bmpbuttn.h>

class CToggleBitmapButton : public wxBitmapButton
{
private:
	wxBitmap m_bitmap;
	wxBitmap m_overBitmap;
	wxBitmap m_selBitmap;
	wxImage m_maskBitmap;

public:
	CToggleBitmapButton( wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxBitmap& overbitmap, const wxBitmap& selbitmap, const wxImage& maskbitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("ToggleBitmapButton"));
	virtual ~CToggleBitmapButton(void);

private:
	void OnPaint(wxPaintEvent & event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnLeftDown(wxMouseEvent& evt);
	void OnLeftUp(wxMouseEvent& evt);
	void OnMouseMove(wxMouseEvent& evt);
	void OnMouseEnter(wxMouseEvent& evt);
	void OnMouseLeave(wxMouseEvent& evt);

private:
	DECLARE_EVENT_TABLE()
};
