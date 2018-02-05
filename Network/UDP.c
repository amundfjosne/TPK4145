#include "UDP.h"

#include <stdio.h>
#include <string.h>


bool UDP_create_socket (int *new_socket)
{
    bool socket_created = false;
    if ((*new_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Can't create socket");
    }

    else
    {
        printf("Created socket\n");
        socket_created = true;
    }

    return socket_created;
}


bool UDP_update_socket_struct (struct sockaddr_in *socket_struct, int port, char *address)
{
    bool socket_updated = false;

    // zero out the structure
    memset((char *) &(*socket_struct), 0, sizeof(socket_struct));
    socket_struct->sin_family = AF_INET;

    socket_struct->sin_port = htons(port);
    if (inet_aton(address, &(*socket_struct).sin_addr) <0 )
    {
        perror("Error with inet_aton");
    }
    else
    {
        socket_updated=true;
    }

    return socket_updated;
}


bool UDP_bind_socket (int *socket, struct sockaddr_in* socket_struct)
{

    bool bound = false;
    if(bind(*socket , (struct sockaddr*)socket_struct, sizeof(*socket_struct)) < 0)
    {
        perror("Bind failed");
    }
    else
    {
        bound=true;
    }
    return bound;
}


bool UDP_recieve_from_blocking (int *socket, char buffer[], int buffer_length, struct sockaddr_in* socket_struct)
{
    bool received = false;
    socklen_t slen = sizeof(*socket_struct);
    if(recvfrom(*socket, buffer, strlen(buffer) , 0 , (struct sockaddr *) socket_struct, &slen) <0)
    {
        perror("Error with recvfrom");
    }
    else
    {
        received = true;
    }
    return received;
}

bool UDP_send_to_blocking (int *socket, char buffer[], int buffer_length, struct sockaddr_in* socket_struct)
{
    bool sent = false;

    if(sendto(*socket, buffer, strlen(buffer) , 0 , (struct sockaddr *) socket_struct, sizeof(*socket_struct)))
    {
        perror("Send failed");
    }
    else
    {
        sent = true;
    }
    return sent;
}


/*
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<arpa/inet.h>


#define SERVER_ADDRESS  "129.241.187.38"
#define BROADCAST_ADDRESS "#.#.#.255"
#define BUFLEN 1024
#define PORT 30000
#define WORKPLACE 12

 int main() {

   struct sockaddr_in si_recv, si_send;

   int send_s, recv_s, i, slen = sizeof(si_send) , recv_len;
   char buf[BUFLEN] = {'1','2','3'};
   // Create UDP Socket
   if ((send_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
     perror("Can't create socket");
     exit(-1);
    }
    else
    {
      printf("created socket\n");
    }



    // Create UDP Socket
    if ((recv_s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
      perror("Can't create socket2");
      exit(-1);
     }
     else
     {
       printf("created socket2\n");
     }


    // zero out the structure
    memset((char *) &si_recv, 0, sizeof(si_recv));

    si_recv.sin_family = AF_INET;
    si_recv.sin_port = htons(20012);
    inet_aton(BROADCAST_ADDRESS, &si_recv.sin_addr);

    memset((char *) &si_send, 0, sizeof(si_send));
    si_send.sin_family = AF_INET;
    si_send.sin_port = htons(20012);
    inet_aton(SERVER_ADDRESS, &si_send.sin_addr);


    setsockopt(recv_s, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    setsockopt(send_s, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    //bind socket to port
    bind(send_s , (struct sockaddr*)&si_send, sizeof(si_send));

    bind(recv_s , (struct sockaddr*)&si_recv, sizeof(si_recv));

    bool wait_for_address = true;


      char msg_buffer[BUFLEN] ={'1','2','3'};
      while (true) {
        //send the message
        sendto(send_s, msg_buffer, strlen(msg_buffer) , 0 , (struct sockaddr *) &si_send, slen);

        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        recvfrom(recv_s, buf, BUFLEN, 0, (struct sockaddr *) &si_recv, &slen);
        printf("%s\n", buf);
      }





      printf("finished\n");
  return 0;
}
*/
