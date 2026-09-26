#include<stdio.h>

struct node{
    struct node* prev;
    int data;
    struct node* next;
};
typedef struct node Node;


void Initialize(Node * n , int value){
    n->prev= NULL;
    n->data = value;
    n->next = NULL;
}


Node* CreateNode(int Data){
    Node* nextNode = (Node*)malloc(sizeof(Node));
    nextNode->data = Data;
    nextNode->next = NULL;
    nextNode->prev = NULL;
    return nextNode;
}



void AddNodeAtEnd(Node* n , int Data){
    Node* new = CreateNode(Data);
    if(n == NULL){
        n = new;
        return;
    }
    Node * current = n;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = new;
    new->prev = current;
}


void DeleteAtEnd(Node*n){
    if(n==NULL){
        printf("node is empty \n");
        return;
    }
    Node* temp = n;
    if(temp->next == NULL){
        free(temp);
        n = NULL;
        return;
    }

    while(temp->next->next != NULL){
        temp = temp->next;
    }
    
    free(temp->next);
    temp->next = NULL;
    return;
}

void Treverse(Node*n){
    if(n == NULL){
        printf("Node = empty \n");
        return;
    }
    Node* temp = n;
    while(temp != NULL){
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("Null\n");
}

int main(){
    Node head ;
    Initialize(&head, 7);
    AddNodeAtEnd(&head , 8);
    AddNodeAtEnd(&head , 10);
    DeleteAtEnd(&head);
    Treverse(&head);
}
