#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtStart(struct Node** head, int data)
{
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
        *head = newNode;
    }
}

void deleteAtStart(struct Node** head)
{
    if (*head == NULL) {
        return;
    } else if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = (*head)->next;
        struct Node* toDelete = *head;
        *head = (*head)->next;
        free(toDelete);
    }
}

void showAllElements(struct Node* head)
{
    if (head == NULL) {
        return;
    }
    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("HEAD\n");
}

int main()
{
    struct Node* head = NULL;
    insertAtStart(&head, 10);
    insertAtStart(&head, 20);
    insertAtStart(&head, 30);
    printf("Circular Linked List: ");
    showAllElements(head);
    deleteAtStart(&head);
    printf("Circular Linked List after deletion: ");
    showAllElements(head);

    return 0;
}
