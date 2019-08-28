#include "DeclaSec.h"
int clipping(int x)
{
	if (x > 255) x = 255;
	else if (x < 0) x = 0;
	return x;
}
void Arithmetic( Buf *DB )
{
	FILE   *fp;
	Char   Operator, WFileName[100], HistoFlag;
	Int    i;
	Double Num;
	UChar  Tmp;	
	Int    BitSize = 1 << BITDEPTH;

	system("cls");
	printf("연산 기호를 입력 하세요 : ");
	scanf_s(" %c", &Operator);
	printf("연산 수를 입력 하세요 : ");
	scanf_s(" %lf", &Num);

	if( Operator == '+' )		sprintf_s( WFileName, sizeof(Char)*100, "Arithmetic Add %.0lf.raw", Num);
	if( Operator == '-' )		sprintf_s( WFileName, sizeof(Char)*100, "Arithmetic Min %.0lf.raw", Num);
	if( Operator == '*' )		sprintf_s( WFileName, sizeof(Char)*100, "Arithmetic Mul %.0lf.raw", Num);
	if( Operator == '/' )		sprintf_s( WFileName, sizeof(Char)*100, "Arithmetic Div %.0lf.raw", Num);
	fopen_s( &fp, WFileName, "wb" );	

	memset( DB->Output, 0, ROW*COL*sizeof(UChar) );
	memset( DB->LUTable, 0, BitSize*sizeof(UChar) );

	for( i=0; i<BitSize; i++ )
	{
		if (Operator == '+')		DB->LUTable[i] = clipping((i + Num) - (int)(i + Num) >= 0.5 ? (int)ceil(i + Num) : (int)floor(i + Num));
		if (Operator == '-')		DB->LUTable[i] = clipping((i - Num) - (int)(i - Num) >= 0.5 ? (int)ceil(i - Num) : (int)floor(i - Num));
		if (Operator == '*')		DB->LUTable[i] = clipping((i * Num) - (int)(i * Num) >= 0.5 ? (int)ceil(i * Num) : (int)floor(i * Num));
		if (Operator == '/')		DB->LUTable[i] = clipping((i / Num) - (int)(i / Num) >= 0.5 ? (int)ceil(i / Num) : (int)floor(i / Num));
	}

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
	