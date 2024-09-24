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

int board[5][5] = { 0, };	//0: ����, 1: ����
char word[5][5] = { 0, };	//12���� ������ �빮�� 2���� + Ư������@ 1��

int score;
int leftcount;

void initBoard() {

	//���� �ʱ�ȭ
	score = 0;
	leftcount = 0;
	//���� �ʱ�ȭ
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
	// �迭�� �� ���� �ֱ�
	int count[12] = { 0 }; // �� ���ĺ��� �� �� ������ Ȯ��
	int filled = 0;
	while (filled < 24)
	{
		int randIndex = rand() % 25;
		if (tempBoard[randIndex] == 0)
		{
			int charIndex = filled / 2;
			if (count[charIndex] < 2)
			{
				tempBoard[randIndex] = 'A' + randABC[charIndex] - 1; // ���ĺ����� ��ȯ
				count[charIndex]++;
				filled++;
			}
		}
	}
	// ���� �� �ڸ��� '@' �ֱ�
	for (int i = 0; i < 25; i++)
	{
		if (tempBoard[i] == 0)
		{
			tempBoard[i] = '@';
			break;
		}
	}

	// 1���� tempBoard �迭�� ���� ���� word 5x5 �迭�� ����
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
	system("cls"); //�ܼ�ȭ�� �����
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
	// ��� ���� ��Ÿ���� ����
	int row1, col1, row2, col2;
	// ������ ���¸� ��Ÿ���� ����
	int state = 0; //0: fail, 1: getPoint, 2: getJoker!

	// �Է°��� ��ȿ���� Ȯ�� (a~e, 1~5)
	if (strlen(input1) == 2 && input1[0] >= 'a' && input1[0] <= 'e' && input1[1] >= '1' && input1[1] <= '5' &&
		strlen(input2) == 2 && input2[0] >= 'a' && input2[0] <= 'e' && input2[1] >= '1' && input2[1] <= '5')
	{
		// 1~5�� 0~4�� ��ȯ (���ڰ� ���� ����)
		col1 = input1[0] - 'a';
		col2 = input2[0] - 'a';

		// a~e�� 0~4�� ��ȯ (���ڰ� ���� ����)
		row1 = input1[1] - '1';
		row2 = input2[1] - '1';

		// ��ȯ�� �ε��� ���
		printf("%s -> [%d][%d]\n", input1, row1, col1);
		printf("%s -> [%d][%d]\n", input2, row2, col2);
		
		// board Ȯ�� �� �����ִ��� üũ -> �۾� ���� �� �����ִ���, ��ȿ���� Ȯ�� �Ϸ����
		if (board[row1][col1] == 1 || board[row2][col2] == 1) 
		{
			printf("�̹� �����ִ� ĭ�� �ֽ��ϴ�!\n");
			return false;
		}
		else 
		{
			//1. Ư������'@'(��Ŀ) üũ
			if (word[row1][col1] == '@' || word[row2][col2] == '@') {
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				state = 2; //���¸� '��Ŀ �߰�'���� ����
				//�� �� �ϳ��� ��Ŀ��� -> �� ��θ� ����, ������ �Ѱ��� ���� ���ڸ� ã�Ƴ��� ����.
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						// ���� ĭ�� �ٽ� ���� �ʵ��� ����
						if ((i == row1 && j == col1) || (i == row2 && j == col2))
						{
							continue;  // ���� �����ִ� ĭ�̸� �ǳʶ�
						}
						// ������ ���� ���ڸ� ã�Ƽ� ����.
						if (word[i][j] == word[row1][col1] || word[i][j] == word[row2][col2])
						{
							board[i][j] = 1;
						}
					}
				}
			}
			//2. �� ���ڰ� ������ üũ
			else if (word[row1][col1] == word[row2][col2]) 
			{
				//�� ���ڰ� ���� ���ٸ� ���带 ����
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				state = 1; //���¸� '���� ȹ��'���� ����
			}
			//3. Ư�����ڵ� ����, �� ���ڰ� ������ �ʴٸ� �ϴ� �����ְ�, 2�� �ڿ� �ݴ´�
			else 
			{
				// ����, ���� ���� ����
				board[row1][col1] = 1;
				board[row2][col2] = 1;
				showBoard();
				Sleep(3000);
				board[row1][col1] = 0;
				board[row2][col2] = 0;
			}
			//���� true�� �����Ͽ� ���� ���带 �����ְڴ� �����ϰ� ������.
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
		printf("��ȿ���� ���� �Է��� �ֽ��ϴ�!\n");
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

		// �� ���� �Է¸� ���� ���� ���� �迭
		char input[10];

		// �Է¹ޱ� (�ִ� �� ���� �Է��� ��ٸ�)
		scanf(" %s", input);

		// ���α׷� ����
		if (input[0] == 'q' && strlen(input) == 1)
		{
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		// ���� ����
		else if (input[0] == 'r' && strlen(input) == 1)
		{
			initBoard();
			showBoard();
			printf("���� ��Ȳ �ʱ�ȭ �Ϸ�.\n\n");
		}
		// �� ĭ�� �Է��� ���� ��� (��: a1 b2)
		else if (strlen(input) == 2) // ù ��° �Է��� �� ������ ���
		{
			char input2[10];
			scanf(" %s", input2);

			if (strlen(input2) == 2)
			{
				int failcheck = false;
				failcheck = compareBoard(input, input2);
				// ��ȯ ���� �� ���� ���
				if (failcheck == true)
				{
					showBoard();
				}
			}
			else
			{
				printf("��ɾ� ������ �����ּ���.(a1 b2)\n\n");
			}
		}
		else
		{
			printf("��ȿ���� ���� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
	}	
	return 0;
}