#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern void init_udp_socket(node_t *);

graph_t * 
create_new_graph(char * topology_name) {

  // calloc allocates and initializes memory to zero
  graph_t * g = calloc(1, sizeof(graph_t));
  strncpy(g->topology_name, topology_name, TOPOLOGY_NAME_SIZE);
  g->topology_name[TOPOLOGY_NAME_SIZE-1] = '\0';

  // initialize the node list glthread
  glthread_init(&g->node_list);

  return g;
}

node_t * 
create_graph_node(graph_t * g, char* node_name) {
  node_t * node = calloc(1, sizeof(node_t));
  strncpy(node->node_name, node_name, NODE_NAME_SIZE);
  node->node_name[NODE_NAME_SIZE-1] = '\0';
  init_node_nw_prop(&node->node_nw_prop);
  init_udp_socket(node);
  // initialize the nodes link into glthread
  glthread_init(&node->graph_glue);
  // append it to the graph's list
  glthread_append(&g->node_list, &node->graph_glue);
  return node;
}

void
insert_link_between_two_nodes(node_t * node_1,
	node_t * node_2,
	char * from_if_name,
	char * to_if_name,
	unsigned int cost ) {

  // create the link - cable between the routers
  link_t * link = calloc(1, sizeof(link_t));
  strncpy(link->if1.if_name, from_if_name, IF_NAME_SIZE);
  link->if1.if_name[IF_NAME_SIZE-1] = '\0';
  strncpy(link->if2.if_name, to_if_name, IF_NAME_SIZE);
  link->if2.if_name[IF_NAME_SIZE-1] = '\0';

  // assign the owning nodes
  link->if1.att_node = node_1;
  link->if2.att_node = node_2;

  // assign back(weak) pointers to this link
  link->if1.link = link;
  link->if2.link = link;
  link->cost = cost;

  // Get the next available slot in the node / router
  // and plug in the cables interface to the slot
  int empty_slot = get_node_intf_available_slot(node_1);
  assert(empty_slot > -1);
  if (empty_slot > -1) {
    node_1->intf[empty_slot] = &link->if1;
  }
  empty_slot = get_node_intf_available_slot(node_2);
  assert(empty_slot > -1);
  if (empty_slot > -1) {
    node_2->intf[empty_slot] = &link->if2;
  }
}

void print_graph(graph_t * g) {
  glthread_t *curr;
  node_t *node;

  printf("Topology %s\n", g->topology_name);
  ITERATE_GLTHREAD_BEGIN(&g->node_list, curr){
    node = graph_glue_to_node(curr);
    print_node(node);    
  } ITERATE_GLTHREAD_END(&g->node_list, curr);
}

void print_node(node_t * node) {
    unsigned int i = 0;
    interface_t *intf;

    printf("Node Name = %s : \n", node->node_name);
    print_node_nw_prop(&node->node_nw_prop);

    for( ; i < MAX_INTF_PER_NODE; i++){
        
        intf = node->intf[i];
        if(!intf) break;
        print_interface(intf);
    }

}

void print_interface(interface_t * endpoint) {

  // Get the link between the two nodes
  link_t *link = endpoint->link;
  // Get the neighbor node of the endpoint
  node_t *nbr_node = get_nbr_node(endpoint);

  printf(" Local Node : %s, Interface From = %s, To %s, cost = %u\n", 
            endpoint->att_node->node_name, 
            endpoint->if_name, nbr_node->node_name, link->cost); 
  print_intf_nw_prop(&endpoint->intf_nw_props);
}

interface_t *
get_node_if_by_name(node_t *node, char *if_name) {
  for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
    // We append the nodes when creating them
    // If we have reached the end of the cables interfaces that are 
    // plugged in...
    if (node->intf[i] == NULL) return NULL;

    if (strncmp(node->intf[i]->if_name, if_name, IF_NAME_SIZE) == 0) 
      return node->intf[i];
  }
  return NULL;
}

node_t *
get_node_by_node_name(graph_t *topo, char *node_name) {
  glthread_t *curr;
  node_t *node;

  ITERATE_GLTHREAD_BEGIN(&topo->node_list, curr){
    if (curr) {
      node = graph_glue_to_node(curr);
      if (strncmp(node->node_name, node_name, NODE_NAME_SIZE) == 0) {
        return node;
      }
    }
  } ITERATE_GLTHREAD_END(&topo->node_list, curr);
  return NULL;
}
