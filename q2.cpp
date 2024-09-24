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

	//파일 이름을 입력하시오 : 
	printf("input filename : ");
	scanf("%s", fname);

	//파일 이름 확인, 열기 -> data.txt
	if ((inputFile = fopen(fname, "r")) == NULL)
	{
		fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
		return 0;
	}

	//색 설정 코드
	//unsigned short text = 12; //밝은 빨강, 15 -> 하양색
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);

	int c;
	printf("\n");
	while ((c = fgetc(inputFile)) != EOF)
	{
		putchar(c);
	}
	//파일닫기
	fclose(inputFile);
	printf("\n");

	char input;
	char strBuffer[MAX_STR];
	int coloredWord = 0;
	int c_OnOff = 0; //0: off상태, 1: on상태
	int d_OnOff = 0; //0: off상태, 1: on상태
	int e_OnOff = 0; //0: off상태, 1: on상태
	int e_Count = 0; //3 단위로 printf("@@");
	int f_OnOff = 0; //0: off상태, 1: on상태
	int g_OnOff = 0; //0: off상태, 1: on상태
	int r_123 = 0; //0: 오름차순, 1: 내림차순, 2: 원래대로

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
			printf("프로그램을 종료합니다.\n");
			return 0;
			break;
		}
		case 't': //test
		{
			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
				return 0;
			}
			printf("\n");
			while ((c = fgetc(inputFile)) != EOF)
			{
				putchar(c);
			}
			//파일닫기
			fclose(inputFile);
			printf("\n");
			break;
		}

		case 'c': //대문자 단어 색깔출력
		{
			coloredWord = 0;
			if (c_OnOff == 0)
			{
				c_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// 단어 하나씩 접근
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						if (ptr[0] >= 65 && ptr[0] <= 90)
						{
							// 밝은 빨강:12, 기본색:7
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
					// 줄 끝에 개행 추가
					printf("\n");
				}
				//파일닫기
				fclose(inputFile);
				printf("대문자로 시작하는 단어 갯수 : %d", coloredWord);
				printf("\n\n");
				break;
			}
			else
			{
				c_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'd': //문장 단위로 거꾸로 출력
		{
			if (d_OnOff == 0)
			{
				d_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					int len = strlen(strBuffer);
					for (int i = len - 1; i >= 0; --i)
					{   // for문의 초기값을 len으로 주어 뒤에서 부터 문자열을 출력한다.
						printf("%c", strBuffer[i]);
					}
					// 줄 끝에 개행 추가
					printf("\n");
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				d_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'e': //3문자 후 특수문자 삽입
		{
			if (e_OnOff == 0)
			{
				e_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
					e_Count++;
					if (e_Count % 3 == 0) printf("@@");
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				e_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'f': //단어 단위로 거꾸로 출력
		{
			if (f_OnOff == 0)
			{
				f_OnOff = 1;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// 단어 하나씩 접근
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						int len = strlen(ptr);
						for (int i = len - 1; i >= 0; --i)
						{   // for문의 초기값을 len으로 주어 뒤에서 부터 문자열을 출력한다.
							printf("%c", ptr[i]);
						}
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
						ptr = strtok(NULL, " ");
					}
					// 줄 끝에 개행 추가
					printf("\n");
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				f_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 'g': //특정 문자를 다른 문자로
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
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
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
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				g_OnOff = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n");
				while ((c = fgetc(inputFile)) != EOF)
				{
					putchar(c);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n");
				break;
			}
		}
		case 'h': //각 줄의 단어 갯수 출력
		{
			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
				return 0;
			}
			printf("\n");
			while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
			{
				int wordCount = 0;

				// 개행 문자를 제거
				strBuffer[strcspn(strBuffer, "\n")] = 0;

				// 단어 하나씩 접근
				char* ptr = strtok(strBuffer, " ");
				while (ptr != NULL)
				{
					printf("%s", ptr);
					if (ptr[strlen(ptr) - 1] != '\n')
						printf(" ");
					ptr = strtok(NULL, " ");
					wordCount++;
				}
				// 줄 끝에 개행 추가
				printf(" : %d단어", wordCount);
				printf("\n");
			}
			//파일닫기
			fclose(inputFile);
			printf("\n\n");
			break;
		}
		case 'r': //단어 갯수에 따라 오름->내림->기본 줄바꾸기
		{
			lineCount = 0;
			if (r_123 == 0)
			{
				r_123 = 1;
				lineCount = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n오름차순 정렬\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;
					//문자열 복사하기		
					strcpy(stringTemp[lineCount], strBuffer);

					// 단어 하나씩 접근
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						//printf("%s", ptr);
						//if (ptr[strlen(ptr) - 1] != '\n')
							//printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					//단어개수 저장하기
					wordCountTemp[lineCount] = wordCount;
					//인덱스 증가
					lineCount++;			
				}

				//오름차순 정렬
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
					printf(" : %d단어\n", wordCountTemp[i]);
				}
				//파일닫기
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
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n내림차순 정렬\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;
					//문자열 복사하기		
					strcpy(stringTemp[lineCount], strBuffer);

					// 단어 하나씩 접근
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						//printf("%s", ptr);
						//if (ptr[strlen(ptr) - 1] != '\n')
							//printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					//단어개수 저장하기
					wordCountTemp[lineCount] = wordCount;
					//인덱스 증가
					lineCount++;
				}

				//내림차순 정렬
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
					printf(" : %d단어\n", wordCountTemp[i]);
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
			else
			{
				r_123 = 0;
				if ((inputFile = fopen(fname, "r")) == NULL)
				{
					fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
					return 0;
				}
				printf("\n원상복구\n");
				while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
				{
					int wordCount = 0;

					// 개행 문자를 제거
					strBuffer[strcspn(strBuffer, "\n")] = 0;

					// 단어 하나씩 접근
					char* ptr = strtok(strBuffer, " ");
					while (ptr != NULL)
					{
						printf("%s", ptr);
						if (ptr[strlen(ptr) - 1] != '\n')
							printf(" ");
						ptr = strtok(NULL, " ");
						wordCount++;
					}
					// 줄 끝에 개행 추가
					printf(" : %d단어", wordCount);
					printf("\n");
				}
				//파일닫기
				fclose(inputFile);
				printf("\n\n");
				break;
			}
		}
		case 's': //단어 검색하기 (색깔 변경)
		{
			coloredWord = 0;
			char inputWord[MAX_STR];
			printf("search word input : ");
			scanf(" %s", inputWord);

			if ((inputFile = fopen(fname, "r")) == NULL)
			{
				fprintf(stderr, "파일 %s 열기에 실패했습니다.\n", fname);
				return 0;
			}
			printf("\n");
			while (fgets(strBuffer, sizeof(strBuffer), inputFile) != NULL)
			{
				// 개행 문자를 제거
				strBuffer[strcspn(strBuffer, "\n")] = 0;

				// 단어 하나씩 접근
				char* ptr = strtok(strBuffer, " ");
				while (ptr != NULL)
				{
					if (0 == _stricmp(ptr, inputWord))
					{
						// 밝은 빨강:12, 기본색:7
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
				// 줄 끝에 개행 추가
				printf("\n");
			}
			//파일닫기
			fclose(inputFile);
			printf("검색된 [%s] 갯수 : %d", inputWord, coloredWord);
			printf("\n\n");
			break;
		}
		default:
			printf("잘못된 명령어 입니다.\n\n");
			break;
		}
	}
	return 0;
}