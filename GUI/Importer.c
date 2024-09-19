#include "GUI.h"





static LRESULT ImporterWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);





extern LPTABTREE NewImportView(void) {
	LPTABTREE lpTabTree;
	size_t StrLen;


	/// Allocate lpTabTree
	lpTabTree = (LPWNDBOX) malloc(sizeof(TABTREE));
	if (lpTabTree == NULL) {
		MessageBoxW(NULL, L"Could not allocate memory for lpTabTree.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	/// Allocate Tab
	lpTabTree->Tab = (LPIMPORTER) malloc(sizeof(IMPORTER));
	if (lpTabTree->Tab == NULL) {
		MessageBoxW(NULL, L"Failed to allocate memory for lpTabTree->Tab.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	/// Allocate the PostEditProvider
	((LPIMPORTER) lpTabTree->Tab)->PostEditor = NewPostEditProvider();
	if (((LPIMPORTER) lpTabTree->Tab)->PostEditor == NULL) {
		return NULL;
	} // End of If

	/// Assign Name
	lpTabTree->Name = (LPWSTR) malloc(7);
	if (lpTabTree->Name == NULL) {
		MessageBoxW(NULL, L"Could not allocate memory for lpTabTree->Name.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	swprintf_s(lpTabTree->Name, 7, L"Import\0");
	lpTabTree->Next = NULL;
	lpTabTree->Previous = NULL;
	lpTabTree->hWnd = ((LPIMPORTER) lpTabTree->Tab)->PostEditor->lpRootLayoutBox->hWnd;


	return lpTabTree;
} // End of Function





extern void RegisterImporterWindowClass(HINSTANCE hInstance) {
	WNDCLASSEXW WindowClass;

	CurrentTabInitialised = FALSE;
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = ImporterWndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_GUI);
	WindowClass.lpszClassName = L"Importer";
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassExW(&WindowClass)) {
		MessageBoxW(NULL, L"Failed to register importer window class.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If
} // End of Function





static LRESULT CALLBACK ImporterWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			CurrentTab->hWnd = NULL;
			break;

		case WM_PAINT: {
			PAINTSTRUCT PaintStruct;
			HDC Hdc = BeginPaint(hWnd, &PaintStruct);

			EndPaint(hWnd, &PaintStruct);
		} break;

		default:
			return DefWindowProcW(hWnd, Msg, wParam, lParam);
	} // End of Switch
} // End of Function