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
 *	\file wxAutoTextCtrl.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include "wx/wx.h"
#endif

#if wxUSE_TEXTCTRL

/**
 * \brief A text control which automatically predicts the list of possible values,
 * based on the user input, and completes the text.
 * \detail NB: Use up & down arrow keys to see the list of possible values as you
 * keep typing, the valid range of values.
 *
 *
 * \par requirements
 * wxWidgets 2.6.0 or later\n
 *
 * \version 1.0
 * first version
 *
 * \date 01-25-2006
 *
 * \author Priyank Bolia <http://priyank.co.in>
 *
 * \par license wxWindows licence <http://wxwidgets.org/licence3.txt>
 * Copyright 2005 Priyank Bolia. All rights reserved.
 * 
 * \example
 * wxArrayString strArray;
 * strArray.Add("Priya");
 * strArray.Add("Priyank");
 * strArray.Add("Priyanka");
 * strArray.Add("Bolia");
 * wxAutoTextCtrl *pAutoTextCtrl = new wxAutoTextCtrl(this, wxID_ANY, wxEmptyString, strArray);
 *
 * \todo 
 *
 * \bug 
 *
 */
class wxAutoTextCtrl : public wxTextCtrl
{
	DECLARE_DYNAMIC_CLASS(wxAutoTextCtrl)

private:
	wxArrayString m_StrValues;		/// Array of valid user inputs
	bool m_bBeep;					/// Beep on invalid user input
	wxString m_strMessage;			/// Message to be displayed on invalid inputs
	bool m_bShowMsg;				/// Whether to show error message on invalid inputs or not.
	int m_nKeyCode;					/// Key code of the last key pressed.
	int m_nArrayIndex;				/// Index of the text control value in the list of valid values.

public:
	/**
	 * Default Constructor
	 */
	wxAutoTextCtrl(void);

	/**
	 * Constructor
	 * \param parent	Parent window pointer
	 * \param id		Control ID
	 * \param value		Text control value
	 * \param pos		Position of the control
	 * \param size		Size of the control
	 * \param style		Style values for the text control
	 * \param validator	Validator for validating the user input
	 * \param name		Name of the control.
	 */
	wxAutoTextCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("Auto Text Control"));

	/**
	 * Constructor
	 * \param parent		Parent window pointer
	 * \param id			Control ID
	 * \param value			Text control value
	 * \param validValues	Array of the valid user inputs.
	 * \param pos			Position of the control
	 * \param size			Size of the control
	 * \param style			Style values for the text control
	 * \param validator		Validator for validating the user input
	 * \param name			Name of the control.
	 */
	wxAutoTextCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& value = wxEmptyString, const wxArrayString& validValues = NULL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxT("Auto Text Control"));

	/**
	 * Default Destructor.
	 */
	virtual ~wxAutoTextCtrl(void);

	/**
	 * Sets whether to beep or not for invalid user inputs.
	 * \param bBeep boolean value to generate a beep sound on invalid user inputs.
	 */
	void SetBeepOnInvalidValue(bool bBeep = true);

	/**
	 * Gets whether to beep or not for invalid user inputs.
	 * \param void 
	 * \return boolean value indicating whether to generate a beep sound on invalid user inputs or not.
	 */
	bool GetBeepOnInvalidValue(void);

	/**
	 * Sets the invalid user input error message, and whether to display or not.
	 * \detail Return the focus back to the control, when the user had input some
	 * invalid inputs, and the focus from the control has lost.
	 * \param strMsg The invalid input message string.
	 * \param bShow Boolean value indicating whether to show error message or not.
	 */
	void SetInvalidInputMessage(wxString strMsg, bool bShow = true);

	/**
	 * Returns the invalid user input error message.
	 * \return The invalid input message string.
	 */
	wxString GetInvalidInputMessage(void);
	
	/**
	 * Returns whether to show error message or not, for invalid user inputs.
	 * \return Boolean value indicating whether to show error message or not.
	 */
	bool IsShowInvalidInputMessage(void);

	/**
	 * Add the predefined values to the list.
	 * \return The index where the value is added in the string.
	 */
	unsigned int AddValidInputValues(wxString);

protected:
	/**
	 * Event handler for text change event of the text control.
	 * \detail Used for updating/predicting the text control value, based on the user input.
	 * \param &event Text change event
	 */
	void OnTextChange(wxCommandEvent &event);

	/**
	 * Event handler for char input.
	 * \detail Used to handle the backspace and delete char press events.
	 * \param &event 
	 */
	void OnChar(wxKeyEvent &event);

	/**
	 * Event handler for key down.
	 * \detail Used to trap the up & down arrow keys and change the text control values accordingly.
	 * \param &event 
	 */
	void OnKeyDown(wxKeyEvent &event);

	/**
	 * Event handler for loss of focus.
	 * \detail Used to validate the input against the given values and
	 * return the focus to the control back on invalid inputs.
	 * \param &event 
	 */
	void OnKillFocus(wxFocusEvent &event);

private:
	// Any class wishing to process wxWindows events must use this macro
	DECLARE_EVENT_TABLE()
};

#endif
	// wxUSE_TEXTCTRL
