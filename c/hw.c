#include <stdio.h>
#include <stdint.h>

#include <arpa/inet.h>

int main()
{
	struct sockaddr_in sa;
	char ip4[INET_ADDRSTRLEN];
	struct sockaddr_in6 sa6;
	char ip6[INET6_ADDRSTRLEN];
	
	if ( inet_pton( AF_INET, 
			"192.168.0.3", 
			&(sa.sin_addr)) != 1)
		return 1;

	if ( inet_ntop( AF_INET, 
			&(sa.sin_addr), 
			ip4, 
			INET_ADDRSTRLEN) == ip4)
		printf("%s\n", ip4);
	else
		return 1;

	if ( inet_pton( AF_INET6, 
			"fe80::2202:afff:fedf:6dce", 
			&(sa6.sin6_addr)) != 1)
		return 1;

	if ( inet_ntop( AF_INET6, 
			&(sa6.sin6_addr), 
			ip6, 
			INET6_ADDRSTRLEN) == ip6)
		printf("%s\n", ip6);
	else
		return 1;

	return 0;
}
