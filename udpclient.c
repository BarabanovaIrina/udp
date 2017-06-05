//
//  main.c
//  udpclient
//
//  Created by Ira Barabanova on 28.05.17.
//  Copyright © 2017 Ira Barabanova. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int sock, bytes_recieved;;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char send_data[1024], recv_data[1024];
    
    host= (struct hostent *) gethostbyname((char *)"192.168.0.100");
    
    
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9005);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);
    
    while (1)
    {
        
        printf("\nType Something (q or Q to quit):");
        gets(send_data);
        
        if ((strcmp(send_data , "q") == 0) || strcmp(send_data , "Q") == 0)
            break;
        
        else
            sendto(sock, send_data, strlen(send_data), 0,
                   (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        
        bytes_recieved=recv(sock,recv_data,1024,0);
        recv_data[bytes_recieved] = '\0';
        
        if (strcmp(recv_data , "q") == 0 || strcmp(recv_data , "Q") == 0)
        {
            close(sock);
            break;
        }
        
        else
            printf("\nThank you for your message = [%s] " , recv_data);
            printf(" Size of your message is: %d" , strlen (recv_data));

        
    }
    
    
}
