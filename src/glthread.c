#include "glthread.h"
#include <stdlib.h>

void
glthread_init(glthread_t * cur_node) {
  cur_node->next = NULL;
  cur_node->prev = NULL;
}

void
glthread_append(glthread_t * base_node, glthread_t * new_node) {
    if(!base_node->next){
      base_node->next = new_node;
      new_node->prev = base_node;
      return;
    }

    glthread_t *temp = base_node->next;
    base_node->next = new_node;
    new_node->prev = base_node;
    new_node->next = temp;
    temp->prev = new_node;
}

void
glthread_insert(glthread_t * base_node, glthread_t * new_node) {
  if (!base_node->prev) {
    new_node->prev = NULL;
    new_node->next = base_node;
    base_node->prev = new_node;
    return;
  }

  glthread_t * temp = base_node->prev;
  temp->next = new_node;
  new_node->prev = temp;
  new_node->next = base_node;
  base_node->prev = new_node;
}

void
glthread_add_tail(glthread_t * base_node, glthread_t * new_node) {
  glthread_t * prev = NULL;
  glthread_t * iter = base_node->next;
  while(iter != NULL) {
    prev = iter;
    iter = iter->next;
  }
  if (prev) {
    glthread_append(prev, new_node);
  } else {
    glthread_append(base_node, new_node);
  }
}

void
glthread_remove(glthread_t * cur_node) {
  if (!cur_node->prev) {
    if (cur_node->next) {
      cur_node->next->prev = NULL;
      cur_node->next = NULL;
      return;
    }
    return;
  }
  if (!cur_node->next) {
    cur_node->prev->next = NULL;
    cur_node->prev = NULL;
    return;
  }

  cur_node->prev->next = cur_node->next;
  cur_node->next->prev = cur_node->prev;
  cur_node->prev = NULL;
  cur_node->next = NULL;
}

void
glthread_delete_list(glthread_t * base_node) {

    glthread_t *glthreadptr = NULL;
               
    ITERATE_GLTHREAD_BEGIN(base_node, glthreadptr){
        glthread_remove(glthreadptr);
    } ITERATE_GLTHREAD_END(base_node, glthreadptr);

}

unsigned int
glthread_get_list_count(glthread_t * base_node) {
  unsigned int count = 0;
    glthread_t *glthreadptr = NULL;
               
    ITERATE_GLTHREAD_BEGIN(base_node, glthreadptr){
        count++;
    } ITERATE_GLTHREAD_END(base_node, glthreadptr);

  return count;
}

void
glthread_priority_insert(glthread_t * base_node, 
			glthread_t * cur_thread,
			int (*comp_fn)(void *, void *),
			int offset) {
    glthread_t *curr = NULL,
               *prev = NULL;

    glthread_init(cur_thread);

    if(IS_GLTHREAD_LIST_EMPTY(base_node)){
        glthread_append(base_node, cur_thread);
        return;
    }

    /* Only one node*/
    if(base_node->next && !base_node->next->next){
        if(comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(base_node->next, offset), 
                GLTHREAD_GET_USER_DATA_FROM_OFFSET(cur_thread, offset)) == -1){
            glthread_append(base_node->next, cur_thread);
        }
        else{
            glthread_append(base_node, cur_thread);
        }
        return;
    }

    if(comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(cur_thread, offset), 
            GLTHREAD_GET_USER_DATA_FROM_OFFSET(base_node->next, offset)) == -1){
        glthread_append(base_node, cur_thread);
        return;
    }

    ITERATE_GLTHREAD_BEGIN(base_node, curr){

        if(comp_fn(GLTHREAD_GET_USER_DATA_FROM_OFFSET(cur_thread, offset), 
                GLTHREAD_GET_USER_DATA_FROM_OFFSET(curr, offset)) != -1){
            prev = curr;
            continue;
        }

        glthread_append(curr, cur_thread);
        return;

    }ITERATE_GLTHREAD_END(base_node, curr);

    /*Add in the end*/
    glthread_append(prev, cur_thread);

}

