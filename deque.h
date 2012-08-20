#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

/** 
 * *********************************************************
 *
 *   ELEMENT       new_ELEMENT(void);  
 *
 *   COLLECTION    new_COLLECTION(void);
 *
 *   void          ELEMENT_delete(ELEMENT a); 
 *
 *   void          COLLECTION_delete(COLLECTION c);
 *
 *   void          COLLECTION_remove(COLLECTION c, ELEMENT a);
 *
 *   void          COLLECTION_add(COLLECTION c, ELEMENT a);
 *
 *   void          COLLECTION_push(COLLECTION c, ELEMENT a);
 *
 *   void          COLLECTION_append(COLLECTION c1, COLLECTION c2);
 *
 *   void          COLLECTION_prepend(COLLECTION c1, COLLECTION c2);
 *
 *   ELEMENT       COLLECTION_poll(COLLECTION c);
 *
 *   ELEMENT       COLLECTION_pop(COLLECTION c);
 *
 *   ELEMENT       COLLECTION_peek(COLLECTION c);
 *
 *   ELEMENT       COLLECTION_last(COLLECTION c);
 *
 *   ELEMENT_iter  COLLECTION_first(COLLECTION c);
 *
 *   ELEMENT_iter  COLLECTION_last(COLLECTION c);
 *
 *   int           COLLECTION_length(COLLECTION c)
 *
 *   append(COLLECTION c1, COLLECTION c2)
 *   prepend(COLLECTION c1, COLLECTION c2)
 *
 *   todo: reverse
 *   map (func, type), mapreduce (fun, type), filter (pred)
 *
 * *********************************************************
 * Example Usage
 *
 *  ThreadDeque threadq;
 *
 * DEQUE(ThreadDeque, Thread
 *    int val1;
 *    int val2;
 *  );
 *
 *  threadq  = new_ThreadDeque();
 *  Thread t = new_Thread();
 *  t->val1  = 0;
 *  t->val2  = 1;
 *  ThreadDeque_push(threadq, t);
 *
 *  Thread_iter i = ThreadDeque_first(threadq);
 *  while (ThreadDeque_hasNext(i)) {
 *    printf("a=%d; b=%d\n", i->a, i->b);
 *  }
 * *********************************************************
 */

/**@hideinitializer
 * Generates a new type for list of elements */
#define DEQUE(COLLECTION, ELEMENT, REST)	                        \
  DEQUE_INIT_TYPE(COLLECTION, ELEMENT)		                        \
  DEQUE_CREATE_TYPE(COLLECTION, ELEMENT, REST)

