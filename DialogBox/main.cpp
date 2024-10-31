#include<Windows.h>
#include "resource.h"

CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON2));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);

	}

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam) )
		{
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 250;
			CHAR sz_buffer[SIZE]{};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
			SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
		}
		case IDC_BUTTON_COPY:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			//ФУНКЦИЯ GetDlgItem() возвращает HWND дочернего элемента окна по его ResourceID.
			//HWND - Heander to Window (Дискриптор окна) - это число при помощи которого можно обратиться к окну.
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE];
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			
		}
		
		break;
		case IDOK: MessageBox(hwnd, "Была нажата кнопка OK!", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
		
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
