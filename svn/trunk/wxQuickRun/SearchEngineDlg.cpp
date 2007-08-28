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
 *	\file SearchEngineDlg.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 1 Nov, 2006
 **/
#include "SearchEngineDlg.h"
#include "SearchEntryDlg.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CSearchEngineDlg, wxDialog)
	EVT_CLOSE(CSearchEngineDlg::OnClose)
	EVT_INIT_DIALOG(CSearchEngineDlg::OnInitDialog)
	EVT_BUTTON(wxID_BUTTON_ADD, CSearchEngineDlg::OnAddButton)
	EVT_BUTTON(wxID_BUTTON_EDIT, CSearchEngineDlg::OnEditButton)
	EVT_BUTTON(wxID_BUTTON_DELETE, CSearchEngineDlg::OnDeleteButton)
	EVT_SIZE(CSearchEngineDlg::OnSize)
END_EVENT_TABLE()

CSearchEngineDlg::CSearchEngineDlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pListCtrlSearchEngine(NULL)
, m_pButtonAdd(NULL)
, m_pButtonEdit(NULL)
, m_pButtonDelete(NULL)
{
}

CSearchEngineDlg::~CSearchEngineDlg(void)
{
}

void CSearchEngineDlg::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CSearchEngineDlg::OnInitDialog(wxInitDialogEvent &event)
{
	///Sizer for adding the controls created by users
	wxBoxSizer *pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pListCtrlSearchEngine = new wxListCtrl(this, wxID_LISTCTRL_SEARCH_ENGINE, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_ADD, wxT("&Add"));
	m_pButtonEdit = new wxButton(this, wxID_BUTTON_EDIT, wxT("&Edit"));
	m_pButtonDelete = new wxButton(this, wxID_BUTTON_DELETE, wxT("&Delete"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonAdd, 0, wxALL|wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonEdit, 0, wxALL|wxEXPAND, 5);
	pButtonSizer->Add(m_pButtonDelete, 0, wxALL|wxEXPAND, 5);
	pButtonSizer->AddStretchSpacer(1);
	pMainSizer->Add(m_pListCtrlSearchEngine, 1, wxALL|wxEXPAND, 5);
	pMainSizer->Add(pButtonSizer, 0, wxALL|wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();

	m_pListCtrlSearchEngine->InsertColumn(0, wxT("Engine Name"), wxLIST_FORMAT_LEFT, 95);
	m_pListCtrlSearchEngine->InsertColumn(1, wxT("Search URL"), wxLIST_FORMAT_LEFT, m_pListCtrlSearchEngine->GetClientRect().GetWidth()-100);
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	FillSearchEnginesList();
}

void CSearchEngineDlg::OnAddButton(wxCommandEvent &event)
{
	CSearchEntryDlg searchEntryDlg(this);
	if(searchEntryDlg.ShowModal() == wxID_OK)
	{
		wxString strEngineName = searchEntryDlg.GetSearchEngineName();
		wxString strEngineURL = searchEntryDlg.GetSearchEngineURL();
		DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
		if(!dbConn->TableExists(wxT("searchengines")))
		{
			dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
		}
		else
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT COUNT(*) FROM searchengines WHERE name = '%s';"), strEngineName);
			if(dbConn->ExecuteScalar(sqlCmd) == 0)
			{
				wxString sqlCmd = wxString::Format(wxT("INSERT INTO searchengines(name, url) VALUES (?, ?);"));
				wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
				// Bind the variables to the SQL statement
				stmt.Bind(1, strEngineName);
				stmt.Bind(2, strEngineURL);
				// Execute the SQL Query
				stmt.ExecuteUpdate();
				int nIndex = m_pListCtrlSearchEngine->InsertItem(m_pListCtrlSearchEngine->GetItemCount(), strEngineName, -1);
				m_pListCtrlSearchEngine->SetItem(nIndex, 1, strEngineURL);
			}
			else
			{
				wxString strMsg = wxString::Format(wxT("A search engine with name: '%s' already present.\nPlease choose a differert search engine name."), strEngineName);
				wxMessageBox(strMsg, wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_ERROR, this);
			}
		}
	}
	event.Skip(false);
}

void CSearchEngineDlg::OnEditButton(wxCommandEvent &event)
{
	long item = -1;
	item = m_pListCtrlSearchEngine->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		CSearchEntryDlg searchEntryDlg(this);
		wxString strEngineName = GetTextByColumn(item, 0);
		wxString strEngineURL = GetTextByColumn(item, 1);

		searchEntryDlg.SetEditMode(true);
		searchEntryDlg.SetSearchEngineName(strEngineName);
		searchEntryDlg.SetSearchEngineURL(strEngineURL);
		if(searchEntryDlg.ShowModal() == wxID_OK)
		{
			DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
			if(!dbConn->TableExists(wxT("searchengines")))
			{
				dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
			}
			else
			{
				wxString sqlCmd = wxString::Format(wxT("SELECT COUNT(*) FROM searchengines WHERE name = '%s';"), searchEntryDlg.GetSearchEngineName());
				if(strEngineName == searchEntryDlg.GetSearchEngineName() || dbConn->ExecuteScalar(sqlCmd) == 0)
				{
					wxString sqlCmd = wxString::Format(wxT("UPDATE searchengines SET name = ?, url = ? WHERE name = ?;"));
					wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
					// Bind the variables to the SQL statement
					stmt.Bind(1, searchEntryDlg.GetSearchEngineName());
					stmt.Bind(2, searchEntryDlg.GetSearchEngineURL());
					stmt.Bind(3, strEngineName);
					// Execute the SQL Query
					stmt.ExecuteUpdate();
					m_pListCtrlSearchEngine->SetItem(item, 0, searchEntryDlg.GetSearchEngineName());
					m_pListCtrlSearchEngine->SetItem(item, 1, searchEntryDlg.GetSearchEngineURL());
				}
				else
				{
					wxString strMsg = wxString::Format(wxT("A search engine with name: '%s' already present.\nPlease choose a differert search engine name."), searchEntryDlg.GetSearchEngineName());
					wxMessageBox(strMsg, wxT("wxQuickRun"), wxOK|wxCENTRE|wxICON_ERROR, this);
				}
			}
		}
	}
	event.Skip(false);
}

