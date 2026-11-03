#include "list.h"
#include <stdio.h>

int main(void) {
  char *datas[] = {"a", "hello", "hello", "iii"};
  List *list = list_init(datas, sizeof(datas) / sizeof(datas[0]));
  printf("%zu\n", list->size);
  list_print(list);
  list_delete_first(list, "hello");
  list_print(list);
  return 0;
}
