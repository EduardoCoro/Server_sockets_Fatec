#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)  /* Função de exibir erro */
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) /* Passado por argumentos */
{
    int sockfd, portno, n;  /* declaração das variaveis do tipo inteiro */
    struct sockaddr_in serv_addr; // Especifica um endereço para o socket
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]); /* verificar conexão e exibir o endereço da port */ 
       exit(0);
    }
	
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Cria um socket servidor */
	
	
    if (sockfd < 0) 
        error("ERROR opening socket"); // passando valores no parametro da função
    server = gethostbyname(argv[1]);
    if (server == NULL) {              // Garantindo se ocorre conexão com o host
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
	
	// conexão do socket
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) // verificar se existe erro de ligação 
        error("ERROR connecting"); // passando valores no parametro da função
    printf("Client: ");
	
	
    while(1)
    {
		// envia dados 
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0)         // verificar se têm passagem de write
             error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0)        // verificar se têm passagem de read
             error("ERROR reading from socket");
        printf("Server : %s\n",buffer);
        int i = strncmp("Bye" , buffer , 3);
        if(i == 0) // finalizando o a repetição
               break; 
    }
	// fecha o socket
    close(sockfd);
    return 0;
}
