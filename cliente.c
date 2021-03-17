#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

int main(int argc, char **argv){
  if(argc<2)
  { printf("<host> <puerto>\n");
    return 1;}

  struct sockaddr_in cliente;
  struct hostent *servidor; 
  servidor = gethostbyname(argv[1]); 
  if(servidor == NULL)


  { printf("Error en host.\n");
    return 1;}

  int puerto, conexion;
  char buffer[100];

  conexion = socket(AF_INET, SOCK_STREAM, 0);
  puerto=(atoi(argv[2])); 
  bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
        //La función bzero() es como memset() pero inicializando a 0 todas la variables


  cliente.sin_family = AF_INET;
  cliente.sin_port = htons(puerto); 
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
  //bcopy(); copia los datos del primer elemendo en el segundo con el tamaño máximo 



  //cliente.sin_addr = *((struct in_addr *)servidor->h_addr); //<--para empezar prefiero que se usen
  //inet_aton(argv[1],&cliente.sin_addr); //<--alguna de estas dos funciones
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)
  { printf("Error al conectar con el host\n");
    close(conexion);
    return 1;}

  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  //inet_ntoa(); está definida en <arpa/inet.h>
  printf("Escribir mensaje, aqui: ");
  fgets(buffer, 100, stdin);
  send(conexion, buffer, 100, 0);
  bzero(buffer, 100);
  recv(conexion, buffer, 100, 0); 
  printf("%s", buffer);


return 0;}