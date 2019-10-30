/*
 * 将十六进制参数转换为点分十进制串并打印
 * 0x8002c2f2 ---> 128.2.194.242
 */

#include <stdio.h>
#include <arpa/inet.h>

#include "wdebug.h"

int main(int argc, char *argv[]){
	if (argc != 2) {
		P_MSG("Usage:\t%s <hex number>\n", argv[0]);
		return -1;
	}
	struct in_addr inaddr;
	uint32_t addr;
	char IP[32];

	sscanf(argv[1], "%x", &addr);
	inaddr.s_addr = htonl(addr);
	          
	if (inet_ntop(AF_INET, &inaddr, IP, sizeof(IP)) == NULL) {
		unix_error("inet_ntop", -1);
	}

	printf("%s\n", IP);

	return 0;
}
