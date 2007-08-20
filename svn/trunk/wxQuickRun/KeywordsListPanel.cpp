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
 *	\file KeywordsListPanel.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 23 Jun, 2006
 **/

#include "KeywordsListPanel.h"
#include "AddKeywordDialog.h"
#include "OptionsPanel.h"
#include "ExtractIcon.h"
#include "wxQuickRun.h"
#include <wx/stdpaths.h>
#include <wx/icon.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CKeywordsListPanel, wxPanel)
	EVT_CLOSE(CKeywordsListPanel::OnClose)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_ADD, CKeywordsListPanel::OnAddKeyword)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_EDIT, CKeywordsListPanel::OnEditKeyword)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_DELETE, CKeywordsListPanel::OnDeleteKeyword)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_IMPORT, CKeywordsListPanel::OnImportKeyword)
	EVT_BUTTON(wxID_BUTTON_KEYWORD_EXPORT, CKeywordsListPanel::OnExportKeyword)
END_EVENT_TABLE()

CKeywordsListPanel::CKeywordsListPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxPanel(parent, id, pos, size, style, name)
, m_pKeywordsListCtrl(NULL)
, m_pButtonAdd(NULL)
, m_pButtonEdit(NULL)
, m_pButtonDelete(NULL)
, m_pButtonImport(NULL)
, m_pButtonExport(NULL)
, m_imageList(16, 16, TRUE)
{
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
	CreateGUIControls();
	FillKeywordsList();
}

CKeywordsListPanel::~CKeywordsListPanel(void)
{
}

void CKeywordsListPanel::OnClose(wxCloseEvent &event)
{
	m_imageList.RemoveAll();
	event.Skip(true);
}

