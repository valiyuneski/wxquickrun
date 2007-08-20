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
 *	\file MachineIdentifier.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 26 Sep, 2006
 **/

#include "MachineIdentifier.h"
#include "diskid32.h"
#include "md5.h"

CMachineIdentifier::CMachineIdentifier(void)
{
}

CMachineIdentifier::~CMachineIdentifier(void)
{
}

CMachineIdentifier::CMachineIdentifier(wxString strExeGUID)
: m_strExeGUID(strExeGUID)
{
}

void CMachineIdentifier::SetExeGUID(wxString strID)
{
	m_strExeGUID = strID;
}

wxString CMachineIdentifier::GetExeGUID(void)
{
	return m_strExeGUID;
}

wxString CMachineIdentifier::GetMachineIdentifier(void)
{
	wxString strMachineGUID;
	strMachineGUID = wxString::Format(wxT("%d"), DiskID32::getHardDriveComputerID());
	strMachineGUID = wxString::Format(wxT("%s%s%s.%s"), strMachineGUID.Left(strMachineGUID.Length()/2), m_strExeGUID.Left(m_strExeGUID.Length()/2), strMachineGUID.Right(strMachineGUID.Length()/2), m_strExeGUID.Right(m_strExeGUID.Length()/2));
	return wxMD5::GetMD5(strMachineGUID);
}
