#ifndef __TCPIP_STACK_GLTHREAD__
#define __TCPIP_STACK_GLTHREAD__

typedef struct _glthread {
  struct _glthread * next;
  struct _glthread * prev;
} glthread_t;

void
glthread_init(glthread_t * node);

void
glthread_append(glthread_t * base_node, glthread_t * new_node);

void
glthread_insert(glthread_t * base_node, glthread_t * new_node);

void
glthread_add_tail(glthread_t * base_node, glthread_t * new_node);

void
glthread_remove(glthread_t * node);

void
glthread_delete_list(glthread_t * base_node);

unsigned int
glthread_get_list_count(glthread_t * base_node);

void
glthread_priority_insert(glthread_t * base_node, 
			glthread_t * node,
			int (*comp_fn)(void *, void *),
			int offset);
 

#define GLTHREAD_TO_STRUCT(fn_name, structure_name, field_name)                        \
    static inline structure_name * fn_name(glthread_t *glthreadptr){                   \
        return (structure_name *)((char *)(glthreadptr) - (char *)&(((structure_name *)0)->field_name)); \
    }
#define IS_GLTHREAD_LIST_EMPTY(glthreadptr)         \
    ((glthreadptr)->prev == 0 && (glthreadptr)->next == 0)

#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(glthreadptr, offset)  \
    (void *)((char *)(glthreadptr) - offset)

#define BASE(glthreadptr)   ((glthreadptr)->next)

#define ITERATE_GLTHREAD_BEGIN(glthreadptrstart, glthreadptr)                                      \
{                                                                                                  \
    glthread_t *_glthread_ptr = NULL;                                                              \
    glthreadptr = BASE(glthreadptrstart);                                                          \
    for(; glthreadptr!= NULL; glthreadptr = _glthread_ptr){                                        \
        _glthread_ptr = (glthreadptr)->next;

#define ITERATE_GLTHREAD_END(glthreadptrstart, glthreadptr)                                        \
        }}


#endif // __TCPIP_STACK_GLTHREAD__
