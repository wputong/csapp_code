/*
 * 域名和它相关的IP地址之间的映射
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "wdebug.h"

#define	 BUFSIZE	(1024)

int main(int argc, char *argv[]) {
	if (argc != 2) {
		P_MSG("Usage:\t%s <domain name>\n", argv[0]);
		return -1;
	}

	struct addrinfo *rp, *result, hints;
	char buf[BUFSIZE];
	int rc = 0;
       	int flags;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((rc = getaddrinfo(argv[1], NULL, &hints, &result)) != 0) {
		fprintf(stderr, "getaddrinfo error:\t%s\n", gai_strerror(rc));
		return -1;
	}

	flags = NI_NUMERICHOST;	/*显示IP地址*/
	for (rp=result; rp!=NULL;rp=rp->ai_next) {
		rc = getnameinfo(rp->ai_addr, rp->ai_addrlen, buf, BUFSIZE, NULL, 0, flags);
		if (rc != 0) {
			fprintf(stderr, "getnameinfo error:\t%s\n", gai_strerror(rc));
			return -1;
		}
		printf("%s\t%s\n", argv[1], buf);
	}

	freeaddrinfo(result);

	return 0;
}
