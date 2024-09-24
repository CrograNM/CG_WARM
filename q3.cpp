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
{ // ť Ÿ��
    element* data;
    int front, rear;
} DequeType;

// ���� ������ �Ÿ�
double cal_distance(element val)
{
    return sqrt(val.x * val.x + val.y * val.y + val.z * val.z);  // ��Ŭ���� �Ÿ� ���
}

// ���� �Լ�
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}
// �ʱ�ȭ
void init_deque(DequeType* q)
{
    q->front = q->rear = 0;
    q->data = (element*)malloc(sizeof(element) * MAX_QUEUE_SIZE); // Allocate memory
}
// ���� ���� ���� �Լ�
int is_empty(DequeType* q)
{
    return (q->front == q->rear);
}
// ��ȭ ���� ���� �Լ�
int is_full(DequeType* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void add_rear(DequeType* q, element item)
{
    if (is_full(q))
        error((char*)"ť�� ��ȭ�����Դϴ�");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}
// ���� �Լ�
element delete_front(DequeType* q)
{
    if (is_empty(q))
        error((char*)"ť�� ��������Դϴ�");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}
element get_front(DequeType* q)
{
    if (is_empty(q))
        error((char*)"ť�� ��������Դϴ�");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ���� �Լ�
void add_front(DequeType* q, element val)
{
    if (is_full(q))
        error((char*)"ť�� ��ȭ�����Դϴ�");
    q->data[q->front] = val;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
// ���� �Լ�
element delete_rear(DequeType* q)
{
    int prev = q->rear;
    if (is_empty(q))
        error((char*)"ť�� ��������Դϴ�");
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}
element get_rear(DequeType* q)
{
    if (is_empty(q))
        error((char*)"ť�� ��������Դϴ�");
    return q->data[q->rear];
}

// ���� ��ť ����Ʈ ��� �Լ�
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
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE - 1;  // ť�� ���� ũ�� - 1
        int count = size;  // ����� �� ����� ī���� (ť ũ�⿡�� ����)

        do
        {
            printf("%d : (%d %d %d), distance : %.2f\n", count, q->data[i].x, q->data[i].y, q->data[i].z, cal_distance(q->data[i]));
            count--;  // ����� ������ ī���� ����
            i = (i - 1 + MAX_QUEUE_SIZE) % (MAX_QUEUE_SIZE);
            if (i == q->front)
                break;
        }
        while (i != q->rear);
    }
    else
    {
        printf("��ť�� �����\n");
    }
    printf("\n");
}
void deleted_deque_print(DequeType* q)
{
    printf("<DQ List>\n");

    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;  // ť�� ���� ũ�� ���
        int count = size;  // ����� �� ����� ī���� (ť ũ�⿡�� ����)

        do
        {
            printf("%d : (%d %d %d), distance : %.2f\n", count, q->data[i].x, q->data[i].y, q->data[i].z, cal_distance(q->data[i]));
            count--;  // ����� ������ ī���� ����
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
        printf("��ť�� �����\n");
    }
    printf("\n");
}
// ���� ���� ���
void deque_size_print(DequeType* q)
{
    int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;  // ť�� ���� ũ�� ���
    printf("<point Count : %d>\n\n", size);
}
// ���� ���� ���
void sortUp_temp(DequeType* q, int mod)
{
    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;  // ť�� ���� ũ�� ��� (1 ������� ũ�� ��Ȯ�� ����)
        element tempData[MAX_QUEUE_SIZE] = {};
        double tempDistance[MAX_QUEUE_SIZE];

        element tempElement = {}; // swap�� ����
        double tempDouble = 0;   // swap�� ����
        int j = 0;
        do
        {
            tempData[j] = q->data[i];  // temp�� data ���� -> ���� temp���� ����
            tempDistance[j] = cal_distance(q->data[i]);
            i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            j++;
        }
        while (i != (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);

        // �������� ���� (���� ����)
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)  // ����� ����
            {
                if (tempDistance[j] > tempDistance[j + 1])
                {
                    // �Ÿ� swap
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
        case 0: // ���ĵ� ť ���
            printf("<DQ List_sortUp>\n");
            for (int i = size - 2; i >= 0; i--)
            {
                printf("%d : (%d %d %d), distance : %.2f\n", i, tempData[i].x, tempData[i].y, tempData[i].z, tempDistance[i]);
            }
            break;
        case 1: // �ִ� �Ÿ� ���
            printf("(%d %d %d), distance : %.2f\n", tempData[size - 2].x, tempData[size - 2].y, tempData[size - 2].z, tempDistance[size - 2]);
            break;
        default:
            printf("moderr\n");
            break;
        }
    }
    else
    {
        printf("��ť�� �����\n");
    }
    printf("\n");
}
// ���� ���� ���
void sortDown_temp(DequeType* q, int mod)
{
    if (!is_empty(q))
    {
        int i = q->rear;
        int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;  // ť�� ���� ũ�� ��� (1 ������� ũ�� ��Ȯ�� ����)
        element tempData[MAX_QUEUE_SIZE] = {};
        double tempDistance[MAX_QUEUE_SIZE];

        element tempElement; // swap�� ����
        double tempDouble;   // swap�� ����
        int j = 0;
        do
        {
            tempData[j] = q->data[i];  // temp�� data ���� -> ���� temp���� ����
            tempDistance[j] = cal_distance(q->data[i]);
            i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
            j++;
        }
        while (i != (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE);

        // �������� ���� (���� ����)
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)  // ����� ����
            {
                if (tempDistance[j] < tempDistance[j + 1])
                {
                    // �Ÿ� swap
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
        case 0: // ���ĵ� ť ���
            printf("<DQ List_sortDown>\n");
            for (int i = size - 2; i >= 0; i--)
            {
                printf("%d : (%d %d %d), distance : %.2f\n", i, tempData[i].x, tempData[i].y, tempData[i].z, tempDistance[i]);
            }
            break;
        case 1: // �ּ� �Ÿ� ���
            printf("(%d %d %d), distance : %.2f\n", tempData[size - 2].x, tempData[size - 2].y, tempData[size - 2].z, tempDistance[size - 2]);
            break;
        default:
            printf("moderr\n");
            break;
        }
    }
    else
    {
        printf("��ť�� �����\n");
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
        scanf(" %c", &input);  // ���� ��ɾ �Է� ����
        switch (input) {
        case 'q':
        {
            printf("���α׷��� �����մϴ�.\n");
            free(deque.data); // Free allocated memory
            return 0;
            break;
        }
        case '+': //������ �Է�
        {
            scanf(" %d %d %d", &x, &y, &z);  // ��ǥ �Է��� �߰��� ����
            coordinate.x = x;
            coordinate.y = y;
            coordinate.z = z;
            add_rear(&deque, coordinate);
            deque_print(&deque);
            break;
        }
        case '-': //������ ����
        {
            delete_rear(&deque);
            deque_print(&deque);
            break;
        }
        case 'e': //�Ʒ����� �Է�
        {
            scanf(" %d %d %d", &x, &y, &z);  // ��ǥ �Է��� �߰��� ����
            coordinate.x = x;
            coordinate.y = y;
            coordinate.z = z;
            add_front(&deque, coordinate);
            deque_print(&deque);
            break;
        }
        case 'd': //�Ʒ����� ����
        {
            delete_front(&deque);
            deleted_deque_print(&deque);
            break;
        }
        case 'l': //���� ����
        {
            deque_size_print(&deque);
            break;
        }
        case 'c': //����Ʈ ����
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
        case 'a': //�������� ���� �� �Ÿ��� ��ǥ�� ��� -> ���� �迭�� �����Ű��.
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
        case 's': //�������� ���� �� �Ÿ��� ��ǥ�� ��� -> ���� �迭�� �����Ű��.
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
            printf("�߸��� ��ɾ� �Դϴ�.\n\n");
            break;
        }
    }
    free(deque.data); // Free allocated memory
    return 0;
}