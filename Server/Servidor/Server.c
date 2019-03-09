#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "PropServer.h"
#include "Utils.h"


int main() {

	 log("inicio servidor");

	 	  int sockfd, newsockfd, portno, clilen;
	      char buffer[256];
	      struct sockaddr_in serv_addr, cli_addr;
	      int n;
	      log("definicion variables");
	      sockfd = socket(AF_INET, SOCK_STREAM, 0);

	      if (sockfd < 0)
	         error("ERROR opening socket");
	      log("inicializacion del socket");

	      bzero((char *) &serv_addr, sizeof(serv_addr));
	      log("inicializa struct serv_addr");

	      serv_addr.sin_family = AF_INET;
	      log("inicializa sin family struct serv_addr");
	      serv_addr.sin_addr.s_addr = INADDR_ANY;
	      log("inicializa s_addr struct serv_addr");
	      serv_addr.sin_port = htons(PORT);
	      log("inicializa sin_port struct serv_addr");


	      if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	               error("ERROR on binding");
	      log("Enlaza el socket con el puerto");

	      listen(sockfd,5);
	      log("empieza a escuhar");
	      clilen = sizeof(cli_addr);
	      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	      log("aceptando conexiones");
	      if (newsockfd < 0)
	           error("ERROR on accept");
		  log("Inicia la escucha");
	      bzero(buffer,256);
	      n = read(newsockfd,buffer,255);

	      if (n < 0) error("ERROR reading from socket");
	      printf("Here is the message: %s\n",buffer);
	      log("lee datos");
	      n = write(newsockfd,"I got your message",18);

	      if (n < 0) error("ERROR writing to socket");
	      log("Escribe datos");

     return 0;
}