#define DEQUE_INIT_TYPE(COLLECTION, ELEMENT)				\
  /** automatic type: ENAME##_list_t is a list of ENAME##_t */		\
  typedef struct COLLECTION##_s* COLLECTION;				\
  /** automatic type: defines ENAME##_t */				\
  typedef struct ELEMENT##_s* ELEMENT;					\
  /** automatic type: ELEMENTIter is an iter on lists of ELEMENT */	\
  typedef ELEMENT ELEMENT##Iter;					\
  typedef struct ELEMENT##_args_s ELEMENT##_args;			\
  typedef void*(*ELEMENT##_lambda)(struct ELEMENT##_args_s*);

/**@hideinitializer
 * The effective type declaration for lists */
#define DEQUE_CREATE_TYPE(COLLECTION, ELEMENT, REST)			\
									\
  struct ELEMENT##_args_s						\
  {									\
    int argc;								\
    char** argv;							\
  };									\
									\
  /** from automatic type: ELEMENT## */					\
  struct ELEMENT##_s							\
  {									\
    struct ELEMENT##_s*_prev; /**< @internal previous cell */		\
    struct ELEMENT##_s*_next; /**< @internal next cell */		\
    int _id;								\
    char* _name;							\
    REST /* user specified by DEQUE macro */				\
  };									\
  									\
  /** @internal */							\
  struct COLLECTION##_s							\
  {									\
    struct ELEMENT##_s* _head; /**< @internal head of the list */	\
    struct ELEMENT##_s* _tail; /**< @internal tail of the list */	\
  };									\
									\
  /** @internal */							\
  /* creates a variable of type ELEMENT */				\
  static inline ELEMENT new_##ELEMENT(void)				\
  {									\
    ELEMENT e = (ELEMENT)malloc(sizeof(struct ELEMENT##_s));		\
    e->_next = NULL;							\
    e->_prev = NULL;							\
    e->_name = "(NULL)";						\
    return e;								\
  }									\
  									\
  /** @internal */							\
  /* Push a ELEMENT## at the head of the Deque (like stack) */		\
  static inline void COLLECTION##_push(COLLECTION l, ELEMENT e)		\
  {									\
    if(l->_tail == NULL) {						\
      l->_tail = e;							\
    } else {								\
      l->_head->_prev = e;						\
      e->_prev = NULL;							\
      e->_next = l->_head; l->_head = e;				\
    }									\
  }									\
  									\
  /** @internal */							\
  /* Push a ELEMENT## at the tail of the Deque (like queue) */		\
  static inline void COLLECTION##_add(COLLECTION l, ELEMENT e)		\
  {									\
    if(l->_head == NULL) {						\
      l->_head = e;							\
    } else {								\
      l->_tail->_next = e;						\
    }									\
    e->_next = NULL;							\
    e->_prev = l->_tail;						\
    l->_tail = e;							\
  }									\
  									\
  /** @internal */							\
  static inline ELEMENT COLLECTION##_stack_peek(COLLECTION l)		\
  {									\
    return l->_head;							\
  }									\
  									\
  /** @internal */							\
  static inline ELEMENT COLLECTION##_queue_peek(COLLECTION l)		\
  {									\
    return l->_tail;							\
  }									\
  									\
  /** @internal */							\
  /* Create a new Deque of type COLLECTION */				\
  static inline COLLECTION new_##COLLECTION(void)			\
  {									\
    COLLECTION l;							\
    l=(COLLECTION)malloc(sizeof(struct COLLECTION##_s));		\
    l->_head = NULL;							\
    l->_tail = l->_head;						\
    return l;								\
  }									\
  									\
  /** @internal */							\
  static inline int COLLECTION##_isEmpty(COLLECTION l)			\
  {									\
    return (l->_head == NULL);						\
  }									\
  									\
  /** @internal */							\
  /* destroys a ELEMENT by freeing its malloc */			\
  static inline void ELEMENT##_destroy(ELEMENT e)			\
  {									\
    free(e);								\
  }									\
  									\
  static inline int ELEMENT##_getId(ELEMENT e)				\
  {									\
    return e->_id;							\
  }									\
  									\
  static inline void ELEMENT##_setId(ELEMENT e, int id)			\
  {									\
    e->_id = id;							\
  }									\
  									\
  static inline char* ELEMENT##_getName(ELEMENT e)			\
  {									\
    return e->_name;							\
  }									\
  									\
  static inline void ELEMENT##_setName(ELEMENT e, char* n)		\
  {									\
    e->_name = n;							\
  }									\
  									\
  static char* ELEMENT##_toString(ELEMENT e)				\
  {									\
    char *__result = NULL;						\
    int __prv = -1;							\
    int __nxt = -1;							\
									\
    if (e->_prev) {							\
      __prv = (e->_prev)->_id;						\
    }									\
    									\
    if (e->_next) {							\
      __nxt = (e->_next)->_id;						\
    }									\
    									\
    asprintf(&__result,							\
	     "{'id' : %d, '_prev' : %d, '_next' : %d, '_name' : '%s'}",	\
	     (e->_id), __prv, __nxt, e->_name);				\
    return __result;							\
  }									\
									\
  static char* ELEMENT##Iter_toString(ELEMENT##Iter e)			\
  {									\
    char *__result = NULL;						\
    int __prv = -1;							\
    int __nxt = -1;							\
									\
    if (e->_prev) {							\
      __prv = (e->_prev)->_id;						\
    }									\
    									\
    if (e->_next) {							\
      __nxt = (e->_next)->_id;						\
    }									\
    									\
    asprintf(&__result,							\
	     "{'id' : %d, '_prev' : %d, '_next' : %d, '_name' : '%s'}",	\
	     (e->_id), __prv, __nxt, e->_name);				\
    return __result;							\
  }									\
									\
  /** @internal */							\
  static inline void COLLECTION##_destroy(COLLECTION l)			\
  {									\
    free(l);								\
  }									\
									\
  /** @internal */							\
  static inline void COLLECTION##_disassociate(COLLECTION l, ELEMENT e)	\
  {									\
    ELEMENT p = e->_prev;						\
    if(p) {								\
      p->_next = e->_next;						\
    } else {								\
      l->_head = e->_next;						\
      if(e->_next) {							\
	e->_next->_prev = p;						\
      } else {								\
	l->_tail = p;							\
      }									\
    }									\
  }									\
									\
  static inline void COLLECTION##_remove(COLLECTION l, ELEMENT e)	\
  {									\
    ELEMENT p = e->_prev;						\
    if(p) {								\
      p->_next = e->_next;						\
    } else {								\
      l->_head = e->_next;						\
      if(e->_next) {							\
	e->_next->_prev = p;						\
      } else {								\
	l->_tail = p;							\
      }									\
    }									\
    ELEMENT##_destroy(e);						\
  }									\
  									\
  /** @internal */							\
  static inline COLLECTION init_##COLLECTION(COLLECTION a)		\
  {									\
    int cnt;								\
    COLLECTION _tmp = new_##COLLECTION();				\
    ELEMENT _i = a->_head;						\
    do {								\
      COLLECTION##_add(_tmp,_i);					\
      _i = _i->_next;							\
    } while (_i->_next);						\
    return _tmp;							\
  }									\
									\
  /** @internal */							\
  static inline COLLECTION COLLECTION##_append(COLLECTION a, COLLECTION z) \
  {									\
    (a->_tail)->_next = (z->_head)->_prev;				\
    (a->_tail) = z->_tail;						\
    return a;								\
  }									\
									\
  /** @internal */							\
  static inline COLLECTION COLLECTION##_prepend(COLLECTION z, COLLECTION a) \
  {									\
    (a->_tail)->_next = (z->_head)->_prev;				\
    (a->_tail) = z->_tail;						\
    return a;								\
  }									\
									\
  /** @internal */							\
  static inline ELEMENT COLLECTION##_pop(COLLECTION l)			\
  {									\
    ELEMENT e = l->_head;						\
    COLLECTION##_disassociate(l, e);					\
    return e;								\
  }									\
  									\
  /** @internal */							\
  /* Make sure this doesn't segfault when empty */			\
  static inline ELEMENT COLLECTION##_poll(COLLECTION l)			\
  {									\
    ELEMENT e = l->_tail;						\
    COLLECTION##_disassociate(l, e);					\
    return e;								\
  }									\
									\
  /** @internal */							\
  static inline ELEMENT##Iter COLLECTION##_iterator(COLLECTION l)	\
  {									\
    return l->_head;							\
  }									\
									\
  /** @internal */							\
  static inline ELEMENT##Iter COLLECTION##_ascentIterator(COLLECTION l)	\
  {									\
    return l->_head;							\
  }									\
									\
  /** @internal */							\
  /* In future, reverse list & return head (always next, no prev) */	\
  static inline ELEMENT##Iter COLLECTION##_descentIterator(COLLECTION l) \
  {									\
    return l->_tail;							\
  }									\
									\
  /** @internal */							\
  static inline int ELEMENT##Iter_hasNext(ELEMENT##Iter i)		\
  {									\
    return (i->_next != NULL);						\
  }									\
									\
  /** @internal */							\
  static inline int ELEMENT##Iter_hasPrev(ELEMENT##Iter i)		\
  {									\
    return (i->_prev != NULL);						\
  }									\
  									\
  /** @internal */							\
  static inline ELEMENT##Iter ELEMENT##Iter_next(ELEMENT##Iter i)	\
  {									\
    return i->_next;							\
  }									\
									\
  /** @internal */							\
  static inline ELEMENT##Iter ELEMENT##Iter_prev(ELEMENT##Iter i)	\
  {									\
    return i->_prev;							\
  }									\
									\
  /** @internal */							\
  static inline int COLLECTION##_size(COLLECTION l)			\
  {									\
    ELEMENT##Iter i= l->_head;						\
    int k=0;								\
    while(i!=NULL) {							\
      k++;								\
      i=i->_next;							\
    }									\
    return k;								\
  }									\
									\
  /** @internal */							\
  static void COLLECTION##_print(COLLECTION l)				\
  {									\
    ELEMENT##Iter i= l->_head;						\
    while(i!=NULL) {							\
      printf("%s\n", ELEMENT##Iter_toString(i));			\
      i=i->_next;							\
    }									\
  }									\
									\
  /** @internal */							\
  static inline ELEMENT##Iter COLLECTION##_getNth(COLLECTION l, int n)	\
  {									\
    ELEMENT##Iter i = l->_head;						\
    int k=0;								\
    while(i!=NULL) {							\
      if (k==n) {							\
	return i;							\
      }									\
      i=i->_next;							\
    }									\
    return NULL;							\
  }
