#include "GUI.h"







extern HWND CreateSearchBox(HWND hParent) {
	HWND hSearchBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, 0, 0, 0, hParent, (HMENU) ID_SEARCH_BOX, GetModuleHandle(NULL), NULL);

	if (hSearchBox == NULL) {
		MessageBoxW(hParent, L"Could not create search box.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If

	SearchHeight = 20;
	SetWindowTextW(hSearchBox, L"Search...");

	return hSearchBox;
} // End of Function





extern void UpdateSearchBoxPosition(HWND hWnd, HWND hParent) {
	RECT rcClient;


	GetClientRect(hParent, &rcClient);
	SetWindowPos(hWnd, NULL, 0, 0, rcClient.right, SearchHeight, SWP_NOZORDER);
} // End of Function
