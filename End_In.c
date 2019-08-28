#include "DeclaSec.h"

void End_In( Buf *DB )
{
	FILE    *fp;
	Char    WFileName[100], HistoFlag;
	Int		LowThresh, HighThresh;
	Int     i, j, MaxPixNum;
	Int		PixSum=0;
	Int		Tmp, Low, High, LowSum=0, HighSum=0, LowPixCnt=0, HighPixCnt=0, LowPix=0, HighPix=0;
	Double  DTmp;
	Int     BitSize = 1 << BITDEPTH;

	system("cls");
	printf("Low �Ӱ� ���� �Է� : ");
	scanf_s(" %d", &LowThresh);
	printf("High �Ӱ� ���� �Է� : ");
	scanf_s(" %d", &HighThresh);

	sprintf_s( WFileName, sizeof(Char)*100, "End_In %d_%d.raw", LowThresh, HighThresh);
	fopen_s( &fp, WFileName, "wb" );	
	
	Frequency( DB->Input, DB->ImageCnt, &MaxPixNum );
	HistogramPrint( DB->Histogram, DB->ImageCnt, DB->NormalImageCnt, MaxPixNum );

	memset( DB->ImageCnt, 0, BitSize*sizeof(Int) );
	memset( DB->Histogram, 0, BitSize*BitSize*sizeof(UChar) );

	for( i=0; i<BitSize; i++ )
		PixSum += DB->NormalImageCnt[i];

	DTmp = PixSum * (LowThresh / 100.0);
	Low  = DTmp >= 0.5 ? (int)ceil(DTmp) : (int)floor(DTmp);
	DTmp = PixSum * (HighThresh / 100.0);
	High = DTmp >= 0.5 ? (int)ceil(DTmp) : (int)floor(DTmp);

	while( TRUE )
	{
		/* �Է� ���� ������ �ش��ϴ� �����տ� �ش��ϴ� ȭ�� ����(LowPix)�� ã�� ���� �˰��� */
		
			Tmp = DB->NormalImageCnt[LowPixCnt];
			LowSum = LowSum + Tmp;
			if (LowSum > Low)
			{
				LowPix = LowPixCnt;
				break;
			}
	
			LowPixCnt++;
	}

	while( TRUE )
	{
		/* �Է� �ִ� ������ �ش��ϴ� �����տ� �ش��ϴ� ȭ�� ����(HighPix)�� ã�� ���� �˰��� */
		
			Tmp = DB->NormalImageCnt[BitSize-1-HighPixCnt];
			HighSum= HighSum + Tmp;
			if (HighSum  > High)
			{
				HighPix = BitSize - 1 - HighPixCnt;
				break;
			}
			HighPixCnt++;
	}
	
	for( i=0; i<COL; i++ )
	{
		for( j=0; j<ROW; j++ )
		{
			if( DB->Input[(i*ROW) + j] <= LowPix )
				DB->Output[(i*ROW) + j] = 0;
			else if( DB->Input[(i*ROW) + j] >= HighPix )
				DB->Output[(i*ROW) + j] = BitSize-1;
			else
			{
				DB->Output[(i*ROW) + j] = 255 * (DB->Input[(i*ROW) + j] - LowPix) / (HighPix - LowPix);
			}
		}
	}

	fwrite( DB->Output, sizeof(UChar), ROW*COL, fp );

	fclose(fp);

	printf("\n������׷��� ��� �Ͻðڽ��ϱ�?(y or n) ");
	scanf_s(" %c", &HistoFlag);

	if( HistoFlag == 'y' )
		Histo( DB );

}