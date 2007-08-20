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
 *	\file KeywordsListPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 23 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/listctrl.h>

class CKeywordsListPanel : public wxPanel
{
public:
	CKeywordsListPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Keywords List Panel"));
	virtual ~CKeywordsListPanel(void);

private:
	void OnClose(wxCloseEvent &event);
	void OnAddKeyword(wxCommandEvent &event);
	void OnEditKeyword(wxCommandEvent &event);
	void OnDeleteKeyword(wxCommandEvent &event);
	void OnImportKeyword(wxCommandEvent &event);
	void OnExportKeyword(wxCommandEvent &event);
	void CreateGUIControls();
	void FillKeywordsList();

private:
	enum
	{
		wxID_LISTCTRL_KEYWORDS = wxID_HIGHEST + 475,
		wxID_BUTTON_KEYWORD_ADD,
		wxID_BUTTON_KEYWORD_EDIT,
		wxID_BUTTON_KEYWORD_DELETE,
		wxID_BUTTON_KEYWORD_IMPORT,
		wxID_BUTTON_KEYWORD_EXPORT
	};
	wxListCtrl *m_pKeywordsListCtrl;
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonEdit;
	wxButton *m_pButtonDelete;
	wxButton *m_pButtonImport;
	wxButton *m_pButtonExport;
	wxImageList m_imageList;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
