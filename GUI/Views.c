#include "GUI.h"




static void UnCheckViewMenus(HMENU hMenu) {
	CheckMenuItem(hMenu, ID_VIEW_ARTISTS, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VIEW_GALLERY, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VIEW_POOLS, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VIEW_RECYCLEBIN, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VIEW_TAGS, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_VIEW_WIKI, MF_UNCHECKED);
} // End of Function





extern void CheckMenu(WORD bMenuItemId, HMENU hMenu) {
	UnCheckViewMenus(hMenu);
	CheckMenuItem(hMenu, bMenuItemId, MF_CHECKED);
	SetDefaultView(bMenuItemId);
	// #TODO: Update the view

	CheckSafeModeEx(hMenu, SafeMode);
	CheckPreviewEx(hMenu, ShowPreview);
	CheckThumbnailSize(hMenu, ThumbSize);
} // End of Function





extern void CheckPreview(HMENU hMenu) {
	MENUITEMINFOW MenuItemInfo;
	UINT uState;


	MenuItemInfo.cbSize = sizeof(MENUITEMINFOW);
	MenuItemInfo.fMask = MIIM_STATE;


	// Get menu state
	if (GetMenuItemInfoW(hMenu, ID_VIEW_PREVIEW, FALSE, &MenuItemInfo)) {
		uState = MenuItemInfo.fState;
	} else {
		MessageBoxW(NULL, L"Failed to retrieved the ID_VIEW_PREVIEW menu state.", L"Error", MB_OK | MB_ICONERROR);
		return;
	} // End of If/Else


	// Set menu state
	if (MenuItemInfo.fState & MFS_CHECKED) {
		CheckMenuItem(hMenu, ID_VIEW_PREVIEW, MF_UNCHECKED);
		ShowPreview = 0;
	} else {
		CheckMenuItem(hMenu, ID_VIEW_PREVIEW, MF_CHECKED);
		ShowPreview = 1;
	} // End of If/Else


	SetShowPreview(ShowPreview);
} // End of Function





extern void CheckPreviewEx(HMENU hMenu, DWORD Value) {
	if (Value == 0) {
		CheckMenuItem(hMenu, ID_VIEW_PREVIEW, MF_UNCHECKED);
		ShowPreview = 0;
		SetShowPreview(ShowPreview);
	} else {
		CheckMenuItem(hMenu, ID_VIEW_PREVIEW, MF_CHECKED);
		ShowPreview = 1;
		SetShowPreview(ShowPreview);
	} // End of If/Else
} // End of Function





// #TODO: Send a message to all relevant views
extern void CheckSafeMode(HMENU hMenu) {
	MENUITEMINFOW MenuItemInfo;
	UINT uState;


	MenuItemInfo.cbSize = sizeof(MENUITEMINFOW);
	MenuItemInfo.fMask = MIIM_STATE;


	if (GetMenuItemInfoW(hMenu, ID_VIEW_SAFEMODE, FALSE, &MenuItemInfo)) {
		uState = MenuItemInfo.fState;
	} else {
		MessageBoxW(NULL, L"Failed to retrieved the ID_VIEW_SAFEMODE menu state.", L"Error", MB_OK | MB_ICONERROR);
		return;
	} // End of If/Else

	if (MenuItemInfo.fState & MFS_CHECKED) {
		CheckMenuItem(hMenu, ID_VIEW_SAFEMODE, MF_UNCHECKED);
		SafeMode = 0;
		SetSafeMode(SafeMode);
	} else {
		CheckMenuItem(hMenu, ID_VIEW_SAFEMODE, MF_CHECKED);
		SafeMode = 1;
		SetSafeMode(SafeMode);
	} // End of If/Else
} // End of Function





// #TODO: Send a message to all relevant views
///

/// <summary>
///
/// </summary>
/// <param name="hMenu">Handle to the main window's menu.</param>
/// <param name="Value"></param>
extern void CheckSafeModeEx(HMENU hMenu, DWORD Value) {
	if (Value == 0) {
		CheckMenuItem(hMenu, ID_VIEW_SAFEMODE, MF_UNCHECKED);
		SafeMode = 0;
		SetSafeMode(SafeMode);
	} else {
		CheckMenuItem(hMenu, ID_VIEW_SAFEMODE, MF_CHECKED);
		SafeMode = 1;
		SetSafeMode(SafeMode);
	} // End of If/Else
} // End of Function





