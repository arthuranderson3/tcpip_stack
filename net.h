#ifndef __TCPIP_STACK_NET__
#define __TCPIP_STACK_NET__

#include <stdint.h>


#define IP_ADDR_V4_ADDR_SIZE   16
#define IP_ADDR_V4_OCTET_SIZE  4 
#define MAC_ADDR_SIZE     8

typedef enum {

  FALSE,
  TRUE 
} bool_t;

typedef struct ip_addr_v4 {

  uint8_t octet[IP_ADDR_V4_OCTET_SIZE];
} ip_addr_v4_t;

typedef struct mac_addr {

  uint8_t id[MAC_ADDR_SIZE];
} mac_addr_t;

typedef struct node_nw_prop {

  bool_t        is_loopback_addr_config;
  ip_addr_v4_t  loopback_addr;
} node_nw_prop_t;

typedef struct intf_nw_prop {

  mac_addr_t    mac_addr;
  bool_t        is_ip_addr_config;
  ip_addr_v4_t  ip_addr;
} intf_nw_prop_t;

ip_addr_v4_t
ip_parse_v4(char * addr);

void 
node_nw_prop_init(node_nw_prop_t *);

void 
intf_nw_prop_init(intf_nw_prop_t *);

#endif // __TCPIP_STACK_NET__
