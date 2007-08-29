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
 *	\file KeyInputCtrl.cpp
 *	\brief 
 *	\author Priyank Bolia
 *  \created 19 August, 2007
 **/

#include "KeyInputCtrl.h"

#ifdef __WXDEBUG__
#define new WXDEBUG_NEW
#endif

IMPLEMENT_DYNAMIC_CLASS(CKeyInputCtrl, wxTextCtrl)

BEGIN_EVENT_TABLE(CKeyInputCtrl, wxTextCtrl)
	EVT_KEY_DOWN(CKeyInputCtrl::OnKeyDown)
	EVT_CHAR(CKeyInputCtrl::OnChar)
END_EVENT_TABLE()

CKeyInputCtrl::CKeyInputCtrl()
: wxTextCtrl(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize)
{
}

CKeyInputCtrl::CKeyInputCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name)
: wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{
}

CKeyInputCtrl::~CKeyInputCtrl(void)
{
}

void CKeyInputCtrl::OnKeyDown(wxKeyEvent &event)
{
	int nKeyCode = event.GetKeyCode();
	SetValue(GetKeyCodeAsString(nKeyCode));
	event.Skip(true);
}

void CKeyInputCtrl::OnChar(wxKeyEvent &event)
{
	event.Skip(false);
}

int CKeyInputCtrl::GetKeyCode()
{
	return GetKeyCode(GetValue());
}

void CKeyInputCtrl::SetKeyCode(int nKeyCode)
{
	SetValue(GetKeyCodeAsString(nKeyCode));
}

