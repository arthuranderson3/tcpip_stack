#include "net.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ip_addr_v4_t
ip_parse_v4(char * addr) {

  ip_addr_v4_t ip;
  memset(ip.octet, 0, IP_ADDR_V4_OCTET_SIZE);

  int size = strlen(addr) + 1;
  char address[size];
  strncpy(address, addr, size - 1);
  address[size - 1] = '\0';

  // IP V4 address xxx.xxx.xxx.xxx
  // each xxx is [0-255]
  int idx = 0;
  char * delim = ".";
  char * token = strtok(address, delim);
  while (token && idx < 4) {
    char * end;
    ip.octet[idx] = (uint8_t)strtol(token, &end, 10);;
    idx++;
    token = strtok(NULL, delim);
  }
  return ip;
}

void 
node_nw_prop_init(node_nw_prop_t *p) {
  p->is_loopback_addr_config = FALSE;
  memset(p->loopback_addr.octet, 0, IP_ADDR_V4_OCTET_SIZE);
}

void 
intf_nw_prop_init(intf_nw_prop_t *i) {
  
}

