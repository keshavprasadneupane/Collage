// WAP TO IMPLEMENT LINEAR STATIC QUEUE

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define Max 10
#define intergerNull -999999
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct LinQ {
    int item[Max];
    int front;
    int rear;
};
typedef struct LinQ Queue;

void MakeQueue(Queue* Q) {
    Q->front = Q->rear = -1;
    printf("\nQueue is made with size %d \n", Max);
}

bool IsEmpty(Queue* Q) {
    return (Q->rear == -1 || Q->rear == Q->front);
}

bool IsFull(Queue* Q) {
    return (Q->rear == Max - 1);
}

void Enqueue(Queue* Q, int val) {
    if (IsFull(Q)) {
        printf("Queue is full\n");
    } else {
        Q->item[++Q->rear] = val;
        printf("Added to queue: value = %d \n", val);
    }
    return;
}

int Dequeue(Queue* Q) {
    int temp;
    if (IsEmpty(Q)) {
        printf("Queue is empty. Nothing to Dequeue\n");
        return intergerNull;
    } else {
        temp = Q->item[++Q->front];
        if (Q->front == Q->rear) {
            Q->front = -1;
            Q->rear = -1;
        }
        return temp;
    }
}

void Peek(Queue* Q) {
    if (IsEmpty(Q)) {
        printf("Queue is empty. Nothing to peek\n");
    } else {
        printf("The front value = %d \n", Q->item[Q->front + 1]);
    }
    return;
}

void Traverse(Queue* Q) {
    if (IsEmpty(Q)) {
        printf("Queue is empty. Nothing to traverse\n");
    } else {
        for (int i = Q->front + 1; i <= Q->rear; ++i) {
            printf("%d, ", Q->item[i]);
        }
        printf(" End\n");
    }
}

int main() {
    Queue queue;
    MakeQueue(&queue);

    int choice, value;
    do {
        printf("\n----- Queue Menu -----\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Traverse\n");
        printf("5. Check if Queue is Empty\n");
        printf("6. Check if Queue is Full\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system(CLEAR);
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                Enqueue(&queue, value);
                break;

            case 2:
                system(CLEAR);
                value = Dequeue(&queue);
                if (value != intergerNull) {
                    printf("Dequeued value = %d\n", value);
                }
                break;

            case 3:
                system(CLEAR);
                Peek(&queue);
                break;

            case 4:
                system(CLEAR);
                Traverse(&queue);
                break;

            case 5:
                system(CLEAR);
                printf("Is Queue Empty? %s\n", IsEmpty(&queue) ? "Yes" : "No");
                break;

            case 6:
                system(CLEAR);
                printf("Is Queue Full? %s\n", IsFull(&queue) ? "Yes" : "No");
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
