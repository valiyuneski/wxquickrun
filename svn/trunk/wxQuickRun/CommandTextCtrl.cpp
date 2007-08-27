/**
 *	wxQuickRun
 *	Copyright � 2006-2007, Priyank Bolia.
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
 *	\file CommandTextCtrl.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include <wx/mimetype.h>
#include <wx/datetime.h>
#include <wx/filename.h>
#include <wx/clipbrd.h>
#include <wx/dir.h>
#include <wx/filename.h>

#include "wxQuickRun.h"
#include "CommandTextCtrl.h"
#include "AboutDialog.h"
#include "AddKeywordDialog.h"
#include "AddTaskDialog.h"
#include "ContactsPanel.h"
#include "AddContactDialog.h"
#include "SetupDialog.h"
#include "QuickRunFrame.h"
#include "ParametersDlg.h"
#include "SendKeys.h"
#include "muParser.h"

//Files included for creating a shell link
#include <Shlobj.h>
#include <atldef.h>
#include <atlconv.h>
#include <atlbase.h>

#define PATH_MAX 256

typedef  bool (CCommandTextCtrl::*CommandHandlers)(wxString);
#define CALL_COMMAND_HANDLER(object, ptrToMember)  ((object).*(ptrToMember))

CCommandTextCtrl* CCommandTextCtrl::m_pCommandTextCtrl = NULL;

BEGIN_EVENT_TABLE(CCommandTextCtrl, wxAutoTextCtrl)
	EVT_KEY_DOWN(CCommandTextCtrl::OnKeyDown)
	EVT_CHAR(CCommandTextCtrl::OnChar)
	EVT_CONTEXT_MENU(CCommandTextCtrl::OnContextMenu)
	EVT_SET_FOCUS(CCommandTextCtrl::OnSetFocus)
	EVT_KILL_FOCUS(CCommandTextCtrl::OnKillFocus)
	EVT_TEXT_ENTER(wxID_ANY, CCommandTextCtrl::OnTextEnter)
	EVT_MENU_RANGE(wxID_MENU_POPUP_KEYWORDS, wxID_MENU_POPUP_KEYWORDS+MAX_KEYWORDS, CCommandTextCtrl::OnMenuKeywords)
	EVT_MENU(wxID_MENU_POPUP_SETUP, CCommandTextCtrl::OnMenuSetup)
	EVT_MENU(wxID_MENU_POPUP_EXIT, CCommandTextCtrl::OnMenuExit)
	EVT_MENU(wxID_MENU_POPUP_ABOUT, CCommandTextCtrl::OnMenuAbout)
	EVT_MENU(wxID_MENU_POPUP_CUT, CCommandTextCtrl::OnMenuCut)
	EVT_MENU(wxID_MENU_POPUP_COPY, CCommandTextCtrl::OnMenuCopy)
	EVT_MENU(wxID_MENU_POPUP_PASTE, CCommandTextCtrl::OnMenuPaste)
	EVT_UPDATE_UI(wxID_MENU_POPUP_CUT, CCommandTextCtrl::OnUpdateMenuCut)
	EVT_UPDATE_UI(wxID_MENU_POPUP_COPY, CCommandTextCtrl::OnUpdateMenuCopy)
	EVT_UPDATE_UI(wxID_MENU_POPUP_PASTE, CCommandTextCtrl::OnUpdateMenuPaste)
	EVT_MENU(wxID_MENU_POPUP_SHOW_HIDE, CCommandTextCtrl::OnMenuShowHide)
	EVT_MENU(wxID_MENU_POPUP_MOVE_USING_KEYBOARD, CCommandTextCtrl::OnMenuMoveUsingKeyboard)
	EVT_MENU(wxID_MENU_POPUP_ADD_KEYWORD, CCommandTextCtrl::OnMenuAddKeyword)
	EVT_MENU(wxID_MENU_POPUP_ADD_TASK, CCommandTextCtrl::OnMenuAddTask)
	EVT_MENU(wxID_MENU_POPUP_ADD_CONTACT, CCommandTextCtrl::OnMenuAddContact)
	EVT_TIMER(wxID_TIMER, CCommandTextCtrl::OnTimer)
	EVT_LEFT_DOWN(CCommandTextCtrl::OnLeftDown)
	EVT_RIGHT_DOWN(CCommandTextCtrl::OnRightDown)
	EVT_CLOSE(CCommandTextCtrl::OnClose)
END_EVENT_TABLE()

CCommandTextCtrl::CCommandTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxAutoTextCtrl(parent, id, value, pos, size, style, validator, name)
, m_pTimer(NULL)
, m_bMove(false)
{
	m_mapSmartProgrammer["sf"] = "http://sourceforge.net/search/?type_of_search=soft&words=$word";
	m_mapSmartProgrammer["cpp"] = "http://www.google.com/search?q=$word&sitesearch=www.cppreference.com&btnG=Search";
	m_mapSmartProgrammer["perl"] = "http://perldoc.perl.org/search.html?q=$word";
	m_mapSmartProgrammer["php"] = "http://us3.php.net/manual-lookup.php?pattern=$word";
	m_mapSmartProgrammer["msdn"] = "http://search.msdn.microsoft.com/search/default.aspx?siteId=0&tab=0&query=$word";
	m_mapSmartProgrammer["sql"] = "http://dev.mysql.com/doc/mysql/search.php?q=$word&base=dev.mysql.com&lang=en&version=5.0&doc=1-5.0&m=o";
	m_mapSmartProgrammer["html"] = "http://www.htmldog.com/reference/htmltags/$word/";
	m_mapSmartProgrammer["css"] = "http://www.htmldog.com/reference/cssproperties/$word";
	m_mapSmartProgrammer["js"] = "http://search.freefind.com/find.html?id=63658479&pageid=r&mode=ALL&n=0&query=$word&I1.x=0&I1.y=0";
	m_mapSmartProgrammer["ogl"] = "http://www.google.com/search?q=$word&sitesearch=www.opengl.org/documentation/&btnG=Search";
	m_mapSmartProgrammer["delphi"] = "http://www.delphibasics.co.uk/RTL.asp?Name=$word";
	m_mapSmartProgrammer["python"] = "http://www.google.com/search?hl=en&domains=docs.python.org&q=$word&btnG=Search&sitesearch=docs.python.org";
	m_mapSmartProgrammer["wx"] = "http://www.google.com/search?q=$word&sitesearch=www.wxwidgets.org/manuals/2.8.0/&btnG=Search";
	m_mapSmartProgrammer["wiki"] = "http://en.wikipedia.org/wiki/$word";
	m_mapSmartProgrammer["google"] = "http://www.google.com/search?q=$word&client=wxQuickRun";
	SetBeepOnInvalidValue(false);
	m_pTimer = new wxTimer(this, wxID_TIMER);
	m_pTimer->Start(m_nTimerInterval, wxTIMER_CONTINUOUS);
	ShowTime();
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select keyword from Commands"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			AddValidInputValues(result.GetString(0));
		}
	}
	else
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table Commands(ID INTEGER PRIMARY KEY AUTOINCREMENT, keyword VARCHAR(32), executableFile VARCHAR(255), params VARCHAR(255), startUpPath VARCHAR(255), notes VARCHAR(255));"));
	}
	if(wxSQLiteDB->TableExists(wxT("users")))
	{
		wxString sqlCmd = wxString::Format(wxT("select nickName from users"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			AddValidInputValues(wxT("c:")+result.GetString(0));
			AddValidInputValues(wxT("m:")+result.GetString(0));
		}
	}
	else
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE users(ID INTEGER PRIMARY KEY AUTOINCREMENT, title VARCHAR(16), firstName VARCHAR(128), middleName VARCHAR(128), lastName VARCHAR(128), suffix VARCHAR(32), nickName VARCHAR(64));"));
	}
	if(!wxSQLiteDB->TableExists(wxT("settings")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(255), value VARCHAR(255));"));
	}
	else
	{
		wxString strFaceName = wxT("Times New Roman");
		wxFontWeight fontWeight = wxFONTWEIGHT_NORMAL;
		int fontStyle = wxFONTSTYLE_NORMAL;
		int nPointSize = 12;
		wxColour fontColor = *wxBLACK;
		wxString sqlCmd;
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'FaceName';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				strFaceName = result.GetString(0);
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'FontWeight';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				fontWeight = (wxFontWeight)wxAtoi(result.GetString(0));
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'fontStyle';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				fontStyle = wxAtoi(result.GetString(0));
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'fontColor';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				fontColor = wxAtol(result.GetString(0));
		}
		{
			sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'PointSize';"));
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
				nPointSize = wxAtoi(result.GetString(0));
		}
		wxFont font = GetFont();
		font.SetFaceName(strFaceName);
		font.SetWeight(fontWeight);
		font.SetStyle(fontStyle);
		font.SetPointSize(nPointSize);
		wxTextAttr textAttr = GetDefaultStyle();
		textAttr.SetFont(font);
		textAttr.SetTextColour(fontColor);
		SetDefaultStyle(textAttr);
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;

	m_pCommandTextCtrl = this;
}

CCommandTextCtrl::~CCommandTextCtrl(void)
{
	m_pCommandTextCtrl = NULL;
	m_pTimer->Stop();
	delete m_pTimer;
	m_pTimer = NULL;
}

void CCommandTextCtrl::ExecuteCommand(wxString strExecCommand)
{
	m_strLastCommand = strExecCommand;
	if(strExecCommand == wxEmptyString)
		return;
	if(SmartProgrammer(strExecCommand))
		return;
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select executableFile, params, startUpPath, ID from Commands WHERE keyword = '%s'"), strExecCommand);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		bool bExecuted = false;
		if(result.NextRow())
		{
			wxString strFileName = result.GetString(0);
			wxFileName filename(strFileName);
			wxString param = result.GetString(1);
			int nCommandID = result.GetInt(3);
			result.Finalize();
			if(wxSQLiteDB)
				wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;
			if(param.Find(wxT("???")) > -1)
			{
				CParametersDlg paramDlg(this);
				paramDlg.SetCommandID(nCommandID);
				if(paramDlg.ShowModal() == wxID_OK)
				{
					param.Replace(wxT("???"), paramDlg.GetParameter());
				}
			}
			if(filename.GetExt().Lower() == wxT("bat"))
			{
				wxString strTmpFile = wxFileName::CreateTempFileName(wxT("wxQuickRun"));
				wxFileName tmpFile(strTmpFile);
				tmpFile.SetExt(wxT("lnk"));
				if(CreateLink(filename.GetFullPath(), tmpFile.GetFullPath(), wxT("wxQuickRun"), filename.GetPath())==S_OK)
				{
					wchar_t wcStrPath[PATH_MAX], wcStrParams[PATH_MAX];
					_tcscpy_s(wcStrPath, PATH_MAX, tmpFile.GetFullPath());
					_tcscpy_s(wcStrParams, PATH_MAX, param);
					SHELLEXECUTEINFO ShExecInfo = {0};
					ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
					ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
					ShExecInfo.hwnd = NULL;
					ShExecInfo.lpVerb = NULL;
					ShExecInfo.lpFile = wcStrPath;		
					ShExecInfo.lpParameters = wcStrParams;	
					ShExecInfo.lpDirectory = NULL;
					ShExecInfo.nShow = SW_SHOW;
					ShExecInfo.hInstApp = NULL;	
					ShellExecuteEx(&ShExecInfo);
					WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
				}
				wxRemoveFile(tmpFile.GetFullPath());
			}
			else if(filename.GetExt().Lower() == wxT("lnk"))
			{
				wchar_t wcStrPath[PATH_MAX], wcStrParams[PATH_MAX];
				_tcscpy_s(wcStrPath, PATH_MAX, strFileName);
				_tcscpy_s(wcStrParams, PATH_MAX, param);
				SHELLEXECUTEINFO ShExecInfo = {0};
				ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
				ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
				ShExecInfo.hwnd = NULL;
				ShExecInfo.lpVerb = NULL;
				ShExecInfo.lpFile = wcStrPath;		
				ShExecInfo.lpParameters = wcStrParams;	
				ShExecInfo.lpDirectory = NULL;
				ShExecInfo.nShow = SW_SHOW;
				ShExecInfo.hInstApp = NULL;	
				ShellExecuteEx(&ShExecInfo);
				WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
			}
			// Check for the sendkeys & keysgroup
			else if(strFileName.Lower()==wxT("sendkeys") && param != wxEmptyString)
			{
				CSendKeys sendKeys;
				sendKeys.SendKeys(param, true);
				wxMilliSleep(500);
				bExecuted = true;
			}
			else if(strFileName.Lower()==wxT("keysgroup") && param != wxEmptyString)
			{
				wxString paramCommands = param;
				wxString strCommand;
				while(paramCommands != wxEmptyString)
				{
					int nLoc = paramCommands.Find(wxT("|"));
					if(nLoc > 0)
					{
						strCommand = paramCommands.Left(nLoc);
						paramCommands = paramCommands.Right(paramCommands.Length()-nLoc-1);
					}
					else
					{
						strCommand = paramCommands;
						paramCommands = wxEmptyString;
					}
					ExecuteCommand(strCommand);
					wxMilliSleep(500);
				}
				bExecuted = true;
			}
			else if(wxExecute(strFileName+wxT(" ")+param, wxEXEC_ASYNC, NULL) >= 0)
			{
				bExecuted = true;
			}
		}
		if(bExecuted == false)
		{
			// This is like chain of responsibility design pattern.
			CommandHandlers handlers[] = {
				&CCommandTextCtrl::OnFilesAndFolderHandler, 
				&CCommandTextCtrl::OnHttpURLHandler,
				&CCommandTextCtrl::OnSendMailHandler,
				&CCommandTextCtrl::OnContactsHandler,
				&CCommandTextCtrl::OnMathematicalEvaluatorHandler,
				&CCommandTextCtrl::OnWindowsExecutionHandler
			};
			int count = sizeof(handlers)/sizeof(void*);
			for (int index=0; index < count; index++)
			{
				if (CALL_COMMAND_HANDLER(*this, handlers[index])(strExecCommand) == true)
					break;
			}
		}
	}
	if(wxSQLiteDB)
		wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CCommandTextCtrl::OnTextEnter(wxCommandEvent &event)
{
	ExecuteCommand(GetValue());
	event.Skip(true);
}

void CCommandTextCtrl::OnKeyDown(wxKeyEvent &event)
{
	if(m_bMove)
	{
		wxPoint point = GetParent()->GetPosition();
		switch(event.GetKeyCode())
		{
		case WXK_LEFT:
			point.x -= 1;
			GetParent()->Move(point);
			break;
		case WXK_RIGHT:
			point.x += 1;
			GetParent()->Move(point);
			break;
		case WXK_UP:
			point.y -= 1;
			GetParent()->Move(point);
			break;
		case WXK_DOWN:
			point.y += 1;
			GetParent()->Move(point);
			break;
		case WXK_RETURN:
			m_bMove = false;
			break;
		}
	}
	else
	{
		event.Skip(true);
	}
	if(WXK_ESCAPE == event.GetKeyCode())
	{
		m_bMove = false;
		((CQuickRunFrame*)GetParent())->ShowTaskIcon(true);
	}
}

void CCommandTextCtrl::OnChar(wxKeyEvent &event)
{
	if(event.GetKeyCode() == WXK_F3)
	{
		wxLaunchDefaultBrowser(wxString::Format(wxT("google.com/search?q=%s&client=wxQuickRun"), GetValue()));
	}
	else if (event.GetKeyCode() == WXK_F1)
	{
		wxLaunchDefaultBrowser(wxString::Format(wxT("answers.com/main/ntquery?s=%s"), GetValue()));
	}
	else if (event.GetKeyCode() == WXK_F4)
	{
		wxLaunchDefaultBrowser(wxString::Format(wxT("en.wikipedia.org/wiki/Special:Search?search=%s&fulltext=fulltext&sourceid=wxQuickRun"), GetValue()));
	}
	else if (event.GetKeyCode() == WXK_F10)
	{
		CSetupDialog setupDlg(this, CSetupDialog::wxID_DIALOG_SETUP);
		setupDlg.ShowModal();
	}
	event.Skip(true);
}

void CCommandTextCtrl::OnContextMenu(wxContextMenuEvent &event)
{
	wxMenu *pPOPMenu = new wxMenu();
	wxMenu* keywords = new wxMenu;

	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select ID, keyword from Commands"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			keywords->Append(wxID_MENU_POPUP_KEYWORDS+result.GetInt(0), result.GetString(1));
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;

	wxMenuItem* move = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_MOVE_USING_KEYBOARD, wxT("&Move using keyboard"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* keyword = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_ADD_KEYWORD, wxT("Add &Keyword..."), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* task = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_ADD_TASK, wxT("A&dd Task..."), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* contact = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_ADD_CONTACT, wxT("Add &Contact..."), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* hide = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_SHOW_HIDE, wxT("&Hide in Taskbar"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* setup = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_SETUP, wxT("&Setup..."), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* cut = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_CUT, wxT("Cu&t"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* copy = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_COPY, wxT("&Copy"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* paste = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_PASTE, wxT("&Paste"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* about = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_ABOUT, wxT("&About"), wxEmptyString, wxITEM_NORMAL);
	wxMenuItem* exit = new wxMenuItem(pPOPMenu, wxID_MENU_POPUP_EXIT, wxT("E&xit"), wxEmptyString, wxITEM_NORMAL);
	pPOPMenu->Append(wxID_MENU_POPUP_KEYWORDS, wxT("Key&words"), keywords );
	pPOPMenu->Append(hide); 
	pPOPMenu->Append(move); 
	pPOPMenu->AppendSeparator();
	pPOPMenu->Append(keyword); 
	pPOPMenu->Append(task); 
	pPOPMenu->Append(contact); 
	pPOPMenu->AppendSeparator();
	pPOPMenu->Append(setup); 
	pPOPMenu->AppendSeparator();
	pPOPMenu->Append(cut); 
	pPOPMenu->Append(copy); 
	pPOPMenu->Append(paste); 
	pPOPMenu->AppendSeparator();
	pPOPMenu->Append(about); 
	pPOPMenu->AppendSeparator();
	pPOPMenu->Append(exit); 
	this->PopupMenu(pPOPMenu, ScreenToClient(event.GetPosition()));
	delete pPOPMenu;
	pPOPMenu = NULL;

	event.Skip(false);
}

void CCommandTextCtrl::OnSetFocus(wxFocusEvent &event)
{
	Clear();
	SetLastUsedCommand();
	event.Skip(true);
}

void CCommandTextCtrl::OnKillFocus(wxFocusEvent &event)
{
	//ShowTime();
	((CQuickRunFrame *)GetParent())->ShowTaskIcon(true);
	m_bMove = false;
	event.Skip(true);
}

void CCommandTextCtrl::OnMenuExit(wxCommandEvent &event)
{
	GetParent()->Close();
	event.Skip(true);
}

void CCommandTextCtrl::OnMenuAbout(wxCommandEvent &event)
{
	CAboutDialog dlgAbout(this, CAboutDialog::wxID_DIALOG_ABOUT);
	dlgAbout.ShowModal();
	event.Skip(true);
}

void CCommandTextCtrl::OnTimer(wxTimerEvent &event)
{
	ShowTime();
	event.Skip(false);
}

void CCommandTextCtrl::ShowTime(void)
{
	if(FindFocus() != this)
	{
		wxDateTime now = wxDateTime::Now();
		SetValue(now.Format(wxT("%a %d %b %I:%M %p"), wxDateTime::Local));
	}
}

void CCommandTextCtrl::OnMenuShowHide(wxCommandEvent& WXUNUSED(event))
{
	((CQuickRunFrame *)GetParent())->ShowTaskIcon(GetParent()->IsShown());
}

void CCommandTextCtrl::OnMenuCut(wxCommandEvent& WXUNUSED(event))
{
	Cut();
}

void CCommandTextCtrl::OnMenuCopy(wxCommandEvent& WXUNUSED(event))
{
	Copy();
}

void CCommandTextCtrl::OnMenuPaste(wxCommandEvent& WXUNUSED(event))
{
	Paste();
}

void CCommandTextCtrl::OnUpdateMenuCut(wxUpdateUIEvent &event)
{
	event.Enable(CanCut());
}

void CCommandTextCtrl::OnUpdateMenuCopy(wxUpdateUIEvent &event)
{
	event.Enable(CanCopy());
}

void CCommandTextCtrl::OnUpdateMenuPaste(wxUpdateUIEvent &event)
{
	event.Enable(CanPaste());
}

void CCommandTextCtrl::OnMenuMoveUsingKeyboard(wxCommandEvent& WXUNUSED(event))
{
	m_bMove = true;
	this->SetFocus();
}

void CCommandTextCtrl::OnMenuAddKeyword(wxCommandEvent& WXUNUSED(event))
{
	CAddKeywordDialog dlgSetup(this, CAddKeywordDialog::wxID_DIALOG_ADD_KEYWORD, wxT("wxQuickRun"));
	dlgSetup.ShowModal();
}

void CCommandTextCtrl::OnMenuSetup(wxCommandEvent& WXUNUSED(event))
{
	CSetupDialog setupDlg(this, CSetupDialog::wxID_DIALOG_SETUP);
	setupDlg.ShowModal();
}

void CCommandTextCtrl::OnMenuKeywords(wxCommandEvent &event)
{
	OnExecuteKeywords(event.GetId());
	event.Skip(false);
}

void CCommandTextCtrl::OnExecuteKeywords(int eventID)
{
	int keyID = eventID-wxID_MENU_POPUP_KEYWORDS;
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select executableFile, params, startUpPath from Commands WHERE ID=%d"), keyID);
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			wxExecute(result.GetString(0)+wxT(" ")+result.GetString(1), wxEXEC_ASYNC, NULL);
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
}

void CCommandTextCtrl::OnMenuAddTask(wxCommandEvent& WXUNUSED(event))
{
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(!wxSQLiteDB->TableExists(wxT("categories")))
	{
		wxSQLiteDB->ExecuteUpdate(wxT("create table categories(ID INTEGER PRIMARY KEY AUTOINCREMENT, category VARCHAR(255));"));
		wxMessageBox(wxT("Please add a task category, before creating a task."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		return;
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT category FROM categories"));
		wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
		if(!result.NextRow())
		{
			wxMessageBox(wxT("Please add a task category, before creating a task."), wxT("wxQuickRun"), wxOK | wxCENTRE | wxICON_ERROR, this);
			wxSQLiteDB->Close();
			delete wxSQLiteDB;
			wxSQLiteDB = NULL;
			return;
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	CAddTaskDialog addTaskDlg(this, CAddTaskDialog::wxID_DIALOG_ADD_TASK);
	addTaskDlg.ShowModal();
}

void CCommandTextCtrl::OnMenuAddContact(wxCommandEvent& WXUNUSED(event))
{
	CAddContactDialog addContact(this, CAddContactDialog::wxID_DIALOG_ADD_CONTACT);
	addContact.ShowModal();
}

void CCommandTextCtrl::OnLeftDown(wxMouseEvent &event)
{
	if(m_bMove)
		m_bMove = false;
	event.Skip(true);
}

void CCommandTextCtrl::OnRightDown(wxMouseEvent &event)
{
	if(m_bMove)
		m_bMove = false;
	event.Skip(true);
}

void CCommandTextCtrl::OnClose(wxCloseEvent &event)
{
	DestroyChildren();
	event.Skip(true);
}

HRESULT CCommandTextCtrl::CreateLink(LPCWSTR FilePath, LPCWSTR LnkPath, LPCWSTR LnkDesc, LPCWSTR WorkDir) 
{ 
	USES_CONVERSION;
	CoInitialize(NULL);
	IShellLink* psl;             
	HRESULT  hres = CoCreateInstance(CLSID_ShellLink, NULL, 
		CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl); 
	if (SUCCEEDED(hres)) 
	{ 
		IPersistFile* ppf; 

		psl->SetPath(FilePath); 
		psl->SetWorkingDirectory(WorkDir);
		psl->SetDescription(LnkDesc); 

		hres = psl->QueryInterface(IID_IPersistFile,(LPVOID*)&ppf); 

		if (SUCCEEDED(hres)) 
		{    
			hres = ppf->Save(LnkPath, TRUE); 
			ppf->Release(); 
		} 
		psl->Release(); 
	}
	CoUninitialize();
	return hres; 
} 

bool CCommandTextCtrl::SmartProgrammer(wxString strCommand)
{
	if(strCommand.Find(wxT(':')) > 0)
	{
		wxString strLang = strCommand.Left(strCommand.Find(wxT(':')));
		wxString strQuery = strCommand.Right(strCommand.Length() - strCommand.Find(wxT(':')) - 1);
		strLang = strLang.Trim(false);
		strLang = strLang.Trim(true);
		std::map<string, string>::iterator iter = m_mapSmartProgrammer.find(wxStringToChar(strLang));
		if(iter != m_mapSmartProgrammer.end())
		{
			string sURL = iter->second;
			wxString strURL = wxString::FromAscii(sURL.c_str());
			strQuery = strQuery.Trim(false);
			strQuery = strQuery.Trim(true);
			strURL.Replace(wxT("$word"), strQuery);
			wxLaunchDefaultBrowser(strURL);
			return true;
		}
	}
	return false;
}

void CCommandTextCtrl::SetLastUsedCommand()
{
	if(m_strLastCommand != wxEmptyString)
	{
		SetValue(m_strLastCommand);
		SetSelection(0, -1);
	}
}

bool CCommandTextCtrl::OnMathematicalEvaluatorHandler(wxString strExp)
{
	try
	{
		mu::Parser p;
		std::string strExp(strExp.mb_str());
		p.SetExpr(strExp);
		wxString strResult;
		strResult << p.Eval();
		SetValue(strResult);
		SetInsertionPointEnd();
	}
	catch (mu::Parser::exception_type& WXUNUSED(e))
	{
		return false;
	}
	return true;
}

bool CCommandTextCtrl::OnWindowsExecutionHandler(wxString strExecCommand)
{
	wxLogNull logNo;
	if(wxExecute(strExecCommand) >= 0)
		return true;
	return false;
}

bool CCommandTextCtrl::OnContactsHandler(wxString strExecCommand)
{
	if((strExecCommand.Find(wxT("c:"))==0 && strExecCommand.Find(wxT("c:\\"))!=0) || (strExecCommand.Find(wxT("C:"))==0 && strExecCommand.Find(wxT("C:\\"))!=0))
	{
		wxString strContact = strExecCommand;
		strContact.Replace(wxT("c:"), wxEmptyString);
		if(strContact == strExecCommand)
			strContact.Replace(wxT("C:"), wxEmptyString);
		strContact.Trim(false);
		strContact.Trim(true);
		CAddContactDialog dlgAddContact(this, CContactsPanel::wxID_DIALOG_ADD_CONTACT);
		wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
		wxSQLiteDB->Open(DATABASE_FILE);
		int nID = -1;
		if(wxSQLiteDB->TableExists(wxT("users")))
		{
			wxString sqlCmd = wxString::Format(wxT("SELECT ID FROM users WHERE nickName = '%s'"), strContact.Lower());
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				nID = result.GetInt(0);
			}
		}
		wxSQLiteDB->Close();
		delete wxSQLiteDB;
		wxSQLiteDB = NULL;
		dlgAddContact.SetEditMode( nID );
		if(dlgAddContact.ShowModal()==wxID_OK)
		{
		}
		return true;
	}
	return false;
}

bool CCommandTextCtrl::OnSendMailHandler(wxString strExecCommand)
{
	bool bSendMail = false;
	wxString strNickName = strExecCommand;
	strNickName.Replace(wxT("m:"), wxEmptyString);
	if(strNickName == strExecCommand)
		strNickName.Replace(wxT("M:"), wxEmptyString);
	strNickName.Trim(false);
	strNickName.Trim(true);
	wxSQLite3Database* wxSQLiteDB = new wxSQLite3Database();
	wxSQLiteDB->Open(DATABASE_FILE);
	if(wxSQLiteDB->TableExists(wxT("users")))
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT emailAddress from email WHERE userID IN (SELECT ID FROM users WHERE nickName = '%s')"), strNickName.Lower());
		try
		{
			wxSQLite3ResultSet result = wxSQLiteDB->ExecuteQuery(sqlCmd);
			if(result.NextRow())
			{
				wxLogNull logNo;
				wxString strEmail = wxT("mailto:")+result.GetString(0);
#ifdef __WXMSW__
				::ShellExecute(NULL, wxT("open"), strEmail, NULL, NULL, SW_NORMAL);
#endif
				bSendMail = true;
			}
		}
		catch (...)
		{
		}
	}
	wxSQLiteDB->Close();
	delete wxSQLiteDB;
	wxSQLiteDB = NULL;
	return bSendMail;
}

bool CCommandTextCtrl::OnHttpURLHandler(wxString strExecCommand)
{
	if(strExecCommand.Find(wxT("http://"))==0 || strExecCommand.Find(wxT("www."))==0)
	{
		wxLaunchDefaultBrowser(strExecCommand);
		return true;
	}
	return false;
}

bool CCommandTextCtrl::OnFilesAndFolderHandler(wxString strExecCommand)
{
	if(wxFileName::FileExists(strExecCommand))
	{
		wxString runCmd;
		wxString strCMD = strExecCommand;
		wxString strExt = wxFileName(strCMD).GetExt();
		wxMimeTypesManager mgr;
		wxFileType* ft = mgr.GetFileTypeFromExtension(strExt);
		runCmd = ft->GetOpenCommand(strExecCommand);
		wxDELETE( ft );
		if ( runCmd != wxEmptyString )
		{
			if(wxExecute( runCmd ) >= 0)
				return true;
		}
	}
	else if(wxDir::Exists(strExecCommand))
	{
#ifdef __WXMSW__
		wxString strCmd = wxT("explorer ") + strExecCommand;
		if(wxExecute(strCmd) >= 0)
			return true;
#endif
	}
	return false;
}