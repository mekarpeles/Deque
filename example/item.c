#include "item.h"

item half(item i) 
{  
  i->value = i->value * .5;
  return i;
}

item print(item i) 
{  
  printf("%i, ", i->value);
  return i;
}

int main(int argc, char *argv[])
{
  itemDequeue ideq = new_itemDequeue();
  int i;
  for (i=0; i<10; i++) {
    item tmp = new_item();
    tmp->value = rand();
    itemDequeue_add(ideq, tmp);
  }
  printf("[");
  ideq = itemDequeue_map(ideq, &print);
  printf("...],\n");
  ideq = itemDequeue_map(ideq, &half);
  printf("[");
  ideq = itemDequeue_map(ideq, &print);
  printf("...]\n");
  return 0;
}