int CKeyInputCtrl::GetKeyCode(wxString ch)
{
	if(ch == wxEmptyString)
		return 0;
	if(ch == wxT("Home"))
		return WXK_HOME;
	else if(ch == wxT("End"))
		return WXK_END;
	else if(ch == wxT("Insert"))
		return WXK_INSERT;
	else if(ch == wxT("Print Screen"))
		return WXK_SNAPSHOT;
	else if(ch == wxT("Tab"))
		return WXK_TAB;
	else if(ch == wxT("Scroll Lock"))
		return WXK_SCROLL;
	else if(ch == wxT("Esc"))
		return WXK_ESCAPE;
	else if(ch == wxT("Page Up"))
		return WXK_PAGEUP;
	else if(ch == wxT("Page Down"))
		return WXK_PAGEDOWN;
	else if(ch == wxT("F1"))
		return WXK_F1;
	else if(ch == wxT("F2"))
		return WXK_F2;
	else if(ch == wxT("F3"))
		return WXK_F3;
	else if(ch == wxT("F4"))
		return WXK_F4;
	else if(ch == wxT("F5"))
		return WXK_F5;
	else if(ch == wxT("F6"))
		return WXK_F6;
	else if(ch == wxT("F7"))
		return WXK_F7;
	else if(ch == wxT("F8"))
		return WXK_F8;
	else if(ch == wxT("F9"))
		return WXK_F9;
	else if(ch == wxT("F10"))
		return WXK_F10;
	else if(ch == wxT("F11"))
		return WXK_F11;
	else if(ch == wxT("F12"))
		return WXK_F12;
	else if(ch == wxT("F13"))
		return WXK_F13;
	else if(ch == wxT("F14"))
		return WXK_F14;
	else if(ch == wxT("F15"))
		return WXK_F15;
	else if(ch == wxT("Up Arrow"))
		return VK_UP;
	else if(ch == wxT("Down Arrow"))
		return VK_DOWN;
	else if(ch == wxT("Left Arrow"))
		return VK_LEFT;
	else if(ch == wxT("Right Arrow"))
		return VK_RIGHT;
	else if(ch == wxT("Backspace"))
		return WXK_BACK;
	else if(ch == wxT("Numpad Multiply"))
		return WXK_NUMPAD_MULTIPLY;
	else if(ch == wxT("Numpad Divide"))
		return WXK_NUMPAD_DIVIDE;
	else if(ch == wxT("Numpad Decimal"))
		return WXK_NUMPAD_DECIMAL;
	else if(ch == wxT("Numpad Subtract"))
		return WXK_NUMPAD_SUBTRACT;
	else if(ch == wxT("Numpad Separator"))
		return WXK_NUMPAD_SEPARATOR;
	else if(ch == wxT("Numpad Add"))
		return WXK_NUMPAD_ADD;
	else if(ch == wxT("Numpad Begin"))
		return WXK_NUMPAD_BEGIN;
	else if(ch == wxT("Numpad End"))
		return WXK_NUMPAD_END;
	else if(ch == wxT("Numpad Page Up"))
		return WXK_NUMPAD_PAGEUP;
	else if(ch == wxT("Numpad Page Down"))
		return WXK_NUMPAD_PAGEDOWN;
	else if(ch == wxT("Numpad Home"))
		return WXK_NUMPAD_HOME;
	else if(ch == wxT("Numpad Add"))
		return WXK_NUMPAD_LEFT;
	else if(ch == wxT("Numpad Right"))
		return WXK_NUMPAD_RIGHT;
	else if(ch == wxT("Numpad Up"))
		return WXK_NUMPAD_UP;
	else if(ch == wxT("Numpad Down"))
		return WXK_NUMPAD_DOWN;
	else if(ch == wxT("Numpad Insert"))
		return WXK_NUMPAD_INSERT;
	else if(ch == wxT("Numpad Delete"))
		return WXK_NUMPAD_DELETE;
	else if(ch == wxT("Numpad Equal"))
		return WXK_NUMPAD_EQUAL;
	else if(ch == wxT("Numpad 0"))
		return WXK_NUMPAD0;
	else if(ch == wxT("Numpad 1"))
		return WXK_NUMPAD1;
	else if(ch == wxT("Numpad 2"))
		return WXK_NUMPAD2;
	else if(ch == wxT("Numpad 3"))
		return WXK_NUMPAD3;
	else if(ch == wxT("Numpad 4"))
		return WXK_NUMPAD4;
	else if(ch == wxT("Numpad 5"))
		return WXK_NUMPAD5;
	else if(ch == wxT("Numpad 6"))
		return WXK_NUMPAD6;
	else if(ch == wxT("Numpad 7"))
		return WXK_NUMPAD7;
	else if(ch == wxT("Numpad 8"))
		return WXK_NUMPAD8;
	else if(ch == wxT("Numpad 9"))
		return WXK_NUMPAD9;
	else if(ch == wxT("DEL"))
		return WXK_DELETE;
	else if(ch == wxT("Space"))
		return WXK_SPACE;
	switch(ch[0])
	{
#ifdef  __WXMSW__
	case wxT('0'):
		return 0x30;
		break;
	case wxT('1'):
		return 0x31;
		break;
	case wxT('2'):
		return 0x32;
		break;
	case wxT('3'):
		return 0x33;
		break;
	case wxT('4'):
		return 0x34;
		break;
	case wxT('5'):
		return 0x35;
		break;
	case wxT('6'):
		return 0x36;
		break;
	case wxT('7'):
		return 0x37;
		break;
	case wxT('8'):
		return 0x38;
		break;
	case wxT('9'):
		return 0x39;
		break;
	case wxT('a'):
	case wxT('A'):
		return 0x41;
		break;
	case wxT('b'):
	case wxT('B'):
		return 0x42;
		break;
	case wxT('c'):
	case wxT('C'):
		return 0x43;
		break;
	case wxT('d'):
	case wxT('D'):
		return 0x44;
		break;
	case wxT('e'):
	case wxT('E'):
		return 0x45;
		break;
	case wxT('f'):
	case wxT('F'):
		return 0x46;
		break;
	case wxT('g'):
	case wxT('G'):
		return 0x47;
		break;
	case wxT('h'):
	case wxT('H'):
		return 0x48;
		break;
	case wxT('i'):
	case wxT('I'):
		return 0x49;
		break;
	case wxT('j'):
	case wxT('J'):
		return 0x4A;
		break;
	case wxT('k'):
	case wxT('K'):
		return 0x4B;
		break;
	case wxT('l'):
	case wxT('L'):
		return 0x4C;
		break;
	case wxT('m'):
	case wxT('M'):
		return 0x4D;
		break;
	case wxT('n'):
	case wxT('N'):
		return 0x4E;
		break;
	case wxT('o'):
	case wxT('O'):
		return 0x4F;
		break;
	case wxT('p'):
	case wxT('P'):
		return 0x50;
		break;
	case wxT('q'):
	case wxT('Q'):
		return 0x51;
		break;
	case wxT('r'):
	case wxT('R'):
		return 0x52;
		break;
	case wxT('s'):
	case wxT('S'):
		return 0x53;
		break;
	case wxT('t'):
	case wxT('T'):
		return 0x54;
		break;
	case wxT('u'):
	case wxT('U'):
		return 0x55;
		break;
	case wxT('v'):
	case wxT('V'):
		return 0x56;
		break;
	case wxT('w'):
	case wxT('W'):
		return 0x57;
		break;
	case wxT('x'):
	case wxT('X'):
		return 0x58;
		break;
	case wxT('y'):
	case wxT('Y'):
		return 0x59;
		break;
	case wxT('z'):
	case wxT('Z'):
		return 0x5A;
		break;
	case wxT('*'):
		return VK_MULTIPLY;
		break;
	case wxT('+'):
		return VK_ADD;
		break;
	case wxT('-'):
		return VK_SUBTRACT;
		break;
	case wxT('.'):
	case wxT('>'):
		return VK_DECIMAL;
		break;
	case wxT(','):
	case wxT('<'):
		return VK_OEM_COMMA;
		break;
	case wxT(';'):
	case wxT(':'):
		return VK_OEM_1;
		break;
	case wxT('/'):
	case wxT('?'):
		return VK_OEM_2;
		break;
	case wxT('`'):
	case wxT('~'):
		return VK_OEM_3;
		break;
	case wxT('['):
	case wxT('{'):
		return VK_OEM_4;
		break;
	case wxT('\\'):
	case wxT('|'):
		return VK_OEM_5;
		break;
	case wxT(']'):
	case wxT('}'):
		return VK_OEM_6;
		break;
	case wxT('\''):
	case wxT('\"'):
		return VK_OEM_7;
		break;
#endif
	default:
		return 0;
	}
}

