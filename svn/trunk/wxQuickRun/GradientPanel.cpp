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
 *	\file GradientPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 30 Oct, 2006
 **/

#include "GradientPanel.h"
#include <wx/dcbuffer.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CGradientPanel, wxPanel)
	EVT_ERASE_BACKGROUND(CGradientPanel::OnEraseBackground)
	EVT_PAINT(CGradientPanel::OnPaint)
	EVT_LEFT_DOWN(CGradientPanel::OnLeftDown)
	EVT_LEFT_UP(CGradientPanel::OnLeftUp)
	EVT_MOTION(CGradientPanel::OnMouseMove)
	EVT_SIZE(CGradientPanel::OnSize)
END_EVENT_TABLE()

CGradientPanel::CGradientPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos , const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
{
	wxColor m_clrLeft = wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION);
	wxColor m_clrRight = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
	m_bCanDoGradientFill = FALSE;

#ifdef __WXMSW__
	m_hinst_msimg32 = LoadLibrary(wxT("msimg32.dll"));
	if (m_hinst_msimg32)
	{
		m_bCanDoGradientFill = TRUE;		
		m_dllfunc_GradientFill = ((LPFNDLLFUNC)::GetProcAddress(m_hinst_msimg32, "GradientFill"));
	}
#endif
}

CGradientPanel::~CGradientPanel(void)
{
#ifdef __WXMSW__
	FreeLibrary(m_hinst_msimg32);
#endif
}

void CGradientPanel::OnEraseBackground(wxEraseEvent &event)
{
}

void CGradientPanel::OnPaint(wxPaintEvent &event)
{
	wxRect rectStep;									// rectangle for color's band
	wxColor clrColor;									// color for the bands
	float fStep = ((float)GetSize().GetWidth())/255.0f;	// width of color's band
	if (m_bCanDoGradientFill) //msimg32.dll library is loaded
	{
#ifdef __WXMSW__
		PAINTSTRUCT ps;
		HDC hdc;
		RECT rect;
		::GetClientRect((HWND)this->m_hWnd, &rect);
		hdc = ::BeginPaint((HWND)this->m_hWnd, &ps);
		TRIVERTEX rcVertex[2];
		rcVertex[0].x = rect.left;
		rcVertex[0].y = rect.top;
		rcVertex[0].Red = m_clrLeft.Red()<<8;	// color values from 0x0000 to 0xff00 !!!!
		rcVertex[0].Green = m_clrLeft.Green()<<8;
		rcVertex[0].Blue = m_clrLeft.Blue()<<8;
		rcVertex[0].Alpha = 0x0000;
		rcVertex[1].x = rect.right; 
		rcVertex[1].y = rect.bottom;
		rcVertex[1].Red = m_clrRight.Red()<<8;
		rcVertex[1].Green = m_clrRight.Green()<<8;
		rcVertex[1].Blue = m_clrRight.Blue()<<8;
		rcVertex[1].Alpha = 0;

		GRADIENT_RECT gRect;
		gRect.UpperLeft = 0;
		gRect.LowerRight = 1;

		// Fill the area 
		m_dllfunc_GradientFill(hdc, rcVertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
		::EndPaint((HWND)this->m_hWnd, &ps);
#endif
	}
	else
	{
		// msimg32.dll is not available. Let's use our own code to display gradient background.
		// This code is very simple and produces worse gradient that function from the library - but works!
		wxBufferedPaintDC dc(this);

		for (int nOnBand = 0; nOnBand < 255; nOnBand++) 
		{
			// Set a current band
			rectStep = 	wxRect((int)(nOnBand * fStep), 0,	fStep, GetSize().GetHeight());	

			// Set a current color
			clrColor = wxColor((m_clrRight.Red() - m_clrLeft.Red()) * ((float)nOnBand) / 255.0f + m_clrLeft.Red(),
				(m_clrRight.Green() - m_clrLeft.Green()) * ((float)nOnBand) / 255.0f + m_clrLeft.Green(),
				(m_clrRight.Blue() - m_clrLeft.Blue()) * ((float)nOnBand) / 255.0f + m_clrLeft.Blue());

			dc.SetPen(wxPen(clrColor));
			dc.SetBrush(wxBrush(clrColor));

			// Fill a current band
			dc.DrawRectangle(rectStep);
		}
	}
}

void CGradientPanel::OnLeftDown(wxMouseEvent &event)
{
	m_bMoving = true;
	wxPoint point = event.GetPosition();
	m_sizeMoveDiff = wxSize(point.x, point.y);
	CaptureMouse();
}

void CGradientPanel::OnLeftUp(wxMouseEvent &event)
{
	m_bMoving = false;
	ReleaseMouse();
}

void CGradientPanel::OnMouseMove(wxMouseEvent &event)
{
	if(m_bMoving && HasCapture())
	{
		wxPoint point = event.GetPosition();
		wxPoint position = GetParent()->GetPosition();
		GetParent()->SetSize(position.x+point.x-m_sizeMoveDiff.GetWidth(), position.y+point.y-m_sizeMoveDiff.GetHeight(), -1, -1, wxSIZE_USE_EXISTING);
	}
}

void CGradientPanel::OnSize(wxSizeEvent &event)
{
	event.Skip(true);
	Refresh(true);
}