#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string.h>
#include <stdlib.h>

int main()
{
	struct addrinfo addr_hint;
	struct addrinfo *a_info;
	int ret;
	
	memset( &addr_hint, 0, sizeof( addr_hint));
	addr_hint.ai_family = AF_UNSPEC;
	addr_hint.ai_socktype = SOCK_STREAM;
	addr_hint.ai_flags = AI_PASSIVE;
	
	ret = getaddrinfo( NULL, "3490", &addr_hint, &a_info);
	if ( ret != 0) 
	{
		fprintf( stderr, "getaddrinfo error: %s\n",
			gai_strerror( ret));
		exit(1);
	}

	
		
	freeaddrinfo( a_info);
	return 0;
}
