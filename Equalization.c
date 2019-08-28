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
		
		/* ȭ�� �� �󵵼��� �������� ����ȭ */
		DB->NormalizedSum[i] = (sum * scale_factor - (int)(sum * scale_factor)) >= 0.5 ? (int)ceil(sum*scale_factor) : (int)floor(sum*scale_factor);
		/* ����ȭ�� �������� �̿��Ͽ� ��� ���̺� ���� */
		DB->LUTable[i] = DB->NormalizedSum[i];


	}

	memset( DB->ImageCnt, 0, BitSize*sizeof(Int) );

	for( i=0; i<COL; i++ )
	{
		for( j=0; j<ROW; j++ )
		{   /* ����ȭ�� ȭ�� �� �󵵼��� �������� �̿��Ͽ� �Է� ȭ�� �� ���ε� ��°��� ���� */
			DB->Output[(i*ROW) + j] = DB->LUTable[DB->Input[(i*ROW) + j]];
		}
	}

	fwrite( DB->Output, sizeof(UChar), ROW*COL, fp );

	fclose(fp);

	printf("\n������׷��� ��� �Ͻðڽ��ϱ�?(y or n) ");
	scanf_s(" %c", &HistoFlag);

	if( HistoFlag == 'y' )
		Histo( DB );
}