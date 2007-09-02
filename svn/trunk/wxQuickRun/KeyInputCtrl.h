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
 *	\file KeyInputCtrl.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 19 August, 2007
 **/

#pragma once
#include "stdwx.h"

class CKeyInputCtrl : public wxTextCtrl
{
	DECLARE_DYNAMIC_CLASS(CKeyInputCtrl)

public:
	CKeyInputCtrl();
	CKeyInputCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxT(""), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("text control"));
	virtual ~CKeyInputCtrl(void);
	virtual void OnKeysModifierChange(int);

private:
	int GetKeyCode(wxString ch);
	wxString GetKeyCodeAsString(int nKeyCode);
	void OnKeyDown(wxKeyEvent &event);
	void OnChar(wxKeyEvent &event);

public:
	int GetKeyCode();
	void SetKeyCode(int nKeyCode);

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
