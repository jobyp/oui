#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "util.h"

int main()
{
	void *context = zmq_ctx_new();

	printf( "Connecting to hello world server...\n");
	
	void *requester = zmq_socket( context, ZMQ_REQ);
	zmq_connect( requester, "tcp://localhost:5555");
	
	for(int i = 0; i < 10; i++) {
		
		s_send( requester, "Hello");
		
		sleep( 1);
		
		char *data = s_recv( requester);
		if ( data) {

			printf( "C Received: %s\n", data);
			free( data);
			data = NULL;
		}
	}

	sleep( 2);
	zmq_close( requester);
	zmq_ctx_destroy( context);
	return 0;
}