/// <summary>
/// Remove the check mark from all thumbnail size MenuItems.
/// </summary>
/// <param name="hMenu">Handle to the main window's menu.</param>
extern void UnCheckThumbnailSizeMenus(HMENU hMenu) {
	CheckMenuItem(hMenu, ID_THUMBNAILS_32, MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_THUMBNAILS_64  , MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_THUMBNAILS_128 , MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_THUMBNAILS_256 , MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_THUMBNAILS_512 , MF_UNCHECKED);
	CheckMenuItem(hMenu, ID_THUMBNAILS_1024, MF_UNCHECKED);
} // End of Function





/// <summary>
/// Check a MenuItem for one of the thumbnail size MenuItems.
/// </summary>
/// <param name="hMenu">Handle to the main window's menu.</param>
/// <param name="Value">ID of the MenuItem to be checked.</param>
extern void CheckThumbnailSize(HMENU hMenu, DWORD Value) {
	UnCheckThumbnailSizeMenus(hMenu);
	switch (Value) {
		case ID_THUMBNAILS_32:
			ThumbSize = 32;
			CheckMenuItem(hMenu, ID_THUMBNAILS_32, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_32);
			break;

		case ID_THUMBNAILS_64:
			ThumbSize = 64;
			CheckMenuItem(hMenu, ID_THUMBNAILS_64, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_64);
			break;

		case ID_THUMBNAILS_128:
			ThumbSize = 128;
			CheckMenuItem(hMenu, ID_THUMBNAILS_128, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_128);
			break;

		case ID_THUMBNAILS_256:
			ThumbSize = 256;
			CheckMenuItem(hMenu, ID_THUMBNAILS_256, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_256);
			break;

		case ID_THUMBNAILS_512:
			ThumbSize = 512;
			CheckMenuItem(hMenu, ID_THUMBNAILS_512, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_512);
			break;

		case ID_THUMBNAILS_1024:
			ThumbSize = 1024;
			CheckMenuItem(hMenu, ID_THUMBNAILS_1024, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_1024);
			break;

		default:
			MessageBoxW(NULL, L"Invalid thumbnail size.", L"Error", MB_OK | MB_ICONINFORMATION);
			ThumbSize = 64;
			CheckMenuItem(hMenu, ID_THUMBNAILS_64, MF_CHECKED);
			SetThumbSize(ID_THUMBNAILS_64);
			break;
	} // End of Switch
} // End of Function





extern void SetCurrentView(WPARAM ViewType) {
	// #NOTE: What the actual fuck is this for?
//	if (CurrentTab != NULL) {
//		DestroyWindow(CurrentTab->hWnd);
//		free(CurrentTab);
//		CurrentTab = NULL;
//	} // End of If


	switch (ViewType) {
		case VIEW_ARTISTS:
		case VIEW_ARTIST:
		case VIEW_GALLERY:
			break;

		case VIEW_IMPORTER:
			CurrentTab = NewImportView();
			SetParent(CurrentTab->hWnd, hMainWindow);
			break;

		case VIEW_OPTIONS:
		case VIEW_POOLS:
		case VIEW_POST:
		case VIEW_RECYCLE_BIN:
		case VIEW_TAGS:
		case VIEW_WIKI:
			break;

		default:
			break;
	} // End of Switch
} // End of Function




extern void UpdateCurrentTab(void) {
	switch (CurrentView) {
		case VIEW_ARTISTS:
		case VIEW_ARTIST:
		case VIEW_GALLERY:
			break;

		case VIEW_IMPORTER:
			UpdateLayoutBox(((LPIMPORTER) CurrentTab->Tab)->PostEditor->lpRootLayoutBox);
			break;

		case VIEW_OPTIONS:
		case VIEW_POOLS:
		case VIEW_POST:
		case VIEW_RECYCLE_BIN:
		case VIEW_TAGS:
		case VIEW_WIKI:
			break;

		default:
			break;
	} // End of Switch
}





extern void UpdateWindowPosition(HWND hParent, HWND hChild, int X, int Y, int Width, int Height, BOOL HzExpand, BOOL VtExpand) {
	RECT ParentRect;


	GetClientRect(hParent, &ParentRect);

	if (HzExpand) {
		Width = ParentRect.right;
	} // End of If

	if (VtExpand) {
		Height = ParentRect.bottom;
	} // End of If

	SetWindowPos(hChild, NULL, X, Y, Width, Height, SWP_NOZORDER);
} // End of Function
