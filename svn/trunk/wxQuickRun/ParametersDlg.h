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
 *	\file CParametersDlg.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 29 March, 2007
 **/

#include "stdwx.h"
#include <wx/dialog.h>
#include <wx/combobox.h>

/*!
* \class CParametersDlg
* \brief 
*/
class CParametersDlg : public wxDialog
{
	DECLARE_DYNAMIC_CLASS(CParametersDlg)

public:
	/*!
	* Default constructor
	*/
	CParametersDlg();

	/*!
	* Constructor
	* Contains parameters and default values as used by the base class constructor
	*/
	CParametersDlg(wxWindow *parent, wxWindowID id=CParametersDlg::wxID_DIALOG_PARAMETERS, const wxString& title = wxT("wxQuickRun"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, const wxString& name = wxT("parameters dialogBox"));

	/*!
	* Virtual destructor
	*/
	virtual ~CParametersDlg();	

private:
	/*!
	* Event handler for EVT_BUTTON
	* \param event object
	* \see wxCommandEvent
	*/
	void OnButtonOK(wxCommandEvent &event);

	/*!
	* Event handler for EVT_INIT_DIALOG
	* \param event object
	* \see wxInitDialogEvent
	*/
	void OnInitDialog(wxInitDialogEvent &event);
	void AddSavedParamsToComboBox(void);
	void SaveParamToDatabase(wxString);
	void RemoveOldestParameter(void);

public:
	wxString GetParameter(void);
	void SetCommandID(int);

private:
	wxComboBox *m_pComboBoxParam; /*!< Displays the previous parameter input and let you select a paramater */
	wxString m_strParameters;
	int m_nCommandID;

public:
	/*!
	* Enum values for the variable's window ID.
	*/
	enum
	{
		wxID_DIALOG_PARAMETERS = wxID_HIGHEST + 2050,
		wxID_COMBOBOX_PARAM /*!< Enum value wxID_COMBOBOX_PARAM corresponding to m_pComboBoxParam */
	};

private:
	DECLARE_EVENT_TABLE()
};
