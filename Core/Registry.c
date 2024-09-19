#include "Core.h"
#include "PrivateCore.h"





extern LSTATUS GetDatabaseName(LPWSTR *DatabaseName, LPDWORD ValueLength) {
	DWORD ValueType = REG_SZ;
	LSTATUS Status;



	Status = RegQueryValueExW(hProfileKey, L"DatabaseName", NULL, &ValueType, NULL, ValueLength);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	AllocateMemory(DatabaseName, *ValueLength, sizeof(wchar_t));
	return RegQueryValueExW(hProfileKey, L"DatabaseName", NULL, &ValueType, (LPBYTE) *DatabaseName, ValueLength);
} // End of Function





extern LSTATUS GetDefaultView(LPDWORD DefaultView) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"DefaultView", NULL, &ValueType, DefaultView, &ValueLength);
} // End of Function





extern LSTATUS GetDomain(LPWSTR *Domain, LPDWORD ValueLength) {
	DWORD ValueType = REG_SZ;
	LSTATUS Status;



	Status = RegQueryValueExW(hProfileKey, L"Domain", NULL, &ValueType, NULL, ValueLength);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	AllocateMemory(Domain, *ValueLength, sizeof(wchar_t));
	return RegQueryValueExW(hProfileKey, L"Domain", NULL, &ValueType, (LPBYTE) *Domain, ValueLength);
} // End of Function




extern DWORD GetMaximise(LPDWORD Maximise) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"Maximise", NULL, &ValueType, Maximise, &ValueLength);
} // End of Function





extern LSTATUS GetPassword(LPWSTR *Password, LPDWORD ValueLength) {
	DWORD ValueType = REG_SZ;
	LSTATUS Status;



	Status = RegQueryValueExW(hProfileKey, L"Password", NULL, &ValueType, NULL, ValueLength);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	AllocateMemory(Password, *ValueLength, sizeof(wchar_t));
	return RegQueryValueExW(hProfileKey, L"Password", NULL, &ValueType, (LPBYTE) *Password, ValueLength);
} // End of Function





extern LSTATUS GetPort(LPDWORD Port) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"Port", NULL, &ValueType, Port, &ValueLength);
} // End of Function





extern LSTATUS GetSafeMode(LPDWORD SafeMode) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"SafeMode", NULL, &ValueType, SafeMode, &ValueLength);
} // End of Function





extern LSTATUS GetSavePassword(LPDWORD SavePassword) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"SavePassword", NULL, &ValueType, SavePassword, &ValueLength);
} // End of Function





extern LSTATUS GetShowPreview(LPDWORD PreviewSize) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"ShowPreview", NULL, &ValueType, PreviewSize, &ValueLength);
} // End of Function





extern LSTATUS GetStoragePath(LPWSTR *PathBuffer, LPDWORD ValueLength) {
	DWORD ValueType = REG_SZ;
	LSTATUS Status;


	Status = RegQueryValueExW(hProfileKey, L"StoragePath", NULL, &ValueType, NULL, ValueLength);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	AllocateMemory(PathBuffer, *ValueLength, sizeof(wchar_t));
	return RegQueryValueExW(hProfileKey, L"StoragePath", NULL, &ValueType, (LPBYTE) *PathBuffer, ValueLength);
} // End of Function





extern LSTATUS GetThumbSize(LPDWORD ThumbSize) {
	DWORD ValueLength = sizeof(DWORD);
	DWORD ValueType = REG_DWORD;


	return RegQueryValueExW(hProfileKey, L"ThumbSize", NULL, &ValueType, ThumbSize, &ValueLength);
} // End of Function





extern LSTATUS GetUsername(LPWSTR *Username, LPDWORD ValueLength) {
	DWORD ValueType = REG_SZ;
	LSTATUS Status;


	Status = RegQueryValueExW(hProfileKey, L"Username", NULL, &ValueType, NULL, ValueLength);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	AllocateMemory(Username, *ValueLength, sizeof(wchar_t));
	return RegQueryValueExW(hProfileKey, L"Username", NULL, &ValueType, (LPBYTE) *Username, ValueLength);
} // End of Function





