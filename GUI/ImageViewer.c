#include "GUI.h"




#define SCROLL_INCREMENT 50





extern LRESULT CALLBACK ImageViewerWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	HDC hDc;
	HDC hDcMem;
	HGDIOBJ hOldBitMap;
	PAINTSTRUCT PaintStruct;
	LPIMAGEVIEWER lpImageViewer;
	BITMAP BitMap;
	static POINT DragStartPoint;

	// #TODO: Add zoom controls
	// #TODO: Decide on a keyboard shortcut for zooming
	// #TODO: Centre the image
	// #TODO: Test this with multiple windows
	// #FIXME: When the image is taller than hWnd and hWnd is maximised, the very bottom of the image is repeated. See below
	// #TODO: Change the page size (nPage) to be divisible by the image's length and width, using a percentage
	// #TODO: Add drag support
	// #FIXME: When the window's width >= the image's width and the the horizontal scrollbar is not a 0, part of the image will be clipped.

//	static bool OneTimeInit = false;
//	if (!OneTimeInit) {
//		if (!DbTest()) {
//			MessageBoxW(NULL, L"Failed to insert value into database.", L"Error", MB_OK | MB_ICONERROR);
//		} // End of If
//		OneTimeInit = true;
//	} // End of If


	/* Store original image as bitmap
	 * Store the width and height of the original image
	 * Zoom factor
	 * Store the position "window" of the image to be displayed
	 *	X-Offset
	 *	Y-Offset
	 * When zooming, Copy pixels in zoom window from original image and scale w/ ImageMagick
	 *
	 */




	switch (Msg) {
		case WM_CREATE:
			// Window-Specific Data
			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			return 0;


		case WM_SIZE: {
			int Delta;


			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			if (lpImageViewer == NULL) {
				break;
			} // End of If


			// Common Values
			lpImageViewer->ScrollInfo.cbSize = sizeof(SCROLLINFO);
			lpImageViewer->ScrollInfo.fMask = SIF_PAGE;


			// Adjust Horizontal ScrollBar Range
			if (lpImageViewer->Width > LOWORD(lParam)) {
				lpImageViewer->ScrollInfo.nMin = 0;
				lpImageViewer->ScrollInfo.nPage = LOWORD(lParam);
				Delta = lpImageViewer->Width - lpImageViewer->ScrollInfo.nPage;
				lpImageViewer->ScrollInfo.nMax = max(0, Delta);
				SetScrollInfo(hWnd, SB_HORZ, &lpImageViewer->ScrollInfo, TRUE);
				ShowScrollBar(hWnd, SB_HORZ, TRUE);
			} else {
				ShowScrollBar(hWnd, SB_HORZ, FALSE);
			} // End of If/Else


			// Adjust Vertical ScrollBar Range
			if (lpImageViewer->Height > HIWORD(lParam)) {
				lpImageViewer->ScrollInfo.nMin = 0;
				lpImageViewer->ScrollInfo.nPage = HIWORD(lParam);
				Delta = lpImageViewer->Height - lpImageViewer->ScrollInfo.nPage;
//				lpImageViewer->ScrollInfo.nMax = max(0, Delta);
				lpImageViewer->ScrollInfo.nMax = lpImageViewer->Height;
				SetScrollInfo(hWnd, SB_VERT, &lpImageViewer->ScrollInfo, TRUE);
				ShowScrollBar(hWnd, SB_VERT, TRUE);
			} else {
				ShowScrollBar(hWnd, SB_VERT, FALSE);
			} // End of If/Else


			InvalidateRect(hWnd, NULL, TRUE);
		} return 0;


		case WM_PAINT:
			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			hDc = BeginPaint(hWnd, &PaintStruct);


			// Memory for BitMap
			hDcMem = CreateCompatibleDC(hDc);
			hOldBitMap = SelectObject(hDcMem, lpImageViewer->hBitMap);


			// Paint Visible Part of BitMap
			BitBlt(hDc, 0, 0, PaintStruct.rcPaint.right - PaintStruct.rcPaint.left, PaintStruct.rcPaint.bottom - PaintStruct.rcPaint.top, hDcMem, lpImageViewer->xScrollPos, lpImageViewer->yScrollPos, SRCCOPY);


			// Clean Up
			SelectObject(hDcMem, hOldBitMap);
			DeleteDC(hDcMem);
			EndPaint(hWnd, &PaintStruct);
			return 0;


		case WM_HSCROLL: {
			int DeltaWidth;


			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			lpImageViewer->ScrollInfo.cbSize = sizeof(lpImageViewer->ScrollInfo);
			lpImageViewer->ScrollInfo.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_HORZ, &lpImageViewer->ScrollInfo);


			switch (LOWORD(wParam)) {
				case SB_PAGEUP:
					lpImageViewer->xScrollPos -= lpImageViewer->ScrollInfo.nPage;
					break;

				case SB_PAGEDOWN:
					lpImageViewer->xScrollPos += lpImageViewer->ScrollInfo.nPage;
					break;

				case SB_LINEUP:
					lpImageViewer->xScrollPos -= SCROLL_INCREMENT;
					break;

				case SB_LINEDOWN:
					lpImageViewer->xScrollPos += SCROLL_INCREMENT;
					break;

				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:
//					lpImageViewer->xScrollPos = HIWORD(wParam);
					lpImageViewer->xScrollPos = lpImageViewer->ScrollInfo.nTrackPos;
					break;

					/*
				default:
					lpImageViewer->xScrollPos = xCurrentScroll;
					break;
					*/
			} // End of Switch


			// Calculate New Position
			DeltaWidth = lpImageViewer->Width - lpImageViewer->ScrollInfo.nPage;
			lpImageViewer->xScrollPos = max(0, min(lpImageViewer->xScrollPos, DeltaWidth));

			lpImageViewer->ScrollInfo.fMask = SIF_POS;
			lpImageViewer->ScrollInfo.nPos = lpImageViewer->xScrollPos;
			SetScrollInfo(hWnd, SB_HORZ, &lpImageViewer->ScrollInfo, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		} return 0;


		case WM_VSCROLL: {
			int DeltaHeight;


			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			lpImageViewer->ScrollInfo.cbSize = sizeof(lpImageViewer->ScrollInfo);
			lpImageViewer->ScrollInfo.fMask = SIF_ALL;
			GetScrollInfo(hWnd, SB_VERT, &lpImageViewer->ScrollInfo);	// Why is this here?



			switch (LOWORD(wParam)) {
				case SB_PAGEUP:
					lpImageViewer->yScrollPos -= lpImageViewer->ScrollInfo.nPage;
					break;

				case SB_PAGEDOWN:
					lpImageViewer->yScrollPos += lpImageViewer->ScrollInfo.nPage;
					break;

				case SB_LINEUP:
					lpImageViewer->yScrollPos -= SCROLL_INCREMENT;
					break;

				case SB_LINEDOWN:
					lpImageViewer->yScrollPos += SCROLL_INCREMENT;
					break;

				// User dragged scroll box
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:
					lpImageViewer->yScrollPos = lpImageViewer->ScrollInfo.nTrackPos;
					break;
			} // End of Switch


			// Calculate New Position
			DeltaHeight = lpImageViewer->Height - lpImageViewer->ScrollInfo.nPage;
			lpImageViewer->yScrollPos = max(0, min(lpImageViewer->yScrollPos, DeltaHeight));

			lpImageViewer->ScrollInfo.fMask = SIF_POS;
			lpImageViewer->ScrollInfo.nPos = lpImageViewer->yScrollPos;
			SetScrollInfo(hWnd, SB_VERT, &lpImageViewer->ScrollInfo, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		} return 0;


//		case WM_LBUTTONDOWN: {
//			DragDetect(hWnd, DragStartPoint);
//		} return 0;
//
//
//		case WM_MOUSEMOVE: {
//		} return 0;


		case WM_RBUTTONDOWN: {
		} break;


		case WM_KEYDOWN: {
			WORD wScrollNotify = 0xFFFF;


			switch (wParam) {
				case VK_UP:
					wScrollNotify = SB_LINEUP;
					break;

				case VK_PRIOR:
					wScrollNotify = SB_PAGEUP;
					break;

				case VK_NEXT:
					wScrollNotify = SB_PAGEDOWN;
					break;

				case VK_DOWN:
					wScrollNotify = SB_LINEDOWN;
					break;

				case VK_HOME:
					wScrollNotify = SB_TOP;
					break;

				case VK_END:
					wScrollNotify = SB_BOTTOM;
					break;

				default:
					break;
			} // End of Switch
		} // End of Switch


		case WM_MOUSEWHEEL: {
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			int DeltaHeight;


			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);


			// Calculate New Position
			lpImageViewer->yScrollPos -= zDelta / WHEEL_DELTA * SCROLL_INCREMENT;
			DeltaHeight = lpImageViewer->Height - lpImageViewer->ScrollInfo.nPage;
			lpImageViewer->yScrollPos = max(0, min(lpImageViewer->yScrollPos, DeltaHeight));


			// Update ScrollInfo
			lpImageViewer->ScrollInfo.fMask = SIF_POS;
			lpImageViewer->ScrollInfo.nPos = lpImageViewer->yScrollPos;
			SetScrollInfo(hWnd, SB_VERT, &lpImageViewer->ScrollInfo, TRUE);
			InvalidateRect(hWnd, NULL, TRUE);
		} return 0;


		case WM_DESTROY:
			lpImageViewer = (LPIMAGEVIEWER) GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			DeleteObject(lpImageViewer->hBitMap);
			free(lpImageViewer);
			PostQuitMessage(0);
			return 0;


		case WM_ERASEBKGND:
			return 1;

		default:
			break;
	} // End of Switch

	return DefWindowProcW(hWnd, Msg, wParam, lParam);
} // End of Function





