#include "net.h"

#include "graph.h"
#include "utils.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static bool_t rand_init = FALSE;

void 
assign_rand_mac(mac_addr_t * addr) {
	if (!rand_init) {
		srand(time(NULL));
		rand_init = TRUE;
	}
	for (int i = 0; i < MAC_ADDR_SIZE; i++) {
		addr->mac[i] = rand() / ((RAND_MAX + 1u) / 255);
	}
}

static unsigned int
hash_code(void *ptr, unsigned int size) {
	unsigned int value = 0, i = 0;
	char * str = (char*)ptr;
	while(i < size) {
		value += *str;
		value *= 97;
		str++;
		i++;
	}
	return value;
}

void 
interface_assign_mac_address(interface_t * interface) {
	node_t * node = interface->att_node;

	if (!node) {
		return;
	}

	assign_rand_mac(&interface->intf_nw_props.mac_addr);
}

bool_t
node_set_loopback_address(node_t *node, char *ip_addr) {
	assert(ip_addr);

	node->node_nw_prop.is_lb_addr_config = TRUE;
	strncpy(NODE_LO_ADDR(node), ip_addr, IP_ADDR_V4_ADDR_SIZE);
	NODE_LO_ADDR(node)[IP_ADDR_V4_ADDR_SIZE - 1] = '\0';
	/* NOTE: loopback address masks are always 32. so we don't need one here */
	return TRUE;
}

bool_t
node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask) {
	interface_t * interface = get_node_if_by_name(node, local_if);
	if (!interface) {
		assert(0);
		return FALSE;
	}

	strncpy(IF_IP(interface), ip_addr, IP_ADDR_V4_ADDR_SIZE);
	interface_assign_mac_address(interface);
	return TRUE;
}

interface_t *
node_get_matching_subnet_interface(node_t *node, char *ip_addr) {
	unsigned int i = 0;
	interface_t *intf;

	char *intf_addr = NULL;
	char mask;
	char intf_subnet[16];
	char subnet2[16];

	for( ; i < MAX_INTF_PER_NODE; i++) {

		intf = node->intf[i];
		if(!intf) return NULL;

		if(intf->intf_nw_props.is_ip_addr_config == FALSE)
			continue;

		intf_addr = IF_IP(intf);
		mask = intf->intf_nw_props.mask;

		memset(intf_subnet, 0 , 16);
		memset(subnet2, 0 , 16);
		apply_mask(intf_addr, mask, intf_subnet);
		apply_mask(ip_addr, mask, subnet2);

		if(strncmp(intf_subnet, subnet2, 16) == 0){
			return intf;
		}
	}
	return NULL;
}
