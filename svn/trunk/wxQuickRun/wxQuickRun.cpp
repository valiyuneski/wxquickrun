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
 *	\file wxQuickRun.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#include "wxQuickRun.h"
#include "MachineIdentifier.h"
#include "md5.h"
#include "RegisterDlg.h"
#include <wx/socket.h>
#include <wx/file.h>
#include <wx/msw/registry.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

BEGIN_EVENT_TABLE(wxQuickRunApp, wxApp)
END_EVENT_TABLE()

IMPLEMENT_APP(wxQuickRunApp)

wxQuickRunApp::wxQuickRunApp(void)
: m_pMainFrame(NULL)
, m_checker(NULL)
, m_TranslationHelper(NULL)
{
}

wxQuickRunApp::~wxQuickRunApp(void)
{
	if(m_TranslationHelper)
	{
		wxDELETE(m_TranslationHelper);
	}
	delete m_checker;
	m_checker = NULL;
}

bool wxQuickRunApp::OnInit()
{
	const wxString name = wxString::Format(wxT("wxQuickRun-%s"), wxGetUserId().c_str());
	m_checker = new wxSingleInstanceChecker(name);
	if ( m_checker->IsAnotherRunning() )
	{
		wxLogError(wxT("Another program instance is already running, aborting."));
		return false;
	}

	wxSocketBase::Initialize();
	wxImage::AddHandler(new wxPNGHandler); 
	m_TranslationHelper = new wxTranslationHelper(*this);

	//const bool fail = false;
	//if(CheckForSoftwarePiracy() == fail)
	//{
	//	CRegisterDlg registerDlg(NULL);
	//	if(registerDlg.ShowModal()!=wxID_OK)
	//	{
	//		return false;
	//	}
	//}
	if(GetSelectedLanguage()==wxEmptyString)
		SelectLanguage(NULL);

	// Create the main application window (a dialog in this case)
	// NOTE: Vertical dimension comprises the caption bar.
	//       Horizontal dimension has to take into account the thin
	//       hilighting border around the dialog (2 points in
	//       Win 95).
	m_pMainFrame = new CQuickRunFrame(NULL, wxID_FRAME_MAIN, wxT("wxQuickRun"), wxDefaultPosition, wxSize(150,25));

	// Show it and tell the application that it's our main window
	m_pMainFrame->Show(TRUE);

	SetTopWindow(m_pMainFrame);

	return true;
}

wxFrame* wxQuickRunApp::GetMainFrameWindow(void)
{
	return m_pMainFrame;
}

int wxQuickRunApp::OnExit()
{
	delete m_checker;
	m_checker = NULL;
	return 0;
}

bool wxQuickRunApp::CheckForPaidVerDatabaseFile(void)
{
	return wxFile::Exists(GetPaidVerDatabaseFileName());
}

wxString wxQuickRunApp::GetPaidVerDatabaseFileName(void)
{
	CMachineIdentifier mcID(wxT("A05898E"));
	wxString strDir = wxStandardPaths().GetExecutablePath();
	strDir = strDir.Left(strDir.Find(wxFileName::GetPathSeparator(), true));
	return wxString::Format(wxT("%s%c%s"), strDir, wxFileName::GetPathSeparator(), mcID.GetMachineIdentifier());
}

wxString wxQuickRunApp::GetDatabaseFileName(void)
{
	//if(CheckForPaidVerDatabaseFile())
	//	return GetPaidVerDatabaseFileName();
	wxString strDir = wxStandardPaths().GetExecutablePath();
	strDir = strDir.Left(strDir.Find(wxFileName::GetPathSeparator(), true));
	return wxString::Format(wxT("%s%c%s"), strDir, wxFileName::GetPathSeparator(), wxT("wxQuickRun.db"));
}

bool wxQuickRunApp::SelectLanguage(wxWindow *pParent)
{
	if (m_TranslationHelper)
	{
		wxArrayString names;
		wxArrayLong identifiers;
		m_TranslationHelper->GetInstalledLanguages(names, identifiers);
		return m_TranslationHelper->AskUserForLanguage(names, identifiers, pParent);	
	}
	return false;
}

wxString wxQuickRunApp::GetSelectedLanguage(void)
{
	if (m_TranslationHelper)
	{
		if(m_TranslationHelper->GetLocale())
			return m_TranslationHelper->GetLocale()->GetLanguageName(m_TranslationHelper->GetLocale()->GetLanguage());
	}
	return wxEmptyString;
}

bool wxQuickRunApp::CheckForSoftwarePiracy(void)
{
	if(CheckForPaidVerDatabaseFile())
	{
		return true;
	}
	else
	{
		wxDateTime time = wxDateTime::Now();
		if(time.GetYear() > 2006)
		{
			return false;
		}
		wxString exeName = wxStandardPaths().GetExecutablePath();
		if(!wxFile::Exists(exeName))
			return false;
		wxFileName fileExec(exeName);
		wxDateTime timeMod = fileExec.GetModificationTime();
#ifdef __WXMSW__
		wxRegKey *pRegKey = new wxRegKey(wxT("HKEY_LOCAL_MACHINE\\Software\\Priyank Bolia\\wxQuickRun"));
		// will create the Key if it does not exist
		if( !pRegKey->Exists() )
		{
			if( !pRegKey->Create() )
			{
				pRegKey->Close();
				delete pRegKey;
				return false;
			}
		}
		if(pRegKey->HasValue(wxT("Time")))
		{
			wxDateTime regTime;
			long ulRegTime;
			pRegKey->QueryValue(wxT("Time"), &ulRegTime);
			regTime.SetFromDOS(ulRegTime);
			if(regTime.IsEarlierThan(timeMod) || wxDateTime::Now().IsLaterThan(regTime+wxTimeSpan(24*30,0,0,0)))
			{
				pRegKey->SetValue(wxT("Time"), 0);
				pRegKey->Close();
				delete pRegKey;
				return false;
			}
			else
			{
				pRegKey->Close();
				delete pRegKey;
				return CheckForDatabaseTimeStamp();
			}
		}
		else
		{
			if(pRegKey->SetValue(wxT("Time"), wxDateTime::Now().GetAsDOS()))
			{
				pRegKey->Close();
				delete pRegKey;
				return CheckForDatabaseTimeStamp();
			}
		}
		pRegKey->Close();
		delete pRegKey;
#endif
	}
	return false;
}

bool wxQuickRunApp::CheckForDatabaseTimeStamp(void)
{
	if(wxFile::Exists(GetDatabaseFileName()))
	{
		wxDateTime t1, t2, t3;
		wxFileName dateBase(GetDatabaseFileName());
		dateBase.GetTimes(&t1, &t2, &t3);
		if(t3.IsEarlierThan(wxDateTime::Now()-wxTimeSpan(24*30)))
			return false;
	}
	return true;
}