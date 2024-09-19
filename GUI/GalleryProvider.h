#ifndef GALLERY_H
#define GALLERY_H

#include "ImageViewer.h"

#include <Windows.h>
#include <WinUser.h>


typedef struct GalleryProvider {
	HWND hWnd;
	LPIMAGEVIEWER ImageViewer;
} GalleryProvider;

#endif
