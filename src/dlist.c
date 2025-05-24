#include "dlist.h"
#include <stdlib.h>

void PrintDList(DNode *head) {
    // DNode *temp = head;
    // while (temp != NULL) {
    //     printf("%d - ", temp->value);
    //     temp = temp->next;
    // }
    // printf("\n");
}

DNode *dlist_create_node(int value) {
    DNode *result = malloc(sizeof(DNode));
    result->value = value;
    result->prev = NULL;
    result->next = NULL;

    return result;
}

void dlist_insert_head(DNode **head, DNode *node) {
    node->next = *head;
    if (*head != NULL)
        (*head)->prev = node;
    *head = node;
    node->prev = NULL;
}

void dlist_insert_after(DNode *tail, DNode *newnode) {
    newnode->next = tail->next;
    if (newnode->next != NULL)
        newnode->next->prev = tail;
    newnode->prev = tail;
    tail->next = newnode;
}

DNode *dlist_find_node(DNode *head, int value) {
    DNode *tmp = head;
    while (tmp != NULL) {
        if (tmp->value == value)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void dlist_remove_node(DNode *head, DNode *entry) {
    if (!entry || !head || !(*(&head))) return;

    // Update head if entry is the head
    if (*(&head) == entry)
        *(&head) = entry->next;

    // Fix the previous node's next pointer
    if (entry->prev)
        entry->prev->next = entry->next;

    // Fix the next node's prev pointer
    if (entry->next)
        entry->next->prev = entry->prev;

    free(entry);
}

DNode *dlist_detach_node(DNode *head, DNode *entry) {
    // Indirect pointers points to the address of the node we will update
    DNode **indirect = &head;

    // Walk the list looking for the thing that points to the entry we want to remove
    while((*indirect) != entry)
        indirect = &(*indirect)->next;

    // .. and just remove it
    DNode *rm = *indirect;
    *indirect = entry->next;

    // Return a pointer to the item so the user can decide what to do with it
    return rm;
}

void dlist_clear(DNode **head) {
    DNode *tmp = *head;
    while (tmp != NULL) {
        DNode *rm = tmp;
        tmp = tmp->next;
        free(rm);
    }
    *head = NULL;
}
