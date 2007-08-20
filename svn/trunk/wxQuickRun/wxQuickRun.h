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
 *	\file wxQuickRun.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#pragma once
#include "QuickRunFrame.h"
#include "wxTranslationHelper.h"
#include <wx/snglinst.h>

class wxQuickRunApp : public wxApp
{
private:
	CQuickRunFrame *m_pMainFrame;
	wxSingleInstanceChecker *m_checker;
	wxTranslationHelper * m_TranslationHelper;

private:
	static bool CheckForPaidVerDatabaseFile(void);
	static bool CheckForSoftwarePiracy(void);
	static bool CheckForDatabaseTimeStamp(void);

public:
	wxQuickRunApp(void);
	virtual ~wxQuickRunApp(void);
	bool SelectLanguage(wxWindow *pParent);
	wxString GetSelectedLanguage(void);
	static wxString GetDatabaseFileName(void);
	static wxString GetPaidVerDatabaseFileName(void);
	wxFrame* GetMainFrameWindow(void);

protected:
	virtual bool OnInit();
	virtual int OnExit();

public:
	enum
	{
		wxID_FRAME_MAIN = wxID_HIGHEST + 1000
	};

private:
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(wxQuickRunApp);