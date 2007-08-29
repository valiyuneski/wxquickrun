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
 *	\file QuickRunFrame.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include "QuickRunFrame.h"
#include "ReminderDialog.h"
#include "ClipBoardManager.h"
#include "wxQuickRun.h"
#include "NotesPanel.h"
#include "AddTaskDialog.h"
#include "SendKeys.h"
#include "StickyNoteFrame.h"
#include "CommandTextCtrl.h"
#include "SpellCheckDlg.h"
#include "KeysAssignDlg.h"
#include "muParser.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(CQuickRunFrame, wxFrame)
	EVT_CLOSE(CQuickRunFrame::OnClose)
	EVT_PAINT(CQuickRunFrame::OnPaint)
	EVT_ERASE_BACKGROUND(CQuickRunFrame::OnEraseBackground)
	EVT_ENTER_WINDOW(CQuickRunFrame::OnEnterWindow)
	EVT_LEAVE_WINDOW(CQuickRunFrame::OnLeaveWindow)
	EVT_TIMER(wxID_TIMER_REMINDER, CQuickRunFrame::OnReminderTimer)
	EVT_HOTKEY(wxID_HOTKEY_BRING_FOCUS, CQuickRunFrame::OnFocusHotKey)
	EVT_HOTKEY(wxID_HOTKEY_COPY_0, CQuickRunFrame::OnTextCopyHotKey0)
	EVT_HOTKEY(wxID_HOTKEY_COPY_1, CQuickRunFrame::OnTextCopyHotKey1)
	EVT_HOTKEY(wxID_HOTKEY_COPY_2, CQuickRunFrame::OnTextCopyHotKey2)
	EVT_HOTKEY(wxID_HOTKEY_COPY_3, CQuickRunFrame::OnTextCopyHotKey3)
	EVT_HOTKEY(wxID_HOTKEY_COPY_4, CQuickRunFrame::OnTextCopyHotKey4)
	EVT_HOTKEY(wxID_HOTKEY_COPY_5, CQuickRunFrame::OnTextCopyHotKey5)
	EVT_HOTKEY(wxID_HOTKEY_COPY_6, CQuickRunFrame::OnTextCopyHotKey6)
	EVT_HOTKEY(wxID_HOTKEY_COPY_7, CQuickRunFrame::OnTextCopyHotKey7)
	EVT_HOTKEY(wxID_HOTKEY_COPY_8, CQuickRunFrame::OnTextCopyHotKey8)
	EVT_HOTKEY(wxID_HOTKEY_COPY_9, CQuickRunFrame::OnTextCopyHotKey9)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_0, CQuickRunFrame::OnTextPasteHotKey0)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_1, CQuickRunFrame::OnTextPasteHotKey1)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_2, CQuickRunFrame::OnTextPasteHotKey2)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_3, CQuickRunFrame::OnTextPasteHotKey3)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_4, CQuickRunFrame::OnTextPasteHotKey4)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_5, CQuickRunFrame::OnTextPasteHotKey5)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_6, CQuickRunFrame::OnTextPasteHotKey6)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_7, CQuickRunFrame::OnTextPasteHotKey7)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_8, CQuickRunFrame::OnTextPasteHotKey8)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_9, CQuickRunFrame::OnTextPasteHotKey9)
	EVT_HOTKEY(wxID_HOTKEY_ADD_NOTE, CQuickRunFrame::OnAddNoteHotKey)
	EVT_HOTKEY(wxID_HOTKEY_INC_PASTE, CQuickRunFrame::OnIncrementPasteHotKey)
	EVT_HOTKEY(wxID_HOTKEY_DEC_PASTE, CQuickRunFrame::OnDecrementPasteHotKey)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_CYCLIC_FORWARD, CQuickRunFrame::OnPasteCyclicForwardHotKey)
	EVT_HOTKEY(wxID_HOTKEY_PASTE_CYCLIC_BACKWARD, CQuickRunFrame::OnPasteCyclicBackwardHotKey)
	EVT_HOTKEY(wxID_HOTKEY_GLOBAL_MENU, CQuickRunFrame::OnGlobalMenuHotKey)
	EVT_HOTKEY(wxID_HOTKEY_COUNT_CHARS, CQuickRunFrame::OnCountCharsHotKey)
	EVT_HOTKEY(wxID_HOTKEY_UPPERCASE, CQuickRunFrame::OnUpperCaseHotKey)
	EVT_HOTKEY(wxID_HOTKEY_LOWERCASE, CQuickRunFrame::OnLowerCaseHotKey)
	EVT_HOTKEY(wxID_HOTKEY_TOGGLECASE, CQuickRunFrame::OnToggleCaseHotKey)
	EVT_HOTKEY(wxID_HOTKEY_SENTENCECASE, CQuickRunFrame::OnSentenceCaseKey)
	EVT_HOTKEY(wxID_HOTKEY_CHECKSPELL, CQuickRunFrame::OnCheckSpellKey)
	EVT_HOTKEY(wxID_HOTKEY_CALCULATE, CQuickRunFrame::OnCalculateKey)
	EVT_MENU(wxID_MENU_ADD_TASK, CQuickRunFrame::OnAddTaskMenu)
	EVT_MENU(wxID_MENU_ADD_NOTE, CQuickRunFrame::OnAddNoteMenu)
	EVT_MENU(wxID_MENU_ADD_STICKY, CQuickRunFrame::OnAddStickyMenu)
	EVT_MENU_RANGE(wxID_POPUPMENU_COPY_0, wxID_POPUPMENU_COPY_9, CQuickRunFrame::OnCopyMenu)
	EVT_MENU_RANGE(wxID_POPUPMENU_PASTE_0, wxID_POPUPMENU_PASTE_9, CQuickRunFrame::OnPasteMenu)
	EVT_MENU_RANGE(CCommandTextCtrl::wxID_MENU_POPUP_KEYWORDS, CCommandTextCtrl::wxID_MENU_POPUP_KEYWORDS+CCommandTextCtrl::MAX_KEYWORDS, CQuickRunFrame::OnMenuKeywords)
	EVT_MENU_RANGE(wxID_MENU_POPUP_SEARCH, wxID_MENU_POPUP_SEARCH+MAX_SEARCH_ENGINES, CQuickRunFrame::OnMenuSearchEngine)
