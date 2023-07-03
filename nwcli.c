#include "CommandParser/libcli.h"
#include "CommandParser/cmdtlv.h"
#include "cmdcodes.h"
#include "graph.h"
#include <stdio.h>

extern graph_t * topo;

int 
show_topology_cb(param_t * param, ser_buff_t * tlv_buff, op_mode enable_or_disable) {
	printf("%s() is called.. ", __FUNCTION__);
	int cmd_code = EXTRACT_CMD_CODE(tlv_buff);
	printf("CMD_CODE %d\n", cmd_code);
	
	print_graph(topo);

	return 0;
}

void
nw_init_cli() {

	init_libcli();

	param_t * show = libcli_get_show_hook();
	param_t * debug = libcli_get_debug_hook();
	param_t * debug_show = libcli_get_debug_show_hook();
	param_t * config = libcli_get_config_hook();
	param_t * clear =libcli_get_clear_hook();
	param_t * run = libcli_get_run_hook();

	/**
	 * show topology
	 * */
	static param_t show_topology;
	init_param(&show_topology, CMD, "topology", show_topology_cb, NULL, INVALID, NULL, "help: show topology");
	libcli_register_param(show, &show_topology);
	set_param_cmd_code(&show_topology, CMDCODES_SHOW_TOPOLOGY);

	support_cmd_negation(config);
}

