#include "Core.h"

#include <math.h>
#include <sha-256.h>
#include <stdio.h>





extern HKEY hProfileKey;
extern LPWSTR ProfileName;




/**
 * Allocate memory to a variable.
 *	Precondition: Dest is NULL.
 *	Precondition: Length is not 0.
 *
 * \param Dest
 * \param Length
 * \param Size: Size of each element
 */
extern void AllocateMemory(void **Dest, size_t Length, size_t Size) {
	DWORD Status;

	Length *= Size;
	printf("Requesting %zu B\n", Length);
	if (Dest == NULL) {
		printf("\nError: Destination pointer is NULl.");
		abort();
	}


	// First attempt
	*Dest = malloc(Length);
	Status = GetLastError();
	if (*Dest == NULL) {
		printf("AllocateMemory: Error: Could not allocate memory. Error code: %0x\n", Status);
	} // End of If


	printf("Allocated %zu B\n\n", Length);
} // End of Function





/// <summary>
/// Concatenate an arbitrary number of strings.
/// </summary>
/// <param name="Destination">String containing all input strings.</param>
/// <param name="DestinationLength">Length of Destination in bytes.</param>
/// <param name="Input">Array of strings to be concatenated.</param>
/// <param name="Lengths">Array of string lengths, where the the element at a given index is the length of </param>
/// <param name="hWnd">Handle to the parent window</param>
extern void ConcatenateStringsW(LPWSTR *Destination, size_t *DestinationLength, LPCWSTR Input[], size_t Lengths[], HWND hWnd) {
	size_t InputCount = sizeof(Input) / sizeof(Input[0]);
	size_t LengthsCount = sizeof(Lengths) / sizeof(Lengths[0]);


	// 1. Check if Input and Lengths have the same number of elements
	if (InputCount != LengthsCount) {
		MessageBoxW(hWnd, L"The arrays, Input and Lengths must have the same number of elements for concatenation to be successful.", L"Data Error", MB_OK | MB_ICONERROR);
		*Destination = NULL;
		*DestinationLength = 0;
		return;
	} // End of If


	// 2. Calculate number of characters
	for (size_t I = 0; I < LengthsCount; I++) {
		*DestinationLength += Lengths[I];
	} // End of For


	// 3. Allocate memory for *Destionation
	(*DestinationLength)++;
	AllocateMemory(Destination, *DestinationLength, sizeof(wchar_t));


	// 4. Concatenate Strings
	for (size_t I = 0; I < InputCount; I++) {
		// #TODO: Check the return code
		wcscat_s(Destination, *DestinationLength, Input[I]);
	} // End of For

	// Zero-Terminate String
	wcscat_s(Destination, *DestinationLength, "\0");
} // End of Function





/// <summary>
/// Convert a UTF-16 string to a UTF-8 string.
/// #TODO: Check what happens when Utf8StringLength is < 0
/// </summary>
/// <param name="OutString">Buffer to write the UTF-8 string to.</param>
/// <param name="InString">UTF-16 string to be converted.</param>
extern void ConvertUtf16ToUtf8(LPSTR *OutString, LPCWSTR InString) {
	int Utf8StringLength;


	Utf8StringLength = WideCharToMultiByte(CP_UTF8, 0, InString, -1, NULL, 0, NULL, NULL);
	AllocateMemory(OutString, Utf8StringLength, sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, InString, -1, *OutString, Utf8StringLength, NULL, NULL);
} // End of Function





extern size_t CountDigits(uint64_t Integer) {
	size_t Digits = 0;

	if (Integer == 0) {
		return 1;
	} // End of If

	if (Integer < 0) {
		Integer = abs(Integer);
		Digits++;
	} // End of If

	while (Integer != 0) {
		Integer /= 10;
		Digits++;
	} // End of While

	return Digits;
} // End of Function





