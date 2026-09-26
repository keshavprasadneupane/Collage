#include <stdio.h>
#include <stdlib.h>

struct stack {
    int* stPtr;
    int size;
    int top;
};

void CreateStack(struct stack* temp, int size) {
    temp->stPtr = (int*)calloc(size, sizeof(int));
    if (temp->stPtr == NULL) {
        printf("Not allocated. Exiting.\n");
        exit(1);
    }
    temp->size = size;
    temp->top = -1;
    printf("Stack is created with size %d.\n", size);
}

void DeleteStack(struct stack* S) {
    printf("Stack is deleted.\n");
    free(S->stPtr);
    S->stPtr = NULL;
}

int IsFull(struct stack* t) {
    return t->top >= t->size - 1;
}

int IsEmpty(struct stack* t) {
    return t->top == -1;
}

void Push(struct stack* S) {
    int value;
    system("cls");
    printf("Enter push value: ");
    scanf("%d", &value);
    if (!IsFull(S)) {
        S->stPtr[++S->top] = value;
        printf("Pushed the value = %d.\n", value);
    } else {
        printf("Stack is full. Cannot push.\n");
    }
}

void Peek(struct stack* S) {
    system("cls");
    if (!IsEmpty(S)) {
        printf("Top value = %d.\n", S->stPtr[S->top]);
    } else {
        printf("Stack is empty. No top value.\n");
    }
}

int Pop(struct stack* S) {
    system("cls");
    if (!IsEmpty(S)) {
        int result = S->stPtr[S->top];
        S->stPtr[S->top--] = 0;
        printf("Popped the value = %d.\n", result);
        return result;
    } else {
        printf("Stack is empty. Cannot pop.\n");
        return 0;
    }
}

int main() {
    struct stack S;
    int size, choice;
    printf("Enter the size of stack: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    CreateStack(&S, size);

    while (1) {
        printf("\n Which operation do you want to perform?\n");
        printf("0. Exit\n1. Push\n2. Pop\n3. Peek\n4. Check Full\n5. Check Empty\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                DeleteStack(&S);
                return 0;
            case 1:
                Push(&S);
                break;
            case 2:
                Pop(&S);
                break;
            case 3:
                Peek(&S);
                break;
            case 4:
                 system("cls");
                printf(IsFull(&S) ? "Stack is full.\n" : "Stack is not full.\n");
                break;
            case 5:
                 system("cls");
                printf(IsEmpty(&S) ? "Stack is empty.\n" : "Stack is not empty.\n");
                break;
            default:
                printf("Enter a valid operation.\n");
                break;
        }
    }
    return 0;
}
