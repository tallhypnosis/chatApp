#include<iostream>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void error(const char* msg){
        perror(msg);
        exit(1);
}

int main(int argc, char *argv[]){
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;
        int  n;
        if(argc < 2){
                fprintf(stderr, "ERROR, no port provided\n");
                exit(1);
        }
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0)
                error("ERROR opening socket");


        bzero((char *) &serv_addr, size_of(serv_addr));

        portno = atoi(argv[1]);

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);


        if(bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0 )
                error("ERROR on binding");


        listen(sockfd, 5);


        clilen = sizeof(cli_addr);
        while(1){
                newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

                if( newsockfd < 0)
                        error("ERROR on accept");

                printf("server: got connection from %s port %d \n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

                int bytesRead = recv(newsockfd, buffer, sizeof(buffer), 0);

                if (bytesRead < 0 ){
                        error("ERROR reading the input");
                        close(newsockfd);
                        return -1;
			continue;
                } else if (bytesRead == 0){
                        printf("Connection close by the client");
                        close(newsockfd);
                        return 0;
			continue;
                } else {
                        buffer[bytesRead] = '\0';
                        printf("Received: %s", buffer);
                }

                char response[] = "Hello, client!";

                int bytesSent = send(newsockfd, response, sizeof(response), 0);

                if (bytesSent < 0){
                        error("ERROR sending the input");
                        close(newsockfd);
                        return -1;
			continue;
                } else {
                        printf("Data %d has been sent", bytesSent);
                }

                close(newsockfd);

        }

        close(sockfd);

        return 0;
}