void CKeywordsListPanel::CreateGUIControls()
{
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pKeywordsListCtrl = new wxListCtrl(this, wxID_LISTCTRL_KEYWORDS, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES | wxLC_SINGLE_SEL);
	m_pKeywordsListCtrl->InsertColumn(0, wxT("Keyword"), wxLIST_FORMAT_LEFT, 80);
	m_pKeywordsListCtrl->InsertColumn(1, wxT("Filename"), wxLIST_FORMAT_LEFT, 200);
	m_pKeywordsListCtrl->InsertColumn(2, wxT("Parameters"), wxLIST_FORMAT_LEFT, 120);
	m_pKeywordsListCtrl->InsertColumn(3, wxT("Notes"), wxLIST_FORMAT_LEFT, 85);
	wxBoxSizer *pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_pButtonAdd = new wxButton(this, wxID_BUTTON_KEYWORD_ADD, wxT("&Add"));
	m_pButtonEdit = new wxButton(this, wxID_BUTTON_KEYWORD_EDIT, wxT("&Edit"));
	m_pButtonDelete = new wxButton(this, wxID_BUTTON_KEYWORD_DELETE, wxT("&Delete"));
	m_pButtonImport = new wxButton(this, wxID_BUTTON_KEYWORD_IMPORT, wxT("&Import"));
	m_pButtonExport = new wxButton(this, wxID_BUTTON_KEYWORD_EXPORT, wxT("&Export"));
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonAdd, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonEdit, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonDelete, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(m_pButtonImport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->Add(m_pButtonExport, 0, wxALL | wxEXPAND, 2);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(m_pKeywordsListCtrl, 1, wxALL | wxEXPAND, 0);
	pMainSizer->Add(pButtonSizer, 0, wxALL | wxEXPAND, 5);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	m_pButtonImport->Disable();
	m_pButtonExport->Disable();
	m_pKeywordsListCtrl->SetImageList(&m_imageList, wxIMAGE_LIST_SMALL);
}

void CKeywordsListPanel::FillKeywordsList()
{
	m_pKeywordsListCtrl->DeleteAllItems();
	m_imageList.RemoveAll();
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select keyword, executableFile, params, startUpPath, notes from Commands"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		int nIndex = 0;
		while(result.NextRow())
		{
			// from winuser.h
			// #define LR_DEFAULTCOLOR     0x0000
			// #define LR_MONOCHROME       0x0001
			// #define LR_COLOR            0x0002
			#define MAX_ICON    1
			int cIcons = -1;
			HICON* pIcons = (HICON*)LocalAlloc( LPTR, MAX_ICON*sizeof(HICON) );
			if(pIcons != NULL)
			{
				if(result.GetString(1).Lower() == wxT("sendkeys") || result.GetString(1).Lower() == wxT("keysgroup"))
					cIcons = (int)ExtractIcons::Get(wxStandardPaths().GetExecutablePath(), 0, 16, 16, pIcons, NULL, MAX_ICON, LR_COLOR);
				else
					cIcons = (int)ExtractIcons::Get(result.GetString(1), 0, 16, 16, pIcons, NULL, MAX_ICON, LR_COLOR);
			}
			if(cIcons > 0)
			{
				wxIcon icon;
				icon.SetHICON((WXHICON)pIcons[0]);
				m_pKeywordsListCtrl->InsertItem(nIndex, result.GetString(0), m_imageList.Add(icon));
			}
			else
			{
				m_pKeywordsListCtrl->InsertItem(nIndex, result.GetString(0));
			}
			if(result.GetString(1).Lower() == wxT("sendkeys"))
				m_pKeywordsListCtrl->SetItem(nIndex, 1, wxT("SendKeys"));
			else if(result.GetString(1).Lower() == wxT("keysgroup"))
				m_pKeywordsListCtrl->SetItem(nIndex, 1, wxT("KeysGroup"));
			else
				m_pKeywordsListCtrl->SetItem(nIndex, 1, result.GetString(1));
			m_pKeywordsListCtrl->SetItem(nIndex, 2, result.GetString(2));
			m_pKeywordsListCtrl->SetItem(nIndex, 3, result.GetString(4));
			if( pIcons != NULL )
				LocalFree((HLOCAL)pIcons);
			nIndex++;
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CKeywordsListPanel::OnAddKeyword(wxCommandEvent &event)
{
	CAddKeywordDialog addKeyDlg(this, CAddKeywordDialog::wxID_DIALOG_ADD_KEYWORD);
	if(addKeyDlg.ShowModal()==wxID_OK)
		FillKeywordsList();
	event.Skip(false);
}

void CKeywordsListPanel::OnEditKeyword(wxCommandEvent &event)
{
	long item = -1;
	item = m_pKeywordsListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		wxString strKeyword = m_pKeywordsListCtrl->GetItemText(item);
		CAddKeywordDialog addKeyDlg(this, CAddKeywordDialog::wxID_DIALOG_ADD_KEYWORD);
		addKeyDlg.SetEditMode(strKeyword);
		if(addKeyDlg.ShowModal()==wxID_OK)
			FillKeywordsList();
	}
	event.Skip(false);
}

void CKeywordsListPanel::OnDeleteKeyword(wxCommandEvent &event)
{
	long item = -1;
	item = m_pKeywordsListCtrl->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if ( item != -1 )
	{
		wxString strKeyword = m_pKeywordsListCtrl->GetItemText(item);
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		if(wxSQLiteDB->TableExists(wxT("Commands")))
		{
			wxString sqlCmd = wxString::Format(wxT("DELETE FROM Commands WHERE keyword = '%s'"), strKeyword);
			wxSQLiteDB->ExecuteUpdate(sqlCmd);
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		m_pKeywordsListCtrl->DeleteItem(item);
	}
	event.Skip(false);
}

void CKeywordsListPanel::OnImportKeyword(wxCommandEvent &event)
{
	event.Skip(false);
}

void CKeywordsListPanel::OnExportKeyword(wxCommandEvent &event)
{
	event.Skip(false);
}
