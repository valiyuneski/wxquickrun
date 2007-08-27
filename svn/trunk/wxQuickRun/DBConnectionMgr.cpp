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
 *	\file DBConnectionMgr.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 25 August, 2007
 **/

#include "DBConnectionMgr.h"
#include "wxQuickRun.h"

wxSQLite3Database* CDBConnectionMgr::m_pSQLiteDB = NULL;
long CDBConnectionMgr::nRefCountDBInstance = 0;

CDBConnectionMgr::CDBConnectionMgr(void)
{
}

CDBConnectionMgr::~CDBConnectionMgr(void)
{
}

boost::shared_ptr<wxSQLite3Database> CDBConnectionMgr::GetDBConnection()
{
	/* This is not a multi threaded application, so their is no need to use 
	   mutex or any locking mechanism, for the purpose of synchronization. */
	if(nRefCountDBInstance == 0 && m_pSQLiteDB == NULL)
	{
		m_pSQLiteDB = new wxSQLite3Database();
	}
#ifdef __WXMSW__
	::InterlockedIncrement(&nRefCountDBInstance);
#else
	++nRefCountDBInstance;
#endif
	boost::shared_ptr<wxSQLite3Database> spDBConn(m_pSQLiteDB, CDBConnectionMgr::CloseDBConnection);
	if(spDBConn->IsOpen() == false)
		spDBConn->Open(DATABASE_FILE);
	return spDBConn;
}

void CDBConnectionMgr::CloseDBConnection(wxSQLite3Database *wxSQLiteDB)
{
	try
	{
#ifdef __WXMSW__
		::InterlockedDecrement(&nRefCountDBInstance);
#else
		--nRefCountDBInstance;
#endif
		if(nRefCountDBInstance == 0 && m_pSQLiteDB != NULL)
		{
			m_pSQLiteDB = dynamic_cast<wxSQLite3Database *>(wxSQLiteDB);
			m_pSQLiteDB->Close();
			delete m_pSQLiteDB;
			m_pSQLiteDB = NULL;
		}
	}
	catch (...)
	{	
	}
}
