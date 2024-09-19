#include "Core.h"
#include "PrivateCore.h"

#include <sha-256.h>
#include <stdio.h>
#include <stdlib.h>





/* ImportFile(Path)
 *	Let FileData = LoadFileData(Path)
 *	Let Width = GetFileDataWidth(FileData)
 *	Let Height = GetFileDataHeight(FileData)
 *	Let Sha256 = CalculateSha256(FileData)
 *	Let Format = GetFileDataFormat(FileData)
 *
 * #TODO: Check if the image has already been imported
 *
 *
 *	RunSqlQuery("INSERT INTO public.posts (sha256, width, height) VALUES (Sha256, Width, Height);");
 *	MoveFile(GetMediaPath() + "\" + Sha256, Path)
 */
extern const char *ImportFile(const char *Path, const char *Source) {
	FILE *File;
	unsigned char *FileData = NULL;
	char *FileType = NULL;
	uint64_t FileSize;
	size_t Width, Height;
	char *Hash = NULL;
	PGresult *Res;
	DWORD StatusCode;
	char *WidthString = NULL;
	char *HeightString = NULL;
	char *SizeString = NULL;
	size_t TempSize;


	/// 1. Open File
	if(fopen_s(&File, Path, "r")) {
		StatusCode = GetLastError();
		if (StatusCode == ERROR_FILE_NOT_FOUND) {
			return "No such file exists.";
		} // End of If
	} // End of If



	/// 2. Check the file type
	///	a. If -1, error.
	FileType = GetImageFormat(Path);
	if (FileType == NULL) {
		return "Unsupported file format.";
	} // End of If


	/// 3. Get the length of File in bytes
	fseek(File, 0L, SEEK_END);
	FileSize = ftell(File);
	rewind(File);



	/// 4. Allocate FileData
	AllocateMemory(&FileData, FileSize, sizeof(unsigned char));
	FileData[FileSize] = 0;



	/// 5. Load the file into FileData
	fread_s(FileData, FileSize + 1, FileSize, 1, File);
	fclose(File);



	/// 6. Get the image hash
	GetSHA256(&Hash, FileData, FileSize + 1);



	/// 7. Get Width & Height
	Height = GetImageHeight(FileData);
	Width = GetImageWidth(FileData);



	/// 8. Check if the image has already been inserted into the database
	Res = PQexecParams(Conn, "SELECT id FROM public.posts WHERE sha256 = $1;", 1, NULL, (const char *[]) { Hash }, NULL, NULL, 0);
	// #TODO: copy the command checking
	if (PQntuples(Res) != 0) {
		return "File has already been imported.";
	} // End of If

	PQclear(Res);



	/// 9. Convert types
	TempSize = CountDigits(Width);
	AllocateMemory(&WidthString, TempSize + 1, sizeof(char));
	sprintf_s(WidthString, TempSize + 1, "%lu\0", Width);

	TempSize = CountDigits(Height);
	AllocateMemory(&HeightString, TempSize + 1, sizeof(char));
	sprintf_s(HeightString, TempSize + 1, "%lu\0", Height);

	TempSize = CountDigits(FileSize);
	AllocateMemory(&SizeString, TempSize + 1, sizeof(char));
	sprintf_s(SizeString, TempSize + 1, "%lu\0", FileSize);



	/// 10. Insert into the database
	if (Source == NULL) {
		Res = PQexecParams(Conn, "INSERT INTO public.posts (sha256, file_type, width, height, size) VALUES ($1, $2, $3, $4, $5);", 5, NULL, (const char *[]) { Hash, FileType, WidthString, HeightString, SizeString }, NULL, NULL, 0);
	} else {
		Res = PQexecParams(Conn, "INSERT INTO public.posts (sha256, file_type, width, height, size, source) VALUES ($1, $2, $3, $4, $5, $6);", 6, NULL, (const char *[]) { Hash, FileType, WidthString, HeightString, SizeString, Source }, NULL, NULL, 0);
	} // End of If/Else



	/// 11. Move the file
	// Get destination path from registry



	/// 12. Generate thumbnails



	/// 13. Free memory
	free(FileType);
	free(WidthString);
	free(HeightString);
	free(SizeString);
	free(Hash);

	FileType = NULL;
	WidthString = NULL;
	HeightString = NULL;
	SizeString = NULL;
	Hash = NULL;
//	File



	return 0;
} // End of Function
