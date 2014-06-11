#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	void *context = zmq_ctx_new();

	printf( "Connecting to hello world server...\n");
	
	void *requester = zmq_socket( context, ZMQ_REQ);
	zmq_connect( requester, "tcp://localhost:5555");
	
	for(int i = 0; i < 10; i++) {
		
		zmq_msg_t request;
		zmq_msg_init_size( &request, 5);
		memcpy( zmq_msg_data( &request), "Hello", 5);
		printf( "Sending Hello %d...", i);
		zmq_msg_send( &request, requester, 0);
		zmq_msg_close( &request);

		zmq_msg_t reply;
		zmq_msg_init( &reply);
		zmq_msg_recv( & reply, requester, 0);
		printf("Recieving World %d\n", i);
		zmq_msg_close( &reply);
	}

	sleep( 2);
	zmq_close( requester);
	zmq_ctx_destroy( context);
	return 0;
}
