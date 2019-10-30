/*
 * 将点分十进制参数转换为十六进制数并打印
 * 128.2.194.242 ---> 0x8002c2f2
 */

#include <stdio.h>
#include <arpa/inet.h>

#include "wdebug.h"

int main(int argc, char *argv[]){
	if (argc != 2) {
		P_MSG("Usage:\t%s <dotted-decimal>\n", argv[0]);
		return -1;
	}
	struct in_addr inaddr;
	int r = 0;
	r = inet_pton(AF_INET, argv[1], &inaddr);
	if (r == 0) {
		fprintf(stderr, "%s\n", "invalid dotted-decimal address");
		return -1;
	} else if (r < 0) {
		unix_error("inet_pton", -1);
	}

	printf("%#x\n", ntohl(inaddr.s_addr));

	return 0;
}
