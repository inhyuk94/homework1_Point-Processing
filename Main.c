#include "DeclaSec.h"

void main()
{	
	Int Num;
	Buffer InOut;	

	BufCon( &InOut, TRUE );
	
	while( TRUE )
	{
		printf("1. ��� ���� \n2. ���� ���� \n3. ��Ʈ��Ī \n4. ��Ȱȭ \n5. ����\n");
		printf("���� �� ���μ����� �����Ͻÿ� : ");
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
			printf("\n�ٽ� �Է� �ϼ���!!");
			_getch();
		}
		system("cls");	
	}

	BufCon( &InOut, FALSE );
}