END_EVENT_TABLE()

CQuickRunFrame::CQuickRunFrame(wxWindow *pParent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
: wxFrame(pParent, id, title, pos, size, style, name)
, m_pTextCtrl(NULL)
, m_pTaskBarIcon(NULL)
, m_bVirtualClipboard(false)
, m_pReminderTimer(NULL)
, m_nTaskReminderID(-1)
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("settings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(255), value VARCHAR(255));"));
		// Center the dialog when first shown
		this->Centre();
		int x = wxSystemSettings::GetMetric(wxSYS_SCREEN_X) - 150;
		int y = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 25 - 30;
		wxSize size(150, 25);
#ifdef  __WXMSW__
		HWND pWndChild = ::FindWindow(wxT("Shell_TrayWnd"), NULL);
		if(pWndChild)
		{
			RECT rect;
			::GetClientRect(pWndChild, &rect);
			y =  wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 25 - rect.bottom;
		}
#endif
		SetSize(x, y, size.GetWidth(), size.GetHeight());
	}
	else
	{
		wxPoint pos;
		wxSize size;
		wxString sqlCmd = wxString::Format(wxT("select * from settings"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			if(result.GetString(0) == wxT("PosX"))
				pos.x = wxAtoi(result.GetString(1));
			else if(result.GetString(0) == wxT("PosY"))
				pos.y = wxAtoi(result.GetString(1));
			else if(result.GetString(0) == wxT("Width"))
				size.SetWidth(wxAtoi(result.GetString(1)));
			else if(result.GetString(0) == wxT("Height"))
				size.SetHeight(wxAtoi(result.GetString(1)));
		}
		result.Finalize();
		SetSize(pos.x, pos.y, size.GetWidth(), size.GetHeight());
	}

	InstallHotKeys();

	CreateGUIControls();
	SetReminderTimer();
}

