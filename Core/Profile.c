#include "Core.h"
#include "PrivateCore.h"

#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <winerror.h>





static void CreateValues(HKEY hKey);





/**
 * Create the sub-directories needed for a profile.
 *
 * \param Path
 */
void CreateProfileInternal(LPCWSTR Path) {
	LPWSTR TempPath = NULL;
	size_t TempPathLength = 0;
	size_t PathLength = wcslen(Path);
	int Status = 0;



	// Create Media Directory
	TempPathLength = 7 + PathLength;
	AllocateMemory(&TempPath, TempPathLength, sizeof(wchar_t));
	swprintf_s(TempPath, TempPathLength, L"%s\\Media\0", Path);
	Status = SHCreateDirectoryExW(NULL, TempPath, NULL);
	printf("CreateProfileInternal: `%S'\n", TempPath);

	switch (Status) {
		case ERROR_SUCCESS:
		case ERROR_FILE_EXISTS:
		case ERROR_ALREADY_EXISTS:
			break;

		default:
			printf("\nCreateProfileInternal: Error 0x%02x: Could not create directory, %S\n", Status, TempPath);
			abort();
	} // End of Switch

	free(TempPath);
	TempPath = NULL;



	// Create Thumbs directory
	TempPathLength = 8 + PathLength;
	AllocateMemory(&TempPath, TempPathLength, sizeof(wchar_t));
	swprintf_s(TempPath, TempPathLength, L"%s\\Thumbs\0", Path);
	Status = SHCreateDirectoryExW(NULL, TempPath, NULL);
	printf("CreateProfileInternal: `%S'\n", TempPath);

	switch (Status) {
		case ERROR_SUCCESS:
		case ERROR_FILE_EXISTS:
		case ERROR_ALREADY_EXISTS:
			break;

		default:
			printf("\nCreateProfileInternal: Error 0x%02x: Could not create directory, %S\n", Status, TempPath);
			abort();
	} // End of Switch

	free(TempPath);
	TempPath = NULL;
	TempPathLength = 0;



	// Create thumbnail directories
	for (int I = 32; I < 1025; I *= 2) {
		TempPathLength = 9 + CountDigits(I) + PathLength;
		AllocateMemory(&TempPath, TempPathLength, sizeof(wchar_t));
		swprintf_s(TempPath, TempPathLength, L"%s\\Thumbs\\%d\0", Path, I);
		Status = SHCreateDirectoryExW(NULL, TempPath, NULL);
		printf("CreateProfileInternal: `%S'\n", TempPath);


		switch (Status) {
			case ERROR_SUCCESS:
			case ERROR_FILE_EXISTS:
			case ERROR_ALREADY_EXISTS:
				break;

			default:
				printf("\nCreateProfileInternal: Error 0x%02x: Could not create directory, %S\n", Status, TempPath);
				abort();
		} // End of Switch


		free(TempPath);
		TempPath = NULL;
	} // End of For

	printf("Created all directories.\n");
} // End of Function





/**
 * Create a new profile.
 *	Precondition: Path is an existing directory.
 *	Precondition: None of the arguments are NULL.
 *
 * \param Name: Name of the profile.
 * \param Path: Path to the profile. Use NULL to create in the default location.
 */
