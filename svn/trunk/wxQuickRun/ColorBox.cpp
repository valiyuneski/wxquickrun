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
 *	\file ColorBox.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 3 Jul, 2006
 **/

#include "ColorBox.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(wxColorBox, wxStaticText)
	EVT_ERASE_BACKGROUND(wxColorBox::OnEraseBackground)
	EVT_PAINT(wxColorBox::OnPaint)
END_EVENT_TABLE()


wxColorBox::wxColorBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxStaticText(parent, id, wxEmptyString, pos, size, style, name)
{
	m_backColor = wxColor(255, 255, 255);
	SetMaxSize(wxSize(9999,20));
	Refresh(false);
}

wxColorBox::~wxColorBox(void)
{
}

void wxColorBox::SetBoxColor(wxColor color)
{
	m_backColor = color;
	Refresh(false);
}

wxColor wxColorBox::GetBoxColor(void)
{
	return m_backColor;
}

void wxColorBox::OnEraseBackground(wxEraseEvent &event)
{
	event.Skip(false);
}

void wxColorBox::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	wxBrush brush(m_backColor, wxSOLID);
	dc.SetBrush(brush);
	dc.DrawRectangle(wxPoint(0, 0), GetSize());
	event.Skip(false);
}