void CQuickRunFrame::InstallHotKeys()
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("keybindings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE keybindings(key VARCHAR(32), modifier NUMERIC(3,0), virtualKey NUMERIC(2,0));"));
		CKeysAssignDlg::AssignDefaultHotKey();
	}
	// Global hot key for bringing the application to focus.
	RegisterHotKey(wxID_HOTKEY_BRING_FOCUS);

	// Global hot key for adding the text from any application to the Notes.
	RegisterHotKey(wxID_HOTKEY_ADD_NOTE);	//0x4E /*N*/, wxMOD_CONTROL|wxMOD_WIN

	// Global hot key for incrementing the clipboard value and paste to the application.
	RegisterHotKey(wxID_HOTKEY_INC_PASTE); //VK_UP, wxMOD_CONTROL

	// Global hot key for decrementing the clipboard value and paste to the application.
	RegisterHotKey(wxID_HOTKEY_DEC_PASTE);	//VK_DOWN, wxMOD_CONTROL

	// Global hot key for the global menu that work from any application.
	RegisterHotKey(wxID_HOTKEY_GLOBAL_MENU);	//0, wxMOD_CONTROL|wxMOD_WIN|wxMOD_ALT

	// Global hot key for counting the number of characters in the selected text.
	RegisterHotKey(wxID_HOTKEY_COUNT_CHARS);	//0x31, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for converting the selected text to upper case.
	RegisterHotKey(wxID_HOTKEY_UPPERCASE);		//0x32, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for converting the selected text to lower case.
	RegisterHotKey(wxID_HOTKEY_LOWERCASE);		//0x33, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for toggling the case of the selected text.
	RegisterHotKey(wxID_HOTKEY_TOGGLECASE);	//0x34, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for converting the selected text to sentence case.
	RegisterHotKey(wxID_HOTKEY_SENTENCECASE);	//0x35, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for spell checking the selected text.
	RegisterHotKey(wxID_HOTKEY_CHECKSPELL);	//0x36, wxMOD_CONTROL|wxMOD_ALT

	// Global hot key for calculating the value of the selected expression.
	RegisterHotKey(wxID_HOTKEY_CALCULATE);		//0x37, wxMOD_CONTROL|wxMOD_ALT

	wxString sqlCmd = wxString::Format(wxT("SELECT value FROM settings WHERE key = 'VirtualClipboard';"));
	wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
	if(result.NextRow())
	{
		if(result.GetString(0) == wxT("true"))
		{
			// Global hot keys for copying text to advanced virtual clipboard from applications.
			int nKeyCode = 0, nModifier = 0;
			CKeysAssignDlg::GetCommandHotKey(wxT("ClipCopy"), nKeyCode, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_0, 0x30 /*0*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_1, 0x31 /*1*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_2, 0x32 /*2*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_3, 0x33 /*3*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_4, 0x34 /*4*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_5, 0x35 /*5*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_6, 0x36 /*6*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_7, 0x37 /*7*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_8, 0x38 /*8*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_COPY_9, 0x39 /*9*/, nModifier);

			// Global hot keys for pasting the text from advanced virtual clipboard to applications.
			CKeysAssignDlg::GetCommandHotKey(wxT("ClipPaste"), nKeyCode, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_0, 0x30 /*0*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_1, 0x31 /*1*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_2, 0x32 /*2*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_3, 0x33 /*3*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_4, 0x34 /*4*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_5, 0x35 /*5*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_6, 0x36 /*6*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_7, 0x37 /*7*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_8, 0x38 /*8*/, nModifier);
			RegisterHotKeyCommand(wxID_HOTKEY_PASTE_9, 0x39 /*9*/, nModifier);

			m_bVirtualClipboard = true;
		}
	}
	result.Finalize();
}

CQuickRunFrame::~CQuickRunFrame(void)
{
}

void CQuickRunFrame::CreateGUIControls(void)
{
	SetIcon(wxICON(IDI_ICON_APPICON));

	/// Sizer for adding the controls created by users
	wxBoxSizer* pMainSizer = new wxBoxSizer(wxVERTICAL);
	m_pTextCtrl = new CCommandTextCtrl(this, wxID_TEXTCTRL_COMMAND, wxEmptyString, wxPoint(0, 0));
	pMainSizer->Add(m_pTextCtrl, 1, wxEXPAND | wxALIGN_CENTER, 0);
	SetSizer(pMainSizer);
	SetAutoLayout (true);
	Layout();

	m_pTaskBarIcon = new CTaskBarIcon(this);
}

void CQuickRunFrame::OnClose(wxCloseEvent& event)
{
	if(m_bShowTaskBar)
	{
		m_pTaskBarIcon->RemoveIcon();
		m_bShowTaskBar = false;
	}

	if(m_pReminderTimer)
	{
		m_pReminderTimer->Stop();
		delete m_pReminderTimer;
	}

	wxWindow::UnregisterHotKey(wxID_HOTKEY_BRING_FOCUS);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_ADD_NOTE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_INC_PASTE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_DEC_PASTE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_GLOBAL_MENU);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_COUNT_CHARS);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_UPPERCASE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_LOWERCASE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_TOGGLECASE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_SENTENCECASE);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_CHECKSPELL);
	wxWindow::UnregisterHotKey(wxID_HOTKEY_CALCULATE);

	if(m_bVirtualClipboard)
	{
		// Unregistering the global hot keys for copying text from applications to advanced virtual clipboard.
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_0);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_1);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_2);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_3);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_4);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_5);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_6);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_7);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_8);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_9);
		// Unregistering the global hot keys for pasting text from advanced virtual clipboard to applications.
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_0);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_1);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_2);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_3);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_4);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_5);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_6);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_7);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_8);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_9);
	}

	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("settings")))
	{
		dbConn->ExecuteUpdate(wxT("CREATE TABLE settings(key VARCHAR(255), value VARCHAR(255));"));
	}

	wxPoint pos = GetPosition();
	wxSize size = GetSize();

	wxString sqlCmd;
	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'PosX'"));
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("Insert into settings('key', 'value') VALUES('PosX', '%d')"), pos.x);
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'PosY'"));
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("Insert into settings('key', 'value') VALUES('PosY', '%d')"), pos.y);
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'Width'"));
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("Insert into settings('key', 'value') VALUES('Width', '%d')"), size.GetWidth());
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("DELETE FROM settings WHERE key = 'Height'"));
	dbConn->ExecuteUpdate(sqlCmd);
	sqlCmd = wxString::Format(wxT("Insert into settings('key', 'value') VALUES('Height', '%d')"), size.GetHeight());
	dbConn->ExecuteUpdate(sqlCmd);

	delete m_pTaskBarIcon;
	m_pTaskBarIcon = NULL;
	event.Skip();
}

