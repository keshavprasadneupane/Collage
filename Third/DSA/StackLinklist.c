#include<stdio.h>
#include<stdlib.h>


struct node{
    int data;
    struct node* next;
};
typedef struct node Node;

struct stack{
    Node * top;
};
typedef struct stack Stack;

void Initialize(Stack* s) {
    s->top = NULL;
}


Node* CreateNode(int Data){
    Node* nextNode = (Node*)malloc(sizeof(Node));
    nextNode->data = Data;
    nextNode->next = NULL;
    return nextNode;
}

void Push(Stack* s , int Data){
    Node* new = CreateNode(Data);
    if(s->top == NULL){
        s->top = new;
        return;
    }
    new->next = s->top;
    s->top = new;
}

void Pop(Stack * s){
    if(s->top == NULL){
        printf("Stack is empty \n");
        return;
    }
    Node* temp = s->top->next;
    free(s->top);
    s->top  = temp;
}

void Treverse(Stack* s){
    if(s->top == NULL){
        printf("Node = empty \n");
        return;
    }
    Node* temp = s->top;
    while(temp != NULL){
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("Null \n");
}

int main() {
    Stack s;
    Initialize(&s);
    int choice, value;
    while (1) {
        printf("\nStack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Traverse\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                Push(&s, value);
                break;
            case 2:
                Pop(&s);
                break;
            case 3:
                Treverse(&s);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}




