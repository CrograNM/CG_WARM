#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <math.h> // 맨해튼 거리 계산을 위한 라이브러리

typedef struct PLAYER {
	int x;
	int y;
	int exist;
}PLAYER;
PLAYER player;							//player.y : 0 ~ 29, player.x : 0 ~ 29

#define BOARD_SIZE 30
char board[BOARD_SIZE][BOARD_SIZE];		// 이 2차원 배열을 수정하며 보드를 출력
char pFigure = '@';						// 플레이어의 모양 초기화

void initPlayer();
void initBoard();
void showBoard();
void setBoard();
void move(char WASD);

void initPlayer() {
	player.x = 0;
	player.y = 0;
	player.exist = false;
}
void initBoard() {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = '1';
		}
	}
}
void showBoard() {
	system("cls"); //콘솔화면 지우기
	int blockCount = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == pFigure) {
				//플레이어 출력
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//밝은빨강색
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//콘솔기본색
			}
			else if (board[i][j] == 'X')
			{
				//장애물 출력
				blockCount++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//시안색
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//콘솔기본색
			}
			else if (board[i][j] == '1')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	//시안색
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//콘솔기본색
			}
			else
			{
				printf("%2c", board[i][j]);
			}
		}
		printf("\n");
	}
	printf("blockcount = %d\n", blockCount);
	//printf("\n\n");
}
void setBoard()
{
	// 장애물 위치를 추적하기 위한 배열
	int obstacleCount = 0;
	int obstacles[BOARD_SIZE * BOARD_SIZE][2]; // 장애물의 좌표를 저장할 배열

	while (obstacleCount < 30)
	{
		int x = rand() % BOARD_SIZE;
		int y = rand() % BOARD_SIZE;

		// 중복 여부 확인
		int isDuplicate = 0;
		for (int j = 0; j < obstacleCount; j++)
		{
			if (obstacles[j][0] == x && obstacles[j][1] == y)
			{
				isDuplicate = 1; // 중복된 위치
				break;
			}
		}

		// 중복되지 않고, 시작 위치(0,0)와 목표 위치(29,29)를 피할 경우 장애물 추가
		if (!isDuplicate && (x != 0 || y != 0) && (x != 29 || y != 29))
		{
			board[y][x] = 'X';
			obstacles[obstacleCount][0] = x;
			obstacles[obstacleCount][1] = y;
			obstacleCount++;
		}
	}
	
	// 경로 생성 애니메이션
	int x = 0, y = 0;
	board[y][x] = 'O';
	int direction = 1; // 현재 방향
	int prevDirection = -1; // 이전 방향
	int sameDirectionCount = 0; // 동일 방향 이동 횟수

	while (1)
	{
		if (x == 29 && y == 29)
		{ // 목표 지점에 도달하면 종료
			showBoard();
			break;
		}

		int possibleDirections[4] = { 1, 1, 1, 1 }; // 0: Left, 1: Right, 2: Up, 3: Down

		// 현재 좌표 기준으로 한 칸 및 두 칸 앞이 이동 가능한지 체크
		if (x - 1 < 0 || board[y][x - 1] == 'X' || (x - 2 >= 0 && board[y][x - 2] == 'X')) 
			possibleDirections[0] = 0; // Left
		if (x + 1 >= BOARD_SIZE || board[y][x + 1] == 'X' || (x + 2 > BOARD_SIZE || board[y][x + 2] == 'X')) 
			possibleDirections[1] = 0; // Right
		if (y - 1 < 0 || board[y - 1][x] == 'X' || (y - 2 >= 0 && board[y - 2][x] == 'X')) 
			possibleDirections[2] = 0; // Up
		if (y + 1 >= BOARD_SIZE || board[y + 1][x] == 'X' || (y + 2 > BOARD_SIZE || board[y + 2][x] == 'X'))
			possibleDirections[3] = 0; // Down

		// 동일 방향 5회 제한 적용
		if (sameDirectionCount >= 5)
		{
			possibleDirections[prevDirection] = 0; // 이전 방향으로 다시 이동하지 않도록
		}

		// 가능한 방향 중 무작위 선택 (단, 이전과 반대 방향은 제외)
		int loopCount = 0;
		while (1)
		{
			loopCount++;
			direction = rand() % 4;
			if (possibleDirections[direction] && direction != (prevDirection ^ 1)) break;
			if (loopCount > 1000)
			{
				showBoard();
				break;
			}
		}

		// 방향에 따른 이동
		if (direction == 0) --x;        // Left
		else if (direction == 1) ++x;   // Right
		else if (direction == 2) --y;   // Up
		else if (direction == 3) ++y;   // Down

		board[y][x] = 'O'; // 경로 생성
		//showBoard();
		//Sleep(100);

		// 이동 횟수 및 방향 업데이트
		if (direction == prevDirection)
		{
			sameDirectionCount++;
		}
		else
		{
			sameDirectionCount = 1;
			prevDirection = direction;
		}
	}
}
void move(char WASD) {
	switch (WASD) 
	{
	case 'w':
	{
		//해당 인덱스가 보드를 벗어나지 않고, 'O'문자라면
		//해당 인덱스로 플레이어 이동 및 원래 자리 'O'문자로 바꾸기. (보드배열에 적용)
		if (player.y - 1 >= 0)
		{
			if (board[player.y - 1][player.x] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. 현재 자리를 수정
				player.y--;								// 2. 플레이어 이동
				board[player.y][player.x] = pFigure;	// 3. 이동된 자리를 수정
			}
			else
			{
				printf("경로 범위를 벗어납니다.\n");
			}
		}
		else
		{
			printf("보드 범위를 벗어납니다.\n");
		}
		break;
	}
	case 'a':
	{
		//해당 인덱스가 보드를 벗어나지 않고, 'O'문자라면
		//해당 인덱스로 플레이어 이동 및 원래 자리 'O'문자로 바꾸기. (보드배열에 적용)
		if (player.x - 1 >= 0)
		{
			if (board[player.y][player.x - 1] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. 현재 자리를 수정
				player.x--;								// 2. 플레이어 이동
				board[player.y][player.x] = pFigure;	// 3. 이동된 자리를 수정
			}
			else
			{
				printf("경로 범위를 벗어납니다.\n");
			}
		}
		else
		{
			printf("보드 범위를 벗어납니다.\n");
		}
		break;
	}
	case 's':
	{
		//해당 인덱스가 보드를 벗어나지 않고, 'O'문자라면
		//해당 인덱스로 플레이어 이동 및 원래 자리 'O'문자로 바꾸기. (보드배열에 적용)
		if (player.y + 1 <= 29)
		{
			if (board[player.y + 1][player.x] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. 현재 자리를 수정
				player.y++;								// 2. 플레이어 이동
				board[player.y][player.x] = pFigure;	// 3. 이동된 자리를 수정
			}
			else
			{
				printf("경로 범위를 벗어납니다.\n");
			}
		}
		else
		{
			printf("보드 범위를 벗어납니다.\n");
		}
		break;
	}
	case 'd':
	{
		//해당 인덱스가 보드를 벗어나지 않고, 'O'문자라면
		//해당 인덱스로 플레이어 이동 및 원래 자리 'O'문자로 바꾸기. (보드배열에 적용)
		if (player.x + 1 <= 29)
		{
			if (board[player.y][player.x + 1] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. 현재 자리를 수정
				player.x++;								// 2. 플레이어 이동
				board[player.y][player.x] = pFigure;	// 3. 이동된 자리를 수정
			}
			else
			{
				printf("경로 범위를 벗어납니다.\n");
			}
		}
		else
		{
			printf("보드 범위를 벗어납니다.\n");
		}
		break;
	}

	}
}

