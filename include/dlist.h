#ifndef DLIST_H
#define DLIST_H
#include "objects.h"

typedef struct DNode {
    int value;
    struct DNode* next, * prev;
} DNode;

void PrintDList(DNode *);
DNode *dlist_create_node(int);
void dlist_insert_head(DNode **, DNode *);
void dlist_insert_after(DNode *, DNode *);
DNode *dlist_find_node(DNode *, int);
void dlist_remove_node(DNode *, DNode *);
DNode *dlist_detach_node(DNode *, DNode *);
void dlist_clear(DNode **);
#endif
