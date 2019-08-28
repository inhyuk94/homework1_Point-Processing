#include "DeclaSec.h"

void Equallization( Buf *DB )
{
	FILE    *fp;
	Char    WFileName[100], HistoFlag;	
	Int		i, j, sum=0, tmp_2=0;
	Double	scale_factor;
	Int     MaxPixNum;
	Int     BitSize = 1 << BITDEPTH;
	
	sprintf_s( WFileName, sizeof(Char)*100, "Equalization.raw");
	fopen_s( &fp, WFileName, "wb" );	
	
	Frequency( DB->Input, DB->ImageCnt, &MaxPixNum );
	
	scale_factor = (Double)(BitSize-1) / (Double)(ROW*COL);
	for( i=0; i<BitSize; i++ )
	{
		tmp_2 = DB->ImageCnt[i];
		sum = sum + tmp_2;
		
		/* 화소 별 빈도수의 누적합을 정규화 */
		DB->NormalizedSum[i] = (sum * scale_factor - (int)(sum * scale_factor)) >= 0.5 ? (int)ceil(sum*scale_factor) : (int)floor(sum*scale_factor);
		/* 정규화된 누적합을 이용하여 룩업 테이블 생성 */
		DB->LUTable[i] = DB->NormalizedSum[i];


	}

	memset( DB->ImageCnt, 0, BitSize*sizeof(Int) );

	for( i=0; i<COL; i++ )
	{
		for( j=0; j<ROW; j++ )
		{   /* 정규화된 화소 별 빈도수의 누적합을 이용하여 입력 화소 별 매핑된 출력값을 저장 */
			DB->Output[(i*ROW) + j] = DB->LUTable[DB->Input[(i*ROW) + j]];
		}
	}

	fwrite( DB->Output, sizeof(UChar), ROW*COL, fp );

	fclose(fp);

	printf("\n히스토그램을 출력 하시겠습니까?(y or n) ");
	scanf_s(" %c", &HistoFlag);

	if( HistoFlag == 'y' )
		Histo( DB );
}