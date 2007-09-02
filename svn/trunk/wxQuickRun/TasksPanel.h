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
 *	\file TasksPanel.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 24 Jun, 2006
 **/

#pragma once
#include "stdwx.h"
#include <wx/imaglist.h>
#include "checkedlistctrl.h"

class CTasksPanel :	public wxPanel
{
public:
	CTasksPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("Tasks List Panel"));
	virtual ~CTasksPanel(void);

protected:
	void OnClose(wxCloseEvent &event);
	void OnAddTask(wxCommandEvent &event);
	void OnEditTask(wxCommandEvent &event);
	void OnDeleteTask(wxCommandEvent &event);
	void OnImportTask(wxCommandEvent &event);
	void OnExportTask(wxCommandEvent &event);
	void OnCategoryChange(wxCommandEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnManageCategories(wxCommandEvent &event);
	void OnItemChecked(wxListEvent &event);
	void OnItemUnChecked(wxListEvent &event);

	void CreateGUIControls();
	void FillTasksList(wxString strCategory);
	void FillTasksCategory(void);
	void MarkCheckedAsComplete(void);
	wxString SetFontStrikethrough(wxString strFontDesc, bool bStrike = true);
	void ReSizeListCtrl();

private:
	enum
	{
		wxID_LISTCTRL_TASKS = wxID_HIGHEST + 575,
		wxID_BUTTON_TASK_ADD,
		wxID_BUTTON_TASK_EDIT,
		wxID_BUTTON_TASK_DELETE,
		wxID_BUTTON_TASK_IMPORT,
		wxID_BUTTON_TASK_EXPORT,
		wxID_STATIC_TEXT_CATEGORY,
		wxID_COMBOBOX_CATEGORY,
		wxID_BUTTON_CATEGORY
	};

	wxCheckedListCtrl *m_pTasksListCtrl;
	wxButton *m_pButtonAdd;
	wxButton *m_pButtonEdit;
	wxButton *m_pButtonDelete;
	wxButton *m_pButtonImport;
	wxButton *m_pButtonExport;
	wxStaticText *m_pStaticTextCategory;
	wxComboBox *m_pComboCategory;
	wxButton *m_pButtonCategory;

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};
