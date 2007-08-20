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
 *	\file ClipBoardManager.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 25 Sep, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/clipbrd.h>

 /// Singleton class to manage the ClipBoard
class CClipBoardManager
{
private:
	CClipBoardManager(void);

public:
	virtual ~CClipBoardManager(void);

	static CClipBoardManager* GetInstance(void);
	void SetStringToVirtualClipBoard(unsigned int nIndex, wxString strText);
	wxString GetStringFromVirtualClipBoard(unsigned int nIndex);
	unsigned int GetVirtualClipBoardIndex(void);
	void SetVirtualClipBoardIndex(unsigned int);
	static wxString ReadFromGlobalClipboard(void);
	static void WriteToGlobalClipboard(wxString);
	void LoadClipboardStringsFromDB(void);

private:
	static CClipBoardManager *m_pClipBoardManager;
	static const unsigned int MAX_CLIPBOARDS_COUNT = 10;
	static const unsigned int MAX_CLIPBOARD_OBJECTS = 10;
	unsigned int m_nClipBoardIndex;
	wxString m_clipBoardStr[MAX_CLIPBOARDS_COUNT][MAX_CLIPBOARD_OBJECTS];
};
