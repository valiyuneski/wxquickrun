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
 *	\file AddKeywordDialog.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include <wx/filename.h>
#include "AddKeywordDialog.h"
#include "CommandTextCtrl.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CAddKeywordDialog, wxDialog)
	EVT_CLOSE(CAddKeywordDialog::OnClose)
	EVT_BUTTON(wxID_OK, CAddKeywordDialog::OnOK)
	EVT_BUTTON(wxID_BUTTON_FILE_DIALOG, CAddKeywordDialog::OnButtonFileDialog)
	EVT_INIT_DIALOG(CAddKeywordDialog::OnInitDialog)
END_EVENT_TABLE()

CAddKeywordDialog::CAddKeywordDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticKeyword(NULL)
, m_pStaticExecFile(NULL)
, m_pStaticParameters(NULL)
, m_pStaticStartUpPath(NULL)
, m_pStaticNotes(NULL)
, m_pTextCtrlKeyword(NULL)
, m_pTextCtrlExecFile(NULL)
, m_pTextCtrlParameters(NULL)
, m_pTextCtrlStartUpPath(NULL)
, m_pTextCtrlNotes(NULL)
, m_pButtonFileDialog(NULL)
{
	SetIcon(wxGetApp().GetMainFrameWindow()->GetIcon());
	CenterOnScreen();
}

CAddKeywordDialog::~CAddKeywordDialog(void)
{
}

void CAddKeywordDialog::OnClose(wxCloseEvent &event)
{
	event.Skip(true);
}

