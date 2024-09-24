#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array1[4][4];
int array2[4][4];
int arrayR[4][4];

// ��� �ʱ�ȭ �� ���
void makeArray() {
	int TwoCount1 = 0;
	int TwoCount2 = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (TwoCount1 < 2) {
				array1[i][j] = rand() % 3; //0, 1, 2
			}
			else {
				array1[i][j] = rand() % 2; //0, 1
			}
			if (array1[i][j] == 2) TwoCount1++;

			if (TwoCount2 < 2) {
				array2[i][j] = rand() % 3; //0, 1, 2
			}
			else {
				array2[i][j] = rand() % 2; //0, 1
			}
			if (array2[i][j] == 2) TwoCount2++;
		}
	}
}
void showArray() {
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", array1[i][j]);
		}
		printf("   | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", array2[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
}

// ����� ����, ����, ����
void addArray() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arrayR[i][j] = array1[i][j] + array2[i][j];
		}
	}
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", arrayR[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}
void remArray() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arrayR[i][j] = array1[i][j] - array2[i][j];
		}
	}
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", arrayR[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}
void mulArray()
{
	for (int k = 0; k < 4; k++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				arrayR[k][j] += array1[k][i] * array2[i][j];
			}
		}
	}
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", arrayR[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}

// ��Ľ� ��� 
int** createMatrix(int n) {
	int** matrix = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(n * sizeof(int));
	}
	return matrix;
}
void freeMatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
int det(int n, int** Matrix) {
	if (n == 1) return Matrix[0][0];

	int i, j, k;
	int** minor_Matrix = createMatrix(n - 1);
	int sum = 0;
	int sign = 1;

	for (k = 0; k < n; k++) {
		// ����� ����
		for (i = 0; i < n - 1; i++) {
			for (j = 0; j < n - 1; j++) {
				if (j < k)
					minor_Matrix[i][j] = Matrix[i + 1][j];
				else
					minor_Matrix[i][j] = Matrix[i + 1][j + 1];
			}
		}
		// ��������� ��Ľ� ���
		sum += sign * Matrix[0][k] * det(n - 1, minor_Matrix);
		sign = -sign; // ��ȣ ����
	}

	freeMatrix(minor_Matrix, n - 1);
	return sum;
}

// ��ġ���
void showTrans(int** Trans1, int** Trans2) {
	printf(" -------------Transpos-------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", Trans1[i][j]);
		}
		printf("   | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", Trans2[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	//printf("\n");
}

// ¦��, Ȧ�� ǥ��
void evenArray() {	//¦��
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			if (array1[i][j] % 2 == 0) {
				printf("%3d", array1[i][j]);
			}
			else {
				printf("  x");
			}
		}
		printf("   | ");
		for (int j = 0; j < 4; j++) {
			if (array2[i][j] % 2 == 0) {
				printf("%3d", array2[i][j]);
			}
			else {
				printf("  x");
			}
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}
void oddArray() {	//Ȧ��
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			if (array1[i][j] % 2 == 1) {
				printf("%3d", array1[i][j]);
			}
			else {
				printf("  x");
			}
		}
		printf("   | ");
		for (int j = 0; j < 4; j++) {
			if (array2[i][j] % 2 == 1) {
				printf("%3d", array2[i][j]);
			}
			else {
				printf("  x");
			}
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}

// ���� ���ϱ�
void numMulArray(int num) {
	printf(" ----------------------------------\n");
	for (int i = 0; i < 4; i++) {
		printf(" | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", num * array1[i][j]);
		}
		printf("   | ");
		for (int j = 0; j < 4; j++) {
			printf("%3d", num * array2[i][j]);
		}
		printf("  | ");
		printf("\n");
	}
	printf(" ----------------------------------\n");
	printf("\n");
}

// ���� �Լ�
int main() {
	srand(time(0));
	char input;
	int cir = 0;

	printf("randomized matrix arrays\n");
	makeArray();
	showArray();
	printf("\n");

	while (1) {
		printf("Input Command : ");
		scanf(" %c", &input);
		switch (input)
		{
		case 'q': //����
		{
			printf("----quit program----\n");
			return 0;
		}
		case 's': //�迭 �ʱ�ȭ
		{
			makeArray();
			showArray();
			break;
		}
		case 'm': //����
		{
			showArray();
			mulArray();
			break;
		}
		case 'a': //����
		{
			showArray();
			addArray();
			break;
		}
		case 'd': //����
		{
			showArray();
			remArray();
			break;
		}
		case 'r': //��Ľ��� �� (2�� ���)
		{
			int n = 4;
			int** matrix1 = createMatrix(n);
			int** matrix2 = createMatrix(n);
			// array1 ���� matrix1�� ����
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					matrix1[i][j] = array1[i][j];
				}
			}
			// array2 ���� matrix2�� ����
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					matrix2[i][j] = array2[i][j];
				}
			}
			showArray();
			printf(" Determinant_1: %d\n", det(n, matrix1));
			printf(" Determinant_2: %d\n", det(n, matrix2));
			printf("\n");
			freeMatrix(matrix1, n);
			freeMatrix(matrix2, n);
			break;
		}
		case 't': //��ġ ��İ� �� ��Ľ��� �� (2�� ���)
		{
			//���ο� 2�����迭�� �����, x,y�ε����� ���� �ٲ㼭 �����ϱ�
			int n = 4;
			int** trans1 = createMatrix(n);
			int** trans2 = createMatrix(n);
			// array1 ���� Trans1�� ����
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					trans1[j][i] = array1[i][j];
				}
			}
			// array2 ���� Trans2�� ����
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					trans2[j][i] = array2[i][j];
				}
			}
			showArray();
			showTrans(trans1, trans2);
			printf(" Determinant_1: %d\n", det(n, trans1));
			printf(" Determinant_2: %d\n", det(n, trans2));
			printf("\n");
			freeMatrix(trans1, n);
			freeMatrix(trans2, n);
			break;
		}
		case 'e': {//¦��, Ȧ��, �������
			if (cir % 3 == 0) 
			{
				evenArray();
			}
			else if (cir % 3 == 1) 
			{
				oddArray();
			}
			else 
			{ 
				showArray(); 
				printf("\n"); 
			}
			cir++;
			break;
		}
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': {
			int i = input - '0';
			numMulArray(i);
			break;
		}
		default:
			printf("�߸��� ��ɾ� �Դϴ�.\n\n");
			break;
		}
	}
	return 0;
}