#include "Core.h"
#include "PrivateCore.h"





extern PGconn *Conn;





extern void InitialiseConnection() {
	// Get the connection string from the registry
	// Convert the connection string to UTF-8
	Conn = PQconnectdb("");
}