void CQuickRunFrame::OnPaint(wxPaintEvent & event)
{
	///TODO: Remove the below line, for custom drawing.
	event.Skip();
}

void CQuickRunFrame::OnEraseBackground(wxEraseEvent& event)
{
	///TODO: Remove the below line, for custom drawing.
	event.Skip();
}

void CQuickRunFrame::OnEnterWindow(wxMouseEvent &event)
{
	event.Skip(true);
}

void CQuickRunFrame::OnLeaveWindow(wxMouseEvent &event)
{
	event.Skip(true);
}

void CQuickRunFrame::ShowTaskIcon(bool bShow)
{
	if(bShow)
	{
		if(m_pTaskBarIcon)
			m_pTaskBarIcon->SetIcon(wxICON(IDI_ICON_APPICON), wxT("wxQuickRun"));
		m_bShowTaskBar = true;
		Hide();
	}
	else
	{
		if(m_pTaskBarIcon)
			m_pTaskBarIcon->RemoveIcon();
		m_bShowTaskBar = false;
		Show();
#ifdef  __WXMSW__
		BringWindowToTop((HWND)this->GetHWND());
		SetForegroundWindow((HWND)this->GetHWND());
#endif
		m_pTextCtrl->SetFocus();
	}
}

void CQuickRunFrame::OnFocusHotKey(wxKeyEvent &event)
{
	ShowTaskIcon(false);
	event.Skip(false);
}

void CQuickRunFrame::RegisterHotKeyCommand(int hotkeyID, int nKeyCode, int modifiers)
{
	wxWindow::UnregisterHotKey(hotkeyID);
	wxWindow::RegisterHotKey(hotkeyID, modifiers, nKeyCode);
}

void CQuickRunFrame::RegisterHotKey(int hotkeyID)
{
	int nKeyCode = 0, modifiers = 0;
	CKeysAssignDlg::GetCommandHotKey(ConvertHotkeyID2String(hotkeyID), nKeyCode, modifiers);
	CQuickRunFrame::RegisterHotKeyCommand(hotkeyID, nKeyCode, modifiers);
}

void CQuickRunFrame::CopyTextToClipboard(int nIndex)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::GetInstance()->SetStringToVirtualClipBoard(nIndex, CClipBoardManager::ReadFromGlobalClipboard());
}

