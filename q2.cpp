#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_STR 256

int main()
{

	FILE* inputFile;
	char fname[MAX_STR];

	//���� �̸��� �Է��Ͻÿ� : 
	printf("input filename : ");
	scanf("%s", fname);

	//���� �̸� Ȯ��, ���� -> data.txt
	if ((inputFile = fopen(fname, "r")) == NULL)
	{
		fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
		return 0;
	}

	//�� ���� �ڵ�
	//unsigned short text = 12; //���� ����, 15 -> �Ͼ��
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);

	int c;
	printf("\n");
	while ((c = fgetc(inputFile)) != EOF)
	{
		putchar(c);
	}
	//���ϴݱ�
	fclose(inputFile);
	printf("\n");

	char input;
	char strBuffer[MAX_STR];
	int coloredWord = 0;
	int c_OnOff = 0; //0: off����, 1: on����
	int d_OnOff = 0; //0: off����, 1: on����
	int e_OnOff = 0; //0: off����, 1: on����
	int e_Count = 0; //3 ������ printf("@@");
	int f_OnOff = 0; //0: off����, 1: on����
	int g_OnOff = 0; //0: off����, 1: on����
	int r_123 = 0; //0: ��������, 1: ��������, 2: �������

	int lineCount = 0;
	char stringTemp[10][MAX_STR];
	int wordCountTemp[10];
	int temp;
	char strSwap[MAX_STR];

	while (1)
	{
		printf("Input Command : ");
		scanf(" %c", &input);

		switch (input)
		{
		case 'q':
		{
			printf("���α׷��� �����մϴ�.\n");
			return 0;
			break;
		}
		case 't': //test
		{
			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
				return 0;
			}
			printf("\n");
			while ((c = fgetc(inputFile)) != EOF)
			{
				putchar(c);
			}
			//���ϴݱ�
			fclose(inputFile);
			printf("\n");
			break;
		}

		case 'c': //�빮�� �ܾ� �������
		{
			coloredWord = 0;
			if (c_OnOff == 0)
			{
				c_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// �ܾ� �ϳ��� ����
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						if (ptr[0] >= 65 && ptr[0] <= 90)
						{
							// ���� ����:12, �⺻��:7
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							printf("%s", ptr);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							if (ptr[strlen(ptr) - 1] != '\n')
								printf(" ");
							coloredWord++;
						}
						else
						{
							printf("%s", ptr);
							if (ptr[strlen(ptr) - 1] != '\n')
								printf(" ");
						}
						ptr = strtok(NULL, " ");
					}
					// �� ���� ���� �߰�
					printf("\n");
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("�빮�ڷ� �����ϴ� �ܾ� ���� : %d", coloredWord);
				printf("\n\n");
				break;
			}
			else
			{
				c_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'd': //���� ������ �Ųٷ� ���
		{
			if (d_OnOff == 0)
			{
				d_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					int len = strlen(strBuffer);
					for (int i = len - 1; i >= 0; --i)
					{   // for���� �ʱⰪ�� len���� �־� �ڿ��� ���� ���ڿ��� ����Ѵ�.
						printf("%c", strBuffer[i]);
					}
					// �� ���� ���� �߰�
					printf("\n");
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				d_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'e': //3���� �� Ư������ ����
		{
			if (e_OnOff == 0)
			{
				e_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
					e_Count++;
					if (e_Count % 3 == 0) printf("@@");
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				e_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'f': //�ܾ� ������ �Ųٷ� ���
		{
			if (f_OnOff == 0)
			{
				f_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// �ܾ� �ϳ��� ����
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						int len = strlen(ptr);
						for (int i = len - 1; i >= 0; --i)
						{   // for���� �ʱⰪ�� len���� �־� �ڿ��� ���� ���ڿ��� ����Ѵ�.
							printf("%c", ptr[i]);
						}
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
						ptr = strtok(NULL, " ");
					}
					// �� ���� ���� �߰�
					printf("\n");
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				f_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'g': //Ư�� ���ڸ� �ٸ� ���ڷ�
		{
			if (g_OnOff == 0)
			{
				char before;
				char after;
				printf("A_to_B mod #input 2 letter : ");
				scanf(" %c %c", &before, &after);

				g_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					if (c != before)
					{
						putchar(c);
					}
					else
					{
						printf("%c", after);
					}
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				g_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n");
				break;
			}
		}
		case 'h': //�� ���� �ܾ� ���� ���
		{
			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
				return 0;
			}
			printf("\n");
			while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
			{
				int wordCount = 0;

				// ���� ���ڸ� ����
				strBuffer[strcspn(strBuffer, "\n")] = 0;

				// �ܾ� �ϳ��� ����
				char* ptr = strtok(strBuffer, " ");
				while (ptr != NULL)
				{
					printf("%s", ptr);
					if (ptr[strlen(ptr) - 1] != '\n')
						printf(" ");
					ptr = strtok(NULL, " ");
					wordCount++;
				}
				// �� ���� ���� �߰�
				printf(" : %d�ܾ�", wordCount);
				printf("\n");
			}
			//���ϴݱ�
			fclose(inputFile);
			printf("\n\n");
			break;
		}
		case 'r': //�ܾ� ������ ���� ����->����->�⺻ �ٹٲٱ�
		{
			lineCount = 0;
			if (r_123 == 0)
			{
				r_123 = 1;
				lineCount = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n�������� ����\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;
					//���ڿ� �����ϱ�		
					strcpy(stringTemp[lineCount], strBuffer);

					// �ܾ� �ϳ��� ����
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						//printf("%s", ptr);
						//if (ptr[strlen(ptr) - 1] != '\n')
							//printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					//�ܾ�� �����ϱ�
					wordCountTemp[lineCount] = wordCount;
					//�ε��� ����
					lineCount++;			
				}

				//�������� ����
				for (int i = 0; i < (lineCount - 1); i++)
				{
					for (int j = 0; j < (lineCount - 1) - i; j++)
					{
						if (wordCountTemp[j] > wordCountTemp[j + 1])
						{
							temp = wordCountTemp[j];
							wordCountTemp[j] = wordCountTemp[j + 1];
							wordCountTemp[j + 1] = temp;

							strcpy(strSwap, stringTemp[j]);
							strcpy(stringTemp[j], stringTemp[j + 1]);
							strcpy(stringTemp[j + 1], strSwap);
						}
					}
				}
				for (int i = 0; i < lineCount; i++)
				{
					printf("%s", stringTemp[i]);
					printf(" : %d�ܾ�\n", wordCountTemp[i]);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else if (r_123 == 1)
			{
				r_123 = 2;
				lineCount = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n�������� ����\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;
					//���ڿ� �����ϱ�		
					strcpy(stringTemp[lineCount], strBuffer);

					// �ܾ� �ϳ��� ����
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						//printf("%s", ptr);
						//if (ptr[strlen(ptr) - 1] != '\n')
							//printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					//�ܾ�� �����ϱ�
					wordCountTemp[lineCount] = wordCount;
					//�ε��� ����
					lineCount++;
				}

				//�������� ����
				for (int i = 0; i < (lineCount - 1); i++)
				{
					for (int j = 0; j < (lineCount - 1) - i; j++)
					{
						if (wordCountTemp[j] < wordCountTemp[j + 1])
						{
							temp = wordCountTemp[j];
							wordCountTemp[j] = wordCountTemp[j + 1];
							wordCountTemp[j + 1] = temp;

							strcpy(strSwap, stringTemp[j]);
							strcpy(stringTemp[j], stringTemp[j + 1]);
							strcpy(stringTemp[j + 1], strSwap);
						}
					}
				}
				for (int i = 0; i < lineCount; i++)
				{
					printf("%s", stringTemp[i]);
					printf(" : %d�ܾ�\n", wordCountTemp[i]);
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				r_123 = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
					return 0;
				}
				printf("\n���󺹱�\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// ���� ���ڸ� ����
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// �ܾ� �ϳ��� ����
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						printf("%s", ptr);
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					// �� ���� ���� �߰�
					printf(" : %d�ܾ�", wordCount);
					printf("\n");
				}
				//���ϴݱ�
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 's': //�ܾ� �˻��ϱ� (���� ����)
		{
			coloredWord = 0;
			char inputWord[MAX_STR];
			printf("search word input : ");
			scanf(" %s", inputWord);

			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "���� %s ���⿡ �����߽��ϴ�.\n", fname);
				return 0;
			}
			printf("\n");
			while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
			{
				// ���� ���ڸ� ����
				strBuffer[strcspn(strBuffer, "\n")] = 0;

				// �ܾ� �ϳ��� ����
				char* ptr = strtok(strBuffer, " ");
				while (ptr != NULL)
				{
					if (0 == _stricmp(ptr, inputWord))
					{
						// ���� ����:12, �⺻��:7
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
						printf("%s", ptr);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
						coloredWord++;
					}
					else
					{
						printf("%s", ptr);
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
					}
					ptr = strtok(NULL, " ");
				}
				// �� ���� ���� �߰�
				printf("\n");
			}
			//���ϴݱ�
			fclose(inputFile);
			printf("�˻��� [%s] ���� : %d", inputWord, coloredWord);
			printf("\n\n");
			break;
		}
		default:
			printf("�߸��� ��ɾ� �Դϴ�.\n\n");
			break;
		}
	}
	return 0;
}