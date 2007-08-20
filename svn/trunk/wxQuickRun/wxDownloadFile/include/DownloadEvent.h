/**********************************************************************
*  File: DownloadEvent.h
*
*  Purpose: Declaration of the download notification event for the
*  wxDownloadFile class.
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

#pragma once
#include <wx/event.h>

class wxDownloadFile;

class wxDownloadEvent : public wxNotifyEvent
{
public:
	/**
	 * \enum DownloadSTATUS
	 * \brief Download current status.
	 */
	static enum DownloadSTATUS
	{
		DOWNLOAD_NONE = -2,				/// No Status, yet to be initialized
		DOWNLOAD_FAIL = -1,				/// Failed to download the file
		DOWNLOAD_RUNNING = 0,			/// Download is currently running
		DOWNLOAD_COMPLETE = 1,			/// Download has completed
		DOWNLOAD_INPROGRESS = 2			/// Number of bytes downloaded notification.
	};

private:
	DownloadSTATUS m_downloadStatus;	/// download current status value from the DownloadSTATUS enum
	wxString m_strURL;					/// URL from where to download the file
	wxString m_strFILE;					/// local file name where the downloaded file would be saved
	wxInt64 m_nBytesDownloaded;			/// Number of bytes downloaded.
	wxInt64 m_nFileSize;				/// The size of the downloading file.

	friend class wxDownloadFile;

public:
	/**
	 * Constructor
	 * \param commandType Event Type
	 * \param id Unique id for the event handler to distinguish between multiple instances.
	 * \return 
	 */
	wxDownloadEvent(wxEventType commandType = wxEVT_NULL, int id = 0 );

	/**
	 * Copy Constructor
	 * \param event const wxDownloadEvent
	 * \return 
	 */
	wxDownloadEvent(const wxDownloadEvent& event);

	/**
	 * Virtual Destructor
	 * \param void 
	 * \return 
	 */
	virtual ~wxDownloadEvent(void);

public:
    /**
     * Returns an identical copy of itself. Required for sending with wxPostEvent() as references
	 * which must be copied, it does not make sense to have a reference counting scheme to do this cloning,
	 * because all wxDownloadEvent should have separate data.
     * \return 
     */
    virtual wxEvent *Clone() const
		{ return new wxDownloadEvent(*this); }

	/**
	 * Returns the current download status.
	 * \param void 
	 * \return 
	 */
	int GetDownLoadStatus(void);

	/**
	 * Returns the download URL, from where the file has to be downloaded.
	 * \param void 
	 * \return 
	 */
	wxString GetDownLoadURL(void);

	/**
	 * Returns the local file name, of the downloaded file.
	 * \param void 
	 * \return 
	 */
	wxString GetDownLoadedFile(void);

	/**
	 * Returns the number of bytes downloaded.
	 * \param void 
	 * \return Number of bytes downloaded.
	 */
	wxInt64 GetDownLoadedBytesCount(void);

	/**
	 * Returns the size of the downloading file.
	 * \param void 
	 * \return The size of the downloading file.
	 */
	wxInt64 GetFileSize(void);

private:
	/**
	 * Sets the current download status.
	 * \param int DownloadSTATUS enum value
	 */
	void SetDownLoadStatus(int);

	/**
	 * Sets the download URL, from where the file has to be downloaded.
	 * \param wxString Download URL
	 */
	void SetDownLoadURL(wxString);

	/**
	 * Sets the local file name, of the downloaded file.
	 * \param wxString Local file name, where to download the file.
	 */
	void SetDownLoadedFile(wxString);

	/**
	 * Sets the number of bytes downloaded; not to be called by the user.
	 * \param wxInt64 Number of bytes downloaded.
	 */
	void SetDownLoadedBytesCount(wxInt64);

	/**
	 * Sets the size of the downloading file.
	 * \param nSize Size of the downloading file
	 */
	void SetFileSize(wxInt64 nSize);

private:
	/**
	 * The objects of wxDownloadEvent class should be dynamically creatable from run-time type information.
	 */
	DECLARE_DYNAMIC_CLASS(wxDownloadEvent);
};

typedef void (wxEvtHandler::*wxDownloadEventFunction)(wxDownloadEvent&);

/**
 * Declares the event types to be used by the user in their event tables.
 */
BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(wxEVT_DOWNLOAD, wxID_EVENT_DOWNLOAD)
END_DECLARE_EVENT_TYPES()

#define EVT_DOWNLOAD(fn) DECLARE_EVENT_TABLE_ENTRY( \
	wxEVT_DOWNLOAD, wxID_ANY, wxID_ANY, (wxObjectEventFunction) (wxEventFunction) \
	(wxDownloadEventFunction) & fn, (wxObject *) NULL ),
