#include <Core.h>
#include "resource.h"





static LSTATUS DbConfigSubmit(HWND hWnd);





// About
BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case IDOK:
					EndDialog(hWnd, IDOK);
					return TRUE;

				case IDCANCEL:
					EndDialog(hWnd, IDCANCEL);
					return TRUE;

				default:
					break;
			} // End of Switch
		} break;

		default:
			return FALSE;
	} // End of Switch

	return FALSE;
} // End of Function

// New profile





// Database configuration
BOOL CALLBACK DbConfigDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hWnd, IDC_EDIT_DBNAME));
			return TRUE;

		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case IDC_BUTTON_OK:
					DbConfigSubmit(hWnd);
					EndDialog(hWnd, IDOK);
					break;

				case IDC_BUTTON_CANCEL:
					EndDialog(hWnd, IDCANCEL);
//					return TRUE;	// Should this be FALSE?
					break;

				case IDC_DATABASE_LABEL:
					printf("Set focus DATABASE\n");
					SetFocus(IDC_EDIT_DBNAME);
					break;

				case IDC_USERNAME_LABEL:
					printf("Set focus USERNAME\n");
					SetFocus(IDC_EDIT_USERNAME);
					break;

				case IDC_PASSWORD_LABEL:
					printf("Set focus PASSWORD\n");
					SetFocus(IDC_EDIT_PASSWORD);
					break;

				case IDC_DOMAIN_LABEL:
					printf("Set focus DOMAIN\n");
					SetFocus(IDC_EDIT_DOMAIN);
					break;

				case IDC_PORT_LABEL:
					printf("Set focus PORT\n");
					SetFocus(IDC_EDIT_PORT);
					break;

				default:
					break;
			} // End of Switch
		} break;

		default:
			return FALSE;
	} // End of Switch

	return FALSE;
} // End of Function





static LSTATUS DbConfigSubmit(HWND hWnd) {
	LSTATUS Status;
	LPWSTR Domain = NULL;
	int DomainLength = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_EDIT_DOMAIN)) + 1;
	LPWSTR DatabaseName = NULL;
	int DatabaseNameLength = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_EDIT_DBNAME)) + 1;
	LPWSTR Password = NULL;
	int PasswordLength = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_EDIT_PASSWORD)) + 1;
	DWORD Port = 5432;
	LPWSTR PortString = NULL;
	int PortStringLength = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_EDIT_PORT)) + 1;
	DWORD SavePassword = 1;	// #TODO: Add a check button to the dialogue
	LPWSTR Username = NULL;
	int UsernameLength = GetWindowTextLengthW(GetDlgItem(hWnd, IDC_EDIT_USERNAME)) + 1;



	// Get Values from dialogue
	AllocateMemory(&Domain, DomainLength, sizeof(wchar_t));
	AllocateMemory(&DatabaseName, DatabaseNameLength, sizeof(wchar_t));
	AllocateMemory(&Password, PasswordLength, sizeof(wchar_t));
	AllocateMemory(&PortString, PortStringLength, sizeof(wchar_t));
	AllocateMemory(&Username, UsernameLength, sizeof(wchar_t));

	GetDlgItemTextW(hWnd, IDC_EDIT_DOMAIN, Domain, DomainLength);
	GetDlgItemTextW(hWnd, IDC_EDIT_DBNAME, DatabaseName, DatabaseNameLength);
	GetDlgItemTextW(hWnd, IDC_EDIT_PASSWORD, Password, PasswordLength);
	GetDlgItemTextW(hWnd, IDC_EDIT_PORT, PortString, PortStringLength);
	GetDlgItemTextW(hWnd, IDC_EDIT_USERNAME, Username, UsernameLength);


	// #TODO: Generate sane defaults


	// Convert port


	printf("Stop here\n");
	Status = ConfigureDatabase(DatabaseName, Domain, Password, SavePassword, Port, Username);
	Status = ConnectInternal(DatabaseName, Domain, Password, Port, Username);	// idk if these need &


	// Clean memory
	free(DatabaseName);
	free(Domain);
	free(Password);
	free(Username);

	DatabaseName = NULL;
	Domain = NULL;
	Password = NULL;
	Username = NULL;


	return Status;
} // End of Function
