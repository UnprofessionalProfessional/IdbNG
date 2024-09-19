#include "Core.h"
#include "PrivateCore.h"






/// <summary>
/// Add a tag to the database.
/// </summary>
/// <param name="TagName">Name of the tag, without square brackets.</param>
/// <param name="TagType">Type ID of the tag, from enum TagTypes.</param>
/// <param name="Enumerate">If TRUE, the tag is enumerable, otherwise it is not. See [TBD] for more details.</param>
/// <param name="hWnd">Handle to the parent window.</param>
/// <returns></returns>
extern LSTATUS CreateTag(LPCWSTR TagName, int TagType, BOOL Enumerate, HWND hWnd) {
	PGresult *Result;


	// 1. Check if the tag exists
	Result = PQexecParams(Conn, "SELECT EXISTS(SELECT id FROM public.tags WHERE name = $1);", 1, NULL, (const char *const *) { TagName }, NULL, NULL, 0);
	ParseCommandStatusEx(PQresultStatus(Result), hWnd, L"");


	// 2. Insert the values into the database
	// 3. Parse the return code.
} // End of Function