int main()
{
	srand(time(0));
	initPlayer();
	initBoard();
	showBoard();
	char input;			//명령어
	int made = false;	//객체 생성 여부
	setBoard();

	while (1)
	{
		printf("input command : ");
		scanf(" %c", &input);
		switch (input)
		{
		case 'q':
		{
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		case 'z':	//보드판 초기화 및 경로 다시만들기
		{	
			made = false;	//객체 생성 여부 초기화
			pFigure = '@';	//플레이어 모양 초기화
			initPlayer();	//플레이어 좌표 및 존재여부 초기화
			initBoard();	//보드 초기화
			setBoard();		//장애물 생성, 경로 생성
			break;
		}
		case 'r':	//임의의 객체 0,0에 생성
		{
			if (made == false)	//객체가 생성되지 않을때 작동
			{
				made = true;	//객체 생성됨.
				//객체 생성과정 
				switch (rand() % 4) {
				case 0:
					pFigure = '@';
					break;
				case 1:
					pFigure = '#';
					break;
				case 2:
					pFigure = '$';
					break;
				case 3:
					pFigure = '%';
					break;
				}
				player.exist = true;
				board[player.y][player.x] = pFigure;
				showBoard();
			}
			else
			{
				printf("이미 객체가 생성되었습니다.\n");
			}
			break;
		}
		case 'w': case 'a': case 's': case 'd':
		{
			//객체 생성 후 움직이기
			if (player.exist == true)
			{
				move(input);
				showBoard();
			}
			else
			{
				printf("아직 객체가 생성되지 않았습니다.\n");
			}
			break;
		}
		default:
			printf("잘못된 명령어\n");
			break;
		}
	}
	return 0;
}