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
 *	\file stdwx.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 22 Jun, 2006
 **/

#ifndef _stdwx_h_
#define _stdwx_h_

// SYSTEM INCLUDES
#include <wx/wxprec.h>
#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// APPLICATION INCLUDES
#include <wx/image.h>
#include "wx/wxsqlite3.h"

#ifdef __VISUALC__
#ifdef __WXDEBUG__
#include <crtdbg.h>
#undef WXDEBUG_NEW
#define WXDEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#undef WXDEBUG_NEW
#define WXDEBUG_NEW new
#endif
#endif

#if defined(__VISUALC__) && __VISUALC__ >= 1400
// Comment these lines below, if you don't want to enable WinXP Style theme.
#if defined(__WXMSW__) && !defined(__WXWINCE__)
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df'\"")
#endif
#endif

#define DATABASE_FILE wxGetApp().GetDatabaseFileName()

char* wxStringToChar(wxString input);  

#endif
