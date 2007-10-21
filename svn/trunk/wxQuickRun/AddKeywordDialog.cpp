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

#include <wx/mimetype.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include "AddKeywordDialog.h"
#include "CommandTextCtrl.h"
#include "TextDropHandler.h"
#include "wxQuickRun.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CAddKeywordDialog, wxDialog)
	EVT_CLOSE(CAddKeywordDialog::OnClose)
	EVT_BUTTON(wxID_OK, CAddKeywordDialog::OnOK)
	EVT_BUTTON(wxID_BUTTON_FILE_DIALOG, CAddKeywordDialog::OnButtonFileDialog)
	EVT_INIT_DIALOG(CAddKeywordDialog::OnInitDialog)
	EVT_DROP_FILES(CAddKeywordDialog::OnDropFiles)
END_EVENT_TABLE()

CAddKeywordDialog::CAddKeywordDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxDialog(parent, id, title, pos, size, style, name)
, m_pStaticTextKeyword(NULL)
, m_pStaticTextExecFile(NULL)
, m_pStaticTextParameters(NULL)
, m_pStaticTextStartUpPath(NULL)
, m_pStaticTextNotes(NULL)
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

void CAddKeywordDialog::OnInitDialog(wxInitDialogEvent& WXUNUSED(event))
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

	m_pStaticTextKeyword = new wxStaticText(this, wxID_STATIC_TEXT_KEYWORD, wxT("Shortcut &Keyword:"));
	m_pTextCtrlKeyword = new wxTextCtrl(this, wxID_TEXTCTRL_KEYWORD, wxT(""));

	m_pStaticTextExecFile = new wxStaticText(this, wxID_STATIC_TEXT_EXEC_FILE, wxT("Executable &File:"));
	m_pTextCtrlExecFile = new wxTextCtrl(this, wxID_TEXTCTRL_EXEC_FILE, wxT(""));
	m_pButtonFileDialog = new wxButton(this, wxID_BUTTON_FILE_DIALOG, wxT("..."));

	m_pStaticTextParameters = new wxStaticText(this, wxID_STATIC_TEXT_PARAMETERS, wxT("Command &Parameters:"));
	m_pTextCtrlParameters = new wxTextCtrl(this, wxID_TEXTCTRL_PARAMETERS, wxT(""));

	m_pStaticTextStartUpPath = new wxStaticText(this, wxID_STATIC_TEXT_STARTUP_PATH, wxT("&Startup Path:"));
	m_pTextCtrlStartUpPath = new wxTextCtrl(this, wxID_TEXTCTRL_STARTUP_PATH, wxT(""));

	m_pStaticTextNotes = new wxStaticText(this, wxID_STATIC_TEXT_NOTES, wxT("&Notes:"));
	m_pTextCtrlNotes = new wxTextCtrl(this, wxID_TEXTCTRL_NOTES, wxT(""));

	wxArrayString modifier;
	modifier.Add(wxT(""));
	modifier.Add(wxT("SHIFT"));
	modifier.Add(wxT("CTRL"));
	modifier.Add(wxT("ALT"));
	modifier.Add(wxT("SHIFT|WIN"));
	modifier.Add(wxT("CTRL|WIN"));
	modifier.Add(wxT("ALT|WIN"));
	modifier.Add(wxT("ALT|SHIFT"));
	modifier.Add(wxT("ALT|CTRL"));
	modifier.Add(wxT("SHIFT|CTRL"));
	modifier.Add(wxT("CTRL|ALT|WIN"));
	modifier.Add(wxT("ALT|SHIFT|CTRL"));

	m_pStaticTextHotKey = new wxStaticText(this, wxID_STATIC_TEXT_HOTKEY, wxT("&HotKey:"));
	m_pKeyInputCtrl = new CKeyInputCtrl(this, wxID_TEXTCTRL_KEY_INPUT, wxEmptyString);
	m_pComboBoxModifier = new wxComboBox(this, wxID_COMBOBOX_KEY_MODIFIER, modifier.Item(0), wxDefaultPosition, wxDefaultSize, modifier, wxCB_READONLY|wxCB_SORT);

	pStaticTextSizer->Add(m_pStaticTextKeyword, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextExecFile, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextParameters, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextStartUpPath, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextNotes, 1, wxALL | wxEXPAND, 5);
	pStaticTextSizer->Add(m_pStaticTextHotKey, 1, wxALL | wxEXPAND, 5);

	pTextCtrlSizer->Add(m_pTextCtrlKeyword, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	wxBoxSizer *pFileSizer = new wxBoxSizer(wxHORIZONTAL);
	pFileSizer->Add(m_pTextCtrlExecFile, 1, wxEXPAND, 0);
	pFileSizer->Add(m_pButtonFileDialog, 0, wxLEFT | wxEXPAND, 5);
	pTextCtrlSizer->Add(pFileSizer, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlParameters, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlStartUpPath, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	pTextCtrlSizer->Add(m_pTextCtrlNotes, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
	wxBoxSizer *pHotKeySizer = new wxBoxSizer(wxHORIZONTAL);
	pHotKeySizer->Add(m_pKeyInputCtrl, 1, wxEXPAND, 0);
	pHotKeySizer->Add(m_pComboBoxModifier, 1, wxLEFT | wxEXPAND, 5);
	pTextCtrlSizer->Add(pHotKeySizer, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);

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

	m_pKeyInputCtrl->SetModifierComboBox(m_pComboBoxModifier);

	SetSizer(pMainSizer);
	SetAutoLayout(true);
	Layout();
	if(m_strEditKeyword != wxEmptyString)
		FillDialog();
	m_pTextCtrlKeyword->SetFocus();
	wxWindow::DragAcceptFiles(true);
	SetDropTarget(new CTextDropTarget<CAddKeywordDialog>(this, &CAddKeywordDialog::OnDropText));
	if(!m_strFileName.IsEmpty())
	{
		OnFileDrop(m_strFileName);
	}
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
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("Commands")))
	{
		dbConn->ExecuteUpdate(wxT("create table Commands(ID INTEGER PRIMARY KEY AUTOINCREMENT, keyword VARCHAR(32), executableFile VARCHAR(255), params VARCHAR(255), startUpPath VARCHAR(255), notes VARCHAR(255));"));
	}

	int nIDOld = -1;
	if(m_strEditKeyword != wxEmptyString)
	{
		wxString sqlCmd = wxString::Format(wxT("Select ID from Commands WHERE keyword = '%s'"), strKeyword);
		nIDOld = dbConn->ExecuteScalar(sqlCmd);
		sqlCmd = wxString::Format(wxT("Delete from Commands WHERE keyword = '%s'"), strKeyword);
		dbConn->ExecuteUpdate(sqlCmd);
	}

	wxString sqlCmd = wxString::Format(wxT("select keyword from Commands WHERE keyword = '%s'"), strKeyword);
	wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
	if(result.NextRow())
	{
		wxMessageBox(wxT("The keyword has been already assigned. Please choose a different keyword."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		m_pTextCtrlKeyword->SetFocus();
		return;
	}
	result.Finalize();

	if(nIDOld == -1)
		sqlCmd = wxString::Format(wxT("Insert INTO Commands('keyword', 'executableFile', 'params', 'startUpPath', 'notes') VALUES('%s', '%s', '%s', '%s', '%s')"), strKeyword.MakeLower(), strExecFile, strParameters, strStartUpPath, strNotes);
	else
		sqlCmd = wxString::Format(wxT("Insert INTO Commands('ID', 'keyword', 'executableFile', 'params', 'startUpPath', 'notes') VALUES(%d, '%s', '%s', '%s', '%s', '%s')"), nIDOld, strKeyword.MakeLower(), strExecFile, strParameters, strStartUpPath, strNotes);
	dbConn->ExecuteUpdate(sqlCmd);
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
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(dbConn->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select executableFile, params, startUpPath, notes from Commands WHERE keyword='%s'"), m_strEditKeyword);
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			m_pTextCtrlKeyword->SetValue(m_strEditKeyword);
			m_pTextCtrlExecFile->SetValue(result.GetString(0));
			m_pTextCtrlParameters->SetValue(result.GetString(1));
			m_pTextCtrlStartUpPath->SetValue(result.GetString(2));
			m_pTextCtrlNotes->SetValue(result.GetString(3));
			m_pTextCtrlKeyword->Disable();
		}
		result.Finalize();
	}
}

void CAddKeywordDialog::OnDropFiles(wxDropFilesEvent &event)
{
	/// Don't handle multiple file drops
	if(event.GetNumberOfFiles() == 1)
	{
		wxString strFileName = ((wxString *)event.GetFiles())[0];
		OnFileDrop(strFileName);
	}
}

void CAddKeywordDialog::OnFileDrop(wxString strFileName)
{
	wxFileName fileName(strFileName);
	if (wxDir::Exists(strFileName))
	{
		m_pTextCtrlKeyword->SetValue(fileName.GetName());
		m_pTextCtrlExecFile->SetValue(wxGetOSDirectory() + wxFileName::GetPathSeparator() + wxT("explorer.exe"));
		m_pTextCtrlParameters->SetValue(strFileName+wxFileName::GetPathSeparator());
		m_pTextCtrlStartUpPath->SetValue(strFileName+wxFileName::GetPathSeparator());
	}
	else if(fileName.GetExt().Lower() == wxT("exe") || fileName.GetExt().Lower() == wxT("bat"))
	{
		m_pTextCtrlKeyword->SetValue(fileName.GetName());
		m_pTextCtrlExecFile->SetValue(strFileName);
		m_pTextCtrlParameters->SetValue(wxEmptyString);
		m_pTextCtrlStartUpPath->SetValue(fileName.GetPath()+wxFileName::GetPathSeparator());
	}
	else if(fileName.FileExists())
	{
		wxMimeTypesManager mgr;
		wxFileType* ft = mgr.GetFileTypeFromExtension(fileName.GetExt());
		wxString runCmd = ft->GetOpenCommand(fileName.GetFullPath());
		wxDELETE( ft );
		if ( runCmd != wxEmptyString )
		{
			m_pTextCtrlKeyword->SetValue(fileName.GetName());
			m_pTextCtrlExecFile->SetValue(ParseCommand(runCmd));
			m_pTextCtrlParameters->SetValue(ParseParameters(runCmd));
			m_pTextCtrlStartUpPath->SetValue(fileName.GetPath()+wxFileName::GetPathSeparator());
		}
	}
}

void CAddKeywordDialog::OnURLLinkDrop(wxString strURLLink)
{
	m_pTextCtrlKeyword->SetValue(ParseLink(strURLLink));
	m_pTextCtrlExecFile->SetValue(GetDefaultBrowser(strURLLink));
	m_pTextCtrlStartUpPath->SetValue(wxEmptyString);
}

wxString CAddKeywordDialog::ParseCommand(wxString strCommand)
{
	wxString strExecFile = strCommand;
	if(strExecFile.Find(wxT("WX_DDE#")) == 0)
	{
	}
	else if(strExecFile.Find('"') == wxNOT_FOUND)
	{
		strExecFile = strExecFile.Left(strExecFile.Find(wxT(' ')));
	}
	else
	{
		strExecFile = strExecFile.Left(strExecFile.Find(wxT("\" ")));
		strExecFile.Replace(wxT("\""), wxEmptyString);
	}
	return strExecFile;
}

wxString CAddKeywordDialog::ParseParameters(wxString strCommand)
{
	wxString strParameters = strCommand;
	if(strParameters.Find(wxT("WX_DDE#")) == 0)
	{
		strParameters = wxEmptyString;
	}
	else if(strParameters.Find('"') == wxNOT_FOUND)
	{
		strParameters = strParameters.Mid(strParameters.Find(wxT(' '))+1);
	}
	else
	{
		strParameters = strParameters.Mid(strParameters.Find(wxT("\" "))+2);
		strParameters.Replace(wxT("\""), wxEmptyString);
	}
	return strParameters;
}

wxString CAddKeywordDialog::ParseLink(wxString strCommand)
{
	wxString strLink = strCommand.Lower();
	strLink.Replace(wxT("http://"), wxEmptyString, true);
	strLink.Replace(wxT("www."), wxEmptyString, true);
	if(strLink.Find(wxT('/')) > 0)
	{
		strLink = strLink.Left(strLink.Find(wxT('/')));
	}
	if(strLink.Find(wxT('?')) > 0)
	{
		strLink = strLink.Left(strLink.Find(wxT('?')));
	}
	return strLink;
}

void CAddKeywordDialog::SetFileName(wxString strFile)
{
	m_strFileName  = strFile;
}

void CAddKeywordDialog::SetLinkName(wxString strURLLink)
{
	m_strURLLinkName = strURLLink;
}

bool CAddKeywordDialog::OnDropText(wxCoord, wxCoord, const wxString& data)
{
	wxFileName fileName(data);
	wxString strLink = data.Lower();
	if(fileName.DirExists() || fileName.FileExists())
	{
		OnFileDrop(data);
	}
	else if(strLink.Find(wxT("http://")) == 0 || strLink.Find(wxT("www.")) == 0)
	{
		OnURLLinkDrop(data);
	}
	return true;
}

wxString CAddKeywordDialog::GetDefaultBrowser(wxString strLink)
{
	wxMimeTypesManager mgr;
	wxFileType* ft = mgr.GetFileTypeFromExtension(wxT("html"));
	wxString runCmd = ft->GetOpenCommand(strLink);
	wxDELETE( ft );
	return runCmd;
}
