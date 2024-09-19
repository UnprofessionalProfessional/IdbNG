#include "framework.h"
#include "GUI.h"

#include <CommCtrl.h>





extern HWND hMainWindow;
static void RegisterMainWindowClass(HINSTANCE hInstance);





int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	MSG Msg;


	RegisterMainWindowClass(hInstance);
	RegisterGalleryProviderClass(hInstance);
	RegisterImageViewerWindowClass(hInstance);
	RegisterLayoutBoxWindowClass(hInstance);


	// Create Window
	hMainWindow = CreateWindowExW(WS_EX_CLIENTEDGE, L"IdbNG_WindowClass", L"Image Database", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 800, NULL, NULL, hInstance, NULL);
	if (hMainWindow == NULL) {
		MessageBox(NULL, L"Window creation failed.", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	} // End of If


	SetWindowTheme(hMainWindow, L" ", L" ");
	ShowWindow(hMainWindow, nShowCmd);
	UpdateWindow(hMainWindow);
	SetupDatabase(hMainWindow);
	BringWindowToTop(hMainWindow);
	PostMessageW(hMainWindow, WM_POSTCREATE, 0, 0);

//	SetWindowTheme(hMainWindow, L" ", L" ");
//	SetWindowTheme(hMainWindow, L" ", L" ");
//	SetWindowTheme(GetWindow(IDD_ABOUTBOX, ), L" ", L" ");


	// Message loop
	while (GetMessageW(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	} // End of While


	return Msg.wParam;
} // End of Function





static void RegisterMainWindowClass(HINSTANCE hInstance) {
	WNDCLASSEXW WindowClass;


	// Register window class
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_GUI);
	WindowClass.lpszClassName = L"IdbNG_WindowClass";
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WindowClass)) {
		MessageBox(NULL, L"Failed to register main window class.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	} // End of If
} // End of Function
