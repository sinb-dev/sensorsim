//Include guard
#ifndef NETCODE_C
#define NETCODE_C
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define NETBUFFER 1024

int netsend(char* message) {
    char* host = "127.0.0.1";
    int sock = 0;//, valread;
    struct sockaddr_in serv_addr;
    
    char buffer[NETBUFFER] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("Unable to create socket on OS");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, host, &serv_addr.sin_addr)<=0) 
    {
        char *err = "";
        sprintf(err,"Host '%s' is invalid", host);
        error(err);
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Unable to connect to host");
        return -1;
    }
    send(sock , message , strlen(message) , 0 );
    
    //read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    close(sock);
    return 0;
}
#endif