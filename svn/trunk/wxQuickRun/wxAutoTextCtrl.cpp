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
 *	\file wxAutoTextCtrl.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include "wxAutoTextCtrl.h"

#if wxUSE_TEXTCTRL

IMPLEMENT_DYNAMIC_CLASS(wxAutoTextCtrl, wxTextCtrl)

BEGIN_EVENT_TABLE(wxAutoTextCtrl, wxTextCtrl)
	EVT_TEXT(wxID_ANY, wxAutoTextCtrl::OnTextChange)
	EVT_CHAR(wxAutoTextCtrl::OnChar)
	EVT_KEY_DOWN(wxAutoTextCtrl::OnKeyDown)
	EVT_KILL_FOCUS(wxAutoTextCtrl::OnKillFocus)
END_EVENT_TABLE()

wxAutoTextCtrl::wxAutoTextCtrl(void)
: m_bBeep(true)
, m_bShowMsg(false)
, m_nKeyCode(0)
, m_nArrayIndex(-1)
{
}

wxAutoTextCtrl::wxAutoTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxTextCtrl(parent, id, value, pos, size, style, validator, name)
, m_bBeep(true)
, m_bShowMsg(false)
, m_nKeyCode(0)
, m_nArrayIndex(-1)
{
}

wxAutoTextCtrl::wxAutoTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxArrayString& validValues, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxTextCtrl(parent, id, value, pos, size, style, validator, name)
, m_StrValues(validValues)
, m_bBeep(true)
, m_bShowMsg(false)
, m_nKeyCode(0)
, m_nArrayIndex(-1)
{
}

wxAutoTextCtrl::~wxAutoTextCtrl(void)
{
}

void wxAutoTextCtrl::OnTextChange(wxCommandEvent &event)
{
	if (m_nKeyCode != WXK_BACK && m_nKeyCode != WXK_DELETE) 
	{
		wxString strValue = GetValue();
		wxString strArray;
		for( size_t i=0; i<m_StrValues.GetCount(); i++ )
		{
			strArray = m_StrValues[i];
			if(strArray.Lower().Find(strValue.Lower()) == 0)
			{
				if(strArray.Length() > strValue.Length())
				{
					m_nArrayIndex = (int)i;
					SetValue(strArray);
					SetSelection((long)strValue.Length(), -1);
				}
				event.Skip(true);
				return;
			}
		}
		if(m_bBeep)
			::wxBell();
	}
	event.Skip(true);
}

void wxAutoTextCtrl::OnChar(wxKeyEvent &event)
{
	m_nKeyCode = event.GetKeyCode();
	event.Skip(true);
}

void wxAutoTextCtrl::OnKeyDown(wxKeyEvent &event)
{
	m_nKeyCode = 0;
	int nKeyCode = event.GetKeyCode();
	if( nKeyCode == WXK_UP || nKeyCode == WXK_DOWN )
	{
		wxString strValue = GetValue();
		wxString strArray;
		long start=-1, end=-1;
		GetSelection(&start, &end);
		if(start >=0 )
		{
			strValue = strValue.Left(start);
		}
		if (nKeyCode == WXK_DOWN) 
		{
			for( size_t i=(m_nArrayIndex+1); i < m_StrValues.GetCount() && m_nArrayIndex >= 0; i++ )
			{
				strArray = m_StrValues[i];
				if(strArray.Find(strValue) == 0)
				{
					m_nArrayIndex = (int)i;
					SetValue(strArray);
					SetSelection((long)strValue.Length(), -1);
					return;
				}
			}
		}
		else
		{
			for( size_t i=(m_nArrayIndex-1); i >= 0 && m_nArrayIndex > 0 && i < m_StrValues.GetCount(); i-- )
			{
				strArray = m_StrValues[i];
				if(strArray.Find(strValue) == 0)
				{
					m_nArrayIndex = (int)i;
					SetValue(strArray);
					SetSelection((long)strValue.Length(), -1);
					return;
				}
			}
		}
		return;
	}
	m_nArrayIndex = -1;
	event.Skip(true);
}

void wxAutoTextCtrl::OnKillFocus(wxFocusEvent &event)
{
	if (m_bShowMsg && m_StrValues.GetCount())
	{
		wxString strValue = GetValue();
		for( size_t i=0; i<m_StrValues.GetCount(); i++ )
		{
			if(strValue == m_StrValues[i])
			{
				event.Skip(true);
				return;
			}
		}
		wxMessageBox(m_strMessage, wxT("Invalid Input"), wxOK | wxCENTRE | wxICON_INFORMATION, this);
		this->SetFocus();
		return;
	}
	event.Skip(true);
}

void wxAutoTextCtrl::SetBeepOnInvalidValue(bool bBeep)
{
	m_bBeep = bBeep;
}

bool wxAutoTextCtrl::GetBeepOnInvalidValue(void)
{
	return m_bBeep;
}

void wxAutoTextCtrl::SetInvalidInputMessage(wxString strMsg, bool bShow)
{
	m_strMessage = strMsg;
	m_bShowMsg = bShow;
}

wxString wxAutoTextCtrl::GetInvalidInputMessage(void)
{
	return m_strMessage;
}

bool wxAutoTextCtrl::IsShowInvalidInputMessage(void)
{
	return m_bShowMsg;
}

unsigned int wxAutoTextCtrl::AddValidInputValues(wxString strValue)
{
	return (unsigned int)m_StrValues.Add(strValue);
}

#endif
	// wxUSE_TEXTCTRL
