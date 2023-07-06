#ifndef __TCPIP_STACK_NET__
#define __TCPIP_STACK_NET__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IP_ADDR_V4_ADDR_SIZE   16
#define MAC_ADDR_SIZE     8

/* Forward declaration */
struct node_;
typedef struct interface_ interface_t;

typedef enum {

	FALSE,
	TRUE 
} bool_t;

typedef struct ip_addr_v4_ {

	char ip_addr[IP_ADDR_V4_ADDR_SIZE];
} ip_addr_v4_t;

typedef struct mac_addr_ {

	uint8_t mac[MAC_ADDR_SIZE];
} mac_addr_t;

typedef struct node_nw_prop_ {

	// L3 properties
	// loopback address
	bool_t        is_lb_addr_config;
	ip_addr_v4_t  lb_addr;
} node_nw_prop_t;

static inline void
init_node_nw_prop(node_nw_prop_t * node_nw_prop) {

	node_nw_prop->is_lb_addr_config = FALSE;
	memset(node_nw_prop->lb_addr.ip_addr, 0, IP_ADDR_V4_ADDR_SIZE);
}

typedef struct intf_nw_prop_ {

	// L2 properties
	mac_addr_t    mac_addr;

	bool_t        is_ip_addr_config;
	ip_addr_v4_t  ip_addr;
	char mask;
} intf_nw_prop_t;

static inline void
init_intf_nw_prop(intf_nw_prop_t * intf_nw_props) {

	memset(intf_nw_props->mac_addr.mac, 0, MAC_ADDR_SIZE);
	intf_nw_props->is_ip_addr_config = FALSE;
	memset(intf_nw_props->ip_addr.ip_addr, 0, IP_ADDR_V4_ADDR_SIZE);
	intf_nw_props->mask = 0;
}

// GET shorthand Macros
#define IF_MAC(intf_ptr)  ((intf_ptr)->intf_nw_props.mac_addr.mac)
#define IF_IP(intf_ptr)   ((intf_ptr)->intf_nw_props.ip_addr.ip_addr)
#define NODE_LO_ADDR(node_ptr)  ((node_ptr)->node_nw_prop.lb_addr.ip_addr)
#define IS_INTF_L3_MODE(intf_ptr) ((intf_ptr)->intf_nw_props.is_ip_addr_config) 

// APIs to set Network Node Properties
bool_t node_set_loopback_address(struct node_ *node, char *ip_addr);
bool_t node_set_intf_ip_address(struct node_ *node, char *local_if, char *ip_addr, char mask);
bool_t node_unset_intf_ip_address(struct node_ *node, char *local_if);

void interface_assign_mac_address(interface_t* interface);

static inline void 
print_node_nw_prop(node_nw_prop_t * node_ptr) {
	printf("\tNode loopback addr : %s/32\n", node_ptr->lb_addr.ip_addr);
}

static inline void
print_intf_nw_prop(intf_nw_prop_t * intf_ptr) {
	printf("\t\tIPv4: %s/%d   MAC : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", 
	intf_ptr->ip_addr.ip_addr, intf_ptr->mask, 
	intf_ptr->mac_addr.mac[0],
	intf_ptr->mac_addr.mac[1],
	intf_ptr->mac_addr.mac[2],
	intf_ptr->mac_addr.mac[3],
	intf_ptr->mac_addr.mac[4],
	intf_ptr->mac_addr.mac[5]);
}

interface_t *
node_get_matching_subnet_interface(struct node_ *node, char *ip_addr);

#endif // __TCPIP_STACK_NET__
