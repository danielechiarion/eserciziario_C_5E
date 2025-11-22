#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    /* constant definition */
    const int SERVERPORT = 1450;
    const char SERVERADDRESS = "";

    /* define the struct for the address */
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(SERVERADDRESS);
    service.sin_port = SERVERPORT;

    /* variable definition */
    int systemcallOutput;
    int userChoice;

    /* create socket and connect it
    handling errors */
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd<0){
        printf("Creazione socket non riuscita");
        exit(1);
    }
    systemcallOutput = connect(socketfd, (struct sockaddr*)&service, sizeof(service));

    return 0;
}