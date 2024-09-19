#include "GUI.h"





/**
 * Add a sub-window to an LPLAYOUTBOX.
 *
 * \param lpLayoutBox: The target LPLAYOUTBOX.
 * \param hChild: The window to be to lpLayoutBox
 * \param LeftPadding: Space on the left of hChild.
 * \param RightPadding: #TODO
 * \param TopPadding: Empty space above hChild. Must be >= 0.
 * \param BottomPadding: Empty space below hChild. Must be >= 0.
 * \param Width: Width of hChild. Use -1 occupy all space on the X-axis, minus the left- and right-padding.
 * \param Height: Height of hChild.
 */
extern void AddChildToLayoutBox(LPLAYOUTBOX lpLayoutBox, HWND hChild, int LeftPadding, int RightPadding, int TopPadding, int BottomPadding, int Width, int Height) {
	int NetLeftPadding = 0;
	int NetRightPadding = 0;
	int NetVerticalPadding = 0;


	// Check for first child
	if (lpLayoutBox->lpFirstChild == NULL) {
		lpLayoutBox->lpFirstChild = (LPWNDBOX) malloc(sizeof(WNDBOX));
		if (lpLayoutBox->lpFirstChild == NULL) {
			MessageBoxW(NULL, L"Failed to allocate memory for lpLayoutBox->lpFirstChild.", L"Error", MB_OK | MB_ICONERROR);
			return;
		} // End of If

		lpLayoutBox->lpFirstChild->hWnd = hChild;
		lpLayoutBox->lpFirstChild->LeftPadding = LeftPadding;
		lpLayoutBox->lpFirstChild->RightPadding = RightPadding;
		lpLayoutBox->lpFirstChild->TopPadding = TopPadding;
		lpLayoutBox->lpFirstChild->BottomPadding = BottomPadding;
		lpLayoutBox->lpFirstChild->Width = Width;
		lpLayoutBox->lpFirstChild->Height = Height;
		lpLayoutBox->lpFirstChild->Next = NULL;
		goto DoneFirstIf;
	} else {
		LPWNDBOX lpTempWndBox;
		LPWNDBOX lpPrevWndBox = NULL;


		// Get the last node in the list
		lpTempWndBox = lpLayoutBox->lpFirstChild;
		while (lpTempWndBox != NULL) {
			lpPrevWndBox = lpTempWndBox;
			lpTempWndBox = lpTempWndBox->Next;
		} // End of While


		// Allocate new node
		lpPrevWndBox->Next = (LPWNDBOX) malloc(sizeof(WNDBOX));
		if (lpPrevWndBox->Next == NULL) {
			MessageBoxW(NULL, L"Failed to allocate memory for lpPrevWndBox->Next.", L"Error", MB_OK | MB_ICONERROR);
			return;
		} // End of If


		/// Assign members
		lpPrevWndBox->Next->hWnd = hChild;
		lpPrevWndBox->Next->LeftPadding = LeftPadding;
		lpPrevWndBox->Next->RightPadding = RightPadding;
		lpPrevWndBox->Next->TopPadding = TopPadding;
		lpPrevWndBox->Next->BottomPadding = BottomPadding;
		lpPrevWndBox->Next->Width = Width;
		lpPrevWndBox->Next->Height = Height;
		lpPrevWndBox->Next->Next = NULL;
		printf("");
	} // End of If/Else



DoneFirstIf:
	SetParent(hChild, lpLayoutBox->hWnd);
	UpdateLayoutBox(lpLayoutBox);
} // End of Function





// #TODO: Write a function insert at





static LRESULT CALLBACK LayoutBoxWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
		case WM_CREATE: {
			INITCOMMONCONTROLSEX CommCtrlEx;


			CommCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
			CommCtrlEx.dwICC = ICC_WIN95_CLASSES;
//			InitCommonControls(&CommCtrlEx);
		} break;

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

	return DefWindowProcW(hWnd, Msg, wParam, lParam);
} // End of Function





