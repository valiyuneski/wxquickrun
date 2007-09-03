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
 *	\file TextDropHandler.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 03 Sep, 2007
 **/

#pragma once
#include <wx/dnd.h>

template <class T>
class CTextDropTarget : public wxTextDropTarget
{
private:
	typedef bool (T::*pt2Func)(wxCoord, wxCoord, const wxString&);
	T* m_pParent;
	pt2Func m_pt2CallbackFunc;

public:
	CTextDropTarget(T* pParent, pt2Func pt2CallbackFunc)
		: m_pParent(pParent)
		, m_pt2CallbackFunc(pt2CallbackFunc)
	{
	}

	virtual ~CTextDropTarget(void) {}

	virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data)
	{		
		return (m_pParent->*m_pt2CallbackFunc)(x, y, data); 	
	}
};
