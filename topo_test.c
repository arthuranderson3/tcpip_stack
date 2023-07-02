#include "graph.h"
#include "net.h"
#include <stdio.h>

extern graph_t *build_first_topo();

int 
main(int argc, char **argv){

    graph_t *topo = build_first_topo();
    print_graph(topo);

    node_t * node = get_node_by_node_name(topo, "R0_re");
    assert(node);
    printf("Found Node %s\n", node->node_name);
    interface_t * intf = get_node_if_by_name(node, "eth0/0");
    assert(intf);
    printf("Found Intf %s\n", intf->if_name);

    return 0;
}