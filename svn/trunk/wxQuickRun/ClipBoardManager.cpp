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
 *	\file ClipBoardManager.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 25 Sep, 2006
 **/

#include "ClipBoardManager.h"
#include "wxQuickRun.h"

CClipBoardManager *CClipBoardManager::m_pClipBoardManager = NULL;

CClipBoardManager::CClipBoardManager(void)
: m_nClipBoardIndex(0)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("settings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(255), value VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'ClipboardIndex';"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
			SetVirtualClipBoardIndex(wxAtoi(result.GetString(0))-1);
		result.Finalize();
	}
}

CClipBoardManager::~CClipBoardManager(void)
{
	m_pClipBoardManager = NULL;
}

CClipBoardManager* CClipBoardManager::GetInstance(void)
{
	if(m_pClipBoardManager == NULL)
	{
		m_pClipBoardManager = new CClipBoardManager();
		m_pClipBoardManager->LoadClipboardStringsFromDB();
	}

	return m_pClipBoardManager;
}

void CClipBoardManager::SetStringToVirtualClipBoard(unsigned int nIndex, wxString strText)
{
	if(nIndex < MAX_CLIPBOARD_OBJECTS)
	{
		m_clipBoardStr[m_nClipBoardIndex][nIndex] = strText;
		DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
		if(!dbConn->TableExists(wxT("clipboard")))
		{
			dbConn->ExecuteUpdate(wxT("CREATE TABLE clipboard(ID INTEGER PRIMARY KEY AUTOINCREMENT, string TEXT);"));
		}
		wxString sqlCmd = wxString::Format(wxT("DELETE FROM clipboard WHERE ID = %d;"), (m_nClipBoardIndex*10)+nIndex);
		dbConn->ExecuteUpdate(sqlCmd);
		sqlCmd = wxString::Format(wxT("Insert INTO clipboard('ID', 'string') VALUES(%d, ?)"), (m_nClipBoardIndex*10)+nIndex);
		wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
		// Bind the variables to the SQL statement
		stmt.Bind(1, strText);
		// Execute the SQL Query
		stmt.ExecuteUpdate();
	}
	else
	{
		wxMessageBox(wxT("The requested clipboard data cannot be set."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR);
	}
}

wxString CClipBoardManager::GetStringFromVirtualClipBoard(unsigned int nIndex)
{
	if(nIndex < MAX_CLIPBOARD_OBJECTS)
		return m_clipBoardStr[m_nClipBoardIndex][nIndex];
	else
		wxMessageBox(wxT("The requested clipboard data is not present."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR);

	return wxEmptyString;
}

unsigned int CClipBoardManager::GetVirtualClipBoardIndex(void)
{
	return m_nClipBoardIndex;
}

void CClipBoardManager::SetVirtualClipBoardIndex(unsigned int nIndex)
{
	if(nIndex < MAX_CLIPBOARDS_COUNT)
		m_nClipBoardIndex = nIndex;
	else
		wxMessageBox(wxT("The requested clipboard is not present."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR);
}

wxString CClipBoardManager::ReadFromGlobalClipboard(void)
{
	// Read some text
	wxString strClipboard;
	if (wxTheClipboard->Open())
	{
		if (wxTheClipboard->IsSupported( wxDF_TEXT ))
		{
			wxTextDataObject data;
			wxTheClipboard->GetData( data );
			strClipboard = data.GetText();
		}  
		wxTheClipboard->Close();
	}
	return strClipboard;
}

void CClipBoardManager::WriteToGlobalClipboard(wxString strClipboard)
{
	// Write some text to the clipboard
	if (wxTheClipboard->Open())
	{
		// This data objects are held by the clipboard, 
		// so do not delete them in the app.
		wxTheClipboard->SetData( new wxTextDataObject(strClipboard) );
		wxTheClipboard->Close();
	}
}

void CClipBoardManager::LoadClipboardStringsFromDB(void)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("clipboard")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE clipboard(ID INTEGER PRIMARY KEY AUTOINCREMENT, string TEXT);"));
	}
	else
	{
		for(int i=0; i<MAX_CLIPBOARDS_COUNT; i++)
		{
			for (int j=0; j<MAX_CLIPBOARD_OBJECTS; j++)
			{
				wxString sqlCmd = wxString::Format(wxT("SELECT string from clipboard WHERE ID = %d;"), (i*10)+j);
				wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
				if(result.NextRow())
				{
					m_clipBoardStr[i][j] = result.GetString(0);
				}
				result.Finalize();
			}
		}
	}
}
