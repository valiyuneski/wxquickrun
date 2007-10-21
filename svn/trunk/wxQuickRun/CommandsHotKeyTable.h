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
 *	\file QuickRunFrame.h
 *	\brief 
 *	\author Priyank Bolia
 *  \created 05 Sep, 2007
 **/
#pragma once
#include "stdwx.h"
#include <vector>
#include <boost/tuple/tuple.hpp>

using namespace std;
typedef boost::tuple<int, int> HotKey;

class CCommandsHotKeyTable
{
public:
	CCommandsHotKeyTable(void);
	~CCommandsHotKeyTable(void);
	bool AddRecord(int nCommandID, int nKeyCode, int nModifier);
	bool DeleteRecord(int nCommandID);
	int CountRecords();
	HotKey GetRecord(int nCommandID);
	int GetCommand(int nKeyCode, int nModifier);
	vector<HotKey> GetAllHotkeys();

private:
	bool CheckDBTableExists();
	void CreateDBTable();

private:
	DBConnPtr m_DBConnection;
};
