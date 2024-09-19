#include "Core.h"
#include <MagickWand/MagickWand.h>





// #TODO: Refactor this to use a single MagickWand.
//extern MagickWand *ImportWand;





extern char *GetImageFormat(const char *Path) {
//extern char *GetImageFormat(MagickWand *Wand) {
	MagickWand *Wand;

	Wand = NewMagickWand();
	if (MagickReadImage(Wand, Path) == MagickFalse) {
		// Error: MagickWand could not read the image.
	} // End of If

	return MagickGetImageFormat(Wand);
} // End of Function





extern size_t GetImageHeight(const char *FilePath) {
	MagickWand *Wand;
	size_t Height;


	Wand = NewMagickWand();
	if (MagickReadImage(Wand, FilePath) == MagickFalse) {
		// Error: MagickWand could not read the image.
	} // End of If


	Height = MagickGetImageWidth(Wand);
	Wand = DestroyMagickWand(Wand);


	return Height;
} // End of Function





extern size_t GetImageWidth(const char *FilePath) {
	MagickWand *Wand;
	size_t Width;


	Wand = NewMagickWand();
	if (MagickReadImage(Wand, FilePath) == MagickFalse) {
		// Error: MagickWand could not read the image.
	} // End of If


	Width = MagickGetImageHeight(Wand);
	Wand = DestroyMagickWand(Wand);

	return Width;
} // End of Function





extern void InitialiseMagick(void) {
	MagickWandGenesis();
} // End of Function





/*
extern void SetImportWand(const char *Path) {
	ImportWand = NewMagickWand();
	if (MagickReadImage(ImportWand, Path) == MagickFalse) {
		// Error: MagickWand could not read the image.
		fprintf(stderr, "SetImportWand: Failed to load file, `%s'\n", Path);
		abort();
	} // End of If
} // End of Function
*/





extern void TerminateMagick(void) {
	MagickWandTerminus();
} // End of Function
