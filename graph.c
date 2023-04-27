#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

graph_t * 
create_new_graph(char * topology_name) {

  graph_t * g = calloc(1, sizeof(graph_t));
  strncpy(g->topology_name, topology_name, TOPOLOGY_NAME_SIZE);
  g->topology_name[TOPOLOGY_NAME_SIZE-1] = '\0';
  glthread_init(&g->node_list);

  return g;
}

node_t * 
create_graph_node(graph_t * g, char* node_name) {

  node_t * n = calloc(1, sizeof(node_t));
  strncpy(n->name, node_name, NODE_NAME_SIZE);
  n->name[NODE_NAME_SIZE-1] = '\0';
  glthread_init(&n->graph_glue);

  glthread_append(&g->node_list, &n->graph_glue);
  return n;
}

void
insert_link_between_two_nodes(node_t * node_1,
	node_t * node_2,
	char * from_intf_name,
	char * to_intf_name,
	unsigned int cost ) {

  link_t * link = calloc(1, sizeof(link_t));
  strncpy(link->intf1.name, from_intf_name, INTF_NAME_SIZE);
  link->intf1.name[INTF_NAME_SIZE-1] = '\0';
  strncpy(link->intf2.name, to_intf_name, INTF_NAME_SIZE);
  link->intf2.name[INTF_NAME_SIZE-1] = '\0';

  link->intf1.att_node = node_1;
  link->intf2.att_node = node_2;
  link->intf1.link = link;
  link->intf2.link = link;
  link->cost = cost;

  int next_avail = get_node_intf_available_slot(node_1);
  assert(next_avail > -1);
  if (next_avail > -1) {
    node_1->intf[next_avail] = &link->intf1;
  }
  next_avail = get_node_intf_available_slot(node_2);
  assert(next_avail > -1);
  if (next_avail > -1) {
    node_2->intf[next_avail] = &link->intf2;
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

    printf("Node Name = %s : \n", node->name);
    for( ; i < MAX_INTF_PER_NODE; i++){
        
        intf = node->intf[i];
        if(!intf) break;
        print_intf(intf);
    }

}

void print_intf(interface_t * endpoint) {
   link_t *link = endpoint->link;
   node_t *nbr_node = get_nbr_node(endpoint);

   printf(" Local Node : %s, Interface Name = %s, Nbr Node %s, cost = %u\n", 
            endpoint->att_node->name, 
            endpoint->name, nbr_node->name, link->cost); 

}
