#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    /* define constants for the
    execution of the socke */
    const int SERVERPORT = 1450;
    /* define variables for
    the execution of the program */
    int socketfd, soa;
    char string[20];
    bool result;

    /* define the struct for the destination */
    struct sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_addr.s_addr = htonl(INADDR_ANY);
    destination.sin_port = htons(SERVERPORT);
    int destinationLength = sizeof(destination);

    /* create socket and bind the connection */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&destination, sizeof(destination));
    listen(socketfd, 2);

    /* create a while true cycle to
    process the request from clients */
    while (true)
    {
        soa = accept(socketfd, (struct sockaddr *)&destination, &destinationLength);
        read(soa, string, sizeof(string)); // read from the string
        fflush(stdout);

        result = strlen(string) > 0; // get the result of the string control

        /* print the string just to visualize
        the correct receiving from the client*/
        printf("Stringa ricevuta: %s\n", string);

        write(soa, &result, sizeof(result)); // send the result back to the client
        close(soa);
    }

    return 0;
}