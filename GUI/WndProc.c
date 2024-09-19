#include "GUI.h"

#include <shlobj_core.h>





extern HWND hCurrentTab;
extern HWND hTabTree;
extern HWND hSearchBox;
extern HWND hStatusBar;





extern LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	static HWND hPreview;
	static HMENU hMenu;
	LSTATUS CoreStatus = 0;



	switch (Msg) {
		case WM_POSTCREATE:
			if (hMainWindow == NULL) {
				MessageBoxW(hWnd, L"hMainWindow is NULL.", L"Error", MB_OK | MB_ICONERROR);
			} // End of If

			InitialiseTab(TabRoot);
			if (TabRoot == NULL) {
				MessageBoxW(hMainWindow, L"Could not allocate memory for importer window.", L"Error", MB_OK | MB_ICONERROR);
				abort();
			} // End of If

			CurrentTab = TabRoot;
			SetCurrentView(CurrentView);
			CurrentTabInitialised = TRUE;
			SendMessageW(hMainWindow, WM_SIZE, 0, 0);
			break;

		case WM_CREATE: {
			INITCOMMONCONTROLSEX CommCtrlEx;


			CommCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
			CommCtrlEx.dwICC = ICC_WIN95_CLASSES;
//			InitCommonControls(&CommCtrlEx);

			Setup(hWnd);

			hMenu = GetMenu(hWnd);
			CheckMenu(CurrentView, hMenu);		// also initialises menu states
			hSearchBox = CreateSearchBox(hWnd);
			hStatusBar = CreateStatusBar(hWnd);
			hTabTree = CreateTreeView(hWnd);

			TabRoot = NULL;
			CurrentTab = NULL;
			AllocateMemory(&TabRoot, 1, sizeof(LPTABTREE));
		} break;

		case WM_COMMAND:
			// #TODO: Add logic for thumbnail size
			switch (LOWORD(wParam)) {
				case IDM_EXIT:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
					break;

				case ID_FILE_IMPORT:
					// 1. Open a file picker dialogue
					// 2. Get the file path
					// 3. Get the file type
					// 4. Check if it's an image
					// 5. Open a new post editor
					// 6. Convert the image to a BMP
					// 7. Set the post editor's ImageViewer->BitMap to the image
					break;

				case ID_VIEW_ARTISTS:
				case ID_VIEW_GALLERY:
				case ID_VIEW_POOLS:
				case ID_VIEW_RECYCLEBIN:
				case ID_VIEW_TAGS:
				case ID_VIEW_WIKI:
					CheckMenu(LOWORD(wParam), hMenu);
					break;

				case ID_VIEW_PREVIEW:
					CheckPreview(hMenu);
					break;

				case ID_VIEW_SAFEMODE:
					CheckSafeMode(hMenu);
					break;

				case ID_IMPORT_FILE:
//					SetupDatabase(hWnd);
					break;

				case ID_THUMBNAILS_32:
				case ID_THUMBNAILS_64:
				case ID_THUMBNAILS_128:
				case ID_THUMBNAILS_256:
				case ID_THUMBNAILS_512:
				case ID_THUMBNAILS_1024:
					CheckThumbnailSize(hMenu, LOWORD(wParam));	// This also changes the view
					break;

				case IDM_ABOUT:
					DialogBoxW(GetModuleHandleW(NULL), IDD_ABOUTBOX, hWnd, AboutDlgProc);
					break;

				default:
					return DefWindowProc(hWnd, Msg, wParam, lParam);
					break;
			} break;

//		case WM_SHOWWINDOW:
//			SetupDatabase(hWnd);
//			break;

		case WM_CLOSE:
			// Disconnect from the database
			DestroyWindow(hWnd);
			break;

		case WM_DESTROY:
			DbDisconnect();
			PostQuitMessage(0);
			break;

		case WM_PARENTNOTIFY: {
			WORD wmId = LOWORD(wParam);

		} break;

		case WM_SIZE: {
			RECT MainWndRect;

			GetClientRect(hMainWindow, &MainWndRect);

			SendMessageW(hStatusBar, WM_SIZE, 0, 0);
			UpdateStatusBarPosition(hStatusBar, hWnd);

			SendMessageW(hSearchBox, WM_SIZE, 0, 0);
			UpdateSearchBoxPosition(hSearchBox, hWnd);

			SendMessageW(hTabTree, WM_SIZE, 0, 0);
			UpdateTreeViewPosition(hTabTree, hWnd);

			SendMessageW(TabRoot->hWnd, WM_SIZE, 0, 0);

			if (CurrentTabInitialised) {
				SendMessageW(CurrentTab->hWnd, WM_SIZE, 0, 0);
				UpdateWindowPosition(hMainWindow, CurrentTab->hWnd, TreeViewWidth, SearchHeight, MainWndRect.right - TreeViewWidth, MainWndRect.bottom - StatusBarHeight - SearchHeight, FALSE, FALSE);
				UpdateCurrentTab();
			} // End of If


			break;
		}

		default:
			return DefWindowProc(hWnd, Msg, wParam, lParam);
	} // End of Switch

	return 0;
}// End of Function
