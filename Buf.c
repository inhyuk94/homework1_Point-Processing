#include "DeclaSec.h"

void BufCon( Buf *DB, Int OrderFlag )
{
	if( OrderFlag )
	{
		FILE *fp;
		Int    BitSize = 1 << BITDEPTH;
		fopen_s( &fp, FILENAME, "rb" );	

		DB->Input = (UChar*)calloc(ROW*COL, sizeof(UChar));
		DB->Output = (UChar*)calloc(ROW*COL, sizeof(UChar));
		DB->LUTable = (UChar*)calloc(BitSize, sizeof(UChar));
		DB->Histogram = (UChar*)calloc(BitSize*BitSize, sizeof(UChar));
		DB->ImageCnt = (Int*)calloc(BitSize, sizeof(Int));
		DB->NormalImageCnt = (Int*)calloc(BitSize, sizeof(Int));
		DB->NormalizedSum = (UChar*)calloc(BitSize, sizeof(UChar));

		fread( DB->Input, sizeof(UChar), ROW*COL, fp );

		fclose(fp);
	}	
	else
	{
		free( DB->Input );
		free( DB->Output );
		free( DB->LUTable );
		free( DB->Histogram );
		free( DB->ImageCnt );
		free( DB->NormalImageCnt );
		free( DB->NormalizedSum );
	}
}