void CQuickRunFrame::OnTextCopyHotKey0(wxKeyEvent &event)
{
	CopyTextToClipboard(0);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey1(wxKeyEvent &event)
{
	CopyTextToClipboard(1);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey2(wxKeyEvent &event)
{
	CopyTextToClipboard(2);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey3(wxKeyEvent &event)
{
	CopyTextToClipboard(3);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey4(wxKeyEvent &event)
{
	CopyTextToClipboard(4);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey5(wxKeyEvent &event)
{
	CopyTextToClipboard(5);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey6(wxKeyEvent &event)
{
	CopyTextToClipboard(6);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey7(wxKeyEvent &event)
{
	CopyTextToClipboard(7);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey8(wxKeyEvent &event)
{
	CopyTextToClipboard(8);
	event.Skip(false);
}

void CQuickRunFrame::OnTextCopyHotKey9(wxKeyEvent &event)
{
	CopyTextToClipboard(9);
	event.Skip(false);
}

void CQuickRunFrame::PasteTextToApp(int nIndex)
{
	CClipBoardManager::WriteToGlobalClipboard(CClipBoardManager::GetInstance()->GetStringFromVirtualClipBoard(nIndex));
	PasteTextFromClipboardToApp();
}

void CQuickRunFrame::OnTextPasteHotKey0(wxKeyEvent &event)
{
	PasteTextToApp(0);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey1(wxKeyEvent &event)
{
	PasteTextToApp(1);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey2(wxKeyEvent &event)
{
	PasteTextToApp(2);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey3(wxKeyEvent &event)
{
	PasteTextToApp(3);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey4(wxKeyEvent &event)
{
	PasteTextToApp(4);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey5(wxKeyEvent &event)
{
	PasteTextToApp(5);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey6(wxKeyEvent &event)
{
	PasteTextToApp(6);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey7(wxKeyEvent &event)
{
	PasteTextToApp(7);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey8(wxKeyEvent &event)
{
	PasteTextToApp(8);
	event.Skip(false);
}

void CQuickRunFrame::OnTextPasteHotKey9(wxKeyEvent &event)
{
	PasteTextToApp(9);
	event.Skip(false);
}

void CQuickRunFrame::OnAddNoteHotKey(wxKeyEvent &event)
{
	AddSelectedToNote();
	event.Skip(false);
}

void CQuickRunFrame::OnIncrementPasteHotKey(wxKeyEvent& WXUNUSED(event))
{
	wxString strPreviousText = CClipBoardManager::ReadFromGlobalClipboard();
	if(strPreviousText.IsNumber())
	{
		int num = wxAtoi(strPreviousText);
		num++;
		wxString strNextText = wxString::Format(wxT("%d"), num);
		CClipBoardManager::WriteToGlobalClipboard(strNextText);
		PasteTextFromClipboardToApp();
	}
}

void CQuickRunFrame::OnDecrementPasteHotKey(wxKeyEvent& WXUNUSED(event))
{
	wxString strPreviousText = CClipBoardManager::ReadFromGlobalClipboard();
	if(strPreviousText.IsNumber())
	{
		int num = wxAtoi(strPreviousText);
		num--;
		wxString strNextText = wxString::Format(wxT("%d"), num);
		CClipBoardManager::WriteToGlobalClipboard(strNextText);
		PasteTextFromClipboardToApp();
	}
}

void CQuickRunFrame::AddSelectedToNote()
{
	CopyTextToClipboardFromApp();
	CNotesPanel::AddNote(CClipBoardManager::ReadFromGlobalClipboard());
}

void CQuickRunFrame::CopyTextToClipboardFromApp(void)
{
#ifdef __WXMSW__
	wxString strPreviousText = CClipBoardManager::ReadFromGlobalClipboard();
	for(int i=0; i<5 && strPreviousText==CClipBoardManager::ReadFromGlobalClipboard(); i++)
	{
		CSendKeys sendKeys;
		sendKeys.SendKeys(wxT("{DELAY=50}^c"), true);
		wxMilliSleep(500);
	}
#endif
}

void CQuickRunFrame::PasteTextFromClipboardToApp(void)
{
#ifdef __WXMSW__
	CSendKeys sendKeys;
	sendKeys.SendKeys(wxT("{DELAY=50}^v"), true);
#endif
}

void CQuickRunFrame::OnPasteCyclicForwardHotKey(wxKeyEvent &event)
{
	event.Skip(false);
}

void CQuickRunFrame::OnPasteCyclicBackwardHotKey(wxKeyEvent &event)
{
	event.Skip(false);
}

void CQuickRunFrame::EnableVirtualClipboard(bool bEnable)
{
	if(m_bVirtualClipboard == bEnable)
		return;
	else if(bEnable)
	{
		// Global hot keys for copying text to advanced virtual clipboard from applications.
		int nKeyCode = 0, nModifier = 0;
		CKeysAssignDlg::GetCommandHotKey(wxT("ClipCopy"), nKeyCode, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_0, 0x30 /*0*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_1, 0x31 /*1*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_2, 0x32 /*2*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_3, 0x33 /*3*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_4, 0x34 /*4*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_5, 0x35 /*5*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_6, 0x36 /*6*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_7, 0x37 /*7*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_8, 0x38 /*8*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_COPY_9, 0x39 /*9*/, nModifier);

		// Global hot keys for pasting the text from advanced virtual clipboard to applications.
		CKeysAssignDlg::GetCommandHotKey(wxT("ClipPaste"), nKeyCode, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_0, 0x30 /*0*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_1, 0x31 /*1*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_2, 0x32 /*2*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_3, 0x33 /*3*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_4, 0x34 /*4*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_5, 0x35 /*5*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_6, 0x36 /*6*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_7, 0x37 /*7*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_8, 0x38 /*8*/, nModifier);
		RegisterHotKeyCommand(wxID_HOTKEY_PASTE_9, 0x39 /*9*/, nModifier);

		m_bVirtualClipboard = true;
	}
	else
	{
		// Unregistering the global hot keys for copying text from applications to advanced virtual clipboard.
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_0);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_1);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_2);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_3);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_4);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_5);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_6);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_7);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_8);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_COPY_9);

		// Unregistering the global hot keys for pasting text from advanced virtual clipboard to applications.
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_0);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_1);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_2);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_3);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_4);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_5);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_6);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_7);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_8);
		wxWindow::UnregisterHotKey(wxID_HOTKEY_PASTE_9);

		m_bVirtualClipboard = false;
	}
}

