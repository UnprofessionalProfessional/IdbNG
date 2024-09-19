#ifndef TAB_TREE_H
#define TAB_TREE_H


#include <Windows.h>
#include <WinUser.h>





/**
 * #NOTE: Does not need a WndProc function, since that is handled by Tab.
 */
typedef struct TabTree {
	HWND hWnd;
	void *Tab;
	LPWSTR Name;
	void *Next;
	void *Previous;
	DWORD Type;
} TABTREE, *LPTABTREE;

typedef struct IdbFolder {
	struct IdbFolder *Parent;
	void *Child;
	LPWSTR Name;
	void *Next;
	void *Previous;
} IDBFOLDER, *LPIDBFOLDER;





#endif
