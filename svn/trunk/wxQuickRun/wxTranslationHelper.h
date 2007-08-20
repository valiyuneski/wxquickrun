#ifndef _WX_TRANSLATION_HELPER_H
#define _WX_TRANSLATION_HELPER_H

#include <wx/wx.h>
#include <wx/intl.h>

class wxTranslationHelper
{
	wxApp & m_App;
	wxLocale * m_Locale;
public:
	wxTranslationHelper(wxApp & app);
	~wxTranslationHelper();
	wxLocale * GetLocale();
	void GetInstalledLanguages(wxArrayString & names, wxArrayLong & identifiers);
	bool AskUserForLanguage(wxArrayString & names, wxArrayLong & identifiers, wxWindow *pParent);
	bool Load();
	void Save(bool bReset = false);
};

#endif
