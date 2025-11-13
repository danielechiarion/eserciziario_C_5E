#include <stdio.h>      
#include <stdlib.h>    
#include <sys/socket.h> 
#include <sys/types.h>  
#include <netinet/in.h> 
#include <errno.h>      
#include <ctype.h>      
#include <unistd.h>
#include <stdbool.h>     

int main(){
    /* constant definition */
    const int SERVERPORT = 1450;

    /* struct definition */
    struct sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_addr.s_addr = htonl(INADDR_ANY);
    destination.sin_port = htons(SERVERPORT);

    /* start socket and connection with server */
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr*)&destination, sizeof(destination));

    /* get the string and write it */
    char stringa[50];
    printf("Inserisci la stringa: ");
    scanf("%s", stringa);

    write(socketfd, stringa, sizeof(stringa));

    /* read the result and 
    print them */
    bool result;
    read(socketfd, &result, sizeof(result));
    if(result)
        printf("La stringa e' stata ricevuta\n");
    else
        printf("La stringa non e' stata ricevuta\n");

    close(socketfd);

    return 0;
}