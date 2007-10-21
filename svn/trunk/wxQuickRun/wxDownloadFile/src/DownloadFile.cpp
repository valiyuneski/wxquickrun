/**********************************************************************
*  File: DownloadFile.cpp
*
*  Purpose: Class for downloading a file from a given URL and send back 
*  event notification to the owner, when the download fails or complete.
*
*  Authors: Priyank Bolia <http://priyank.co.in> 
*
*  Created: 24 December, 2005 
*
*  Modified: 01 May, 2007
*
*  Copyright (C) 2005-2007 by Priyank Bolia. All rights reserved.
*
*  Licence: wxWindows licence
* 
*  http://www.priyank.co.in
*********************************************************************/

#include "DownloadFile.h"
#ifdef  __WXMSW__
	#include <wx/msw/registry.h>
#endif

wxDownloadFile::wxDownloadFile(wxWindow *pParent, wxString strURL, wxString strFile, bool bNotify, wxInt64 nBytes)
: wxThread(wxTHREAD_DETACHED)
, m_pParent(pParent)
, m_strURL(strURL)
, m_strFile(strFile)
, m_bIsDownload(true)
, m_nFileSize(0)
, m_bNotifyDownloading(bNotify)
, m_nNotifyBytes(nBytes)
{
	if ( this->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError(wxT("Can't create download thread!"));
	}
	else
	{
		if ( this->Run() != wxTHREAD_NO_ERROR )
		{
			wxLogError(wxT("Can't start download thread!"));
		}
	}
}

wxDownloadFile::~wxDownloadFile(void)
{
}

void* wxDownloadFile::Entry()
{
    char c = 0;
    int bytesread = 0;
	m_bIsDownload = true;
	wxDownloadEvent event( wxEVT_DOWNLOAD, GetId() );
	event.SetEventObject( (wxObject *)this->This() );
	event.SetDownLoadURL( m_strURL);
	event.SetDownLoadedFile( m_strFile);
	event.SetDownLoadStatus(wxDownloadEvent::DOWNLOAD_RUNNING);
	
	wxURL Url(m_strURL);
	if (Url.GetError() == wxURL_NOERR)
	{
		((wxProtocol &)Url.GetProtocol()).SetTimeout(100);
		wxInputStream *pIn_Stream = NULL;
#ifdef __WXMSW__
		wxRegKey *pRegKey = new wxRegKey(wxT("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"));
		if( pRegKey->Exists() && pRegKey->HasValue(wxT("ProxyEnable")))
		{
			long lProxyEnable;
			pRegKey->QueryValue(wxT("ProxyEnable"), &lProxyEnable);
			if(lProxyEnable == 1 && pRegKey->HasValue(wxT("ProxyServer")))
			{
				wxString strProxyAddress;
				pRegKey->QueryValue(wxT("ProxyServer"), strProxyAddress);
				Url.SetProxy(strProxyAddress);
				pIn_Stream = Url.GetInputStream();
			}
			else
			{
				pIn_Stream = Url.GetInputStream();
			}
		}
		delete pRegKey;
#else
		pIn_Stream = Url.GetInputStream();
#endif
		if(pIn_Stream)
		{
			m_nFileSize = pIn_Stream->GetSize();
			if(m_nFileSize != 0xFFFFFFFF)
				event.SetFileSize(m_nFileSize);
			wxFile file;
			wxInt64 nCount = 0;
			file.Create(m_strFile, true);
			while ((bytesread = (int)(pIn_Stream->Read(&c, 1)).LastRead()) > 0 && m_bIsDownload && !TestDestroy() )
			{
				file.Write((const void *)&c, bytesread);
				nCount += bytesread;
				if (m_bNotifyDownloading && (nCount%m_nNotifyBytes) == 0 && nCount>=m_nNotifyBytes) 
				{
					event.SetDownLoadStatus(wxDownloadEvent::DOWNLOAD_INPROGRESS);
					event.SetDownLoadedBytesCount(nCount);
					m_pParent->GetEventHandler()->AddPendingEvent( event );
				}
			}
			file.Close();
			delete pIn_Stream;
			event.SetDownLoadStatus(wxDownloadEvent::DOWNLOAD_COMPLETE);
			if(m_pParent)
				m_pParent->GetEventHandler()->AddPendingEvent( event );
		}
		else
		{
			event.SetDownLoadStatus(wxDownloadEvent::DOWNLOAD_FAIL);
			if(m_pParent)
				m_pParent->GetEventHandler()->AddPendingEvent( event );
		}
	}
	else
	{
		event.SetDownLoadStatus(wxDownloadEvent::DOWNLOAD_FAIL);
		if(m_pParent)
			m_pParent->GetEventHandler()->AddPendingEvent( event );
	}
	return 0;
}

void wxDownloadFile::OnExit()
{
}

void wxDownloadFile::CancelDownload(void)
{
	m_bIsDownload = false;
	m_pParent = NULL;
}

wxInt64 wxDownloadFile::GetFileSize(void)
{
	return m_nFileSize;
}

void wxDownloadFile::SetDownloadingNotification(bool bEnable, wxInt64 nBytes)
{
	m_bNotifyDownloading = bEnable;
	m_nNotifyBytes = nBytes;
}
