#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_QUEUE_SIZE 21

typedef struct
{
    int x;
    int y;
    int z;
}element;
typedef struct
{ // 큐 타입
    element* data;
    int front, rear;
} DequeType;

// 점과 원점의 거리
double cal_distance(element val)
{
    return sqrt(val.x * val.x + val.y * val.y + val.z * val.z);  // 유클리드 거리 계산
}

// 오류 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
    q->front = q->rear = 0;
    q->data = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE); // Allocate memory
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
    return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void add_rear(DequeType* q, element item)
{
    if (is_full(q))
        error((char*)"큐가 포화상태입니다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
    if (is_empty(q))
        error((char*)"큐가 공백상태입니다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
element get_front(DequeType* q)
{
    if (is_empty(q))
        error((char*)"큐가 공백상태입니다");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// 삽입 함수
void add_front(DequeType* q, element val)
{
    if (is_full(q))
        error((char*)"큐가 포화상태입니다");
    q->data[q->front] = val;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
// 삭제 함수
element delete_rear(DequeType* q)
{
    int prev = q->rear;
    if (is_empty(q))
        error((char*)"큐가 공백상태입니다");
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}
element get_rear(DequeType* q)
{
    if (is_empty(q))
        error((char*)"큐가 공백상태입니다");
    return q->data[q->rear];
}

// 원형 데큐 리스트 출력 함수
void deque_print(DequeType* q)
{
    //printf("<DEQUE_LIST(front=%d, rear=%d)> \n", q->front, q->rear);
    printf("<DQ List>\n");
    /*if (!is_empty(q))
    {
        int i = q->front;
        do
        {
           i = (i + 1) % (MAX_QUEUE_SIZE);
           printf("%d : (%d %d %d)\n", i, q->data[i].x, q->data[i].y, q->data[i].z);
           if (i == q->rear)
               break;
        }
        while (i != q->front);
    }*/
    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE - 1;  // 큐의 현재 크기 - 1
        int count = size;  // 출력할 때 사용할 카운터 (큐 크기에서 감소)

        do
        {
            printf("%d : (%d %d %d), distance : %.2f\n", count, q->data[i].x, q->data[i].y, q->data[i].z, cal_distance(q->data[i]));
            count--;  // 출력할 때마다 카운터 감소
            i = (i - 1 + MAX_QUEUE_SIZE) % (MAX_QUEUE_SIZE);
            if (i == q->front)
                break;
        }
        while (i != q->rear);
    }
    else
    {
        printf("데큐가 비었음\n");
    }
    printf("\n");
}
void deleted_deque_print(DequeType* q)
{
    printf("<DQ List>\n");

    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;  // 큐의 현재 크기 계산
        int count = size;  // 출력할 때 사용할 카운터 (큐 크기에서 감소)

        do
        {
            printf("%d : (%d %d %d), distance : %.2f\n", count, q->data[i].x, q->data[i].y, q->data[i].z, cal_distance(q->data[i]));
            count--;  // 출력할 때마다 카운터 감소
            i = (i - 1 + MAX_QUEUE_SIZE) % (MAX_QUEUE_SIZE);
            if (i == q->front)
            {
                printf("%d : \n", count);
                break;
            }
        }
        while (i != q->rear);
    }
    else
    {
        printf("데큐가 비었음\n");
    }
    printf("\n");
}
// 점의 개수 출력
void deque_size_print(DequeType* q)
{
    int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;  // 큐의 현재 크기 계산
    printf("<point Count : %d>\n\n", size);
}
// 오름 차순 출력
void sortUp_temp(DequeType* q, int mod)
{
    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;  // 큐의 현재 크기 계산 (1 더해줘야 크기 정확히 계산됨)
        element tempData[MAX_QUEUE_SIZE] = {};
        double tempDistance[MAX_QUEUE_SIZE];

        element tempElement = {}; // swap용 변수
        double tempDouble = 0;   // swap용 변수
        int j = 0;
        do
        {
            tempData[j] = q->data[i];  // temp에 data 저장 -> 이후 temp에서 정렬
            tempDistance[j] = cal_distance(q->data[i]);
            i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            j++;
        }
        while (i != (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);

        // 오름차순 정렬 (버블 정렬)
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)  // 변경된 범위
            {
                if (tempDistance[j] > tempDistance[j + 1])
                {
                    // 거리 swap
                    tempDouble = tempDistance[j];
                    tempDistance[j] = tempDistance[j + 1];
                    tempDistance[j + 1] = tempDouble;

                    // element swap
                    tempElement = tempData[j];
                    tempData[j] = tempData[j + 1];
                    tempData[j + 1] = tempElement;
                }
            }
        }   
        switch (mod)
        {
        case 0: // 정렬된 큐 출력
            printf("<DQ List_sortUp>\n");
            for (int i = size - 2; i >= 0; i--)
            {
                printf("%d : (%d %d %d), distance : %.2f\n", i, tempData[i].x, tempData[i].y, tempData[i].z, tempDistance[i]);
            }
            break;
        case 1: // 최대 거리 출력
            printf("(%d %d %d), distance : %.2f\n", tempData[size - 2].x, tempData[size - 2].y, tempData[size - 2].z, tempDistance[size - 2]);
            break;
        default:
            printf("moderr\n");
            break;
        }
    }
    else
    {
        printf("데큐가 비었음\n");
    }
    printf("\n");
}
// 내림 차순 출력
void sortDown_temp(DequeType* q, int mod)
{
    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;  // 큐의 현재 크기 계산 (1 더해줘야 크기 정확히 계산됨)
        element tempData[MAX_QUEUE_SIZE] = {};
        double tempDistance[MAX_QUEUE_SIZE];

        element tempElement; // swap용 변수
        double tempDouble;   // swap용 변수
        int j = 0;
        do
        {
            tempData[j] = q->data[i];  // temp에 data 저장 -> 이후 temp에서 정렬
            tempDistance[j] = cal_distance(q->data[i]);
            i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            j++;
        }
        while (i != (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);

        // 내림차순 정렬 (버블 정렬)
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)  // 변경된 범위
            {
                if (tempDistance[j] < tempDistance[j + 1])
                {
                    // 거리 swap
                    tempDouble = tempDistance[j];
                    tempDistance[j] = tempDistance[j + 1];
                    tempDistance[j + 1] = tempDouble;

                    // element swap
                    tempElement = tempData[j];
                    tempData[j] = tempData[j + 1];
                    tempData[j + 1] = tempElement;
                }
            }
        }

        switch (mod) {
        case 0: // 정렬된 큐 출력
            printf("<DQ List_sortDown>\n");
            for (int i = size - 2; i >= 0; i--)
            {
                printf("%d : (%d %d %d), distance : %.2f\n", i, tempData[i].x, tempData[i].y, tempData[i].z, tempDistance[i]);
            }
            break;
        case 1: // 최소 거리 출력
            printf("(%d %d %d), distance : %.2f\n", tempData[size - 2].x, tempData[size - 2].y, tempData[size - 2].z, tempDistance[size - 2]);
            break;
        default:
            printf("moderr\n");
            break;
        }
    }
    else
    {
        printf("데큐가 비었음\n");
    }
    printf("\n");
}

