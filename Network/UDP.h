#ifndef UDP_H
#define UDP_H

#include <sys/socket.h>
#include <stdbool.h>
#include <arpa/inet.h>

bool UDP_create_socket (int *new_socket);
bool UDP_update_socket_struct (struct sockaddr_in* socket_struct, int port, int address);
bool UDP_bind_socket (int *socket, struct sockaddr_in* socket_struct);
bool UDP_recieve_from (int *socket, char buffer[], int buffer_length, struct sockaddr_in* socket_struct /*, slen ?*/); //TODO: Should this take buffer as parameter or return recieved value?
bool UDP_send_to (int *socket, char buffer[], int buffer_length, struct sockaddr_in* socket_struct /*, slen ?*/);

#endif /*UDP_H*/
