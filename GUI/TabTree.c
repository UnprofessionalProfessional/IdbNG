#include "GUI.h"





extern LPTABTREE TabRoot;
extern LPTABTREE CurrentTab;
extern BOOL CurrentTabInitialised;





extern void InitialiseTab(LPTABTREE *lTab) {
	*lTab = (LPTABTREE) malloc(sizeof(TABTREE));
	if (*lTab == NULL) {
		MessageBoxW(NULL, L"null", L"", MB_OK);
	} // End of If

	(*lTab)->hWnd = NULL;
//	(*lTab)->Tab = NULL;
//	(*lTab)->Name = NULL;
//	(*lTab)->Next = NULL;
//	(*lTab)->Previous = NULL;
} // End of Function