void CAddKeywordDialog::OnInitDialog(wxInitDialogEvent &event)
{
	///Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticBoxSizer* pStaticBoxSizer;
	if(m_strEditKeyword == wxEmptyString)
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Add keyword:"));
	else
		pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Edit keyword:"));

	wxBoxSizer *pStaticTextSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *pTextCtrlSizer = new wxBoxSizer(wxVERTICAL);

	m_pStaticKeyword = new wxStaticText(this, wxID_STATIC_TEXT_KEYWORD, wxT("Shortcut &Keyword:"));
	m_pTextCtrlKeyword = new wxTextCtrl(this, wxID_TEXTCTRL_KEYWORD, wxT(""));

	m_pStaticExecFile = new wxStaticText(this, wxID_STATIC_TEXT_EXEC_FILE, wxT("Executable &File:"));
	m_pTextCtrlExecFile = new wxTextCtrl(this, wxID_TEXTCTRL_EXEC_FILE, wxT(""));
	m_pButtonFileDialog = new wxButton(this, wxID_BUTTON_FILE_DIALOG, wxT("..."));

	m_pStaticParameters = new wxStaticText(this, wxID_STATIC_TEXT_PARAMETERS, wxT("Command &Parameters:"));
	m_pTextCtrlParameters = new wxTextCtrl(this, wxID_TEXTCTRL_PARAMETERS, wxT(""));

	m_pStaticStartUpPath = new wxStaticText(this, wxID_STATIC_TEXT_STARTUP_PATH, wxT("&Startup Path:"));
	m_pTextCtrlStartUpPath = new wxTextCtrl(this, wxID_TEXTCTRL_STARTUP_PATH, wxT(""));

	m_pStaticNotes = new wxStaticText(this, wxID_STATIC_TEXT_NOTES, wxT("&Notes:"));
	m_pTextCtrlNotes = new wxTextCtrl(this, wxID_TEXTCTRL_NOTES, wxT(""));

	pStaticTextSizer->Add(m_pStaticKeyword, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticExecFile, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticParameters, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticStartUpPath, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticNotes, 1, wxALL | wxEXPAND, 5);

	pTextCtrlSizer->Add(m_pTextCtrlKeyword, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	wxBoxSizer *pFileSizer = new wxBoxSizer(wxHORIZONTAL);
	pFileSizer->Add(m_pTextCtrlExecFile, 1, wxEXPAND, 0);
	pFileSizer->Add(m_pButtonFileDialog, 0, wxLEFT | wxEXPAND, 5);
	pTextCtrlSizer->Add(pFileSizer, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlParameters, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlStartUpPath, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlNotes, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);

	wxBoxSizer *pControlsSizer = new wxBoxSizer(wxHORIZONTAL);
	pControlsSizer->Add(pStaticTextSizer, 0, wxALL | wxEXPAND, 5);
	pControlsSizer->Add(pTextCtrlSizer, 1, wxALL | wxEXPAND, 5);
	pStaticBoxSizer->Add(pControlsSizer, 1, wxALL | wxEXPAND, 0);

	wxBoxSizer* pButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	pButtonSizer->AddStretchSpacer(1);
	pButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND, 0);
	pButtonSizer->AddStretchSpacer(1);

	pMainSizer->Add(pStaticBoxSizer, 1, wxEXPAND | wxALL, 10);
	pMainSizer->Add(pButtonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();
	if(m_strEditKeyword != wxEmptyString)
		FillDialog();
	m_pTextCtrlKeyword->SetFocus();
}

void CAddKeywordDialog::OnOK(wxCommandEvent& event)
{
	wxString strKeyword, strExecFile, strParameters, strStartUpPath, strNotes;
	strKeyword = m_pTextCtrlKeyword->GetValue();
	strExecFile = m_pTextCtrlExecFile->GetValue();
	strParameters = m_pTextCtrlParameters->GetValue();
	strStartUpPath = m_pTextCtrlStartUpPath->GetValue();
	strNotes = m_pTextCtrlNotes->GetValue();
	if(strKeyword == wxEmptyString)
	{
		wxMessageBox(wxT("Please enter a short keyword for the command to be executed."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		m_pTextCtrlKeyword->SetFocus();
		return;
	}
	if(strKeyword.Contains(wxT("|")))
	{
		wxMessageBox(wxT("Invalid characters in the keyword. Please enter it again using alphanumeric characters."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		m_pTextCtrlKeyword->SetFocus();
		return;
	}
	if (strExecFile == wxEmptyString || !wxFileName::FileExists(strExecFile))
	{
		wxString strFileName = strExecFile;
		strFileName = strFileName.Lower();
		strFileName.Trim(true);
		strFileName.Trim(false);
		if(strFileName == wxT("sendkeys"))
		{
		}
		else if(strFileName == wxT("keysgroup"))
		{
		}
		else
		{
			wxMessageBox(wxT("Please enter the full path of the executable file."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
			m_pTextCtrlExecFile->SetFocus();
			return;
		}
	}
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table Commands(ID INTEGER PRIMARY KEY AUTOINCREMENT, keyword VARCHAR(32), executableFile VARCHAR(255), params VARCHAR(255), startUpPath VARCHAR(255), notes VARCHAR(255));"));
	}

	int nIDOld = -1;
	if(m_strEditKeyword != wxEmptyString)
	{
		wxString sqlCmd = wxString::Format(wxT("Select ID from Commands WHERE keyword = '%s'"), strKeyword);
		nIDOld = wxSQLiteDB->ExecuteScalar(sqlCmd);
		sqlCmd = wxString::Format(wxT("Delete from Commands WHERE keyword = '%s'"), strKeyword);
		wxSQLiteDB->ExecuteUpdate(sqlCmd);
	}

	wxString sqlCmd = wxString::Format(wxT("select keyword from Commands WHERE keyword = '%s'"), strKeyword);
	wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
	if(result.NextRow())
	{
		wxMessageBox(wxT("The keyword has been already assigned. Please choose a different keyword."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		m_pTextCtrlKeyword->SetFocus();
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		return;
	}

	if(nIDOld == -1)
		sqlCmd = wxString::Format(wxT("Insert INTO Commands('keyword', 'executableFile', 'params', 'startUpPath', 'notes') VALUES('%s', '%s', '%s', '%s', '%s')"), strKeyword.MakeLower(), strExecFile, strParameters, strStartUpPath, strNotes);
	else
		sqlCmd = wxString::Format(wxT("Insert INTO Commands('ID', 'keyword', 'executableFile', 'params', 'startUpPath', 'notes') VALUES(%d, '%s', '%s', '%s', '%s', '%s')"), nIDOld, strKeyword.MakeLower(), strExecFile, strParameters, strStartUpPath, strNotes);
	wxSQLiteDB->ExecuteUpdate(sqlCmd);
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	if(m_strEditKeyword == wxEmptyString)
	{
		CCommandTextCtrl* pTextCtrl = static_cast<CCommandTextCtrl *>(CCommandTextCtrl::GetInstance());
		if(pTextCtrl)
			pTextCtrl->AddValidInputValues(strKeyword);
	}
	event.Skip(true);
}

void CAddKeywordDialog::OnButtonFileDialog(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog fileDlg(this, wxT("Choose an executable file"), wxEmptyString, wxEmptyString, wxT("Executable files (*.exe)|*.exe;|All files (*.*)|*.*"), wxOPEN | wxFILE_MUST_EXIST);
	if(fileDlg.ShowModal() == wxID_OK)
	{
		m_pTextCtrlExecFile->SetValue(fileDlg.GetPath());
	}
}

void CAddKeywordDialog::SetEditMode(wxString strEditKeyword)
{
	 m_strEditKeyword = strEditKeyword;
}

void CAddKeywordDialog::FillDialog()
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select executableFile, params, startUpPath, notes from Commands WHERE keyword='%s'"), m_strEditKeyword);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			m_pTextCtrlKeyword->SetValue(m_strEditKeyword);
			m_pTextCtrlExecFile->SetValue(result.GetString(0));
			m_pTextCtrlParameters->SetValue(result.GetString(1));
			m_pTextCtrlStartUpPath->SetValue(result.GetString(2));
			m_pTextCtrlNotes->SetValue(result.GetString(3));
			m_pTextCtrlKeyword->Disable();
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}
