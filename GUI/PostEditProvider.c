#include "GUI.h"

#include <Windows.h>
#include <CommCtrl.h>
#include <WinUser.h>





extern WNDCLASSEXW PostEditProviderRatingButtonSubClass;
static LSTATUS CALLBACK RatingBtnWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubClass, DWORD_PTR dwRefData);





extern LPPOSTEDITPROVIDER NewPostEditProvider(void) {
	LPPOSTEDITPROVIDER lpPostEditProvider;

	// #TODO: Simplify this with functions.
	// #TODO: Make the alt key work with the form members.
	// #TODO: Add scrollbar to this window or the other edit window
	// #TODO: Add variable AdditionalFlags to LayoutBox constructor
	// #TODO: Make it possible to "pop out" the tags window. This will require creating a new class, so it will be done later.


	/// Create lpPostEditProvider
	lpPostEditProvider = (LPPOSTEDITPROVIDER) malloc(sizeof(POSTEDITPROVIDER));
	if (lpPostEditProvider == NULL) {
		MessageBoxW(NULL, L"Failed to allocate memory for lpPostEditProvider.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	/// Create LayoutBoxes
	lpPostEditProvider->lpRootLayoutBox = NewLayoutBox(LB_VERTICAL);
	lpPostEditProvider->lpRadioLayoutBox = NewLayoutBox(LB_HORIZONTAL);
	lpPostEditProvider->lpControlBtnLayoutBox = NewLayoutBox(LB_HORIZONTAL);


	/// Create elements
	lpPostEditProvider->ImageView = NewImageViewer();


	// #NOTE: WS_CHILD must be used so windows may be added programatically.
	lpPostEditProvider->hRatingLabel = CreateWindowExW(0, L"STATIC", L"Rating:", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hRatingLabel == NULL) {
		MessageBoxW(NULL, L"Failed to create hRatingLabel window.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	/// hExplicitRadioBtn
	lpPostEditProvider->hExplicitRadioBtn = CreateWindowExW(0, L"BUTTON", L"E&xplicit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 0, 0, 0, 0, lpPostEditProvider->lpRadioLayoutBox->hWnd, (HMENU) ID_POSTEDITPROVIDER_RATING_EXPLICIT, (HINSTANCE) GetWindowLongPtrW(lpPostEditProvider->lpRadioLayoutBox->hWnd, GWLP_HINSTANCE), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hExplicitRadioBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	if (!SetWindowSubclass(lpPostEditProvider->hExplicitRadioBtn, RatingBtnWndProc, 0, ID_POSTEDITPROVIDER_RATING_EXPLICIT)) {
		MessageBoxW(NULL, L"Failed to set lpPostEditProvider->hExplicitRadioBtn's subclass.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If


	/// hQuestionableRadioBtn
	lpPostEditProvider->hQuestionableRadioBtn = CreateWindowExW(0, L"BUTTON", L"&Questionable", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, (HMENU) ID_POSTEDITPROVIDER_RATING_QUESTIONABLE, GetWindowLongPtrW(lpPostEditProvider->lpRadioLayoutBox->hWnd, GWLP_HINSTANCE), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hQuestionableRadioBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	if (!SetWindowSubclass(lpPostEditProvider->hQuestionableRadioBtn, RatingBtnWndProc, 0, ID_POSTEDITPROVIDER_RATING_QUESTIONABLE)) {
		MessageBoxW(NULL, L"Failed to set lpPostEditProvider->hExplicitRadioBtn's subclass.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If


	/// hSensitiveRadioBtn
	lpPostEditProvider->hSensitiveRadioBtn = CreateWindowExW(0, L"BUTTON", L"&Sensitive", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, (HMENU) ID_POSTEDITPROVIDER_RATING_SENSITIVE, GetWindowLongPtrW(lpPostEditProvider->lpRadioLayoutBox->hWnd, GWLP_HINSTANCE), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hSensitiveRadioBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	if (!SetWindowSubclass(lpPostEditProvider->hSensitiveRadioBtn, RatingBtnWndProc, 0, ID_POSTEDITPROVIDER_RATING_SENSITIVE)) {
		MessageBoxW(NULL, L"Failed to set lpPostEditProvider->hExplicitRadioBtn's subclass.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If


	/// hSafeRadioBtn
	lpPostEditProvider->hSafeRadioBtn = CreateWindowExW(0, L"BUTTON", L"&General", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, (HMENU) ID_POSTEDITPROVIDER_RATING_SAFE, GetWindowLongPtrW(lpPostEditProvider->lpRadioLayoutBox->hWnd, GWLP_HINSTANCE), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hSafeRadioBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	if (!SetWindowSubclass(lpPostEditProvider->hSafeRadioBtn, RatingBtnWndProc, 0, ID_POSTEDITPROVIDER_RATING_SAFE)) {
		MessageBoxW(NULL, L"Failed to set lpPostEditProvider->hExplicitRadioBtn's subclass.", L"Error", MB_OK | MB_ICONERROR);
	} // End of If


	/// hArtistLabel
	lpPostEditProvider->hArtistLabel = CreateWindowExW(0, L"STATIC", L"A&rtist(s)", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hArtistLabel.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	/// hArtistEdit
	lpPostEditProvider->hArtistEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hArtistEdit.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	/// hSourceLabel
	lpPostEditProvider->hSourceLabel = CreateWindowExW(0, L"STATIC", L"S&ource", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hSourceLabel.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	/// hSourceEdit
	lpPostEditProvider->hSourceEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hSourceEdit.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	/// hTagLabel
	lpPostEditProvider->hTagLabel = CreateWindowExW(0, L"STATIC", L"Ta&gs", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hTagLabel.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	/// hTagEntry
	lpPostEditProvider->hTagEntry = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 0, 0, 0, 0, lpPostEditProvider->lpRootLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hExplicitRadioBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hTagEntry.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If



	SetWindowTheme(lpPostEditProvider->hTagEntry, L" ", L" ");

	/* Add Elements */
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->ImageView->hWnd, 0, 0, 00, 0, -1, 500);
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hRatingLabel, 0, 0, 00, 0, -1, 20);

	/// lpRadioLayoutBox
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->lpRadioLayoutBox->hWnd, 0, 0, 0, 0, -1, 40);
	AddChildToLayoutBox(lpPostEditProvider->lpRadioLayoutBox, lpPostEditProvider->hExplicitRadioBtn, 0, 0, 0, 0, 90, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRadioLayoutBox, lpPostEditProvider->hQuestionableRadioBtn, 0, 0, 0, 0, 120, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRadioLayoutBox, lpPostEditProvider->hSensitiveRadioBtn, 0, 0, 0, 0, 100, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRadioLayoutBox, lpPostEditProvider->hSafeRadioBtn, 0, 0, 0, 0, 80, 20);

	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hArtistLabel, 0, 0, 10, 0, -1, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hArtistEdit, 0, 0, 0, 0, -1, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hSourceLabel, 0, 0, 10, 0, -1, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hSourceEdit, 0, 0, 0, 0, -1, 20);
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hTagLabel, 0, 0, 10, 0, -1, 20);

	/// hTagEntry
	/// #TODO: Make this vertically resizeable
	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->hTagEntry, 0, 0, 0, 0, -1, 100);


	/// Control Buttons
	lpPostEditProvider->hSubmitBtn = CreateWindowExW(0, L"BUTTON", L"S&ubmit", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpControlBtnLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hSubmitBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hSubmitBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If

	lpPostEditProvider->hCancelBtn = CreateWindowExW(0, L"BUTTON", L"&Cancel", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, lpPostEditProvider->lpControlBtnLayoutBox->hWnd, NULL, GetModuleHandleW(NULL), NULL);
	if (lpPostEditProvider->hSubmitBtn == NULL) {
		MessageBoxW(NULL, L"Failed to create hCancelBtn.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	AddChildToLayoutBox(lpPostEditProvider->lpRootLayoutBox, lpPostEditProvider->lpControlBtnLayoutBox->hWnd, -1, 0, 0, 0, 170, 40);
	AddChildToLayoutBox(lpPostEditProvider->lpControlBtnLayoutBox, lpPostEditProvider->hSubmitBtn, 0, 5, 0, 0, 80, 30);
	AddChildToLayoutBox(lpPostEditProvider->lpControlBtnLayoutBox, lpPostEditProvider->hCancelBtn, -1, 0, 0, 0, 80, 30);


	return lpPostEditProvider;
} // End of Function





static LSTATUS CALLBACK RatingBtnWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubClass, DWORD_PTR dwRefData) {
	switch (Msg) {
		case WM_LBUTTONDOWN: {
			switch (dwRefData) {
				case ID_POSTEDITPROVIDER_RATING_EXPLICIT:
				case ID_POSTEDITPROVIDER_RATING_QUESTIONABLE:
				case ID_POSTEDITPROVIDER_RATING_SENSITIVE:
				case ID_POSTEDITPROVIDER_RATING_SAFE:
					CheckRadioButton(GetParent(hWnd), ID_POSTEDITPROVIDER_RATING_EXPLICIT, ID_POSTEDITPROVIDER_RATING_SAFE, GetDlgCtrlID(hWnd));
					UpdateWindow(hWnd);
					return 0;

				default:
					break;
			} // End of Switch
		} break;

		default:
			return DefSubclassProc(hWnd, Msg, wParam, lParam);
	} // End of Switch

	return DefSubclassProc(hWnd, Msg, wParam, lParam);
} // End of Function
