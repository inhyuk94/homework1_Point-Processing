#include "ImgInfo.h"

typedef struct _Buffer
{
	UChar *Input;
	UChar *Output;
	UChar *LUTable;
	UChar *Histogram;
	Int   *ImageCnt;
	Int   *NormalImageCnt;
	UChar *NormalizedSum;
}Buffer;

typedef Buffer Buf;

void BufCon( Buf *DB, Int OrderFlag );

void Arithmetic( Buf *DB );
void Gamma( Buf *DB );
void Histo( Buf *DB );
void Frequency( UChar *Dat, Int *Cnt, Int *MaxPixNum );
void HistogramPrint( UChar *Histogram, Int *Cnt, Int *NormalCnt, Int MaxPixNum );
void End_In( Buf *DB );
void Equallization( Buf *DB );
int clipping(int x);




