#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

int main()
{
	void *context = zmq_ctx_new();

	void *responder = zmq_socket( context, ZMQ_REP);
	zmq_bind( responder, "tcp://*:5555");

	while( 1) {
		
		char *msg = s_recv( responder);
		if ( msg != NULL) {
			printf("S received: %s\n", msg);
			free( msg);
			msg = NULL;
		} else 
			printf("S recieved: NULL\n");
		

		sleep( 1);

		s_send( responder, "PCJ");
	}

	zmq_close( responder);
	zmq_ctx_destroy( context);
	
	return 0;
}
