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
 *	\file StickyManager.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 31 Oct, 2006
 **/

#pragma once
#include "stdwx.h"
#include "StickyNoteFrame.h"
#include <vector>

class CStickyManager :	public wxObject
{
private:
	static CStickyManager *m_pStickyManager;

private:
	// Singleton class : Private Constructor.
	CStickyManager(void);

public:
	virtual ~CStickyManager(void);

	static CStickyManager* GetStickyManager(void);
	static void DeleteStickyManager(void);

	CStickyNoteFrame* CreateNote(void);
};