int main()
{
    int x = 0, y = 0, z = 0;
    DequeType deque;
    init_deque(&deque);
    element coordinate = {};
    int a_OnOff = 0; //0: on, 1: off
    int s_OnOff = 0; //0: on, 1: off

    while (1)
    {
        char input;
        printf("input command : ");
        scanf(" %c", &input);  // 먼저 명령어만 입력 받음
        switch (input) {
        case 'q':
        {
            printf("프로그램을 종료합니다.\n");
            free(deque.data); // Free allocated memory
            return 0;
            break;
        }
        case '+': //위에서 입력
        {
            scanf(" %d %d %d", &x, &y, &z);  // 좌표 입력을 추가로 받음
            coordinate.x = x;
            coordinate.y = y;
            coordinate.z = z;
            add_rear(&deque, coordinate);
            deque_print(&deque);
            break;
        }
        case '-': //위에서 삭제
        {
            delete_rear(&deque);
            deque_print(&deque);
            break;
        }
        case 'e': //아래에서 입력
        {
            scanf(" %d %d %d", &x, &y, &z);  // 좌표 입력을 추가로 받음
            coordinate.x = x;
            coordinate.y = y;
            coordinate.z = z;
            add_front(&deque, coordinate);
            deque_print(&deque);
            break;
        }
        case 'd': //아래에서 삭제
        {
            delete_front(&deque);
            deleted_deque_print(&deque);
            break;
        }
        case 'l': //점의 개수
        {
            deque_size_print(&deque);
            break;
        }
        case 'c': //리스트 삭제
        {
            free(deque.data); // Free allocated memory
            init_deque(&deque);
            if (is_empty(&deque))
            {
                printf("cleared\n\n");
            }
            break;
        }
        case 'm':
        {
            sortUp_temp(&deque, 1);
            break;
        }
        case 'n':
        {
            sortDown_temp(&deque, 1);
            break;
        }
        case 'a': //원점에서 가장 먼 거리의 좌표값 출력 -> 따로 배열에 저장시키자.
        {
            if (a_OnOff == 0)
            {
                a_OnOff = 1;
                sortUp_temp(&deque, 0);
            }
            else
            {
                a_OnOff = 0;
                deque_print(&deque);
            }
            break;
        }
        case 's': //원점에서 가장 먼 거리의 좌표값 출력 -> 따로 배열에 저장시키자.
        {
            if (s_OnOff == 0)
            {
                s_OnOff = 1;
                sortDown_temp(&deque, 0);
            }
            else
            {
                s_OnOff = 0;
                deque_print(&deque);
            }
            break;
        }
        default:
            printf("잘못된 명령어 입니다.\n\n");
            break;
        }
    }
    free(deque.data); // Free allocated memory
    return 0;
}