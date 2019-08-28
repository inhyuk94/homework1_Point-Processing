#include "DeclaSec.h"

void Histo( Buf *DB )
{
	FILE   *fp;
	Char   WFileName[100];
	Int    MaxPixNum;
	Int    BitSize = 1 << BITDEPTH;

	system("cls");
	
	sprintf_s( WFileName, sizeof(Char)*100, "Histogram.raw");
	fopen_s( &fp, WFileName, "wb" );	
	
	Frequency( DB->Output, DB->ImageCnt, &MaxPixNum );
	HistogramPrint( DB->Histogram, DB->ImageCnt, DB->NormalImageCnt, MaxPixNum );
	
	fwrite( DB->Histogram, sizeof(UChar), BitSize*BitSize, fp );

	fclose(fp);
}

void Frequency( UChar *Dat, Int *Cnt, Int *MaxPixNum )
{
	Int   i;
	Int   Min=0;
	UChar Tmp;
	Int   BitSize = 1 << BITDEPTH;

	for( i=0; i<ROW*COL; i++ )
	{
		/* ȭ�� �� �󵵼��� ���� Cnt ���ۿ� ���� */
		Cnt[Dat[i]]++;
	}

	for( i=0; i<BitSize; i++ )
	{
		if( Cnt[i] > Min )
		{
			/* �ִ� �󵵼��� ���� ȭ�Ҹ� MaxPicNum�� ���� */
			* MaxPixNum = Cnt[i];
			  Min = Cnt[i];
		}
	}
}

void HistogramPrint( UChar *Histogram, Int *Cnt, Int *NormalCnt, Int MaxPixNum )
{
	Int i, j;
	Int BitSize = 1 << BITDEPTH;

	for (i = 0; i < BitSize; i++)
		NormalCnt[i] = Cnt[i] * (BitSize-1) / MaxPixNum ; 
		

	for( i=0; i<BitSize; i++ )
		for( j=0; j<NormalCnt[i]; j++ )
			Histogram[( i + ((BitSize) - NormalCnt[i])*BitSize )  + j*BitSize ] = BitSize-1;
}

