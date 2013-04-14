#include "item.h"

int main(int argc, char *argv[])
{
  itemDequeue ideq = new_itemDequeue();
  item i = new_item();
  i->value = 4;
  itemDequeue_add(ideq, i);
  itemDequeue_print(ideq);
  return 1;
}