extern LPIMAGEVIEWER NewImageViewer(void) {
	LPIMAGEVIEWER lpImageViewer;
	BITMAP TempBitMap;


	lpImageViewer = (LPIMAGEVIEWER) malloc(sizeof(IMAGEVIEWER));
	if (lpImageViewer == NULL) {
		MessageBoxW(NULL, L"Failed to allocate memory for lpImageViewer.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	lpImageViewer->hWnd = CreateWindowExW(WS_EX_CLIENTEDGE, L"ImageViewer", L"", WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_VSCROLL, 0, 0, 0, 0, hMainWindow, NULL, GetModuleHandleW(NULL), NULL);
	if (lpImageViewer->hWnd == NULL) {
		MessageBoxW(NULL, L"Failed to create lpImageViewer window.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	SetWindowTheme(lpImageViewer->hWnd, L" ", L" ");
	SetWindowLongPtrW(lpImageViewer->hWnd, GWLP_USERDATA, (LONG_PTR) lpImageViewer);
	lpImageViewer->hBitMap = LoadImageW(NULL, L"D:\\Desktop\\chen.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!lpImageViewer->hBitMap) {
		// #TODO: Determine if this should free used memory or not.
		MessageBoxW(NULL, L"Failed to load BitMap.", L"Error", MB_OK | MB_ICONERROR);
		return NULL;
	} // End of If


	// Get Width and Height
	GetObjectW(lpImageViewer->hBitMap, sizeof(TempBitMap), &TempBitMap);

	lpImageViewer->Width = TempBitMap.bmWidth;
	lpImageViewer->Height = TempBitMap.bmHeight;
	lpImageViewer->xScrollPos = 0;
	lpImageViewer->yScrollPos = 0;


	// Setup Both ScrollBars
	lpImageViewer->ScrollInfo.cbSize = sizeof(lpImageViewer->ScrollInfo);
	lpImageViewer->ScrollInfo.fMask = SIF_RANGE | SIF_PAGE;
	lpImageViewer->ScrollInfo.nMin = 0;


	// Setup Horizontal Scrollbar
	lpImageViewer->ScrollInfo.nMax = lpImageViewer->Width - 1;
	lpImageViewer->ScrollInfo.nPage = 100;
	SetScrollInfo(lpImageViewer->hWnd, SB_HORZ, &lpImageViewer->ScrollInfo, TRUE);


	// Setup Vertical ScrollBar
	lpImageViewer->ScrollInfo.nMax = lpImageViewer->Height - 1;
	lpImageViewer->ScrollInfo.nPage = 300;
	SetScrollInfo(lpImageViewer->hWnd, SB_VERT, &lpImageViewer->ScrollInfo, TRUE);

	return lpImageViewer;
} // End of Function





extern void RegisterImageViewerWindowClass(HINSTANCE hInstance) {
	WNDCLASSEXW WindowClass;

	// Register window class
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = ImageViewerWndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW);
	WindowClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	WindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_GUI);
	WindowClass.lpszClassName = L"ImageViewer";
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WindowClass)) {
		MessageBox(NULL, L"Failed to register main window class.", L"Error", MB_ICONEXCLAMATION | MB_OK);
	} // End of If
} // End of Function