void CQuickRunFrame::OnGlobalMenuHotKey(wxKeyEvent& WXUNUSED(event))
{
	wxMenu *pContextMenu  = new wxMenu();
	wxMenu* pKeywords = new wxMenu;
	wxMenu* pSearch = new wxMenu;

	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(dbConn->TableExists(wxT("Commands")))
	{
		wxString sqlCmd = wxString::Format(wxT("select ID, keyword from Commands"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			pKeywords->Append(CCommandTextCtrl::wxID_MENU_POPUP_KEYWORDS+result.GetInt(0), result.GetString(1));
		}
		result.Finalize();
	}
	if(dbConn->TableExists(wxT("searchengines")))
	{
		wxString sqlCmd = wxString::Format(wxT("select ID, name from searchengines"));
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		while(result.NextRow())
		{
			pSearch->Append(wxID_MENU_POPUP_SEARCH+result.GetInt(0), result.GetString(1));
		}
		result.Finalize();
	}

	wxMenu* pCopyMenu = new wxMenu;
	wxMenu* pPasteMenu = new wxMenu;
	for(int nIndex=0; nIndex<10; nIndex++)
	{
		wxString strMenuText = CClipBoardManager::GetInstance()->GetStringFromVirtualClipBoard(nIndex);
		if(strMenuText == wxEmptyString)
			strMenuText = wxString::Format(wxT("-%d-"), nIndex);
		pCopyMenu->Append(wxID_POPUPMENU_COPY_0+nIndex, strMenuText);
		pPasteMenu->Append(wxID_POPUPMENU_PASTE_0+nIndex, strMenuText);
	}

	pContextMenu->Append(wxID_MENU_POPUP_SEARCH, wxT("&Search"), pSearch );
	pContextMenu->AppendSeparator();
	pContextMenu->Append(CCommandTextCtrl::wxID_MENU_POPUP_KEYWORDS, wxT("Key&words"), pKeywords );
	pContextMenu->AppendSeparator();
	pContextMenu->Append(wxID_MENU_POPUP_COPY, wxT("Copy"), pCopyMenu);
	pContextMenu->Append(wxID_MENU_POPUP_PASTE, wxT("Paste"), pPasteMenu);
	pContextMenu->AppendSeparator();
	//pContextMenu->Append(wxID_MENU_ADD_STICKY, wxT("Add &Sticky"));
	pContextMenu->Append(wxID_MENU_ADD_NOTE, wxT("Add &Note"));
	pContextMenu->Append(wxID_MENU_ADD_TASK, wxT("Add &Task"));
	wxMouseState mouse = wxGetMouseState();
	PopupMenu(pContextMenu, mouse.GetX()-GetPosition().x-10, mouse.GetY()-GetPosition().y-10);
	delete pCopyMenu;
	delete pPasteMenu;
	delete pKeywords;
	delete pSearch;
	delete pContextMenu;
}

void CQuickRunFrame::OnAddTaskMenu(wxCommandEvent &event)
{
	CopyTextToClipboardFromApp();
	CAddTaskDialog taskDlg(this);
	taskDlg.SetTaskSubjet(CClipBoardManager::ReadFromGlobalClipboard());
	if(taskDlg.ShowModal()==wxID_OK)
	{
	}
	event.Skip(false);
}

void CQuickRunFrame::OnAddNoteMenu(wxCommandEvent &event)
{
	AddSelectedToNote();
	event.Skip(false);
}

void CQuickRunFrame::OnAddStickyMenu(wxCommandEvent &event)
{
	event.Skip(false);
}

void CQuickRunFrame::OnCopyMenu(wxCommandEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::GetInstance()->SetStringToVirtualClipBoard(event.GetId()-wxID_POPUPMENU_COPY_0, CClipBoardManager::ReadFromGlobalClipboard());
	event.Skip(false);
}

void CQuickRunFrame::OnPasteMenu(wxCommandEvent &event)
{
	CClipBoardManager::WriteToGlobalClipboard(CClipBoardManager::GetInstance()->GetStringFromVirtualClipBoard(event.GetId()-wxID_POPUPMENU_PASTE_0));
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnMenuKeywords(wxCommandEvent &event)
{
	CCommandTextCtrl::GetInstance()->OnExecuteKeywords(event.GetId());
	event.Skip(false);
}

void CQuickRunFrame::OnCountCharsHotKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	wxString strMsg = wxString::Format(wxT("The number of words in the selected string are: %d\n and the number of characters in the selected string are: %d"), CountWords(CClipBoardManager::ReadFromGlobalClipboard()), CClipBoardManager::ReadFromGlobalClipboard().Length());
	wxMessageBox(strMsg, wxT("wxQuickRun"), wxOK|wxCENTER|wxICON_INFORMATION, this);
	event.Skip(false);
}

int CQuickRunFrame::CountWords(wxString str)
{
	bool bInWord = false;
	int nWords = 0;
	for(size_t i=0; i<str.Length(); i++)
	{
		if(isalnum(str[i]))
		{
			if(bInWord == false)
				bInWord = true;
		}
		else if(isspace(str[i]) || ispunct(str[i]))
		{
			if(bInWord == true)
			{
				bInWord = false;
				nWords++;
			}
		}
	}
	if(bInWord == true)
	{
		bInWord = false;
		nWords++;
	}
 	return nWords;
}

wxString CQuickRunFrame::ToggleCase(wxString str)
{
	wxString strToggle;
	for(size_t i=0; i<str.Length(); i++)
	{
		if(isalpha(str[i]))
		{
			if(isupper(str[i]))
				strToggle += tolower(str[i]);
			else
				strToggle += toupper(str[i]);
		}
		else
		{
			strToggle += str[i];
		}
	}
	return strToggle;
}

wxString CQuickRunFrame::SentenceCase(wxString str)
{
	wxString strSentence;
	bool bNewSentence = false;
	for(size_t i=0; i<str.Length(); i++)
	{
		if(isalnum(str[i]))
		{
			if(bNewSentence == false)
			{
				bNewSentence = true;
				strSentence += toupper(str[i]);
			}
			else
				strSentence += str[i];
		}
		else
		{
			if(str[i] == wxT('.') || str[i] == wxT('?') || str[i] == wxT('!'))
			{
				if(bNewSentence == true)
					bNewSentence = false;
			}
			strSentence += str[i];
		}
	}
	return strSentence;
}

void CQuickRunFrame::OnUpperCaseHotKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::WriteToGlobalClipboard(CClipBoardManager::ReadFromGlobalClipboard().Upper());
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnLowerCaseHotKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::WriteToGlobalClipboard(CClipBoardManager::ReadFromGlobalClipboard().Lower());
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnToggleCaseHotKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::WriteToGlobalClipboard(ToggleCase(CClipBoardManager::ReadFromGlobalClipboard()));
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnSentenceCaseKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::WriteToGlobalClipboard(SentenceCase(CClipBoardManager::ReadFromGlobalClipboard()));
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnCheckSpellKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CSpellCheckDlg spChkDlg(this);
	spChkDlg.SetTextToCheck(CClipBoardManager::ReadFromGlobalClipboard());
	if(spChkDlg.ShowModal()==wxID_OK)
		CClipBoardManager::WriteToGlobalClipboard(spChkDlg.GetCorrectedText());
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

void CQuickRunFrame::OnCalculateKey(wxKeyEvent &event)
{
	CopyTextToClipboardFromApp();
	CClipBoardManager::WriteToGlobalClipboard(CalculateExpression(CClipBoardManager::ReadFromGlobalClipboard()));
	PasteTextFromClipboardToApp();
	event.Skip(false);
}

wxString CQuickRunFrame::CalculateExpression(wxString str)
{
	try
	{
		mu::Parser p;
		std::string strExp(str.mb_str());
		p.SetExpr(strExp);
		wxString strResult;
		strResult << p.Eval();
		return strResult;
	}
	catch (mu::Parser::exception_type& WXUNUSED(e))
	{
	}
	return wxEmptyString;
}

void CQuickRunFrame::OnMenuSearchEngine(wxCommandEvent &event)
{
	CopyTextToClipboardFromApp();
	wxString strSearch = CClipBoardManager::ReadFromGlobalClipboard();
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("searchengines")))
	{
		dbConn->ExecuteUpdate(wxT("create table searchengines(ID INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(64), url VARCHAR(255));"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT url FROM searchengines WHERE ID = %d"), event.GetId()-wxID_MENU_POPUP_SEARCH);
		wxSQLite3ResultSet result = dbConn->ExecuteQuery(sqlCmd);
		if(result.NextRow())
		{
			wxString strURL = result.GetString(0);
			strURL.Replace(wxT("{searchTerms}"), strSearch);
			strURL.Replace(wxT(" "), wxT("+"));
			strURL.Replace(wxT("&"), wxT("&amp;"));
			wxLaunchDefaultBrowser(strURL);
		}
		result.Finalize();
	}
	event.Skip(false);
}

void CQuickRunFrame::OnReminderTimer(wxTimerEvent& WXUNUSED(event))
{
	CReminderDialog remDlg(this);
	remDlg.SetTaskID(m_nTaskReminderID);
	if(remDlg.ShowModal()==wxID_OK)
	{
	}
	SetReminderTimer();
}

void CQuickRunFrame::SetReminderTimer()
{
	DBConnPtr dbConn = CDBConnectionMgr::GetDBConnection();
	if(!dbConn->TableExists(wxT("tasks")))
	{
		dbConn->ExecuteUpdate(wxT("create table tasks(ID INTEGER PRIMARY KEY AUTOINCREMENT, subject VARCHAR(255), category VARCHAR(64), status NUMERIC(1,0), priority NUMERIC(1,0), completion NUMERIC(3,0), startTime TIMESTAMP, endTime TIMESTAMP, reminderTime TIMESTAMP, reminder BOOLEAN, description TEXT);"));
	}
	else
	{
		wxString sqlCmd = wxString::Format(wxT("SELECT COUNT(reminderTime) FROM tasks WHERE reminder = 1"));
		if(dbConn->ExecuteScalar(sqlCmd) > 0)
		{
			sqlCmd = wxString::Format(wxT("SELECT ID, MIN(reminderTime) FROM tasks WHERE reminder = 1 AND reminderTime > ?"));
			wxSQLite3Statement stmt = dbConn->PrepareStatement(sqlCmd);
			// Bind the variables to the SQL statement
			stmt.BindTimestamp(1, wxDateTime::Now());
			// Execute the SQL Query			
			wxSQLite3ResultSet result = stmt.ExecuteQuery();
			if(result.NextRow())
			{
				wxDateTime reminderTime = result.GetDateTime(1);
				if(reminderTime.IsValid())
				{
					wxDateTime nowTime = wxDateTime::Now();
					wxTimeSpan timeSpan = reminderTime - nowTime;
					m_nTaskReminderID = result.GetInt(0);
					if(timeSpan.IsPositive())
					{
						if(m_pReminderTimer == NULL)
							m_pReminderTimer = new wxTimer(this, wxID_TIMER_REMINDER);
						m_pReminderTimer->Stop();
						m_pReminderTimer->Start((int)timeSpan.GetSeconds().ToLong()*(int)1000, true);
					}
				}
			}
			result.Finalize();
		}
	}
}

#ifdef  __WXMSW__
WXLRESULT CQuickRunFrame::MSWWindowProc ( WXUINT message, WXWPARAM wParam, WXLPARAM lParam )
{
	return wxFrame::MSWWindowProc ( message, wParam, lParam );
}
#endif

unsigned int CQuickRunFrame::GetHotkeyID(wxString strKeyID)
{
	if(strKeyID == wxT("Focus"))
		return wxID_HOTKEY_BRING_FOCUS;
	else if(strKeyID == wxT("AddNote"))
		return wxID_HOTKEY_ADD_NOTE;
	else if(strKeyID == wxT("PasteFwd"))
		return wxID_HOTKEY_PASTE_CYCLIC_FORWARD;
	else if(strKeyID == wxT("PasteBkwd"))
		return wxID_HOTKEY_PASTE_CYCLIC_BACKWARD;
	else if(strKeyID == wxT("ClipCopy"))
		return wxID_HOTKEY_COPY_0;
	else if(strKeyID == wxT("ClipPaste"))
		return wxID_HOTKEY_PASTE_0;
	else if(strKeyID == wxT("PasteInc"))
		return wxID_HOTKEY_INC_PASTE;
	else if(strKeyID == wxT("PasteDec"))
		return wxID_HOTKEY_DEC_PASTE;
	else if(strKeyID == wxT("GbMenu"))
		return wxID_HOTKEY_GLOBAL_MENU;
	else if(strKeyID == wxT("CountChars"))
		return wxID_HOTKEY_COUNT_CHARS;
	else if(strKeyID == wxT("UpperCase"))
		return wxID_HOTKEY_UPPERCASE;
	else if(strKeyID == wxT("LowerCase"))
		return wxID_HOTKEY_LOWERCASE;
	else if(strKeyID == wxT("ToogleCase"))
		return wxID_HOTKEY_TOGGLECASE;
	else if(strKeyID == wxT("SentenceCase"))
		return wxID_HOTKEY_SENTENCECASE;
	else if(strKeyID == wxT("CheckSpell"))
		return wxID_HOTKEY_CHECKSPELL;
	else if(strKeyID == wxT("Calculation"))
		return wxID_HOTKEY_CALCULATE;
	return 0;
}

wxString CQuickRunFrame::ConvertHotkeyID2String(int nKeyID)
{
	if(nKeyID == wxID_HOTKEY_BRING_FOCUS)
		return wxT("Focus");
	else if(nKeyID == wxID_HOTKEY_ADD_NOTE)
		return wxT("AddNote");
	else if(nKeyID == wxID_HOTKEY_PASTE_CYCLIC_FORWARD)
		return wxT("PasteFwd");
	else if(nKeyID == wxID_HOTKEY_PASTE_CYCLIC_BACKWARD)
		return wxT("PasteBkwd");
	else if(nKeyID == wxID_HOTKEY_COPY_0)
		return wxT("ClipCopy");
	else if(nKeyID ==  wxID_HOTKEY_PASTE_0)
		return wxT("ClipPaste");
	else if(nKeyID == wxID_HOTKEY_INC_PASTE)
		return wxT("PasteInc");
	else if(nKeyID == wxID_HOTKEY_DEC_PASTE)
		return wxT("PasteDec");
	else if(nKeyID == wxID_HOTKEY_GLOBAL_MENU)
		return wxT("GbMenu");
	else if(nKeyID == wxID_HOTKEY_COUNT_CHARS)
		return wxT("CountChars");
	else if(nKeyID == wxID_HOTKEY_UPPERCASE)
		return wxT("UpperCase");
	else if(nKeyID == wxID_HOTKEY_LOWERCASE)
		return wxT("LowerCase");
	else if(nKeyID == wxID_HOTKEY_TOGGLECASE)
		return wxT("ToogleCase");
	else if(nKeyID == wxID_HOTKEY_SENTENCECASE)
		return wxT("SentenceCase");
	else if(nKeyID == wxID_HOTKEY_CHECKSPELL)
		return wxT("CheckSpell");
	else if(nKeyID == wxID_HOTKEY_CALCULATE)
		return wxT("Calculation");
	return wxEmptyString;
}
