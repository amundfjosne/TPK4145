
#include "Network/UDP.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>


#define BUFLEN 1024
#define SERVER_ADDRESS  "129.241.187.38"
#define BROADCAST_ADDRESS "#.#.#.255"
#define PORT 20012
#define WORKPLACE 12

int main(){
    int r_s, s_s;

    if (!UDP_create_socket(&s_s))
    {
        printf("Error_1.1\n");
    }

    if (!UDP_create_socket(&r_s))
    {
        printf("Error_1.2\n");
    }


    int enable = 1;


    struct sockaddr_in socket_s;
    struct sockaddr_in socket_r;

    if(!UDP_update_socket_struct(&socket_s, PORT, SERVER_ADDRESS))
    {
        printf("Error_2.1\n");
    }

    if(!UDP_update_socket_struct(&socket_r, PORT, BROADCAST_ADDRESS))
    {
        printf("Error_2.2\n");
    }

    setsockopt(s_s, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));
    setsockopt(r_s, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int));

    if(!UDP_bind_socket(&s_s, &socket_s))
    {
        printf("Error_3.1\n");
    }

    if(!UDP_bind_socket(&r_s, &socket_r))
    {
        printf("Error_3.2\n");
    }




    //char msg_buffer[BUFLEN] ={'1','2','3'};

    /*while (true) {
        //send the message
        if(!UDP_send_to_blocking(&s, msg_buffer, BUFLEN, &socket_1))
        {
            printf("Error_4\n");
        }

        memset(msg_buffer,'\0', BUFLEN);

        if(!UDP_recieve_from_blocking(&s, msg_buffer, BUFLEN, &socket_1))
        {
            printf("Error_5\n");
        }
        printf("%s\n", msg_buffer);
    }*/
    return 0;
}
