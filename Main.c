#include "DeclaSec.h"

void main()
{	
	Int Num;
	Buffer InOut;	

	BufCon( &InOut, TRUE );
	
	while( TRUE )
	{
		printf("1. 산술 연산 \n2. 감마 보정 \n3. 스트레칭 \n4. 평활화 \n5. 종료\n");
		printf("수행 할 프로세스를 선택하시오 : ");
		scanf_s(" %d", &Num );

		if( Num == 1 )
			Arithmetic( &InOut );
		else if( Num == 2 )
			Gamma( &InOut );
		else if( Num == 3 )
			End_In( &InOut );	
		else if( Num == 4 )
			Equallization( &InOut );
		else if( Num == 5 )
		{
			printf("\n");
			_exit(0);
		}
		else
		{
			printf("\n다시 입력 하세요!!");
			_getch();
		}
		system("cls");	
	}

	BufCon( &InOut, FALSE );
}