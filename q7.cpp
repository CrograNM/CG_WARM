#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BOARD_SIZE 30
#define MAX_LENGTH 25
#define figureA 'O'
#define figureB 'X'
#define figureDuplicate '#'

// 이 2차원 배열을 수정하며 보드를 출력
char rect1[BOARD_SIZE][BOARD_SIZE]; // '.': not Rect, 'O': is Rect
char rect2[BOARD_SIZE][BOARD_SIZE]; // '.': not Rect, 'X': is Rect
void initRect1()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			rect1[i][j] = '.';
		}
	}
}
void initRect2()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			rect2[i][j] = '.';
		}
	}
}
void showBoard()
{
	system("cls"); //콘솔화면 지우기
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//충돌체크
			if (rect1[i][j] == rect2[i][j]) //'.'으로 동일할때
			{
				printf("%2c", rect1[i][j]);
			}
			else if(rect1[i][j] == figureA && rect2[i][j] == figureB)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//밝은빨강색
				printf("%2c", figureDuplicate);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//기본콘솔색상
			}
			else if (rect1[i][j] == figureA) {
				printf("%2c", rect1[i][j]);
			}
			else if (rect2[i][j] == figureB)
			{
				printf("%2c", rect2[i][j]);
			}
		}
		printf("\n");
	}
	//printf("\n\n");
}
void makeRect1(int x1, int y1, int x2, int y2)
{
	// x1, y1, x2, y2를 기준에 맞게 변경한다
	// x1 이 음수라면 변환된 x1을 
	// 받은 좌표에 따른 인덱스들을 알파벳'O'로 바꿔주면 된다.
	int height = y2 - y1 + 1;	//for문의 i크기
	int width = x2 - x1 + 1;	//for문의 j크기

	//부족한 길이 구하기
	x1 = (BOARD_SIZE + x1) % BOARD_SIZE;
	y1 = (BOARD_SIZE + y1) % BOARD_SIZE;
	int leftWidth = x1 + width - BOARD_SIZE;
	int leftHeight = y1 + height - BOARD_SIZE;
	int tempLeftWidth = 0;
	int tempLeftHeight = 0;
	if (leftWidth > 0)
	{
		tempLeftWidth = leftWidth;
	}
	if (leftHeight > 0)
	{
		tempLeftHeight = leftHeight;
	}

	int i, j;
	if (leftWidth <= 0 && leftHeight <= 0)
	{
		initRect1();
		for (i = y1; i < y1 + height; i++)
		{
			for (j = x1; j < x1 + width; j++)
			{
				rect1[i][j] = figureA;
			}
		}
	}
	else
	{
		initRect1();
		if (leftWidth > 0 && leftHeight > 0)
		{
			for (i = 0; i < leftHeight; i++)
			{
				for (j = 0; j < leftWidth; j++)
				{
					rect1[i][j] = figureA;
				}
			}
		}
		if (leftWidth > 0)
		{

			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = x1; j < BOARD_SIZE; j++)
				{
					rect1[i][j] = figureA;
				}
			}
			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = 0; j < leftWidth; j++)
				{
					rect1[i][j] = figureA;
				}
			}
		}
		if (leftHeight > 0)
		{
			for (j = x1; j < x1 + width - tempLeftWidth; j++)
			{
				for (i = y1; i < BOARD_SIZE; i++)
				{
					rect1[i][j] = figureA;
				}
				for (i = 0; i < leftHeight; i++)
				{
					rect1[i][j] = figureA;
				}
			}
		}
	}
}
void makeRect2(int x1, int y1, int x2, int y2)
{
	int height = y2 - y1 + 1;	//for문의 i크기
	int width = x2 - x1 + 1;	//for문의 j크기

	//부족한 길이 구하기
	x1 = (BOARD_SIZE + x1) % BOARD_SIZE;
	y1 = (BOARD_SIZE + y1) % BOARD_SIZE;
	int leftWidth = x1 + width - BOARD_SIZE;
	int leftHeight = y1 + height - BOARD_SIZE;
	int tempLeftWidth = 0;
	int tempLeftHeight = 0;
	if (leftWidth > 0)
	{
		tempLeftWidth = leftWidth;
	}
	if (leftHeight > 0)
	{
		tempLeftHeight = leftHeight;
	}

	int i, j;
	if (leftWidth <= 0 && leftHeight <= 0)
	{
		initRect2();
		for (i = y1; i < y1 + height; i++)
		{
			for (j = x1; j < x1 + width; j++)
			{
				rect2[i][j] = figureB;
			}
		}
	}
	else
	{
		initRect2();
		if (leftWidth > 0 && leftHeight > 0)
		{
			for (i = 0; i < leftHeight; i++)
			{
				for (j = 0; j < leftWidth; j++)
				{
					rect2[i][j] = figureB;
				}
			}
		}
		if (leftWidth > 0)
		{

			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = x1; j < BOARD_SIZE; j++)
				{
					rect2[i][j] = figureB;
				}
			}
			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = 0; j < leftWidth; j++)
				{
					rect2[i][j] = figureB;
				}
			}
		}
		if (leftHeight > 0)
		{
			for (j = x1; j < x1 + width - tempLeftWidth; j++)
			{
				for (i = y1; i < BOARD_SIZE; i++)
				{
					rect2[i][j] = figureB;
				}
				for (i = 0; i < leftHeight; i++)
				{
					rect2[i][j] = figureB;
				}
			}
		}
	}
}
int main()
{
	initRect1();
	initRect2();
	showBoard();

	int init = 0;
	int Ax1, Ay1, Ax2, Ay2;
	int Bx1, By1, Bx2, By2;
	char input;
	int Awidth = 0;
	int Aheight = 0;
	int Bwidth = 0;
	int Bheight = 0;
	while (1)
	{
		if (init == 0)
		{	// 좌표설정
			printf("사각형A 좌표 입력 (x1, y1), (x2, y2): ");
			scanf(" %d %d %d %d", &Ax1, &Ay1, &Ax2, &Ay2);
			if (Ax2 < Ax1)
			{
				int temp = Ax1;
				Ax1 = Ax2;
				Ax2 = temp;
			}
			if (Ay2 < Ay1)
			{
				int temp = Ay1;
				Ay1 = Ay2;
				Ay2 = temp;
			}
			Awidth = Ax2 - Ax1 + 1;
			Aheight = Ay2 - Ay1 + 1;
			if (Awidth <= MAX_LENGTH && Aheight <= MAX_LENGTH)
			{
				if (0 <= Ax1 && Ax1 < BOARD_SIZE && 0 <= Ay1 && Ay1 < BOARD_SIZE &&
					0 <= Ax2 && Ax2 < BOARD_SIZE && 0 <= Ay2 && Ay2 < BOARD_SIZE)
				{
					// 모든 입력이 성공적이라면 다음 반복문 -> 명령어 입력으로 이동
					// 그전에 입력된 좌표의 사각형 저장해주기
					// 좌표는 어떤 순서든 더 큰값이 오른쪽으로 온다
					makeRect1(Ax1, Ay1, Ax2, Ay2);
					showBoard();
					printf("사각형A (%d, %d) (%d, %d) 구현 성공\n", Ax1, Ay1, Ax2, Ay2);

					//성공시 사각형2 입력
					printf("사각형B 좌표 입력 (x1, y1), (x2, y2): ");
					scanf(" %d %d %d %d", &Bx1, &By1, &Bx2, &By2);
					//성공시 init = 1;
					if (Bx2 < Bx1)
					{
						int temp = Bx1;
						Bx1 = Bx2;
						Bx2 = temp;
					}
					if (By2 < By1)
					{
						int temp = By1;
						By1 = By2;
						By2 = temp;
					}
					Bwidth = Bx2 - Bx1 + 1;
					Bheight = By2 - By1 + 1;
					if (Bwidth <= MAX_LENGTH && Bheight <= MAX_LENGTH)
					{
						if (0 <= Bx1 && Bx1 < BOARD_SIZE && 0 <= By1 && By1 < BOARD_SIZE &&
							0 <= Bx2 && Bx2 < BOARD_SIZE && 0 <= By2 && By2 < BOARD_SIZE)
						{
							// 모든 입력이 성공적이라면 다음 반복문 -> 명령어 입력으로 이동
							// 그전에 입력된 좌표의 사각형 저장해주기
							// 좌표는 어떤 순서든 더 큰값이 오른쪽으로 온다
							makeRect2(Bx1, By1, Bx2, By2);
							showBoard();
							printf("사각형B (%d, %d) (%d, %d) 구현 성공\n", Bx1, By1, Bx2, By2);
							init = 1;
						}
						else
						{
							printf("초기 좌표는 보드 안에 만들어주세요\n");
						}
					}
					else
					{
						printf("최대 길이는 [%d]입니다! 좌표를 조정해주세요\n", MAX_LENGTH);
					}
				}
				else
				{
					printf("초기 좌표는 보드 안에 만들어주세요\n");
				}
			}
			else
			{
				printf("최대 길이는 [%d]입니다! 좌표를 조정해주세요\n", MAX_LENGTH);
			}
		}
		else
		{	// 좌표설정이 끝나면 다음 반복문부터 명령어 입력
			printf("input command : ");
			scanf(" %c", &input);

			switch (input)
			{
			case 'q':
			{
				printf("프로그램을 종료합니다.\n");
				break;
			}
			case 'r':
			{
				init = 0;
				initRect1();
				showBoard();
				printf("프로그램을 초기화하였습니다.\n");
				break;
			}
			//사각형A
			case 'a':
			{
				Ax1--;
				Ax2--;
				makeRect1(Ax1, Ay1, Ax2, Ay2);
				showBoard();
				break;
			}
			case 'd':
			{
				Ax1++;
				Ax2++;
				makeRect1(Ax1, Ay1, Ax2, Ay2);
				showBoard();
				break;
			}
			case 'w':
			{
				Ay1--;
				Ay2--;
				makeRect1(Ax1, Ay1, Ax2, Ay2);
				showBoard();
				break;
			}
			case 's':
			{
				Ay1++;
				Ay2++;
				makeRect1(Ax1, Ay1, Ax2, Ay2);
				showBoard();
				break;
			}
			case 'm':
			{
				Awidth = Ax2 - Ax1 + 1;
				Aheight = Ay2 - Ay1 + 1;
				if (Ax1 + 1 < Ax2 && Ay1 + 1 < Ay2)
				{
					Ax2--;
					Ay2--;
					makeRect1(Ax1, Ay1, Ax2, Ay2);
					showBoard();
				}
				else
				{
					printf("!!범위초과 : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			}
			case 'M':
			{
				Awidth = Ax2 - Ax1 + 1;
				Aheight = Ay2 - Ay1 + 1;
				if (Awidth < MAX_LENGTH && Aheight < MAX_LENGTH &&
					Ax2 < BOARD_SIZE - 1 && Ay2 < BOARD_SIZE - 1)
				{
					Ax2++;
					Ay2++;
					makeRect1(Ax1, Ay1, Ax2, Ay2);
					showBoard();
				}
				else
				{
					printf("!!범위초과 : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			}	
			//사각형B
			case 'j':
			{
				Bx1--;
				Bx2--;
				makeRect2(Bx1, By1, Bx2, By2);
				showBoard();
				break;
			}
			case 'l':
			{
				Bx1++;
				Bx2++;
				makeRect2(Bx1, By1, Bx2, By2);
				showBoard();
				break;
			}
			case 'i':
			{
				By1--;
				By2--;
				makeRect2(Bx1, By1, Bx2, By2);
				showBoard();
				break;
			}
			case 'k':
			{
				By1++;
				By2++;
				makeRect2(Bx1, By1, Bx2, By2);
				showBoard();
				break;
			}
			case 'n':
			{
				if (Bx1 + 1 < Bx2 && By1 + 1 < By2)
				{
					Bx2--;
					By2--;
					makeRect2(Bx1, By1, Bx2, By2);
					showBoard();
				}
				else
				{
					printf("!!범위초과 : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			}
			case 'N':
			{
				Bwidth = Bx2 - Bx1 + 1;
				Bheight = By2 - By1 + 1;
				if (Bwidth < MAX_LENGTH && Bheight < MAX_LENGTH &&
					Bx2 < BOARD_SIZE - 1 && By2 < BOARD_SIZE - 1)
				{
					Bx2++;
					By2++;
					makeRect2(Bx1, By1, Bx2, By2);
					showBoard();
				}
				else
				{
					printf("!!범위초과 : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			}
			}
		}
	}
	return 0;
}