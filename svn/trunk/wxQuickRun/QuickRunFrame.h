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
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/dcbuffer.h>
#include "CommandTextCtrl.h"
#include "TaskBarIcon.h"

class CQuickRunFrame : public wxFrame
{
public:
	CQuickRunFrame(wxWindow *pParent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style = wxRESIZE_BORDER | wxCLIP_CHILDREN | wxSTAY_ON_TOP | wxFRAME_NO_TASKBAR | wxNO_BORDER | wxWANTS_CHARS, const wxString& name = wxT("Main Frame"));
	virtual ~CQuickRunFrame(void);
	void ShowTaskIcon(bool bShow);
	void RegisterHotKeyCommand(int hotkeyID, int nKeyCode, int modifiers);
	void RegisterHotKey(int hotkeyID);
	void InstallHotKeys();
	void DeInstallHotKeys();
	void EnableVirtualClipboard(bool bEnable);
	void SetReminderTimer();

private:
	void OnClose(wxCloseEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnEnterWindow(wxMouseEvent &event);
	void OnLeaveWindow(wxMouseEvent &event);
	void OnFocusHotKey(wxKeyEvent &event);
	void OnTextCopyHotKey0(wxKeyEvent &event);
	void OnTextCopyHotKey1(wxKeyEvent &event);
	void OnTextCopyHotKey2(wxKeyEvent &event);
	void OnTextCopyHotKey3(wxKeyEvent &event);
	void OnTextCopyHotKey4(wxKeyEvent &event);
	void OnTextCopyHotKey5(wxKeyEvent &event);
	void OnTextCopyHotKey6(wxKeyEvent &event);
	void OnTextCopyHotKey7(wxKeyEvent &event);
	void OnTextCopyHotKey8(wxKeyEvent &event);
	void OnTextCopyHotKey9(wxKeyEvent &event);
	void OnTextPasteHotKey0(wxKeyEvent &event);
	void OnTextPasteHotKey1(wxKeyEvent &event);
	void OnTextPasteHotKey2(wxKeyEvent &event);
	void OnTextPasteHotKey3(wxKeyEvent &event);
	void OnTextPasteHotKey4(wxKeyEvent &event);
	void OnTextPasteHotKey5(wxKeyEvent &event);
	void OnTextPasteHotKey6(wxKeyEvent &event);
	void OnTextPasteHotKey7(wxKeyEvent &event);
	void OnTextPasteHotKey8(wxKeyEvent &event);
	void OnTextPasteHotKey9(wxKeyEvent &event);
	void OnAddNoteHotKey(wxKeyEvent &event);
	void OnIncrementPasteHotKey(wxKeyEvent &event);
	void OnDecrementPasteHotKey(wxKeyEvent &event);
	void OnPasteCyclicForwardHotKey(wxKeyEvent &event);
	void OnPasteCyclicBackwardHotKey(wxKeyEvent &event);
	void OnGlobalMenuHotKey(wxKeyEvent &event);
	void OnAddTaskMenu(wxCommandEvent &event);
	void OnAddNoteMenu(wxCommandEvent &event);
	void OnAddStickyMenu(wxCommandEvent &event);
	void OnSearchMenu(wxCommandEvent &event);
	void OnCopyMenu(wxCommandEvent &event);
	void OnPasteMenu(wxCommandEvent &event);
	void OnMenuKeywords(wxCommandEvent &event);
	void OnMenuSearchEngine(wxCommandEvent &event);
	void OnCountCharsHotKey(wxKeyEvent &event);
	void OnUpperCaseHotKey(wxKeyEvent &event);
	void OnLowerCaseHotKey(wxKeyEvent &event);
	void OnToggleCaseHotKey(wxKeyEvent &event);
	void OnSentenceCaseKey(wxKeyEvent &event);
	void OnCheckSpellKey(wxKeyEvent &event);
	void OnCalculateKey(wxKeyEvent &event);
	void OnReminderTimer(wxTimerEvent &event);

private:
	void CreateGUIControls(void);
	void CopyTextToClipboardFromApp(void);
	void PasteTextFromClipboardToApp(void);
	void AddSelectedToNote();
	int CountWords(wxString str);
	wxString ToggleCase(wxString str);
	wxString SentenceCase(wxString str);
	wxString CalculateExpression(wxString str);
	unsigned int GetHotkeyID(wxString strKeyID);
	wxString ConvertHotkeyID2String(int nKeyID);
	void CopyTextToClipboard(int nIndex);
	void PasteTextToApp(int nIndex);

#ifdef __WXMSW__
private:
	WXLRESULT MSWWindowProc ( WXUINT message, WXWPARAM wParam, WXLPARAM lParam );
#endif

public:
	enum 
	{
		wxID_TEXTCTRL_COMMAND = wxID_HIGHEST + 1,
		wxID_HOTKEY_BRING_FOCUS = 0xA0C9,
		wxID_HOTKEY_COPY_0,
		wxID_HOTKEY_COPY_1,
		wxID_HOTKEY_COPY_2,
		wxID_HOTKEY_COPY_3,
		wxID_HOTKEY_COPY_4,
		wxID_HOTKEY_COPY_5,
		wxID_HOTKEY_COPY_6,
		wxID_HOTKEY_COPY_7,
		wxID_HOTKEY_COPY_8,
		wxID_HOTKEY_COPY_9,
		wxID_HOTKEY_PASTE_0,
		wxID_HOTKEY_PASTE_1,
		wxID_HOTKEY_PASTE_2,
		wxID_HOTKEY_PASTE_3,
		wxID_HOTKEY_PASTE_4,
		wxID_HOTKEY_PASTE_5,
		wxID_HOTKEY_PASTE_6,
		wxID_HOTKEY_PASTE_7,
		wxID_HOTKEY_PASTE_8,
		wxID_HOTKEY_PASTE_9,
		wxID_HOTKEY_ADD_NOTE,
		wxID_HOTKEY_INC_PASTE,
		wxID_HOTKEY_DEC_PASTE,
		wxID_HOTKEY_PASTE_CYCLIC_FORWARD,
		wxID_HOTKEY_PASTE_CYCLIC_BACKWARD,
		wxID_HOTKEY_GLOBAL_MENU,
		wxID_HOTKEY_COUNT_CHARS,
		wxID_HOTKEY_UPPERCASE,
		wxID_HOTKEY_LOWERCASE,
		wxID_HOTKEY_TOGGLECASE,
		wxID_HOTKEY_SENTENCECASE,
		wxID_HOTKEY_CHECKSPELL,
		wxID_HOTKEY_CALCULATE,
		wxID_MENU_ADD_NOTE,
		wxID_MENU_ADD_STICKY,
		wxID_MENU_ADD_TASK,
		wxID_POPUPMENU_COPY_0,
		wxID_POPUPMENU_COPY_1,
		wxID_POPUPMENU_COPY_2,
		wxID_POPUPMENU_COPY_3,
		wxID_POPUPMENU_COPY_4,
		wxID_POPUPMENU_COPY_5,
		wxID_POPUPMENU_COPY_6,
		wxID_POPUPMENU_COPY_7,
		wxID_POPUPMENU_COPY_8,
		wxID_POPUPMENU_COPY_9,
		wxID_POPUPMENU_PASTE_0,
		wxID_POPUPMENU_PASTE_1,
		wxID_POPUPMENU_PASTE_2,
		wxID_POPUPMENU_PASTE_3,
		wxID_POPUPMENU_PASTE_4,
		wxID_POPUPMENU_PASTE_5,
		wxID_POPUPMENU_PASTE_6,
		wxID_POPUPMENU_PASTE_7,
		wxID_POPUPMENU_PASTE_8,
		wxID_POPUPMENU_PASTE_9,
		wxID_MENU_POPUP_COPY,
		wxID_MENU_POPUP_PASTE,
		wxID_TIMER_REMINDER,
		wxID_MENU_POPUP_SEARCH = wxID_HIGHEST + 3000
	};
private:
	CCommandTextCtrl *m_pTextCtrl;
	CTaskBarIcon *m_pTaskBarIcon;
	bool m_bShowTaskBar;
	bool m_bVirtualClipboard;
	wxTimer *m_pReminderTimer;
	int m_nTaskReminderID;

public:
	static const int MAX_SEARCH_ENGINES = 25;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
