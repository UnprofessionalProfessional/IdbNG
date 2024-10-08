#include <Core.h>
#include "PrivateCore.h"
#include <stdio.h>
#include <crtdbg.h>

int main(int argc, char *argv[]) {
	const char *Path = "C:\\Users\\nsm\\Pictures\\jpegxl-home.jxl";
	LSTATUS Status;
	DWORD Preview = 0;
	LPWSTR StoragePath = NULL;


	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
	Status = InitialiseRegistry();


	Status = InitialiseCore();
	switch (Status) {
		case ERROR_FILE_NOT_FOUND:
			printf("Creating profile\n");
			//CreateProfile(L"nsm", L"D:\\Pictures\\Art\\IDB");
			break;

		case ERROR_NOT_FOUND:
			printf("Setting default profile\n");
			Status = SetDefaultProfile(L"nsm");
			printf("SetDefaultProfile: 0x%02x\n", Status);
			break;

		default:
			printf("InitialiseCore: 0x%02x\n", Status);
			break;
	} // End of Switch




	InitialiseMagick();


	GetShowPreview(&Preview);
	printf("Preview enabled: %lu\n", Preview);

	GetSafeMode(&Preview);
	printf("Safe mode enabled: %lu\n", Preview);

	GetMaximise(&Preview);
	printf("Maximise: %lu\n", Preview);

	GetDefaultView(&Preview);
	printf("Default view: %lu\n", Preview);

	GetThumbSize(&Preview);
	printf("Thumbnail size: %lu\n", Preview);

	GetStoragePath(&StoragePath, &Preview);
	printf("`%S', %lu\n", StoragePath, Preview);

	SetPassword(L"nsm");


	printf("This file is %zu pixels wide.\n", GetImageWidth(Path));
	printf("This file is %zu pixels tall\n", GetImageHeight(Path));
	printf("This file's type is `%s'\n", GetImageFormat(Path));
	TerminateMagick();


	return 0;
}