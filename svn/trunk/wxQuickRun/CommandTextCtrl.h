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
 *	\file CommandTextCtrl.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/timer.h>
#include "wxAutoTextCtrl.h"
#include <map>
#include <string>

using namespace std;

class CCommandTextCtrl : public wxAutoTextCtrl
{
public:
	CCommandTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTE_PROCESS_ENTER | wxTE_LEFT | wxTE_CHARWRAP, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("Command Text Ctrl"));
	virtual ~CCommandTextCtrl(void);
	static CCommandTextCtrl* GetInstance(void)
	{
		return m_pCommandTextCtrl;
	}
	void OnExecuteKeywords(int eventID);
	void SetLastUsedCommand();

private:
	void OnKeyDown(wxKeyEvent &event);
	void OnChar(wxKeyEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnSetFocus(wxFocusEvent &event);
	void OnKillFocus(wxFocusEvent &event);
	void OnTextEnter(wxCommandEvent &event);
	void OnMenuKeywords(wxCommandEvent &event);
	void OnMenuExit(wxCommandEvent &event);
	void OnMenuAbout(wxCommandEvent &event);
	void OnMenuCut(wxCommandEvent& WXUNUSED(event));
	void OnMenuCopy(wxCommandEvent& WXUNUSED(event));
	void OnMenuPaste(wxCommandEvent& WXUNUSED(event));
	void OnUpdateMenuCut(wxUpdateUIEvent &event);
	void OnUpdateMenuCopy(wxUpdateUIEvent &event);
	void OnUpdateMenuPaste(wxUpdateUIEvent &event);
	void OnMenuShowHide(wxCommandEvent& WXUNUSED(event));
	void OnMenuSetup(wxCommandEvent& WXUNUSED(event));
	void OnMenuMoveUsingKeyboard(wxCommandEvent& WXUNUSED(event));
	void OnMenuAddKeyword(wxCommandEvent& WXUNUSED(event));
	void OnMenuAddTask(wxCommandEvent& WXUNUSED(event));
	void OnMenuAddContact(wxCommandEvent& WXUNUSED(event));
	void OnTimer(wxTimerEvent &event);
	void OnLeftDown(wxMouseEvent &event);
	void OnRightDown(wxMouseEvent &event);
	void OnClose(wxCloseEvent &event);
	void ShowTime(void);
	void ExecuteCommand(wxString strExecCommand);
	bool SmartProgrammer(wxString strCommand);
	/* This class is used by dynamic_cast, thats why added a dummy virtual function.
	   This should have a small performance penalty, will revisit this section later. */
	virtual void DummyFuncToGenerateVTable(void){}
	bool OnMathematicalEvaluatorHandler(wxString strExp);
	bool OnWindowsExecutionHandler(wxString strExecCommand);
	bool OnContactsHandler(wxString strExecCommand);
	bool OnSendMailHandler(wxString strExecCommand);
	bool OnHttpURLHandler(wxString strExecCommand);
	bool OnFilesAndFolderHandler(wxString strExecCommand);
	bool GetNewValidInputValues();
	void FillValidValuesWithDirContents(wxString strDir);

public:
	enum
	{
		wxID_TIMER = wxID_HIGHEST + 100,
		wxID_MENU_POPUP_EXIT,
		wxID_MENU_POPUP_ABOUT,
		wxID_MENU_POPUP_CUT,
		wxID_MENU_POPUP_COPY,
		wxID_MENU_POPUP_PASTE,
		wxID_MENU_POPUP_SHOW_HIDE,
		wxID_MENU_POPUP_MOVE_USING_KEYBOARD,
		wxID_MENU_POPUP_ADD_KEYWORD,
		wxID_MENU_POPUP_ADD_CONTACT,
		wxID_MENU_POPUP_ADD_TASK,
		wxID_MENU_POPUP_SETUP,
		wxID_MENU_POPUP_KEYWORDS = wxID_HIGHEST + 2000
	};
private:
	std::map<string, string> m_mapSmartProgrammer;
	wxTimer *m_pTimer;
	static CCommandTextCtrl *m_pCommandTextCtrl;
	bool m_bMove;
	wxString m_strLastCommand;
	bool m_bIsFolder;
	wxString m_strLastFolder;

public:
	static const int m_nTimerInterval = 60000;	// 60 thousand milliseconds or 1 minute
	static const int MAX_KEYWORDS = 1000;
	HRESULT CreateLink(LPCWSTR FilePath, LPCWSTR LnkPath, LPCWSTR LnkDesc, LPCWSTR WorkDir);

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
