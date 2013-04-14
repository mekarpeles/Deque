Deque
=====

## Header

DEQUE is a macro will automatically defines 2 new types: and COLLECTION type and a ELEMENT type. The names for these types is specified by the variable names of the first two parameters to the DEQUE macro call, respectively. For example:
    
    DEQUE(collectionName, elementName);

In addition to a COLLECTION name and an ELEMENT name, any number of optional variable declarations can be provided to DEQUE. These variable declarations describe the ELEMENT's fields / represent the values that the ELEMENT type will have in its struct. Declarations should be delimited / terminated with a ;

In the following example, we'll name our COLLECTION type 'itemList' and our ELEMENT type 'item'. In addition, each 'item' ELEMENT will have an integer field called value and a float field called weight:

    import "deque.h"
    
    DEQUE(itemList,
          item,
          int value; // item->value items have a an int value member
          float weight; // item->weight items have a float weight member
          );
          
## Application

Once a new DEQUE macro has completed and its types (the COLLECTION and ELEMENT) have been created, it can be used within an application by using the following API:

| Method | Description |
| -------|-------------|
| COLLECTION_new() | Create and Intantiate / Allocate a new COLLECTION 
| COLLECTION_add(ELEMENT) | Push a ELEMENT## at the head of the Deque (like stack) |
| COLLECTION_push(ELEMENT) | Push a ELEMENT## at the tail of the Deque (like queue) |

### Example

In the example/ directory, the following working example is provided:

    include "item.h"
    
    int main(int argc, char *argv[])
    {
      itemDequeue ideq = new_itemDequeue();
      item i = new_item();
      i->value = 4;
      itemDequeue_add(ideq, i);
      itemDequeue_print(ideq);
      return 1;
    }

## TODO

Soon, the COLLECTIONS will have map and reduce inline function which accepts a lambda (a void* function pointer) enabling them to be suitable for functional programming.
