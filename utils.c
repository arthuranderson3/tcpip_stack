#include "utils.h"

#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>

/*
    apply_mask :
    prefix - is a pointer to string representing an IP address.
    mask : is any value [0-32]
    str_prefix : pointer to a char array of size 16 bytes. 
                This function must fill this array with the output.

    This function must apply the mask on prefix and store the result in str_prefix.
    For eg : prefix = 122.1.1.1, mask 24, then str_prefix will store 122.1.1.0
*/
void
apply_mask(char *prefix, char mask, char *str_prefix) {
    
	uint32_t binary_prefix = 0;
	uint32_t subnet_mask = 0xFFFFFFFF;

	if (mask == 32) {
		strncpy(str_prefix, prefix, 16);
		str_prefix[15] = '\0';
		return;
	}

	inet_pton(AF_INET, prefix, &binary_prefix);
	binary_prefix = htonl(binary_prefix);

	subnet_mask = subnet_mask << (32 - mask);

	binary_prefix = binary_prefix & subnet_mask;

	binary_prefix = htonl(binary_prefix);
	inet_ntop(AF_INET, &binary_prefix, str_prefix, 16);
	str_prefix[15] = '\0';
}

void
layer2_fill_with_broadcast_mac(char *mac) {
	mac[0] = 0xFF;
	mac[1] = 0xFF;
	mac[2] = 0xFF;
	mac[3] = 0xFF;
	mac[4] = 0xFF;
	mac[5] = 0xFF;
}

uint32_t
convert_ip_from_str_to_int(char *ip_addr) {
	int32_t inet_addr = 0;
	inet_pton(AF_INET, ip_addr, &inet_addr);
	inet_addr = htonl(inet_addr);
	return inet_addr;
}

void
convert_ip_from_int_to_str(uint32_t ip_addr, char *output_buffer) {
	char *out = output_buffer;
	memset(out, 0, 16);
	ip_addr = htonl(ip_addr);
	inet_ntop(AF_INET, &ip_addr, out, 16);
	out[15] = '\0';
}

char *
tcp_ip_convert_ip_n_to_p(uint32_t ip_addr, char *output_buffer) {

	char *out = NULL;
	static char str_ip[16];
	out = !output_buffer ? str_ip : output_buffer;
	memset(out, 0, 16);
	ip_addr = htonl(ip_addr);
	inet_ntop(AF_INET, &ip_addr, out, 16);
	out[15] = '\0';
	return out;
}

uint32_t
tcp_ip_convert_ip_p_to_n(char *ip_addr) {

	uint32_t binary_prefix = 0;
	inet_pton(AF_INET, ip_addr, &binary_prefix);
	binary_prefix = htonl(binary_prefix);
	return binary_prefix;
}

