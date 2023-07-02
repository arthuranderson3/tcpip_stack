#include <stdio.h>
#include "utils.h"


int main(int argc, char* argv[]) {

    char * prefix = "122.1.1.1";
    char mask = 24;
    char masked_prefix[16] = { '\0' };

    apply_mask(prefix, mask, masked_prefix);

    printf("masked_prefix: %s\n", masked_prefix);

    
	return 0;
}