/**
 * Create a new LPLAYOUTBOX.
 *
 * \param Direction:
 * \return
 */
extern LPLAYOUTBOX NewLayoutBox(BOOL Direction) {
	LPLAYOUTBOX lpLayoutBox;


	lpLayoutBox = (LPLAYOUTBOX) malloc(sizeof(LAYOUTBOX));
	if (lpLayoutBox == NULL) {
		MessageBoxW(NULL, L"Failed to allocate memory for lpLayoutBox.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If



	lpLayoutBox->hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, L"LayoutBox", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT, 0, 0, 0, 0, hMainWindow, (HMENU) PROVIDER_LAYOUT_VIEW, GetModuleHandleW(NULL), NULL);
	if (lpLayoutBox->hWnd == NULL) {
		MessageBoxW(NULL, L"Failed to create LayoutBox window.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	SetWindowTheme(lpLayoutBox->hWnd, L" ", L" ");
	lpLayoutBox->Direction = Direction;
	lpLayoutBox->lpFirstChild = NULL;


	return lpLayoutBox;
} // End of Function





extern void RegisterLayoutBoxWindowClass(HINSTANCE hInstance) {
	WNDCLASSEXW WindowClass;

	CurrentTabInitialised = FALSE;
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = LayoutBoxWndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_GUI);
	WindowClass.lpszClassName = L"LayoutBox";
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassExW(&WindowClass)) {
		MessageBoxW(NULL, L"Failed to register importer window class.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If
} // End of Function





extern void UpdateLayoutBox(LPLAYOUTBOX lpLayoutBox) {
	int NetHorizontalPadding = 0;
	int NetVerticalPadding = 0;
	LPWNDBOX lpTempWndBox;
	RECT LayoutBoxRect;


	// Set Expansion Properties
	// #TODO: Add logic for centring things (ie, LeftPadding and RightPadding are -1
	GetClientRect(lpLayoutBox->hWnd, &LayoutBoxRect);
	lpTempWndBox = lpLayoutBox->lpFirstChild;

	if (lpLayoutBox->Direction == LB_VERTICAL) {
		while (lpTempWndBox != NULL) {
			NetVerticalPadding += lpTempWndBox->TopPadding;

			if (lpTempWndBox->Width == -1) {
				SetWindowPos(lpTempWndBox->hWnd, NULL, lpTempWndBox->LeftPadding, NetVerticalPadding, LayoutBoxRect.right - lpTempWndBox->LeftPadding - lpTempWndBox->RightPadding, lpTempWndBox->Height, SWP_NOZORDER);
			} else {
				SetWindowPos(lpTempWndBox->hWnd, NULL, lpTempWndBox->LeftPadding, NetVerticalPadding, lpTempWndBox->Width, lpTempWndBox->Height, SWP_NOZORDER);
			} // End of If/Else

			NetVerticalPadding += lpTempWndBox->BottomPadding + lpTempWndBox->Height;
			lpTempWndBox = lpTempWndBox->Next;
		} // End of While
	} else {
		while (lpTempWndBox != NULL) {
			NetHorizontalPadding += lpTempWndBox->LeftPadding;

			// #FIXME: Passing -1 doesn't work
			if (lpTempWndBox->Height = -1) {
				SetWindowPos(lpTempWndBox->hWnd, NULL, NetHorizontalPadding, lpTempWndBox->TopPadding, lpTempWndBox->Width, LayoutBoxRect.bottom - lpTempWndBox->Height, SWP_NOZORDER);
			} else {
				SetWindowPos(lpTempWndBox->hWnd, NULL, NetHorizontalPadding, lpTempWndBox->TopPadding, lpTempWndBox->Width, lpTempWndBox->Height, SWP_NOZORDER);
			} // End of If/Else

			NetHorizontalPadding += lpTempWndBox->RightPadding + lpTempWndBox->Width;
			lpTempWndBox = lpTempWndBox->Next;
		} // End of While
	} // End of If/Else


	SetFocus(hMainWindow);
} // End of Function