void CSearchEngineDlg::OnDeleteButton(wxCommandEvent &event)
{
	long item = -1;
	item = m_pListCtrlSearchEngine->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		wxString strEngineName = m_pListCtrlSearchEngine->GetItemText(item);
		m_pListCtrlSearchEngine->DeleteItem(item);
		DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
		if(!dbConn->TableExists(wxT("searchengines")))
		{
			dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
		}
		else
		{
			wxString sqlCmd = wxString::Format(wxT("DELETE FROM searchengines WHERE name = ?;"));
			wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.Bind(1, strEngineName);
			// Execute the SQL Query
			stmt.ExecuteUpdate();
		}
	}
	event.Skip(false);
}

void CSearchEngineDlg::OnSize(wxSizeEvent &event)
{
	m_pListCtrlSearchEngine->SetColumnWidth(1, m_pListCtrlSearchEngine->GetClientRect().GetWidth()-100);
	event.Skip(true);
}

wxString CSearchEngineDlg::GetTextByColumn(long nIndex, int nCol)
{
	if ( m_pListCtrlSearchEngine->GetWindowStyle() & wxLC_REPORT ) 
	{
		wxListItem Item; // the item whose text we want
		Item.SetId(nIndex); // set the index
		Item.SetColumn(nCol); // set the column
		Item.SetMask(wxLIST_MASK_TEXT); // enable GetText()
		m_pListCtrlSearchEngine->GetItem(Item); // get the item     

		return Item.GetText(); // get and return its text
	}
	return wxEmptyString;
}

void CSearchEngineDlg::FillSearchEnginesList(void)
{
	m_pListCtrlSearchEngine->DeleteAllItems();
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("searchengines")))
	{
		dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT name, url FROM searchengines"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		int nCount = 0;
		while(result.NextRow())
		{
			int item = m_pListCtrlSearchEngine->InsertItem(nCount, result.GetString(0));
			m_pListCtrlSearchEngine->SetItem(item, 1, result.GetString(1));
			nCount++;
		}
		result.Finalize();
	}
}