// #TODO: Refactor this
extern LSTATUS InitialiseRegistry(void) {
	PHKEY IdbKey;
	LSTATUS Status;
	int ret;



	/* Check if Key exists */
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\IDB\\Profiles", 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &IdbKey);

	if (Status == ERROR_SUCCESS) {
		return ERROR_SUCCESS;
	} // End of If

	if (Status == ERROR_FILE_NOT_FOUND) {
		// Create IdbKey
		Status = RegCreateKeyW(HKEY_CURRENT_USER, L"Software\\IDB", &IdbKey);
		switch (Status) {
			case ERROR_SUCCESS:
			case ERROR_FILE_EXISTS:
				break;

			default:
				return Status;
		} // End of Switch


		// Create Profiles Key
		Status = RegCreateKeyW(HKEY_CURRENT_USER, L"Software\\IDB\\Profiles", &IdbKey);
		switch (Status) {
			case ERROR_SUCCESS:
			case ERROR_FILE_EXISTS:
				break;

			default:
				return Status;
		} // End of Switch
	} // End of If



	// Open the key, second pass
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\IDB\\Profiles", 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &IdbKey);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If


	// Create DefaultProfile Value
	printf("Creating DefaultProfile\n");
	Status = RegSetValueExW(IdbKey, L"DefaultProfile", NULL, REG_SZ, NULL, 0);


	Status = RegCloseKey(IdbKey);

	return Status;
} // End of Function





extern LSTATUS SetDefaultProfile(LPCWSTR ProfileName) {
	LSTATUS Status;
	HKEY hTempProfile;


	// Check if profile exists
	Status = RegOpenKeyExW(hProfileKey, ProfileName, 0, KEY_READ | KEY_QUERY_VALUE, &hTempProfile);
	if (Status == ERROR_FILE_NOT_FOUND || Status == ERROR_NOT_FOUND) {
		return Status;	// TODO: Find a suitable error code
	} // End of If


	// Open Profiles key
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\IDB\\Profiles", 0, KEY_READ | KEY_WRITE | KEY_QUERY_VALUE, &hTempProfile);


	Status = RegSetValueExW(hTempProfile, L"DefaultProfile", NULL, REG_SZ, ProfileName, (wcslen(ProfileName) + 1) * sizeof(wchar_t));
	return Status;
} // End of Function





// WTH? Where is this supposed to be used?
extern LSTATUS SetAppDataPath(LPCWSTR AppDataPath) {
	return RegSetValueExW(hProfileKey, L"", NULL, REG_SZ, AppDataPath, (wcslen(AppDataPath) +1) * sizeof(wchar_t));
} // End of Function





extern LSTATUS SetDatabaseName(LPCWSTR DatabaseName) {
	return RegSetValueExW(hProfileKey, L"DatabaseName", NULL, REG_SZ, DatabaseName, (wcslen(DatabaseName) + 1) * sizeof(DWORD));
} // End of Function





extern LSTATUS SetDefaultView(DWORD DefaultView) {
	return RegSetValueExW(hProfileKey, L"DefaultView", NULL, REG_DWORD, &DefaultView, sizeof(DWORD));
} // End of Function





extern LSTATUS SetDomain(LPCWSTR Domain) {
	return RegSetValueExW(hProfileKey, L"Domain", NULL, REG_SZ, Domain, (wcslen(Domain) + 1) * sizeof(DWORD));
} // End of Function





extern LSTATUS SetMaximise(DWORD Maximised) {
	return RegSetValueExW(hProfileKey, L"Maximise", NULL, REG_DWORD, &Maximised, sizeof(DWORD));
} // End of Function





extern LSTATUS SetPassword(LPCWSTR Password) {
	return RegSetValueExW(hProfileKey, L"Password", NULL, REG_SZ, Password, (wcslen(Password) + 1) * sizeof(DWORD));
} // End of Function




extern LSTATUS SetPortDb(DWORD Port) {
	return RegSetValueExW(hProfileKey, L"Port", NULL, REG_DWORD, &Port, sizeof(DWORD));
} // End of Function





extern LSTATUS SetSafeMode(DWORD SafeMode) {
	return RegSetValueExW(hProfileKey, L"SafeMode", NULL, REG_DWORD, &SafeMode, sizeof(DWORD));
} // End of Function




extern LSTATUS SetSavePassword(DWORD SavePassword) {
	return RegSetValueExW(hProfileKey, L"SavePassword", NULL, REG_DWORD, &SavePassword, sizeof(DWORD));
} // End of Function





extern LSTATUS SetShowPreview(DWORD ShowPreview) {
	return RegSetValueExW(hProfileKey, L"ShowPreview", NULL, REG_DWORD, &ShowPreview, sizeof(DWORD));
} // End of Function





extern LSTATUS SetStoragePath(LPCWSTR StoragePath) {
	return RegSetValueExW(hProfileKey, L"StoragePath", NULL, REG_SZ, StoragePath, (wcslen(StoragePath) +1) * sizeof(wchar_t));
} // End of Function





extern LSTATUS SetThumbSize(DWORD ThumbSize) {
	return RegSetValueExW(hProfileKey, L"ThumbSize", NULL, REG_DWORD, &ThumbSize, sizeof(DWORD));
} // End of Function





extern LSTATUS SetUsername(LPCWSTR Username) {
	return RegSetValueExW(hProfileKey, L"Username", NULL, REG_SZ, Username, (wcslen(Username) +1) * sizeof(wchar_t));
} // End of Function
