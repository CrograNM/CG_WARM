#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_COMMAND 10
#define MAX_LEFTCOUNT 20
#define SCORE_BONUS 10000
#define JOKER_MULTIPLE 10

int board[5][5] = { 0, };	//0: 닫힘, 1: 열림
char word[5][5] = { 0, };	//12개의 랜덤한 대문자 2개씩 + 특수문자@ 1개

int score;
int leftcount;

void initBoard() {

	//점수 초기화
	score = 0;
	leftcount = 0;
	//보드 초기화
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board[i][j] = 0;
			word[i][j] = 0;
		}
	}

	int randABC[12] = {0};
	char tempBoard[25] = {0};
	for (int i = 0; i < 12; i++)
	{
		randABC[i] = (rand() % 26) + 1; //rand 1~26
		for (int j = 0; j < i; j++)
		{
			if (randABC[i] == randABC[j]) i--;
		}
	}
	// 배열에 두 번씩 넣기
	int count[12] = { 0 }; // 각 알파벳이 두 번 들어갔는지 확인
	int filled = 0;
	while (filled < 24)
	{
		int randIndex = rand() % 25;
		if (tempBoard[randIndex] == 0)
		{
			int charIndex = filled / 2;
			if (count[charIndex] < 2)
			{
				tempBoard[randIndex] = 'A' + randABC[charIndex] - 1; // 알파벳으로 변환
				count[charIndex]++;
				filled++;
			}
		}
	}
	// 남은 한 자리에 '@' 넣기
	for (int i = 0; i < 25; i++)
	{
		if (tempBoard[i] == 0)
		{
			tempBoard[i] = '@';
			break;
		}
	}

	// 1차원 tempBoard 배열을 전역 변수 word 5x5 배열에 대입
	int index = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			word[i][j] = tempBoard[index++];
		}
	}
}
void printWordInBoard(char word) {
	if ('A' <= word && word <= 'Z')
	{
		int n = ((int)word - 64) % 15 + 1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
		printf("%4c", word);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else 
	{
		printf("%4c", word);
	}
}
void showBoard() {
	system("cls"); //콘솔화면 지우기
	printf("\n      a   b   c   d   e\n\n");
	for (int i = 0; i < 5; i++) {
		printf("%3d", i + 1);
		for (int j = 0; j < 5; j++) {
			switch (board[i][j]) {
			case 0:
				printf("%4c", '*');
				break;
			case 1:
				printWordInBoard(word[i][j]);
				break;
			}
		}
		printf("\n\n");
	}
	printf("score: %d\n", score);
	printf("left count: %d\n", MAX_LEFTCOUNT - leftcount);
}
int compareBoard(char* input1, char* input2)
{
	// 행과 열을 나타내는 변수
	int row1, col1, row2, col2;
	// 점수의 상태를 나타내는 변수
	int state = 0; //0: fail, 1: getPoint, 2: getJoker!

	// 입력값이 유효한지 확인 (a~e, 1~5)
	if (strlen(input1) == 2 && input1[0] >= 'a' && input1[0] <= 'e' && input1[1] >= '1' && input1[1] <= '5' &&
		strlen(input2) == 2 && input2[0] >= 'a' && input2[0] <= 'e' && input2[1] >= '1' && input2[1] <= '5')
	{
		// 1~5를 0~4로 변환 (숫자가 열을 맡음)
		col1 = input1[0] - 'a';
		col2 = input2[0] - 'a';

		// a~e를 0~4로 변환 (문자가 행을 맡음)
		row1 = input1[1] - '1';
		row2 = input2[1] - '1';

		// 변환된 인덱스 출력
		printf("%s -> [%d][%d]\n", input1, row1, col1);
		printf("%s -> [%d][%d]\n", input2, row2, col2);
		
		// board 확인 후 열려있는지 체크 -> 작업 수행 후 열려있는지, 유효한지 확인 완료상태
		if (board[row1][col1] == 1 || board[row2][col2] == 1) 
		{
			printf("이미 열려있는 칸이 있습니다!\n");
			return false;
		}
		else 
		{
			//1. 특수문자'@'(조커) 체크
			if (word[row1][col1] == '@' || word[row2][col2] == '@') {
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				state = 2; //상태를 '조커 발견'으로 변경
				//둘 중 하나가 조커라면 -> 둘 모두를 열고, 나머지 한개의 같은 문자를 찾아내서 연다.
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						// 같은 칸을 다시 열지 않도록 방지
						if ((i == row1 && j == col1) || (i == row2 && j == col2))
						{
							continue;  // 현재 열려있는 칸이면 건너뜀
						}
						// 나머지 같은 문자를 찾아서 연다.
						if (word[i][j] == word[row1][col1] || word[i][j] == word[row2][col2])
						{
							board[i][j] = 1;
						}
					}
				}
			}
			//2. 두 문자가 같은지 체크
			else if (word[row1][col1] == word[row2][col2]) 
			{
				//두 문자가 서로 같다면 보드를 연다
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				state = 1; //상태를 '점수 획득'으로 변경
			}
			//3. 특수문자도 없고, 두 문자가 같지도 않다면 일단 보여주고, 2초 뒤에 닫는다
			else 
			{
				// 실패, 상태 변경 없음
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				showBoard();
				Sleep(3000);
				board[row1][col1] = 0;
				board[row2][col2] = 0;
			}
			//이후 true를 리턴하여 남은 보드를 보여주겠다 설정하고 나간다.
			leftcount++;
			switch (state) {
			case 1:
				score += SCORE_BONUS;
				break;
			case 2:
				score += (SCORE_BONUS * JOKER_MULTIPLE);
				break;
			}
			return true;
		}
	}
	else
	{
		printf("유효하지 않은 입력이 있습니다!\n");
		return false;
	}
}

int main() 
{
	srand(time(0));

	char input1[3];
	char input2[3];

	initBoard();
	showBoard();
	while (1)
	{
		if (leftcount == MAX_LEFTCOUNT) {
			printf("[END!]\n");
			return 0;
		}
		printf("input command : ");

		// 한 번의 입력만 받을 때를 위한 배열
		char input[10];

		// 입력받기 (최대 한 번의 입력을 기다림)
		scanf(" %s", input);

		// 프로그램 종료
		if (input[0] == 'q' && strlen(input) == 1)
		{
			printf("프로그램을 종료합니다.\n");
			return 0;
		}
		// 게임 리셋
		else if (input[0] == 'r' && strlen(input) == 1)
		{
			initBoard();
			showBoard();
			printf("게임 상황 초기화 완료.\n\n");
		}
		// 두 칸의 입력을 받을 경우 (예: a1 b2)
		else if (strlen(input) == 2) // 첫 번째 입력이 두 글자일 경우
		{
			char input2[10];
			scanf(" %s", input2);

			if (strlen(input2) == 2)
			{
				int failcheck = false;
				failcheck = compareBoard(input, input2);
				// 반환 성공 시 보드 출력
				if (failcheck == true)
				{
					showBoard();
				}
			}
			else
			{
				printf("명령어 형식을 지켜주세요.(a1 b2)\n\n");
			}
		}
		else
		{
			printf("유효하지 않은 입력입니다. 다시 입력해주세요.\n");
		}
	}	
	return 0;
}