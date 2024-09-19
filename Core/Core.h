#ifndef CORE_H
#define CORE_H

#include <Windows.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

// #TODO: Link against ImageMagick DLLs
#pragma comment(lib, "Shlwapi.lib")


enum TagTypes {
	Noun = 0,
	Verb = 1,
	Character = 2,
	Copyright = 3,
	Artist = 4,
	Meta = 5
};

enum Status {
	Active,
	Deleted,
	Expunged,
	Corrupted,
	FileMissing
};

LPWSTR ProfileName;


/**
 * Allocate memory to a variable.
 *	Precondition: Dest is NULL.
 *	Precondition: Size is not 0.
 *
 * \param Dest
 * \param Size
 */
extern void AllocateMemory(void **Dest, size_t Length, size_t Size);


/// <summary>
/// Concatenate an arbitrary number of strings.
/// </summary>
/// <param name="Destination">String containing all input strings.</param>
/// <param name="DestinationLength">Length of Destination in bytes.</param>
/// <param name="Input">Array of strings to be concatenated.</param>
/// <param name="Lengths">Array of string lengths, where the the element at a given index is the length of </param>
/// <param name="hWnd">Handle to the parent window</param>
extern void ConcatenateStringsW(LPWSTR *Destination, size_t *DestinationLength, LPCWSTR Input[], size_t Lengths[], HWND hWnd);


extern LSTATUS ConfigureDatabase(LPCWSTR DatabaseName, LPCWSTR Domain, LPCWSTR Password, LPDWORD SavePassword, LPDWORD Port, LPCWSTR Username);


extern LSTATUS ConnectInternal(LPCWSTR DatabaseName, LPCWSTR Domain, LPCTSTR Password, LPDWORD Port, LPCWSTR Username);


extern void ConvertUtf16ToUtf8(LPSTR *OutString, LPCWSTR InString);


extern size_t CountDigits(uint64_t Integer);


extern LSTATUS CreateProfile(LPCWSTR Name, LPCWSTR Path, LPCWSTR DatabaseName, LPCWSTR Username, LPCWSTR Password, LPDWORD SavePassword, LPCWSTR Address, LPDWORD Port);


extern void DbDisconnect(void);


// #TODO: Refactor this to write to a variable directly
extern LPWSTR GetAppDataPath(void);
extern LSTATUS GetDatabaseName(LPWSTR *DatabaseName, LPDWORD ValueLength);
extern LSTATUS GetDefaultView(LPDWORD DefaultView);
extern LSTATUS GetDomain(LPWSTR *Domain, LPDWORD ValueLength);
extern LSTATUS GetMaximise(LPDWORD Maximised);
extern LSTATUS GetPassword(LPWSTR *Password, LPDWORD ValueLength);
extern LSTATUS GetPort(LPDWORD Port);
extern LSTATUS GetSafeMode(LPDWORD SafeMode);
extern LSTATUS GetSavePassword(LPDWORD SavePassword);
extern LSTATUS GetShowPreview(LPDWORD PreviewSize);
extern LSTATUS GetStoragePath(LPWSTR *PathBuffer, LPDWORD ValueLength);
extern LSTATUS GetThumbSize(LPDWORD ThumbSize);
extern LSTATUS GetUsername(LPWSTR *Username, LPDWORD ValueLength);

extern LSTATUS SetAppDataPath(LPCWSTR AppDataPath);
extern LSTATUS SetDatabaseName(LPCWSTR DatabaseName);
extern LSTATUS SetDefaultView(DWORD DefaultView);
extern LSTATUS SetDomain(LPCWSTR Domain);
extern LSTATUS SetMaximise(DWORD Maximised);
extern LSTATUS SetPassword(LPCWSTR Password);
extern LSTATUS SetPortDb(DWORD Port);
extern LSTATUS SetSafeMode(DWORD SafeMode);
extern LSTATUS SetSavePassword(DWORD SavePassword);
extern LSTATUS SetUsername(LPCWSTR Username);
extern LSTATUS SetShowPreview(DWORD PreviewSize);
extern LSTATUS SetStoragePath(LPCWSTR PathBuffer);
extern LSTATUS SetThumbSize(DWORD ThumbSize);


/**
 * Calculate the SHA256 hash of arbitrary data.
 *
 * \param Hash: Pointer to a string containing the hash.
 * \param Data: Byte string to be hashed.
 * \param Length: Length of Data in bytes.
 */
extern void GetSHA256(char **Hash, const char *Data, size_t Length);


EXTERNC char *GetImageFormat(const char *Path);


EXTERNC extern size_t GetImageHeight(const char *FilePath);


EXTERNC extern size_t GetImageWidth(const char *FilePath);


EXTERNC extern void InitialiseMagick(void);


extern LSTATUS InitialiseCore(void);


/// <summary>
/// Parse the status code of a PostgreSQL command, with a MessageBox.
/// </summary>
/// <param name="StatusCode">Code returned from PQexecStatus.</param>
/// <param name="hWnd">Handle to the parent window.</param>
/// <param name="AddendumMessage">Message to be added after the built-in message.</param>
/// <returns></returns>
extern BOOL ParseCommandStatusEx(int StatusCode, HWND hWnd, LPCWSTR AddendumMessage);


extern LSTATUS SetDefaultProfile(LPCWSTR ProfileName);




extern LSTATUS InitialiseRegistry(void);


EXTERNC void TerminateMagick(void);


extern bool DbTest(void);


 #endif // CORE_H
