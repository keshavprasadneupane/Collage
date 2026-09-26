// WAP TO IMPLEMENT DYNAMIC LINKLIST QUEUE
#include<stdio.h>
#include<stdlib.h>
#ifdef _WIN32
    #define Clear "cls"
#else
    #define Clear "clear"
#endif

struct list {
    int value;
    struct list* next;
};
typedef struct list LinkList;

struct Queue {
    LinkList* front;
    LinkList* rear;
};
typedef struct Queue Queue;

LinkList* CreateNode(int value) {
    LinkList* newNode = (LinkList*)malloc(sizeof(LinkList));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void InitializeQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void Enqueue(Queue* q, int value) {
    LinkList* newNode = CreateNode(value);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;  
    } else {
        q->rear->next = newNode;  
        q->rear = newNode;  
    }
    printf("\nEnqueued: %d\n", value);
}

void Dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("\nQueue is empty! Cannot dequeue.\n");
        return;
    }
    LinkList* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) { 
        q->rear = NULL;
    }
    printf("\nDequeued: %d\n", temp->value);
    free(temp); 
}

void Peek(Queue* q) {
    if (q->front == NULL) {
        printf("\nQueue is empty! Nothing to peek.\n");
        return;
    }
    printf("\nFront value: %d\n", q->front->value);
}

void DisplayQueue(Queue* q) {
    if (q->front == NULL) {
        printf("\nQueue is empty\n");
        return;
    }
    LinkList* temp = q->front;
    printf("\nQueue contents: ");
    while (temp != NULL) {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL\n");
}

int getValidInput() {
    int value;
    while (1) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter an integer: ");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return value;
}

int main() {
    Queue q;
    InitializeQueue(&q); 
    int choice, value;

    do {
        printf("\nQueue Menu:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek Front\n");
        printf("4. Display Queue\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = getValidInput();
        
        switch (choice) {
            case 1:
                system(Clear);
                printf("Enter value to enqueue: ");
                value = getValidInput();
                Enqueue(&q, value);
                break;
            case 2:
                system(Clear);
                Dequeue(&q);
                break;
            case 3:
                system(Clear);
                Peek(&q);
                break;
            case 4:
                system(Clear);
                DisplayQueue(&q);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