extern LSTATUS CreateProfile(LPCWSTR Name, LPCWSTR Path, LPCWSTR DatabaseName, LPCWSTR Username, LPCWSTR Password, LPDWORD SavePassword, LPCWSTR Address, LPDWORD Port) {
	LSTATUS Status;
	LPWSTR *KeyName;
	size_t NameLength = wcslen(Name);
	HKEY hKey;
	DWORD DefaultView = 32795;



	// Create Parent Key
	printf("%S\n", Path);
	AllocateMemory(&KeyName, (23 + NameLength), sizeof(wchar_t));
	swprintf_s(KeyName, 23 + NameLength, L"Software\\IDB\\Profiles\\%s\0", Name);
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, KeyName, 0, KEY_WRITE | KEY_READ | KEY_WOW64_64KEY | KEY_QUERY_VALUE, &hKey);

	if (Status != ERROR_SUCCESS) {
		printf("Could not open handle. Error code 0x%0x\n", Status);
	} // End of If

	switch (Status) {
		case ERROR_SUCCESS:
			break;

		case ERROR_FILE_NOT_FOUND:
			Status = RegCreateKeyW(HKEY_CURRENT_USER, KeyName, &hKey);
			break;

		default:
			return Status;
	} // End of Switch


	// Create DatabaseName
	Status = RegSetValueExW(hKey, L"DatabaseName", 0, REG_SZ, NULL, 0);
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create DefaultView
	Status = RegSetValueExW(hKey, L"DefaultView", 0, REG_DWORD, (const BYTE *) &DefaultView, sizeof(DefaultView));
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create ShowPreview
	DefaultView = 0;
	Status = RegSetValueExW(hKey, L"ShowPreview", 0, REG_DWORD, (const BYTE *) &DefaultView, sizeof(DefaultView));
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create SafeMode
	DefaultView = 0;
	Status = RegSetValueExW(hKey, L"SafeMode", 0, REG_DWORD, (const BYTE *) &DefaultView, sizeof(DefaultView));
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create ThumbSize
	DefaultView = 512;
	Status = RegSetValueExW(hKey, L"ThumbSize", 0, REG_DWORD, (const BYTE *) &DefaultView, sizeof(DefaultView));
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create Maximise
	DefaultView = 1;
	Status = RegSetValueExW(hKey, L"Maximise", 0, REG_DWORD, (const BYTE *) &DefaultView, sizeof(DefaultView));
	if (Status != ERROR_SUCCESS) {
		printf("Could not set value. Error code 0x%0x\n", Status);
	} // End of If


	// Create Storage Directory & Registry Value
	if (Path == NULL) {
		LPWSTR AppData;
		size_t AppDataLength;
		LPWSTR TempPath = NULL;
		size_t TempPathLength;



		// Create AppData path
		AppData = GetAppDataPath();
		AppDataLength = wcslen(AppData);

		printf("AppData: %S\n", AppData);
		Status = SHCreateDirectoryExW(NULL, AppData, NULL);
		switch (Status) {
			case ERROR_SUCCESS:
			case ERROR_FILE_EXISTS:
			case ERROR_ALREADY_EXISTS:
				break;

			default:
				printf("\nCreateProfileInternal: Error 0x%02x: Could not create directory, %S\n", Status, TempPath);
				abort();
		} // End of Switch



		// Create the new string
		TempPathLength = AppDataLength + NameLength + 2;
		AllocateMemory(&TempPath, TempPathLength, sizeof(wchar_t));
		swprintf_s(TempPath, TempPathLength, L"%s\\%s\0", AppData, Name);
		free(AppData);
		AppData = NULL;

		printf("TempPath: %S\n", TempPath);

		// Create the directory
		// What directory?
		Status = SHCreateDirectoryExW(NULL, TempPath, NULL);
		switch (Status) {
			case ERROR_SUCCESS:
			case ERROR_FILE_EXISTS:
			case ERROR_ALREADY_EXISTS:
				break;

			default:
				printf("\nCreateProfileInternal: Error 0x%02x: Could not create directory, %S\n", Status, TempPath);
				abort();
		} // End of Switch



		printf("TempPath: %S\n", TempPath);
		Status = RegSetValueExW(hKey, L"StoragePath", 0, REG_SZ, TempPath, TempPathLength * sizeof(wchar_t));
		if (Status != ERROR_SUCCESS) {
			printf("Could not set value. Error code 0x%0x\n", Status);
		} // End of If


		CreateProfileInternal(TempPath);
		free(TempPath);
		TempPath = NULL;
	} else {
		printf("%S, %zu\n", Path, wcslen(Path));
		CreateDirectoryW(Path, NULL);
		Status = RegSetValueExW(hKey, L"StoragePath", 0, REG_SZ, Path, wcslen(Path) * sizeof(wchar_t));
		if (Status != ERROR_SUCCESS) {
			printf("Could not set value. Error code 0x%0x\n", Status);
		} // End of If

		CreateProfileInternal(Path);
	} // End of If/Else


	RegCloseKey(hKey);
	free(KeyName);
	KeyName = NULL;
	return ERROR_SUCCESS;
} // End of Function
