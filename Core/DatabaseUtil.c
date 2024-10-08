#include "Core.h"
#include "PrivateCore.h"





/// <summary>
/// Check if a value exists in a column of a table.
/// </summary>
/// <param name="TableName">Name of the table to be queried.</param>
/// <param name="ColumnName">Name of the column to be queried</param>
/// <param name="Value">Value to check for.</param>
/// <returns></returns>
extern BOOL CheckIfValueExists(LPCWSTR TableName, LPCWSTR ColumnName, LPCWSTR Value) {
	PGresult *Result;

	// 1. Create the query
	// 2. Convert the query to UTF-8
	// 3. Run the query
	// 4. Check return code
	// 5. Return
} // End of Function





extern bool DbTest(void) {
	PGresult *Result;
	char *Utf8Query;



	ConvertUtf16ToUtf8(&Utf8Query, L"INSERT INTO public.artists (name) VALUES ('つんべじ') ON CONFLICT DO NOTHING;");
	Result = PQexec(Conn, Utf8Query);
	ExecStatusType Status = PQresultStatus(Result);

//	PQclear(Result);

//	Result = PQexec(Conn, "SELECT * FROM public.tags;");
//	char *value = PQgetvalue(Result, 1, 1);

	if (Status != PGRES_COMMAND_OK) {
		return false;
	} else {
		return true;
	} // End of If
} // End of Function





extern BOOL ParsePqResultStatus(ExecStatusType StatusCode) {
} // End of Function





/// <summary>
/// Parse the status code of a PostgreSQL command, with a MessageBox.
/// </summary>
/// <param name="StatusCode">Code returned from PQexecStatus.</param>
/// <param name="hWnd">Handle to the parent window.</param>
/// <param name="AddendumMessage">Message to be added after the built-in message.</param>
/// <returns></returns>
extern BOOL ParseCommandStatusEx(int StatusCode, HWND hWnd, LPCWSTR AddendumMessage) {
	LPWSTR Message = L"";
	size_t MessageLength = 0;


	// #TODO: Get a SQL error message from PQerrorMessage
	switch (StatusCode) {
		case PGRES_EMPTY_QUERY:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L"No SQL query was provided to the server. ", AddendumMessage }, (size_t []) { 41, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;

		case PGRES_COMMAND_OK:
		case PGRES_TUPLES_OK:
		case PGRES_SINGLE_TUPLE:
		case PGRES_COPY_OUT:
		case PGRES_COPY_IN:
		case PGRES_COPY_BOTH:
		case PGRES_PIPELINE_SYNC:
			return TRUE;

		case PGRES_BAD_RESPONSE:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L". ", AddendumMessage }, (size_t []) { 0, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;

		case PGRES_NONFATAL_ERROR:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L". ", AddendumMessage }, (size_t []) { 0, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;

		case PGRES_FATAL_ERROR:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L"A fatal SQL error occured, and if a transaction was in progress, it failed. ", AddendumMessage }, (size_t []) { 0, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;

		case PGRES_PIPELINE_ABORTED:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L"The SQL pipeline has been aborted. ", AddendumMessage }, (size_t []) { 0, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;


		default:
			ConcatenateStringsW(Message, MessageLength, (LPWSTR []) { L"Unknown error. ", AddendumMessage }, (size_t []) { 0, wcslen(AddendumMessage) }, hWnd);
			MessageBoxW(hWnd, Message, L"SQL Error", MB_OK | MB_ICONERROR);
			break;
	} // End of Switch

	return FALSE;
} // End of Function