extern LPWSTR GetAppDataPath(void) {
	LPWSTR AppDataPath;
	size_t AppDataLength = 0;
	LPWSTR FullPath;


	printf("GetAppDataPath\n");
	if (_wdupenv_s(&AppDataPath, &AppDataLength, L"LOCALAPPDATA") != 0) {
		fprintf(stderr, "GetApPDataPath: Error: Could not get %%LOCALAPPDATA%% environment variable.");
		abort();
	} // End of If

	AllocateMemory(&FullPath, AppDataLength + 8, sizeof(wchar_t));
	swprintf_s(FullPath, AppDataLength + 8, L"%s\\IDB\\v2\0", AppDataPath);
	free(AppDataPath);
	AppDataPath = NULL;

	return FullPath;
} // End of Function





/**
 * Calculate the SHA256 hash of arbitrary data.
 *
 * \param Hash: Pointer to a string containing the hash.
 * \param Data: Byte string to be hashed.
 * \param Length: Length of Data in bytes.
 */
extern void GetSHA256(char **Hash, const char *Data, size_t Length) {
	uint8_t Raw[32]; // Raw SHA256 data

	calc_sha_256(Raw, Data, Length);
	hash_to_string(Hash, Raw);
} // End of Function





/**
 * Prepare IDB for using the Registry.
 *
 * \return ERROR_SUCCESS if no errors were encountered. ERROR_FILE_NOT_FOUND if the default profile's key could not be found. ERROR_NOT_FOUND if the DefaultProfile value could not be found.
 */
extern LSTATUS InitialiseCore(void) {
	LSTATUS Status;
	LPWSTR ProfileName = NULL;
	DWORD ProfileNameLength = 0;
	LPWSTR ProfileKeyPath = NULL;
	DWORD ProfileKeyPathLength = 0;
	DWORD ValueType = 0;



	// Open IDB key
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\IDB\\Profiles", 0, KEY_READ | KEY_WOW64_64KEY | KEY_WRITE | KEY_QUERY_VALUE, &hProfileKey);
	printf("InitialiseCore RegOpenKeyExW: 0x%02x\n", Status);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If



	// Get default profile length
	Status = RegQueryValueExW(hProfileKey, L"DefaultProfile", NULL, &ValueType, NULL, &ProfileNameLength);
	if (Status != ERROR_SUCCESS) {
		printf("RegQueryValueExW error\n");
		return Status;
	} // End of If

	if (ProfileNameLength == 0) {
		printf("InitialiseCore: Error: No default profile.\n");
		return ERROR_NOT_FOUND;
	} // End of If



	// Get default profile name
	AllocateMemory(&ProfileName, ProfileNameLength, sizeof(wchar_t));
	Status = RegQueryValueExW(hProfileKey, L"DefaultProfile", NULL, &ValueType, (LPBYTE) ProfileName, &ProfileNameLength);
	if (Status != ERROR_SUCCESS) {
		printf("RegQueryValueExW error\n");
		return Status;
	} // End of If


	if (ProfileName == NULL) {
		printf("InitialiseCore: Error: No default profile.\n");
		return ERROR_NOT_FOUND;
	} // End of If

	RegCloseKey(hProfileKey);


	printf("PNL: %lu\n", ProfileNameLength);
	printf("Profile Name: `%S'\n", ProfileName);



	// Generate ProfileKeyPath
	ProfileKeyPathLength = ProfileNameLength + 23;
	AllocateMemory(&ProfileKeyPath, ProfileKeyPathLength, sizeof(wchar_t));
	swprintf_s(ProfileKeyPath, ProfileKeyPathLength, L"SOFTWARE\\IDB\\Profiles\\%s\0", ProfileName);
	printf("PKP: %S\n", ProfileKeyPath);



	// Open Profile key
	Status = RegOpenKeyExW(HKEY_CURRENT_USER, ProfileKeyPath, 0, KEY_READ | KEY_WOW64_64KEY | KEY_WRITE | KEY_QUERY_VALUE, &hProfileKey);
	if (Status != ERROR_SUCCESS) {
		return Status;
	} // End of If



	return ERROR_SUCCESS;
} // End of Function
