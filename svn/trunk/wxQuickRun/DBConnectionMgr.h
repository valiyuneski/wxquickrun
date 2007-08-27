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
 *	\file DBConnectionMgr.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 25 August, 2007
 **/

#pragma once

// SYSTEM INCLUDES
#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/wxsqlite3.h"
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<wxSQLite3Database> DBConnPtr;
#define DATABASE_FILE wxGetApp().GetDatabaseFileName()

class CDBConnectionMgr
{
public:
	virtual ~CDBConnectionMgr(void);
	static boost::shared_ptr<wxSQLite3Database> GetDBConnection();
	static void CloseDBConnection(wxSQLite3Database *wxSQLiteDB);

private:
	CDBConnectionMgr(void);
	CDBConnectionMgr(const CDBConnectionMgr &);
	CDBConnectionMgr& operator=(const CDBConnectionMgr &);

private:
	static wxSQLite3Database *m_pSQLiteDB;
	static long nRefCountDBInstance;
};
