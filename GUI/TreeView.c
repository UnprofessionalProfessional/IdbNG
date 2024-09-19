#include "GUI.h"


extern HWND CreateTreeView(HWND hParent) {
	HWND hTreeView = CreateWindowExW(WS_EX_CLIENTEDGE, WC_TREEVIEW, L"Tree View", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS, 0, 0, 0, 0, hParent, (HMENU) ID_TREEVIEW, GetModuleHandleW(NULL), NULL);

	TreeViewWidth = 150;
	if (hTreeView == NULL) {
		MessageBoxW(hParent, L"Could not create Tree View.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If

	return hTreeView;
} // End of Function





extern void UpdateTreeViewPosition(HWND hChild, HWND hParent) {
	RECT rcClient;


	GetClientRect(hParent, &rcClient);
	SetWindowPos(hChild, NULL, 0, SearchHeight, TreeViewWidth, rcClient.bottom - StatusBarHeight - SearchHeight, SWP_NOZORDER);
} // End of Function
