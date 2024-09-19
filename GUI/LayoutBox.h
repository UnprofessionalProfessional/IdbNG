#ifndef LAYOUT_BOX_H
#define LAYOUT_BOX_H


#include "TabTree.h"

#include <Windows.h>
#include <WinUser.h>
#include <stdint.h>





#define LB_HORIZONTAL FALSE
#define LB_VERTICAL TRUE
typedef struct WndBox {
	HWND hWnd;
	int LeftPadding;
	int RightPadding;
	int TopPadding;
	int BottomPadding;
	int Width;
	int Height;
	struct WndBox *Next;
} WNDBOX, *LPWNDBOX;


typedef struct LayoutBox {
	HWND hWnd;
	BOOL Direction;
	LPWNDBOX lpFirstChild;
} LAYOUTBOX, *LPLAYOUTBOX;





/// <summary>
/// Add a sub-window to an LPLAYOUTBOX.
/// #TODO: Implement horizontal
/// </summary>
/// <param name="lpLayoutBox">The target LPLAYOUTBOX.</param>
/// <param name="hChild">The window to be to lpLayoutBox</param>
/// <param name="LeftPadding">White space between hChild and the left border.</param>
/// <param name="RightPadding">White space between hChild and the right border.</param>
/// <param name="TopPadding">White space above hChild. Must be >= 0.</param>
/// <param name="BottomPadding">White space below hChild. Must be >= 0.</param>
/// <param name="Width">Width of hChild. Use -1 occupy all space on the X-axis, minus the left- and right-padding.</param>
/// <param name="Height">Height of hChild.</param>
extern void AddChildToLayoutBox(LPLAYOUTBOX lpLayoutBox, HWND hChild, int LeftPadding, int RightPadding, int TopPadding, int BottomPadding, int Width, int Height);


extern LPLAYOUTBOX NewLayoutBox(BOOL Direction);


extern void UpdateLayoutBox(LPLAYOUTBOX lpLayoutBox);


extern void RegisterLayoutBoxWindowClass(HINSTANCE hInstance);






#endif
