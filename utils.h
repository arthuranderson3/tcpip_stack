#ifndef __TCPIP_STACK_UTILS__
#define __TCPIP_STACK_UTILS__

#include <stdint.h>

/*
apply_mask :
prefix - is a pointer to string representing an IP address.
mask : is any value [0-32]
str_prefix : pointer to a char array of size 16 bytes. This function must fill this array with the output.

This function must apply the mask on prefix and store the result in str_prefix.
For eg : prefix = 122.1.1.1, mask 24, then str_prefix will store 122.1.1.0
*/
void
apply_mask(char *prefix, char mask, char *str_prefix);

void
layer2_fill_with_broadcast_mac(char *mac_array);

#define IS_MAC_BROADCAST_ADDR(mac) \
    (mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF \
    && mac[3] == 0xFF && mac[4] == 0xFF && mac[5] == 0xFF)
 
unsigned int
convert_ip_from_str_to_int(char *ip_addr);

void
convert_ip_from_int_to_str(uint32_t ip_addr, char *output_buffer);

char *
tcp_ip_convert_ip_n_to_p(uint32_t ip_addr, char *output_buffer);

uint32_t
tcp_ip_convert_ip_p_to_n(char *ip_addr);

#endif // __TCPIP_STACK_UTILS__
