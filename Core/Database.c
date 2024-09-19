#include "Core.h"
#include "PrivateCore.h"
#include <uri_encode.h>





extern LSTATUS ConfigureDatabase(LPCWSTR DatabaseName, LPCWSTR Domain, LPCWSTR Password, LPDWORD SavePassword, LPDWORD Port, LPCWSTR Username) {
	LSTATUS Status;


	// Create DatabaseName
	Status = SetDatabaseName(DatabaseName);
	Status = SetDomain(Domain);
	Status = SetPortDb(Port);
	Status = SetSavePassword(SavePassword);
	Status = SetUsername(Username);


	if (SavePassword) {
		MessageBoxW(NULL, L"Setting password.", L"Notice", MB_OK | MB_ICONINFORMATION);
		Status = SetPassword(Password);
	} else {
		Status = RegSetValueExW(hProfileKey, L"Password", NULL, REG_SZ, NULL, 0);
	} // End of If/Else


	return Status;
} // End of Function





extern LSTATUS ConnectInternal(LPCWSTR DatabaseName, LPCWSTR Domain, LPCTSTR Password, LPDWORD Port, LPCWSTR Username) {
	LSTATUS Status = 0;
	char *Utf8DabaseName = NULL;
	size_t Utf8DabaseNameLength = WideCharToMultiByte(CP_UTF8, 0, DatabaseName, -1, NULL, 0, NULL, NULL);
	char *Utf8Domain = NULL;
	size_t Utf8DomainLength = WideCharToMultiByte(CP_UTF8, 0, Domain, -1, NULL, 0, NULL, NULL);
	char *Utf8Password = NULL;
	size_t Utf8PasswordLength = WideCharToMultiByte(CP_UTF8, 0, Password, -1, NULL, 0, NULL, NULL);
	char *Utf8Port = NULL;
	size_t Utf8PortLength = CountDigits(Port) + 1;
	char *Utf8Username = NULL;
	size_t Utf8UsernameLength = WideCharToMultiByte(CP_UTF8, 0, Username, -1, NULL, 0, NULL, NULL);
	char *EncodedDatabaseName = NULL;
	size_t EncodedDatabaseNameLength = (Utf8DabaseNameLength * 3) + 1;
	char *EncodedDomain = NULL;
	size_t EncodedDomainLength = (Utf8DomainLength * 3) + 1;
	char *EncodedPassword = NULL;
	size_t EncodedPasswordLength = (Utf8PasswordLength * 3) + 1;
	char *EncodedUsername = NULL;
	size_t EncodedUsernameLength = (Utf8UsernameLength * 3) + 1;
	char *ConnectionString = NULL;
	size_t ConnectionStringLength = 17;


	// Convert Arguments to UTF-8
	AllocateMemory(&Utf8DabaseName, Utf8DabaseNameLength, sizeof(char));
	AllocateMemory(&Utf8Domain, Utf8DomainLength, sizeof(char));
	AllocateMemory(&Utf8Password, Utf8PasswordLength, sizeof(char));
	AllocateMemory(&Utf8Port, Utf8PortLength, sizeof(char));
	AllocateMemory(&Utf8Username, Utf8UsernameLength, sizeof(char));

	WideCharToMultiByte(CP_UTF8, 0, DatabaseName, -1, Utf8DabaseName, Utf8DabaseNameLength, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, Domain, -1, Utf8Domain, Utf8DomainLength, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, Password, -1, Utf8Password, Utf8PasswordLength, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, Username, -1, Utf8Username, Utf8UsernameLength, NULL, NULL);
	sprintf_s(Utf8Port, Utf8PortLength, "%lu\0", *Port);



	// Percent encode UTF-8 strings
	AllocateMemory(&EncodedDatabaseName, EncodedDatabaseNameLength, sizeof(char));
	AllocateMemory(&EncodedDomain, EncodedDomainLength, sizeof(char));
	AllocateMemory(&EncodedPassword, EncodedPasswordLength, sizeof(char));
	AllocateMemory(&EncodedUsername, EncodedUsernameLength, sizeof(char));

	Status = uri_encode(EncodedDatabaseName, Utf8DabaseNameLength - 1, Utf8DabaseName);
	Status = uri_encode(EncodedDomain, Utf8DomainLength - 1, Utf8Domain);
	Status = uri_encode(EncodedPassword, Utf8PasswordLength - 1, Utf8Password);
	Status = uri_encode(EncodedUsername, Utf8UsernameLength - 1, Utf8Username);



	// Cleanup
	free(Utf8DabaseName);
	free(Utf8Domain);
	free(Utf8Password);
	free(Utf8Username);

	Utf8DabaseName = NULL;
	Utf8Domain = NULL;
	Utf8Password = NULL;
	Utf8Username = NULL;



	// Generate Connection String
	ConnectionStringLength += EncodedDatabaseNameLength + EncodedDomainLength + EncodedPasswordLength + Utf8PortLength + Utf8UsernameLength;
	AllocateMemory(&ConnectionString, ConnectionStringLength, sizeof(char));
	sprintf_s(ConnectionString, ConnectionStringLength, "postgresql://%s:%s@%s:%s/%s", EncodedUsername, EncodedPassword, EncodedDomain, Utf8Port, EncodedDatabaseName);


	// Cleanup
	free(EncodedDatabaseName);
	free(EncodedDomain);
	free(EncodedPassword);
	free(EncodedUsername);
	free(Utf8Port);

	EncodedDatabaseName = NULL;
	EncodedDomain = NULL;
	EncodedPassword = NULL;
	EncodedUsername = NULL;
	Utf8Port = NULL;



	// Connect to database
	Conn = PQconnectdb(ConnectionString);
	if (PQstatus(Conn) == CONNECTION_OK) {
		Status = ERROR_SUCCESS;
	} else {
		Status = ERROR_CONNECTION_INVALID;
	} // End of If/Else


	return Status;
} // End of Function





extern void DbDisconnect(void) {
	PQfinish(Conn);
} // End of Function
