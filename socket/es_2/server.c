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
    /* define constants for the 
    execution of the socke */
    const int SERVERPORT = 1450;

    /* define the struct for the destination */
    struct sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_addr.s_addr = htonl(INADDR_ANY);
    destination.sin_port = htons(SERVERPORT);

    return 0;
}