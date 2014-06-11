#include <zmq.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"

char* s_recv(void *socket)
{
	zmq_msg_t message;
	zmq_msg_init( &message);

	int size = zmq_msg_recv( &message, socket, 0);
	if ( size == -1)
		return NULL;

	char *string = malloc( size + 1);
	if ( string == NULL)
		return NULL;

	memcpy( string, zmq_msg_data( &message), size);
	zmq_msg_close( &message);
	string[size] = '\0';

	return string;
}

void s_send(void *socket, char *string)
{
	if ( string == NULL)
		return;

	size_t s_size = strlen( string);
	zmq_msg_t request;

	zmq_msg_init_size( &request, s_size);
	memcpy( zmq_msg_data( &request), string,  s_size);
	zmq_msg_send( &request, socket, 0);
	zmq_msg_close( &request);

	return;
}
