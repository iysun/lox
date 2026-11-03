#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} List;

static inline int list_insert_first(List *list, char *data) {
  Node *node = (Node *)malloc(sizeof(Node));
  *node = (Node){
      .data = data,
      .prev = NULL,
      .next = NULL,
  };
  if (!node) {
    return 1;
  }
  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    Node *firstNode = list->head;
    firstNode->prev = node;
    node->next = firstNode;
    list->head = node;
  }
  list->size++;

  return 0;
}

static inline int list_insert_last(List *list, char *data) {
  Node *node = (Node *)malloc(sizeof(Node));
  *node = (Node){
      .data = data,
      .prev = NULL,
      .next = NULL,
  };
  if (!node) {
    return 1;
  }
  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    Node *lastNode = list->tail;
    lastNode->next = node;
    node->prev = lastNode;
    list->tail = node;
  }
  list->size++;

  return 0;
}

static inline List *list_init(char **datas, size_t n) {
  List *list = (List *)malloc(sizeof(List));

  if (!list) {
    fprintf(stderr, "malloc list err\n");
    return NULL;
  }

  *list = (List){.head = NULL, .tail = NULL, .size = 0};
  if (n == 0) {
    return list;
  }

  for (int i = 0; i < n; i++) {
    list_insert_last(list, datas[i]);
  }

  return list;
}

static Node *list_find_first(List *list, char *data) {
  Node *p = list->head;
  if (p == NULL) {
    return NULL;
  }
  for (; p != NULL;) {
    if (strcmp(p->data, data) == 0) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}
static Node *list_find_last(List *list, char *data) {
  Node *p = list->tail;
  if (p == NULL) {
    return NULL;
  }
  for (; p != NULL;) {
    if (strcmp(p->data, data) == 0) {
      return p;
    }
    p = p->prev;
  }
  return NULL;
}

static inline int list_delete_first(List *list, char *data) {
  Node *p = list_find_first(list, data);
  if (p == NULL) {
    return 1;
  }
  Node *prev = p->prev;
  Node *next = p->next;
  // 1. 只有一个节点 2. 在头 3. 在尾 4. 在中
  if (prev != NULL) {
    prev->next = next;
  } else {
    list->head = p->next;
  }
  if (next != NULL) {
    next->prev = prev;
  } else {
    list->tail = p->prev;
  }
  list->size--;
  free(p);
  return 0;
}

static inline int list_delete_last(List *list, char *data) {
  Node *p = list_find_last(list, data);
  if (p == NULL) {
    return 1;
  }
  Node *prev = p->prev;
  Node *next = p->next;
  // 1. 只有一个节点 2. 在头 3. 在尾 4. 在中
  if (prev != NULL) {
    prev->next = next;
  } else {
    list->head = p->next;
  }
  if (next != NULL) {
    next->prev = prev;
  } else {
    list->tail = p->prev;
  }
  list->size--;
  free(p);
  return 0;
}

static void list_print(List *list) {
  Node *p = list->head;
  printf("list: ");
  for (; p != NULL;) {
    printf("%s", p->data);
    p = p->next;
    if (p != NULL) {
      printf("<=>");
    }
  }
  printf("\n");
}

static void list_destroy(List *list) {
  if (!list)
    return;
  Node *cur = list->head;
  while (cur) {
    Node *next = cur->next;
    free(cur->data);
    free(cur);
    cur = next;
  }
  free(list);
}
