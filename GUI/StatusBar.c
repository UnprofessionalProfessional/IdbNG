#include "GUI.h"


extern HWND hStatusBar;


extern HWND CreateStatusBar(HWND hwndParent) {
	hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
		WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
		0, 0, 0, 0,
		hwndParent, (HMENU) ID_STATUSBAR, GetModuleHandle(NULL), NULL);

	if (hStatusBar) {
		int statwidths[] = { 80, -1 };
		SendMessage(hStatusBar, SB_SETPARTS, 2, (LPARAM) statwidths);
		SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM) L"Disconnected");
	} // End of If

	SetWindowTheme(hStatusBar, L" ", L" ");

	return hStatusBar;
} // End of Function






extern void UpdateStatusBarPosition(HWND hChild, HWND hParent) {
	RECT rcClient;
	RECT rcStatus;


	GetClientRect(hParent, &rcClient);
	GetWindowRect(hChild, &rcStatus);
	StatusBarHeight = rcStatus.bottom - rcStatus.top;
	SetWindowPos(hChild, NULL, 0, rcClient.bottom - StatusBarHeight, rcClient.right, StatusBarHeight, SWP_NOZORDER);
} // End of Function
