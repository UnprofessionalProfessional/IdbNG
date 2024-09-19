#include "Core.h"
#include "GUI.h"





extern LRESULT CALLBACK GalleryProviderWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	LRESULT lStatus;

	lStatus = 0;

	return lStatus;
} // End of Function





extern LSTATUS NewGalleryProvider(HWND hWnd) {
	LSTATUS Status;

	Status = 0;

	return Status;
} // End of Function





extern void RegisterGalleryProviderClass(HINSTANCE hInstance) {
	WNDCLASSEX WindowClass;

	// Register window class
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = GalleryProviderWndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = NULL;
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = L"ImageView";
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WindowClass)) {
		MessageBox(NULL, L"Failed to register ImageView class.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	} // End of If
} // End of Function
