#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void){
	//cria um socket
	
	int networ_socket;
	
	//primeiro parametro é o dominio, segundo o tipo, terceiro o protocolo
	//AF_INET - É IPv4 Internet protocol
	//SOCK_STREAM - fornece duas formas de conexao em streams de byte
	
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Garante que o socket foi criado
	if(network_access)
		printf("SOCKET CREATED %d\n", network_socket);
	// Especifica um endereço para o socket
	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);

	server_address.sin_addr.s_addr = INADDR_ANY;

	// Conexão para o socket
	// Primeiro parametro é o socket atual

	int connection_status;
	connection_status = connect(network_socket, (struct sockaddr *)(&server_address),sizeof(server_address));

	if(connection_status)
		printf("Connection_established = %d\n", connection_status);

	// Recebe informação do servidor
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// Imprime os dados recebidos do servidor
	printf("DATA_FORM_SERVER: %s\n", server_response);

	// Fecha o socket
	close(network_socket);

	return 0;
}	
