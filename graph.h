#ifndef __AA_TCPIP_STACK_GRAPH__
#define __AA_TCPIP_STACK_GRAPH__

#include <assert.h>
#include <string.h>
#include "gluethread/glthread.h"
#include "net.h"

#define IF_NAME_SIZE 16
#define NODE_NAME_SIZE 16
#define TOPOLOGY_NAME_SIZE 32
#define MAX_INTF_PER_NODE 10


/* Forward Declarations */
typedef struct node_ node_t;
typedef struct link_ link_t;

/**
 Router 
  + 1..* Interfaces

 Link
  Router @ interface -> Nbr Router @ interface

 Network Topology
  Router List

  [Router: Node] -- have -- [Ports: Interfaces]
  [Cable: Link] -- has -- [2 Endpoints: Interface]
 **/
typedef struct interface_ {
  char if_name[IF_NAME_SIZE];
  struct node_ * att_node;
  struct link_ * link;
  struct intf_nw_prop_ intf_nw_props;
} interface_t;

struct node_ {
  char node_name[NODE_NAME_SIZE];
  struct interface_ * intf[MAX_INTF_PER_NODE];
  glthread_t graph_glue;
  struct node_nw_prop_ node_nw_prop;
};

struct link_ {
  struct interface_ if1;
  struct interface_ if2;
  unsigned int cost;
};

GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, graph_glue);

typedef struct graph_ {
  char topology_name[TOPOLOGY_NAME_SIZE];
  glthread_t node_list; 
} graph_t;

/* Get Neighbor Node */
static inline node_t *
get_nbr_node(interface_t *interface) {
  
  assert(interface->link);
  assert(interface->att_node);

  if (interface == &interface->link->if1) {
    return interface->link->if2.att_node;
  }
  return interface->link->if1.att_node;
}

/* Get available interface slot */
static inline int
get_node_intf_available_slot(node_t *node) {
  for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
    if (node->intf[i]) continue;
    return i;
  }
  return -1;
}

graph_t * 
create_new_graph(char * topology_name);
void free_graph(graph_t * g);

node_t * 
create_graph_node(graph_t * g, char* node_name);

void
insert_link_between_two_nodes(node_t * rt_1,
	node_t * rt_2,
	char * from_if_name,
	char * to_if_name,
	unsigned int cost );

node_t *
get_linked_node(interface_t * intf);

int
get_node_available_intf(node_t * rt);

void 
print_graph(graph_t * g);

void 
print_node(node_t * node);

void
print_interface(interface_t * endpoint);

interface_t *
get_node_if_by_name(node_t *node, char *if_name);

node_t *
get_node_by_node_name(graph_t *topo, char *node_name);

#endif // __AA_TCPIP_STACK_GRAPH__
