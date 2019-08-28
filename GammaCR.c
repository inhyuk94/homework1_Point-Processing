#include "DeclaSec.h"

void Gamma( Buf *DB )
{
	FILE   *fp;
	Char   WFileName[100], HistoFlag;
	Int    i;
	Double Num;
	UChar  Tmp;	
	Int    BitSize = 1 << BITDEPTH;

	system("cls");
	printf("Gamma값을 입력 하세요 : ");
	scanf_s(" %lf", &Num);
	
	sprintf_s( WFileName, sizeof(Char)*100, "Gamma Val %.1lf.raw", Num);
	fopen_s( &fp, WFileName, "wb" );	

	memset( DB->Output, 0, ROW*COL*sizeof(UChar) );
	memset( DB->LUTable, 0, BitSize*sizeof(UChar) );

	for (i = 0; i < BitSize; i++)
		DB->LUTable[i] = clipping( (pow(i, 1 / Num) - (int)pow(i, 1 / Num)) >= 0.5 ? (int)ceil(pow(i, 1 / Num)) : (int)floor(pow(i, 1 / Num)) );

	for( i=0; i<ROW*COL; i++ )
	{
		Tmp = DB->Input[i];
		DB->Output[i] = DB->LUTable[Tmp];
	}

	fwrite( DB->Output, sizeof(UChar), ROW*COL, fp );

	fclose(fp);

	printf("\n히스토그램을 출력 하시겠습니까?(y or n) ");
	scanf_s(" %c", &HistoFlag);

	if( HistoFlag == 'y' )
		Histo( DB );
}
