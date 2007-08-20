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

#include "ToggleBitmapButton.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CToggleBitmapButton, wxBitmapButton)
	EVT_LEFT_DOWN(CToggleBitmapButton::OnLeftDown)
	EVT_LEFT_UP(CToggleBitmapButton::OnLeftUp)
	EVT_MOTION(CToggleBitmapButton::OnMouseMove)
	EVT_ERASE_BACKGROUND(CToggleBitmapButton::OnEraseBackground)
	EVT_PAINT(CToggleBitmapButton::OnPaint)
	EVT_ENTER_WINDOW(CToggleBitmapButton::OnMouseEnter)
	EVT_LEAVE_WINDOW(CToggleBitmapButton::OnMouseLeave)
END_EVENT_TABLE()

CToggleBitmapButton::CToggleBitmapButton( wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxBitmap& overbitmap, const wxBitmap& selbitmap, const wxImage& maskbitmap, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxBitmapButton(parent, id, bitmap, pos, size, style, validator, name)
, m_bitmap(bitmap)
, m_overBitmap(overbitmap)
, m_selBitmap(selbitmap)
, m_maskBitmap(maskbitmap)
{
	SetSize(m_bitmap.GetWidth(), m_bitmap.GetHeight());
	SetMinSize(wxSize(m_bitmap.GetWidth(), m_bitmap.GetHeight()));
	SetMaxSize(wxSize(m_bitmap.GetWidth(), m_bitmap.GetHeight()));
	SetBitmapSelected(m_selBitmap);
}

CToggleBitmapButton::~CToggleBitmapButton(void)
{
}

void CToggleBitmapButton::OnPaint(wxPaintEvent & event)
{
	event.Skip();
}

void CToggleBitmapButton::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

void CToggleBitmapButton::OnLeftDown(wxMouseEvent& evt)
{
	wxPoint pt = evt.GetPosition();
	if(m_maskBitmap.GetRed(pt.x, pt.y))
		evt.Skip();
}

void CToggleBitmapButton::OnLeftUp(wxMouseEvent& evt)
{
	evt.Skip();
}

void CToggleBitmapButton::OnMouseMove(wxMouseEvent& evt)
{
	evt.Skip();
}

void CToggleBitmapButton::OnMouseEnter(wxMouseEvent& evt)
{
	SetBitmapLabel(m_overBitmap);
	evt.Skip();
}

void CToggleBitmapButton::OnMouseLeave(wxMouseEvent& evt)
{
	SetBitmapLabel(m_bitmap);
	evt.Skip();
}
