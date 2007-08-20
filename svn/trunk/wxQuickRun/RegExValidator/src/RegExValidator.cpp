///////////////////////////////////////////////////////////////////////////////
// Name:		RegExValidator.h
// Purpose:     implementation of regular expression validator class.
// Author:      Priyank Bolia <http://priyank.co.in>
// URL:			http://www.priyank.co.in
// Modified by:
// Created:     29/12/2005
// Copyright:   (c) 2005 Priyank Bolia <http://priyank.co.in>
// Licence:     wxWindows licence <http://www.wxwidgets.org/licence3.txt>
///////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "RegExValidator.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if wxUSE_VALIDATORS && wxUSE_REGEX && wxUSE_TEXTCTRL 

#ifndef WX_PRECOMP
	#include <stdio.h>
	#include "wx/textctrl.h"
	#include "wx/msgdlg.h"
#endif

#include "regexvalidator.h"

#include <string.h>

IMPLEMENT_DYNAMIC_CLASS(wxRegExValidator, wxValidator)

BEGIN_EVENT_TABLE(wxRegExValidator, wxValidator)
END_EVENT_TABLE()

wxRegExValidator::wxRegExValidator(wxString regex, wxString *valPtr, wxString strErrorMsg)
: m_stringValue(valPtr)
, m_strErrorMsg(strErrorMsg)
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

wxRegExValidator::wxRegExValidator(const wxRegExValidator& val)
: wxValidator()
{
	Copy(val);
}

wxRegExValidator::~wxRegExValidator(void)
{
}

bool wxRegExValidator::Copy(const wxRegExValidator& val)
{
	wxValidator::Copy(val);

	if(m_regEx.Compile(val.m_strRegEx))
	{
		m_strRegEx = val.m_strRegEx;
	}
	else
	{
		m_regEx.Compile(m_strRegEx);
		wxASSERT_MSG(false, wxT("The regular expression provided has a syntax error."));
	}
	m_stringValue = val.m_stringValue;
	m_strErrorMsg = val.m_strErrorMsg;

	return true;
}

bool wxRegExValidator::Validate(wxWindow *parent)
{
	if( !CheckValidator() )
		return false;

	wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;

	// If window is disabled, simply return
	if ( !control->IsEnabled() )
		return true;

	if(!m_regEx.IsValid())
	{
		wxMessageBox(wxT("The regular expression provided has a syntax error."), wxT("Invalid expression"),
			wxOK | wxICON_ERROR, parent);
		return false;
	}

	wxString val(control->GetValue());

	bool bMatch = false;
	if ( m_regEx.Matches(val) )
	{
		if ( m_regEx.GetMatch(val) == val )
		{
			bMatch = true;
		}
	}

	if (!bMatch) 
	{
		wxASSERT_MSG( !m_strErrorMsg.empty(), wxT("you forgot to set errormsg") );

		m_validatorWindow->SetFocus();

		wxString buf = wxString::Format(wxT("'%s'%s"), val.c_str(), m_strErrorMsg);

		wxMessageBox(buf, wxT("Validation conflict"),
			wxOK | wxICON_EXCLAMATION, parent);
	}

	return bMatch;
}

bool wxRegExValidator::TransferToWindow()
{
	if( !CheckValidator() )
		return false;

	if ( m_stringValue )
	{
		wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
		control->SetValue(* m_stringValue);
	}

	return true;
}

bool wxRegExValidator::TransferFromWindow(void)
{
	if( !CheckValidator() )
		return false;

	if ( m_stringValue )
	{
		wxTextCtrl *control = (wxTextCtrl *) m_validatorWindow;
		*m_stringValue = control->GetValue();
	}

	return true;
}

#endif
	// wxUSE_VALIDATORS && wxUSE_REGEX && wxUSE_TEXTCTRL