wxString CKeyInputCtrl::GetKeyCodeAsString(int nKeyCode)
{
	//if(nKeyCode >= 33 && nKeyCode <= 126)
	//{
	//	wxString strKeyCode = wxT("0");
	//	strKeyCode[0] = nKeyCode;
	//	return strKeyCode;
	//}
	switch(nKeyCode)
	{
#ifdef  __WXMSW__
	case WXK_HOME:
		return wxT("Home");
		break;
	case WXK_END:
		return wxT("End");
		break;
	case WXK_INSERT:
		return wxT("Insert");
		break;		
	case WXK_SNAPSHOT:
		return wxT("Print Screen");
		break;
	case WXK_TAB:
		return wxT("Tab");
		break;
	case WXK_SCROLL:
		return wxT("Scroll Lock");
		break;
	case WXK_ESCAPE:
		return wxT("Esc");
		break;
	case WXK_PAGEUP:
		return wxT("Page Up");
		break;
	case WXK_PAGEDOWN:
		return wxT("Page Down");
		break;
	case WXK_F1:
		return wxT("F1");
		break;
	case WXK_F2:
		return wxT("F2");
		break;
	case WXK_F3:
		return wxT("F3");
		break;
	case WXK_F4:
		return wxT("F4");
		break;
	case WXK_F5:
		return wxT("F5");
		break;
	case WXK_F6:
		return wxT("F6");
		break;
	case WXK_F7:
		return wxT("F7");
		break;
	case WXK_F8:
		return wxT("F8");
		break;
	case WXK_F9:
		return wxT("F9");
		break;
	case WXK_F10:
		return wxT("F10");
		break;
	case WXK_F11:
		return wxT("F11");
		break;
	case WXK_F12:
		return wxT("F12");
		break;
	case WXK_F13:
		return wxT("F13");
		break;
	case WXK_F14:
		return wxT("F14");
		break;
	case WXK_F15:
		return wxT("F15");
		break;
	case WXK_UP:
	case VK_UP:
		return wxT("Up Arrow");
		break;
	case WXK_DOWN:
	case VK_DOWN:
		return wxT("Down Arrow");
		break;
	case WXK_LEFT:
	case VK_LEFT:
		return wxT("Left Arrow");
		break;
	case WXK_RIGHT:
	case VK_RIGHT:
		return wxT("Right Arrow");
		break;
	case WXK_BACK:
		return wxT("Backspace");
		break;
	case WXK_NUMPAD0:
		return wxT("Numpad 0");
		break;
	case WXK_NUMPAD1:
		return wxT("Numpad 1");
		break;
	case WXK_NUMPAD2:
		return wxT("Numpad 2");
		break;
	case WXK_NUMPAD3:
		return wxT("Numpad 3");
		break;
	case WXK_NUMPAD4:
		return wxT("Numpad 4");
		break;
	case WXK_NUMPAD5:
		return wxT("Numpad 5");
		break;
	case WXK_NUMPAD6:
		return wxT("Numpad 6");
		break;
	case WXK_NUMPAD7:
		return wxT("Numpad 7");
		break;
	case WXK_NUMPAD8:
		return wxT("Numpad 8");
		break;
	case WXK_NUMPAD9:
		return wxT("Numpad 9");
		break;
	case WXK_NUMPAD_MULTIPLY:
		return wxT("Numpad Multiply");
		break;
	case WXK_NUMPAD_DIVIDE:
		return wxT("Numpad Divide");
		break;
	case WXK_NUMPAD_DECIMAL:
		return wxT("Numpad Decimal");
		break;
	case WXK_NUMPAD_SUBTRACT:
		return wxT("Numpad Subtract");
		break;
	case WXK_NUMPAD_SEPARATOR:
		return wxT("Numpad Separator");
		break;
	case WXK_NUMPAD_ADD:
		return wxT("Numpad Add");
		break;
	case WXK_NUMPAD_BEGIN:
		return wxT("Numpad Begin");
		break;
	case WXK_NUMPAD_END:
		return wxT("Numpad End");
		break;
	case WXK_NUMPAD_PAGEUP:
		return wxT("Numpad Page Up");
		break;
	case WXK_NUMPAD_PAGEDOWN:
		return wxT("Numpad Page Down");
		break;
	case WXK_NUMPAD_HOME:
		return wxT("Numpad Home");
		break;
	case WXK_NUMPAD_LEFT:
		return wxT("Numpad Add");
		break;
	case WXK_NUMPAD_RIGHT:
		return wxT("Numpad Right");
		break;
	case WXK_NUMPAD_UP:
		return wxT("Numpad Up");
		break;
	case WXK_NUMPAD_DOWN:
		return wxT("Numpad Down");
		break;
	case WXK_NUMPAD_INSERT:
		return wxT("Numpad Insert");
		break;
	case WXK_NUMPAD_DELETE:
		return wxT("Numpad Delete");
		break;
	case WXK_NUMPAD_EQUAL:
		return wxT("Numpad Equal");
		break;
	case WXK_DELETE:
		return wxT("DEL");
		break;
	case WXK_SPACE:
		return wxT("Space");
		break;
	case 0x29:
	case 0x30:
		return wxT("0");
		break;
	case 0x21:
	case 0x31:
		return wxT("1");
		break;
	case 0x40:
	case 0x32:
		return wxT("2");
		break;
	case 0x23:
	case 0x33:
		return wxT("3");
		break;
	case 0x24:
	case 0x34:
		return wxT("4");
		break;
	case 0x35:
		return wxT("5");
		break;
	case 0x5E:
	case 0x36:
		return wxT("6");
		break;
	case 0x37:
		return wxT("7");
		break;
	case 0x2A:
	case 0x38:
		return wxT("8");
		break;
	case 0x39:
		return wxT("9");
		break;
	case 0x41:
		return wxT("A");
		break;
	case 0x42:
		return wxT("B");
		break;
	case 0x43:
		return wxT("C");
		break;
	case 0x44:
		return wxT("D");
		break;
	case 0x45:
		return wxT("E");
		break;
	case 0x46:
		return wxT("F");
		break;
	case 0x47:
		return wxT("G");
		break;
	case 0x48:
		return wxT("H");
		break;
	case 0x49:
		return wxT("I");
		break;
	case 0x4A:
		return wxT("J");
		break;
	case 0x4B:
		return wxT("K");
		break;
	case 0x4C:
		return wxT("L");
		break;
	case 0x4D:
		return wxT("M");
		break;
	case 0x4E:
		return wxT("N");
		break;
	case 0x4F:
		return wxT("O");
		break;
	case 0x50:
		return wxT("P");
		break;
	case 0x51:
		return wxT("Q");
		break;
	case 0x52:
		return wxT("R");
		break;
	case 0x53:
		return wxT("S");
		break;
	case 0x54:
		return wxT("T");
		break;
	case 0x55:
		return wxT("U");
		break;
	case 0x56:
		return wxT("V");
		break;
	case 0x57:
		return wxT("W");
		break;
	case 0x58:
		return wxT("X");
		break;
	case 0x59:
		return wxT("Y");
		break;
	case 0x5A:
		return wxT("Z");
		break;
	case VK_MULTIPLY:
		return wxT("*");
		break;
	case VK_ADD:
		return wxT("+");
		break;
	case VK_SUBTRACT:
		return wxT("-");
		break;
	case VK_DECIMAL:
		return wxT(".");
		break;
	case 0x3A:
	case 0x3B:
	case VK_OEM_1:
		return wxT(";");
		break;
	case 0x2F:
	case 0x3F:
	case VK_OEM_2:
		return wxT("/");
		break;
	case 0x60:
	case 0x7E:
	case VK_OEM_3:
		return wxT("`");
		break;
	case 0x5B:
	case 0x7B:
	case VK_OEM_4:
		return wxT("[");
		break;
	case 0x5C:
	case 0x7C:
	case VK_OEM_5:
		return wxT("\\");
		break;
	case 0x5D:
	case 0x7D:
	case VK_OEM_6:
		return wxT("]");
		break;
	case 0x22:
	case VK_OEM_7:
		return wxT("'");
		break;
	case 0x2B:
	case 0x3D:
	case VK_OEM_PLUS:
		return wxT("+");
		break;
	case 0x2C:
	case 0x3C:
	case VK_OEM_COMMA:
		return wxT(",");
		break;
	case 0x2D:
	case VK_OEM_MINUS:
		return wxT("-");
		break;
	case 0x2E:
	case 0x3E:
	case VK_OEM_PERIOD:
		return wxT(".");
		break;
#endif
	default:
		return wxEmptyString;
	}
}
