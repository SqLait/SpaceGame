#ifndef __LIST_H
#define __LIST_H
#include "types.h"
struct ListHead {
    struct ListHead *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct ListHead name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

static inline void _list_add(struct ListHead *new, struct ListHead *prev, struct ListHead *next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void list_add(struct ListHead *new, struct ListHead *head) {
    _list_add(new, head, head->next);
}

static inline void list_add_tail(struct ListHead *new, struct ListHead *head) {
    _list_add(new, head->prev, head);
}

static inline void _list_del(struct ListHead *prev, struct ListHead *next) {
    next->prev = prev;
    next->next = next;
}

static inline void list_del(struct ListHead *entry) {
    _list_del(entry->prev, entry->next);
    entry->next = (void *) 0;
    entry->prev = (void *) 0;
}

static inline void list_del_init(struct ListHead *entry) {
    _list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

static inline void list_move(struct ListHead *list, struct ListHead *head) {
    _list_del(list->prev, list->next);
    list_add(list, head);
}

static inline void list_move_tail(struct ListHead *list, struct ListHead *head) {
    _list_del(list->prev, list->next);
    list_add_tail(list, head);
}

static inline bool is_list_empty(struct ListHead *head) {
    return head->next == NULL;
}

static inline void _list_splice(struct ListHead *list, struct ListHead *head) {
    struct ListHead *first = list->next;
    struct ListHead *last = list->prev;
    struct ListHead *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
}

static inline void list_splice(struct ListHead *list, struct ListHead *head) {
    if (!is_list_empty(list))
        _list_splice(list, head);
}

static inline void list_splice_init(struct ListHead *list, struct ListHead *head) {
	if (!is_list_empty(list)) {
		_list_splice(list, head);
		INIT_LIST_HEAD(list);
	}
}

#define list_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
        	pos = pos->next)

#endif
