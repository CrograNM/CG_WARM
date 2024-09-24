#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <math.h> // ����ư �Ÿ� ����� ���� ���̺귯��

typedef struct PLAYER {
	int x;
	int y;
	int exist;
}PLAYER;
PLAYER player;							//player.y : 0 ~ 29, player.x : 0 ~ 29

#define BOARD_SIZE 30
char board[BOARD_SIZE][BOARD_SIZE];		// �� 2���� �迭�� �����ϸ� ���带 ���
char pFigure = '@';						// �÷��̾��� ��� �ʱ�ȭ

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
	system("cls"); //�ܼ�ȭ�� �����
	int blockCount = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == pFigure) {
				//�÷��̾� ���
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//����������
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//�ֱܼ⺻��
			}
			else if (board[i][j] == 'X')
			{
				//��ֹ� ���
				blockCount++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//�þȻ�
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//�ֱܼ⺻��
			}
			else if (board[i][j] == '1')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	//�þȻ�
				printf("%2c", board[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//�ֱܼ⺻��
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
	// ��ֹ� ��ġ�� �����ϱ� ���� �迭
	int obstacleCount = 0;
	int obstacles[BOARD_SIZE * BOARD_SIZE][2]; // ��ֹ��� ��ǥ�� ������ �迭

	while (obstacleCount < 30)
	{
		int x = rand() % BOARD_SIZE;
		int y = rand() % BOARD_SIZE;

		// �ߺ� ���� Ȯ��
		int isDuplicate = 0;
		for (int j = 0; j < obstacleCount; j++)
		{
			if (obstacles[j][0] == x && obstacles[j][1] == y)
			{
				isDuplicate = 1; // �ߺ��� ��ġ
				break;
			}
		}

		// �ߺ����� �ʰ�, ���� ��ġ(0,0)�� ��ǥ ��ġ(29,29)�� ���� ��� ��ֹ� �߰�
		if (!isDuplicate && (x != 0 || y != 0) && (x != 29 || y != 29))
		{
			board[y][x] = 'X';
			obstacles[obstacleCount][0] = x;
			obstacles[obstacleCount][1] = y;
			obstacleCount++;
		}
	}
	
	// ��� ���� �ִϸ��̼�
	int x = 0, y = 0;
	board[y][x] = 'O';
	int direction = 1; // ���� ����
	int prevDirection = -1; // ���� ����
	int sameDirectionCount = 0; // ���� ���� �̵� Ƚ��

	while (1)
	{
		if (x == 29 && y == 29)
		{ // ��ǥ ������ �����ϸ� ����
			showBoard();
			break;
		}

		int possibleDirections[4] = { 1, 1, 1, 1 }; // 0: Left, 1: Right, 2: Up, 3: Down

		// ���� ��ǥ �������� �� ĭ �� �� ĭ ���� �̵� �������� üũ
		if (x - 1 < 0 || board[y][x - 1] == 'X' || (x - 2 >= 0 && board[y][x - 2] == 'X')) 
			possibleDirections[0] = 0; // Left
		if (x + 1 >= BOARD_SIZE || board[y][x + 1] == 'X' || (x + 2 > BOARD_SIZE || board[y][x + 2] == 'X')) 
			possibleDirections[1] = 0; // Right
		if (y - 1 < 0 || board[y - 1][x] == 'X' || (y - 2 >= 0 && board[y - 2][x] == 'X')) 
			possibleDirections[2] = 0; // Up
		if (y + 1 >= BOARD_SIZE || board[y + 1][x] == 'X' || (y + 2 > BOARD_SIZE || board[y + 2][x] == 'X'))
			possibleDirections[3] = 0; // Down

		// ���� ���� 5ȸ ���� ����
		if (sameDirectionCount >= 5)
		{
			possibleDirections[prevDirection] = 0; // ���� �������� �ٽ� �̵����� �ʵ���
		}

		// ������ ���� �� ������ ���� (��, ������ �ݴ� ������ ����)
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

		// ���⿡ ���� �̵�
		if (direction == 0) --x;        // Left
		else if (direction == 1) ++x;   // Right
		else if (direction == 2) --y;   // Up
		else if (direction == 3) ++y;   // Down

		board[y][x] = 'O'; // ��� ����
		//showBoard();
		//Sleep(100);

		// �̵� Ƚ�� �� ���� ������Ʈ
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
		//�ش� �ε����� ���带 ����� �ʰ�, 'O'���ڶ��
		//�ش� �ε����� �÷��̾� �̵� �� ���� �ڸ� 'O'���ڷ� �ٲٱ�. (����迭�� ����)
		if (player.y - 1 >= 0)
		{
			if (board[player.y - 1][player.x] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. ���� �ڸ��� ����
				player.y--;								// 2. �÷��̾� �̵�
				board[player.y][player.x] = pFigure;	// 3. �̵��� �ڸ��� ����
			}
			else
			{
				printf("��� ������ ����ϴ�.\n");
			}
		}
		else
		{
			printf("���� ������ ����ϴ�.\n");
		}
		break;
	}
	case 'a':
	{
		//�ش� �ε����� ���带 ����� �ʰ�, 'O'���ڶ��
		//�ش� �ε����� �÷��̾� �̵� �� ���� �ڸ� 'O'���ڷ� �ٲٱ�. (����迭�� ����)
		if (player.x - 1 >= 0)
		{
			if (board[player.y][player.x - 1] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. ���� �ڸ��� ����
				player.x--;								// 2. �÷��̾� �̵�
				board[player.y][player.x] = pFigure;	// 3. �̵��� �ڸ��� ����
			}
			else
			{
				printf("��� ������ ����ϴ�.\n");
			}
		}
		else
		{
			printf("���� ������ ����ϴ�.\n");
		}
		break;
	}
	case 's':
	{
		//�ش� �ε����� ���带 ����� �ʰ�, 'O'���ڶ��
		//�ش� �ε����� �÷��̾� �̵� �� ���� �ڸ� 'O'���ڷ� �ٲٱ�. (����迭�� ����)
		if (player.y + 1 <= 29)
		{
			if (board[player.y + 1][player.x] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. ���� �ڸ��� ����
				player.y++;								// 2. �÷��̾� �̵�
				board[player.y][player.x] = pFigure;	// 3. �̵��� �ڸ��� ����
			}
			else
			{
				printf("��� ������ ����ϴ�.\n");
			}
		}
		else
		{
			printf("���� ������ ����ϴ�.\n");
		}
		break;
	}
	case 'd':
	{
		//�ش� �ε����� ���带 ����� �ʰ�, 'O'���ڶ��
		//�ش� �ε����� �÷��̾� �̵� �� ���� �ڸ� 'O'���ڷ� �ٲٱ�. (����迭�� ����)
		if (player.x + 1 <= 29)
		{
			if (board[player.y][player.x + 1] == 'O')
			{
				board[player.y][player.x] = 'O';		// 1. ���� �ڸ��� ����
				player.x++;								// 2. �÷��̾� �̵�
				board[player.y][player.x] = pFigure;	// 3. �̵��� �ڸ��� ����
			}
			else
			{
				printf("��� ������ ����ϴ�.\n");
			}
		}
		else
		{
			printf("���� ������ ����ϴ�.\n");
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
	char input;			//��ɾ�
	int made = false;	//��ü ���� ����
	setBoard();

	while (1)
	{
		printf("input command : ");
		scanf(" %c", &input);
		switch (input)
		{
		case 'q':
		{
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 'z':	//������ �ʱ�ȭ �� ��� �ٽø����
		{	
			made = false;	//��ü ���� ���� �ʱ�ȭ
			pFigure = '@';	//�÷��̾� ��� �ʱ�ȭ
			initPlayer();	//�÷��̾� ��ǥ �� ���翩�� �ʱ�ȭ
			initBoard();	//���� �ʱ�ȭ
			setBoard();		//��ֹ� ����, ��� ����
			break;
		}
		case 'r':	//������ ��ü 0,0�� ����
		{
			if (made == false)	//��ü�� �������� ������ �۵�
			{
				made = true;	//��ü ������.
				//��ü �������� 
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
				printf("�̹� ��ü�� �����Ǿ����ϴ�.\n");
			}
			break;
		}
		case 'w': case 'a': case 's': case 'd':
		{
			//��ü ���� �� �����̱�
			if (player.exist == true)
			{
				move(input);
				showBoard();
			}
			else
			{
				printf("���� ��ü�� �������� �ʾҽ��ϴ�.\n");
			}
			break;
		}
		default:
			printf("�߸��� ��ɾ�\n");
			break;
		}
	}
	return 0;
}