#ifndef IMPORTER_H
#define IMPORTER_H

#include "GUI.h"
#include "PostEditProvider.h"





/**
 * #NOTE: Does not need a WndProc function.
 * #TODO: Remove the class for this window
 */
typedef struct Importer {
	LPPOSTEDITPROVIDER PostEditor;
	HWND hPathLabel;
	HWND hPathEdit;
	HWND hFolderPickerBtn;
} IMPORTER, *LPIMPORTER;





extern LPTABTREE NewImportView(void);
extern void RegisterImporterWindowClass(HINSTANCE hInstance);





#endif
