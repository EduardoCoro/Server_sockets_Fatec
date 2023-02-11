#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) /* Função de exibir erro */
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) /* Passado por argumentos */
{
     int sockfd, newsockfd, portno; /* declaração das variaveis do tipo inteiro */
     socklen_t clilen;
     char buffer[255];
     struct sockaddr_in serv_addr, cli_addr; /* Criando e declarando os elementos da estrutura */ 
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");   /* verificar se existe conexao ou comunicação */
         exit(1); // efetivamente irá terminar o processo do programa e fechar.
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0); /* Cria um socket servidor */
	 
     if (sockfd < 0) 
        error("ERROR opening socket"); // passando valores no parametro da função
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
	 
	 /* Define o endereço do servidor */
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY; /* coloca IP automaticamente */
     serv_addr.sin_port = htons(portno);
	 
	 // Liga o socket em um endereço e a uma porta específica
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) // verificar se existe ligação do socket com o endereço ou algo espefico
              error("ERROR on binding");  // passando valores no parametro da função
		  
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	 
     if (newsockfd < 0) 
          error("ERROR on accept"); // passando valores no parametro da função
	  
     while(1)
     {
           bzero(buffer,256);
           n = read(newsockfd,buffer,255);
           if (n < 0) error("ERROR reading from socket"); // verificando se têm ligação 
           printf("Client: %s\n",buffer); // Envia os dados
          bzero(buffer,256);
          fgets(buffer,255,stdin);
          n = write(newsockfd,buffer,strlen(buffer));
           if (n < 0) error("ERROR writing to socket");
           int i=strncmp("Bye" , buffer, 3); 
           if(i == 0)
               break;
     }
	 
	 // fecha conexão do socket servidor
     close(newsockfd);
     close(sockfd);
     return 0; 
}
