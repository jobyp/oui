#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct addrinfo addr_hint;
	struct addrinfo *a_info;
	char ipstr[INET6_ADDRSTRLEN];
	int ret;
	char *node;
	char *service;
	
	memset( &addr_hint, 0, sizeof( addr_hint));
	addr_hint.ai_family = AF_UNSPEC;
	addr_hint.ai_socktype = SOCK_STREAM;
	addr_hint.ai_flags = AI_PASSIVE;
	
	
	node = (argc > 1) ? argv[1] : NULL; 
	service = (argc > 2) ? argv[2] : "http";
	
	ret = getaddrinfo( node, service, &addr_hint, &a_info);
	if ( ret != 0) 
	{
		fprintf( stderr, "getaddrinfo error: %s\n",
			gai_strerror( ret));
		exit(1);
	}

	for(struct addrinfo *p = a_info; p != NULL; p = p->ai_next)
	{
		void *addr;
		char *ipver;

		if ( p->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4;
			ipv4 = (struct sockaddr_in *) p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else if ( p->ai_family == AF_INET6)
		{
			struct sockaddr_in6 *ipv6;
			ipv6 = (struct sockaddr_in6 *) p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}
		else
		{
			fprintf( stderr, "Unexpected value of 'ai_family'\n");
			exit( 1);
		}
		
		inet_ntop( p->ai_family, addr, ipstr, sizeof( ipstr));
		printf("%s: %s\n", ipver, ipstr);
	}
		
	freeaddrinfo( a_info);
	return 0;
}
