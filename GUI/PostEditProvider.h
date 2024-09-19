#ifndef POST_EDIT_PROVIDER_H
#define POST_EDIT_PROVIDER_H

#include "LayoutBox.h"

#include <Windows.h>
#include <WinUser.h>




/**
 * #NOTE: Does not need a WndProc function.
 */
typedef struct PostEditProvider {
	/* ImageViewer
	 * Rating
	 *	Explicit
	 *	Questionable
	 *	Sensitive
	 *	Safe
	 * Artist Label
	 * Artist Edit
	 * Source Label
	 * Source Edit
	 * Tag Label
	 * Tag Edit
	 */
	LPLAYOUTBOX lpRootLayoutBox;
	LPIMAGEVIEWER ImageView;


	// Rating
	HWND hRatingLabel;
	LPLAYOUTBOX lpRadioLayoutBox;
	HWND hExplicitRadioBtn;
	HWND hQuestionableRadioBtn;
	HWND hSensitiveRadioBtn;
	HWND hSafeRadioBtn;


	// Labels and text boxes
	HWND hArtistLabel;
	HWND hArtistEdit;
	HWND hSourceLabel;
	HWND hSourceEdit;
	HWND hTagLabel;
	HWND hTagEntry;


	// Control buttons
	LPLAYOUTBOX lpControlBtnLayoutBox;
	HWND hSubmitBtn;
	HWND hCancelBtn;


	// Scroll controls
	SCROLLINFO ScrollInfo;
	int xScrollPos;
	int yScrollPos;
} POSTEDITPROVIDER, *LPPOSTEDITPROVIDER;





WNDCLASSEXW PostEditProviderRatingButtonSubClass;
extern LPPOSTEDITPROVIDER NewPostEditProvider(void);





#endif
