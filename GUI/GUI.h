#ifndef GUI_H
#define GUI_H

#define _WIN64
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "uxtheme.lib")

#include "resource.h"

#include "GalleryProvider.h"
#include "PostEditProvider.h"
#include "ImageViewer.h"
#include "Importer.h"
#include "LayoutBox.h"
#include "TabTree.h"

#include <Windows.h>
#include <WinUser.h>
#include <commctrl.h>
#include <Uxtheme.h>
#include <Core.h>





DWORD CurrentView;
DWORD Maximise;
DWORD SafeMode;
DWORD ShowPreview;
LPWSTR StoragePath;
DWORD ThumbSize;

#define WM_POSTCREATE (WM_USER + 1)
// #TODO: Move the preview to inside subwindows
// #TODO: Rename the preview window to hCurrentPreview
// #TODO: Create NewTag dialogue
// Provider Flags
#define PROVIDER_GALLERY	0b1
#define PROVIDER_IMPORT		0b10
#define PROVIDER_LIST		0b100
#define PROVIDER_OPTIONS	0b1000
#define PROVIDER_POST		0b10000
#define PROVIDER_WIKI		0b100000
#define PROVIDER_LAYOUT_VIEW	0b1000000
#define PROVIDER_ARTSIT		0b10000000
#define PROVIDER_		0b100000000

// Lower 32 bits are for flags, upper are for type ID
#define VIEW_ARTISTS		1
#define VIEW_ARTIST		2
#define VIEW_GALLERY		3
#define VIEW_IMPORTER		4
#define VIEW_OPTIONS		5
#define VIEW_POOLS		6
#define VIEW_POST		7
#define VIEW_RECYCLE_BIN	8
#define VIEW_TAGS		9
#define VIEW_			10
#define VIEW_			11
#define VIEW_			12
#define VIEW_			13
#define VIEW_WIKI		14

DWORD StatusBarHeight;
DWORD SearchHeight;
DWORD TreeViewWidth;


HWND hCurrentTab;
HWND hMainWindow;
HWND hSearchBox;
HWND hStatusBar;
HWND hTabTree;

LPTABTREE TabRoot;
LPTABTREE CurrentTab;
BOOL CurrentTabInitialised;





BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
extern void CheckMenu(WORD bMenuItemId, HMENU hMenu);
extern void CheckPreview(HMENU hMenu);
extern void CheckPreviewEx(HMENU hMenu, DWORD Value);
extern void CheckSafeMode(HMENU hMenu);
extern void CheckSafeModeEx(HMENU hMenu, DWORD Value);
extern void CheckThumbnailSize(HMENU hMenu, DWORD Value);
extern HWND CreateSearchBox(HWND hParent);
extern HWND CreateStatusBar(HWND hParent);
extern HWND CreateTreeView(HWND hParent);
BOOL CALLBACK DbConfigDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
extern void InitialiseTab(LPTABTREE *lTab);
extern void RegisterGalleryProviderClass(HINSTANCE hInstance);
extern void SetCurrentView(WPARAM ViewType);
extern void Setup(HWND hWnd);
extern void SetupDatabase(HWND hWnd);
extern void UpdateCurrentTab(void);
extern void UpdateSearchBoxPosition(HWND hWnd, HWND hParent);
extern void UpdateStatusBarPosition(HWND hWnd, HWND hParent);
extern void UpdateTreeViewPosition(HWND hChild, HWND hParent);
extern void UpdateWindowPosition(HWND hParent, HWND hChild, int X, int Y, int Width, int Height, BOOL HzExpand, BOOL VtExpand);
extern LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);





#endif
