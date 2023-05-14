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
    printf("Found Node %s\n", node->name);
    interface_t * intf = get_node_if_by_name(node, "eth0/0");
    assert(intf);
    printf("Found Intf %s\n", intf->name);

    ip_addr_v4_t ip_v4 = ip_parse_v4("127.0.0.1");
    assert(ip_v4.octet[0] == 127);
    assert(ip_v4.octet[1] == 0);
    assert(ip_v4.octet[2] == 0);
    assert(ip_v4.octet[3] == 1);

    return 0;
}