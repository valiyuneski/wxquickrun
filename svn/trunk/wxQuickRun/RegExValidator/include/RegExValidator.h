///////////////////////////////////////////////////////////////////////////////
// Name:		RegExValidator.h
// Purpose:     declaration of regular expression validator class.
// Author:      Priyank Bolia <http://priyank.co.in>
// URL:			http://www.priyank.co.in
// Modified by:
// Created:     29/12/2005
// Copyright:   (c) 2005 Priyank Bolia <http://priyank.co.in>
// Licence:     wxWindows license <http://www.wxwidgets.org/licence3.txt>
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_REGEXVALIDATOR_H
#define _WX_REGEXVALIDATOR_H

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "RegExValidator.h"
#endif

#include "wx/defs.h"

#if wxUSE_VALIDATORS && wxUSE_REGEX && wxUSE_TEXTCTRL 

#include "wx/textctrl.h"
#include "wx/validate.h"
#include "wx/regex.h"

class WXDLLEXPORT wxRegExValidator;

/**
 * \file RegExValidator.h
 * \class wxRegExValidator
 * \brief Regular expression validator
 *
 * \par requirements
 * wxWidgets 2.6.0 or later\n
 *
 * \version 1.0
 * first version
 *
 * \date 12-29-2005
 *
 * \author Priyank Bolia
 *
 * \par license
 * Copyright  2005 Priyank Bolia. All rights reserved. 
 * Distributed under wxWindows license.
 * 
 */
class wxRegExValidator : public wxValidator
{
	DECLARE_DYNAMIC_CLASS(wxRegExValidator)

public:
	wxRegExValidator(wxString regex = wxEmptyString, wxString *valPtr = 0, wxString strErrorMsg = wxT(": is invalid."));
	wxRegExValidator(const wxRegExValidator& val);
	virtual ~wxRegExValidator(void);

public:
	/**
	 *
	 * \return 
	 */
	wxObject* Clone() const { return new wxRegExValidator(*this); }

	/**
	 *
	 * \param val 
	 * \return 
	 */
	bool Copy(const wxRegExValidator& val);

	/**
	 * Called when the value in the window must be validated.
	 * This function can pop up an error message.
	 * \param *parent 
	 * \return 
	 */
	virtual bool Validate(wxWindow *parent);

	/**
	 *
	 * \return 
	 */
	virtual bool TransferToWindow();

	/**
	 *
	 * \param void 
	 * \return 
	 */
	virtual bool TransferFromWindow(void);

	/**
	 * Gets the regular expression
	 * \return 
	 */
	inline wxString GetRegEx() const { return m_strRegEx; }

	/**
	 * Sets the regular expression
	 * \param *regex 
	 */
	inline void SetRegEx(wxString regex) 
	{ 
		if(m_regEx.Compile(regex))
		{
			m_strRegEx = regex;
		}
		else
		{
			m_regEx.Compile(m_strRegEx);
			wxASSERT_MSG(false, wxT("The regular expression provided has a syntax error."));
		}
	}

	/**
	 * Gets the error message
	 * \param void 
	 * \return 
	 */
	inline wxString GetErrorMsg(void) { return m_strErrorMsg; }

	/**
	 * Sets the error message
	 * \param strErrorMsg 
	 */
	inline void SetErrorMsg(wxString strErrorMsg) { m_strErrorMsg = strErrorMsg; } 

protected:
	wxRegEx			m_regEx;
	wxString		m_strRegEx;
	wxString		m_strErrorMsg;
	wxString*		m_stringValue;

	bool CheckValidator() const
	{
		wxCHECK_MSG( m_validatorWindow, false,
			wxT("No window associated with validator") );
		wxCHECK_MSG( m_validatorWindow->IsKindOf(CLASSINFO(wxTextCtrl)), false,
			wxT("wxRegExValidator is only for wxTextCtrl's") );
		wxCHECK_MSG( m_strRegEx, false,
			wxT("No variable storage for validator") );
		return true;
	}

private:
	/**
	 * Assignment operator
	 * Cannot use DECLARE_NO_COPY_CLASS(wxRegExValidator)
	 * because copy constructor is explicitly declared above;
	 * but no copy assignment operator is defined, so declare
	 * it private to prevent the compiler from defining it:
	 * \param wxRegExValidator& 
	 * \return 
	 */
	wxRegExValidator& operator=(const wxRegExValidator&);

public:
	DECLARE_EVENT_TABLE()
};

#endif
	// wxUSE_VALIDATORS && wxUSE_REGEX && wxUSE_TEXTCTRL
#endif
	// _WX_REGEXVALIDATOR_H
