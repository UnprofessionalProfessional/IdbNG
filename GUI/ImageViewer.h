#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <Windows.h>
#include <WinUser.h>


typedef struct IMAGEVIEWER {
	HWND hWnd;
	HBITMAP hBitMap;
	PAINTSTRUCT PaintStruct;
	SCROLLINFO ScrollInfo;
	int xScrollPos;
	int yScrollPos;
	LONG Width;
	LONG Height;
} IMAGEVIEWER, *LPIMAGEVIEWER;





extern LPIMAGEVIEWER NewImageViewer(void);
extern void RegisterImageViewerWindowClass(HINSTANCE hInstance);





#endif
