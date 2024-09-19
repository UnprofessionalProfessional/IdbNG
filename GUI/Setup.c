#include "GUI.h"





extern DWORD CurrentView;
extern DWORD Maximise;
extern DWORD SafeMode;
extern DWORD ShowPreview;
extern LPWSTR StoragePath;
extern DWORD ThumbSize;





extern void Setup(HWND hWnd) {
	LSTATUS Status;
	LPWSTR ErrorMessage = NULL;
	DWORD StoragePathLength = 0;



	// Initialise the Registry
	Status = InitialiseRegistry();
	if (Status != ERROR_SUCCESS) {
		// Convert Status to ErrorMessage
		MessageBoxW(hWnd, L"Could not initialise the Registry.", L"Error", MB_OK | MB_ICONERROR);
		return;
	} // End of If



	// Initialise the core
RetryInit:
	Status = InitialiseCore();
	switch (Status) {
		case ERROR_FILE_NOT_FOUND:
			/* DefaultProfile value exists, but key does not */
			break;

		case ERROR_NOT_FOUND:
			/* DefaultProfile value does not exist, no profiles known. */
			break;

		default:
			// Convert Status to ErrorMessage
			printf("InitialiseCore: 0x%02x\n", Status);
			break;
	} // End of Switch



	InitialiseMagick();
	GetDefaultView(&CurrentView);
	GetMaximise(&Maximise);
	GetSafeMode(&SafeMode);
//	GetShowPreview(&ShowPreview);
	GetStoragePath(&StoragePath, &StoragePathLength);
	GetThumbSize(&ThumbSize);
} // End of Function





extern void SetupDatabase(HWND hWnd) {
	LPWSTR DatabaseName = NULL;
	DWORD DatabaseNameLength = 0;
	LPWSTR Domain = NULL;
	DWORD DomainLength = 0;
	LPWSTR Password = NULL;
	DWORD PasswordLength = 0;
	LPWSTR Username = NULL;
	DWORD UsernameLength = 0;
	DWORD Port = 0;
	DWORD SavePassword = 0;
	LSTATUS Status;


	Status = GetDatabaseName(&DatabaseName, &DatabaseNameLength);
	Status = GetDomain(&Domain, &DomainLength);
	Status = GetPassword(&Password, &PasswordLength);
	Status = GetUsername(&Username, &UsernameLength);
	Status = GetPort(&Port);
	Status = GetSavePassword(&SavePassword);


	// Check if the password is NULL or SavePassword is 0
	if (Password == NULL || PasswordLength == 0 || SavePassword == 0) {
		// #TODO: Prompt the user for a password
		MessageBoxW(hWnd, L"Please enter your database password to continue.", L"IDB Authentication", MB_OK | MB_ICONWARNING);
	} // End of If


	// #TODO Check if the required variables are valid
	// For now, we'll just assume that everything is correct.


	// Connect to the database
	Status = ConnectInternal(DatabaseName, Domain, Password, &Port, Username);
	if (Status == ERROR_SUCCESS) {
//		MessageBoxW(NULL, L"Successfully connected to the database.", L"Notice", MB_OK | MB_ICONINFORMATION);
		SendMessage(hStatusBar, SB_SETTEXTW, 0, (LPARAM) L"Connected");
	} // End of If
} // End of Function
