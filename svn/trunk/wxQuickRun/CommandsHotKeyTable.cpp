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
 *	\file QuickRunFrame.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 05 Sep, 2007
 **/
#include "CommandsHotKeyTable.h"
#include "QuickRunFrame.h"

CCommandsHotKeyTable::CCommandsHotKeyTable(void)
{
	m_DBConnection = CDBConnectionMgr::GetDBConnection();
}

CCommandsHotKeyTable::~CCommandsHotKeyTable(void)
{
}

bool CCommandsHotKeyTable::AddRecord(int nCommandID, int nKeyCode, int nModifier)
{
	if(nKeyCode == 0 && nModifier == 0)
		return DeleteRecord(nCommandID);
	if(CountRecords() > CQuickRunFrame::MAX_COMMAND_HOTKEYS)
	{
		return false;
	}
	else
	{
		if(CheckDBTableExists())
			DeleteRecord(nCommandID);
		else
			CreateDBTable();
		wxString sqlCmd = wxString::Format(wxT("INSERT INTO CommandsHotkey(commandID, keycode, modifier) VALUES(%d, %d, %d);"), nCommandID, nKeyCode, nModifier);
		m_DBConnection->ExecuteUpdate(sqlCmd);
		return true;
	}
	return false;
}

bool CCommandsHotKeyTable::DeleteRecord(int nCommandID)
{
	if(CheckDBTableExists())
	{
		wxString sqlCmd = wxString::Format(wxT("DELETE FROM CommandsHotkey WHERE commandID = %d;"), nCommandID);
		m_DBConnection->ExecuteUpdate(sqlCmd);
		return true;
	}
	return false;
}

int CCommandsHotKeyTable::CountRecords()
{
	if(CheckDBTableExists())
	{
		wxString sqlCmd = wxString::Format(wxT("select count(*) from CommandsHotkey;"));
		return m_DBConnection->ExecuteScalar(sqlCmd);
	}
	return 0;
}

HotKey CCommandsHotKeyTable::GetRecord(int nCommandID)
{
	int nKeyCode = 0, nModifier = 0;
	if(CheckDBTableExists())
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT keycode, modifier FROM CommandsHotkey WHERE commandID = %d;"), nCommandID);
		wxSQLite3ResultSet result = m_DBConnection->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			nKeyCode = result.GetInt(0);
			nModifier = result.GetInt(1);
		}
		result.Finalize();
	}
	return HotKey(nKeyCode, nModifier);
}

int CCommandsHotKeyTable::GetCommand(int nKeyCode, int nModifier)
{
	if(CheckDBTableExists())
	{
		wxString sqlCmd = wxString::Format(wxT("select commandID from CommandsHotkey WHERE keycode = %d AND modifier = %d;"), nKeyCode, nModifier);
		return m_DBConnection->ExecuteScalar(sqlCmd);
	}
	return 0;
}

vector<HotKey> CCommandsHotKeyTable::GetAllHotkeys()
{
	vector<HotKey> vecHotkey;
	if(CheckDBTableExists())
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT keycode, modifier FROM CommandsHotkey"));
		wxSQLite3ResultSet result = m_DBConnection->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			HotKey hotkey(result.GetInt(0), result.GetInt(1));
			vecHotkey.push_back(hotkey);
		}
		result.Finalize();
	}
	return vecHotkey;
}

bool CCommandsHotKeyTable::CheckDBTableExists()
{
	if(m_DBConnection->TableExists(wxT("CommandsHotkey")))
	{
		return true;
	}
	return false;
}

void CCommandsHotKeyTable::CreateDBTable()
{
	if(!m_DBConnection->TableExists(wxT("CommandsHotkey")))
	{
		m_DBConnection->ExecuteUpdate(wxT("create table CommandsHotkey(ID INTEGER PRIMARY KEY AUTOINCREMENT, commandID INTEGER, keycode NUMERIC(3,0), modifier NUMERIC(3,0));"));
	}
}
