#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BOARD_SIZE 30
#define MAX_LENGTH 25

// �� 2���� �迭�� �����ϸ� ���带 ���
char rect1[BOARD_SIZE][BOARD_SIZE]; // '.': not Rect, 'O': is Rect

void initRect() {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			rect1[i][j] = '.';
		}
	}
}
void showBoard() {
	system("cls"); //�ܼ�ȭ�� �����
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			printf("%2c", rect1[i][j]);
		}
		printf("\n");
	} 
	//printf("\n\n");
}
void makeRect(int x1, int y1, int x2, int y2) {
	// x1, y1, x2, y2�� ���ؿ� �°� �����Ѵ�
	// x1 �� ������� ��ȯ�� x1�� 
	// ���� ��ǥ�� ���� �ε������� ���ĺ�'O'�� �ٲ��ָ� �ȴ�.
	int height = y2 - y1 + 1;	//for���� iũ��
	int width = x2 - x1 + 1;	//for���� jũ��
		
	//������ ���� ���ϱ�
	x1 = (BOARD_SIZE + x1) % BOARD_SIZE;
	y1 = (BOARD_SIZE + y1) % BOARD_SIZE;
	int leftWidth = x1 + width - BOARD_SIZE;
	int leftHeight = y1 + height - BOARD_SIZE;
	int tempLeftWidth = 0;
	int tempLeftHeight = 0;
	if (leftWidth > 0) {
		tempLeftWidth = leftWidth;
	}
	if (leftHeight > 0) {
		tempLeftHeight = leftHeight;
	}
	
	int i, j;
	if (leftWidth <= 0 && leftHeight <= 0)
	{
		initRect();
		for (i = y1; i < y1 + height; i++)
		{
			for (j = x1; j < x1 + width; j++)
			{
				rect1[i][j] = 'O';
			}
		}
	}
	else
	{
		initRect();
		if (leftWidth > 0 && leftHeight > 0) {
			for (i = 0; i < leftHeight; i++) 
			{
				for (j = 0; j < leftWidth; j++) 
				{
					rect1[i][j] = 'O';
				}
			}
		}
		if (leftWidth > 0)
		{

			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = x1; j < BOARD_SIZE; j++)
				{
					rect1[i][j] = 'O';
				}
			}
			for (i = y1; i < y1 + height - tempLeftHeight; i++)
			{
				for (j = 0; j < leftWidth; j++)
				{
					rect1[i][j] = 'O';
				}
			}
		}
		if (leftHeight > 0)
		{
			for (j = x1; j < x1 + width - tempLeftWidth; j++)
			{
				for (i = y1; i < BOARD_SIZE; i++)
				{
					rect1[i][j] = 'O';
				}
				for (i = 0; i < leftHeight; i++)
				{
					rect1[i][j] = 'O';
				}
			}
		}
	}
}

int main()
{
	initRect();
	showBoard();

	int init = 0;
	int x1, y1, x2, y2;
	char input;
	int wide = 0;
	int width = 0;
	int height = 0;

	while (1) {
		if (init == 0) 
		{	// ��ǥ����
			printf("input coord value (x1, y1), (x2, y2): ");
			scanf(" %d %d %d %d", &x1, &y1, &x2, &y2);	
			if (x2 < x1)
			{
				int temp = x1;
				x1 = x2;
				x2 = temp;
			}
			if (y2 < y1)
			{
				int temp = y1;
				y1 = y2;
				y2 = temp;
			}
			width = x2 - x1 + 1;
			height = y2 - y1 + 1;
			if (width <= MAX_LENGTH && height <= MAX_LENGTH) 
			{
				if (0 <= x1 && x1 < BOARD_SIZE && 0 <= y1 && y1 < BOARD_SIZE &&
					0 <= x2 && x2 < BOARD_SIZE && 0 <= y2 && y2 < BOARD_SIZE)
				{
					// ��� �Է��� �������̶�� ���� �ݺ��� -> ��ɾ� �Է����� �̵�
					// ������ �Էµ� ��ǥ�� �簢�� �������ֱ�
					// ��ǥ�� � ������ �� ū���� ���������� �´�
					wide = width * height;
					makeRect(x1, y1, x2, y2);
					showBoard();
					init = 1;
				}	
				else
				{
					printf("�ʱ� ��ǥ�� ���� �ȿ� ������ּ���\n");
				}
			}
			else
			{
				printf("�ִ� ���̴� [%d]�Դϴ�! ��ǥ�� �������ּ���\n", MAX_LENGTH);
			}
		}
		else 
		{	// ��ǥ������ ������ ���� �ݺ������� ��ɾ� �Է�
			printf("input command : ");
			scanf(" %c", &input);

			switch (input) {
			case 'q':
				printf("���α׷��� �����մϴ�.\n");
				break;
			case 'r':
				init = 0;
				initRect();
				showBoard();
				printf("���α׷��� �ʱ�ȭ�Ͽ����ϴ�.\n");
				break;
			case 'x':
				x1--;
				x2--;
				makeRect(x1, y1, x2, y2);
				showBoard();
				break;
			case 'X':
				x1++;
				x2++;
				makeRect(x1, y1, x2, y2);
				showBoard();
				break;
			case 'y':
				y1--;
				y2--;
				makeRect(x1, y1, x2, y2);
				showBoard();
				break;
			case 'Y':
				y1++;
				y2++;
				makeRect(x1, y1, x2, y2);
				showBoard();
				break;
			case 's':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if(width < MAX_LENGTH && height < MAX_LENGTH && 
					x2 < BOARD_SIZE - 1 && y2 < BOARD_SIZE - 1)
				{
					x2++;
					y2++;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			case 'i':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (width < MAX_LENGTH && x2 < BOARD_SIZE - 1)
				{	//���� �˻�, ������ �ʰ� �˻�
					x2++;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			case 'I':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (x1 + 1 < x2)
				{	//�ּ� ���� �˻�
					x2--;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;		
			case 'j':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (height < MAX_LENGTH && y2 < BOARD_SIZE - 1)
				{	//���� �˻�, ������ �ʰ� �˻�
					y2++;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			case 'J':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (y1 + 1 < y2)
				{	//�ּ� ���� �˻�
					y2--;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;		
			case 'a':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (width < MAX_LENGTH && x2 < BOARD_SIZE - 1 && y1 + 1 < y2)
				{
					x2++;
					y2--;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			case 'A':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				if (height < MAX_LENGTH && y2 < BOARD_SIZE - 1 && x1 + 1 < x2)
				{
					x2--;
					y2++;
					makeRect(x1, y1, x2, y2);
					showBoard();
				}
				else
				{
					printf("!!�����ʰ� : 2~%d, or board Exit\n", MAX_LENGTH);
				}
				break;
			case 'm':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				wide = width * height;
				printf(" ���� : %d x %d = %d\n", width , height, wide);
				break;
			case 'n':
				width = x2 - x1 + 1;
				height = y2 - y1 + 1;
				wide = width * height;
				printf(" ��ü ���� : %d x %d = %d\n", BOARD_SIZE, BOARD_SIZE, BOARD_SIZE * BOARD_SIZE);
				printf(" �簢�� ���� : %d\n", wide);
				printf(" ���� ���� : (%d/%d)*100 = %d%%\n", wide, BOARD_SIZE * BOARD_SIZE, (100 * wide) / (BOARD_SIZE * BOARD_SIZE));
				break;
			}
		}
	}
	return 0;
}