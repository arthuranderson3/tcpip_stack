#include "CommandParser/libcli.h"
#include "graph.h"

extern void nw_init_cli();
extern graph_t * build_first_topo();
graph_t * topo;

int
main(int argc, char **argv) {

	nw_init_cli();
	topo = build_first_topo();
	start_shell();

	return 0;
}