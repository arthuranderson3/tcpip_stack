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

int
run_node_resolvearp_cb(param_t * param, ser_buff_t * tlv_buff, op_mode enable_or_disable) {
	printf("%s() is called.. ", __FUNCTION__);
	int cmd_code = EXTRACT_CMD_CODE(tlv_buff);
	printf("CMD_CODE %d\n", cmd_code);
	
	tlv_struct_t * tlv;
	char * node_name = NULL;
	char * ip_address = NULL;
	TLV_LOOP_BEGIN(tlv_buff, tlv) {
		if (strncmp(tlv->leaf_id, "node-name", strlen("node-name")) == 0) {
			node_name = tlv->value;
			continue;
		}
		if (strncmp(tlv->leaf_id, "ip-address", strlen("ip-address")) == 0) {
			ip_address = tlv->value;
			continue;
		}
	} TLV_LOOP_END;
	
	node_name = node_name ? node_name: "NO NODE NAME";
	ip_address = ip_address ? ip_address: "255.255.255.255";
	printf("node resolve arp { name: %s, ip-address: %s }\n", node_name, ip_address);

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

	/**
	 * run node <node-name> resolve-arp <ip-address>
	 * */
	static param_t run_node;
	init_param(&run_node, CMD, "node", NULL, NULL, INVALID, NULL, "help: run node");
	libcli_register_param(run, &run_node);

	static param_t run_node_name;
	init_param(&run_node_name, LEAF, NULL, NULL, NULL, STRING, "node-name", "help: run node <node-name>");
	libcli_register_param(&run_node, &run_node_name);

	static param_t run_node_name_resolvearp;
	init_param(&run_node_name_resolvearp, CMD, "resolve-arp", NULL, NULL, INVALID, NULL, "help: run node <node-name> resolve-arp");
	libcli_register_param(&run_node_name, &run_node_name_resolvearp);

	static param_t run_node_name_resolvearp_ipaddress;
	init_param(&run_node_name_resolvearp_ipaddress, LEAF, NULL, run_node_resolvearp_cb, NULL, IPV4, "ip-address", "help: run node <node-name> resolve-arp <ip-address>");
	libcli_register_param(&run_node_name_resolvearp, &run_node_name_resolvearp_ipaddress);
	set_param_cmd_code(&run_node_name_resolvearp_ipaddress, CMDCODES_RUN_NODE_RESOLVE_ARP);
	
	support_cmd_negation(config);
}

