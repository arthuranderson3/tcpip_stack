#include <stdio.h>
#include "CommandParser/libcli.h"
#include "graph.h"
#include "comm.h"

extern void nw_init_cli();
extern graph_t * build_first_topo();
graph_t * topo;

int
main(int argc, char **argv) {

	nw_init_cli();
	topo = build_first_topo();


	sleep(2); // give some time to receive the data

	node_t * snode = get_node_by_node_name(topo, "R0_re");
	interface_t * oif = get_node_if_by_name(snode, "eth0/0");
	char msg[] = "Hello, how are you\0";
	send_pkt_out(msg, strlen(msg), oif);

	printf("\nFLOOD =====\n");
	send_pkt_flood(snode, oif, msg, strlen(msg));

	start_shell();

	return 0;
}
